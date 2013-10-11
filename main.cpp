/*
 * A0118400X
 * Shen Juanli
 * for CS3230 PJ2 @NUS
 * 2013.10
 *
 */
 
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include "RBT.h"

using namespace std;

int main()
{
    freopen("in.txt", "r", stdin);

    RBT* PhoneBook = new RBT();

    int n;
    cin >> n;

    string line;
    stringstream ss;
    getline(cin, line); // eat the rest of 1st line

    string option;
    KeyType name = "";
    TelType tel = "";

    while(n--)
    {
        getline(cin, line);
        ss.clear();
        ss << line;
        ss >> option >> name >> tel;

        // cout << "current action\t" << line << endl;

        switch(option[0])
        {
            case 'H': cout << "H=" << PhoneBook->Height() << endl; break;
            case 'S': cout << PhoneBook->Search(name) << endl; break;
            case 'I': PhoneBook->Insert(name, tel); break;
            case 'D': PhoneBook->Delete(name); break;

            default: break;
        }

        // PhoneBook->CheckBalance();
        // cout <<"option is ["<<option<<"] name is ["<<name<<"] and tel is ["<<tel<<"]"<<endl;
        // PhoneBook->Print();
    }

    return 0;
}
