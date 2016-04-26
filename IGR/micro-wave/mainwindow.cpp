#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include<QStateMachine>
#include <QTime>
#include <qtimer.h>
#include "Transitions.h"
#include <iostream>

static int countHeating = 0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->time = new QTime(0,1);
    this->clock = new QTime(0,0,0);
    this->timer = new QTimer(this);

    connect(this->timer, SIGNAL(timeout()), this, SLOT(increaseClock()));
    (this->timer)->start(1000);

    ui->setupUi(this);

    QStateMachine * microWave = new QStateMachine();
    QState * s1 = new QState();
    microWave->addState(s1);

    QState * defaultState = new QState(s1);

    QState * setTemp = new QState(s1);
    QState * setTime = new QState(s1);

    QState * heating = new QState(s1);


    QState * setWeight = new QState(s1);

    QState * setType = new QState(s1);

    QState * setHour = new QState(s1);
    QState * setMinute = new QState(s1);

    defaultState->addTransition(ui->paramButton,SIGNAL(clicked()),setTemp);
    setTemp->addTransition(ui->paramButton,SIGNAL(clicked()),setTime);
    setTime->addTransition(ui->startButton,SIGNAL(clicked()),heating);

    defaultState->addTransition(ui->startButton,SIGNAL(clicked()),heating);

    defaultState->addTransition(ui->defrostButton,SIGNAL(clicked()),setWeight);
    setWeight->addTransition(ui->startButton,SIGNAL(clicked()),heating);

    defaultState->addTransition(ui->modeButton,SIGNAL(clicked()),setType);
    setType->addTransition(ui->modeButton,SIGNAL(clicked()),setTime);

    defaultState->addTransition(ui->clockButton,SIGNAL(clicked()),setHour);
    setHour->addTransition(ui->clockButton,SIGNAL(clicked()),setMinute);
    setMinute->addTransition(ui->clockButton,SIGNAL(clicked()),defaultState);

    heating->addTransition(ui->startButton,SIGNAL(clicked()),heating);
    heating->addTransition((QObject *) time,SIGNAL(timeout()),defaultState);

    s1->addTransition(ui->stopButton,SIGNAL(clicked()),s1);

    QObject::connect(heating,SIGNAL(entered()),this,SLOT(enterHeating()));
    QObject::connect(defaultState,SIGNAL(entered()),this,SLOT(enterDefault()));

    s1->setInitialState(defaultState);

    microWave->setInitialState(s1);
    microWave->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enterHeating(){
    countHeating++;
    disconnect(this->timer, SIGNAL(timeout()), this, SLOT(displayClock()));
    if (countHeating == 1){
        this->time = new QTime(0,1);
        (ui->lcdNumber)->display((this->time)->toString("hh:mm:ss"));
        connect(this->timer, SIGNAL(timeout()), this, SLOT(increaseTime()));
    } else{
        *(this->time) = (this->time)->addSecs(60);
    }

}

void MainWindow::increaseTime(){
    *(this->time) = (this->time)->addSecs(-1);
    (ui->lcdNumber)->display((this->time)->toString("hh:mm:ss"));
    if((this->time)->toString("mm:ss")=="00:00"){
       disconnect(this->timer, SIGNAL(timeout()),this,SLOT(increaseTime()));
       (ui->lcdNumber)->display("00:00:00");
    }
}

void MainWindow::enterDefault(){
    disconnect(this->timer, SIGNAL(timeout()),this,SLOT(increaseTime()));
    connect(this->timer,SIGNAL(timeout()),this,SLOT(displayClock()));
    countHeating = 0;
}

void MainWindow::increaseClock(){
    *(this->clock)=(this->clock)->addSecs(1);
}

void MainWindow::displayClock(){
    (ui->lcdNumber)->display((this->clock)->toString("hh:mm:ss"));
}

