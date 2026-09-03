#include "GraphicObject.h"

void GraphicObject::setSelected(bool value)
{
    selected = value;
}

bool GraphicObject::isSelected() const
{
    return selected;
}

ObjectId GraphicObject::id() const
{
    return objectId;
}

const QString& GraphicObject::name() const
{
    return objectName;
}

void GraphicObject::setName(const QString& value)
{
    objectName = value;
}