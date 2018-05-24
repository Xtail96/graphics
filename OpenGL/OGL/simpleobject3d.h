#ifndef SIMPLEOBJECT3D_H
#define SIMPLEOBJECT3D_H

#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

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

class SimpleObject3D
{
public:
    SimpleObject3D();
    SimpleObject3D(const QVector<VertexData> &vertexData, const QVector<GLuint> &indexes, const QImage &texture);
    ~SimpleObject3D();

    void init(const QVector<VertexData> &vertexData, const QVector<GLuint> &indexes, const QImage &texture);
    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions);
    void translate(const QVector3D &translateVector);

private:
    QOpenGLBuffer m_vertexBuffer;
    QOpenGLBuffer m_indexBuffer;
    QMatrix4x4 m_modelMatrix;
    QOpenGLTexture *m_texture;
};

#endif // SIMPLEOBJECT3D_H
