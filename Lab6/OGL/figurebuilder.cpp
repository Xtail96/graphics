#include "figurebuilder.h"

FigureBuilder::FigureBuilder()
{

}

SimpleObject3D *FigureBuilder::initCube(const QImage &texture, float width)
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

    //return new SimpleObject3D(vertexes, indexes, QImage(":/123.jpg"));
    return new SimpleObject3D(vertexes, indexes, texture);
}

SimpleObject3D *FigureBuilder::initDiskSector(const QImage &texture, QVector3D point, double r, double angle, double step, bool invert)
{
    double zNormal = 1.0;
    if(invert)
    {
        zNormal = -1.0;
    }

    QVector<VertexData> vertexes;
    QVector<GLuint> indexes;

    VertexData center = VertexData(point,
                                   QVector2D(0.0, 0.0),
                                   QVector3D(0.0, 0.0, zNormal));
    vertexes.push_back(center);

    QList<QVector3D> diskPoints;
    for(float i = 0; i <= angle + step; i += step)
    {
        diskPoints.push_back(QVector3D(center.position.x() + sin(i) * r, center.position.y() + cos(i) * r, center.position.z()));
    }

    for(int i = 1; i < diskPoints.size(); i++)
    {
        vertexes.push_back(VertexData(QVector3D(diskPoints[i].x(), diskPoints[i].y(), diskPoints[i].z()),
                                      QVector2D(1.0, 1.0),
                                      QVector3D(0.0, 0.0, zNormal)));
        vertexes.push_back(VertexData(QVector3D(diskPoints[i-1].x(), diskPoints[i-1].y(), diskPoints[i - 1].z()),
                                      QVector2D(1.0, 1.0),
                                      QVector3D(0.0, 0.0, zNormal)));
    }

    int count = vertexes.size();
    for(int i = 0; i < count - 1; i += 2)
    {
        if(!invert)
        {
            indexes.push_back(0);
            indexes.push_back(i + 1);
            indexes.push_back(i + 2);
        }
        else
        {
            indexes.push_back(0);
            indexes.push_back(i + 2);
            indexes.push_back(i + 1);
        }

    }

    /*for(int i = 0 ; i < vertexes.size(); i++)
    {
        qDebug() << "#" << i << vertexes[i].position << vertexes[i].texCoords << vertexes[i].normal;
    }*/
    //qDebug() << indexes;

    return new SimpleObject3D(vertexes, indexes, texture);
}

