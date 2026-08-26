#include "MainWindow.h"
#include <QWidget>
#include <qwidget.h>
#include "canvas.h"

MainWindow::MainWindow(){
    setWindowTitle("SGC");
    resize(1200,600);

    Canvas *canvas = new Canvas(this);
    setCentralWidget(canvas);
}