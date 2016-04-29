#include "onedollargesturerecognizer.h"

OneDollarGestureRecognizer::OneDollarGestureRecognizer()
{
}

QGesture * OneDollarGestureRecognizer::create(QObject*){
    OneDollarGesture *  dollarGesture = new OneDollarGesture(QPolygonF(),GestureTemplate(),0);
    return dollarGesture;
}

void OneDollarGestureRecognizer::reset(QGesture* qgesture){
    (static_cast<OneDollarGesture*>(qgesture))->clear();
    QGestureRecognizer::reset(qgesture);
}


QGestureRecognizer::Result OneDollarGestureRecognizer::recognize(QGesture * gesture, QObject * watched, QEvent * e){

 static bool pressed = false;
   QGestureRecognizer::Result result = QGestureRecognizer::Ignore;
   OneDollarGesture *pGesture = static_cast<OneDollarGesture*>(gesture);
   switch(e->type()) {
   case QEvent::MouseButtonPress: {
       pressed = true;
       QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(e);
       //TODO initialiser le stroke dans pGesture avec mouseEvent->pos()
       pGesture->setTrace(QPolygonF()<<mouseEvent->pos());
       result = QGestureRecognizer::MayBeGesture; //le widget recevra un QGestureEvent avec state() == Qt::GestureStarted
       qDebug("gesture started");
   }
       break;
   case QEvent::MouseMove:{
       if(pressed){
           QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(e);
           //TODO mettre a jour le stroke dans PGesture avec les nouvelles coordonnÃ©es
           QPolygonF stroke = pGesture->getTrace();
           stroke<<mouseEvent->pos();
           pGesture->setTrace(stroke);

           result = QGestureRecognizer::TriggerGesture; //le widget recevra un QGestureEvent avec state() == Qt::GestureUpdated
       }
   }
       break;
   case QEvent::MouseButtonRelease: {
       pressed = false;
       QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(e);
       //TODO mettre a jour le stroke dans PGesture avec les nouvelles coordonnÃ©es
       QPolygonF stroke = pGesture->getTrace();
       stroke<<mouseEvent->pos();
       pGesture->setTrace(stroke);

       result = QGestureRecognizer::CancelGesture; //le widget recevra un QGestureEvent avec state() == Qt::GestureCanceled
       GestureTemplate winner;
       float * score = 0;

       if(stroke.size()>10 && templates.size()>0){
           //TODO appeler la mÃ©thode OneDollarUtil::recognizeStroke
           winner = OneDollarUtil::recognizeStroke(pGesture->getTrace(),score);
           if (*score > 0.3){
               //TODO mettre Ã  jour les diffÃ©rents attributs de pGesture
               pGesture->setGestureTemplate(winner);
               pGesture->setScore(*score);
               result = QGestureRecognizer::FinishGesture; //le widget recevra un QGestureEvent avec state() == Qt::GestureFinished
               qDebug()<<"gesture finished; score: "<< score<< " name: " <<winner.name();
           }
       }
   }
       break;
   default:
       break;
   }

   return result;
}
