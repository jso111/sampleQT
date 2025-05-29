#include "camerawidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <QChart>
#include <QLineSeries>
#include <QChartView>
#include <QFont>
#include <QLabel>
#include <QValueAxis>
#include <QFileDialog>
#include <QEvent>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include "opencv2/imgproc.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/videoio.hpp"
using namespace std;

CameraWidget::CameraWidget(QWidget *parent)
    : QWidget{parent}
{
    setAttribute(Qt::WA_StaticContents);
    QSize newSize(10,10);
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(0, 0, 0));
    imagePlot = newImage;
    update();
}
void CameraWidget::initialize(Ui::MainWindow* uiTemp){
    cout<<"CameraWidget::initialize"<<endl;
    ui=uiTemp;
    camZoom=1.0;
}
void CameraWidget::paintEvent(QPaintEvent *event){
    cout<<"CameraWidget::paintEvent"<<endl;
    QPainter painter(this);
    double sideW=imagePlot.width();
    double sideH=imagePlot.height();
    QRect plotRect = QRect(0, 0, sideW, sideH);
    painter.setWindow(plotRect);
    painter.setViewport(plotRect);
    painter.drawImage(plotRect,imagePlot);
    cout<<"CameraWidget::paintEvent finished"<<endl;
}
void CameraWidget::loadImage(QImage qImagePlot){
    cout<<"CameraWidget::loadImage this->width(),this->height(): "<<this->width()<<" "<<this->height()<<endl;
    cout<<"CameraWidget::loadImage qImagePlot.width(),qImagePlot.height(): "<<qImagePlot.width()<<" "<<qImagePlot.height()<<endl;
    imagePlot=qImagePlot.scaled(this->width(),this->height(),Qt::KeepAspectRatio,Qt::FastTransformation); // scale image to the window
    cout<<"CameraWidget::loadImage scaled imagePlot"<<endl;
    update();
}

void CameraWidget::loadMat(cv::Mat image){
    cout<<"CameraWidget::loadMat this->width(),this->height(): "<<this->width()<<" "<<this->height()<<endl;
    cv::Mat image1;
    cv::Mat image2;
    cv::resize(image,image1,cv::Size(), 0.3, 0.3, cv::INTER_LINEAR);
    cout<<"starting to convert to QImage"<<endl;
    //QPixmap pixmap;
    if(image1.type()==CV_8UC3){
        cout<<"starting to convert to QImage1"<<endl;
        const uchar *qImageBuffer = (const uchar*)image1.data;
        cout<<"starting to convert to QImage2"<<endl;
        QImage img(qImageBuffer, image1.cols, image1.rows, image1.step, QImage::Format_RGB888);
        cout<<"starting to convert to QImage3"<<endl;
        imagePlot=img.rgbSwapped();
        cout<<"starting to convert to QImage4"<<endl;
        //pixmap = QPixmap::fromImage(img.rgbSwapped());
    }
    elsevo
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return;
    }

    //ui->camera_label->setPixmap(pixmap);
    //ui->camera_label->setScaledContents(true);


    //imagePlot=QImage(bgr_image1.data, bgr_image1.cols, bgr_image1.rows, QImage::Format_RGB888);
    //cout<<"CameraWidget::loadMat imagePlot.width(),imagePlot.height(): "<<imagePlot.width()<<" "<<imagePlot.height()<<endl;
    
    update();

}

void CameraWidget::wheelEvent(QWheelEvent *event){
    //cout<<"CameraWidget mousewheel activated and signals are blocked: "<<eventBeingHandled<<endl;
    //QList<QEventPoint> test=event->points();
    //cout<<test.size()<<endl;
    //for (int i=0;i<test.size();i++){
    //    cout<<test[i].position().x()<<" "<<test[i].position().y()<<endl;
    //}
    //cout<<"event->type(): "<<event->type()<<" "<<event->angleDelta().y()<<" "<<event->pixelDelta().y()<<" "<<event->position().x()<<endl;
    event->accept();
    if (!eventBeingHandled){
        eventBeingHandled=true;
        //cout<<"tNow,tickCountLast,timeMS: "<<tNow<<" "<<tickCountLast<<" "<<timeMS<<endl;
        {
            QPoint numDegrees = event->angleDelta();
            QPointF point=event->position();
            QPoint numPixels = event->pixelDelta();
            double angle;
            if (!numPixels.isNull()) {
                angle=-1*numPixels.y();
            } else if (!numDegrees.isNull()) {
                angle=numDegrees.y();
            }
            double delta=1.0;
            if (angle<0){
                delta=1/CamScaleFactor;
            } else if (angle>0){
                delta=CamScaleFactor;
            }
            camZoom=camZoom*delta; 
            if (camZoom<1.0){
                camZoom=1.0;
            } else if (camZoom>10){
                camZoom=10;
            }
            
            if (angle!=0){
                point.x();
                point.y();
                
            }
        }
        eventBeingHandled=false;
    } 
    //cout<<"Bscan widget mousewheel finished; signals should be unblocked"<<endl;
}
