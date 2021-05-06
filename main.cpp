#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include "encrypt.h"
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

int m_code = 0, sel_user = 0;
bool ok = false;

struct cred
{
    string password = "";
    int code = 0;
};

void clear()
{
#ifdef __APPLE__
    if (!cur_term)
    {
        int results;
        setupterm(NULL, STDOUT_FILENO, &results);
        if (results <= 0) return;
    }
    putp(tigetstr("clear"));
#endif
#ifdef _WIN32 || _WIN64
    system("clear");
#endif
}

void pause()
{
#ifdef __APPLE__
    system("read -n 1 -s -p \"Press any key to continue\"");
#endif
#ifdef _WIN32 || _WIN64
    system("pause");
#endif
}

class account
{
public:
    float balance = 0.0f;
    std::string name = "", surname = "";
    int code = 0;
    void printBal() { clear(); cout << "The account balance is : " << balance << endl; }
};

account select_account(int x)
{
    account aux;
    ifstream in("database.txt");
    while (in >> aux.code >> aux.name >> aux.surname >> aux.balance)
    {
        if (aux.code == x) break;
    }
    return aux;
}

void writeToFile(account x)
{
    ifstream in("database.txt");
    vector<account> all;
    account aux;
    while (in >> aux.code >> aux.name >> aux.surname >> aux.balance)
    {
        all.push_back(aux);
    }
    all.push_back(x);
    in.close();
    for (vector<account>::size_type i = 0; i != all.size() - 1; i++)
    {
        for (vector<account>::size_type j = i + 1; j != all.size(); j++)
        {
            if (all[i].code > all[j].code)
            {
                swap(all[i], all[j]);
            }
        }
    }
    ofstream out("database.txt");
    for (vector<account>::size_type i = 0; i != all.size(); i++)
    {
        out << all[i].code << " " << all[i].name << " " << all[i].surname << " " << all[i].balance << endl;
    }
    out.close();
}

bool login()
{
    string name, surname, name_c, surname_c;
    cred a, c;
    ifstream in("accounts.txt");
    clear();
    cout << "LOGIN SCREEN\n";
    cout << "USER NAME : "; cin >> name;
    cout << "USER SURNAME : "; cin >> surname;
    cout << "PASSWORD : "; cin >> a.password;
    bool found = false;
    while (in >> c.code >> name_c >> surname_c >> c.password)
    {
        if (name_c == name && surname_c == surname) {
            found = true;
            break;
        }
    }
    if (found) {
        SHA256 sha;
        sha.update(a.password);
        uint8_t* digest = sha.digest();
        string aux = SHA256::toString(digest);

        in.close();
        delete[] digest;
        if (aux == c.password) {
            sel_user = c.code;
            cout << "LOGIN SUCCESSFULL\n";
            pause();
            return true;
        }
        cout << "FAILED ATTEMPT TO LOGIN\n";
        pause();
        return false;
    }
    else
    {
        cout << "USER NAME OR SURNAME INCORRECT\n";
        return false;
    }
}

void create_user()
{
    clear();
    ifstream in("accounts.txt");
    cred aux;
    account aux1;
    string name,surname,password;
    vector<cred> a;
    while (in >> aux.code >> aux.password)
    {
        a.push_back(aux);
        m_code = aux.code;
    }
    in.close();
    cout << "REGISTER SCREEN\n";
    cout << "NAME : "; cin >> name;
    cout << "SURNAME :"; cin >> surname;
    cout << "PASSWORD : "; cin >> aux.password;
    cout << "REPEAT THE PASSWORD : "; cin >> password;
    aux1.name = name;
    aux1.surname = surname;
    aux1.balance = 0;
    if (password == aux.password)
    {
        m_code++;
        aux.code = m_code;
        aux1.code = aux.code;
        //Password Handle
        SHA256 sha;
        sha.update(aux.password);
        uint8_t* digest = sha.digest();
        string aux2 = SHA256::toString(digest);
        delete[] digest;
        aux.password = aux2;

        a.push_back(aux);
        ofstream out("accounts.txt");
        for (vector<cred>::size_type i = 0; i != a.size() - 1; i++)
        {
            for (vector<cred>::size_type j = i + 1; j != a.size(); j++)
            {
                if (a[i].code > a[j].code)
                {
                    swap(a[i],a[j]);
                }
            }
        }
        for (vector<cred>::size_type i = 0; i != a.size(); i++)
            out << a[i].code << " " << a[i].password << endl;
        out.close();
        writeToFile(aux1);
        cout << "USER REGISTERED SUCCESFULLY. YOU CAN NOW LOGIN\n";
        pause();
    }
    else cout << "PASSWORDS MUST BE THE SAME\n";

}

void loop()
{
    account selected = select_account(sel_user);
    while (ok)
    {
        clear();
        cout << "USER MENU\n";
        cout << "1. View balance\n";
        cout << "2. Deposit balance\n";
        cout << "3. Cash out balance\n";
        cout << "4. Transfer to another account\n";
        cout << "5. Change password\n";
        cout << "6. Logout\n";
        int op = 0;
        cin >> op;
        switch (op)
        {
        case 1:

        }
    }
}

void login_screen()
{
    while (!ok)
    {
        clear();
        int op = 0;
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";
        cin >> op;
        if (op == 1)
        {
            ok = login();
        }
        else if (op == 2)
        {
            create_user();
        }
        else if (op == 3)
        {
            break;
        }
        else
        {
            cout << "INVALID CHOICE\n";
            pause();
            login_screen();
        }
    }
    if(ok)loop();
}

int main()
{
    login_screen();
    return 0;
}