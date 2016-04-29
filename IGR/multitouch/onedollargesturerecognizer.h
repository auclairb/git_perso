#ifndef ONEDOLLARGESTURERECOGNIZER_H
#define ONEDOLLARGESTURERECOGNIZER_H
#include <QGestureRecognizer>
#include <QGesture>
#

class OneDollarGestureRecognizer: public QGestureRecognizer
{
public:
    OneDollarGestureRecognizer();
    QGestureRecognizer::Result recognize(QGesture *,QObject*,QEvent*);
    QGesture * create(QObject*);
    void reset(QGesture*);
};

#endif // ONEDOLLARGESTURERECOGNIZER_H
