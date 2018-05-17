#include "gl_widget.h"

GL_Widget::GL_Widget(QWidget *parent):
    QGLWidget(parent)
{
    //setGeometry(20, 20, 550, 500);
}

void GL_Widget::initializeGL(){
    //glClearColor(0.913, 0.933, 0.996, 1);
    //glClearColor(0, 0, 0, 1);
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glViewport(0, 0, 1, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0.0, 800.0, 0.0, 0.0, 700.0, 0.0);
    glScalef(m_scale, m_scale, m_scale);

    //glViewport(0, 0, this->width(), this->height());

    //glClearColor(1.0, 1.0, 1.0, 0.0);

    /*glColor3f(0.0, 0.0, 0.0);
    glPointSize(3);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();*/

    //
    //gluOrtho2D(0.0, 800.0, 0.0, 700.0);
}

void GL_Widget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);

    //glViewport(0, 0, 1, 1);

    //Задаем режим матрицы
    glMatrixMode(GL_PROJECTION);

    //Загружаем матрицу
    glLoadIdentity();

    //move();

    for(auto point : m_points) {
        drawPoint(point);
    }

    drawCurve();

    //glScalef(m_scale, m_scale, m_scale);

    /*glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glEnd();*/
}

void GL_Widget::move()
{
    glTranslatef(0.5f * m_positionX, -(0.5f * m_positionY), 0);
}

void GL_Widget::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    double dx = (mouseEvent->x() - m_mousePositionX) / 10;
    double dy = (mouseEvent->y() - m_mousePositionY) / 10;

    if (mouseEvent->buttons() == Qt::LeftButton)
    {
        setPositionX(m_positionX + dx/1000);
        setPositionY(m_positionY + dy/1000);
    }

    updateGL();
}

void GL_Widget::mousePressEvent(QMouseEvent *mouseEvent)
{
    m_mousePositionX = mouseEvent->x();
    m_mousePositionY = mouseEvent->y();

    Point2Df center((double) this->width() / 2, (double) this->height() / 2);

    double x = (double) (m_mousePositionX - center.m_x) / 350;
    double y = (double) (center.m_y - m_mousePositionY) / 350;

    //qDebug() << x << y << center.m_x << center.m_y;


    Point2Df point(x, y);
    m_points.push_back(point);

    m_points[currentPointIndex].m_x = x;
    m_points[currentPointIndex].m_y = y;

    currentPointIndex++;

    updateGL();
}

void GL_Widget::setPositionX(double value)
{
    m_positionX = value;
}

void GL_Widget::setPositionY(double value)
{
    m_positionY = value;
}

void GL_Widget::drawLine(Point2Df begin, Point2Df end)
{
    glBegin(GL_LINES);
    glVertex2f(begin.m_x, begin.m_y);
    glVertex2f(end.m_x, end.m_y);
    glEnd();
    glFlush();
}

void GL_Widget::drawPoint(double x, double y)
{
    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(5);
    glVertex2f(x, y);
    glEnd();
    glFlush();
}

void GL_Widget::drawPoint(Point2Df point)
{
    //qDebug() << "point" << point.m_x << point.m_y;

    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(point.m_x, point.m_y);
    glEnd();
    glFlush();
}

void GL_Widget::drawCurve()
{
    if(currentPointIndex == curvePointCount)
    {
        glColor3f(0.2, 1.0, 0.0);
        // Drawing the control lines
        //for (int k = 0; k<clicks - 1; k++)
        //drawLine(abc[k], abc[k + 1]);

        Point2Df p1 = m_points[0];
        /* Draw each segment of the curve.Make t increment in smaller amounts for a more detailed curve.*/
        for (double t = 0.0; t <= 1.0; t += 0.02)
        {
            Point2Df p2 = drawBezierGeneralized(m_points, t);
            qDebug() << p1.m_x << "," << p1.m_y;
            qDebug() << p2.m_x << "," << p2.m_y;
            drawLine(p1, p2);
            p1 = p2;
        }
        glColor3f(0.0, 0.0, 0.0);

        currentPointIndex = 0;
    }
}

Point2Df GL_Widget::rotateMatrix(Point2Df point, double angle, Point2Df offset)
{
    double radian = angle * (M_PI/180);

    Point2Df res;

    res.m_x = point.m_x * cos(radian) - point.m_y * sin(radian) + offset.m_x;
    res.m_y = point.m_x * sin(radian) + point.m_y * cos(radian) + offset.m_y;

    return res;
}


/*void GL_Widget::wheelEvent(QWheelEvent *wheelEvent)
{
    scaling(wheelEvent->delta());
}*/

/*void GL_Widget::scaling(int delta)
{
    // если колесико вращаем вперед -- умножаем переменную масштаба на 1.1
    // иначе - делим на 1.1
    if (delta > 0)
    {
        m_scale *= 1.1;
    }
    else
    {
        if (delta < 0)
        {
            m_scale /= 1.1;
        }
    }
    updateGL();
}*/
