#include "canvas.h"
#include "GraphicObject.h"
#include "LineObject.h"
#include "RectangleObject.h"
#include <QPainter>
#include <QMenu>
#include <memory>
#include <qcolor.h>
#include <qevent.h>
#include <qnamespace.h>
#include <qpoint.h>

Canvas::Canvas(QWidget * parent) : QWidget(parent){setFocusPolicy(Qt::StrongFocus);}
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
    painter.translate(canvasOffset);
    for (const auto& object : objects){
        object -> draw(painter);//sex
    }
}
void Canvas::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::RightButton){
        panning = true;
        panStart = event->pos();
        rightClickStart = event->pos();
        return;
    }
    if(event->button() != Qt::LeftButton){
        setFocus();
        return;
    }
    const QPoint position = event->pos() - canvasOffset;
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
            emit objectsChanged();
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
        emit objectsChanged();
        draggedObject = it->get();
        lastMousePosition = position;
        update();
        return;
    }

    }
update();
}

void Canvas::mouseMoveEvent(QMouseEvent *event){
    if (panning) {
        const QPoint currentPosition = event->pos();
        const QPoint delta = currentPosition - panStart;
        canvasOffset += delta;
        panStart = currentPosition;
        update();
        return;
    }
    
    const QPoint currentPosition = event->pos()- canvasOffset;
    const int dx = currentPosition.x() - lastMousePosition.x();
    const int dy = currentPosition.y() - lastMousePosition.y();
    if (resizedRectangle){
        resizedRectangle -> resizeBy(dx,dy, resizedHandle);
        lastMousePosition = currentPosition;
        update();
        return;
    }
    if (draggedObject){
        draggedObject -> moveBy(dx,dy);
        lastMousePosition = currentPosition;
        update();
        
    }
    update();
}
void Canvas::mouseReleaseEvent(QMouseEvent *event){
if (event->button() == Qt::RightButton)
{
    panning = false;
    const QPoint delta = event->pos() - rightClickStart;
    if (delta.manhattanLength() < 5)
    {
        QMenu menu(this);
        QAction* rectangleAction = menu.addAction("Rectangle");
        QAction* lineAction = menu.addAction("Line");
        QAction* selectedAction = menu.exec(event->globalPosition().toPoint());
        if (selectedAction == rectangleAction)
        {
            QPoint pos = event->pos() - canvasOffset;
            for (auto& object : objects)
                object->setSelected(false);
            auto rectangle = std::make_unique<RectangleObject>(pos.x()-25,pos.y()-25,50,50);
            rectangle->setSelected(true);
            objects.push_back(std::move(rectangle));
            emit objectsChanged();
            update();
        }
        else if (selectedAction == lineAction)
        {
            qDebug() << "Create Line";
        }
    }
    return;
}
    if(event->button() == Qt::LeftButton)
    {
        draggedObject = nullptr;
        resizedRectangle = nullptr;
        resizedHandle =0;
    }
}
void Canvas::keyPressEvent(QKeyEvent *event)
{
    const int count = objectCount();

    switch (event->key())
    {
        case Qt::Key_Down:
        {
            if (count == 0)
                return;

            int index = selectedObjectIndex();

            if (index < 0)
                index = count - 1;
            else
                index--;

            if (index < 0)
                index = count - 1;

            selectObject(index);
            return;
        }

        case Qt::Key_Up:
        {
            if (count == 0)
                return;

            int index = selectedObjectIndex();

            if (index < 0)
                index = 0;
            else
                index++;

            if (index >= count)
                index = 0;

            selectObject(index);
            return;
        }

        case Qt::Key_Delete:
        {
            for (auto it = objects.begin(); it != objects.end();)
            {
                if ((*it)->isSelected())
                    it = objects.erase(it);
                else
                    ++it;
            }

            emit objectsChanged();
            update();
            return;
        }

        case Qt::Key_Escape:
        {
            for (auto &object : objects)
                object->setSelected(false);

            emit objectsChanged();
            update();
            return;
        }

        case Qt::Key_Return:
        case Qt::Key_Enter:
        {
            if (count > 0 && selectedObjectIndex() < 0)
                selectObject(0);

            return;
        }

        default:
            break;
    }

    QWidget::keyPressEvent(event);
}
int Canvas::objectCount() const
{
    return static_cast<int>(objects.size());
}
GraphicObject* Canvas::objectAt(int index) const
{
    if (index < 0 || index >= static_cast<int>(objects.size()))
        return nullptr;

    return objects[index].get();
}
int Canvas::selectedObjectIndex() const
{
    for (int i = 0; i < objectCount(); ++i)
    {
        if (objects[i]->isSelected())
            return i;
    }

    return -1;
}

void Canvas::selectObject(int index)
{
    if (index < 0 || index >= objectCount())
        return;

    for (int i = 0; i < objectCount(); ++i)
        objects[i]->setSelected(i == index);

    emit objectsChanged();
    update();
}