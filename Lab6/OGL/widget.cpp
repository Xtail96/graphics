#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    m_camera = QSharedPointer<Camera3D>(new Camera3D());
    m_camera->translate(QVector3D(0.0f, 0.0f, -5.0f));
}

Widget::~Widget()
{
    //delete m_camera;
}

void Widget::initializeGL()
{
    // каким цветом будет производиться очистка экрана
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    initShaders();
    initSandGlass2();

    QQuaternion rotation = QQuaternion::fromAxisAndAngle(1.0, 0.0, 0.0, -90);
    for(auto object : m_transformObjects)
    {
        object->rotate(rotation);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);

    //m_transformObjects.append(QSharedPointer<Transformational>(FigureBuilder::initCube(2)));

    //m_timer.start(30, this);
}

void Widget::resizeGL(int w, int h)
{
    float aspect = w / (float) h;
    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(45, aspect, 0.01f, 100.0f);
}

void Widget::paintGL()
{
    // выставляем флаги
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    m_program.bind();
    m_program.setUniformValue("u_projectionMatrix", m_projectionMatrix);
    m_program.setUniformValue("u_lightPosition", QVector4D(0.0, 0.0, 0.0, 1.0));
    m_program.setUniformValue("u_lightPower", 1.0f);

    m_camera->draw(&m_program);

    for(auto object : m_transformObjects)
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

    m_camera->rotate(QQuaternion::fromAxisAndAngle(axis, angle));

    update();
}

void Widget::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
    {
        m_camera->translate(QVector3D(0.0f, 0.0f, 0.25f));
    }
    else
    {
        if(event->delta() < 0)
        {
            m_camera->translate(QVector3D(0.0f, 0.0f, -0.25f));
        }
    }
    update();
}

