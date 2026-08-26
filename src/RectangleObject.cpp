#include "RectangleObject.h"
#include "QPoint"
#include <QPainter>
RectangleObject::RectangleObject(int x, int y, int width, int height) : x(x), y(y),width(width),height(height){
}
void RectangleObject::draw(QPainter& painter){
    if (selected)
    {
        QPen selectionPen(Qt::yellow);
        selectionPen.setWidth(3);
        painter.setPen(selectionPen);
    }
    else{
        painter.setPen(Qt::white);
    }
    painter.drawRect(x,y,width,height);
}
bool RectangleObject::contains(const QPoint& point) const {
    return point.x() >= x && point.x() <= x + width && point.y() >= y && point.y() <= y + height;
}

