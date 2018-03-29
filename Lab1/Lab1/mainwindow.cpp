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
}

MainWindow::~MainWindow()
{
    delete ui;
}
