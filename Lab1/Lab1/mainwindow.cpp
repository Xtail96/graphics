#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->angleLineEdit->setText(QString::number(ui->fieldGLWidget->angle()));
    ui->branchLineEdit->setText(QString::number(ui->fieldGLWidget->l()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_angleLineEdit_returnPressed()
{
    ui->fieldGLWidget->setAngle(ui->angleLineEdit->text().toDouble());
}

void MainWindow::on_branchLineEdit_returnPressed()
{
    ui->fieldGLWidget->setL(ui->branchLineEdit->text().toInt());
}
