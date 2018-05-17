#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pointsCountLineEdit->setText(QString::number(ui->fieldGLWidget->getCurvePointCount()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_applyPushButton_clicked()
{
    QString pointsCount = ui->pointsCountLineEdit->text();
    bool ok = true;
    double value = pointsCount.toUInt(&ok);

    if(ok)
    {
        ui->fieldGLWidget->setCurvePointCount(value);
    }
    else
    {
        ui->pointsCountLineEdit->setText(QString::number(ui->fieldGLWidget->getCurvePointCount()));
    }
}
