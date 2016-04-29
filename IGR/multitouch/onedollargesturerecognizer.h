#ifndef ONEDOLLARGESTURERECOGNIZER_H
#define ONEDOLLARGESTURERECOGNIZER_H
#include <QGestureRecognizer>
#include <QGesture>
#include "onedollarutil.h"
#include "onedollargesture.h"

class OneDollarGestureRecognizer: public QGestureRecognizer,OneDollarUtil
{
public:
    OneDollarGestureRecognizer();
    QGestureRecognizer::Result recognize(QGesture *,QObject*,QEvent*);
    QGesture * create(QObject*);
    void reset(QGesture*);
};

#endif // ONEDOLLARGESTURERECOGNIZER_H
