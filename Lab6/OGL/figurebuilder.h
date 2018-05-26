#ifndef FIGUREBUILDER_H
#define FIGUREBUILDER_H

#include "simpleobject3d.h"

class FigureBuilder
{
public:
    FigureBuilder();

    static SimpleObject3D *initCube(float width);
    static SimpleObject3D *initDiskSector(QVector3D point, double r, double angle);
    static SimpleObject3D *initSandGlass();
};

#endif // FIGUREBUILDER_H
