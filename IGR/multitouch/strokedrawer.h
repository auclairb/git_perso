#ifndef STROKEDRAWER_H
#define STROKEDRAWER_H

#include  <QWidget>
#include <QPolygonF>
#include <QPainter>

class StrokeDrawer:public QWidget
{
    QPolygonF gesture;

public:
    StrokeDrawer(QPolygonF);

private:
    void setStroke(QPolygonF);
    QPolygonF getStroke();
    void clearStroke();
    void displayStroke();
    QSize sizeHint() const;
    QSize minimumSizeHint() const;

};

#endif // STROKEDRAWER_H
