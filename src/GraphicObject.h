#pragma once
class QPainter;
class QPoint;

class GraphicObject {
    public:
        virtual ~GraphicObject() = default;
        virtual void draw(QPainter& painter) = 0;
        virtual bool contains(const QPoint& point) const = 0;
        virtual void moveBy(int dx, int dy) = 0;

        void setSelected(bool value);
        bool isSelected() const;

    protected:
        bool selected = false;
};
