#pragma once
#include "GraphicObject.h"
#include <QPoint>
class LineObject : public GraphicObject{
    public:
        LineObject(int x1, int y1, int x2, int y2);
        void draw(QPainter& painter) override;
        bool contains(const QPoint& point) const override;
    private:
        int x1;
        int y1;
        int x2;
        int y2;
};