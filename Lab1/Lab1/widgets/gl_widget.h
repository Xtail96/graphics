#ifndef GL_WINDGET_H
#define GL_WINDGET_H

#include <QGLWidget>
#include <QDebug>

struct Point3Df
{
    double x;
    double y;
    double z;
    double red;
    double green;
    double blue;
    double alpha;
};

class GL_Widget: public QGLWidget
{
    Q_OBJECT
private:
    int m_primitiveIndex;
    QList<Point3Df> m_points;

    int m_alphaTestIndex = -1;
    double m_alphaTestValue = 0;

    int m_blendTestIndexFirst = -1;
    int m_blendTestIndexSecond = -1;

public:
    explicit GL_Widget(QWidget *parent = 0);
    void initializeGL();
    void paintGL();
    void figuresGL();
    void startDrawing();

    void opacityTestEnable();
    void blendTestEnable();

public slots:
    void setPrimitive(int p);
    void setAlphaTestIndex(int alphaTestIndex);
    void setAlphaTestValue(int alphaTestValue);
    void setBlendTestIndexFirst(int blendTestIndexFirst);
    void setBlendTestIndexSecond(int blendTestIndexSecond);
};

#endif // GL_WINDGET_H
