#pragma once
#include "GraphicObject.h"
#include <QPainter>
#include <QPoint>
#include <qcolor.h>

class RectangleObject : public GraphicObject{
    public:
        RectangleObject(int x, int y, int width, int height);
        void draw(QPainter& painter) override;
        bool contains(const QPoint& point) const override;
    private:
     int x;
     int y;
     int width;
     int height;
};
