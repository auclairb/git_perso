#include "strokedrawer.h"
#include <qmath.h>

StrokeDrawer::StrokeDrawer()
{
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

void StrokeDrawer::paintEvent(QPaintEvent * paintEvent){
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::blue);
    pen.setStyle(Qt::SolidLine);
    QWidget::paintEvent(paintEvent);
    QPainter painter(this);
    painter.setPen(pen);

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
