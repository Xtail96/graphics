#ifndef FIGUREBUILDER_H
#define FIGUREBUILDER_H

#include "simpleobject3d.h"

class FigureBuilder
{
public:
    FigureBuilder();

    static SimpleObject3D *initCube(float width);
    static SimpleObject3D *initDiskSector(QVector3D point = QVector3D(0.0f, 0.0f, 0.0f), double r = 1.0, double angle = M_PI / 2);
    static SimpleObject3D *initSandGlass();
};

#endif // FIGUREBUILDER_H
