#ifndef GL_WINDGET_H
#define GL_WINDGET_H

#include <QGLWidget>

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

public:
    explicit GL_Widget(QWidget *parent = 0);
    void initializeGL();
    void paintGL();
    void figuresGL();
    void startDrawing();

    void opacityTestEnable();

public slots:
    void setPrimitive(int p);
    void setAlphaTestIndex(int alphaTestIndex);
    void setAlphaTestValue(int alphaTestValue);
};

#endif // GL_WINDGET_H
