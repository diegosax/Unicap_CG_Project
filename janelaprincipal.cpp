#include "janelaprincipal.h"
#include "ui_janelaprincipal.h"

JanelaPrincipal::JanelaPrincipal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JanelaPrincipal)
{
    ui->setupUi(this);
}

JanelaPrincipal::~JanelaPrincipal()
{
    delete ui;
}
