#ifndef ONEDOLLARGESTURE_H
#define ONEDOLLARGESTURE_H

#include <QGesture>
#include <QPolygonF>
#include "gesturetemplate.h"

class OneDollarGesture:public QGesture
{
    Q_OBJECT
    QPolygonF trace;
    GestureTemplate gestureTemplate;
    float score;

public:
    OneDollarGesture(QPolygonF,GestureTemplate,float);
    void setTrace(QPolygonF);
    void setGestureTemplate(GestureTemplate);
    void setScore(float);
    QPolygonF getTrace();
    GestureTemplate getGestureTemplate();
    float getScore();
};

#endif // ONEDOLLARGESTURE_H
