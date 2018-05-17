#ifndef GL_WINDGET_H
#define GL_WINDGET_H

#include <cmath>

#include <QGLWidget>
#include <QDebug>
#include <QMouseEvent>

/*class Point2Df{
public:
    float x, y;
    void setxy(float x2, float y2)
    {
        x = x2; y = y2;
    }
    //operator overloading for '=' sign
    const Point2Df& operator=(const Point2Df&rPoint)
    {
        x = rPoint.x;
        y = rPoint.y;
        return *this;
    }

};*/

struct Point2Df
{
    double m_x;
    double m_y;
    Point2Df(double x = 0.0, double y = 0.0) : m_x(x), m_y(y) {}

    const Point2Df & operator=(const Point2Df &rPoint)
    {
        m_x = rPoint.m_x;
        m_y = rPoint.m_y;
        return *this;
    }

    void setxy(float x, float y)
        {
            m_x = x; m_y = y;
        }
};

/*void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}*/

class GL_Widget: public QGLWidget
{
    Q_OBJECT
private:
    //double m_scale = 0.0015;

    double m_scale = 1;

    int m_mousePositionX = 0;

    int m_mousePositionY = 0;

    double m_positionX = 0;

    double m_positionY = 0;

    QList<Point2Df> m_points;

    int currentPointIndex = 0;
    int curvePointCount = 4;

public:
    explicit GL_Widget(QWidget *parent = 0);

    void initializeGL();

    void paintGL();

    int getCurvePointCount() const;
    void setCurvePointCount(int value);

public slots:

    //void wheelEvent(QWheelEvent *wheelEvent);

    void mouseMoveEvent(QMouseEvent *mouseEvent);

    void mousePressEvent(QMouseEvent *mouseEvent);

    void setPositionX(double value);

    void setPositionY(double value);

protected slots:
    //void scaling(int delta);

    void move();

public slots:
    void drawLine(Point2Df begin, Point2Df end);
    void drawPoint(double x, double y);
    void drawPoint(Point2Df point);

    void drawCurve();

    Point2Df rotateMatrix(Point2Df point, double angle, Point2Df offset = Point2Df());

    //Calculate the bezier point [generalized]
    Point2Df drawBezierGeneralized(QList<Point2Df> pointsList, double t) {
        Point2Df bezierPoint;
        bezierPoint.m_x = 0; bezierPoint.m_y = 0;
        for (int i = 0; i < curvePointCount; i++)
        {
            bezierPoint.m_x = bezierPoint.m_x + binomial_coff((float)(curvePointCount - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (curvePointCount - 1 - i)) * pointsList[i].m_x;
            bezierPoint.m_y = bezierPoint.m_y + binomial_coff((float)(curvePointCount - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (curvePointCount - 1 - i)) * pointsList[i].m_y;
        }
        return bezierPoint;
    }

    //Calculate the bezier point
    Point2Df drawBezier(QList<Point2Df> pointsList, double t) {
        Point2Df bezierCurvePoint;
        bezierCurvePoint.m_x = pow((1 - t), 3) * pointsList[0].m_x + 3 * t * pow((1 - t), 2) * pointsList[1].m_x + 3 * (1 - t) * pow(t, 2)* pointsList[2].m_x + pow(t, 3)* pointsList[3].m_x;
        bezierCurvePoint.m_y = pow((1 - t), 3) * pointsList[0].m_y + 3 * t * pow((1 - t), 2) * pointsList[1].m_y + 3 * (1 - t) * pow(t, 2)* pointsList[2].m_y + pow(t, 3)* pointsList[3].m_y;

        return bezierCurvePoint;
    }

    int factorial(int n)
    {
        if (n <= 1)
            return(1);
        else
            n = n * factorial(n - 1);
        return n;
    }

    float binomial_coff(float n, float k)
    {
        float ans;
        ans = factorial(n) / (factorial(k)*factorial(n - k));
        return ans;
    }
};

#endif // GL_WINDGET_H
