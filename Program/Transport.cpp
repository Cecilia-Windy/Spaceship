#include "Spaceship.h"
#include "Transport.h"
#include <thread>

TransportShip::TransportShip()
{
}

TransportShip::~TransportShip()
{
}

double TransportShip::getShipLoad()
{
    return CCW;
}

bool TransportShip::ThrShipLogin(bool temp)
{
    try
    {
        while (true)
        {
            Sleep(randNum(25.0, 1000.0) * 1000);
            string RLOAD = to_string(randNum(25.0, 1500.0)); // random payload
            string RSNAME = randStr(randNum(3, 15));     // random ship name
            string ROWNME = randStr(randNum(3, 15));     // random owner name

            T_ship.connectToDB("localhost", "root", "root", "spaceship");

            T_ship.Query(
                "insert into spaceship.ship(id,shipname,shiptype,payload,sowner,c_numc,f_loss,t_load) \
				value(default,'" +
                RSNAME + "','Fighting','" + RLOAD + "','" + ROWNME + "',null,0.00,null);");

            T_ship.closeConnection();
            Modify = true;
        }
        return true;
    }
    catch (...)
    {
        TransportShip Temp;
        thread Thrnd(&TransportShip::ThrShipLogin, &Temp, false);
        return false;
    }
}

bool TransportShip::ShipLogin(int id)
{
    return false;
}

bool TransportShip::ShipExists(int id)
{
    return false;
}
