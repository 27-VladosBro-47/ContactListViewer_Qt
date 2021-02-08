#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QPointF>

#include <QDebug>

#include <vector>

#include "ContactListProvider.h"


enum FiguresType
{
    SQUARE = 0,
    RECTANGE = 1
};



class Scene : public QGraphicsScene
{
    Q_OBJECT

private:
    const int minWidth = 361;
    const int minHeight = 431;

    FiguresType type = RECTANGE;


    // Клас, який містить необхідні елементи для відображення контакту
    // і також зберігає вказівник userContact на контакт з ContactListProvider

    //----------GraphicsElementsOfContact----------
    class GraphicsElementsOfContact
    {
    private:
        const int standartWidthSquare = 100;
        const int standartHeightSquare = 100;
        const int standartHeightRectangle = 80;
        // standartWidthRectangle sets relatively scene`s width
    public:
        Contact* userContact;
        int positionX = 0, positionY = 0;

        // Осноний прямокутник\квадрат
        QGraphicsRectItem *mainRect = nullptr;

        // Фотографія контакту
        QPixmap *pixmapIcon = nullptr;
        QGraphicsPixmapItem *icon = nullptr;

        // Ім'я та прізвище контакту
        QGraphicsTextItem *name = nullptr;

        // Активна зона (при натиснені на неї - здійснюється дзвінок)
        // зона є прозорою
        QGraphicsRectItem *activeZone = nullptr;

        // Іконка "Вибране"
        // При натисненні - контакт додається до вибраного
        QPixmap *pixmapStar = nullptr;
        QGraphicsPixmapItem *iconStar = nullptr;


    GraphicsElementsOfContact(FiguresType Type, int currentWidthOfScene, Contact*& userC)
    {
        this->userContact = userC;

        //========//
        mainRect = new QGraphicsRectItem(0,0, currentWidthOfScene - 40 , 80);
        mainRect->setBrush(QColor(255,127,39));
        mainRect->setPen(QColor(255,127,39));
        //========//
        pixmapIcon =  new QPixmap();
        if(!pixmapIcon->load(userContact->getPhoto()))
        {
            QMessageBox::critical(0, "pixmapIcon", "GraphicsElementsOfContact() cannot loading pixmapIcon image");
        }
        icon = new QGraphicsPixmapItem(*pixmapIcon);
        //========//
        name = new QGraphicsTextItem(userContact->getName()+" "+userContact->getSurname());
        //========//
        activeZone = new QGraphicsRectItem(0,0, currentWidthOfScene - 40 , 80);
        //========//
        pixmapStar =  new QPixmap();
        QString pathToIcon;
        if(userContact->getIsFavorite())
        { pathToIcon = QApplication::applicationDirPath() + "/Data/Icon/star_active.png"; }
        else
        { pathToIcon = QApplication::applicationDirPath() + "/Data/Icon/star_inactive.png"; }

        if(!pixmapStar->load(pathToIcon))
        {
            QMessageBox::critical(0, "pixmapIcon", "GraphicsElementsOfContact() cannot loading pixmapIcon image");
        }
        iconStar = new QGraphicsPixmapItem(*pixmapStar);
        //========//

        setFiguresType(Type, currentWidthOfScene);
    }

    // Функція трансформує контакт у "прямокутник" чи "квадрат"
    void setFiguresType(FiguresType Type, int currentWidthOfScene)
    {
        switch(Type)
        {
        case SQUARE:
        {
            mainRect->setRect(0,0, standartWidthSquare, standartHeightSquare);
            activeZone->setRect(0,0, standartWidthSquare, standartHeightSquare);
            break;
        }
        case RECTANGE:
        {
            mainRect->setRect(0,0, currentWidthOfScene-30, standartHeightRectangle);
            activeZone->setRect(0,0, currentWidthOfScene-30, standartHeightRectangle);
            break;
        }
        }
    }

    // Функція задає положення едементів контакту (зображення, текст, іконка, активна зона)
    // відносно лівого верхнього кута основного прямокутника\квадрату
    void setPositionsOfFigure(FiguresType Type, int X, int Y)
    {
        positionX = X;
        positionY = Y;

        switch(Type)
        {
        case SQUARE:
        {
            mainRect->setPos(X,Y);
            icon->setPos(X+20,Y+3);
            name->setPos(-100,-100);
            activeZone->setPos(X,Y);
            iconStar->setPos(X+35,Y+67);
            break;
        }
        case RECTANGE:
        {
            mainRect->setPos(X,Y);
            icon->setPos(X+10,Y+10);
            name->setPos(X+120,Y+30);
            activeZone->setPos(X,Y);
            iconStar->setPos(X+80,Y+25);
            break;
        }
        }

    }

    ~GraphicsElementsOfContact()
    {
        delete mainRect;
        delete pixmapIcon ;
        delete icon;
        delete name;
        delete activeZone;
        delete pixmapStar;
        delete iconStar;
    }

    };
    //----------GraphicsElementsOfContact----------

    // Вектор, що зберігає графічні елементи
    std::vector<GraphicsElementsOfContact*> Elements;

