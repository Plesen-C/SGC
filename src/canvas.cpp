#include "canvas.h"
#include "GraphicObject.h"
#include "LineObject.h"
#include "RectangleObject.h"
#include <QPainter>
#include <memory>
#include <qcolor.h>
#include <qnamespace.h>
Canvas::Canvas(QWidget * parent) : QWidget(parent){
    objects.push_back(std::make_unique<LineObject>(30,250,120,120));
    objects.push_back(std::make_unique<RectangleObject>(500,150,200,80));
    objects.push_back(std::make_unique<RectangleObject>(700,400,100,150));
}
void Canvas::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.fillRect(rect(),Qt::black);
    QPen gridPen;
    gridPen.setColor(QColor(40,40,40));
    gridPen.setWidth(1);
    painter.setPen(gridPen);
    for (int x = 0; x < width(); x += 50){
        painter.drawLine(x,0,x,height());
    }
    for (int y = 0; y < height();y+=50){
        painter.drawLine(0,y,width(),y);
    }
    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawLine(100,200,200,200);
    pen.setColor(Qt::cyan);
    pen.setWidth(2);
    painter.setPen(pen);
    for (const auto& object : objects){
        object -> draw(painter);//sex
    }
    QFont font;
    font.setPointSize(20);
    font.setBold(1);
    painter.setFont(font);
    painter.drawText(100,150,"swag");

}
void Canvas::mousePressEvent(QMouseEvent *event){
    QPoint position = event->position().toPoint();
    for (const auto& object : objects){
        object->setSelected(object->contains(position));
    }
    update();
}