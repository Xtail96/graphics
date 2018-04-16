#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->typesComboBox->addItem("GL_POINTS");
    ui->typesComboBox->addItem("GL_LINES");
    ui->typesComboBox->addItem("GL_LINE_STRIP");
    ui->typesComboBox->addItem("GL_LINE_LOOP");
    ui->typesComboBox->addItem("GL_TRIANGLES");
    ui->typesComboBox->addItem("GL_TRIANGLE_STRIP");
    ui->typesComboBox->addItem("GL_TRIANGLE_FAN");
    ui->typesComboBox->addItem("GL_QUADS");
    ui->typesComboBox->addItem("GL_QUAD_STRIP");
    ui->typesComboBox->addItem("GL_POLYGON");
    QObject::connect(ui->typesComboBox, SIGNAL(activated(int)), ui->fieldGLWidget, SLOT(setPrimitive(int)));

    ui->opacityTestComboBox->addItem("GL_NEVER");
    ui->opacityTestComboBox->addItem("GL_LESS");
    ui->opacityTestComboBox->addItem("GL_EQUAL");
    ui->opacityTestComboBox->addItem("GL_LEQUAL");
    ui->opacityTestComboBox->addItem("GL_GREATER");
    ui->opacityTestComboBox->addItem("GL_NOTEQUAL");
    ui->opacityTestComboBox->addItem("GL_GEQUAL");
    ui->opacityTestComboBox->addItem("GL_ALWAYS");
    QObject::connect(ui->opacityTestComboBox, SIGNAL(activated(int)), ui->fieldGLWidget, SLOT(setAlphaTestIndex(int)));
    QObject::connect(ui->opacityDial, SIGNAL(valueChanged(int)), ui->fieldGLWidget, SLOT(setAlphaTestValue(int)));
    QObject::connect(ui->opacityDial, SIGNAL(valueChanged(int)), this, SLOT(setOpacityValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setOpacityValue(int value)
{
    double tmp = (double) value / 100;
    qDebug() << tmp;
    ui->opacityLcdNumber->display(tmp);
}
