#include "stroketraining.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include "mainwindow.h"
#include <QList>
#include <QVector>

StrokeTraining::StrokeTraining(QWidget * parent):StrokeDrawer() {
    point1 = QPoint(0,0);
    point2 = QPoint(0,0);
    pathList = QList<QPoint>{};

    path = QPainterPath();
    pathCurrent = QPainterPath();
    firstClick = true;
}

void StrokeTraining::mousePressEvent(QMouseEvent * event)
{
    if(event->button() == Qt::LeftButton){
        if(firstClick == true){
            this->point1 = event->pos();
            pathList.append(point1);
            firstClick = false;
        } else {
            this->point1 = pathList.back();
        }
    }

    else if (event->button() == Qt::RightButton){
        pathList.pop_back();
        this->point2 = event->pos();
        update();
    }
}

void StrokeTraining:: mouseMoveEvent(QMouseEvent *event)
{
    this->point2 = event->pos();
    pathCurrent=QPainterPath(point1);
    pathCurrent.lineTo(point2);
    update();
}

void StrokeTraining::mouseReleaseEvent(QMouseEvent * event)
{
    this->point2 = event->pos();
    path=QPainterPath(point1);
    pathCurrent.lineTo(point2);
    pathList.append(point2);
    update();
}

void StrokeTraining::paintEvent(QPaintEvent *paintEvent){
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::blue);
    pen.setStyle(Qt::SolidLine);
    QWidget::paintEvent(paintEvent);
    QPainter painter(this);
    painter.setPen(pen);
    for(int i = 0; i<pathList.size()-1;i++){
       path = QPainterPath(pathList.at(i));
       path.lineTo(pathList.at(i+1));
       painter.drawPath(path);
    }
    painter.drawPath(pathCurrent);
}

void StrokeTraining::submit(){

}
