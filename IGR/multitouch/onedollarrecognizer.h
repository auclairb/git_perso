#ifndef ONEDOLLARRECOGNIZER_H
#define ONEDOLLARRECOGNIZER_H
#include <QGestureRecognizer>
#include <QGesture>
#

class OneDollarRecognizer: public QGestureRecognizer
{
public:
    OneDollarRecognizer();
    Result recognize(QGesture *,QObject*,QEvent*);
    QGesture * create(QObject*);
    void reset(QGesture*);
};

#endif // ONEDOLLARRECOGNIZER_H
