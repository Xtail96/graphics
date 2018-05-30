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
    //glEnable(GL_CULL_FACE);

    double precision = 0.1;

    std::random_device rd;
    std::mt19937 random(rd());
    std::uniform_real_distribution<double> randomZ(0, 0.7);
    std::uniform_int_distribution<double> randomTextureIndex(0, 2);

    QImage texture = QImage(":123.jpg");

    initShaders();
    initSandGlass2(-1.0, 1.0, 0.9, precision);
    //initBook(QVector3D(0.0, 0.0, -1.4), QVector3D(0.0, 0.0, -2.0), 3, 4, 0.01);
    initSimpleBook(texture, QVector3D(0.0, 0.0, -1.4), QVector3D(0.0, 0.0, -2.0), 3, 4, precision);

    double topBorder = -2.0 - precision;
    double bottomBorder = -3.0;

    for(int i = 0; i < 14; i++)
    {
        int textureIndex = randomTextureIndex(random);
        switch (textureIndex) {
        case 0:
            texture = QImage(":123.jpg");
            break;
        case 1:
            texture = QImage(":glass2.jpg");
            break;
        case 2:
            texture = QImage(":paper2.jpg");
            break;
        default:
            texture = QImage(":123.jpg");
            break;
        }

        initSimpleBook(texture, QVector3D(0.0, 0.0, topBorder), QVector3D(0.0, 0.0, bottomBorder), 3, 4, precision);

        if(i % 2 != 0)
        {
            m_groups.last()->rotate(QQuaternion::fromAxisAndAngle(0.0, 0.0, 1.0, -10 - i * 10));
        }
        else
        {
            m_groups.last()->rotate(QQuaternion::fromAxisAndAngle(0.0, 0.0, 1.0, 10 + i * 10));
        }

        topBorder = bottomBorder - precision;
        bottomBorder = bottomBorder - (1 - randomZ(random));
    }

    //initStairs(QVector3D(0.0, -2.0, 0.0), QVector3D(0.0, -5.0, -10.0), 1, 1);
    initStairs(QVector3D(0.0, -1.75, -1.0), 1, -topBorder, 0.15, 1, -15);

    QQuaternion rotation = QQuaternion::fromAxisAndAngle(1.0, 0.0, 0.0, -90);
    for(auto object : m_transformObjects)
    {
        object->rotate(rotation);
        object->scale(0.125);
    }






    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);

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

    m_groups.last()->addObject(FigureBuilder::initDiskSector(QImage(":/123.jpg"), QVector3D(0.0, 0.0, 0.0), 1, 2 * M_PI));

    QVector3D center1 = QVector3D(0.0, 0.0, 0.0);
    QVector3D center2 = QVector3D(0.0, 0.0, -0.25);
    double r1 = 1;
    double r2 = 1.5;
    double step = 0.1;
    m_groups.last()->addObject(FigureBuilder::initBelt(QImage(":/123.jpg"), center1, center2, r1, r2, step));

    center1 = QVector3D(0.0, 0.0, -0.25);
    center2 = QVector3D(0.0, 0.0, -1.0);
    r1 = 1.5;
    r2 = 1.5;
    m_groups.last()->addObject(FigureBuilder::initBelt(QImage(":/123.jpg"), center1, center2, r1, r2, step));

    center1 = QVector3D(0.0, 0.0, -1.0);
    center2 = QVector3D(0.0, 0.0, -1.25);
    r1 = 1.5;
    r2 = 1;
    m_groups.last()->addObject(FigureBuilder::initBelt(QImage(":/123.jpg"), center1, center2, r1, r2, step));

    m_groups.last()->addObject(FigureBuilder::initDiskSector(QImage(":/123.jpg"), center2, r2, 2 * M_PI, 0.1, true));

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
        m_groups.last()->addObject(FigureBuilder::initBelt(QImage(":/123.jpg"), nextCenter, currentCenter, r, radiusCurrent));

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
    m_groups.last()->addObject(FigureBuilder::initBelt(QImage(":/123.jpg"),
                                                       nextCenter,
                                                       currentCenter,
                                                       rBorder1,
                                                       rBorder1));

    radiusDelta = 0.01;
    for(double r = radiusCurrent + radiusDelta; r > rTop; r -= radiusDelta)
    {
        m_groups.last()->addObject(FigureBuilder::initBelt(QImage(":/123.jpg"), nextCenter, currentCenter, r, radiusCurrent));

        radiusCurrent = r;
        currentCenter = nextCenter;

        nextCenter = QVector3D(currentCenter.x(),
                               currentCenter.y(),
                               currentCenter.z() + 0.1 * r * r);
    }
    m_groups.last()->addObject(FigureBuilder::initDiskSector(QImage(":/123.jpg"), currentCenter, radiusCurrent, 2 * M_PI));


    radiusDelta = 0.05;
    radiusCurrent = rMiddle;
    currentCenter = middle;
    nextCenter = QVector3D(currentCenter.x(),
                           currentCenter.y(),
                           currentCenter.z() - 0.5 * radiusCurrent);

    for(double r = rMiddle + radiusDelta; r < rBorder2; r += radiusDelta)
    {
        m_groups.last()->addObject(FigureBuilder::initBelt(QImage(":/123.jpg"), currentCenter, nextCenter, radiusCurrent, r));

        radiusCurrent = r;
        currentCenter = nextCenter;

        nextCenter = QVector3D(currentCenter.x(),
                               currentCenter.y(),
                               currentCenter.z() - 0.5 * r);
    }

    nextCenter = QVector3D(currentCenter.x(),
                           currentCenter.y(),
                           currentCenter.z() - 0.25);
    m_groups.last()->addObject(FigureBuilder::initBelt(QImage(":/123.jpg"),
                                                       currentCenter,
                                                       nextCenter,
                                                       rBorder1,
                                                       rBorder1));

    radiusDelta = 0.01;
    for(double r = radiusCurrent + radiusDelta; r > rBottom; r -= radiusDelta)
    {
        m_groups.last()->addObject(FigureBuilder::initBelt(QImage(":/123.jpg"), currentCenter, nextCenter, radiusCurrent, r));

        radiusCurrent = r;
        currentCenter = nextCenter;

        nextCenter = QVector3D(currentCenter.x(),
                               currentCenter.y(),
                               currentCenter.z() - 0.1 * r * r);
    }
    m_groups.last()->addObject(FigureBuilder::initDiskSector(QImage(":/123.jpg"), currentCenter, radiusCurrent, 2 * M_PI, 0.1, true));

    m_transformObjects.append(m_groups.last());
}

