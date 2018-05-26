#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
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
    initCube(2.0f);
    m_objects[0]->translate(QVector3D(-1.5, 0.0, 0.0));

    initCube(2.0f);
    m_objects[1]->translate(QVector3D(1.5, 0.0, 0.0));
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

    m_program.bind();
    m_program.setUniformValue("u_projectionMatrix", m_projectionMatrix);
    m_program.setUniformValue("u_viewMatrix", m_viewMatrix);
    m_program.setUniformValue("u_lightPosition", QVector4D(0.0, 0.0, 0.0, 1.0));
    m_program.setUniformValue("u_lightPower", 5.0f);

    for(auto object : m_objects)
    {
        object->draw(&m_program, context()->functions());
    }
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

    m_objects.append(new SimpleObject3D(vertexes, indexes, QImage(":/123.jpg")));
}
