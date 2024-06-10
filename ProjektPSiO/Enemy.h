#ifndef ENEMY_H
#define ENEMY_H

#include "Postac.h"

class Enemy : public Postac {
public:
    Enemy(float gravity, int health) : Postac(gravity), health(health) {}

    void takeDamage(int damage) {
        if (health > 0) {
            health -= damage;
        }
    }

    bool isAlive() const {
        return health > 0;
    }

    int getHealth() const {
        return health;
    }

protected:
    int health;
};

#endif 

