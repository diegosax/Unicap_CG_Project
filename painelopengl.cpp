#include <QMouseEvent>
#include <QKeyEvent>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include "painelopengl.h"

PainelOpenGL::PainelOpenGL(QWidget *parent) :
    QGLWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    xRot = 1;
    yRot = 1;
    zRot = 0;
    xMax = yMax = zMax = 10.0;
    malha = false;
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
    //glClearDepth(1.0f);

    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    //glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_NICEST);

    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
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
    gluPerspective(75.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2, 1, 15, 0, 0, 0, 0, 1, 0);

}

/*
 * onde a mágica acontece
 *
 */
void PainelOpenGL::paintGL(){

    // Limpa a janela de visualizao com a cor branca
    // e Limpa o buffer de teste de profundidade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix(); 	// It is important to push the Matrix before calling
                        // glRotatef and glTranslatef

    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
/*
    glRotatef(85.0, 1.0, 1.0, 1.0);
       for (int j = 0; j <= 8; j++) {
          glBegin(GL_LINE_STRIP);
          for (int i = 0; i <= 30; i++)
             glEvalCoord2f((GLfloat)i/30.0, (GLfloat)j/8.0);
          glEnd();
          glBegin(GL_LINE_STRIP);
          for (int i = 0; i <= 30; i++)
             glEvalCoord2f((GLfloat)j/8.0, (GLfloat)i/30.0);
          glEnd();
       }
*/
    tracarEixo();
    plotarPontosControle();
    if (malha)
        desenharMalhaControle();
    desenharSuperficieBezier();

    glPopMatrix();

}

void PainelOpenGL::tracarEixo(){

    glLineWidth(1);

    glBegin(GL_LINES);

        // Eixo X
        glColor3f(0.0f,0.0f,0.0f);
        glVertex3i(0, 0, 0);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3i(xMax, 0, 0);

        // Eixo Y
        glColor3f(0.0f,0.0f,0.0f);
        glVertex3i(0, 0, 0);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3i(0, yMax, 0);


        // Eixo Z
        glColor3f(0.0f,0.0f,0.0f);
        glVertex3i(0, 0, 0);
        glColor3f(0.0f,0.0f,1.0f);
        glVertex3i(0, 0, zMax);

    glEnd();

}

void PainelOpenGL::plotarPontosControle(){

    GLfloat ctrlpoints[4][4][3] = {
        {{-1.5, -1.5, 4.0}, {-0.5, -1.5, 2.0},
        {0.5, -1.5, -1.0}, {1.5, -1.5, 2.0}},
        {{-1.5, -0.5, 1.0}, {-0.5, -0.5, 3.0},
        {0.5, -0.5, 0.0}, {1.5, -0.5, -1.0}},
        {{-1.5, 0.5, 4.0}, {-0.5, 0.5, 0.0},
        {0.5, 0.5, 3.0}, {1.5, 0.5, 4.0}},
        {{-1.5, 1.5, -2.0}, {-0.5, 1.5, -2.0},
        {0.5, 1.5, 0.0}, {1.5, 1.5, -1.0}}
    };
    glColor3f(0.9f,0.5f,0.7f);
    glPointSize(2);
    glBegin(GL_POINTS);
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                glVertex3f(ctrlpoints[i][j][0], ctrlpoints[i][j][1], ctrlpoints[i][j][2]);
            }
        }
    glEnd();
}

void PainelOpenGL::desenharMalhaControle(){

    GLfloat ctrlpoints[4][4][3] = {
        {{-1.5, -1.5, 4.0}, {-0.5, -1.5, 2.0},
        {0.5, -1.5, -1.0}, {1.5, -1.5, 2.0}},
        {{-1.5, -0.5, 1.0}, {-0.5, -0.5, 3.0},
        {0.5, -0.5, 0.0}, {1.5, -0.5, -1.0}},
        {{-1.5, 0.5, 4.0}, {-0.5, 0.5, 0.0},
        {0.5, 0.5, 3.0}, {1.5, 0.5, 4.0}},
        {{-1.5, 1.5, -2.0}, {-0.5, 1.5, -2.0},
        {0.5, 1.5, 0.0}, {1.5, 1.5, -1.0}}
    };
    glColor3f(0.0f,1.0f,0.7f);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                glVertex3f(ctrlpoints[i][j][0], ctrlpoints[i][j][1], ctrlpoints[i][j][2]);
            }
        }
    glEnd();

}

void PainelOpenGL::desenharSuperficieBezier(){

    glColor3f(0.0, 0.0, 0.0);

    GLfloat ctrlpoints[4][4][3] = {
        {{-1.5, -1.5, 4.0}, {-0.5, -1.5, 2.0},
        {0.5, -1.5, -1.0}, {1.5, -1.5, 2.0}},
        {{-1.5, -0.5, 1.0}, {-0.5, -0.5, 3.0},
        {0.5, -0.5, 0.0}, {1.5, -0.5, -1.0}},
        {{-1.5, 0.5, 4.0}, {-0.5, 0.5, 0.0},
        {0.5, 0.5, 3.0}, {1.5, 0.5, 4.0}},
        {{-1.5, 1.5, -2.0}, {-0.5, 1.5, -2.0},
        {0.5, 1.5, 0.0}, {1.5, 1.5, -1.0}}
    };
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);


    for (int j = 0; j <= 8; j++) {

        glBegin(GL_LINE_STRIP);
        for (int i = 0; i <= 30; i++)
            glEvalCoord2f((GLfloat)i/30.0, (GLfloat)j/8.0);
        glEnd();

        glBegin(GL_LINE_STRIP);
        for (int i = 0; i <= 30; i++)
            glEvalCoord2f((GLfloat)j/8.0, (GLfloat)i/30.0);
        glEnd();
    }

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
    case Qt::Key_O:
        xRot = yRot = 1;
        zRot = 0;
        this->malha = false;
        break;
    case Qt::Key_P:
        this->malha = !this->malha;
        break;
    }
    updateGL();
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
    this->x = x;
    this->y = y;
    this->z = z;
}

Ponto3D::~Ponto3D(){

}

double Ponto3D::getX(){
    return this->x;
}

double Ponto3D::getY(){
    return this->y;
}

double Ponto3D::getZ(){
    return this->z;
}

double Ponto3D::getXDispositivo(){
    return this->x * 10.0;
}

double Ponto3D::getYDispositivo(){
    return this->y * 10.0;
}

double Ponto3D::getZDispositivo(){
    return this->z * 10.0;
}

void Ponto3D::setX(double x){
    this->x = x;
}

void Ponto3D::setY(double y){
    this->y = y;
}

void Ponto3D::setZ(double z){
    this->z = z;
}
