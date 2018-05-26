#include "figurebuilder.h"

FigureBuilder::FigureBuilder()
{

}

SimpleObject3D *FigureBuilder::initCube(float width)
{
    float width_div_2 = width / 2.0f;
    QVector<VertexData> vertexes;

    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2),
                               QVector2D(0.0, 1.0),
                               QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2),
                               QVector2D(0.0, 0.0),
                               QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2),
                               QVector2D(1.0, 1.0),
                               QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2),
                               QVector2D(1.0, 0.0),
                               QVector3D(0.0, 0.0, 1.0)));

    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2),
                               QVector2D(0.0, 1.0),
                               QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2),
                               QVector2D(0.0, 0.0),
                               QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2),
                               QVector2D(1.0, 1.0),
                               QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2),
                               QVector2D(1.0, 0.0),
                               QVector3D(1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2),
                               QVector2D(0.0, 1.0),
                               QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2),
                               QVector2D(0.0, 0.0),
                               QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2),
                               QVector2D(1.0, 1.0),
                               QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2),
                               QVector2D(1.0, 0.0),
                               QVector3D(0.0, 1.0, 0.0)));

    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2),
                               QVector2D(0.0, 1.0),
                               QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2),
                               QVector2D(0.0, 0.0),
                               QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2),
                               QVector2D(1.0, 1.0),
                               QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2),
                               QVector2D(1.0, 0.0),
                               QVector3D(0.0, 0.0, -1.0)));

    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2),
                               QVector2D(0.0, 1.0),
                               QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2),
                               QVector2D(0.0, 0.0),
                               QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2),
                               QVector2D(1.0, 1.0),
                               QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2),
                               QVector2D(1.0, 0.0),
                               QVector3D(-1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2),
                               QVector2D(0.0, 1.0),
                               QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2),
                               QVector2D(0.0, 0.0),
                               QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2),
                               QVector2D(1.0, 1.0),
                               QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2),
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

    return new SimpleObject3D(vertexes, indexes, QImage(":/123.jpg"));
}

SimpleObject3D *FigureBuilder::initDiskSector(QVector3D point, double r, double angle)
{
    QVector<VertexData> vertexes;
    QVector<GLuint> indexes;

    VertexData center = VertexData(point,
                                   QVector2D(0.0, 0.0),
                                   QVector3D(0.0, 0.0, 1.0));
    vertexes.push_back(center);

    QList<QVector3D> diskPoints;
    for(float i = 0; i <= angle + 0.1; i += 0.1)
    {
        diskPoints.push_back(QVector3D(center.position.x() + sin(i) * r, center.position.y() + cos(i) * r, center.position.z()));
    }

    for(int i = 1; i < diskPoints.size(); i++)
    {
        vertexes.push_back(VertexData(QVector3D(diskPoints[i].x(), diskPoints[i].y(), diskPoints[i].z()),
                                      QVector2D(0.0, 1.0),
                                      QVector3D(0.0, 0.0, 1.0)));
        vertexes.push_back(VertexData(QVector3D(diskPoints[i-1].x(), diskPoints[i-1].y(), diskPoints[i - 1].z()),
                                      QVector2D(1.0, 0.0),
                                      QVector3D(0.0, 0.0, 1.0)));
    }

    int count = vertexes.size();
    for(int i = 0; i < count - 1; i += 2)
    {
        indexes.push_back(0);
        indexes.push_back(i + 1);
        indexes.push_back(i + 2);
    }

    /*for(int i = 0 ; i < vertexes.size(); i++)
    {
        qDebug() << "#" << i << vertexes[i].position << vertexes[i].texCoords << vertexes[i].normal;
    }*/
    //qDebug() << indexes;

    return new SimpleObject3D(vertexes, indexes, QImage(":/123.jpg"));
}

