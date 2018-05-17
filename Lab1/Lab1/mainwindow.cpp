#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pointsCountLineEdit->setText(QString::number(ui->fieldGLWidget->getCurvePointCount()));
    ui->debugCheckBox->setChecked(ui->fieldGLWidget->getDebugMode());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_applyPushButton_clicked()
{
    int currentPointCount = ui->fieldGLWidget->getCurvePointCount();

    QString pointsCount = ui->pointsCountLineEdit->text();
    bool ok = true;
    double value = pointsCount.toUInt(&ok);

    if(ok)
    {
        if(value != currentPointCount)
        {
            ui->fieldGLWidget->setCurvePointCount(value);
        }
    }
    else
    {
        ui->pointsCountLineEdit->setText(QString::number(currentPointCount));
    }

    if(ui->debugCheckBox->isChecked())
    {
        ui->fieldGLWidget->setDebugMode(true);
    }
    else
    {
        ui->fieldGLWidget->setDebugMode(false);
    }
}
