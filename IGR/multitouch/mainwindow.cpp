#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QTextEdit>
#include "strokedrawer.h"
#include "stroketraining.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QPolygonF polygon;
    QWidget * window = new QWidget(this);
    StrokeTraining * drawing = new StrokeTraining(this,polygon);
    drawing->setMinimumWidth(600);
    drawing->setMinimumHeight(500);
    drawing->setAutoFillBackground(true);

    ui->setupUi(this);

    setCentralWidget(window);

    //We add a vertical layout to the central widget
    QVBoxLayout * vLayout = new QVBoxLayout;
    QHBoxLayout * hLayout = new QHBoxLayout;


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

    QTextEdit * text = new QTextEdit("Salut beau gosse !");
    hLayout->addWidget(text);
    hLayout->addWidget(drawing);
    vLayout->addWidget(scrollArea);
    vLayout->addLayout(hLayout);

    window->setLayout(vLayout);
    window->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}
