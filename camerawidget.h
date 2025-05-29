#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QWidget>
#include <QColor>
#include <QImage>
#include <QPoint>
#include <cstdlib>
#include <vector>
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include "opencv2/imgproc.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/videoio.hpp"

using namespace std;

class CameraWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CameraWidget(QWidget *parent = nullptr);
    Ui::MainWindow *ui;
    void loadImage(QImage qImagePlot);
    void initialize(Ui::MainWindow*);
    void loadMat(cv::Mat image);
signals:
    

protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event);
private:
    QImage imagePlot;
    bool eventBeingHandled=false;
    double CamScaleFactor=1.3;
    double camZoom;
};

#endif // CAMERAWIDGET_H
