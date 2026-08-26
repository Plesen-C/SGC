#include "RectangleObject.h"
#include "GraphicObject.h"
#include "QPoint"
#include <QPainter>
#include <qnamespace.h>
RectangleObject::RectangleObject(int x, int y, int width, int height) : x(x), y(y),width(width),height(height){
}
void RectangleObject::draw(QPainter& painter){
    if (selected)
    {
        QPen selectionPen(Qt::yellow);
        selectionPen.setWidth(2);
        selectionPen.setStyle(Qt::DashLine);
        painter.setPen(selectionPen);
        painter.drawRect(x-6,y-6,width + 12,height + 12);
        painter.setPen(Qt::yellow);
        painter.setBrush(Qt::yellow);
        const int handleSize = 16;

        painter.drawRect(x-handleSize /2, y-handleSize/2, handleSize,handleSize);
        painter.drawRect(x + width - handleSize/ 2 , y- handleSize/2, handleSize, handleSize);
        painter.drawRect(x-handleSize/2, y + height - handleSize/2,handleSize,handleSize);
        painter.drawRect(x + width - handleSize/2, y+height-handleSize/2,handleSize,handleSize);

    }
    else{
        painter.setPen(Qt::white);
    }
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(x,y,width,height);
}
bool RectangleObject::contains(const QPoint& point) const {
    return point.x() >= x && point.x() <= x + width && point.y() >= y && point.y() <= y + height;
}
int RectangleObject::handleAt(const QPoint& point)const {
    const int handleSize = 16; 
    const int half = handleSize /2;
    QRect topLeft(x-half,y-half,handleSize,handleSize);
    QRect topRight(x+width-half,y-half,handleSize,handleSize);
    QRect bottomLeft(x-half,y+height-half,handleSize,handleSize);
    QRect bottomRight(x+width-half,y+height-half,handleSize,handleSize);
    if (topLeft.contains(point))
        return 1;
    if (topRight.contains(point))
        return 2;
    if (bottomRight.contains(point))
        return 3;
    if (bottomLeft.contains(point))
        return 4;
    return 0;
}
void RectangleObject::moveBy(int dx, int dy){
    x += dx;
    y += dy;
}
void RectangleObject::resizeBy(int dx, int dy,int handle){
    const int minSize = 20;
    switch (handle) {
        case 1:
            x += dx;
            y += dy;
            width -= dx;
            height -= dy;
            break;
        case 2:
            y+=dy;
            width += dx;
            height -= dy;
            break;
        case 3:
            width += dx;
            height += dy;
            break;
        case 4:
            x += dx;
            width -= dx;
            height += dy;
            break;
    }

    if (width < minSize)
        width = minSize;

    if (height < minSize)
        height = minSize;
}
