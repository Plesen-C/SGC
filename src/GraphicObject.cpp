#include "GraphicObject.h"
void GraphicObject::setSelected(bool value){
    selected = value;
}
bool GraphicObject::isSelected() const{
    return selected;
}