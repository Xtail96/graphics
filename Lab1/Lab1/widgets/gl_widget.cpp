#include "gl_widget.h"

GL_Widget::GL_Widget(QWidget *parent):
    QGLWidget(parent),
    m_program(new QOpenGLShaderProgram(this))
{
    //setGeometry(20, 20, 550, 500);
    xAxisRotation = yAxisRotation = 0;
}

GL_Widget::~GL_Widget()
{
    if(m_texture != nullptr)
    {
        delete m_texture;
    }
}

void GL_Widget::initializeGL(){
    glClearColor(0.913, 0.933, 0.996, 1);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);

    //initShaders();
    initTextures();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void GL_Widget::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glOrtho(-0.5, 1.5, -0.5, 1.5, -10.0, 10.0);

    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);

    currentWidth = nWidth;
    currentHeight = nHeight;
}

void GL_Widget::initShaders()
{
    //m_texture = new QOpenGLTexture(QImage(":/123.jpg").mirrored());

    if(!m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":vsh.vsh"))
    {
        qDebug() << "can not add vertex shader";
        this->close();
    }
    if(!m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":fsh.fsh"))
    {
        qDebug() << "can not add fragment shader";
        this->close();
    }

    if(!m_program->link())
    {
        qDebug() << "can not link program";
        this->close();
    }

    if(!m_program->bind())
    {
        qDebug() << "can not bind program";
        this->close();
    }
}

void GL_Widget::initTextures()
{
    m_texture = new QOpenGLTexture(QImage(":/123.jpg").mirrored());

    glGenTextures(6, textures);

    QImage texture1;
    texture1.load(":/123.jpg");
    texture1 = QGLWidget::convertToGLFormat(texture1);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)texture1.width(), (GLsizei)texture1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture1.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    QImage texture2;
    texture2.load(":/123.jpg");
    texture2 = QGLWidget::convertToGLFormat(texture2);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)texture2.width(), (GLsizei)texture2.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture2.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    QImage texture3;
    texture3.load(":/123.jpg");
    texture3 = QGLWidget::convertToGLFormat(texture3);
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)texture3.width(), (GLsizei)texture3.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture3.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    QImage texture4;
    texture4.load(":/123.jpg");
    texture4 = QGLWidget::convertToGLFormat(texture4);
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)texture4.width(), (GLsizei)texture4.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture4.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    QImage texture5;
    texture5.load(":/123.jpg");
    texture5 = QGLWidget::convertToGLFormat(texture5);
    glBindTexture(GL_TEXTURE_2D, textures[4]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)texture5.width(), (GLsizei)texture5.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture5.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    QImage texture6;
    texture6.load(":/123.jpg");
    texture6 = QGLWidget::convertToGLFormat(texture6);
    glBindTexture(GL_TEXTURE_2D, textures[5]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)texture6.width(), (GLsizei)texture6.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture6.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

