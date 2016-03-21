#ifndef STROKEDRAWER_H
#define STROKEDRAWER_H

#include  <QWidget>
#include <QGesture>

class StrokeDrawer:public QWidget
{
    QGesture gesture;

public:
    StrokeDrawer();

private:
    void setStroke(QGesture gesture);
    QGesture getStroke();
    void clearStroke();
    void displayStroke();

};

#endif // STROKEDRAWER_H
