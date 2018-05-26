#ifndef GROUP3D_H
#define GROUP3D_H

#include <QVector>
#include <QQuaternion>
#include <QVector3D>
#include <QMatrix4x4>

#include "transformational.h"

class Group3D : public Transformational
{
public:
    Group3D();
    ~Group3D();

    void rotate(const QQuaternion &r) override;
    void translate(const QVector3D &t) override;
    void scale(const float &s) override;
    void setGlobalTransform(const QMatrix4x4 &g) override;
    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions) override;

    void addObject(Transformational* obj);
    void removeObject(Transformational* obj);
    void removeObject(int index);
private:
    // составляющие модельно-видовой матрицы
    QQuaternion m_rotate;
    QVector3D m_translate;
    float m_scale;
    QMatrix4x4 m_globalTransform;

    QVector<Transformational*> m_objects;

    void setViewMatrix();
};

#endif // GROUP3D_H
