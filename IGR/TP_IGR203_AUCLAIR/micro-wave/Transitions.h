//
//  Transitions.h: Useful functions for QStateMachine transitions.
//  (c) Eric Lecolinet - Telecom ParisTech - 2016.
//  http://www.telecom-paristech.fr/~elc
//

#ifndef TRANSITION_H
#define TRANSITION_H

#include <QWidget>
#include <QMouseEvent>
#include <QState>
#include <QStateMachine>
#include <QSignalTransition>
#include <QKeyEventTransition>
#include <QMouseEventTransition>

/// returns the position of the mouse cursor in widget coordinates.
inline QPoint cursorPos(QWidget* w) {return w->mapFromGlobal(QCursor::pos());}

/// returns the position of the mouse cursor in widget coordinates.
inline QPoint cursorPos(QWidget& w) {return w.mapFromGlobal(QCursor::pos());}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/** Add a transition for signals.
 */
inline QSignalTransition* addTrans(QState* from, QState* to,
                                   QObject* sender, const char* signal) {
  return from->addTransition(sender, signal, to);
}

/** Add a transition for signals and connects a slot to this transition.
 */
inline QSignalTransition* addTrans(QState* from, QState* to,
                                   QObject* sender, const char* signal,
                                   QObject* receiver, const char* slot) {
  QSignalTransition* trans = from->addTransition(sender, signal, to);
  QObject::connect(trans, SIGNAL(triggered()), receiver, slot);
  return trans;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/** Add a transition for events.
 */
inline QEventTransition* addEventTrans(QState* from, QState* to,
                                       QObject* sender, QEvent::Type type) {
  QEventTransition* trans = new QEventTransition(sender, type);
  trans->setTargetState(to);
  from->addTransition(trans);
  return trans;
}

/** Add a transition for events and connects a slot to this transition..
 */
inline QEventTransition* addEventTrans(QState* from, QState* to,
                                       QObject* sender, QEvent::Type type,
                                       QObject* receiver, const char* slot) {
  QEventTransition* trans = addEventTrans(from, to, sender, type);
  QObject::connect(trans, SIGNAL(triggered()), receiver, slot);
  return trans;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/** Add a transition for key events.
 */
inline QKeyEventTransition* addKeyTrans(QState* from, QState* to,
                                        QObject* sender, QEvent::Type type, int key) {
  QKeyEventTransition* trans = new QKeyEventTransition(sender, type, key);
  trans->setTargetState(to);
  from->addTransition(trans);
  return trans;
}

/** Add a transition for key events and connect a slot to this transition.
 */
inline QKeyEventTransition* addKeyTrans(QState* from, QState* to,
                                        QObject* sender, QEvent::Type type, int key,
                                        QObject* receiver, const char* slot) {
  QKeyEventTransition* trans = addKeyTrans(from, to, sender, type, key);
  QObject::connect(trans, SIGNAL(triggered()), receiver, slot);
  return trans;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/** Add a transition for mouse events.
 */
inline QMouseEventTransition* addMouseTrans(QState* from, QState* to,
                                            QObject* sender, QEvent::Type type, Qt::MouseButton btn) {
  QMouseEventTransition* trans = new QMouseEventTransition(sender, type, btn);
  trans->setTargetState(to);
  from->addTransition(trans);
  return trans;
}

/** Add a transition for mouse events and connect a slot to this transition.
 */
inline QMouseEventTransition* addMouseTrans(QState* from, QState* to,
                                            QObject* sender, QEvent::Type type, Qt::MouseButton btn,
                                            QObject* receiver, const char* slot) {
  QMouseEventTransition* trans = addMouseTrans(from, to, sender, type, btn);
  QObject::connect(trans, SIGNAL(triggered()), receiver, slot);
  return trans;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/** Transition for mouse events which updates the mouse position.
 */
class MouseEventTransition : public QMouseEventTransition {
  QPoint& pos;
public:
  MouseEventTransition(QObject* sender, QEvent::Type type, Qt::MouseButton button, QPoint& pos)
  : QMouseEventTransition(sender, type, button), pos(pos) {}
  
  virtual void onTransition(QEvent *e) {
    QEvent* realEvent = static_cast<QStateMachine::WrappedEvent*>(e)->event();
    switch (realEvent->type()) {
      case QEvent::MouseMove:
      case QEvent::MouseButtonPress:
      case QEvent::MouseButtonRelease:
      case QEvent::MouseButtonDblClick:
        pos = (static_cast<QMouseEvent*>(realEvent))->pos();
      default: break;
    }
  }
};

/** Add a transition for mouse events that updates the mouse position.
 * _pos_ is a QPoint which value is updated when the transition is fired.
 * _pos_ must not be destroyed as long as this transition exists.
 */
inline MouseEventTransition* addMouseTrans(QState* from, QState* to,
                                           QObject* sender, QEvent::Type type, Qt::MouseButton btn,
                                           QPoint& pos) {
  MouseEventTransition* trans = new MouseEventTransition(sender, type, btn, pos);
  trans->setTargetState(to);
  from->addTransition(trans);
  return trans;
}

/** Add a transition for mouse events that updates the mouse position, and connect a slot to this transition.
 * _pos_ is a QPoint which value is updated when the transition is fired.
 * _pos_ must not be destroyed as long as this transition exists.
 */
inline MouseEventTransition* addMouseTrans(QState* from, QState* to,
                                           QObject* sender, QEvent::Type type, Qt::MouseButton btn,
                                           QObject* receiver, const char* slot,
                                           QPoint& pos) {
  MouseEventTransition* trans = addMouseTrans(from, to, sender, type, btn, pos);
  QObject::connect(trans, SIGNAL(triggered()), receiver, slot);
  return trans;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/** Transition for user events.
 */
class UserEventTransition : public QAbstractTransition {
public:
  /** constructor.
   * _eventType_ must be between QEvent::User and QEvent::MaxUser.
   */
  UserEventTransition(int eventType) : type(eventType) {}

  int eventType() const {return type;}
  void setEventType(int eventType) {type = eventType;}

protected:
  int type;
  virtual bool eventTest(QEvent* e) {return type == e->type();}
  virtual void onTransition(QEvent*) {}
};


/** Add a transition that can be fired by a user event.
 * _eventType_ must be between QEvent::User and QEvent::MaxUser.
 * The transition is fired by posting a QEvent having the same _eventType_:
 *        state_machine->postEvent(new QEvent(type));
 */
inline UserEventTransition* addUserEventTrans(QState* from, QState* to, int eventType) {
  UserEventTransition* trans = new UserEventTransition(eventType);
  trans->setTargetState(to);
  from->addTransition(trans);
  return trans;
}

/** Add a transition that can be fired by a user event and connect a slot to this transition.
 * _eventType_ must be between QEvent::User and QEvent::MaxUser.
 * The transition is fired by posting a QEvent having the same _eventType_:
 *        state_machine->postEvent(new QEvent(type));
 */
inline UserEventTransition* addUserEventTrans(QState* from, QState* to, int eventType,
                                              QObject* receiver, const char* slot) {
  UserEventTransition* trans = addUserEventTrans(from, to, eventType);
  QObject::connect(trans, SIGNAL(triggered()), receiver, slot);
  return trans;
}

#endif // TRANSITION_H