SimpleObject3D *FigureBuilder::initBelt(const QImage &texture, QVector3D center1, QVector3D center2, double r1, double r2, double step)
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
    for(float i = 0; i <= 2 * M_PI + step; i += step)
    {
        disk1Points.push_back(QVector3D(disk1Center.position.x() + sin(i) * r1, disk1Center.position.y() + cos(i) * r1, disk1Center.position.z()));
        disk1Normals.push_back(QVector3D(sin(i), cos(i), zNormal));
    }


    VertexData disk2Center = VertexData(center2,
                                   QVector2D(0.0, 0.0),
                                   QVector3D(0.0, 0.0, 1.0));


    QList<QVector3D> disk2Points;
    for(float i = 0; i <= 2 * M_PI + step; i += step)
    {
        disk2Points.push_back(QVector3D(disk2Center.position.x() + sin(i) * r2, disk2Center.position.y() + cos(i) * r2, disk2Center.position.z()));
    }

    for(int i = 0; i < disk1Points.size(); i += 1)
    {
        QVector2D texture;
        if(i % 2 == 0)
        {
            texture.setX(1.0);
            texture.setY(0.0);
        }
        else
        {
            texture.setX(0.0);
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
            texture.setX(1.0);
            texture.setY(0.0);
        }
        else
        {
            texture.setX(0.0);
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

    return new SimpleObject3D(vertexes, indexes, texture);
}

double FigureBuilder::calculteLemniscatePoint(double x, double c)
{
    return 0.05f + sqrt(sqrt(pow(c, 4) + 4 * pow(x, 2) * pow(c, 2)) - pow(x, 2) - pow(c, 2));
}

SimpleObject3D *FigureBuilder::initParallelepiped(const QImage &texture, double width, double height, double deep)
{
    double width_div_2 = width / 2.0f;
    double height_div_2 = height / 2.0f;
    double deep_div_2 = deep / 2.0f;

    QVector<VertexData> vertexes;

    vertexes.append(VertexData(QVector3D(-width_div_2, height_div_2, deep_div_2),
                               QVector2D(0.0, 1.0),
                               QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -height_div_2, deep_div_2),
                               QVector2D(0.0, 0.0),
                               QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, height_div_2, deep_div_2),
                               QVector2D(1.0, 1.0),
                               QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -height_div_2, deep_div_2),
                               QVector2D(1.0, 0.0),
                               QVector3D(0.0, 0.0, 1.0)));

    vertexes.append(VertexData(QVector3D(width_div_2, height_div_2, deep_div_2),
                               QVector2D(0.0, 1.0),
                               QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -height_div_2, deep_div_2),
                               QVector2D(0.0, 0.0),
                               QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, height_div_2, -deep_div_2),
                               QVector2D(1.0, 1.0),
                               QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -height_div_2, -deep_div_2),
                               QVector2D(1.0, 0.0),
                               QVector3D(1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(width_div_2, height_div_2, deep_div_2),
                               QVector2D(0.0, 1.0),
                               QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, height_div_2, -deep_div_2),
                               QVector2D(0.0, 0.0),
                               QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, height_div_2, deep_div_2),
                               QVector2D(1.0, 1.0),
                               QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, height_div_2, -deep_div_2),
                               QVector2D(1.0, 0.0),
                               QVector3D(0.0, 1.0, 0.0)));

    vertexes.append(VertexData(QVector3D(width_div_2, height_div_2, -deep_div_2),
                               QVector2D(0.0, 1.0),
                               QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -height_div_2, -deep_div_2),
                               QVector2D(0.0, 0.0),
                               QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, height_div_2, -deep_div_2),
                               QVector2D(1.0, 1.0),
                               QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -height_div_2, -deep_div_2),
                               QVector2D(1.0, 0.0),
                               QVector3D(0.0, 0.0, -1.0)));

    vertexes.append(VertexData(QVector3D(-width_div_2, height_div_2, deep_div_2),
                               QVector2D(0.0, 1.0),
                               QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, height_div_2, -deep_div_2),
                               QVector2D(0.0, 0.0),
                               QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -height_div_2, deep_div_2),
                               QVector2D(1.0, 1.0),
                               QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -height_div_2, -deep_div_2),
                               QVector2D(1.0, 0.0),
                               QVector3D(-1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(-width_div_2, -height_div_2, deep_div_2),
                               QVector2D(0.0, 1.0),
                               QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -height_div_2, -deep_div_2),
                               QVector2D(0.0, 0.0),
                               QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -height_div_2, deep_div_2),
                               QVector2D(1.0, 1.0),
                               QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -height_div_2, -deep_div_2),
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

    return new SimpleObject3D(vertexes, indexes, texture);
}

