#ifndef ENEMY_H
#define ENEMY_H

#include "Postac.h"

class Enemy : public Postac {
public:
    Enemy(float gravity) : Postac(gravity) {}
};

#endif // ENEMY_H
