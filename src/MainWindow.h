#pragma once
#include <QMainWindow>
#include <QToolBar>
#include <QListWidget>
#include <QAction>
#include "canvas.h"
#include <QDockWidget>
#include <QStatusBar>
class MainWindow : public QMainWindow
{
    public:
        MainWindow(QWidget *parent = nullptr);
    private:
        void refreshLayers();
        Canvas* canvas;
        QToolBar* toolBar;
        QDockWidget* layersDock;
        QStatusBar* statusBar;
        QAction* selectAction;
        QAction* rectangleAction;
        QAction* lineAction;
        QListWidget* layersList;
};