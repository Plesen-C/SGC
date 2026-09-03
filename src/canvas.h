#pragma once

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QKeyEvent>

#include "GraphicObject.h"
#include "RectangleObject.h"
#include "Scene.h"

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);

    int objectCount() const;
    GraphicObject* objectAt(int index) const;

    void selectObject(int index);
    int selectedObjectIndex() const;
    void createRectangle(QPoint position);
protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

private:
    Scene scene;

    GraphicObject* draggedObject = nullptr;
    QPoint lastMousePosition;

    RectangleObject* resizedRectangle = nullptr;
    int resizedHandle = 0;

    bool panning = false;
    QPoint panStart;
    QPoint rightClickStart;
    QPoint canvasOffset;


    void moveObjectUp(int index);
    void moveObjectDown(int index);

signals:
    void objectSelected(int index);
    void objectsChanged();
};