#pragma once

#include <QWidget>


class Canvas;

class HUDWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HUDWidget(Canvas *canvas, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Canvas *canvas;
};