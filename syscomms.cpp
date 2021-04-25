#include "syscomms.h"
#include "account.h"
#include <algorithm>
#include <fstream>
#include <vector>
#ifdef __APPLE__
    #define WINDOWS_OS 0
    #include <unistd.h>
    #include <term.h>
    #include <stdlib.h>
#elif defined(_WIN32) || defined(WIN32)
    #define WINDOWS_OS 1
    #include <windows.h>
#endif

using namespace std;

void clear()
{
    if(!WINDOWS_OS)
    {
        if(!cur_term)
        {
            int results;
            setupterm(NULL,STDOUT_FILENO,&results);
            if(results <= 0) return;
        }
        putp(tigetstr("clear"));
    }
    #ifdef _WIN32 || _WIN64
        system("clear");
    #endif
}

void pause()
{
    if(!WINDOWS_OS)
    {
        system("read -n 1 -s -p \"Press any key to continue\"");
    }
    #ifdef _WIN32 || _WIN64
        system("pause");
    #endif
}

void writeToFile(account x)
{
    ifstream in("database.txt");
    vector<account> all;
    account aux;
    while(in>>aux.code>>aux.name>>aux.surname>>aux.balance)
    {
        all.push_back(aux);
    }
    all.push_back(x);
    in.close();
    for(vector<account>::size_type i = 0; i != all.size() - 1;i++)
    {
        for(vector<account>::size_type j = i + 1; j != all.size(); j++)
        {
            if(all[i].code > all[j].code)
            {
                swap(all[i],all[j]);
            }
        }
    }
    ofstream out("database.txt");
    for(vector<account>::size_type i = 0; i != all.size(); i++)
    {
        out<<all[i].code<<" "<<all[i].name<<" "<<all[i].surname<<" "<<all[i].balance<<endl;
    }
    out.close();
}