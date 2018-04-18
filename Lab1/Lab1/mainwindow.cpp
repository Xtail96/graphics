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

    ui->filterComboBox->addItem("Тест прозрачности");
    ui->filterComboBox->addItem("Тест смешения цветов");
    ui->filterComboBox->addItem("Тест отсечения");
    QObject::connect(ui->filterComboBox, SIGNAL(activated(int)), ui->fieldGLWidget, SLOT(setFilter(int)));

    ui->opacityTestComboBox->addItem("GL_NEVER");
    ui->opacityTestComboBox->addItem("GL_LESS");
    ui->opacityTestComboBox->addItem("GL_EQUAL");
    ui->opacityTestComboBox->addItem("GL_LEQUAL");
    ui->opacityTestComboBox->addItem("GL_GREATER");
    ui->opacityTestComboBox->addItem("GL_NOTEQUAL");
    ui->opacityTestComboBox->addItem("GL_GEQUAL");
    ui->opacityTestComboBox->addItem("GL_ALWAYS");
    QObject::connect(ui->opacityTestComboBox, SIGNAL(activated(int)), ui->fieldGLWidget, SLOT(setAlphaTestIndex(int)));
    QObject::connect(ui->alphaTestHorizontalSlider, SIGNAL(valueChanged(int)), ui->fieldGLWidget, SLOT(setAlphaTestValue(int)));
    QObject::connect(ui->alphaTestHorizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setOpacityValue(int)));

    ui->blendTest1ComboBox->addItem("GL_ZERO");
    ui->blendTest1ComboBox->addItem("GL_ONE");
    ui->blendTest1ComboBox->addItem("GL_SRC_COLOR");
    ui->blendTest1ComboBox->addItem("GL_ONE_MINUS_SRC_COLOR");
    ui->blendTest1ComboBox->addItem("GL_SRC_ALPHA");
    ui->blendTest1ComboBox->addItem("GL_ONE_MINUS_SRC_ALPHA");
    ui->blendTest1ComboBox->addItem("GL_DST_ALPHA");
    ui->blendTest1ComboBox->addItem("GL_ONE_MINUS_DST_ALPHA");
    ui->blendTest1ComboBox->addItem("GL_SRC_ALPHA_SATURATE");
    QObject::connect(ui->blendTest1ComboBox, SIGNAL(activated(int)), ui->fieldGLWidget, SLOT(setBlendTestIndexFirst(int)));

    ui->blendTest2ComboBox->addItem("GL_ZERO");
    ui->blendTest2ComboBox->addItem("GL_ONE");
    ui->blendTest2ComboBox->addItem("GL_SRC_COLOR");
    ui->blendTest2ComboBox->addItem("GL_ONE_MINUS_SRC_COLOR");
    ui->blendTest2ComboBox->addItem("GL_SRC_ALPHA");
    ui->blendTest2ComboBox->addItem("GL_ONE_MINUS_SRC_ALPHA");
    ui->blendTest2ComboBox->addItem("GL_DST_ALPHA");
    ui->blendTest2ComboBox->addItem("GL_ONE_MINUS_DST_ALPHA");
    QObject::connect(ui->blendTest2ComboBox, SIGNAL(activated(int)), ui->fieldGLWidget, SLOT(setBlendTestIndexSecond(int)));

    QObject::connect(ui->scissorTestXHorizontalSlider, SIGNAL(valueChanged(int)), ui->fieldGLWidget, SLOT(setScissorTestX(int)));
    QObject::connect(ui->scissorTestYHorizontalSlider, SIGNAL(valueChanged(int)), ui->fieldGLWidget, SLOT(setScissorTestY(int)));
    QObject::connect(ui->scissorTestWHorizontalSlider, SIGNAL(valueChanged(int)), ui->fieldGLWidget, SLOT(setScissorTestW(int)));
    QObject::connect(ui->scissorTestHHorizontalSlider, SIGNAL(valueChanged(int)), ui->fieldGLWidget, SLOT(setScissorTestH(int)));

    QObject::connect(ui->scissorTestXHorizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setScissorXValue(int)));
    QObject::connect(ui->scissorTestYHorizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setScissorYValue(int)));
    QObject::connect(ui->scissorTestWHorizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setScissorWValue(int)));
    QObject::connect(ui->scissorTestHHorizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setScissorHValue(int)));

    ui->alphaTestLabel->setEnabled(false);
    ui->alphaTestHorizontalSlider->setEnabled(false);
    ui->opacityLcdNumber->setEnabled(false);
    ui->opacityTestComboBox->setEnabled(false);

    ui->blendTestLabel->setEnabled(false);
    ui->blendTest1ComboBox->setEnabled(false);
    ui->blendTest2ComboBox->setEnabled(false);

    ui->scissorTestLabel->setEnabled(false);

    ui->scissorTestXLabel->setEnabled(false);
    ui->scissorTestXHorizontalSlider->setEnabled(false);
    ui->scissorTestXLcdNumber->setEnabled(false);

    ui->scissorTestYLabel->setEnabled(false);
    ui->scissorTestYHorizontalSlider->setEnabled(false);
    ui->scissorTestYLcdNumber->setEnabled(false);

    ui->scissorTestWidthLabel->setEnabled(false);
    ui->scissorTestWHorizontalSlider->setEnabled(false);
    ui->scissorTestWLcdNumber->setEnabled(false);

    ui->scissorTestHeightLabel->setEnabled(false);
    ui->scissorTestHHorizontalSlider->setEnabled(false);
    ui->scissorTestHLcdNumber->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setOpacityValue(int value)
{
    double tmp = (double) value;
    ui->opacityLcdNumber->display(tmp);
}

