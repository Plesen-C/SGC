#pragma once

#include <vector>
#include <memory>

#include "GraphicObject.h"

class Scene
{
public:
    int objectCount() const;

    GraphicObject* objectAt(int index) const;
    GraphicObject* objectById(ObjectId id) const;

    void addObject(std::unique_ptr<GraphicObject> object);

    void selectObject(int index);
    int selectedObjectIndex() const;
    void deselectAll();

    void deleteSelected();

    void moveObjectUp(int index);
    void moveObjectDown(int index);

private:
    std::vector<std::unique_ptr<GraphicObject>> objects;

    ObjectId nextObjectId = 1000;
};