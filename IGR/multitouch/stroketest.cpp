#include "stroketest.h"

StrokeTest::StrokeTest() :StrokeDrawer()
{
    OneDollarGestureRecognizer * gestureRecognize;
    grabGesture(QGestureRecognizer::registerRecognizer(gestureRecognize));
}

bool StrokeTest::event(QEvent * event){
    if (event->type() == QEvent::Gesture){
        return gestureEvent(static_cast<QGestureEvent*>(event));
    }
    return QWidget::event(event);
}

bool StrokeTest::gestureEvent(QGestureEvent * gestureEvent){
    QGesture * qgesture = gestureEvent->gesture(Qt::SwipeGesture);
    QSwipeGesture * swipeGesture = static_cast<QSwipeGesture *>(qgesture);
    if(swipeGesture==NULL){
        return false;
    }
    std::cout<<swipeGesture->state()<<std::endl;
    if(swipeGesture->state()==Qt::GestureFinished){
        if(swipeGesture->horizontalDirection()==QSwipeGesture::Left || swipeGesture->verticalDirection()==QSwipeGesture::Up){
            QLabel Left("Previous");
            Left.show();
            return true;
        } else if(swipeGesture->horizontalDirection()==QSwipeGesture::Right || swipeGesture->verticalDirection()==QSwipeGesture::Down){
            QLabel Right("Next");
            Right.show();
            return true;
        }
    }
}
