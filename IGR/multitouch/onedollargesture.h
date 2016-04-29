#ifndef ONEDOLLARGESTURE_H
#define ONEDOLLARGESTURE_H

#include <QGesture>
#include <QPolygonF>
#include "gesturetemplate.h"
#include "onedollargesture.h"

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
    void clear();
};

#endif // ONEDOLLARGESTURE_H
