#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void gameType(const QString str);

public slots:
    void classicGame();
    void gelikGame();

private:
    Ui::MainWindow* _ui;
    Game* _game;
};

#endif // MAINWINDOW_H
