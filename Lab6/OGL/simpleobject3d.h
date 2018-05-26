#ifndef SIMPLEOBJECT3D_H
#define SIMPLEOBJECT3D_H

#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QtMath>

#include "transformational.h"

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

class SimpleObject3D : public Transformational
{
public:
    SimpleObject3D();
    SimpleObject3D(const QVector<VertexData> &vertexData, const QVector<GLuint> &indexes, const QImage &texture);
    ~SimpleObject3D();

    void init(const QVector<VertexData> &vertexData, const QVector<GLuint> &indexes, const QImage &texture);

    void rotate(const QQuaternion &r) override;
    void translate(const QVector3D &t) override;
    void scale(const float &s) override;
    void setGlobalTransform(const QMatrix4x4 &g) override;
    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions) override;

    static QVector2D rotateMatrix(QVector2D point, double angle);

private:
    QOpenGLBuffer m_vertexBuffer;
    QOpenGLBuffer m_indexBuffer;
    QOpenGLTexture *m_texture;

    // составляющие модельно-видовой матрицы
    QQuaternion m_rotate;
    QVector3D m_translate;
    float m_scale;
    QMatrix4x4 m_globalTransform;
};

#endif // SIMPLEOBJECT3D_H
