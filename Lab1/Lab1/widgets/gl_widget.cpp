#include "gl_widget.h"

GL_Widget::GL_Widget(QWidget *parent):
    QGLWidget(parent)
{
    m_primitiveIndex=0;
    setGeometry(20, 20, 550, 500);

    int pointsCount = 9;

    double floor = -0.9;
    double up = 0.9;

    for(int i = 0; i < pointsCount; i++)
    {
        Point3Df tmp;
        tmp.x = (double) (rand()) / RAND_MAX * (up - floor) + floor;
        tmp.y = (double) (rand()) / RAND_MAX * (up - floor) + floor;
        tmp.z = (double) (rand()) / RAND_MAX * (up - floor) + floor;
        m_points.push_back(tmp);
    }

}

void GL_Widget::initializeGL(){
    glClearColor(0.913, 0.933, 0.996, 1);
}

void GL_Widget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);
    startDrawing();
}

void GL_Widget::figuresGL(){
    switch (m_primitiveIndex) {
    case 0:
    {
        glPointSize(5);
        glBegin(GL_POINTS);


        for(auto point : m_points)
        {
            glColor4f((double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX);
            glVertex3f(point.x, point.y, point.z);
        }

        glEnd();

        break;
    };
    case 1:
    {
        glLineWidth(5);
        glBegin(GL_LINES);

        for(auto point : m_points)
        {
            glColor4f((double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX);
            glVertex3f(point.x, point.y, point.z);
        }

        glEnd();
 break;
    };
    case 2:{

        glLineWidth(5);
        glBegin(GL_LINE_STRIP);

        for(auto point : m_points)
        {
            glColor4f((double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX);
            glVertex3f(point.x, point.y, point.z);
        }

        glEnd();
    break;
    };
    case 3:{

        glLineWidth(5);
        glBegin(GL_LINE_LOOP);

        for(auto point : m_points)
        {
            glColor4f((double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX);
            glVertex3f(point.x, point.y, point.z);
        }

        glEnd();
        break;
    };
    case 4:{

        glLineWidth(5);
        glBegin(GL_TRIANGLES);

        for(auto point : m_points)
        {
            glColor4f((double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX);
            glVertex3f(point.x, point.y, point.z);
        }

        glEnd();
        break;
    };
    case 5:{

        glLineWidth(5);
        glBegin(GL_TRIANGLE_STRIP);

        for(auto point : m_points)
        {
            glColor4f((double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX);
            glVertex3f(point.x, point.y, point.z);
        }

        glEnd();
        break;
    };
    case 6:{
        glBegin(GL_TRIANGLE_FAN);
        glLineWidth(5);

        for(auto point : m_points)
        {
            glColor4f((double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX);
            glVertex3f(point.x, point.y, point.z);
        }

        glEnd();
        break;
    };
    case 7:{

        glLineWidth(5);
        glBegin(GL_QUADS);

        for(auto point : m_points)
        {
            glColor4f((double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX);
            glVertex3f(point.x, point.y, point.z);
        }

        glEnd();
        break;
    };
    case 8:{

        glLineWidth(5);
        glBegin(GL_QUAD_STRIP);

        for(auto point : m_points)
        {
            glColor4f((double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX);
            glVertex3f(point.x, point.y, point.z);
        }

        glEnd();
        break;
    };
    case 9:{

        glLineWidth(5);
        glBegin(GL_POLYGON);

        for(auto point : m_points)
        {
            glColor4f((double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX,
                      (double) (rand()) / RAND_MAX);
            glVertex3f(point.x, point.y, point.z);
        }

        glEnd();
        break;
    };
    default:
        break;
    }
}

void GL_Widget::startDrawing(){
    figuresGL();
}

void GL_Widget::setPrimitive(int p){
    this->m_primitiveIndex = p;
    this->updateGL();
}

