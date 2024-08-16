#include "Spaceship.h"
#include "Fighting.h"
#include <thread>

FightingShip::FightingShip()
{
}

FightingShip::~FightingShip()
{
}

double FightingShip::getShipLoss()
{
    return FLoss;
}

bool FightingShip::ThrShipLogin(bool temp)
{
    try
    {
        while (!EndFlag)
        {
            Sleep(randNum(25.0, 1000.0) * 1000);
            string RLOAD = to_string(randNum(25.0, 1500.0)); // random payload
            string RSNAME = randStr(randNum(3, 15));         // random ship name
            string ROWNME = randStr(randNum(3, 15));         // random owner name
            string DD = to_string(randNum(0.00, 100.00));           // random degree of damage

            F_ship.connectToDB("localhost", "root", "root", "spaceship");

            F_ship.Query(
                "insert into spaceship.ship(id,shipname,shiptype,payload,sowner,c_numc,f_loss,t_load) \
				value(default,'" +
                RSNAME + "','Fighting','" + RLOAD + "','" + ROWNME + "',NULL," + DD +",NULL);");

            F_ship.closeConnection();
            Modify = true;
        }
        return true;
    }
    catch (...)
    {
        FightingShip Temp;
        thread Thrnd(&FightingShip::ThrShipLogin, &Temp, false);
        return false;
    }
}

bool FightingShip::ShipLogin(int id)
{
    return false;
}

bool FightingShip::ShipExists(int id)
{
    return false;
}
