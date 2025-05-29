#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QChart>
#include <QLineSeries>
#include <QChartView>
#include <QFont>
#include <QLabel>
#include <QValueAxis>
#include <QFileDialog>
#include <QEvent>
#include "camerawidget.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include "opencv2/imgproc.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/videoio.hpp"
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cameraWidget(new CameraWidget(this))
{
    ui->setupUi(this);
    ui->text_label->setText("Hello, World!");
    cout<<"Program should be working if you see this"<<endl;
    ui->camera_gridLayout->addWidget(cameraWidget);

    //runLoop();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_run_pushButton_clicked(){
    int i=0;
    cameraWidget->initialize(ui);
    while (i<1){
        ui->text_label->setText(QString::number(i));
        cv::Mat image;
        cv::Mat image1;
        cv::Mat image2;
        cv::Mat image3;
        image = cv::imread("C:/Users/jsogh/Dropbox/CPP/sampleQT/Wandell.jpg");
        cout<<"image.type() "<<image.type()<<endl;
        cameraWidget->loadMat(image);
        //cout<<"MainWindow::on_run_pushButton_clicked() image: "<<image.cols<<" "<<image.rows<<" "<<image.type()<<endl;
        //cv::cvtColor(image, image1, cv::COLOR_BGR2RGB); // invert BGR to RGB
        //cameraWidget->loadMat(image);
        //cout<<"MainWindow::on_run_pushButton_clicked() image1: "<<image1.cols<<" "<<image1.rows<<" "<<image1.type()<<endl;
        cv::resize(image,image2,cv::Size(), 0.3, 0.3, cv::INTER_LINEAR);
        //cout<<"MainWindow::on_run_pushButton_clicked() image2: "<<image2.cols<<" "<<image2.rows<<" "<<image2.type()<<endl;
        //image3=image2.clone();
        //QImage imagePlot=QImage(image3.data, image3.cols, image3.rows, QImage::Format_RGB888);
        QImage imagePlot=QImage(image3.data, image3.cols, image3.rows, QImage::Format_RGB888);
        //cout<<"MainWindow::on_run_pushButton_clicked() imagePlot: "<<imagePlot.width()<<" "<<imagePlot.height()<<endl;
 
        //cv::imshow("image",image);
        //cv::imshow("image1",image1);
        //cv::imshow("image2",image2);
        //cv::imshow("image3",image3);
        
        //cout<<"starting to plot graphicsScene"<<endl;
        QPixmap pixmap;
        if(image2.type()==CV_8UC3){
            const uchar *qImageBuffer = (const uchar*)image2.data;
            // Create QImage with same dimensions as input Mat
            QImage img(qImageBuffer, image2.cols, image2.rows, image2.step, QImage::Format_RGB888);
            pixmap = QPixmap::fromImage(img.rgbSwapped());
        }
        else
        {
            qDebug() << "ERROR: Mat could not be converted to QImage or QPixmap.";
            return;
        }

        ui->camera_label->setPixmap(pixmap);
        ui->camera_label->setScaledContents(true);
/*
        QGraphicsScene *scene = new QGraphicsScene;
        scene->clear();
        QPixmap pix = QPixmap::fromImage(imagePlot,Qt::ColorOnly);

        scene->addPixmap(pix);
        ui->camera_graphicsView->setScene(scene);
        ui->camera_graphicsView->show();
*/
        i=i+1;
        cout<<"i="<<i<<endl;
        qApp->processEvents();
    }
    cout<<"Stopping acquisition."<<endl;
    return;
}