void Widget::initSandGlass2(double lowerBound, double upperBound, double c, double delta)
{
    // рисуем силуэт часов
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
        m_groups.last()->addObject(FigureBuilder::initBelt(QImage(":/paper2.jpg"), center2, center1, r2, r1));
    }

    // рисуем верх и низ часов
    double r = curvePoints.first().x();
    QVector3D center1 = QVector3D(0.0, 0.0, curvePoints.first().z());
    m_groups.last()->addObject(FigureBuilder::initDiskSector(QImage(":/paper2.jpg"), center1, r, 2 * M_PI, 0.1, true));
    r = curvePoints.last().x();
    center1 = QVector3D(0.0, 0.0, curvePoints.last().z());
    m_groups.last()->addObject(FigureBuilder::initDiskSector(QImage(":/paper2.jpg"), center1, r, 2 * M_PI, 0.1, false));

    // рисуем каркас вокруг часов
    r = curvePoints.first().x() * 2;
    center1 = QVector3D(0.0, 0.0, curvePoints.first().z());
    QVector3D center2 = center1;
    center2.setZ(center1.z() - 0.25);
    m_groups.last()->addObject(FigureBuilder::initBelt(QImage(":/123.jpg"), center1, center2, r, r, 0.1));
    m_groups.last()->addObject(FigureBuilder::initDiskSector(QImage(":/123.jpg"), center1, r, 2 * M_PI, 0.1, false));
    m_groups.last()->addObject(FigureBuilder::initDiskSector(QImage(":/123.jpg"), center2, r, 2 * M_PI, 0.1, true));

    r = curvePoints.last().x() * 2;
    center1 = QVector3D(0.0, 0.0, curvePoints.last().z());
    center2 = center1;
    center2.setZ(center1.z() + 0.25);
    m_groups.last()->addObject(FigureBuilder::initBelt(QImage(":/123.jpg"), center2, center1, r, r, 0.1));
    m_groups.last()->addObject(FigureBuilder::initDiskSector(QImage(":/123.jpg"), center1, r, 2 * M_PI, 0.1, true));
    m_groups.last()->addObject(FigureBuilder::initDiskSector(QImage(":/123.jpg"), center2, r, 2 * M_PI, 0.1, false));

    double offset = 0.1;
    r = 0.05;
    center1 = QVector3D(curvePoints.last().x() + offset, curvePoints.last().x() + offset, curvePoints.last().z());
    center2 = QVector3D(curvePoints.first().x() + offset, curvePoints.first().x() + offset, curvePoints.first().z());
    SimpleObject3D* obj = FigureBuilder::initBelt(QImage(":/123.jpg"), center2, center1, r, r, 0.1);
    m_groups.last()->addObject(obj);

    center1 = QVector3D(curvePoints.last().x() + offset, curvePoints.last().x() + offset, curvePoints.last().z());
    center2 = QVector3D(curvePoints.first().x() + offset, curvePoints.first().x() + offset, curvePoints.first().z());
    obj = FigureBuilder::initBelt(QImage(":/123.jpg"), center2, center1, r, r, 0.1);
    obj->rotate(QQuaternion::fromAxisAndAngle(0.0, 0.0, 1.0, 120));
    m_groups.last()->addObject(obj);

    center1 = QVector3D(curvePoints.last().x() + offset, curvePoints.last().x() + offset, curvePoints.last().z());
    center2 = QVector3D(curvePoints.first().x() + offset, curvePoints.first().x() + offset, curvePoints.first().z());
    obj = FigureBuilder::initBelt(QImage(":/123.jpg"), center2, center1, r, r, 0.1);
    obj->rotate(QQuaternion::fromAxisAndAngle(0.0, 0.0, 1.0, -120));
    m_groups.last()->addObject(obj);

    m_transformObjects.append(m_groups.last());
}

