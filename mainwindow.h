#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "camerawidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    CameraWidget *cameraWidget;

private slots:
   void on_run_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    //void runLoop();
};
#endif // MAINWINDOW_H
