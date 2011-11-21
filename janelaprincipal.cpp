#include "janelaprincipal.h"
#include "ui_janelaprincipal.h"

JanelaPrincipal::JanelaPrincipal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JanelaPrincipal)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::StrongFocus);
}

JanelaPrincipal::~JanelaPrincipal()
{
    delete ui;
}
