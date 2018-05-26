#include "group3d.h"

Group3D::Group3D()
{
    m_scale = 1.0;
}

Group3D::~Group3D()
{

}

void Group3D::rotate(const QQuaternion &r)
{
    m_rotate = r * m_rotate;
    setViewMatrix();
}

void Group3D::translate(const QVector3D &t)
{
    m_translate += t;
    setViewMatrix();
}

void Group3D::scale(const float &s)
{
    m_scale *= s;
    setViewMatrix();
}

void Group3D::setGlobalTransform(const QMatrix4x4 &g)
{
    m_globalTransform = g;
    setViewMatrix();
}

void Group3D::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions)
{
    /*QMatrix4x4 localMatrix;
    localMatrix.setToIdentity();
    localMatrix.translate(m_translate);
    localMatrix.rotate(m_rotate);
    localMatrix.scale(m_scale);
    localMatrix= m_globalTransform * localMatrix;

    for(auto object : m_objects)
    {
        object->setGlobalTransform(localMatrix);
        object->draw(program, functions);
    }*/

    for(auto object : m_objects)
    {
        object->draw(program, functions);
    }
}

void Group3D::addObject(Transformational *obj)
{
    QMatrix4x4 viewMatrix;
    viewMatrix.setToIdentity();
    viewMatrix.translate(m_translate);
    viewMatrix.rotate(m_rotate);
    viewMatrix.scale(m_scale);
    viewMatrix= m_globalTransform * viewMatrix;

    obj->setGlobalTransform(viewMatrix);

    m_objects.append(obj);
}

void Group3D::removeObject(Transformational *obj)
{
    m_objects.removeAll(obj);
}

void Group3D::removeObject(int index)
{
    m_objects.remove(index);
}

void Group3D::setViewMatrix()
{
    QMatrix4x4 viewMatrix;
    viewMatrix.setToIdentity();
    viewMatrix.translate(m_translate);
    viewMatrix.rotate(m_rotate);
    viewMatrix.scale(m_scale);
    viewMatrix= m_globalTransform * viewMatrix;

    for(auto object : m_objects)
    {
        object->setGlobalTransform(viewMatrix);
    }
}
