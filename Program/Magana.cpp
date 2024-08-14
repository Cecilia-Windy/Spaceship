#include "Spaceship.h"
#include "Commuter.h"
#include "Fighting.h"
#include "Transport.h"
#include <mysql.h>
#include <iostream>
#include <thread>
#include <windows.h>
#include <cstdlib>

using namespace std;

int main()
{
    FightingShip FS;
    CommuterShip CS;
    TransportShip TS;
    Spaceship ship;

    thread F(&FightingShip::ThrShipLogin, &FS, false);
    F.detach();

    thread T(&TransportShip::ThrShipLogin, &TS, false);
    T.detach();

    thread C(&CommuterShip::ThrShipLogin, &CS, false);
    C.detach();

    bool flag = true; // Login flag

    cout << "Welcome to the Database of Spaceship in the Forest! \n"
         << endl;

    while (true)
    {
        if (flag) // 第一次查询并输出数据
        {
            cout << "Show the data of spaceship ?" << endl
                 << "[Y | N] : ";
            OutInfo(ship);
            flag = false;
        }
        if (Modify)
        {
            cout << "[Ship data changed] " << endl
                 << "show it ? [Y | N] : ";
            OutInfo(ship);
            Modify = false;
        }
        cout << "Break? [Y | N]: ";
        char flg = '\0';
        cin >> flg;
        if (flg == 'Y' || flg != 'y') break;
    }
    EndFlag = true;

    Sleep(5000);
    system("pause");
    return 0;
}
