#pragma once

#include "Spaceship.h"

class FightingShip :
    public Spaceship
{
    friend class Spaceship;

public:
    FightingShip();
    ~FightingShip();

    double getShipLoss();

    bool ThrShipLogin(bool); // Use Thread
    bool ShipLogin(int id);
    bool ShipExists(int id);

private:
    Spaceship F_ship;

    double FLoss; // Degree of Damage
};