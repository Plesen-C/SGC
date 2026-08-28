#pragma once
#include <QWidget>
#include <QMouseEvent>
#include <qpoint.h>
#include <QKeyEvent>
#include <qtmetamacros.h>
#include <vector>
#include <memory>
#include "GraphicObject.h"
#include "RectangleObject.h"
class Canvas : public QWidget{
        Q_OBJECT
    public:
        explicit Canvas(QWidget *parent = nullptr);
        int objectCount() const;
        GraphicObject* objectAt(int index) const;
        void selectObject(int index);
        int selectedObjectIndex() const;
    protected:
        void paintEvent(QPaintEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void keyPressEvent(QKeyEvent* event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
    private:
        GraphicObject* draggedObject = nullptr;
        QPoint lastMousePosition;
        RectangleObject* resizedRectangle = nullptr;
        int resizedHandle = 0;
        std::vector<std::unique_ptr<GraphicObject>> objects;
        bool panning = false;
        QPoint panStart;
        QPoint rightClickStart;
        QPoint canvasOffset;
    signals:
        void objectSelected(int index);
        void objectsChanged();
};