    // Буферний вектор для отримання контактів з ContactListProvider
    // отримує вектор вказівників ChunkContainer класу ContactListProvider
    std::vector<Contact*> *GraphicsChunkContainer;

public:
    explicit Scene(QGraphicsScene* parent = 0);
    ~Scene();

    // Функція ініціалізує Elements за допомогою даних з GraphicsChunkContainer
    // і відображає необхідні контакти
    void setContacts()
    {
        initializationElements();
        addElementsToScene();
        setPosition();
    }

    // За допомогою події мишки
    // активуються дзвінки і додавання/видалення з "Вибраного"
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        if(event->button() == Qt::LeftButton && items(QPointF(event->scenePos().x(), event->scenePos().y())).size() != 0)
        {
            for(int i = 0; i < Elements.size(); i++)
            {
                // Clicked on ActiveZone
                if(Elements[i]->activeZone == items(QPointF(event->scenePos().x(), event->scenePos().y())).first())
                {
                    emit signalCall(Elements[i]->userContact->getId());
                }
                // Clicked on IconStar
                if(Elements[i]->iconStar == items(QPointF(event->scenePos().x(), event->scenePos().y())).first())
                {
                    changeFavorite(i);
                }
            }
        }
    }

    // Додавання/Вилучення з "Вибраного"
    void changeFavorite(int index)
    {
        if(Elements[index]->userContact->getIsFavorite())
        {
            Elements[index]->userContact->setIsFavorite(false);
            setStar(index, false);
        }
        else
        {
            Elements[index]->userContact->setIsFavorite(true);
            setStar(index, true);
        }
    }

    // Встановлення необхідної іконки "Вибране"
    void setStar(int index, bool status)
    {
        QString pathToIcon;
        if(status)
        { pathToIcon = QApplication::applicationDirPath() + "/Data/Icon/star_active.png"; }
        else
        { pathToIcon = QApplication::applicationDirPath() + "/Data/Icon/star_inactive.png"; }

        if(!Elements[index]->pixmapStar->load(pathToIcon))
        {
            QMessageBox::critical(0, "pixmapIcon", "setStar() cannot loading pixmapIcon image");
        }
        Elements[index]->iconStar->setPixmap(*Elements[index]->pixmapStar);

    }

    // Ініціалізація Elements
    void initializationElements()
    {
        for(auto &element : Elements) { delete element; }
        Elements.clear();

        emit signalGetPtrChunkContainer(GraphicsChunkContainer);

        int i = 0;
        for(auto &element : *GraphicsChunkContainer)
        {
            Elements.push_back(new GraphicsElementsOfContact(type, width(), element));
        }
    }

    // Додавання елементів контакту на сцену
    void addElementsToScene()
    {
        for(auto &element : Elements)
        {
            addItem(element->mainRect);
            addItem(element->icon);
            addItem(element->name);
            addItem(element->activeZone);
            addItem(element->iconStar);
        }
    }

    // Задає місцеположення на сцені для об'єктів сцени
    void setPosition()
    {
        int baseX = 5, baseY = 5;

            int currWidth;
            int currHeight;

            emit signalGetCurrWidthHeight(currWidth, currHeight);

            int countX = 0;
            int countY = 0;

            int size = Elements.size();

            switch(type)
            {
            case SQUARE:
            {
                countX = currWidth / 110;
                countY = ceil(size / (float)countX);

                if(110*countY>minHeight) { setSceneRect(0.0,0.0, currWidth, 110*countY); }
                if(110*countY<currHeight) { setSceneRect(0.0,0.0, currWidth, currHeight); }

                int count = 0;
                for (int y = 0; y < countY; y++)
                {
                    for (int x = 0; x < countX; x++)
                    {
                        if (count < size)
                        {
                            int X = baseX, Y = baseY;
                            X += 110 * x;
                            Y += 110 * y;
                            Elements[count]->setFiguresType(type, currWidth);
                            Elements[count]->setPositionsOfFigure(type, X, Y);
                            count++;
                        }
                    }
                }

                break;
            }
            case RECTANGE:
            {
                if(90*size>minHeight) { setSceneRect(0.0,0.0, currWidth, 90*size); }
                if(90*size<currHeight) { setSceneRect(0.0,0.0, currWidth, currHeight); }

                for(int count = 0; count < size; count++)
                {
                    int X = baseX, Y = baseY;
                    Y+= 90 * count;

                    Elements[count]->setFiguresType(type, currWidth);
                    Elements[count]->setPositionsOfFigure(type, X, Y);
                }
                break;
            }
            }
    }

    // Функція поіертає true, якщо Elements порожній
    // інакше - false
    bool isEmpty()
    {
        if(Elements.size()==0){ return true; }
        else { return false; }

    }

    // Функція, для змінни типу фігур "прямокутник"/"увадрат"
    void setFiguresType(bool arg)
    {
        emit signalSetCenterOn(0,0);
        if(arg){ type = RECTANGE; } else { type = SQUARE; }
        setPosition();
    }

public slots:

signals:
    void signalGetPtrChunkContainer(std::vector<Contact*>*& GraphicChunkContainer);
    void signalCall(int id);
    void signalGetCurrWidthHeight(int& W, int&H);
    void signalSetCenterOn(int W, int H);

};



#endif // SCENE_H
