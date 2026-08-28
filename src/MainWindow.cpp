#include "MainWindow.h"
#include "canvas.h"
#include "HUDWidget.h"

#include <QWidget>
#include <QFile>
#include <QStackedLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("SGC — System Graphics Creation");
    resize(1200, 800);

    QWidget *central = new QWidget(this);

    QStackedLayout *layout = new QStackedLayout(central);
    layout->setStackingMode(QStackedLayout::StackAll);
    layout->setContentsMargins(0, 0, 0, 0);

    canvas = new Canvas(central);
    layout->addWidget(canvas);

    hud = new HUDWidget(canvas, central);
    layout->addWidget(hud);

    setCentralWidget(central);

    hud->raise();
    hud->show();

    connect(canvas, &Canvas::objectsChanged,
            hud, [this]()
    {
        hud->update();
    });

    QFile styleFile("assets/style.qss");

    if (styleFile.open(QFile::ReadOnly | QFile::Text))
    {
        setStyleSheet(QString::fromUtf8(styleFile.readAll()));
        styleFile.close();
    }

    canvas->setFocus();
}