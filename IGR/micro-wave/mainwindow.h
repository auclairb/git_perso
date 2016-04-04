#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
  QTime * time;
  QTime * clock;
  QTimer * timer;
 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  
  public slots:
    void enterHeating();
    void increaseTime();
    void enterDefault();
    void increaseClock();
    void displayClock();
      
};


#endif // MAINWINDOW_H
