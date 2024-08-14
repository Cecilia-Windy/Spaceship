#pragma once
#include <iostream>
#include <mysql.h>
#include <string>
#include <iomanip>
#include <random>
#include <cstdlib>

using namespace std;

static bool Modify = false;
static bool EndFlag = false;

class Spaceship;
class TransportShip;
class FightingShip;
class CommuterShip;

// 声明函数
void OutInfo(Spaceship &ship);

class Uncopyable
{
protected:
    Uncopyable() {}
    virtual ~Uncopyable() {}

private:
    Uncopyable(const Uncopyable &);
    Uncopyable &operator=(const Uncopyable &);
};

class Spaceship : private Uncopyable // Spaceship
{
public: // BASIC
    Spaceship();
    virtual ~Spaceship();

    template <typename AnyNum> static AnyNum randNum(AnyNum, AnyNum);
    string randStr(const int len);

    bool connectToDB(string host, string username, string password, string database);

    inline MYSQL_ROW whileRow() { return row = mysql_fetch_row(result); }

    /*
        0 = 黑色  1 = 蓝色  2 = 绿色  3 = 浅绿色
        4 = 红色  5 = 紫色  6 = 黄色  7 = 白色
        8 = 灰色  9 = 淡蓝色     10 = 淡绿色
        11 = 淡浅绿色   12 = 淡红色    13 = 淡紫色
        14 = 淡黄色    15 = 亮白色
    */
    void outCF(const char* s, int color) // out with Color and Format
    {
        cout.width(16);
        cout.flags(ios::left);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | color);
        cout << s;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 7); //"7"设置白色
    }

    inline MYSQL_ROW returnRow() { return mysql_fetch_row(result); }
    inline char* getRowi(int i)
    {
        const char *str = "NULL";
        char *mutable_str = new char[strlen(str) + 1];
        strcpy_s(mutable_str, strlen(str) + 1, str);
        if (row[i] != NULL)
            return row[i];
        else
            return mutable_str;
    }

    inline void getResult() { result = mysql_store_result(&mysql); }
    inline MYSQL_RES *returnResult() { return result; }

    inline bool Query(string cmd) { return mysql_query(&mysql, cmd.c_str()); }
    inline void closeConnection() { mysql_close(&mysql); }

private:
    string str;
    MYSQL mysql;
    MYSQL_ROW row;
    MYSQL_RES *result;
};

template <typename AnyNum>
AnyNum Spaceship::randNum(AnyNum min, AnyNum max) // int or double
{
    if (typeid(min) == typeid(double) && typeid(max) == typeid(double))
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(min, max);
        return static_cast<AnyNum>(dis(gen));
    }
    if (typeid(min) == typeid(int) && typeid(max) == typeid(int))
    {
        return static_cast<AnyNum>(static_cast<int>(rand()) % static_cast<int>((max - min + 1) + min));
    }
    return static_cast<AnyNum>(NULL);
}
