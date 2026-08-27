#include "MainWindow.h"
#include <QWidget>
#include <qwidget.h>
#include "canvas.h"
#include "LineObject.h"
#include <QVBoxLayout>
#include <QFile>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("SGC — System Graphics Creation");
    resize(1200, 800);

    canvas = new Canvas(this);
    setCentralWidget(canvas);
    connect(canvas, &Canvas::objectsChanged,
        this, &MainWindow::refreshLayers);
    QFile styleFile("assets/style.qss");

    if (styleFile.open(QFile::ReadOnly | QFile::Text))
    {
        setStyleSheet(QString::fromUtf8(styleFile.readAll()));
        styleFile.close();
    }

    toolBar = addToolBar("Tools");
    toolBar->setMovable(false);
    selectAction = new QAction("Select", this);
    rectangleAction = new QAction("Rectangle", this);
    lineAction = new QAction("Line", this);

    selectAction->setCheckable(true);
    rectangleAction->setCheckable(true);
    lineAction->setCheckable(true);

    selectAction->setChecked(true);

    toolBar->addAction(selectAction);
    toolBar->addAction(rectangleAction);
    toolBar->addAction(lineAction);

    layersDock = new QDockWidget("OBJECTS", this);
    layersDock->setAllowedAreas(Qt::LeftDockWidgetArea);

    layersList = new QListWidget(layersDock);
    std::vector<std::unique_ptr<GraphicObject>> objects;

    layersDock->setWidget(layersList);

    addDockWidget(Qt::LeftDockWidgetArea, layersDock);
    refreshLayers();

    connect(layersList, &QListWidget::currentRowChanged,
        this, [this](int row)
{
    if (row < 0)
        return;
    const int objectIndex = canvas->objectCount() - 1 - row;

    canvas->selectObject(objectIndex);
});

    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    statusBar->showMessage("Ready");
}
void MainWindow::refreshLayers()
{
    layersList->clear();
    for (int i = canvas->objectCount() - 1; i >= 0; --i)
    {
        GraphicObject* object = canvas->objectAt(i);
        if (!object)
            continue;
        QString name;
        if (dynamic_cast<RectangleObject*>(object))
            name = "▣ RECTANGLE";
        else if (dynamic_cast<LineObject*>(object))
            name = "─ LINE";
        else
            name = "? OBJECT";

        layersList->addItem(name);
    }
}