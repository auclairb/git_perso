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
    Q_OBJECT

  private:
  QPoint point1,point2;
  QList<QPoint> pathList;
  QPainterPath path,pathCurrent;
  bool firstClick;
  QPolygonF polygon;

  public:
    explicit StrokeTraining();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    void submit();
    void erase();
};

#endif

