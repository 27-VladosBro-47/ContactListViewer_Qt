#ifndef CONTACT_H
#define CONTACT_H

#include <QString>

// Клас, який зберігає дані про певний контакт
class Contact
{
private:
    const int id;

    bool isFavorite;

    QString name;
    QString surname;
    QString phone;
    QString photo;


public:
    static int idGenerator;

    Contact(QString Name, QString Surname, QString Phone, QString Photo)
        : id(idGenerator++), isFavorite(false), name(Name), surname(Surname), phone(Phone), photo(Photo)
    {

    }

    ~Contact()
    {

    }

    const int getId() { return id; }
    bool getIsFavorite() { return isFavorite; }
    QString getName() { return name; }
    QString getSurname() { return surname; }
    QString getPhone() { return phone; }
    QString getPhoto() { return photo; }

    void setIsFavorite(bool flag) { isFavorite = flag; }
};

#endif // CONTACT_H
