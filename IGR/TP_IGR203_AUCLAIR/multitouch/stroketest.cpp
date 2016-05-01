#include "stroketest.h"

StrokeTest::StrokeTest() :StrokeDrawer()
{
    grabGesture(QGestureRecognizer::registerRecognizer(gestureRecognize));
}

bool StrokeTest::event(QEvent * event){
    if (event->type() == QEvent::Gesture){
        return gestureEvent(static_cast<QGestureEvent*>(event));
    }
    return QWidget::event(event);
}

bool StrokeTest::gestureEvent(QGestureEvent * gestureEvent){


    if( QGesture * qgesture = gestureEvent->gesture(Qt::SwipeGesture)){
        QSwipeGesture * swipeGesture = static_cast<QSwipeGesture *>(qgesture);
        if(swipeGesture==NULL){
            return false;
        }
        std::cout<<swipeGesture->state()<<std::endl;
        if(swipeGesture->state()==Qt::GestureFinished){
            if(swipeGesture->horizontalDirection()==QSwipeGesture::Left || swipeGesture->verticalDirection()==QSwipeGesture::Up){
                QLabel Left("Previous");
                Left.show();
            } else if(swipeGesture->horizontalDirection()==QSwipeGesture::Right || swipeGesture->verticalDirection()==QSwipeGesture::Down){
                QLabel Right("Next");
                Right.show();
            }
        }
    }

    else if (QGesture * qgesture = gestureEvent->gesture(Qt::PanGesture)){
        QPanGesture * panGesture = static_cast<QPanGesture *>(qgesture);
        if(panGesture==NULL){
            return false;
        }
        std::cout<<panGesture->state()<<std::endl;
        if(panGesture->state()==Qt::GestureFinished){

        }
    }

    else if (QGesture * qgesture = gestureEvent->gesture(Qt::PinchGesture)){
        QPinchGesture * pinchGesture = static_cast<QPinchGesture *>(qgesture);
        if(pinchGesture==NULL){
            return false;
        }
        std::cout<<pinchGesture->state()<<std::endl;
        if(pinchGesture->state()==Qt::GestureFinished){

        }
    }

    return true;
}
