#include "gl_widget.h"

GL_Widget::GL_Widget(QWidget *parent):
    QGLWidget(parent)
{
    setGeometry(20, 20, 550, 500);
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

    for(int i = 0; i < m_points.size(); i++)
    {
        drawPoint(m_points[i], i);
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
    double dx = (double) (mouseEvent->x() - m_mousePositionX) / (10 * (this->width() / 2));
    double dy = (double) (mouseEvent->y() - m_mousePositionY) / (10 * (this->height() / 2));

    qDebug() << m_debugPointIndex << dx << dy;

    if(m_debugMode)
    {
        if(m_debugPointIndex > 0 && m_debugPointIndex < m_points.size())
        {
            m_points[m_debugPointIndex].m_x += dx;
            m_points[m_debugPointIndex].m_y -= dy;
        }
    }

    //qDebug() << m_debugPointIndex;

    updateGL();

    if(m_debugMode)
    {
        Point2Df center((double) this->width() / 2, (double) this->height() / 2);
        double x = (double) (m_mousePositionX - center.m_x) / 350;
        double y = (double) (center.m_y - m_mousePositionY) / 350;

        double deltaX = INT_MAX;
        double deltaY = INT_MAX;

        int pointIndex = -1;

        for(int i = 0; i < m_points.size(); i++)
        {
            double currentDeltaX = abs(m_points[i].m_x - x);
            double currentDeltaY = abs(m_points[i].m_y - y);
            if(currentDeltaX < deltaX && currentDeltaY < deltaY)
            {
                pointIndex = i;
            }
        }

        if(pointIndex >= 0 && pointIndex < m_points.size())
        {
            m_points[pointIndex].m_x += dx;
            m_points[pointIndex].m_y += dy;
        }

        updateGL();
    }

    /*double dx = (mouseEvent->x() - m_mousePositionX) / 10;
    double dy = (mouseEvent->y() - m_mousePositionY) / 10;

    if (mouseEvent->buttons() == Qt::LeftButton)
    {
        setPositionX(m_positionX + dx/1000);
        setPositionY(m_positionY + dy/1000);
    }

    updateGL();*/
}

void GL_Widget::mousePressEvent(QMouseEvent *mouseEvent)
{
    m_mousePositionX = mouseEvent->x();
    m_mousePositionY = mouseEvent->y();

    Point2Df center((double) this->width() / 2, (double) this->height() / 2);
    double x = (double) (m_mousePositionX - center.m_x) / (this->width() / 2);
    double y = (double) (center.m_y - m_mousePositionY) / (this->height() / 2);

    //qDebug() << x << y;

    if(!m_debugMode)
    {
        if(m_points.size() >= curvePointCount)
        {
            m_points.clear();
            currentPointIndex = 0;
        }

        Point2Df point(x, y);
        m_points.push_back(point);

        m_points[currentPointIndex].m_x = x;
        m_points[currentPointIndex].m_y = y;

        currentPointIndex++;
    }
    else
    {
        /*for(int i = 0; i < m_points.size(); i++)
        {
            double deltaX = abs(m_points[i].m_x - x);
            double deltaY = abs(m_points[i].m_y - x);

            qDebug() << "point" + QString::number(i) << deltaX << deltaY;

            if(deltaX < 0.2 && deltaY < 0.2)
            {
                m_debugPointIndex = i;
                break;
            }
        }

        qDebug() << "---";*/

        double deltaX = INT_MAX;
        double deltaY = INT_MAX;

        for(int i = 0; i < m_points.size(); i++)
        {
            double currentDeltaX = abs(m_points[i].m_x - x);
            double currentDeltaY = abs(m_points[i].m_y - y);
            if(currentDeltaX < deltaX && currentDeltaY < deltaY)
            {
                deltaX = currentDeltaX;
                deltaY = currentDeltaY;
                m_debugPointIndex = i;
            }
        }
    }

    //qDebug() << m_debugPointIndex;

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

void GL_Widget::drawPoint(Point2Df point, int index)
{
    //qDebug() << "point" << point.m_x << point.m_y;
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(point.m_x, point.m_y);
    glEnd();
    glFlush();

    renderText(point.m_x, point.m_y, 0, QString::number(index));
}

void GL_Widget::drawCurve()
{
    if(currentPointIndex == curvePointCount)
    {
        // Drawing the control lines
        glColor3f(0.0, 0.0, 1.0);
        glLineWidth(1);
        for (int i = 0; i < curvePointCount - 1; i++)
        {
            drawLine(m_points[i], m_points[i+1]);
        }


        glColor3f(0.2, 1.0, 0.0);
        glLineWidth(5);

        Point2Df p1 = m_points[0];
        /* Draw each segment of the curve.Make t increment in smaller amounts for a more detailed curve.*/
        for (double t = 0.0; t <= 1.0; t += 0.02)
        {
            Point2Df p2 = drawBezierGeneralized(m_points, t);
            //qDebug() << p1.m_x << "," << p1.m_y;
            //qDebug() << p2.m_x << "," << p2.m_y;
            drawLine(p1, p2);
            p1 = p2;
        }
        glColor3f(0.0, 0.0, 0.0);
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

int GL_Widget::getCurvePointCount() const
{
    return curvePointCount;
}

void GL_Widget::setCurvePointCount(int value)
{
    curvePointCount = value;
    m_points.clear();
    currentPointIndex = 0;
    updateGL();
}

bool GL_Widget::getDebugMode() const
{
    return m_debugMode;
}

void GL_Widget::setDebugMode(bool debugMode)
{
    m_debugMode = debugMode;
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
