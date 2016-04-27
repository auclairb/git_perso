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
    StrokeTraining * drawing = new StrokeTraining(this);
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
    QPushButton * submitButton = new QPushButton("Submit",drawing);
    submitButton->resize(100,50);


    scrollingWidget->setLayout(scrollingLayout);

    //We add a widget to the scrollArea
    scrollArea->setWidget(scrollingWidget);
    scrollArea->setWidgetResizable(true);

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
