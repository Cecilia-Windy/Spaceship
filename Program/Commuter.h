#pragma once

#include "Spaceship.h"

class CommuterShip : public Spaceship
{
    friend class Spaceship;

public:
    CommuterShip();
    ~CommuterShip();

    int getPGNum();

    bool ThrShipLogin(bool); // Use Thread
    bool ShipLogin(int id);
    bool ShipExists(int id);

private:
    Spaceship C_ship;
    int PNum; // Number of Passengers Carrying
};