void Widget::timerEvent(QTimerEvent *event)
{
    /*for(int i = 0; i < m_objects.size(); i++)
    {
        if(i % 2 == 0)
        {
            m_objects[i]->rotate(QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, qSin(m_angleObject)));
            m_objects[i]->rotate(QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, qCos(m_angleObject)));
        }
        else
        {
            m_objects[i]->rotate(QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, qSin(m_angleObject)));
            m_objects[i]->rotate(QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, qCos(m_angleObject)));
        }
    }

    m_groups[0]->rotate(QQuaternion::fromAxisAndAngle(0.0f, 0.0f, 1.0f, qSin(m_angleGroup1)));
    m_groups[0]->rotate(QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, -qSin(m_angleGroup1)));

    m_groups[1]->rotate(QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, qCos(m_angleGroup2)));
    m_groups[1]->rotate(QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, -qCos(m_angleGroup2)));

    m_groups[2]->rotate(QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, qCos(m_angleMain)));
    m_groups[2]->rotate(QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, qCos(m_angleMain)));

    m_angleObject += M_PI / 180.0f;
    m_angleGroup1 += M_PI / 360.0f;
    m_angleGroup2 -= M_PI / 360.0f;
    m_angleMain += M_PI / 720.0f;

    event->accept();
    update();*/
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    /*switch (event->key()) {
    case Qt::Key_Left:
        m_groups[0]->removeObject(m_camera.data());
        m_groups[1]->removeObject(m_camera.data());
        m_transformObjects.removeAll(m_camera);
        m_groups[1]->addObject(m_camera.data());
        break;
    case Qt::Key_Right:
        m_groups[0]->removeObject(m_camera.data());
        m_groups[1]->removeObject(m_camera.data());
        m_transformObjects.removeAll(m_camera);
        m_groups[0]->addObject(m_camera.data());
        break;
    case Qt::Key_Down:
        m_groups[0]->removeObject(m_camera.data());
        m_groups[1]->removeObject(m_camera.data());
        m_transformObjects.removeAll(m_camera);
        m_transformObjects.append(m_camera);
        break;
    case Qt::Key_Up:
        m_groups[0]->removeObject(m_camera.data());
        m_groups[1]->removeObject(m_camera.data());
        m_transformObjects.removeAll(m_camera);
        m_transformObjects.append(m_camera);

        QMatrix4x4 tmp;
        tmp.setToIdentity();
        m_camera->setGlobalTransform(tmp);
        break;
    }

    update();*/
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

void Widget::initWoodenWheel()
{
    m_groups.push_back(QSharedPointer<Group3D>(new Group3D()));

    m_groups.last()->addObject(FigureBuilder::initDiskSector(QVector3D(0.0, 0.0, 0.0), 1, 2 * M_PI));

    QVector3D center1 = QVector3D(0.0, 0.0, 0.0);
    QVector3D center2 = QVector3D(0.0, 0.0, -0.25);
    double r1 = 1;
    double r2 = 1.5;
    double step = 0.1;
    m_groups.last()->addObject(FigureBuilder::initBelt(center1, center2, r1, r2, step));

    center1 = QVector3D(0.0, 0.0, -0.25);
    center2 = QVector3D(0.0, 0.0, -1.0);
    r1 = 1.5;
    r2 = 1.5;
    m_groups.last()->addObject(FigureBuilder::initBelt(center1, center2, r1, r2, step));

    center1 = QVector3D(0.0, 0.0, -1.0);
    center2 = QVector3D(0.0, 0.0, -1.25);
    r1 = 1.5;
    r2 = 1;
    m_groups.last()->addObject(FigureBuilder::initBelt(center1, center2, r1, r2, step));

    m_groups.last()->addObject(FigureBuilder::initDiskSector(center2, r2, 2 * M_PI, 0.1, true));

    m_transformObjects.append(m_groups.last());
}

void Widget::initSandGlass()
{
    m_groups.push_back(QSharedPointer<Group3D>(new Group3D()));
    double radiusDelta = 0.05;

    double rTop = 0.25;
    double rBorder1 = 0.5;
    double rMiddle = 0.05;
    double rBorder2 = 0.5;
    double rBottom = 0.25;

    QVector3D middle = QVector3D(0.0, 0.0, 0.0);

    double radiusCurrent = rMiddle;
    QVector3D currentCenter = middle;
    QVector3D nextCenter = QVector3D(currentCenter.x(),
                                     currentCenter.y(),
                                     currentCenter.z() + 0.5 * radiusCurrent);

    for(double r = rMiddle + radiusDelta; r < rBorder1; r += radiusDelta)
    {
        m_groups.last()->addObject(FigureBuilder::initBelt(nextCenter, currentCenter, r, radiusCurrent));

        radiusCurrent = r;
        currentCenter = nextCenter;

        nextCenter = QVector3D(currentCenter.x(),
                               currentCenter.y(),
                               currentCenter.z() + 0.5 * r);
    }


    //currentCenter = nextCenter;
    nextCenter = QVector3D(currentCenter.x(),
                           currentCenter.y(),
                           currentCenter.z() + 0.25);
    m_groups.last()->addObject(FigureBuilder::initBelt(nextCenter,
                                                       currentCenter,
                                                       rBorder1,
                                                       rBorder1));

    radiusDelta = 0.01;
    for(double r = radiusCurrent + radiusDelta; r > rTop; r -= radiusDelta)
    {
        m_groups.last()->addObject(FigureBuilder::initBelt(nextCenter, currentCenter, r, radiusCurrent));

        radiusCurrent = r;
        currentCenter = nextCenter;

        nextCenter = QVector3D(currentCenter.x(),
                               currentCenter.y(),
                               currentCenter.z() + 0.1 * r * r);
    }
    m_groups.last()->addObject(FigureBuilder::initDiskSector(currentCenter, radiusCurrent, 2 * M_PI));


    radiusDelta = 0.05;
    radiusCurrent = rMiddle;
    currentCenter = middle;
    nextCenter = QVector3D(currentCenter.x(),
                           currentCenter.y(),
                           currentCenter.z() - 0.5 * radiusCurrent);

    for(double r = rMiddle + radiusDelta; r < rBorder2; r += radiusDelta)
    {
        m_groups.last()->addObject(FigureBuilder::initBelt(currentCenter, nextCenter, radiusCurrent, r));

        radiusCurrent = r;
        currentCenter = nextCenter;

        nextCenter = QVector3D(currentCenter.x(),
                               currentCenter.y(),
                               currentCenter.z() - 0.5 * r);
    }

    nextCenter = QVector3D(currentCenter.x(),
                           currentCenter.y(),
                           currentCenter.z() - 0.25);
    m_groups.last()->addObject(FigureBuilder::initBelt(currentCenter,
                                                       nextCenter,
                                                       rBorder1,
                                                       rBorder1));

    radiusDelta = 0.01;
    for(double r = radiusCurrent + radiusDelta; r > rBottom; r -= radiusDelta)
    {
        m_groups.last()->addObject(FigureBuilder::initBelt(currentCenter, nextCenter, radiusCurrent, r));

        radiusCurrent = r;
        currentCenter = nextCenter;

        nextCenter = QVector3D(currentCenter.x(),
                               currentCenter.y(),
                               currentCenter.z() - 0.1 * r * r);
    }
    m_groups.last()->addObject(FigureBuilder::initDiskSector(currentCenter, radiusCurrent, 2 * M_PI, 0.1, true));

    m_transformObjects.append(m_groups.last());
}

void Widget::initSandGlass2(double lowerBound, double upperBound, double c, double delta)
{
    QList<QVector3D> curvePoints;

    for(double x = lowerBound - delta; x <= upperBound + delta; x += delta)
    {
        curvePoints.push_back(QVector3D(FigureBuilder::calculteLemniscatePoint(x, c), 0.0, x));
    }

    m_groups.push_back(QSharedPointer<Group3D>(new Group3D()));

    for(int i = 0; i < curvePoints.size() - 1; i++)
    {
        //double r = curvePoints[i + 1].x() - curvePoints[i].x();
        double r1 = curvePoints[i].x();
        double r2 = curvePoints[i + 1].x();

        QVector3D center1 = QVector3D(0.0, 0.0, curvePoints[i].z());
        QVector3D center2 = QVector3D(0.0, 0.0, curvePoints[i + 1].z());
        m_groups.last()->addObject(FigureBuilder::initBelt(center2, center1, r2, r1));
    }

    double r = curvePoints.first().x();
    QVector3D center = QVector3D(0.0, 0.0, curvePoints.first().z());
    m_groups.last()->addObject(FigureBuilder::initDiskSector(center, r, 2 * M_PI, 0.1, true));

    r = curvePoints.last().x();
    center = QVector3D(0.0, 0.0, curvePoints.last().z());
    m_groups.last()->addObject(FigureBuilder::initDiskSector(center, r, 2 * M_PI, 0.1, false));

    m_transformObjects.append(m_groups.last());
}
