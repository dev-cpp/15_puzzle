#include "button.h"

Button::Button(QWidget *parent) : QPushButton(parent)
{
    this->setGeometry(QRect(QPoint(3, 3), QSize(85, 85)));
}

Button::Button(int posX, int posY, int id, QString picture, QWidget *parent) : QPushButton(parent)
{
    _id = id;
    this->setStyleSheet("QPushButton {"
                        "background-image: url("+picture+");"
                        "background-position: center;"
                        "border: none;"
                        "}");
    this->setGeometry(QRect(QPoint(posX, posY), QSize(85, 85)));
    connect(this,SIGNAL(clicked(bool)),this,SLOT(moveCoordinate()));
}

Button::~Button()
{

}

//Метод меняет id кнопки
void Button::setId(int id)
{
    _id = id;
}

//Метод меняет расположение кнопки на поле
void Button::changeButton(int posX, int posY)
{
    this->setGeometry(QRect(QPoint(posX, posY), QSize(85, 85)));
}

//Метод меняет расположение кнопки на поле и ее картинку
void Button::changeButton(int posX, int posY, int id, const QString picture)
{
    _id = id;
    this->setStyleSheet("QPushButton {"
                        "background-image: url("+picture+");"
                        "background-position: center;"
                        "border: none;"
                        "}");
    this->setGeometry(QRect(QPoint(posX, posY), QSize(85, 85)));
}

//Слот инициирует сигнал получения новых координат для кнопки
void Button::moveCoordinate()
{
    emit getCoordinate(_id);
    return;
}

//Слот перемещает кнопку по новым координатам на поле
void Button::move(int posX, int posY, int id)
{   
    if(_id == id)
    {
        this->setGeometry(QRect(QPoint(posX,posY), QSize(85, 85)));
    }
    return;
}
