#pragma once

#include <cstdint>
#include <QString>

class QPainter;
class QPoint;

using ObjectId = std::uint64_t;

class GraphicObject
{
public:
    virtual ~GraphicObject() = default;

    virtual void draw(QPainter& painter) = 0;
    virtual bool contains(const QPoint& point) const = 0;
    virtual void moveBy(int dx, int dy) = 0;

    // Тип объекта
    virtual QString typeName() const = 0;

    // Выделение
    void setSelected(bool value);
    bool isSelected() const;

    // ID
    ObjectId id() const;

    // Имя
    const QString& name() const;
    void setName(const QString& value);

protected:
    friend class Scene;

    ObjectId objectId = 0;
    QString objectName = "Object";

    bool selected = false;
};