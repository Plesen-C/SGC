#include "canvas.h"
#include "GraphicObject.h"
#include "LineObject.h"
#include "RectangleObject.h"
#include <QPainter>
#include <memory>
#include <qcolor.h>
#include <qevent.h>
#include <qnamespace.h>
#include <qpoint.h>
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
}
void Canvas::mousePressEvent(QMouseEvent *event){
    if(event->button() != Qt::LeftButton)
        return;
    const QPoint position = event->pos();
    draggedObject = nullptr;
    resizedRectangle = nullptr;
    resizedHandle = 0;
    for (auto& object : objects)
        object -> setSelected(0);
    
    for (auto it = objects.rbegin(); it != objects.rend(); ++it)
{
    auto* rectangle = dynamic_cast<RectangleObject*>(it->get());

    if (rectangle)
    {
        const int handle = rectangle->handleAt(position);

        if (handle != 0)
        {
            rectangle->setSelected(true);

            resizedRectangle = rectangle;
            resizedHandle = handle;
            lastMousePosition = position;

            update();
            return;
        }
    }

    if ((*it)->contains(position))
    {
        (*it)->setSelected(true);

        draggedObject = it->get();
        lastMousePosition = position;

        update();
        return;
    }

    }
update();
}

void Canvas::mouseMoveEvent(QMouseEvent *event){
    
    const QPoint currentPosition = event->pos();
    const int dx = currentPosition.x() - lastMousePosition.x();
    const int dy = currentPosition.y() - lastMousePosition.y();
    if (resizedRectangle){
        resizedRectangle -> resizeBy(dx,dy, resizedHandle);
        lastMousePosition = currentPosition;
        update();
        return;
    }
    if (draggedObject){
        draggedObject -> moveBy(dx, dy);
        lastMousePosition = currentPosition;
        update();
        
    }
    update();
}
void Canvas::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton)
    {
        draggedObject = nullptr;
        resizedRectangle = nullptr;
        resizedHandle =0;
    }
}