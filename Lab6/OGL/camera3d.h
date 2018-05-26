#ifndef CAMERA3D_H
#define CAMERA3D_H

#include <QVector>
#include <QQuaternion>
#include <QVector3D>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

#include "transformational.h"

class Camera3D : public Transformational
{
public:
    Camera3D();
    ~Camera3D();

    void rotate(const QQuaternion &r) override;
    void translate(const QVector3D &t) override;
    void scale(const float &s) override;
    void setGlobalTransform(const QMatrix4x4 &g) override;
    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions = 0) override;

    void setViewMatrix();
private:
    // составляющие модельно-видовой матрицы
    QQuaternion m_rotate;
    QVector3D m_translate;
    float m_scale;
    QMatrix4x4 m_globalTransform;

    QMatrix4x4 m_viewMatrix;
};

#endif // CAMERA3D_H
