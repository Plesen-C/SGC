#pragma once
#include <QWidget>
#include <QMouseEvent>
#include <vector>
#include <memory>
#include "GraphicObject.h"
class Canvas : public QWidget{
    public:
        explicit Canvas(QWidget *parent = nullptr);
    protected:
    
        void paintEvent(QPaintEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
    private:
        std::vector<std::unique_ptr<GraphicObject>> objects;
};