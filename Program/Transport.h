#pragma once

#include "Spaceship.h"

class TransportShip : 
    public Spaceship
{
    friend class Spaceship;

public:
    TransportShip();
    ~TransportShip();

    double getShipLoad();

    bool ThrShipLogin(bool); // Use Thread
    bool ShipLogin(int id);
    bool ShipExists(int id);

private:
    Spaceship T_ship;

    double CCW; // Current cargo weight
};
