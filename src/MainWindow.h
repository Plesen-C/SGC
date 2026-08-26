#pragma once
#include <QMainWindow>
#include <QToolBar>
#include "canvas.h"
#include <QDockWidget>
#include <QStatusBar>
class MainWindow : public QMainWindow
{
    public:
        MainWindow(QWidget *parent = nullptr);
    private:
        Canvas* canvas;
        QToolBar* toolBar;
        QDockWidget* layersDock;
        QStatusBar* statusBar;
};