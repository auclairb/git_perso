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

class StrokeTraining::public StrokDrawer
{
  
 private:
  QPoint point1,point2;
  QPainterPath path;
  int penWidth;
  bool mousePress;
  bool mouseRightPress;
  bool donePop;
  bool selectionFirstClick,moveForms;
  int chosenForm;
  QVector<int> index;
  QColor penColor;
  Qt::PenStyle penStyle;
  QList< QPair<QPainterPath,QPen > > pathsList;

  public:
    explicit DrawingArea( QWidget *parent = 0 );
    QList<QPair<QPainterPath,QPen> > getList() {return pathsList;}
    void setList(QList<QPair<QPainterPath,QPen> > ) ;
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);


};

#endif
