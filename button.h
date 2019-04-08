#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class Button : public QPushButton
{
    Q_OBJECT

public:
    Button(QWidget *parent = nullptr);    
    Button(int posX, int posY, int id, QString picture, QWidget *parent = nullptr);
    ~Button();
    void setId(int id);
    void changeButton(int posX, int posY);
    void changeButton(int posX, int posY, int id, const QString picture);

signals:
    void getCoordinate(int id);

public slots:
    void moveCoordinate();
    void move(int posX, int posY, int id);

private:
    int _id;
};

#endif // BUTTON_H
