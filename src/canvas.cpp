#include "canvas.h"
#include "GraphicObject.h"
#include "LineObject.h"
#include "RectangleObject.h"

#include <QPainter>
#include <QMenu>
#include <memory>

Canvas::Canvas(QWidget *parent)
    : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
}

void Canvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.fillRect(rect(), Qt::black);

    QPen gridPen;
    gridPen.setColor(QColor(40, 40, 40));
    gridPen.setWidth(1);

    painter.setPen(gridPen);

    for (int x = 0; x < width(); x += 50)
        painter.drawLine(x, 0, x, height());

    for (int y = 0; y < height(); y += 50)
        painter.drawLine(0, y, width(), y);

    painter.translate(canvasOffset);

    for (int i = 0; i < scene.objectCount(); ++i)
    {
        GraphicObject *object = scene.objectAt(i);

        if (object)
            object->draw(painter);
    }
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        panning = true;
        panStart = event->pos();
        rightClickStart = event->pos();
        return;
    }

    if (event->button() != Qt::LeftButton)
    {
        setFocus();
        return;
    }

    setFocus();

    const QPoint position = event->pos() - canvasOffset;

    draggedObject = nullptr;
    resizedRectangle = nullptr;
    resizedHandle = 0;

    scene.deselectAll();

    for (int i = scene.objectCount() - 1; i >= 0; --i)
    {
        GraphicObject *object = scene.objectAt(i);

        if (!object)
            continue;

        auto *rectangle = dynamic_cast<RectangleObject *>(object);

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

        if (object->contains(position))
        {
            object->setSelected(true);

            emit objectsChanged();

            draggedObject = object;
            lastMousePosition = position;

            update();
            return;
        }
    }

    emit objectsChanged();
    update();
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (panning)
    {
        const QPoint currentPosition = event->pos();
        const QPoint delta = currentPosition - panStart;

        canvasOffset += delta;
        panStart = currentPosition;

        update();
        return;
    }

    const QPoint currentPosition =
        event->pos() - canvasOffset;

    const int dx =
        currentPosition.x() - lastMousePosition.x();

    const int dy =
        currentPosition.y() - lastMousePosition.y();

    if (resizedRectangle)
    {
        resizedRectangle->resizeBy(
            dx,
            dy,
            resizedHandle
        );

        lastMousePosition = currentPosition;

        update();
        return;
    }

    if (draggedObject)
    {
        draggedObject->moveBy(dx, dy);

        lastMousePosition = currentPosition;

        update();
        return;
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        panning = false;

        const QPoint delta =
            event->pos() - rightClickStart;

        if (delta.manhattanLength() < 5)
        {
            QMenu menu(this);

            QAction *rectangleAction =
                menu.addAction("Rectangle");

            QAction *lineAction =
                menu.addAction("Line");

            QAction *selectedAction =
                menu.exec(
                    event->globalPosition().toPoint()
                );

            const QPoint position =
                event->pos() - canvasOffset;

            if (selectedAction == rectangleAction)
            {
                createRectangle(position);
            }
            else if (selectedAction == lineAction)
            {
                scene.deselectAll();

                auto line =
                    std::make_unique<LineObject>(
                        position.x() - 25,
                        position.y() - 25,
                        50,
                        50
                    );

                line->setSelected(true);

                scene.addObject(std::move(line));

                emit objectsChanged();
                update();
            }
        }

        return;
    }

    if (event->button() == Qt::LeftButton)
    {
        draggedObject = nullptr;
        resizedRectangle = nullptr;
        resizedHandle = 0;
    }
}

void Canvas::keyPressEvent(QKeyEvent *event)
{
    const int count = scene.objectCount();

    switch (event->key())
    {
        case Qt::Key_Down:
        {
            if (count == 0)
                return;

            int index = scene.selectedObjectIndex();

            if (index < 0)
                index = count - 1;
            else
                index--;

            if (index < 0)
                index = count - 1;

            scene.selectObject(index);

            emit objectsChanged();
            update();

            return;
        }

        case Qt::Key_Up:
        {
            if (count == 0)
                return;

            int index = scene.selectedObjectIndex();

            if (index < 0)
                index = 0;
            else
                index++;

            if (index >= count)
                index = 0;

            scene.selectObject(index);

            emit objectsChanged();
            update();

            return;
        }

        case Qt::Key_Delete:
        {
            scene.deleteSelected();

            emit objectsChanged();
            update();

            return;
        }

        case Qt::Key_Escape:
        {
            scene.deselectAll();

            emit objectsChanged();
            update();

            return;
        }

        case Qt::Key_PageUp:
        {
            scene.moveObjectUp(
                scene.selectedObjectIndex()
            );

            emit objectsChanged();
            update();

            return;
        }

        case Qt::Key_PageDown:
        {
            scene.moveObjectDown(
                scene.selectedObjectIndex()
            );

            emit objectsChanged();
            update();

            return;
        }

        case Qt::Key_Return:
        case Qt::Key_Enter:
        {
            if (count > 0 &&
                scene.selectedObjectIndex() < 0)
            {
                scene.selectObject(0);

                emit objectsChanged();
                update();
            }

            return;
        }

        default:
            break;
    }

    QWidget::keyPressEvent(event);
}

int Canvas::objectCount() const
{
    return scene.objectCount();
}

GraphicObject *Canvas::objectAt(int index) const
{
    return scene.objectAt(index);
}

int Canvas::selectedObjectIndex() const
{
    return scene.selectedObjectIndex();
}

void Canvas::selectObject(int index)
{
    scene.selectObject(index);

    emit objectsChanged();
    update();
}

void Canvas::moveObjectUp(int index)
{
    scene.moveObjectUp(index);

    emit objectsChanged();
    update();
}

void Canvas::moveObjectDown(int index)
{
    scene.moveObjectDown(index);

    emit objectsChanged();
    update();
}

void Canvas::createRectangle(QPoint position)
{
    scene.deselectAll();

    auto rectangle =
        std::make_unique<RectangleObject>(
            position.x() - 25,
            position.y() - 25,
            50,
            50
        );

    rectangle->setSelected(true);

    scene.addObject(std::move(rectangle));

    emit objectsChanged();
    update();
}