void GL_Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glRotatef(yAxisRotation, 0.0, 1.0, 0.0);
    glRotatef(xAxisRotation, 1.0, 0.0, 0.0);

    glBindTexture(GL_TEXTURE_2D, textures[0]);

    cubeVertexArray[0][0] = 0.0;
    cubeVertexArray[0][1] = 0.0;
    cubeVertexArray[0][2] = 1.0;

    cubeVertexArray[1][0] = 0.0;
    cubeVertexArray[1][1] = 1.0;
    cubeVertexArray[1][2] = 1.0;

    cubeVertexArray[2][0] = 1.0;
    cubeVertexArray[2][1] = 1.0;
    cubeVertexArray[2][2] = 1.0;

    cubeVertexArray[3][0] = 1.0;
    cubeVertexArray[3][1] = 0.0;
    cubeVertexArray[3][2] = 1.0;

    cubeVertexArray[4][0] = 0.0;
    cubeVertexArray[4][1] = 0.0;
    cubeVertexArray[4][2] = 0.0;

    cubeVertexArray[5][0] = 0.0;
    cubeVertexArray[5][1] = 1.0;
    cubeVertexArray[5][2] = 0.0;

    cubeVertexArray[6][0] = 1.0;
    cubeVertexArray[6][1] = 1.0;
    cubeVertexArray[6][2] = 0.0;

    cubeVertexArray[7][0] = 1.0;
    cubeVertexArray[7][1] = 0.0;
    cubeVertexArray[7][2] = 0.0;

    cubeTextureArray[0][0] = 0.0;
    cubeTextureArray[0][1] = 0.0;

    cubeTextureArray[1][0] = 1.0;
    cubeTextureArray[1][1] = 0.0;

    cubeTextureArray[2][0] = 1.0;
    cubeTextureArray[2][1] = 1.0;

    cubeTextureArray[3][0] = 0.0;
    cubeTextureArray[3][1] = 1.0;

    cubeIndexArray[0][0] = 0;
    cubeIndexArray[0][1] = 3;
    cubeIndexArray[0][2] = 2;
    cubeIndexArray[0][3] = 1;

    glVertexPointer(3, GL_FLOAT, 0, cubeVertexArray);
    glTexCoordPointer(2, GL_FLOAT, 0, cubeTextureArray);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cubeIndexArray);

    glBindTexture(GL_TEXTURE_2D, textures[1]);

    cubeTextureArray[0][0] = 0.0;
    cubeTextureArray[0][1] = 0.0;

    cubeTextureArray[1][0] = 1.0;
    cubeTextureArray[1][1] = 0.0;

    cubeTextureArray[5][0] = 1.0;
    cubeTextureArray[5][1] = 1.0;

    cubeTextureArray[4][0] = 0.0;
    cubeTextureArray[4][1] = 1.0;

    cubeIndexArray[0][0] = 0;
    cubeIndexArray[0][1] = 1;
    cubeIndexArray[0][2] = 5;
    cubeIndexArray[0][3] = 4;

    glVertexPointer(3, GL_FLOAT, 0, cubeVertexArray);
    glTexCoordPointer(2, GL_FLOAT, 0, cubeTextureArray);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cubeIndexArray);

    glBindTexture(GL_TEXTURE_2D, textures[2]);

    cubeTextureArray[7][0] = 0.0;
    cubeTextureArray[7][1] = 0.0;

    cubeTextureArray[4][0] = 1.0;
    cubeTextureArray[4][1] = 0.0;

    cubeTextureArray[5][0] = 1.0;
    cubeTextureArray[5][1] = 1.0;

    cubeTextureArray[6][0] = 0.0;
    cubeTextureArray[6][1] = 1.0;

    cubeIndexArray[0][0] = 7;
    cubeIndexArray[0][1] = 4;
    cubeIndexArray[0][2] = 5;
    cubeIndexArray[0][3] = 6;

    glVertexPointer(3, GL_FLOAT, 0, cubeVertexArray);
    glTexCoordPointer(2, GL_FLOAT, 0, cubeTextureArray);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cubeIndexArray);

    glBindTexture(GL_TEXTURE_2D, textures[3]);

    cubeTextureArray[3][0] = 0.0;
    cubeTextureArray[3][1] = 0.0;

    cubeTextureArray[7][0] = 1.0;
    cubeTextureArray[7][1] = 0.0;

    cubeTextureArray[6][0] = 1.0;
    cubeTextureArray[6][1] = 1.0;

    cubeTextureArray[2][0] = 0.0;
    cubeTextureArray[2][1] = 1.0;

    cubeIndexArray[0][0] = 3;
    cubeIndexArray[0][1] = 7;
    cubeIndexArray[0][2] = 6;
    cubeIndexArray[0][3] = 2;

    glVertexPointer(3, GL_FLOAT, 0, cubeVertexArray);
    glTexCoordPointer(2, GL_FLOAT, 0, cubeTextureArray);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cubeIndexArray);

    glBindTexture(GL_TEXTURE_2D, textures[4]);

    cubeTextureArray[1][0] = 0.0;
    cubeTextureArray[1][1] = 0.0;

    cubeTextureArray[2][0] = 1.0;
    cubeTextureArray[2][1] = 0.0;

    cubeTextureArray[6][0] = 1.0;
    cubeTextureArray[6][1] = 1.0;

    cubeTextureArray[5][0] = 0.0;
    cubeTextureArray[5][1] = 1.0;

    cubeIndexArray[0][0] = 1;
    cubeIndexArray[0][1] = 2;
    cubeIndexArray[0][2] = 6;
    cubeIndexArray[0][3] = 5;

    glVertexPointer(3, GL_FLOAT, 0, cubeVertexArray);
    glTexCoordPointer(2, GL_FLOAT, 0, cubeTextureArray);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cubeIndexArray);

    glBindTexture(GL_TEXTURE_2D, textures[5]);

    cubeTextureArray[0][0] = 0.0;
    cubeTextureArray[0][1] = 0.0;

    cubeTextureArray[4][0] = 1.0;
    cubeTextureArray[4][1] = 0.0;

    cubeTextureArray[7][0] = 1.0;
    cubeTextureArray[7][1] = 1.0;

    cubeTextureArray[3][0] = 0.0;
    cubeTextureArray[3][1] = 1.0;

    cubeIndexArray[0][0] = 0;
    cubeIndexArray[0][1] = 4;
    cubeIndexArray[0][2] = 7;
    cubeIndexArray[0][3] = 3;

    glVertexPointer(3, GL_FLOAT, 0, cubeVertexArray);
    glTexCoordPointer(2, GL_FLOAT, 0, cubeTextureArray);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cubeIndexArray);
}

void GL_Widget::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    //double dx = (double) (mouseEvent->x() - m_mousePositionX) / (10 * (this->width() / 2));
    //double dy = (double) (mouseEvent->y() - m_mousePositionY) / (10 * (this->height() / 2));

    xAxisRotation += (180 * ((GLfloat)mouseEvent->y() - (GLfloat)pressPosition.y())) / (currentHeight);
    yAxisRotation += (180 * ((GLfloat)mouseEvent->x() - (GLfloat)pressPosition.x())) / (currentWidth);

    pressPosition = mouseEvent->pos();
    updateGL();
}

void GL_Widget::mousePressEvent(QMouseEvent *mouseEvent)
{
    //m_mousePositionX = mouseEvent->x();
    //m_mousePositionY = mouseEvent->y();

    pressPosition = mouseEvent->pos();

    updateGL();
}


/*void GL_Widget::wheelEvent(QWheelEvent *wheelEvent)
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
}*/
