#include "strokedrawer.h"
#include <qmath.h>

StrokeDrawer::StrokeDrawer(QPolygonF gesture_new)
{
  this->gesture = gesture_new;
}

void StrokeDrawer::setStroke(QPolygonF gesture_new) {
    this->gesture = gesture_new;
}

QPolygonF StrokeDrawer::getStroke(){
    return this->gesture;
}

void StrokeDrawer::clearStroke(){
  this->gesture = QPolygonF();
}

void StrokeDrawer::displayStroke(){
  QPainter painter(this);
  painter.drawPolyline(this->gesture);
}

QSize StrokeDrawer::sizeHint() const{
  QRectF r = (this->gesture).boundingRect();
  int max = qMax(r.width(),r.height());
  return QSize(max,max);
}

QSize StrokeDrawer::minimumSizeHint() const{
  QRectF r = (this->gesture).boundingRect();
  int max = qMax(r.width(),r.height());
  return QSize(max,max);
}
