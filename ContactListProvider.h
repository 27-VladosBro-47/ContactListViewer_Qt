#ifndef CONTACTLISTPROVIDER_H
#define CONTACTLISTPROVIDER_H

#include <QString>
#include <QDir>
#include <QFileDialog>
#include <QApplication>
#include <QMessageBox>

#include <QDebug>

#include <vector>
#include <fstream>
#include <algorithm>

#include "json-develop/single_include/nlohmann/json.hpp"

#include "Contact.h"



class ContactListProvider : public QWidget
{
    Q_OBJECT

private:

    // Вектор, що зберігає контакти
    std::vector<Contact*> Contacts;
    // Даний вектор слугує для передачі вказівників на контакти,
    // які необхідно буде відобразити на полотні
    std::vector<Contact*> *ChunkContainer;

    // Шлях до папки з виконавчим файлом програми
    QString exePath;
    // Шлях до бази даних (БД)
    QString pathToDirContacts;

    // Функція по очистці векторів
    void clearContacts()
    {
        if(Contacts.size()>0)
        {
            // ВИКЛИКАТИ СИГНАЛ ПО ОЧИСТЦІ ГРАФІЧНИХ ЕЛЕМЕНТІВ

            Contact::idGenerator = 0;
            for(auto &element : Contacts)
            {
                delete element;
            }
            Contacts.clear();
        }

        if(ChunkContainer != nullptr) { ChunkContainer->clear(); }
    }

    // Функція сортування за алфавітом
    void sortContacts()
    {
        std::sort(Contacts.begin(), Contacts.end(), [](Contact* obj1, Contact* obj2)
        {
            QString str1 = obj1->getName();
            QString str2 = obj2->getName();

            int result = QString::compare(str1, str2);

            if(QString::compare(str1, str2)==0)
            {
                QString str1 = obj1->getSurname();
                QString str2 = obj2->getSurname();

                int result = QString::compare(str1, str2);

                if(result < 0)
                { return true; }
                else
                { return false; }
            }
            else
            {
                if(result < 0)
                { return true; }
                else
                { return false; }
            }

        });
    }

public:
    // Необхідні для перевантаженої функції getChunk()
    enum Options
    {
        ALL = 0,
        FAVORITES = 1
    };

    ContactListProvider(QWidget *parent = Q_NULLPTR) : QWidget(parent)
    {
        exePath = QApplication::applicationDirPath() + "/";
        ChunkContainer = new std::vector<Contact*>;
    }

    ~ContactListProvider()
    {
        clearContacts();
    }

    // Отримання шляхів до каталогів із даними
    bool getNameOfDirContacts()
    {
        QString path = exePath + "ContactsData/";
        QString pathToDir = QFileDialog::getExistingDirectory(this, "Open Dir", path, QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);
        pathToDir+='/';

        // Створюю об'єкт для роботи з папкою із базою даних
        QDir *directory = new QDir(pathToDir);
        // Отримую дані про файли, що містяться у теці
        QFileInfoList infoListBase = directory->entryInfoList(QDir::AllEntries);

        if(infoListBase.size() == 4 && infoListBase[3].baseName() == "Photos" && infoListBase[2].baseName() == "ContactsList")
        {
            pathToDirContacts = pathToDir;
            return true;
        }
        else
        {
            QMessageBox::information(this, "Contacts", "Incorrect folder.");
            pathToDirContacts = "";
            return false;
        }

        delete directory;
    }

    // getChunk записує відібрані, за певним критерієм, контакти до ChunkContainer
    std::vector<Contact*>* getChunk(int index, int size)
    {
        if(ChunkContainer->size() > 0) { ChunkContainer->clear(); }

        assert(index >=0 && index < Contacts.size() && "getChunk: out_of_range");

        for(int i = 0; i < size; i++)
        {
            signalsetDisableButtons(Contacts[i]->getName().toStdString()[0], 0);
            ChunkContainer->push_back(Contacts[i]);
        }

        return ChunkContainer;
    }

    std::vector<Contact*>* getChunk( Options opt )
    {
        if(ChunkContainer->size() > 0) { ChunkContainer->clear(); }

        switch(opt)
        {
        case ALL:
        {
            for(auto &element : Contacts)
            {
                signalsetDisableButtons(element->getName().toStdString()[0], 0);
                ChunkContainer->push_back(element);
            }
            break;
        }
        case FAVORITES:
        {
            for(auto &element : Contacts)
            {
                if(element->getIsFavorite())
                {
                    signalsetDisableButtons(element->getName().toStdString()[0], 0);
                    ChunkContainer->push_back(element);
                }
            }
            break;
        }
        }
    }

    std::vector<Contact*>* getChunk(QString phrase)
    {
        if(ChunkContainer->size() > 0) { ChunkContainer->clear(); }

        for(auto &element : Contacts)
        {
            if(QString::compare(phrase.toLower(), (element->getName()+" "+element->getSurname()).left(phrase.size()).toLower() )==0)
            {
                signalsetDisableButtons(element->getName().toStdString()[0], 0);
                ChunkContainer->push_back(element);
            }
        }

        return ChunkContainer;
    }

    // Повертає кількість контактів, які містяться у Contacts
    int getQuantityOfContacts()
    {
        return Contacts.size();
    }

    // Отримую контакти з БД і записую до Contacts
    // Після цього, відразу відбувається сортування вектора
    void getContacts()
    {
        clearContacts();

        using json = nlohmann::json;
        std::ifstream file;
        json j;

        QString pathToContactsList = pathToDirContacts + "ContactsList.json";

        file.open(pathToContactsList.toStdString());

        if(!file.is_open())
        {
            QMessageBox::information(this, "Loading contacts data", "Contacts data has not been loading.");
            exit(-1);
        }

        j = json::parse(file);
        file.close();

        QString name, surname, phone, photo;
        int countOfContacts = j["Contacts"].size();
        for(int i = 0; i < countOfContacts; i++)
        {
            name = QString::fromStdString(j["Contacts"][i]["name"]);
            surname = QString::fromStdString(j["Contacts"][i]["surname"]);
            phone = QString::fromStdString(j["Contacts"][i]["phone"]);
            photo = pathToDirContacts + "Photos/" + QString::fromStdString(j["Contacts"][i]["photo"]);
            Contacts.push_back(new Contact(name, surname, phone, photo));
        }

        j.clear();

        sortContacts();
    }

    // Функція, що симулює дзвінок
    void call(int id)
    {
        for(auto &element : Contacts)
        {
            if(element->getId() == id)
            {
                emit signalSendDataToMainWin(element->getName()+ " " + element->getSurname(), element->getPhone(), element->getPhoto());
            }
        }
    }

signals:
    // Сигнал по відправці даних для вікна дзвінку
    void signalSendDataToMainWin(QString NameSurname, QString Phone, QString Photo);
    // Функція яка керує вкл/вимк кнопок "алфавітного пошуку"
    void signalsetDisableButtons(int codeOfSymbol, bool flag);

public slots:
    // У разі, якщо від сцени надходить сигнал на запит контактів
    // які необхідно відобразити, даний слот передасть необхідні контакти (через посилання)
    void slotSendPtrChunkContainer(std::vector<Contact*>*& GraphicChunkContainer)
    {
        GraphicChunkContainer = ChunkContainer;
    }
    // Якщо від сцени надходить сигнал на дзвінок,
    // даний слот розпочне процедуру дзвінка
    void slotCall(int id)
    {
        call(id);
    }

};

#endif // CONTACTLISTPROVIDER_H
