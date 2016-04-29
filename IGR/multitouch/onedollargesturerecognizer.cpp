#include "onedollargesturerecognizer.h"

OneDollarGestureRecognizer::OneDollarGestureRecognizer()
{
}

QGestureRecognizer::Result OneDollarGestureRecognizer::recognize(QGesture *,QObject*,QEvent*){

}

QGesture * OneDollarGestureRecognizer::create(QObject*){
    OneDollarGesture *  dollarGesture = new OneDollarGesture(QPolygonF(),GestureTemplate(),0);
    return dollarGesture;
}

void OneDollarGestureRecognizer::reset(QGesture* qgesture){
    (static_cast<OneDollarGesture*>(qgesture))->clear();
    QGestureRecognizer::reset(qgesture);
}
