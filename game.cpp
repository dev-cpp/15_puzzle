#include "game.h"

Game::Game(const QString str, QWidget *parent) : QWidget(parent)
{
    for(int i = 0; i < 16; ++i)
        _basicArray[i] = i;
    initButtons(str);
}

Game::~Game()
{
    foreach(Button* btn, _buttons)
    {
        disconnect(btn,SIGNAL(getCoordinate(int)),this,SLOT(findCoordinate(int)));
        disconnect(this,SIGNAL(sendCoordinate(int,int,int)),btn,SLOT(move(int,int,int)));
        delete btn;
    }
}

//Метод создает кнопки и структуру координат игрового поля
void Game::initButtons(const QString str)
{
    _buttons.push_back(new Button(3, 3, 1, ":/buttons/"+str+"/1.png", this));
    _buttons.push_back(new Button(89, 3, 2, ":/buttons/"+str+"/2.png", this));
    _buttons.push_back(new Button(175, 3, 3, ":/buttons/"+str+"/3.png", this));
    _buttons.push_back(new Button(261, 3, 4, ":/buttons/"+str+"/4.png", this));
    _buttons.push_back(new Button(3, 89, 5, ":/buttons/"+str+"/5.png", this));
    _buttons.push_back(new Button(89, 89, 6, ":/buttons/"+str+"/6.png", this));
    _buttons.push_back(new Button(175, 89, 7, ":/buttons/"+str+"/7.png", this));
    _buttons.push_back(new Button(261, 89, 8, ":/buttons/"+str+"/8.png", this));
    _buttons.push_back(new Button(3, 175, 9, ":/buttons/"+str+"/9.png", this));
    _buttons.push_back(new Button(89, 175, 10, ":/buttons/"+str+"/10.png", this));
    _buttons.push_back(new Button(175, 175, 11, ":/buttons/"+str+"/11.png", this));
    _buttons.push_back(new Button(261, 175, 12, ":/buttons/"+str+"/12.png", this));
    _buttons.push_back(new Button(3, 261, 13, ":/buttons/"+str+"/13.png", this));
    _buttons.push_back(new Button(89, 261, 14, ":/buttons/"+str+"/14.png", this));
    _buttons.push_back(new Button(175, 261, 15, ":/buttons/"+str+"/15.png", this));

    foreach(Button* btn, _buttons)
    {
        btn->setDisabled(true);
        connect(btn,SIGNAL(getCoordinate(int)),this,SLOT(findCoordinate(int)));
        connect(this,SIGNAL(sendCoordinate(int,int,int)),btn,SLOT(move(int,int,int)));
    }

    int coordY = 3;
    int id = 1;
    for(int i = 0; i < 4; ++i)
    {
        int coordX = 3;
        for(int j = 0; j < 4; ++j)
        {
            _matrix[i][j].id = id;
            _matrix[i][j].point.setX(coordX);
            _matrix[i][j].point.setY(coordY);
            coordX += 86;
            ++id;
        }
        coordY += 86;
    }
    _matrix[3][3].id = 0;
}

//Метод перемешивает базовый массив и проверяет существование решения
bool Game::mixArray()
{
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    int id = 0;
    int rand = 0;
    for(int i = 0; i < 16; ++i)
    {
        rand = qrand() % 16;
        id = _basicArray[i];
        _basicArray[i] = _basicArray[rand];
        _basicArray[rand] = id;
    }
    int inv = 0;   //колличество инвариантов
    for(int i = 0; i < 16; ++i)
    {
        if(_basicArray[i])
        {
            for(int j = 0; j < i; ++j)
            {
                if(_basicArray[j] > _basicArray[i])
                {
                    ++inv;
                }

            }
        }
    }
    for(int i = 0; i < 16; ++i)
    {
        if(_basicArray[i] == 0)
            inv += 1 + i / 4;
    }

    if(!(inv % 2))
    {
        return true;
    }
    else
    {
        int tmp = 0;
        int rand1 = qrand() % 16;
        int rand2 = qrand() % 16;
        while(rand1 == rand2)
            rand2 = qrand() % 16;
        tmp = _basicArray[rand1];
        _basicArray[rand1] = _basicArray[rand2];
        _basicArray[rand2] = tmp;
    }

    inv = 0;
    for(int i = 0; i < 16; ++i)
    {
        if(_basicArray[i])
        {
            for(int j = 0; j < i; ++j)
            {
                if(_basicArray[j] > _basicArray[i])
                {
                    ++inv;
                }

            }
        }
    }
    for(int i = 0; i < 16; ++i)
    {
        if(_basicArray[i] == 0)
            inv += 1 + i / 4;
    }
    if(!(inv % 2))
    {
        return true;
    }
    else
        mixArray();
    return false;
}

