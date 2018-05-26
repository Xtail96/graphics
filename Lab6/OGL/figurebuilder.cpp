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

    VertexData center = VertexData(QVector3D(0.0, 0.0, 0.0),
                                   QVector2D(0.0, 0.0),
                                   QVector3D(0.0, 0.0, 1.0));
    vertexes.push_back(center);

    QList<QVector3D> diskPoints;
    for(float i = 0; i <= (M_PI + 0.1) / 2; i += 0.1)
    {
        diskPoints.push_back(QVector3D(0.0 + sin(i) * 1.0, 0.0 + cos(i) * 1.0, 0.0));
    }

    for(int i = 1; i < diskPoints.size(); i ++)
    {
        vertexes.push_back(VertexData(QVector3D(diskPoints[i].x(), diskPoints[i].y(), 0.0),
                                      QVector2D(0.0, 1.0),
                                      QVector3D(0.0, 0.0, 1.0)));
        vertexes.push_back(VertexData(QVector3D(diskPoints[i-1].x(), diskPoints[i-1].y(), 0.0),
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
    QVector<VertexData> vertexes;
    QVector<GLuint> indexes;

    VertexData center = VertexData(QVector3D(0.0, 0.0, 0.0),
                                   QVector2D(0.0, 0.0),
                                   QVector3D(0.0, 0.0, 1.0));
    vertexes.push_back(center);

    QList<QVector3D> diskPoints;
    for(float i = 0; i <= (M_PI + 0.1) / 2; i += 0.1)
    {
        diskPoints.push_back(QVector3D(0.0 + sin(i) * 1.0, 0.0 + cos(i) * 1.0, 0.0));
    }

    for(int i = 1; i < diskPoints.size(); i ++)
    {
        vertexes.push_back(VertexData(QVector3D(diskPoints[i].x(), diskPoints[i].y(), 0.0),
                                      QVector2D(0.0, 1.0),
                                      QVector3D(0.0, 0.0, 1.0)));
        vertexes.push_back(VertexData(QVector3D(diskPoints[i-1].x(), diskPoints[i-1].y(), 0.0),
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
