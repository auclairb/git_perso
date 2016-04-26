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
  QPoint point1,point2,point3,point4;
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
    explicit StrokeTraining( QWidget * parent , QPolygonF);
    QList<QPair<QPainterPath,QPen> > getList() {return pathsList;}
    void setList(QList<QPair<QPainterPath,QPen> > ) ;
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);


public slots:
    void erase();
    void eraseAll();
    void modify();
    void line();
};

#endif

