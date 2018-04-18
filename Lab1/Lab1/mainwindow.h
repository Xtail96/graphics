#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

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
    void setOpacityValue(int value);
    void setScissorXValue(int value);
    void setScissorYValue(int value);
    void setScissorWValue(int value);
    void setScissorHValue(int value);
private slots:
    void on_filterComboBox_activated(int index);
};

#endif // MAINWINDOW_H
