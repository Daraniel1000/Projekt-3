#include<iostream>
#include"classes.h"
using namespace std;






int main()
{
    //fstream bookl("ksiazki.txt",fstream::in|fstream::out),userl("ludzie.txt",fstream::in|fstream::out);
    userlist ul; booklist bl;
    ul.getusers();
    bl.getbooks();
    adminmenu menu(bl,ul);
    menu.start();/*
    while(!login(ul));
    if(ul.isadmin())
    {
        adminmenu(ul,bl);
    }
    else
    {
        usermenu(ul,bl);
    }*/
    ul.saveusers();
    bl.savebooks();
    return 0;
}

