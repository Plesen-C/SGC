#pragma once

#include <QMainWindow>

class Canvas;
class HUDWidget;

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    Canvas *canvas;
    HUDWidget *hud;
};