void Widget::initBook(QVector3D centerTop, QVector3D centerBottom, double sideX, double sideY, double delta)
{
    m_groups.push_back(QSharedPointer<Group3D>(new Group3D));

    double offset = std::fabs(std::fabs(centerTop.z()) - std::fabs(centerBottom.z()));

    QVector3D centerMiddle = QVector3D(centerTop.x() - centerBottom.x(), centerTop.y() - centerBottom.y(), centerBottom.z() + offset / 2);
    QVector3D center = QVector3D(0.0, 0.0, centerBottom.z());

    for(double z = centerBottom.z() + delta; z <= centerMiddle.z(); z += delta)
    {
        center = QVector3D(center.x() + delta / 2.5, center.y(), z);
        m_groups.last()->addObject(FigureBuilder::initParallelepiped(QImage(":paper1.jpg"),
                                                                     center,
                                                                     sideX - delta * 10, sideY - delta * 10, delta));
        // часть корешка книги
        QVector3D rootCenter = QVector3D((center.x() + (sideX - delta * 10) / 2 + delta / 2),
                                         (center.y()),
                                         (center.z()));
        m_groups.last()->addObject(FigureBuilder::initParallelepiped(QImage(":123.jpg"),
                                                                     rootCenter,
                                                                     delta * 5, sideY, delta));

    }

    center.setZ(center.z() + delta);

    for(double z = center.z() + delta; z < centerTop.z(); z += delta)
    {
        m_groups.last()->addObject(FigureBuilder::initParallelepiped(QImage(":paper1.jpg"),
                                                                     center,
                                                                     sideX - delta * 10, sideY - delta * 10, delta));

        // часть корешка книги
        QVector3D rootCenter = QVector3D((center.x() + (sideX - delta * 10) / 2 + delta / 2),
                                         (center.y()),
                                         (center.z()));
        m_groups.last()->addObject(FigureBuilder::initParallelepiped(QImage(":123.jpg"),
                                                                     rootCenter,
                                                                     delta * 5, sideY, delta));
        center = QVector3D(center.x() - delta / 2.5, center.y(), z);
    }

    m_groups.last()->addObject(FigureBuilder::initParallelepiped(QImage(":123.jpg"), centerTop, sideX, sideY, 0.1));
    m_groups.last()->addObject(FigureBuilder::initParallelepiped(QImage(":123.jpg"), centerBottom, sideX, sideY, 0.1));
    m_transformObjects.append(m_groups.last());
}

