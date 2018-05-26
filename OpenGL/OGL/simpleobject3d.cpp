#include "simpleobject3d.h"

SimpleObject3D::SimpleObject3D() :
    m_vertexBuffer(QOpenGLBuffer::VertexBuffer),
    m_indexBuffer(QOpenGLBuffer::IndexBuffer),
    m_texture(0),
    m_scale(1.0f)
{

}

SimpleObject3D::SimpleObject3D(const QVector<VertexData> &vertexData, const QVector<GLuint> &indexes, const QImage &texture) :
    m_vertexBuffer(QOpenGLBuffer::VertexBuffer),
    m_indexBuffer(QOpenGLBuffer::IndexBuffer),
    m_texture(0),
    m_scale(1.0f)
{
    init(vertexData, indexes, texture);
}

SimpleObject3D::~SimpleObject3D()
{
    if(m_vertexBuffer.isCreated())
    {
        m_vertexBuffer.destroy();
    }

    if(m_indexBuffer.isCreated())
    {
        m_indexBuffer.destroy();
    }

    if(m_texture != 0)
    {
        if(m_texture->isCreated())
        {
            m_texture->destroy();
        }
    }
}

void SimpleObject3D::init(const QVector<VertexData> &vertexData, const QVector<GLuint> &indexes, const QImage &texture)
{
    if(m_vertexBuffer.isCreated())
    {
        m_vertexBuffer.destroy();
    }

    if(m_indexBuffer.isCreated())
    {
        m_indexBuffer.destroy();
    }

    if(m_texture != 0)
    {
        if(m_texture->isCreated())
        {
            delete m_texture;
            m_texture = 0;
        }
    }

    m_vertexBuffer.create();
    m_vertexBuffer.bind();
    m_vertexBuffer.allocate(vertexData.constData(), vertexData.size() * sizeof(VertexData));
    m_vertexBuffer.release();

    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));
    m_indexBuffer.release();

    m_texture = new QOpenGLTexture(texture.mirrored());
    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_texture->setWrapMode(QOpenGLTexture::Repeat);
}

void SimpleObject3D::rotate(const QQuaternion &r)
{
    m_rotate = r * m_rotate;
}

void SimpleObject3D::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions)
{
    if(!m_vertexBuffer.isCreated() || !m_indexBuffer.isCreated())
    {
        return;
    }

    m_texture->bind(0);
    program->setUniformValue("u_texture", 0);


    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();

    // важен порядок выполнения
    modelMatrix.translate(m_translate);
    modelMatrix.rotate(m_rotate);
    modelMatrix.scale(m_scale);
    modelMatrix = m_globalTransform * modelMatrix;

    program->setUniformValue("u_modelMatrix", modelMatrix);

    m_vertexBuffer.bind();

    int offset = 0;

    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int textureLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(textureLocation);
    program->setAttributeBuffer(textureLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    offset += sizeof(QVector2D);

    int normalLocation = program->attributeLocation("a_normal");
    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    m_indexBuffer.bind();
    functions->glDrawElements(GL_TRIANGLES, m_indexBuffer.size(), GL_UNSIGNED_INT, 0);

    m_vertexBuffer.release();
    m_indexBuffer.release();
    m_texture->release();
}

void SimpleObject3D::translate(const QVector3D &t)
{
    m_translate += t;
}

void SimpleObject3D::scale(const float &s)
{
    m_scale *= s;
}

void SimpleObject3D::setGlobalTransform(const QMatrix4x4 &g)
{
    m_globalTransform = g;
}
