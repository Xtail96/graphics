#ifndef FIGUREBUILDER_H
#define FIGUREBUILDER_H

#include "simpleobject3d.h"

class FigureBuilder
{
public:
    FigureBuilder();

    static SimpleObject3D *initCube(float width);
    static SimpleObject3D *initDiskSector(QVector3D point = QVector3D(0.0f, 0.0f, 0.0f), double r = 1.0, double angle = M_PI / 2, double step = 0.1, bool invert = false);
    static SimpleObject3D *initBelt(QVector3D center1, QVector3D center2, double r1, double r2, double step = 0.1);
    static double calculteLemniscatePoint(double x, double c);
};

#endif // FIGUREBUILDER_H