//Метод проверяет выигрыш
void Game::checkWin()
{
    int index = 0;
    int sum = 0;
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            if(_matrix[i][j].id == _basicArray[index])
            {
                ++sum;
                ++index;
            }
        }
    }
    if(sum == 16)
    {
        QMessageBox::information(this, "Победа", "<h1 align=\"center\"><u><i>Победа!!!</i></u></h1>");
        foreach(Button* btn, _buttons)
        {
            btn->setDisabled(true);
        }
    }
}

//Слот ищет координаты для перемещения кнопки
void Game::findCoordinate(int id)
{
    int iButtonIndex = 0;
    int jButtonIndex = 0;
    int iEmptyIndex = 0;
    int jEmptyIndex = 0;
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            if(_matrix[i][j].id == 0)
            {
                iEmptyIndex = i;
                jEmptyIndex = j;
            }
            if(_matrix[i][j].id == id)
            {
                iButtonIndex = i;
                jButtonIndex = j;
            }
        }
    }
    int indexIHigh = iButtonIndex - 1;
    int indexILow = iButtonIndex + 1;
    int indexJHigh = jButtonIndex - 1;
    int indexJLow = jButtonIndex + 1;
    if(iEmptyIndex == iButtonIndex && (indexJHigh == jEmptyIndex || indexJLow == jEmptyIndex))
    {
        emit sendCoordinate(_matrix[iEmptyIndex][jEmptyIndex].point.x(), _matrix[iEmptyIndex][jEmptyIndex].point.y(), id); //сигнал отсылает координаты кнопке
        _matrix[iEmptyIndex][jEmptyIndex].id = id;
        _matrix[iButtonIndex][jButtonIndex].id = 0;
        checkWin();
        return;
    }
    else if(jEmptyIndex == jButtonIndex && (indexIHigh == iEmptyIndex || indexILow == iEmptyIndex))
    {
        emit sendCoordinate(_matrix[iEmptyIndex][jEmptyIndex].point.x(), _matrix[iEmptyIndex][jEmptyIndex].point.y(), id);  //сигнал отсылает координаты кнопке
        _matrix[iEmptyIndex][jEmptyIndex].id = id;
        _matrix[iButtonIndex][jButtonIndex].id = 0;
        checkWin();
        return;
    }
    return;
}

//Слот меняет вид игры
void Game::gameType(const QString str)
{
    _buttons[0]->changeButton(3, 3, 1, ":/buttons/"+str+"/1.png");
    _buttons[1]->changeButton(89, 3, 2, ":/buttons/"+str+"/2.png");
    _buttons[2]->changeButton(175, 3, 3, ":/buttons/"+str+"/3.png");
    _buttons[3]->changeButton(261, 3, 4, ":/buttons/"+str+"/4.png");
    _buttons[4]->changeButton(3, 89, 5, ":/buttons/"+str+"/5.png");
    _buttons[5]->changeButton(89, 89, 6, ":/buttons/"+str+"/6.png");
    _buttons[6]->changeButton(175, 89, 7, ":/buttons/"+str+"/7.png");
    _buttons[7]->changeButton(261, 89, 8, ":/buttons/"+str+"/8.png");
    _buttons[8]->changeButton(3, 175, 9, ":/buttons/"+str+"/9.png");
    _buttons[9]->changeButton(89, 175, 10, ":/buttons/"+str+"/10.png");
    _buttons[10]->changeButton(175, 175, 11, ":/buttons/"+str+"/11.png");
    _buttons[11]->changeButton(261, 175, 12, ":/buttons/"+str+"/12.png");
    _buttons[12]->changeButton(3, 261, 13, ":/buttons/"+str+"/13.png");
    _buttons[13]->changeButton(89, 261, 14, ":/buttons/"+str+"/14.png");
    _buttons[14]->changeButton(175, 261, 15, ":/buttons/"+str+"/15.png");

    foreach(Button* btn, _buttons)
    {
        btn->setDisabled(true);
    }

    int id = 1;
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            _matrix[i][j].id = id;
            ++id;
        }
    }
    _matrix[3][3].id = 0;
}

//Слот начинает новую игру
void Game::newGame()
{
    if(mixArray())
    {
        int index = 0;
        for(int i = 0; i < 4; ++i)
        {
            for(int j = 0; j < 4; ++j)
            {
                _matrix[i][j].id = _basicArray[index];
                if(_matrix[i][j].id)
                    _buttons[_matrix[i][j].id - 1]->changeButton(_matrix[i][j].point.x(), _matrix[i][j].point.y());
                ++index;
            }
        }
    }
    foreach(Button* btn, _buttons)
    {
        btn->setEnabled(true);
    }
    //заполняем массив выигрышней комбинацией для дальнейших сравнений
    for(int i = 0; i < 16; ++i)
        _basicArray[i] = i + 1;
    _basicArray[15] = 0;
}

