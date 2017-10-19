#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    m_theBaseLayout = new QGridLayout(this);
    this->setLayout(m_theBaseLayout);
    qOpenGLMain = new QOpenGLMain(this);
    m_theBaseLayout->addWidget(qOpenGLMain, 0, 0);
    ui->setupUi(this);
    m_timer.start(20);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
}

Widget::~Widget()
{
    delete m_theBaseLayout;
    delete qOpenGLMain;
    //delete ui;
}
size_t i = 0;
void Widget::onTimeOut()
{
    //qDebug() << i++;
//    CRender* render = qOpenGLMain->getRender();
//    vector4f _color = {(float)random() / RAND_MAX, (float)random() / RAND_MAX, (float)random() / RAND_MAX, 1};
//    render->setBackGround(_color);
    //update();
    qOpenGLMain->update();
}
