#ifndef STROKETRAINING_H
#define STROKETRAINING_H

#include "strokedrawer.h"
#include <string>
#include <QColor>
#include <QList>
#include <stdio.h>
#include <iostream>
#include <QPair>
#include <QPen>
#include <QPainterPath>
#include <QVector>

class StrokeTraining:public StrokeDrawer{

  private:
  QPoint point1,point2;
  QList<QPoint> pathList;
  QPainterPath path,pathCurrent;
  bool firstClick;

  public:
    explicit StrokeTraining( QWidget * parent);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);


public slots:
    void submit();
};

#endif

