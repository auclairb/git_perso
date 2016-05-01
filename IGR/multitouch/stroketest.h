#ifndef STROKETEST_H
#define STROKETEST_H
#include "strokedrawer.h"
#include <QEvent>
#include <QGestureEvent>
#include <QSwipeGesture>
#include <QGesture>
#include <iostream>
#include <QLabel>
#include "onedollargesturerecognizer.h"
#include <QGestureRecognizer>

class StrokeTest:public StrokeDrawer
{
    Q_OBJECT
public:
    StrokeTest();
    bool event(QEvent*);
    bool gestureEvent(QGestureEvent*);
};

#endif // STROKETEST_H
