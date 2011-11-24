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

    bool malha;

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

    void tracarEixo();
    void plotarPontosControle();
    void desenharMalhaControle();
    void desenharSuperficieBezier();
    void plotPoint();

};

class Ponto3D{
public:
    Ponto3D();
    Ponto3D(double x, double y, double z);
    ~Ponto3D();

    double getX();
    double getY();
    double getZ();
    double getXDispositivo();
    double getYDispositivo();
    double getZDispositivo();
    void setX(double);
    void setY(double);
    void setZ(double);

    //GLfloat *getMatriz(); // TODO
private:
    double x;
    double y;
    double z;
};

class Tranformacao{
public:
    Tranformacao();
    ~Tranformacao();

    char getTipo() const { return tipo;}
    Ponto3D getPonto() const { return ponto; }
    double getRotacao() const { return rotacao; }

    void setTipo(char t) {this->tipo = t; }
    void setPonto(Ponto3D p) { this->ponto = p; }
    void setRotacao(double rot) { this->rotacao = rot; }
private:

    char tipo;
    Ponto3D ponto;
    double rotacao;

};

#endif // PAINELOPENGL_H
