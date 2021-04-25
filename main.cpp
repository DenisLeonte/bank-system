#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "syscomms.h"
#include "login.h"
#include "account.h"

using namespace std;

void login_screen()
{
    clear();
    int op = 0;
    cout<<"1. Login\n";
    cout<<"2.Register\n";
    cin>>op;
    if(op == 1)
    {
        login();
    }
    else if(op == 2)
    {
        create_user();
    }
    else
    {
        cout<<"INVALID CHOICE\n";
        pause();
        login_screen();
    }
}

int main()
{
    bool isRunning = true;
    login_screen();
    while(isRunning)
    {
    }
    return 0;
}