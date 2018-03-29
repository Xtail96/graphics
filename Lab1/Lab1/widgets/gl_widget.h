#ifndef GL_WINDGET_H
#define GL_WINDGET_H

#include <QGLWidget>

struct Point3Df
{
    double x;
    double y;
    double z;
};

class GL_Widget: public QGLWidget
{
    Q_OBJECT
private:
    int m_primitiveIndex;
    QList<Point3Df> m_points;

public:
    explicit GL_Widget(QWidget *parent = 0);
    void initializeGL();
    void paintGL();
    void figuresGL();
    void startDrawing();

public slots:
    void setPrimitive(int p);
};

#endif // GL_WINDGET_H
