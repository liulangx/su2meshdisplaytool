#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include "qopenglmain.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void onTimeOut();

private:
    Ui::Widget *ui;
    QOpenGLMain* qOpenGLMain;
    QGridLayout* m_theBaseLayout;
    QTimer m_timer;
};

#endif // WIDGET_H
