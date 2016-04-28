#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QScrollArea>
#include <QPushButton>
#include <QTextEdit>
#include "strokedrawer.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    QWidget * window = new QWidget(this);
    QPolygonF polygon;
    drawing = new StrokeTraining();
    drawing->setMinimumWidth(600);
    drawing->setMinimumHeight(500);

    ui->setupUi(this);

    setCentralWidget(window);

    //We add a vertical layout to the central widget
    QVBoxLayout * vLayout = new QVBoxLayout;
    QHBoxLayout * hLayout = new QHBoxLayout;

    //ScrollArea creation
    QScrollArea * scrollArea = new QScrollArea();
    QWidget * scrollingWidget = new QWidget();


    //We add a horizontal layout to the widget of the scrollArea
    scrollingLayout = new QHBoxLayout();

    //Add some buttons
    QPushButton * submitButton = new QPushButton("Submit");
    submitButton->resize(100,50);
    connect(submitButton,SIGNAL(clicked()),drawing,SLOT(submit()));
    connect(submitButton,SIGNAL(clicked()),this,SLOT(move()));
    connect(submitButton,SIGNAL(clicked()),drawing,SLOT(erase()));

    QPushButton * eraseButton = new QPushButton("Erase");
    submitButton->resize(100,50);
    connect(eraseButton,SIGNAL(clicked()),drawing,SLOT(erase()));

    QHBoxLayout * buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(submitButton);
    buttonLayout->addWidget(eraseButton);

    scrollingWidget->setLayout(scrollingLayout);

    //We add a widget to the scrollArea
    scrollArea->setWidget(scrollingWidget);
    scrollArea->setWidgetResizable(true);

    hLayout->addWidget(drawing);
    vLayout->addWidget(scrollArea);
    vLayout->addLayout(hLayout);
    vLayout->addLayout(buttonLayout);

    window->setLayout(vLayout);
    window->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::move(){
    /*StrokeDrawer * templaBuff = new StrokeDrawer;
    templaBuff->setStroke(drawing->getStroke());
    if((!templaBuff->getStroke())->isEmpty()){
        templa.append(templaBuff);
        scrollingLayout->addWidget(templa.back());
    }*/
    GestureTemplate polygon = GestureTemplate(drawing->getStroke());
    if (!polygon.isEmpty()){
        polygon.normalize();
        polygon=GestureTemplate(polygon.scaleToSquare(polygon));
        polygon.translate(QPoint(125,125));
        gestureTemplate.append(polygon);
        StrokeDrawer * templaBuff = new StrokeDrawer;
        templaBuff->setStroke(gestureTemplate.back());
        scrollingLayout->addWidget(templaBuff);
    }
}
