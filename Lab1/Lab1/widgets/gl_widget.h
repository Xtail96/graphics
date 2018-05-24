#ifndef GL_WINDGET_H
#define GL_WINDGET_H

#include <QGLWidget>
#include <QDebug>
#include <QPoint>
#include <QMouseEvent>
#include <QOpenGLShaderProgram>

class GL_Widget: public QGLWidget
{
    Q_OBJECT
private:
    QOpenGLShaderProgram *m_program;

    GLfloat cubeVertexArray[8][3];
    GLfloat cubeColorArray[8][3];
    GLubyte cubeIndexArray[6][4];
    GLfloat cubeTextureArray[8][2];

    // events variable
    QPoint pressPosition;
    QPoint releasePosition;
    GLfloat xAxisRotation;
    GLfloat yAxisRotation;
    GLfloat currentWidth;
    GLfloat currentHeight;
    GLuint texture;
    double m_scale = 1;

    void initTextures();

public:
    explicit GL_Widget(QWidget *parent = 0);
    ~GL_Widget();

    void initializeGL();
    void resizeGL(int nWidth, int nHeight);

    void initShaders();

    void paintGL();

public slots:

    void wheelEvent(QWheelEvent *wheelEvent);

    void mouseMoveEvent(QMouseEvent *mouseEvent);
    void mousePressEvent(QMouseEvent *mouseEvent);

protected slots:
    void scaling(int delta);

public slots:
};

#endif // GL_WINDGET_H
