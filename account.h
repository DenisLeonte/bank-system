#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>

int m_code = 0;

class account
{
public:
    float balance = 0.0f;
    std::string name = "", surname = "";
    int code = 0;
    void input();
};

#endif