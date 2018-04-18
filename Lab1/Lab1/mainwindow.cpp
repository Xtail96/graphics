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

    ui->filterComboBox->addItem("-");
    ui->filterComboBox->addItem("Тест прозрачности");
    ui->filterComboBox->addItem("Тест смешения цветов");
    ui->filterComboBox->addItem("Тест отсечения");
    ui->filterComboBox->addItem("Включить все тесты");
    QObject::connect(ui->filterComboBox, SIGNAL(activated(int)), this, SLOT(activateTest(int)));
    //QObject::connect(ui->filterComboBox, SIGNAL(activated(int)), ui->fieldGLWidget, SLOT(setFilter(int)));


    ui->opacityTestComboBox->addItem("GL_NEVER");
    ui->opacityTestComboBox->addItem("GL_LESS");
    ui->opacityTestComboBox->addItem("GL_EQUAL");
    ui->opacityTestComboBox->addItem("GL_LEQUAL");
    ui->opacityTestComboBox->addItem("GL_GREATER");
    ui->opacityTestComboBox->addItem("GL_NOTEQUAL");
    ui->opacityTestComboBox->addItem("GL_GEQUAL");
    ui->opacityTestComboBox->addItem("GL_ALWAYS");
    QObject::connect(ui->opacityTestComboBox, SIGNAL(activated(int)), ui->fieldGLWidget, SLOT(setAlphaTestIndex(int)));
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

void MainWindow::activateAlphaTest()
{
    ui->fieldGLWidget->setAlphaTestIndex(ui->opacityTestComboBox->currentIndex());
    //ui->fieldGLWidget->setAlphaTestValue(ui->alphaTestHorizontalSlider->value());
    setOpacityValue(ui->alphaTestHorizontalSlider->value());
}

void MainWindow::activateBlendTest()
{
    ui->fieldGLWidget->setBlendTestIndexFirst(ui->blendTest1ComboBox->currentIndex());
    ui->fieldGLWidget->setBlendTestIndexSecond(ui->blendTest2ComboBox->currentIndex());
}

void MainWindow::activateScissorTest()
{
    /*ui->fieldGLWidget->setScissorTestX(ui->scissorTestXHorizontalSlider->value());
    ui->fieldGLWidget->setScissorTestY(ui->scissorTestYHorizontalSlider->value());
    ui->fieldGLWidget->setScissorTestW(ui->scissorTestWHorizontalSlider->value());
    ui->fieldGLWidget->setScissorTestH(ui->scissorTestHHorizontalSlider->value());*/

    setScissorXValue(ui->scissorTestXHorizontalSlider->value());
    setScissorYValue(ui->scissorTestYHorizontalSlider->value());
    setScissorWValue(ui->scissorTestWHorizontalSlider->value());
    setScissorHValue(ui->scissorTestHHorizontalSlider->value());
}

void MainWindow::activateTest(int index)
{
    switch (index)
    {
    case 1:
        ui->fieldGLWidget->setFilter(ALPHA_TEST);
        activateAlphaTest();

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
    case 2:
        ui->fieldGLWidget->setFilter(BLEND_TEST);
        activateBlendTest();

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
    case 3:
        ui->fieldGLWidget->setFilter(SCISSOR_TEST);
        activateScissorTest();

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
    case 4:
        ui->fieldGLWidget->setFilter(ALL_TEST);
        activateAlphaTest();
        activateBlendTest();
        activateScissorTest();

        ui->alphaTestLabel->setEnabled(true);
        ui->alphaTestHorizontalSlider->setEnabled(true);
        ui->opacityLcdNumber->setEnabled(true);
        ui->opacityTestComboBox->setEnabled(true);

        ui->blendTestLabel->setEnabled(true);
        ui->blendTest1ComboBox->setEnabled(true);
        ui->blendTest2ComboBox->setEnabled(true);

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
        ui->fieldGLWidget->setFilter(NONE);

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

void MainWindow::setOpacityValue(int value)
{
    double tmp = (double) value;
    ui->opacityLcdNumber->display(tmp);
    ui->fieldGLWidget->setAlphaTestValue(tmp);
}

void MainWindow::setScissorXValue(int value)
{
    double tmp = (double) value;
    ui->scissorTestXLcdNumber->display(tmp);
    ui->fieldGLWidget->setScissorTestX(tmp);
}

void MainWindow::setScissorYValue(int value)
{
    double tmp = (double) value;
    ui->scissorTestYLcdNumber->display(tmp);
    ui->fieldGLWidget->setScissorTestY(tmp);
}

void MainWindow::setScissorWValue(int value)
{
    double tmp = (double) value;
    ui->scissorTestWLcdNumber->display(tmp);
    ui->fieldGLWidget->setScissorTestW(tmp);
}

void MainWindow::setScissorHValue(int value)
{
    double tmp = (double) value;
    ui->scissorTestHLcdNumber->display(tmp);
    ui->fieldGLWidget->setScissorTestH(tmp);
}
