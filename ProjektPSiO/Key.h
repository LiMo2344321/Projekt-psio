#ifndef KEY_H
#define KEY_H

#include "Collectable.h"
class Key : public Collectable {
public:
    Key(const std::vector<sf::Texture>& textures, float x, float y)
        : Collectable(textures, x, y) {}
};

#endif
