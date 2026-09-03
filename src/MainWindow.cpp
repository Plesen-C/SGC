#include "MainWindow.h"
#include "canvas.h"
#include "HUDWidget.h"

#include <QWidget>
#include <QFile>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("SGC — System Graphics Creation");
    resize(1200, 800);

    QWidget *central = new QWidget(this);

    QHBoxLayout *layout = new QHBoxLayout(central);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    canvas = new Canvas(central);

    hud = new HUDWidget(canvas, central);
    hud->setFixedWidth(400);

    layout->addWidget(hud, 0);
    layout->addWidget(canvas, 1);

    setCentralWidget(central);

    connect(canvas, &Canvas::objectsChanged,
            hud, [this]()
    {
        hud->update();
    });

    QFile styleFile("assets/styles/style.qss");

    if (styleFile.open(QFile::ReadOnly | QFile::Text))
    {
        setStyleSheet(QString::fromUtf8(styleFile.readAll()));
        styleFile.close();
    }

    canvas->setFocus();
}