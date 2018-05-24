#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QVector>
#include <QMouseEvent>

// структура для описания вершины
struct VertexData
{
    VertexData()
    {
    }

    VertexData(QVector3D p, QVector2D t, QVector3D n) :
        position(p),
        texCoords(t),
        normal(n)
    {
    }

    // координаты в трехмерном пространстве
    QVector3D position;

    // координаты накладываемой текстуры
    QVector2D texCoords;

    // координаты вектора-нормали в трехмерном пространстве для текущей вершины
    QVector3D normal;
};


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

    void initShaders();
    void initCube(float width);
private:
    // матрица проекции
    QMatrix4x4 m_projectionMatrix;

    // матрица вида
    QMatrix4x4 m_viewMatrix;

    // матрица модели
    QMatrix4x4 m_modelMatrix;

    // для подключения шейдеров
    QOpenGLShaderProgram m_program;

    // для наложения текстуры
    QOpenGLTexture *m_texture;

    // для отрисовки куба
    QOpenGLBuffer m_arrayBuffer;
    QOpenGLBuffer m_indexBuffer;

    // для вращения сцены
    QVector2D m_mousePosition;
    QQuaternion m_rotation;
};

#endif // WIDGET_H
