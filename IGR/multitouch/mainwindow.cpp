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

    QWidget * window = new QWidget(this);
    QPolygonF polygon;
    StrokeTraining * drawing = new StrokeTraining();
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
    QHBoxLayout * scrollingLayout = new QHBoxLayout();

    //Add some buttons
    QPushButton * submitButton = new QPushButton("Submit");
    submitButton->resize(100,50);
    connect(submitButton,SIGNAL(clicked()),drawing,SLOT(submit()));

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
