#ifndef STROKEDRAWER_H
#define STROKEDRAWER_H

#include  <QWidget>
#include <QPolygonF>
#include <QPainter>
#include "QPen"

class StrokeDrawer:public QWidget
{
    QPolygonF gesture;

public:
    StrokeDrawer();

public:
    void setStroke(QPolygonF);
    QPolygonF getStroke();
    void clearStroke();
    void paintEvent(QPaintEvent * paintEvent);
    QSize sizeHint() const;
    QSize minimumSizeHint() const;
};

#endif // STROKEDRAWER_H
