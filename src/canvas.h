#pragma once
#include <QWidget>
#include <QMouseEvent>
#include <qpoint.h>
#include <vector>
#include <memory>
#include "GraphicObject.h"
#include "RectangleObject.h"
class Canvas : public QWidget{
    public:
        explicit Canvas(QWidget *parent = nullptr);
    protected:
        void paintEvent(QPaintEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
    private:
        GraphicObject* draggedObject = nullptr;
        QPoint lastMousePosition;
        RectangleObject* resizedRectangle = nullptr;
        int resizedHandle = 0;
        std::vector<std::unique_ptr<GraphicObject>> objects;
};