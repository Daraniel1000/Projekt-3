#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<set>
#include<fstream>
#include<cstdlib>
#include<regex>
#include<stack>
using namespace std;

struct Date     //DO PRZECHOWYWANIA DATY
    {
        Date(int d=0,int m=0,int y=0): day(d), month(m), year(y){};
        int day;
        int month;
        int year;
    };

class commonlist    //WSPOLNE CZESCI KLAS DO OBSLUGI LISTY UZYTKOWNIKOW I KSIAZEK
{
protected:
    int lsize=0,i;
    priority_queue<int, vector<int>, greater<int> >freeid;
public:
    void next();
    void previous();
    bool setcur(int);
    int size();
};

class booklist: public commonlist   //KLASA OBSLUGUJACA LISTE KSIAZEK
{
private:
    struct book
    {
        bool borrowed;
        int bookid;
        string booktitle;
        string bookauthor;
        Date borrowedto;
    };
    vector<book> lib;
public:
    booklist(){freeid.push(0);}
    void addbook(bool, string, string, Date, int=-2);
    void deletebook(int);
    void deletebook();
    string title(int);
    string title();
    string author(int);
    string author();
    bool isborrowed(int);
    bool isborrowed();
    Date borrowedto(int);
    Date borrowedto();
    int id(int);
    int id();
    void borrow(Date);
    void returnbook();
    void savebooks();
    void getbooks();
};

class userlist : public commonlist      //KLASA OBSLUGUJACA LISTE UZYTKOWNIKOW
{
private:
    struct entity
    {
        int userid;
        string name;
        string surname;
        Date date;
        string password;
        set<int> borrowed;
        bool admin;
    };
    vector<entity>entlist;
public:
    userlist(){freeid.push(0);}
    void adduser(bool, string, string, Date, string, set<int>&,int=-2);
    void deleteuser(int);
    void deleteuser();
    bool isadmin(int);
    bool isadmin();
    string name(int);
    string name();
    string surname(int);
    string surname();
    string password(int);
    string password();
    Date birthdate(int);
    Date birthdate();
    int id(int);
    int id();
    bool wrongid(int);
    void borrow(int, int);
    bool hasbook(int, int);
    void returnbook(int, int);
    string borrowed(int ii)
    {
        stringstream s;
        s<<entlist[ii].borrowed.size();
        for (set<int>::iterator it=entlist[ii].borrowed.begin(); it!=entlist[ii].borrowed.end(); ++it)
            s<<" "<<*it;
        return s.str();
    }
    void saveusers();
    void getusers();
};

class usermenu
{
protected:
    booklist &bl;
    userlist &ul;
    void booksearch();
public:
    usermenu(booklist& bb, userlist& uu) :bl(bb), ul(uu){};
    void userstart();
};

class adminmenu: protected usermenu
{
protected:
    bool login();
    void adminstart();
    void adduser();
    void addbook();
    void borrowbook();
    void returnbook();
    void usersearch();
public:
    void start();
    adminmenu(booklist& bb, userlist& uu) : usermenu(bb,uu){};
};
