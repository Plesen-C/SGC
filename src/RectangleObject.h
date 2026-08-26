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
        int handleAt(const QPoint& point) const;
        void moveBy(int dx, int dy) override;
        void resizeBy(int dx, int dy,int handle);
    private:
     int x;
     int y;
     int width;
     int height;
};
