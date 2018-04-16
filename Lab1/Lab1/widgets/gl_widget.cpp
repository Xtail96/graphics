#include "gl_widget.h"

void GL_Widget::setBlendTestIndexFirst(int blendTestIndexFirst)
{
    m_blendTestIndexFirst = blendTestIndexFirst;
    this->updateGL();
}

void GL_Widget::setBlendTestIndexSecond(int blendTestIndexSecond)
{
    m_blendTestIndexSecond = blendTestIndexSecond;
    this->updateGL();
}

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
        tmp.red = (double) (rand()) / RAND_MAX;
        tmp.green = (double) (rand()) / RAND_MAX;
        tmp.blue = (double) (rand()) / RAND_MAX;
        tmp.alpha = (double) (rand()) / RAND_MAX;
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
            glColor4f(point.red, point.green, point.blue, point.alpha);
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
            glColor4f(point.red, point.green, point.blue, point.alpha);
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
            glColor4f(point.red, point.green, point.blue, point.alpha);
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
            glColor4f(point.red, point.green, point.blue, point.alpha);
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
            glColor4f(point.red, point.green, point.blue, point.alpha);
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
            glColor4f(point.red, point.green, point.blue, point.alpha);
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
            glColor4f(point.red, point.green, point.blue, point.alpha);
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
            glColor4f(point.red, point.green, point.blue, point.alpha);
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
            glColor4f(point.red, point.green, point.blue, point.alpha);
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
            glColor4f(point.red, point.green, point.blue, point.alpha);
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
    opacityTestEnable();
    blendTestEnable();
    figuresGL();
}

void GL_Widget::opacityTestEnable()
{
    glEnable(GL_ALPHA_TEST);

    switch (m_alphaTestIndex) {
    case 0:
        glAlphaFunc(GL_NEVER, m_alphaTestValue);
        break;
    case 1:
        glAlphaFunc(GL_LESS, m_alphaTestValue);
        break;
    case 3:
        glAlphaFunc(GL_EQUAL, m_alphaTestValue);
        break;
    case 4:
        glAlphaFunc(GL_LEQUAL, m_alphaTestValue);
        break;
    case 5:
        glAlphaFunc(GL_GREATER, m_alphaTestValue);
        break;
    case 6:
        glAlphaFunc(GL_NOTEQUAL, m_alphaTestValue);
        break;
    case 7:
        glAlphaFunc(GL_ALWAYS, m_alphaTestValue);
        break;
    default:
        glDisable(GL_ALPHA_TEST);
        break;
    }
}

void GL_Widget::blendTestEnable()
{
    glEnable(GL_BLEND);
    GLenum sfactor;
    GLenum dfactor;

    switch (m_blendTestIndexFirst) {
    case 0:
        sfactor = GL_ZERO;
        break;
    case 1:
        sfactor = GL_ONE;
        break;
    case 2:
        sfactor = GL_DST_COLOR;
        break;
    case 3:
        sfactor = GL_ONE_MINUS_DST_COLOR;
        break;
    case 4:
        sfactor = GL_SRC_ALPHA;
        break;
    case 5:
        sfactor = GL_ONE_MINUS_SRC_ALPHA;
        break;
    case 6:
        sfactor = GL_DST_ALPHA;
        break;
    case 7:
        sfactor = GL_ONE_MINUS_DST_ALPHA;
        break;
    case 8:
        sfactor = GL_SRC_ALPHA_SATURATE;
        break;
    default:
        //glDisable(GL_BLEND);
        break;
    }

    switch (m_blendTestIndexSecond) {
    case 0:
        dfactor = GL_ZERO;
        break;
    case 1:
        dfactor = GL_ONE;
        break;
    case 2:
        dfactor = GL_DST_COLOR;
        break;
    case 3:
        dfactor = GL_ONE_MINUS_DST_COLOR;
        break;
    case 4:
        dfactor = GL_SRC_ALPHA;
        break;
    case 5:
        dfactor = GL_ONE_MINUS_SRC_ALPHA;
        break;
    case 6:
        dfactor = GL_DST_ALPHA;
        break;
    case 7:
        dfactor = GL_ONE_MINUS_DST_ALPHA;
        break;
    case 8:
        dfactor = GL_SRC_ALPHA_SATURATE;
        break;
    default:
        //glDisable(GL_BLEND);
        break;
    }

    qDebug() << m_blendTestIndexFirst << m_blendTestIndexSecond;

    glBlendFunc(sfactor, dfactor);
}

void GL_Widget::setPrimitive(int p){
    this->m_primitiveIndex = p;
    this->updateGL();
}

void GL_Widget::setAlphaTestIndex(int alphaTestIndex)
{
    m_alphaTestIndex = alphaTestIndex;
    this->updateGL();
}

void GL_Widget::setAlphaTestValue(int alphaTestValue)
{
    m_alphaTestValue =  (double) alphaTestValue / 100;
    this->updateGL();
}

