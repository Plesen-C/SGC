#include "Scene.h"

int Scene::objectCount() const
{
    return static_cast<int>(objects.size());
}

GraphicObject* Scene::objectAt(int index) const
{
    if (index < 0 || index >= objectCount())
        return nullptr;

    return objects[index].get();
}

GraphicObject* Scene::objectById(ObjectId id) const
{
    for (const auto& object : objects)
    {
        if (object->id() == id)
            return object.get();
    }

    return nullptr;
}

void Scene::addObject(std::unique_ptr<GraphicObject> object)
{
    if (!object)
        return;

    object->objectId = nextObjectId++;

    objects.push_back(std::move(object));
}

void Scene::selectObject(int index)
{
    if (index < 0 || index >= objectCount())
        return;

    for (int i = 0; i < objectCount(); ++i)
    {
        objects[i]->setSelected(i == index);
    }
}

int Scene::selectedObjectIndex() const
{
    for (int i = 0; i < objectCount(); ++i)
    {
        if (objects[i]->isSelected())
            return i;
    }

    return -1;
}

void Scene::deselectAll()
{
    for (auto& object : objects)
    {
        object->setSelected(false);
    }
}

void Scene::deleteSelected()
{
    for (auto it = objects.begin(); it != objects.end();)
    {
        if ((*it)->isSelected())
            it = objects.erase(it);
        else
            ++it;
    }
}

void Scene::moveObjectUp(int index)
{
    if (index < 0 || index >= objectCount() - 1)
        return;

    std::swap(objects[index], objects[index + 1]);
}

void Scene::moveObjectDown(int index)
{
    if (index <= 0 || index >= objectCount())
        return;

    std::swap(objects[index], objects[index - 1]);
}