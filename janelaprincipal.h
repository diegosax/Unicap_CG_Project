#ifndef JANELAPRINCIPAL_H
#define JANELAPRINCIPAL_H

#include <QWidget>

namespace Ui {
    class JanelaPrincipal;
}

class JanelaPrincipal : public QWidget
{
    Q_OBJECT

public:
    explicit JanelaPrincipal(QWidget *parent = 0);
    ~JanelaPrincipal();

private:
    Ui::JanelaPrincipal *ui;
};

#endif // JANELAPRINCIPAL_H
