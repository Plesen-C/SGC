#include "LineObject.h"
#include <QPainter>
#include <algorithm>

LineObject::LineObject(int x1, int y1, int x2, int y2) 
    : x1(x1), y1(y1), x2(x2),y2(y2){}
void LineObject::draw(QPainter& painter){
    painter.drawLine(x1,y1,x2,y2);
}
bool LineObject::contains(const QPoint& point) const{
    const double dx = x2 - x1;
    const double dy = y2 - y1;
    const double lengthSquared = dx * dx + dy *dy;
    if (lengthSquared == 0)
        return false;
    const double t = std::clamp(
        ((point.x()-x1)*dx+(point.y()-y1)*dy)/lengthSquared,0.0,1.0
    );
    const double closestX = x1 + t * dx;
    const double closestY = y1 + t * dy;
    const double distX = point.x() - closestX;
    const double distY = point.y() - closestY;
    return (distX * distX + distY * distY) <= 36;
}
void LineObject::moveBy(int dx, int dy){
    x1 += dx;
    y1 += dy;
    x2 += dx;
    y2 += dy;
}