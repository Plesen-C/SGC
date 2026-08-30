#pragma once

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>


class Canvas;

class HUDWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HUDWidget(Canvas *canvas, QWidget *parent = nullptr); 

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    Canvas *canvas;
    int hoveredAction = -1;
};