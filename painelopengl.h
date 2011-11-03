#ifndef PAINELOPENGL_H
#define PAINELOPENGL_H

#include <QGLWidget>
#include <cmath>
#include <string>
#include <list>
#include <QPainter>

using std::string;

class Ponto3D;

class PainelOpenGL : public QGLWidget
{
    Q_OBJECT
public:
    explicit PainelOpenGL(QWidget *parent = 0);

signals:

public slots:

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    QPoint lastPos;

    std::list<Ponto3D> pontos;

    int xRot;
    int yRot;
    int zRot;

    int xMax;
    int yMax;
    int zMax;

    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

    void lerArquivo(string path);

};

class Ponto3D{
public:
    Ponto3D();
    Ponto3D(double x, double y, double z);
    ~Ponto3D();

    int getX();
    int getY();
    int getZ();
    void setX(int);
    void setY(int);
    void setZ(int);
private:
    int x;
    int y;
    int z;
};

#endif // PAINELOPENGL_H
