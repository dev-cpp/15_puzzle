#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    _ui->groupBox->setStyleSheet("QGroupBox {"
                                "border-style: solid;"
                                "border-width: 2px;"
                                "border-color: black;"
                                "background-color: silver;"
                                "}");

    _game = new Game("Classic", _ui->groupBox);
    connect(_ui->newGameButton,SIGNAL(clicked(bool)),_game,SLOT(newGame()));
    connect(this,SIGNAL(gameType(QString)),_game,SLOT(gameType(QString)));

    connect(_ui->classic,SIGNAL(triggered(bool)),this,SLOT(classicGame()));
    connect(_ui->gelik,SIGNAL(triggered(bool)),this,SLOT(gelikGame()));
}

MainWindow::~MainWindow()
{
    delete _ui;
}

//Слот отправляет сигнал для изменения вида игры на классический
void MainWindow::classicGame()
{
    emit gameType("Classic");
    return;
}

//Слот отправляет сигнал для изменения вида игры на гелик
void MainWindow::gelikGame()
{
    emit gameType("Gelik");
    return;
}
