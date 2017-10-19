#include "widget.h"
#include <QApplication>
#include "objloader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //ObjLoader* objLoader = new ObjLoader("A");

    Widget w;
    w.show();
    w.setWindowTitle("su2网格文件可视化");

    return a.exec();
}
