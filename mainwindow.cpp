#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->text_label->setText("Hello, World!");
    cout<<"Program should be working if you see this"<<endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}
