#include "syscomms.h"
#include "encrypt.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool login()
{
    string name,surname,password;
    string name_c,surname_c,password_c;
    ifstream in("accounts.txt");
    clear();
    cout<<"LOGIN SCREEN\n";
    cout<<"USER NAME : "; cin>>name;
    cout<<"USER SURNAME : "; cin>>surname;
    cout<<"PASSWORD : "; cin>>password;
    while(in>>name_c>>surname_c>>password_c)
    {
        if(name_c == name && surname_c == surname)
            break;
    }
    SHA256 sha;
    sha.update(password);
    uint8_t * digest = sha.digest();
    string aux = SHA256::toString(digest);

    in.close();
    delete[] digest;
    if(aux == password_c) return true;
    return false;
}

void create_user()
{
    string name, surname, password;
    cout<<"REGISTER SCREEN";
}