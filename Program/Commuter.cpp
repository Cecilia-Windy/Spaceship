#include "Spaceship.h"
#include "Commuter.h"
#include <thread>

CommuterShip::CommuterShip()
{
}

CommuterShip::~CommuterShip()
{
}

int CommuterShip::getPGNum()
{
    return PNum;
}

bool CommuterShip::ThrShipLogin(bool temp)
{
    try
    {
        while (!EndFlag)
        {
            Sleep(randNum(25.0, 1000.0) * 1000);
            string RLOAD = to_string(randNum(25.0, 1500.0)); // random payload
            string RSNAME = randStr(randNum(3, 15));         // random ship name
            string ROWNME = randStr(randNum(3, 15));         // random owner name
            string NP = to_string((randNum(1, 1500)));       // random number of passengers

            C_ship.connectToDB("localhost", "root", "root", "spaceship");

            C_ship.Query(
                "insert into spaceship.ship(id,shipname,shiptype,payload,sowner,c_numc,f_loss,t_load) \
				value(default,'" +
                RSNAME + "','Fighting'," + RLOAD + ",'" + ROWNME + "'," + NP + ",NULL,NULL);");

            C_ship.closeConnection();
            Modify = true;
        }
        return true;
    }
    catch (...)
    {
        CommuterShip Temp;
        thread Thrnd(&CommuterShip::ThrShipLogin, &Temp, false);
        return false;
    }
}

bool CommuterShip::ShipLogin(int id)
{
    return false;
}

bool CommuterShip::ShipExists(int id)
{
    return false;
}
