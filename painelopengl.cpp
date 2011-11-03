#include <QMouseEvent>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include "painelopengl.h"

PainelOpenGL::PainelOpenGL(QWidget *parent) :
    QGLWidget(parent)
{
    xRot = 1;
    yRot = 1;
    zRot = 0;
}

static void qNormalizeAngle(int &angle);
static Ponto3D* lerPonto(QString line);
static float lerNumero(QString line);

/*
 * inicializa os parâmetros OpenGL
 *
 */
void PainelOpenGL::initializeGL(){

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

/*
 * executada quando a tela é redimensionada
 *
 */
void PainelOpenGL::resizeGL(int width, int height){

    height = height?height:1;

    glViewport( 0, 0, (GLint)width, (GLint)height );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

/*
 * onde a mágica acontece
 *
 */
void PainelOpenGL::paintGL(){

    // Limpa a janela de visualizao com a cor branca
    // e Limpa o buffer de teste de profundidade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); // limpa todas as transformaes

   // glTranslated(0.0, 0.0, -5.0);

    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);



    glLineWidth(1);
    glColor3f(0,0.7f,0.7f);
    glBegin(GL_LINES);
        glVertex3i(0, 0, 0);
        glVertex3i(0, 2.0, 0);

        glVertex3i(0, 0, 0);
        glVertex3i(2.0, 0, 0);

        glVertex3i(0, 0, 0);
        glVertex3i(0, 0, 2.0);
    glEnd();

}

/*
 * captura os eventos do mouse
 *
 */
void PainelOpenGL::mousePressEvent(QMouseEvent *event){

    lastPos = event->pos();

 }

void PainelOpenGL::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    //glFrustum();
    lastPos = event->pos();
}

void PainelOpenGL::keyPressEvent(QKeyEvent *e){

    switch (e->key())
    {
    case Qt::Key_Escape:
    case Qt::Key_Q:
        parentWidget()->close();
        exit(0);
        break;
    case Qt::Key_T:
        // tela transformações
        break;
    }
}


/*
 * slots
 */


/*
 * getters e setters
 *
 */
void PainelOpenGL::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        //emit xRotationChanged(angle);
        updateGL();
    }
}


void PainelOpenGL::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        //emit yRotationChanged(angle);
        updateGL();
    }
}

void PainelOpenGL::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        //emit zRotationChanged(angle);
        updateGL();
    }
}


/******/

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}


void PainelOpenGL::lerArquivo(string path){

    QFile file(path.c_str());
    QTextStream ts(&file);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }

    while (!file.atEnd()){
        QString line = ts.readLine();

        switch (line.toUpper().at(0).toAscii()){
        case 'V': {
            Ponto3D *p = lerPonto(line);
            if (p != NULL){
                pontos.push_back(*p);
            }
            break;
        }
        case 'S': // TODO
            break;
        case 'T': // TODO
            break;
        case 'X':
            //lista.append(line.simplified().split(" "));
            //xRot = lista.at(1).toFloat();
            break;
        case 'Y':
            //lista.append(line.simplified().split(" "));
            //yRot = lista.at(1).toFloat();
            break;
        case 'Z':
            //lista.append(line.simplified().split(" "));
            //zRot = lista.at(1).toFloat();
            break;
        case 'C': // TODO
            break;
        case 'E': // TODO
            break;
        }
        updateGL();
    }

}

static Ponto3D* lerPonto(QString line){
    QStringList lista = line.split(" ", QString::SkipEmptyParts);
    if (lista.count() == 4){
        Ponto3D *p = new Ponto3D;
        p->setX(lista.at(1).toFloat());
        p->setY(lista.at(2).toFloat());
        p->setZ(lista.at(3).toFloat());
        return p;
    }
    return NULL;
}

static float lerNumero(QString line){
    // TODO
}


Ponto3D::Ponto3D(){

}

Ponto3D::Ponto3D(double x, double y, double z){

}

Ponto3D::~Ponto3D(){

}

int Ponto3D::getX(){
    return this->x;
}

int Ponto3D::getY(){
    return this->y;
}

int Ponto3D::getZ(){
    return this->z;
}

void Ponto3D::setX(int x){
    this->x = x;
}

void Ponto3D::setY(int y){
    this->y = y;
}

void Ponto3D::setZ(int z){
    this->z = z;
}