void Widget::initSimpleBook(const QImage &texture, QVector3D centerTop, QVector3D centerBottom, double sideX, double sideY, double delta)
{
    m_groups.push_back(QSharedPointer<Group3D>(new Group3D));
    double offset = std::fabs(std::fabs(centerTop.z()) - std::fabs(centerBottom.z())) - delta;

    m_groups.last()->addObject(FigureBuilder::initParallelepiped(texture, centerTop, sideX, sideY, delta));

    //qDebug() << offset << centerTop.z() - delta;

    m_groups.last()->addObject(FigureBuilder::initParallelepiped(QImage(":paper1.jpg"),
                                                                 QVector3D(centerTop.x(),
                                                                           centerTop.y(),
                                                                           centerTop.z() - delta),
                                                                 sideX - delta * 2,
                                                                 sideY - delta * 2,
                                                                 offset));
    m_groups.last()->addObject(FigureBuilder::initParallelepiped(texture,
                                                                 QVector3D(centerTop.x() + sideX / 2 - delta / 2,
                                                                           centerTop.y(),
                                                                           centerTop.z() - delta),
                                                                 delta,
                                                                 sideY,
                                                                 offset));
    m_groups.last()->addObject(FigureBuilder::initParallelepiped(texture, centerBottom, sideX, sideY, delta));
    m_transformObjects.append(m_groups.last());
}

void Widget::initStairs(QVector3D centerTop, QVector3D centerBottom, double width, double delta)
{
    double side = 0.25;
    m_groups.push_back(QSharedPointer<Group3D>(new Group3D));

    QVector3D topLeftCenter = QVector3D(centerTop.x() - width / 2,
                                        centerTop.y(),
                                        centerTop.z());
    QVector3D topRightCenter = QVector3D(centerTop.x() + width / 2,
                                         centerTop.y(),
                                         centerTop.z());

    QVector3D bottomLeftCenter = QVector3D(centerBottom.x() - width / 2,
                                           centerBottom.y(),
                                           centerBottom.z());
    QVector3D bottomRightCenter = QVector3D(centerBottom.x() + width / 2,
                                            centerBottom.y(),
                                            centerBottom.z());

    m_groups.last()->addObject(FigureBuilder::initParallelepiped(QImage(":123.jpg"), topLeftCenter, side, side, 0.05));
    m_groups.last()->addObject(FigureBuilder::initParallelepiped(QImage(":123.jpg"), topRightCenter, side, side, 0.05));

    m_groups.last()->addObject(FigureBuilder::initParallelepiped(QImage(":123.jpg"), bottomLeftCenter, side, side, 0.05));
    m_groups.last()->addObject(FigureBuilder::initParallelepiped(QImage(":123.jpg"), bottomRightCenter, side, side, 0.05));


    m_groups.last()->addObject(FigureBuilder::initSquareBelt(QImage(":123.jpg"),
                                                             topLeftCenter, side, side,
                                                             bottomLeftCenter, side, side));

    m_groups.last()->addObject(FigureBuilder::initSquareBelt(QImage(":123.jpg"),
                                                             topRightCenter, side, side,
                                                             bottomRightCenter, side, side));

    //double height = std::fabs(centerTop.z()) - std::fabs(centerBottom.z());

    double centerTopX = centerTop.y();
    double centerBottomX = centerBottom.y();

    //qDebug() << centerBottom.y() << centerTop.y();

    double centerTopZ = centerTop.z();
    double centerBottomZ = centerBottom.z();

    double katetHorizontal = centerBottomX - centerTopX;
    double katetVertical = centerTopZ - centerBottomZ;

    double tgA = katetVertical / katetHorizontal;

    double cosA = sqrt(1 / (tgA * tgA + 1));
    double sinA = sqrt(1 - cosA * cosA);
    //qDebug() << cosA << tgA << katetVertical << katetHorizontal;


    /*SimpleObject3D* obj = FigureBuilder::initBelt(QImage(":123.jpg"),
                                                  QVector3D(centerBottom.x(),
                                                            centerBottom.y(),
                                                            centerBottom.z() + width / 2),
                                                  QVector3D(centerBottom.x(),
                                                            centerBottom.y(),
                                                            centerBottom.z() - width / 2),
                                                  sqrt(side) / 2,
                                                  sqrt(side) / 2,
                                                  0.1);
    obj->translate(QVector3D(10 * width, -katetHorizontal, 0.0));
    obj->rotate(QQuaternion::fromAxisAndAngle(0.0, 1.0, 0.0, 90));
    m_groups.last()->addObject(obj);*/

    for(double level = centerBottom.z(); level <= centerTop.z() - delta; level += delta)
    {
        //qDebug() << level + width / 2 << level - width / 2;

        QVector3D center1 = QVector3D(centerBottom.x() / sinA,
                                     centerBottom.y() / sinA,
                                     centerBottom.z() / sinA - level);
        QVector3D center2 = QVector3D(centerBottom.x() / sinA,
                                     centerBottom.y() / sinA,
                                     centerBottom.z() / sinA + width);

        SimpleObject3D* obj = FigureBuilder::initParallelepiped(QImage(":123.jpg"),
                                                                center1,
                                                                width,
                                                                side,
                                                                side);

        /*SimpleObject3D* obj = FigureBuilder::initBelt(QImage(":123.jpg"),
                                                      center1,
                                                      center2,
                                                      sqrt(side) / 2,
                                                      sqrt(side) / 2,
                                                      0.1);*/
        //obj->rotate(QQuaternion::fromAxisAndAngle(0.0, 1.0, 0.0, 90));
        //obj->translate(QVector3D((centerBottom.z() - level) * width, -katetHorizontal, (centerBottom.z() - level)));
        obj->rotate(QQuaternion::fromAxisAndAngle(1.0, 0.0, 0.0, -(90 - acos(cosA) * 180 / M_PI)));

        //obj->translate(QVector3D());
        //obj->rotate(QQuaternion::fromAxisAndAngle(0.0, 1.0, 0.0, 90));
        //obj->translate(QVector3D((centerBottom.z() - level) * width, 1.5 * width, (centerBottom.z() - level)));

        m_groups.last()->addObject(obj);
    }

    m_transformObjects.append(m_groups.last());
}

