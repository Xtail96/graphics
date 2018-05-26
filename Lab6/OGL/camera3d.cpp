#include "camera3d.h"

Camera3D::Camera3D()
{
   m_scale = 1.0f;
   m_globalTransform.setToIdentity();
}

Camera3D::~Camera3D()
{

}

void Camera3D::rotate(const QQuaternion &r)
{
    m_rotate = r * m_rotate;
    setViewMatrix();
}

void Camera3D::translate(const QVector3D &t)
{
    m_translate += t;
    setViewMatrix();
}

void Camera3D::scale(const float &s)
{
    m_scale *= s;
    setViewMatrix();
}

void Camera3D::setGlobalTransform(const QMatrix4x4 &g)
{
    m_globalTransform = g;
    setViewMatrix();
}

void Camera3D::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions)
{
    if(functions != 0)
    {
        return;
    }

    program->setUniformValue("u_viewMatrix", m_viewMatrix);
}

void Camera3D::setViewMatrix()
{
    m_viewMatrix.setToIdentity();
    m_viewMatrix.translate(m_translate);
    m_viewMatrix.rotate(m_rotate);
    m_viewMatrix.scale(m_scale);
    m_viewMatrix = m_viewMatrix * m_globalTransform.inverted();
}
