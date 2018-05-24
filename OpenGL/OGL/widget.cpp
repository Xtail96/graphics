#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent),
      m_texture(0),
      m_arrayBuffer(QOpenGLBuffer::VertexBuffer),
      m_indexBuffer(QOpenGLBuffer::IndexBuffer)
{

}

Widget::~Widget()
{

}

void Widget::initializeGL()
{
    // каким цветом будет производиться очистка экрана
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    initShaders();
    initCube(1.0f);
}

void Widget::resizeGL(int w, int h)
{
    float aspect = w / (float) h;
    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(45, aspect, 0.1f, 10.0f);
}

void Widget::paintGL()
{
    // выставляем флаги
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_viewMatrix.setToIdentity();
    m_viewMatrix.translate(0.0, 0.0, -5.0);
    m_viewMatrix.rotate(m_rotation);

    // привязка текстуры 0 - номер текстуры
    m_texture->bind(0);

    m_program.bind();
    m_program.setUniformValue("u_projectionMatrix", m_projectionMatrix);
    m_program.setUniformValue("u_viewMatrix", m_viewMatrix);
    m_modelMatrix.setToIdentity();
    m_program.setUniformValue("u_modelMatrix", m_modelMatrix);
    m_program.setUniformValue("u_lightPosition", QVector4D(0.0, 0.0, 0.0, 1.0));
    m_program.setUniformValue("u_lightPower", 5.0f);

    // инициалиация текстуры в шейдере, 0 - номер текстуры (тот же что и при teture->bind)
    m_program.setUniformValue("u_texture", 0);

    m_arrayBuffer.bind();
    int offset = 0;

    int vertexLocation = m_program.attributeLocation("a_position");
    m_program.enableAttributeArray(vertexLocation);
    m_program.setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int textureLocation = m_program.attributeLocation("a_texcoord");
    m_program.enableAttributeArray(textureLocation);
    m_program.setAttributeBuffer(textureLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    offset += sizeof(QVector2D);

    int normalLocation = m_program.attributeLocation("a_normal");
    m_program.enableAttributeArray(normalLocation);
    m_program.setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    m_indexBuffer.bind();
    glDrawElements(GL_TRIANGLES, m_indexBuffer.size(), GL_UNSIGNED_INT, 0);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        m_mousePosition = QVector2D(event->localPos());
    }
    event->accept();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() != Qt::LeftButton)
    {
        return;
    }

    QVector2D diff = QVector2D(event->localPos()) - m_mousePosition;
    m_mousePosition = QVector2D(event->localPos());

    float angle = diff.length() / 2.0;

    // вектор, вокруг которого выполняется поворот, перпендикулярен направлению движения мыши
    QVector3D axis = QVector3D(diff.y(), diff.x(), 0.0);

    m_rotation = QQuaternion::fromAxisAndAngle(axis, angle) * m_rotation;

    update();
}

void Widget::initShaders()
{
    if(!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.vsh"))
    {
        qDebug() << "can not compile vertex shader";
        this->close();
    }

    if(!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.fsh"))
    {
        qDebug() << "can not compile fragment shader";
        this->close();
    }

    if(!m_program.link())
    {
        qDebug() << "can not link shader program";
        this->close();
    }
}

void Widget::initCube(float width)
{
    float width_div_2 = width / 2.0f;
    QVector<VertexData> vertexes;

    vertexes.append(VertexData(QVector3D(-width_div_2,
                                         width_div_2,
                                         width_div_2),
                               QVector2D(0.0, 1.0),
                               QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,
                                         -width_div_2,
                                         width_div_2),
                               QVector2D(0.0, 0.0),
                               QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,
                                         width_div_2,
                                         width_div_2),
                               QVector2D(1.0, 1.0),
                               QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,
                                         -width_div_2,
                                         width_div_2),
                               QVector2D(1.0, 0.0),
                               QVector3D(0.0, 0.0, 1.0)));





    vertexes.append(VertexData(QVector3D(width_div_2,
                                         width_div_2,
                                         width_div_2),
                               QVector2D(0.0, 1.0),
                               QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,
                                         -width_div_2,
                                         width_div_2),
                               QVector2D(0.0, 0.0),
                               QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,
                                         width_div_2,
                                         -width_div_2),
                               QVector2D(1.0, 1.0),
                               QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,
                                         -width_div_2,
                                         -width_div_2),
                               QVector2D(1.0, 0.0),
                               QVector3D(1.0, 0.0, 0.0)));



    vertexes.append(VertexData(QVector3D(width_div_2,
                                         width_div_2,
                                         width_div_2),
                               QVector2D(0.0, 1.0),
                               QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,
                                         width_div_2,
                                         -width_div_2),
                               QVector2D(0.0, 0.0),
                               QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,
                                         width_div_2,
                                         width_div_2),
                               QVector2D(1.0, 1.0),
                               QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,
                                         width_div_2,
                                         -width_div_2),
                               QVector2D(1.0, 0.0),
                               QVector3D(0.0, 1.0, 0.0)));


    vertexes.append(VertexData(QVector3D(width_div_2,
                                         width_div_2,
                                         -width_div_2),
                               QVector2D(0.0, 1.0),
                               QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,
                                         -width_div_2,
                                         -width_div_2),
                               QVector2D(0.0, 0.0),
                               QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,
                                         width_div_2,
                                         -width_div_2),
                               QVector2D(1.0, 1.0),
                               QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,
                                         -width_div_2,
                                         -width_div_2),
                               QVector2D(1.0, 0.0),
                               QVector3D(0.0, 0.0, -1.0)));


    vertexes.append(VertexData(QVector3D(-width_div_2,
                                         width_div_2,
                                         width_div_2),
                               QVector2D(0.0, 1.0),
                               QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,
                                         width_div_2,
                                         -width_div_2),
                               QVector2D(0.0, 0.0),
                               QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,
                                         -width_div_2,
                                         width_div_2),
                               QVector2D(1.0, 1.0),
                               QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,
                                         -width_div_2,
                                         -width_div_2),
                               QVector2D(1.0, 0.0),
                               QVector3D(-1.0, 0.0, 0.0)));


    vertexes.append(VertexData(QVector3D(-width_div_2,
                                         -width_div_2,
                                         width_div_2),
                               QVector2D(0.0, 1.0),
                               QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,
                                         -width_div_2,
                                         -width_div_2),
                               QVector2D(0.0, 0.0),
                               QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,
                                         -width_div_2,
                                         width_div_2),
                               QVector2D(1.0, 1.0),
                               QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,
                                         -width_div_2,
                                         -width_div_2),
                               QVector2D(1.0, 0.0),
                               QVector3D(0.0, -1.0, 0.0)));



    QVector<GLuint> indexes;
    for(int i = 0; i < 24; i += 4)
    {
        indexes.append(i + 0);
        indexes.append(i + 1);
        indexes.append(i + 2);
        indexes.append(i + 2);
        indexes.append(i + 1);
        indexes.append(i + 3);
    }

    m_arrayBuffer.create();
    m_arrayBuffer.bind();
    m_arrayBuffer.allocate(vertexes.constData(), vertexes.size() * sizeof(VertexData));
    m_arrayBuffer.release();

    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));
    m_indexBuffer.release();

    // загрузка и настройка текстуры
    m_texture = new QOpenGLTexture(QImage(":/123.jpg").mirrored());
    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_texture->setWrapMode(QOpenGLTexture::Repeat);
}
