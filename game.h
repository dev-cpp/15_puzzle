#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QString>
#include <QVector>
#include <QTime>
#include <QMessageBox>

#include "button.h"

struct matrixElement
{
    int id;
    QPoint point;
};

class Game : public QWidget
{
    Q_OBJECT
public:
    explicit Game(const QString str, QWidget *parent = nullptr);
    ~Game();
    void initButtons(const QString str);
    bool mixArray();
    void checkWin();

signals:
    void sendCoordinate(int posX, int posY, int id);

public slots:
    void findCoordinate(int id);
    void gameType(const QString str);
    void newGame();

private:
    QVector<Button*> _buttons;    //массив кнопок
    matrixElement _matrix[4][4];  //матрица координат и id кнопок
    int _basicArray[16];          //базовый массив
};

#endif // GAME_H
