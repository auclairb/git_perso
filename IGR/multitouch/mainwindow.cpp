#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QBoxLayout>
#include <QScrollArea>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QWidget * window = new QWidget();
    ui->setupUi(this);

    setCentralWidget(window);

    //We add a vertical layout to the central widget
    QVBoxLayout * vLayout = new QVBoxLayout;


    //ScrollArea creation
    QScrollArea * scrollArea = new QScrollArea();
    QWidget * scrollingWidget = new QWidget();



    //We add a horizontal layout to the widget of the scrollArea
    QHBoxLayout * scrollingLayout = new QHBoxLayout();

    //Add some buttons
    QPushButton * totoButton = new QPushButton("toto");
    totoButton->resize(100,50);
    QPushButton * helloButton = new QPushButton("hello !");
    helloButton->resize(100,50);
    QPushButton * hello1Button = new QPushButton("hello !");
    hello1Button->resize(100,50);
    QPushButton * hello2Button = new QPushButton("hello !");
    hello2Button->resize(100,50);
    QPushButton * hello3Button = new QPushButton("hello !");
    hello3Button->resize(100,50);
    QPushButton * hello4Button = new QPushButton("hello !");
    hello4Button->resize(100,50);

    scrollingLayout->addWidget(totoButton);
    scrollingLayout->addWidget(helloButton);
    scrollingLayout->addWidget(hello1Button);
    scrollingLayout->addWidget(hello2Button);
    scrollingLayout->addWidget(hello3Button);
    scrollingLayout->addWidget(hello4Button);

    scrollingWidget->setLayout(scrollingLayout);

    //We add a widget to the scrollArea
    scrollArea->setWidget(scrollingWidget);
    scrollArea->setWidgetResizable(true);

    vLayout->addWidget(scrollArea);

    window->setLayout(vLayout);
    window->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}
