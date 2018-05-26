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

SimpleObject3D *FigureBuilder::initBelt(QVector3D center1, QVector3D center2, double r1, double r2, double step)
{

    double zNormal;
    double delta = r2 - r1;
    if(delta > 0)
    {
        zNormal = 1.0;
    }
    else
    {
        if(delta < 0)
        {
            zNormal = -1.0;
        }
        else
        {
            zNormal = 0.0;
        }
    }

    QVector<VertexData> vertexes;
    QVector<GLuint> indexes;

    VertexData disk1Center = VertexData(center1,
                                   QVector2D(0.0, 0.0),
                                   QVector3D(0.0, 0.0, 1.0));

    QList<QVector3D> disk1Points;
    QList<QVector3D> disk1Normals;
    for(float i = 0; i <= 2 * M_PI + 0.1; i += step)
    {
        disk1Points.push_back(QVector3D(disk1Center.position.x() + sin(i) * r1, disk1Center.position.y() + cos(i) * r1, disk1Center.position.z()));
        disk1Normals.push_back(QVector3D(sin(i), cos(i), zNormal));
    }


    VertexData disk2Center = VertexData(center2,
                                   QVector2D(0.0, 0.0),
                                   QVector3D(0.0, 0.0, 1.0));


    QList<QVector3D> disk2Points;
    for(float i = 0; i <= 2 * M_PI + 0.1; i += step)
    {
        disk2Points.push_back(QVector3D(disk2Center.position.x() + sin(i) * r2, disk2Center.position.y() + cos(i) * r2, disk2Center.position.z()));
    }

    for(int i = 0; i < disk1Points.size(); i += 1)
    {
        QVector2D texture;
        if(i % 2 == 0)
        {
            texture.setX(0.0);
            texture.setY(0.0);
        }
        else
        {
            texture.setX(1.0);
            texture.setY(1.0);
        }
        vertexes.push_back(VertexData(QVector3D(disk1Points[i].x(), disk1Points[i].y(), disk1Points[i].z()),
                                      texture,
                                      disk1Normals[i]));
    }

    for(int i = 0; i < disk2Points.size(); i += 1)
    {
        QVector2D texture;
        if(i % 2 == 0)
        {
            texture.setX(0.0);
            texture.setY(0.0);
        }
        else
        {
            texture.setX(1.0);
            texture.setY(1.0);
        }

        vertexes.push_back(VertexData(QVector3D(disk2Points[i].x(), disk2Points[i].y(), disk2Points[i].z()),
                                      texture,
                                      disk1Normals[i]));
    }


    int disk2FirstIndex = disk1Points.size();
    for(int i = 0; i < disk1Points.size() - 1; i++)
    {
        indexes.push_back(i);
        indexes.push_back(i + 1);
        indexes.push_back(disk2FirstIndex + i + 1);
    }

    indexes.push_back(disk1Points.size() - 1);
    indexes.push_back(0);
    indexes.push_back(disk2FirstIndex + 0);

    for(int i = 0; i < disk1Points.size() - 1; i++)
    {
        indexes.push_back(i);
        indexes.push_back(disk2FirstIndex + i + 1);
        indexes.push_back(disk2FirstIndex + i);
    }

    indexes.push_back(disk1Points.size() - 1);
    indexes.push_back(disk2FirstIndex + 0);
    indexes.push_back(disk2FirstIndex + disk2Points.size() - 1);

    /*for(int i = 0 ; i < vertexes.size(); i++)
    {
        qDebug() << "#" << i << vertexes[i].position << vertexes[i].texCoords << vertexes[i].normal;
    }
    qDebug() << indexes;*/

    return new SimpleObject3D(vertexes, indexes, QImage(":/123.jpg"));
}
