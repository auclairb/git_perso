#include "onedollargesture.h"

OneDollarGesture::OneDollarGesture(QPolygonF _trace, GestureTemplate _gestureTemplate, float _score)
{
    this->trace=_trace;
    this->gestureTemplate=_gestureTemplate;
    this->score=_score;
}

void OneDollarGesture::setGestureTemplate(GestureTemplate _gestureTemplate){
    this->gestureTemplate = _gestureTemplate;
}

void OneDollarGesture::setScore(float _score){
    this->score = _score;
}

void OneDollarGesture::setTrace(QPolygonF _trace){
    this->trace = _trace;
}

GestureTemplate OneDollarGesture::getGestureTemplate(){
    return this->gestureTemplate;
}

float OneDollarGesture::getScore(){
    return this->score;
}

QPolygonF OneDollarGesture::getTrace(){
    return this->trace;
}

void OneDollarGesture::clear(){
    this->score=0;
    this->gestureTemplate=GestureTemplate();
    this->trace=QPolygonF();
}