void Widget::initStairs(QVector3D centerTop, double width, double height, double side, double delta, double angle)
{
    m_groups.push_back(QSharedPointer<Group3D>(new Group3D));

    QVector3D topLeftCenter = QVector3D(centerTop.x() - width / 2,
                                        centerTop.y(),
                                        centerTop.z());
    QVector3D topRightCenter = QVector3D(centerTop.x() + width / 2,
                                         centerTop.y(),
                                         centerTop.z());

    QVector3D bottomLeftCenter = QVector3D(centerTop.x() - width / 2,
                                           centerTop.y(),
                                           centerTop.z() - height);
    QVector3D bottomRightCenter = QVector3D(centerTop.x() + width / 2,
                                            centerTop.y(),
                                            centerTop.z() - height);

    m_groups.last()->addObject(FigureBuilder::initParallelepiped(QImage(":123.jpg"), topLeftCenter, side, side, 0.05));
    m_groups.last()->addObject(FigureBuilder::initParallelepiped(QImage(":123.jpg"), topRightCenter, side, side, 0.05));

    m_groups.last()->addObject(FigureBuilder::initParallelepiped(QImage(":123.jpg"), bottomLeftCenter, side, side, 0.05));
    m_groups.last()->addObject(FigureBuilder::initParallelepiped(QImage(":123.jpg"), bottomRightCenter, side, side, 0.05));


    m_groups.last()->addObject(FigureBuilder::initSquareBelt(QImage(":123.jpg"),
                                                             topLeftCenter, side, side,
                                                             bottomLeftCenter, side, side));

    m_groups.last()->addObject(FigureBuilder::initSquareBelt(QImage(":123.jpg"),
                                                             topRightCenter, side, side,
                                                             bottomRightCenter, side, side));

    QVector3D centerBottom = QVector3D(centerTop.x(),
                                       centerTop.y(),
                                       centerTop.z() - height);

    for(double level = centerBottom.z() + delta; level < centerTop.z(); level += delta)
    {
        SimpleObject3D* obj = FigureBuilder::initParallelepiped(QImage(":123.jpg"),
                                                                QVector3D(centerBottom.x(),
                                                                          centerBottom.y(),
                                                                          level),
                                                                width,
                                                                side,
                                                                side);
        m_groups.last()->addObject(obj);
    }

    m_groups.last()->rotate(QQuaternion::fromAxisAndAngle(1.0, 0.0, 0.0, angle));
    m_transformObjects.append(m_groups.last());
}