void MainWindow::setScissorXValue(int value)
{
    double tmp = (double) value;
    ui->scissorTestXLcdNumber->display(tmp);
}

void MainWindow::setScissorYValue(int value)
{
    double tmp = (double) value;
    ui->scissorTestYLcdNumber->display(tmp);
}

void MainWindow::setScissorWValue(int value)
{
    double tmp = (double) value;
    ui->scissorTestWLcdNumber->display(tmp);
}

void MainWindow::setScissorHValue(int value)
{
    double tmp = (double) value;
    ui->scissorTestHLcdNumber->display(tmp);
}

void MainWindow::on_filterComboBox_activated(int index)
{
    switch (index) {
    case 0:
        ui->alphaTestLabel->setEnabled(true);
        ui->alphaTestHorizontalSlider->setEnabled(true);
        ui->opacityLcdNumber->setEnabled(true);
        ui->opacityTestComboBox->setEnabled(true);

        ui->blendTestLabel->setEnabled(false);
        ui->blendTest1ComboBox->setEnabled(false);
        ui->blendTest2ComboBox->setEnabled(false);

        ui->scissorTestLabel->setEnabled(false);

        ui->scissorTestXLabel->setEnabled(false);
        ui->scissorTestXHorizontalSlider->setEnabled(false);
        ui->scissorTestXLcdNumber->setEnabled(false);

        ui->scissorTestYLabel->setEnabled(false);
        ui->scissorTestYHorizontalSlider->setEnabled(false);
        ui->scissorTestYLcdNumber->setEnabled(false);

        ui->scissorTestWidthLabel->setEnabled(false);
        ui->scissorTestWHorizontalSlider->setEnabled(false);
        ui->scissorTestWLcdNumber->setEnabled(false);

        ui->scissorTestHeightLabel->setEnabled(false);
        ui->scissorTestHHorizontalSlider->setEnabled(false);
        ui->scissorTestHLcdNumber->setEnabled(false);
        break;
    case 1:
        ui->alphaTestLabel->setEnabled(false);
        ui->alphaTestHorizontalSlider->setEnabled(false);
        ui->opacityLcdNumber->setEnabled(false);
        ui->opacityTestComboBox->setEnabled(false);

        ui->blendTestLabel->setEnabled(true);
        ui->blendTest1ComboBox->setEnabled(true);
        ui->blendTest2ComboBox->setEnabled(true);

        ui->scissorTestLabel->setEnabled(false);

        ui->scissorTestXLabel->setEnabled(false);
        ui->scissorTestXHorizontalSlider->setEnabled(false);
        ui->scissorTestXLcdNumber->setEnabled(false);

        ui->scissorTestYLabel->setEnabled(false);
        ui->scissorTestYHorizontalSlider->setEnabled(false);
        ui->scissorTestYLcdNumber->setEnabled(false);

        ui->scissorTestWidthLabel->setEnabled(false);
        ui->scissorTestWHorizontalSlider->setEnabled(false);
        ui->scissorTestWLcdNumber->setEnabled(false);

        ui->scissorTestHeightLabel->setEnabled(false);
        ui->scissorTestHHorizontalSlider->setEnabled(false);
        ui->scissorTestHLcdNumber->setEnabled(false);
        break;
    case 2:
        ui->alphaTestLabel->setEnabled(false);
        ui->alphaTestHorizontalSlider->setEnabled(false);
        ui->opacityLcdNumber->setEnabled(false);
        ui->opacityTestComboBox->setEnabled(false);

        ui->blendTestLabel->setEnabled(false);
        ui->blendTest1ComboBox->setEnabled(false);
        ui->blendTest2ComboBox->setEnabled(false);

        ui->scissorTestLabel->setEnabled(true);

        ui->scissorTestXLabel->setEnabled(true);
        ui->scissorTestXHorizontalSlider->setEnabled(true);
        ui->scissorTestXLcdNumber->setEnabled(true);

        ui->scissorTestYLabel->setEnabled(true);
        ui->scissorTestYHorizontalSlider->setEnabled(true);
        ui->scissorTestYLcdNumber->setEnabled(true);

        ui->scissorTestWidthLabel->setEnabled(true);
        ui->scissorTestWHorizontalSlider->setEnabled(true);
        ui->scissorTestWLcdNumber->setEnabled(true);

        ui->scissorTestHeightLabel->setEnabled(true);
        ui->scissorTestHHorizontalSlider->setEnabled(true);
        ui->scissorTestHLcdNumber->setEnabled(true);
        break;
    default:
        ui->alphaTestLabel->setEnabled(false);
        ui->alphaTestHorizontalSlider->setEnabled(false);
        ui->opacityLcdNumber->setEnabled(false);
        ui->opacityTestComboBox->setEnabled(false);

        ui->blendTestLabel->setEnabled(false);
        ui->blendTest1ComboBox->setEnabled(false);
        ui->blendTest2ComboBox->setEnabled(false);

        ui->scissorTestLabel->setEnabled(false);

        ui->scissorTestXLabel->setEnabled(false);
        ui->scissorTestXHorizontalSlider->setEnabled(false);
        ui->scissorTestXLcdNumber->setEnabled(false);

        ui->scissorTestYLabel->setEnabled(false);
        ui->scissorTestYHorizontalSlider->setEnabled(false);
        ui->scissorTestYLcdNumber->setEnabled(false);

        ui->scissorTestWidthLabel->setEnabled(false);
        ui->scissorTestWHorizontalSlider->setEnabled(false);
        ui->scissorTestWLcdNumber->setEnabled(false);

        ui->scissorTestHeightLabel->setEnabled(false);
        ui->scissorTestHHorizontalSlider->setEnabled(false);
        ui->scissorTestHLcdNumber->setEnabled(false);
        break;
    }
}
