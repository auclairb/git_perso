#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include "stroketraining.h"
#include "gesturetemplate.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    StrokeTraining * drawing;
    QHBoxLayout * scrollingLayout;
    QVector<GestureTemplate> gestureTemplate;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void move();

};

#endif // MAINWINDOW_H