SimpleObject3D *FigureBuilder::initSandGlass()
{
    // params
    //float height = 2;
    //float step = 0.2;

    QVector<VertexData> vertexes;
    QVector<GLuint> indexes;

    QVector<VertexData> disk1Vertexes;
    QVector<GLuint> disk1Indexes;

    VertexData disk1Center = VertexData(QVector3D(0.0, 0.0, 0.0),
                                   QVector2D(0.0, 0.0),
                                   QVector3D(0.0, 0.0, 1.0));

    //disk1Vertexes.push_back(disk1Center);

    QList<QVector3D> disk1Points;
    for(float i = 0; i <= 2 * M_PI + 0.1; i += 1)
    {
        disk1Points.push_back(QVector3D(disk1Center.position.x() + sin(i) * 1.0, disk1Center.position.y() + cos(i) * 1.0, disk1Center.position.z()));
    }

    //qDebug() << disk1Points;

    for(int i = 1; i < disk1Points.size(); i++)
    {
        disk1Vertexes.push_back(VertexData(QVector3D(disk1Points[i].x(), disk1Points[i].y(), disk1Points[i].z()),
                                      QVector2D(0.0, 1.0),
                                      QVector3D(0.0, 0.0, 1.0)));
        disk1Vertexes.push_back(VertexData(QVector3D(disk1Points[i-1].x(), disk1Points[i-1].y(), disk1Points[i - 1].z()),
                                      QVector2D(1.0, 0.0),
                                      QVector3D(0.0, 0.0, 1.0)));
    }

    int count = disk1Vertexes.size();
    for(int i = 0; i < count - 1; i += 2)
    {
        //disk1Indexes.push_back(0);
        disk1Indexes.push_back(i);
        disk1Indexes.push_back(i + 1);
    }



    int disk2FirstNumber = disk1Vertexes.size();
    QVector<VertexData> disk2Vertexes;
    QVector<GLuint> disk2Indexes;
    VertexData disk2Center = VertexData(QVector3D(0.0, 0.0, -0.5),
                                   QVector2D(0.0, 0.0),
                                   QVector3D(0.0, 0.0, 1.0));
    //disk2Vertexes.push_back(disk2Center);
    QList<QVector3D> disk2Points;
    for(float i = 0; i <= 2 * M_PI + 0.1; i += 1)
    {
        disk2Points.push_back(QVector3D(disk2Center.position.x() + sin(i) * 1.5, disk2Center.position.y() + cos(i) * 1.5, disk2Center.position.z()));
    }

    for(int i = 1; i < disk2Points.size(); i ++)
    {
        disk2Vertexes.push_back(VertexData(QVector3D(disk2Points[i].x(), disk2Points[i].y(), disk2Points[i].z()),
                                      QVector2D(0.0, 1.0),
                                      QVector3D(0.0, 0.0, 1.0)));
        disk2Vertexes.push_back(VertexData(QVector3D(disk2Points[i-1].x(), disk2Points[i-1].y(), disk2Points[i-1].z()),
                                      QVector2D(1.0, 0.0),
                                      QVector3D(0.0, 0.0, 1.0)));
    }

    count = disk2Vertexes.size();
    for(int i = 0; i < count - 1; i += 2)
    {
        //disk2Indexes.push_back(disk2FirstNumber + 0);
        disk2Indexes.push_back(disk2FirstNumber + i + 0);
        disk2Indexes.push_back(disk2FirstNumber + i + 1);
    }


    vertexes = disk1Vertexes + disk2Vertexes;
    indexes = disk1Indexes + disk2Indexes;

    qDebug() << disk1Vertexes.size() << disk1Indexes.size();
    qDebug() << disk2Vertexes.size() << disk2Indexes.size();


    for(int i = 0; i < disk1Vertexes.size() - 1; i++)
    {
        indexes.push_back(disk1Indexes[i]);
        indexes.push_back(disk2Indexes[i]);
        indexes.push_back(disk2Indexes[i + 1]);
    }

    indexes.push_back(disk1Indexes[0]);
    indexes.push_back(disk1Indexes[disk1Indexes.size() - 1]);
    indexes.push_back(disk2Indexes[0]);

    /*for(int i = 0; i < disk1Vertexes.size() - 1; i++)
    {
        indexes.push_back(disk1Indexes[i]);
        indexes.push_back(disk1Indexes[i + 1]);
        indexes.push_back(disk2Indexes[i]);
    }

    indexes.push_back(disk2Indexes[0]);
    indexes.push_back(disk2Indexes[disk2Indexes.size() - 1]);
    indexes.push_back(disk1Indexes[0]);*/


    /*for(int i = 0 ; i < vertexes.size(); i++)
    {
        qDebug() << "#" << i << vertexes[i].position << vertexes[i].texCoords << vertexes[i].normal;
    }*/
    //qDebug() << indexes;

    return new SimpleObject3D(vertexes, indexes, QImage(":/123.jpg"));
}
