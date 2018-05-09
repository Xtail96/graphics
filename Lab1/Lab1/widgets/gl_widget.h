#ifndef GL_WINDGET_H
#define GL_WINDGET_H

#include <cmath>

#include <QGLWidget>
#include <QDebug>
#include <QMouseEvent>

//#include <fractset.h>

struct Point3Df
{
    double x;
    double y;
    double z;
    double red;
    double green;
    double blue;
    double alpha;
};

struct Point2Df
{
    double m_x;
    double m_y;
    Point2Df(double x = 0.0, double y = 0.0) : m_x(x), m_y(y) {}
};

class GL_Widget: public QGLWidget
{
    Q_OBJECT
private:
    // Lab3
    Point2Df m_startPoint = Point2Df(0.0, -500);
    double m_angle = -M_PI/2;
    size_t m_l = 200;

    double m_scale = 0.0015;

    int m_mousePositionX = 0;

    int m_mousePositionY = 0;

    double m_positionX = 0;

    double m_positionY = 0;

public:
    explicit GL_Widget(QWidget *parent = 0);

    void initializeGL();

    void paintGL();

public slots:
    void drawLeafFractal(double x, double y, double l, double angle, QString side);

    void wheelEvent(QWheelEvent *wheelEvent);

    void mouseMoveEvent(QMouseEvent *mouseEvent);

    void mousePressEvent(QMouseEvent *mouseEvent);

    void setPositionX(double value);

    void setPositionY(double value);

    void setStartPoint(double x, double y);

    void setL(int value);

    void setAngle(double gradValue);

    double angle() const;

    size_t l() const;

    std::pair<double, double> startPoint() const;

protected slots:
    void drawLine(Point2Df begin, Point2Df end);

    Point2Df rotateMatrix(Point2Df point, double angle, Point2Df offset = Point2Df());

    void lineTo(double x, double y, double l, double angle);

    void scaling(int delta);

    void move();
};

#endif // GL_WINDGET_H
