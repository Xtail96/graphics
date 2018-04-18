#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

enum tests {NONE, ALPHA_TEST, BLEND_TEST, SCISSOR_TEST, ALL_TEST};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

protected slots:
    void activateAlphaTest();
    void activateBlendTest();
    void activateScissorTest();
    void activateTest(int index);

    void setOpacityValue(int value);
    void setScissorXValue(int value);
    void setScissorYValue(int value);
    void setScissorWValue(int value);
    void setScissorHValue(int value);
private slots:
};

#endif // MAINWINDOW_H
