#include "Spaceship.h"
#include "Commuter.h"
#include "Fighting.h"
#include "Transport.h"
#include <mysql.h>
#include <iostream>
#include <thread>
#include <windows.h>
#include <cstdlib>

// 创建对象
static FightingShip FS;
static CommuterShip CS;
static TransportShip TS;
static Spaceship ship;

static int Options = -1;
static string tempStr = "NULL";
static int ShipType = -1;

int main()
{
    // 代码块I: 启动线程
    {
        thread F(&FightingShip::ThrShipLogin, &FS, false);
        F.detach();

        thread T(&TransportShip::ThrShipLogin, &TS, false);
        T.detach();

        thread C(&CommuterShip::ThrShipLogin, &CS, false);
        C.detach();
    }

    // 代码块II: 主程序
    {
        cout << endl
             << "Welcome to the Manage System of Spaceship in the Forest!" << endl;
        while (true)
        {
            cout << endl
                 << "Please Enter :\n"
                 << "A:[Add Spaceship Info]\n"
                 << "D:[Delete Spaceship Info]\n"
                 << "S:[Show Data of Spaceship]\n"
                 << "[/help] | [Other to Exit]"
                 << endl;

            std::cin >> tempStr;
            if (tempStr == "/help")
            {
                Help();
                continue;
            }
            else if (tempStr == "A" || tempStr == "a" || tempStr == "1")
                Options = ADD;
            else if (tempStr == "D" || tempStr == "d" || tempStr == "2")
                Options = DEL;
            else if (tempStr == "S" || tempStr == "s" || tempStr == "3")
                Options = SHOW;
            else
                Options = -1;

            switch (Options)
            {
            case ADD:
                cout << "[/help] Please Enter the Type of Spaceship: ";
                cin >> tempStr;
                if (tempStr == "/help")
                {
                    Help();
                    continue;
                }
                else if (tempStr == "Fighting" || tempStr == "fighting" || tempStr == "F")
                    ShipType = FIGHTING;
                else if (tempStr == "Transport" || tempStr == "transport" || tempStr == "T")
                    ShipType = TRANSPORT;
                else if (tempStr == "Commuter" || tempStr == "commuter" || tempStr == "C")
                    ShipType = COMMUTER;
                else
                    continue;
                cout << ShipType;
                break;

            case DEL:
                break;

            case SHOW:
                OutInfo(ship);
                break;

            default:
                break;
            }
            if (Options != ADD && Options != DEL && Options != SHOW)
            {
                EndFlag = true;
                break;
            }
        }
    }

    system("pause");
    cout << "Waiting for the Thread to Finish...";
    Sleep(1000);
    return 0;
}