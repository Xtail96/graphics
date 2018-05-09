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
private slots:
    void on_angleLineEdit_returnPressed();
    void on_branchLineEdit_returnPressed();
};

#endif // MAINWINDOW_H
