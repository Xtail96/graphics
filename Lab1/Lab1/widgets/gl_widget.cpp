#include "gl_widget.h"

GL_Widget::GL_Widget(QWidget *parent):
    QGLWidget(parent)
{
    setGeometry(20, 20, 550, 500);
}

void GL_Widget::initializeGL(){
    //glClearColor(0.913, 0.933, 0.996, 1);
    //glViewport(0, 0, this->width(), this->height());

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GL_Widget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);

    //glViewport(0, 0, 1, 1);

    //Задаем режим матрицы
    glMatrixMode(GL_PROJECTION);

    //Загружаем матрицу
    glLoadIdentity();

    move();
    glScalef(m_scale, m_scale, m_scale);

    /*glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glEnd();*/

    drawLeafFractal(m_startPoint.m_x, m_startPoint.m_y, m_l, m_angle, "left");
}

void GL_Widget::drawLeafFractal(double x, double y, double l, double angle, QString side)
{
    if(l > 1)
    {
        lineTo(x, y, l, angle);
        x = std::round(x + l * cos(angle));
        y = std::round(y - l * sin(angle));

        if(side == "left")
        {

            drawLeafFractal(x, y, l*0.5, angle - M_PI/4, "right");
            //drawLeafFractal(x, y, l*0.4, angle + M_PI/4, "left");
            drawLeafFractal(x, y, l*0.8, angle, "right");
        }
        else
        {
            //drawLeafFractal(x, y, l*0.4, angle - M_PI/4, "left");
            drawLeafFractal(x, y, l*0.5, angle + M_PI/4, "left");
            drawLeafFractal(x, y, l*0.8, angle, "left");
        }

    }
}

void GL_Widget::lineTo(double x, double y, double l, double angle)
{
    double newX = std::round(x + l * cos(angle));
    double newY = std::round(y - l * sin(angle));

    //qDebug() << newX << newY;

    glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(newX, newY);
    glEnd();

    //Line(x, y, Round(x + l * cos(u)), Round(y - l * sin(u)));
}

void GL_Widget::wheelEvent(QWheelEvent *wheelEvent)
{
    scaling(wheelEvent->delta());
}

void GL_Widget::scaling(int delta)
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
}

void GL_Widget::setPositionX(double value)
{
    m_positionX = value;
}

void GL_Widget::setPositionY(double value)
{
    m_positionY = value;
}

void GL_Widget::setStartPoint(double x, double y)
{
    m_startPoint = Point2Df(x, y);
    updateGL();
}

void GL_Widget::setL(int value)
{
    m_l = value;
    updateGL();
}

void GL_Widget::setAngle(double gradValue)
{
    m_angle = (180/M_PI) * gradValue;
    updateGL();
}

void GL_Widget::drawLine(Point2Df begin, Point2Df end)
{
    glVertex2f(begin.m_x, begin.m_y);
    glVertex2f(end.m_x, end.m_y);
}

Point2Df GL_Widget::rotateMatrix(Point2Df point, double angle, Point2Df offset)
{
    double radian = angle * (M_PI/180);

    Point2Df res;

    res.m_x = point.m_x * cos(radian) - point.m_y * sin(radian) + offset.m_x;
    res.m_y = point.m_x * sin(radian) + point.m_y * cos(radian) + offset.m_y;

    return res;
}

double GL_Widget::angle() const
{
    return m_angle* (M_PI/180);
}

size_t GL_Widget::l() const
{
    return m_l;
}

std::pair<double, double> GL_Widget::startPoint() const
{
    return std::make_pair(m_startPoint.m_x, m_startPoint.m_y);
}