SimpleObject3D *FigureBuilder::initSquareBelt(const QImage &texture, QVector3D center1, double w1, double h1, QVector3D center2, double w2, double h2)
{
    double zNormal;
    double delta = qMax(w2 - w1, h2 - h1);
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

    double square1WidthDiv2 = w1 / 2.0f;
    double square1HeightDiv2 = h1 / 2.0f;

    double square2WidthDiv2 = w2 / 2.0f;
    double square2HeightDiv2 = h2 / 2.0f;

    QVector<VertexData> vertexes;
    QVector<GLuint> indexes;

    QVector<VertexData> vertexes1;
    QVector<VertexData> vertexes2;

    // вершины 1 квадрата
    // 0
    vertexes1.push_back(VertexData(QVector3D(center1.x() + square1WidthDiv2, center1.y() + square1HeightDiv2, center1.z()),
                                  QVector2D(0.0, 1.0),
                                  QVector3D(0.0, 1.0, zNormal)));

    // 1
    vertexes1.push_back(VertexData(QVector3D(-(center1.x() + square1WidthDiv2), center1.y() + square1HeightDiv2, center1.z()),
                                  QVector2D(1.0, 1.0),
                                  QVector3D(0.0, 1.0, zNormal)));
    vertexes1.push_back(VertexData(QVector3D(-(center1.x() + square1WidthDiv2), center1.y() + square1HeightDiv2, center1.z()),
                                  QVector2D(0.0, 1.0),
                                  QVector3D(-1.0, 0.0, zNormal)));

    // 2
    vertexes1.push_back(VertexData(QVector3D(-(center1.x() + square1WidthDiv2), -(center1.y() + square1HeightDiv2), center1.z()),
                                  QVector2D(1.0, 1.0),
                                  QVector3D(-1.0, 0.0, 0.0)));
    vertexes1.push_back(VertexData(QVector3D(-(center1.x() + square1WidthDiv2), -(center1.y() + square1HeightDiv2), center1.z()),
                                  QVector2D(0.0, 1.0),
                                  QVector3D(0.0, -1.0, zNormal)));

    // 3
    vertexes1.push_back(VertexData(QVector3D(center1.x() + square1WidthDiv2, -(center1.y() + square1HeightDiv2), center1.z()),
                                  QVector2D(1.0, 1.0),
                                  QVector3D(0.0, -1.0, 0.0)));
    vertexes1.push_back(VertexData(QVector3D(center1.x() + square1WidthDiv2, -(center1.y() + square1HeightDiv2), center1.z()),
                                  QVector2D(0.0, 1.0),
                                  QVector3D(1.0, 0.0, zNormal)));

    // 0
    vertexes1.push_back(VertexData(QVector3D(center1.x() + square1WidthDiv2, center1.y() + square1HeightDiv2, center1.z()),
                                  QVector2D(1.0, 1.0),
                                  QVector3D(1.0, 0.0, zNormal)));

    // вершины 2 квадрата
    // 0
    vertexes2.push_back(VertexData(QVector3D(center2.x() + square2WidthDiv2, center2.y() + square2HeightDiv2, center2.z()),
                                  QVector2D(0.0, 0.0),
                                  QVector3D(0.0, 1.0, zNormal)));

    // 1
    vertexes2.push_back(VertexData(QVector3D(-(center2.x() + square2WidthDiv2), center2.y() + square2HeightDiv2, center2.z()),
                                  QVector2D(1.0, 0.0),
                                  QVector3D(0.0, 1.0, zNormal)));
    vertexes2.push_back(VertexData(QVector3D(-(center2.x() + square2WidthDiv2), center2.y() + square2HeightDiv2, center2.z()),
                                  QVector2D(0.0, 0.0),
                                  QVector3D(-1.0, 0.0, zNormal)));

    // 2
    vertexes2.push_back(VertexData(QVector3D(-(center2.x() + square2WidthDiv2), -(center2.y() + square2HeightDiv2), center2.z()),
                                  QVector2D(1.0, 0.0),
                                  QVector3D(-1.0, 0.0, zNormal)));
    vertexes2.push_back(VertexData(QVector3D(-(center2.x() + square2WidthDiv2), -(center2.y() + square2HeightDiv2), center2.z()),
                                  QVector2D(0.0, 0.0),
                                  QVector3D(0.0, -1.0, zNormal)));

    // 3
    vertexes2.push_back(VertexData(QVector3D(center2.x() + square2WidthDiv2, -(center2.y() + square2HeightDiv2), center2.z()),
                                  QVector2D(1.0, 0.0),
                                  QVector3D(0.0, -1.0, zNormal)));
    vertexes2.push_back(VertexData(QVector3D(center2.x() + square2WidthDiv2, -(center2.y() + square2HeightDiv2), center2.z()),
                                  QVector2D(0.0, 0.0),
                                  QVector3D(1.0, 0.0, zNormal)));

    // 0
    vertexes2.push_back(VertexData(QVector3D(center2.x() + square2WidthDiv2, center2.y() + square2HeightDiv2, center2.z()),
                                  QVector2D(1.0, 0.0),
                                  QVector3D(1.0, 0.0, zNormal)));

    vertexes += vertexes1;
    vertexes += vertexes2;

    int square2FirstIndex = vertexes1.size();

    for(int i = 0; i < vertexes1.size(); i += 2)
    {
        indexes.push_back(i + 0);
        indexes.push_back(i + 1 + square2FirstIndex);
        indexes.push_back(i + 0 + square2FirstIndex);
        indexes.push_back(i + 0);
        indexes.push_back(i + 1);
        indexes.push_back(i + 1 + square2FirstIndex);
    }

    return new SimpleObject3D(vertexes, indexes, texture);
}
