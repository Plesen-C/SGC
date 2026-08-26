#include "MainWindow.h"
#include <QWidget>
#include <qwidget.h>
#include "canvas.h"
#include <QVBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("SGC — System Graphics Creation");
    resize(1200, 800);

    canvas = new Canvas(this);
    setCentralWidget(canvas);

    toolBar = addToolBar("Tools");
    toolBar->setMovable(false);

    layersDock = new QDockWidget("Layers", this);
    layersDock->setAllowedAreas(Qt::LeftDockWidgetArea);

    layersDock->setWidget(new QLabel("Layers", layersDock));

    addDockWidget(Qt::LeftDockWidgetArea, layersDock);

    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    statusBar->showMessage("Ready");
}