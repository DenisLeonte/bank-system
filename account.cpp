#include "syscomms.h"
#include "account.h"
#include <iostream>

using namespace std;

void account::input()
{
    account aux;
    cout<<"NEW ACCOUNT CREATION TOOL\n";
    cout<<"NAME : "; cin>>aux.name;
    cout<<"SURNAME : "; cin>>aux.surname;
    cout<<"INITIAL BALANCE : "; cin>>aux.balance;
    aux.code = m_code + 1;
    m_code++;
    writeToFile();
}