#include "strokedrawer.h"

StrokeDrawer::StrokeDrawer()
{
}

void StrokeDrawer::setStroke(QGesture gesture_new) {
    this->gesture = gesture_new;
}

QGesture StrokeDrawer::getStroke(){
    return this->gesture;
}

void StrokeDrawer::clearStroke(){
    this->gesture = NULL;
}

void StrokeDrawer::displayStroke(){

}
