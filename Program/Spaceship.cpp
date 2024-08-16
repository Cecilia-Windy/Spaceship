#include "Spaceship.h"
#include "Fighting.h"
#include "Transport.h"
#include "Commuter.h"
#include <iostream>
#include <mysql.h>
#include <string>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

Spaceship::Spaceship()
{
}

Spaceship::~Spaceship()
{
}

string randStr(const int len) // 参数为字符串的长度
{
    string str;                       // 声明用来保存随机字符串的str
    srand(static_cast<int>(time(0))); // 设置随机数种子
    // rand()%26是取余，余数为0~25加上'a',就是字母a~z,push_back()是string类尾插函数。这里插入随机字符
    for (int idx = 0; idx < len; idx++)
        str.push_back(('a' + rand() % 26));
    return str;
}

bool Spaceship::connectToDB(string host, string username, string password, string database)
{
    mysql_init(&mysql); // 初始化数据库连接

    mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk"); // 设置字符集

    if (mysql_real_connect(&mysql, host.c_str(), username.c_str(), password.c_str(), database.c_str(), 3306, NULL, 0) == NULL) // 连接数据库
    {
        cout << "connect error: " << mysql_error(&mysql) << endl;
        return false;
    }
    return true;
}

void Help()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 12);
    cout << endl
         << "[Tabular Output of the Database]:\n"
         << "N P : Number of Passengers\n"
         << "D D : Degree of Damage\n"
         << "C W : Current cargo weight"
         << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 7); //"7"设置白色
    Sleep(2000);
    return;
}

void OutInfo(Spaceship &ship)
{

    ship.connectToDB("localhost", "root", "root", "spaceship");

    ship.Query("SELECT * FROM ship;"); // 查询数据
    ship.getResult();                  // 获取查询结果

    ship.outCF("id", 8);
    ship.outCF("ship name", 8);
    ship.outCF("ship type", 8);
    ship.outCF("payload", 8);
    ship.outCF("ship owner", 8);
    ship.outCF("P N [Per]", 8);
    ship.outCF("D D [%]", 8);
    ship.outCF("C W [T]", 8);
    cout << endl;

    while (ship.whileRow()) // 遍历结果
    {
        ship.outCF(ship.getRowi(0), 8); // id
        ship.outCF(ship.getRowi(1), 8); // shipname
        ship.outCF(ship.getRowi(2), 8); // shiptype
        ship.outCF(ship.getRowi(3), 8); // payload
        ship.outCF(ship.getRowi(4), 8); // ship owner

        ship.outCF(ship.getRowi(5), 8); // Num of Passengers
        ship.outCF(ship.getRowi(6), 8); // Degree of Damage
        ship.outCF(ship.getRowi(7), 8); // Current cargo weight
        cout << endl;
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 14);
    cout << "[Attention]" << endl
         << "N P = Number of Passengers" << endl
         << "D D = Degree of Damage" << endl
         << "C W = Current cargo weight" << endl
         << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 7); //"7"设置白色
    Sleep(2000);

    mysql_free_result(ship.returnResult()); // 释放结果集
    ship.closeConnection();                 // 关闭数据库连接
}
