#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QVector>
#include <QMouseEvent>
#include <QOpenGLContext>

#include "simpleobject3d.h"
#include "group3d.h"

class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
protected:
    // обязательные функции для переопределения
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent *event);

    void initShaders();
    void initCube(float width);
private:
    // матрица проекции
    QMatrix4x4 m_projectionMatrix;

    // матрица вида
    QMatrix4x4 m_viewMatrix;

    // для подключения шейдеров
    QOpenGLShaderProgram m_program;

    // все объекты на сцене
    QVector<SimpleObject3D*> m_objects;

    // все группы объектов на сцене
    QVector<Group3D*> m_groups;

    // все корневые группы объектов на сцене
    QVector<Transformational*> m_transformObjects;

    // для вращения сцены
    QVector2D m_mousePosition;
    QQuaternion m_rotation;

    // для приближения/отдаления сцены по оси Z
    float m_z;
};

#endif // WIDGET_H
