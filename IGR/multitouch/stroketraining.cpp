#include "stroketraining.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include "mainwindow.h"
#include <QList>
#include <QVector>

StrokeTraining::StrokeTraining(QWidget * parent, QPolygonF gesture_new):StrokeDrawer(gesture_new) {
    point1 = QPoint(0,0);
    point2 = QPoint(0,0);
    point3 = QPoint(0,0);
    point4 = QPoint(0,0);

    path = QPainterPath();

    index = QVector<int>();

    penWidth = 2;
    penColor = "black";
    penStyle = Qt::SolidLine;
    chosenForm = 1;
    pathsList = QList< QPair<QPainterPath,QPen> > {};

    mousePress=false;
    mouseRightPress = false;

    selectionFirstClick = true;
}

void StrokeTraining::setList(QList<QPair<QPainterPath,QPen> > list) {
    pathsList = QList< QPair<QPainterPath,QPen> > {};
    for (int i=0;i<list.length();i++){
        pathsList.append(list[i]);
    }
}

void StrokeTraining::mousePressEvent(QMouseEvent * event)
{
    //IF modify button was clicked
    if (chosenForm == 0){
         mousePress = true;
        this->point1 = event->pos();
         //If the selection has been made
         //and we want to move it
        if (! selectionFirstClick){
            this->point3 = event->pos();
        }
    }

    else if(event->button() == Qt::LeftButton){
        this->point1 = event->pos();
        mousePress = true;
    }

    else if (event->button() == Qt::RightButton){
        this->point2 = event->pos();
        mouseRightPress = true;
        update();
    }
    //Set the stack poper for right click event to false
    donePop = false;
}

void StrokeTraining:: mouseMoveEvent(QMouseEvent *event)
{
    this->point2 = event->pos();

    path =QPainterPath(point1);
    //Depending on the form we draw the path
    switch (chosenForm){
    case 1 :
            path.lineTo(point2); break;
    case 2 :
            path.addRect(point1.x(),point1.y(),point2.x()-point1.x(),point2.y()-point1.y()); break;
    case 3 :
            path.addEllipse(point1.x(),point1.y(),point2.x()-point1.x(),point2.y()-point1.y()); break;
    case 0 :
        {
            //To select the forms
            if(selectionFirstClick){
                path.addRect(point1.x(),point1.y(),point2.x()-point1.x(),point2.y()-point1.y());
            }
            //To drag them
            else {
                moveForms = true;
                this->point4 = event->pos();
            }
            break;
        }
    }
    update();
}

void StrokeTraining::mouseReleaseEvent(QMouseEvent * event)
{
    this->point2 = event->pos();
    this->point3 = event->pos();
    mousePress = false;
    mouseRightPress = false;
    //If modify button clicked
    if (chosenForm == 0){
        //To select the forms
        if (selectionFirstClick){
            index = QVector<int>();
            for (int i=0;i<pathsList.length();i++){
                if ( path.intersects(pathsList[i].first) ){
                    index.append(i);
                }
            }
            selectionFirstClick = false;
        }
        else{
            update();
        }
    }
    else {
        QPen pen;
        pen.setWidth(this->penWidth);
        pen.setColor(this->penColor);
        pen.setStyle(this->penStyle);
        pathsList.append(qMakePair(path,pen));
        update();
    }
}

void StrokeTraining::paintEvent(QPaintEvent *paintEvent){
    QPen pen;
    pen.setWidth(this->penWidth);
    pen.setColor(this->penColor);
    pen.setStyle(this->penStyle);
    QWidget::paintEvent(paintEvent);
    QPainter painter(this);
    painter.setPen(pen);
    //Modify mode
    if (chosenForm ==0){
        //selection mode
        if (selectionFirstClick){
            if (mousePress || mouseRightPress) {
                for (int i=0; i<pathsList.length(); i++)
                {
                    painter.setPen(pathsList[i].second);
                    painter.drawPath(pathsList[i].first);
                }
                pen.setWidth(1);
                pen.setColor("black");
                pen.setStyle(Qt::DashLine);
                painter.setPen(pen);
                painter.drawPath(path);
            }
        }
        //moving forms and repainting
        else{
            if (! index.isEmpty() && moveForms){
                for (int cpt=0; cpt<index.size();cpt++){
                    //We divide the translation from experience, because the translations were way too fast
                    pathsList[index[cpt]].first = pathsList[index[cpt]].first.translated((point4- point3)/20);
                }
            }
            else{
                for (int cpt=0; cpt<index.size();cpt++) {
                    pathsList[index[cpt]].second = pen;
                }
            }
            for (int i=0; i<pathsList.length(); i++) {
                painter.setPen(pathsList[i].second);
                painter.drawPath(pathsList[i].first);
            }
        }
    }
    //If left click, draw saved forms and the new one being designed
    else if (mousePress){
        painter.drawPath(path);
        for (int i=0; i<pathsList.length(); i++){
            painter.setPen(pathsList[i].second);
            painter.drawPath(pathsList[i].first);
        }
    }

    //If right click, pop last form and modify its p2 and draw former forms
    else if (mouseRightPress){
        //pop the last form to redraw it
        if(! donePop){
            pathsList.pop_back();
            donePop = true;
        }
        painter.drawPath(path);
        for (int i=0; i<pathsList.length(); i++){
            painter.setPen(pathsList[i].second);
            painter.drawPath(pathsList[i].first);
        }
    }

    //If nothing clicked, just draw the data
    else{
        for (int i=0; i<pathsList.length(); i++) {
            painter.setPen(pathsList[i].second);
            painter.drawPath(pathsList[i].first);
        }
    }
}

void StrokeTraining::erase(){
    //Returning to line mode to avoid trouble for erasing after modifying mode
    chosenForm = 1;
    pathsList.pop_back();
    point1 = QPoint(0,0);
    point2 = QPoint(0,0);
    update();
}

void StrokeTraining::eraseAll(){
    pathsList = QList< QPair<QPainterPath,QPen> > {};
    //Re-initialize
    point1 = QPoint(0,0);
    point2 = QPoint(0,0);
    penWidth = 2;
    penColor = "black";
    penStyle = Qt::SolidLine;
    mousePress=false;
    mouseRightPress = false;
    donePop = false;
    chosenForm = 1;
    update();
}
