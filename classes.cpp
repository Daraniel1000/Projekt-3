#include"classes.h"

inline bool Y(char x)
{
    return x=='y'||x=='Y';
}
inline bool N(char x)
{
    return x=='n'||x=='N';
}

void cls()
{
    #ifdef __linux__

    system("clear");

    #else

    system("cls");

    #endif
}

void wait()
{
    cout << "\nAby kontynuowac, nacisnij enter...";
    cin.ignore(10000, '\n');
    cin.get();
}

//FUNKCJE COMMONLIST

    void commonlist::next()
    {
        i++;
        if(i>=lsize)
        {
            i=0;
        }
    }
    void commonlist::previous()
    {
        i--;
        if(i<0)
        {
            i=lsize-1;
        }
    }
    bool commonlist::setcur(int ii)
    {
        if(ii<0||ii>=lsize)
            return false;
        i=ii;
        return true;
    }
    int commonlist::size()
    {
        return lsize;
    }

//FUNKCJE BOOKLIST

    void booklist::addbook(bool borrowed, string title, string author, Date data, int id)
    {
        if(freeid.top()<lsize-1)
        {
            book &ref=lib[freeid.top()];
            ref.borrowed=borrowed;
            ref.bookid=freeid.top();
            freeid.pop();
            if(freeid.empty()) freeid.push(++lsize);
            ref.booktitle=title;
            ref.bookauthor=author;
            ref.borrowedto=data;
        }
        else
        {
            book *ptr=new book;
            ptr->borrowed=borrowed;
            if(id==-2)
            {
                ptr->bookid=freeid.top();
            }
            else
            {
                ptr->bookid=id;
            }
            freeid.pop();
            if(freeid.empty()) freeid.push(++lsize);
            ptr->booktitle=title;
            ptr->bookauthor=author;
            ptr->borrowedto=data;
            lib.push_back(*ptr);
            delete ptr;
        }
    }
    void booklist::deletebook(int ii)
    {
        lib[ii].bookid=-1;
        queue<int> q;
        if(ii==lsize-1)
        {
            lib.pop_back();
            lsize--;
            while(lib[lib.size()-1].bookid==-1)
            {
                lib.pop_back();
                lsize--;
            }
            while(!freeid.empty())
            {
                if(freeid.top()<lsize) q.push(freeid.top());
                freeid.pop();
            }
            while(!q.empty()) freeid.push(q.front());
            freeid.push(lsize);
        }
        else
        {
            freeid.push(ii);
        }
    }
    void booklist::deletebook()
    {
        queue<int>q;
        lib[i].bookid=-1;
        if(i==lsize-1)
        {
            lib.pop_back();
            lsize--;
            freeid.pop();
            while(lib[lib.size()-1].bookid==-1)
            {
                lib.pop_back();
                lsize--;
            }
            while(!freeid.empty())
            {
                if(freeid.top()<lsize) q.push(freeid.top());
                freeid.pop();
            }
            while(!q.empty()) freeid.push(q.front());
            freeid.push(lsize);
        }
        else
        {
            freeid.push(i);
        }
        next();
    }
    string booklist::title(int ii)
    {
        return lib[ii].booktitle;
    }
    string booklist::title()
    {
        return lib[i].booktitle;
    }
    string booklist::author(int ii)
    {
        return lib[ii].bookauthor;
    }
    string booklist::author()
    {
        return lib[i].bookauthor;
    }
    bool booklist::isborrowed(int ii)
    {
        return lib[ii].borrowed;
    }
    bool booklist::isborrowed()
    {
        return lib[i].borrowed;
    }
    Date booklist::borrowedto(int ii)
    {
        return lib[ii].borrowedto;
    }
    Date booklist::borrowedto()
    {
        return lib[i].borrowedto;
    }
    int booklist::id(int ii)
    {
        return lib[ii].bookid;
    }
    int booklist::id()
    {
        return lib[i].bookid;
    }
    void booklist::borrow(Date data)
    {
        lib[i].borrowed=1;
        lib[i].borrowedto=data;
    }
    void booklist::returnbook()
    {
        lib[i].borrowed=0;
        Date data(0,0,0);
        lib[i].borrowedto=data;
    }
    void booklist::savebooks()
    {
        fstream fout("ksiazki.txt",fstream::out);
        fout<<lsize<<endl;
        for(int a=0; a<lsize; a++)
        {
            fout<<id(a)<<" "<<isborrowed(a)<<endl
                <<author(a)<<endl
                <<title(a)<<endl
                <<borrowedto(a).day<<" "<<borrowedto(a).month<<" "<<borrowedto(a).year<<endl;
        }
        fout<<freeid.size()-1;
        while(freeid.top()!=lsize)
        {
            fout<<" "<<freeid.top();
            freeid.pop();
        }
        fout.close();
    }
    void booklist::getbooks()
    {
        fstream fin("ksiazki.txt",fstream::in);
        int n,id; stack<int>s;
        bool borrowed;
        Date date;
        string author, title;
        fin>>n;
        for(int a=0; a<n; a++)
        {
            fin>>id>>borrowed>>author;
            fin.ignore(10000,'\n');
            getline(fin,title);
            fin>>date.day>>date.month>>date.year;
            addbook(borrowed,title,author,date,id);
        }
        fin>>n;
        for(int a=0; a<n; a++)
        {
            fin>>id;
            s.push(id);
        }
        while(!s.empty())
        {
            freeid.push(s.top());
            s.pop();
        }
        fin.close();
    }

//FUNKCJE USERLIST

    void userlist::adduser(bool ad, string name, string surname, Date date, string password, set<int>& v, int id)
    {
        if(freeid.top()<lsize-1)
        {
            entity &entref=entlist[freeid.top()];
            entref.userid=freeid.top();
            freeid.pop();
            if(freeid.empty()) freeid.push(++lsize);
            entref.admin=ad;
            entref.name=name;
            entref.surname=surname;
            entref.date=date;
            entref.password=password;
            entref.borrowed=v;
            entlist.push_back(entref);
        }
        else
        {
            entity *entptr=new entity;
            entptr->admin=ad;
            if(id==-2)
            {
                entptr->userid=freeid.top();
            }
            else
            {
                entptr->userid=id;
            }
            freeid.pop();
            if(freeid.empty()) freeid.push(++lsize);
            entptr->name=name;
            entptr->surname=surname;
            entptr->date=date;
            entptr->password=password;
            entptr->borrowed=v;
            entlist.push_back(*entptr);
        }
    }
    void userlist::deleteuser(int ii)
    {
        queue<int>q;
        entlist[ii].userid=-1;
        if(ii==lsize-1)
        {
            entlist.pop_back();
            lsize--;
            freeid.pop();
            while(entlist[entlist.size()-1].userid==-1)
            {
                entlist.pop_back();
                lsize--;
            }
            while(!freeid.empty())
            {
                if(freeid.top()<lsize) q.push(freeid.top());
                freeid.pop();
            }
            while(!q.empty()) freeid.push(q.front());
            freeid.push(lsize);
        }
        else
        {
            freeid.push(ii);
        }
    }
    void userlist::deleteuser()
    {
        queue<int>q;
        entlist[i].userid=-1;
        if(i==lsize-1)
        {
            entlist.pop_back();
            lsize--;
            freeid.pop();
            while(entlist[entlist.size()-1].userid==-1)
            {
                entlist.pop_back();
                lsize--;
            }
            while(!freeid.empty())
            {
                if(freeid.top()<lsize) q.push(freeid.top());
                freeid.pop();
            }
            while(!q.empty()) freeid.push(q.front());
            freeid.push(lsize);
        }
        else
        {
            freeid.push(i);
        }
    }
    bool userlist::isadmin()
    {
        return entlist[i].admin;
    }
    bool userlist::isadmin(int ii)
    {
        return entlist[ii].admin;
    }
    string userlist::name(int ii)
    {
        return entlist[ii].name;
    }
    string userlist::name()
    {
        return entlist[i].name;
    }
    string userlist::surname(int ii)
    {
        return entlist[ii].surname;
    }
    string userlist::surname()
    {
        return entlist[i].surname;
    }
    string userlist::password(int ii)
    {
        return entlist[ii].password;
    }
    string userlist::password()
    {
        return entlist[i].password;
    }
    Date userlist::birthdate(int ii)
    {
        return entlist[ii].date;
    }
    Date userlist::birthdate()
    {
        return entlist[i].date;
    }
    void userlist::borrow(int n, int i)
    {
        entlist[i].borrowed.insert(n);
    }
    int userlist::id(int ii)
    {
        return entlist[ii].userid;
    }
    int userlist::id()
    {
        return entlist[i].userid;
    }
    bool userlist::wrongid(int ii)
    {
        return ii<1||ii>=size()||id(ii)==-1;
    }
    bool userlist::hasbook(int n, int i)
    {
        return entlist[i].borrowed.count(n);
    }
    void userlist::returnbook(int n, int i)
    {
        entlist[i].borrowed.erase(n);
    }
    void userlist::getusers()
    {
        fstream fin("ludzie.txt",fstream::in);
        int n,x,y,id; set<int> v;
        stack<int>s;
        bool admin;
        string name,surname,password;
        Date date;
        fin>>n;
        for(int a=0; a<n; a++)
        {
            fin>>id>>admin>>name>>surname>>date.day>>date.month>>date.year;
            fin>>password;
            fin>>x;
            for(int b=0; b<x; b++)
            {
                fin>>y; v.insert(y);
            }
            adduser(admin,name,surname,date,password,v,id);
        }
        fin>>n;
        for(int a=0; a<n; a++)
        {
            fin>>id;
            s.push(id);
        }
        while(!s.empty())
        {
            freeid.push(s.top());
            s.pop();
        }
        fin.close();
    }
    void userlist::saveusers()
    {
        fstream fout("ludzie.txt",fstream::out);
        fout<<lsize<<endl;
        for(int a=0; a<lsize; a++)
        {
            fout<<id(a)<<" "<<isadmin(a)<<" "<<name(a)<<endl
                <<surname(a)<<endl
                <<birthdate(a).day<<" "<<birthdate(a).month<<" "<<birthdate(a).year<<" "<<password(a)<<endl
                <<borrowed(a)<<endl;
        }
        fout<<freeid.size()-1;
        while(freeid.top()!=lsize)
        {
            fout<<" "<<freeid.top();
            freeid.pop();
        }
        fout.close();
    }
//FUNKCJE USERMENU

    void usermenu::userstart()
{
    int n;
    while(true)
    {
        n=0;
        cls();
        cout<<"Menu:"<<endl
            <<"1. Przeszukaj ksiazki"<<endl
            <<"2. Zakoncz dzialanie"<<endl;
        while(!(n>0&&n<3))cin>>n;
        switch(n)
        {
        case 1:
            booksearch();
            break;
        case 2:
            return;
        }
    }
}

void usermenu::booksearch()
{
    cls();
    int n=0,i;
    Date data;
    string s;
    cout<<"1. Wyszukaj ksiazke po nazwisku autora"<<endl
        <<"2. Wyszukaj ksiazke po tytule"<<endl
        <<"3. Przegladaj katalog ksiazek po id"<<endl
        <<"4. Anuluj"<<endl;
    while(!(n>0&&n<5))cin>>n;
    switch(n)
    {
    case 1:
        cls();
        cout<<"Podaj nazwisko autora: ";
        cin>>s;
        cout<<"id  | Tytul  |  Nazwisko"<<endl;
        for(i=0; i<bl.size(); i++)
        {
            if(bl.author(i).find(s)!=string::npos&&bl.id(i)!=-1)
            {
                cout<<i<<" | "<<bl.title(i)<<" | "<<bl.author(i)<<" |";
                if(bl.isborrowed(i))
                {
                    data=bl.borrowedto(i);
                    cout<<" wypozyczona do "<<data.day<<"."<<data.month<<"."<<data.year<<endl;
                }
                else
                {
                    cout<<" niewypozyczona"<<endl;
                }
            }
        }
        wait();
        break;
    case 2:
        cls();
        cout<<"Podaj tytul ksiazki: ";
        cin>>s;
        cout<<"id |  Tytul  |  Nazwisko"<<endl;
        for(i=0; i<bl.size(); i++)
        {
            if(bl.title(i).find(s)!=string::npos&&bl.id(i)!=-1)
            {
                cout<<i<<" | "<<bl.title(i)<<" | "<<bl.author(i)<<" |";
                if(bl.isborrowed(i))
                {
                    data=bl.borrowedto(i);
                    cout<<" wypozyczona do "<<data.day<<"."<<data.month<<"."<<data.year<<endl;
                }
                else
                {
                    cout<<" niewypozyczona"<<endl;
                }
            }
        }
        wait();
        break;
    case 3:
        cls();
        bl.setcur(0);
        i=0;
        cout<<"id |  Tytul  |  Nazwisko"<<endl;
        while(true)
        {
            n=0;
            while(bl.id()==-1) bl.next();
            cout<<bl.id()<<" | "<<bl.title()<<" | "<<bl.author()<<" |";
            if(bl.isborrowed())
            {
                data=bl.borrowedto();
                cout<<" wypozyczona do "<<data.day<<"."<<data.month<<"."<<data.year<<endl;
            }
            else
            {
                cout<<" niewypozyczona"<<endl;
            }
            cout<<"1. Nastepna ksiazka\n2. Wyjdz"<<endl;
            while(!(n>0&&n<3))cin>>n;
            if(n==1) bl.next();
            else break;
        }
        break;
    case 4:
        return;
    }
}

//FUNKCJE ADMINMENU

    void adminmenu::start()
    {
        bl.getbooks();
        ul.getusers();
        while(!login());
        if (!ul.isadmin())
        {
            userstart();
        }
        else
        {
            adminstart();
        }
        bl.savebooks();
        ul.saveusers();
    }
bool adminmenu::login()
{
    int n;
    cout<<"Aby zalogowac sie, wybierz 1.\nAby kontynuowac jako gosc, wybierz 2.\n";
    do
    {
        n=cin.get()-'0';
        cin.ignore(10000,'\n');
    } while(n<1||n>2);
    if(n==2)
    {
        ul.setcur(0);
        return 1;
    }
    cout<<"Podaj id: ";
    n=cin.get()-'0';
    //cin.ignore(10000,'\n');
    if(!ul.setcur(n)||n==0)
    {
        cout<<"Blad: niewlasciwe id!"<<endl;
        wait();
        return 0;
    }
    cout<<"Podaj haslo: ";
    string s;
    cin>>s;
    cin.ignore(10000,'\n');
    if(s==ul.password())
    {
        return 1;
    }
    cout<<"Blad: zle haslo!"<<endl;
    wait();
    return 0;
}
void adminmenu::adminstart()
{
    int n,i;
    while(true)
    {
        n=0;
        cls();
        cout<<"Menu:"<<endl
            <<"1. Przeszukaj ksiazki"<<endl
            <<"2. Przeszukaj uzytkownikow"<<endl
            <<"3. Wypozycz ksiazke"<<endl
            <<"4. Oddaj ksiazke"<<endl
            <<"5. Dodaj uzytkownika"<<endl
            <<"6. Dodaj ksiazke"<<endl
            <<"7. Usun ksiazke"<<endl
            <<"8. Usun uzytkownika"<<endl
            <<"9. Zakoncz dzialanie"<<endl;
        while(!(n>0&&n<10))cin>>n;
        switch(n)
        {
        case 1:
            booksearch();
            break;
        case 2:
            usersearch();
            break;
        case 3:
            borrowbook();
            break;
        case 4:
            returnbook();
            break;
        case 5:
            adduser();
            break;
        case 6:
            addbook();
            break;
        case 7:
            cls();
            cout<<"Podaj id ksiazki do usuniecia: ";
            cin>>i;
            if(!bl.setcur(i))
            {
                cout<<"Blad: niewlasciwe id!"<<endl;
                wait();
                break;
            }
            bl.deletebook();
            break;
        case 8:
            cls();
            cout<<"Podaj id uzytkownika do usuniecia: ";
            cin>>i;
            if(ul.wrongid(i))
            {
                cout<<"Blad: niewlasciwe id!"<<endl;
                wait();
                break;
            }
            ul.deleteuser(i);
            break;
        case 9:
            return;
        }
    }
}
void adminmenu::borrowbook()
{
    int n,i;
    Date data;
    cls();
    cout<<"Podaj id ksiazki: ";
    cin>>n;
    if(!bl.setcur(n)||bl.id()==-1)
    {
        cout<<"Blad: niewlasciwe id!"<<endl;
        wait();
        return;
    }
    if(bl.isborrowed())
    {
        cout<<"Blad: ksiazka juz wypozyczona."<<endl;
        wait();
        return;
    }
    cout<<"Podaj id wypozyczajacego: ";
    cin>>i;
    if(ul.wrongid(i))
    {
        cout<<"Blad: niewlasciwe id!";
        wait();
        return;
    }
    cout<<"Podaj date do oddania: DD MM YYYY\n";
    cin>>data.day>>data.month>>data.year;
    bl.borrow(data);
    ul.borrow(n,i);
}
void adminmenu::returnbook()
{
    int n,i;
    Date data;
    cls();
    cout<<"Podaj id wypozyczajacego: ";
    cin>>i;
    if(ul.wrongid(i))
    {
        cout<<"Blad: niewlasciwe id!";
        wait();
        return;
    }
    cout<<"Podaj id ksiazki: ";
    cin>>n;
    if(!bl.setcur(n)||bl.id()==-1)
    {
        cout<<"Blad: niewlasciwe id!"<<endl;
        wait();
        return;
    }
    if(!bl.isborrowed()||!ul.hasbook(n,i))
    {
        cout<<"Blad: ksiazka nie jest wypozyczona przez ta osobe!"<<endl;
        wait();
        return;
    }
    data=bl.borrowedto();
    cout<<"Ksiazka wypozyczona do "<<data.day<<". "<<data.month<<". "<<data.year<<endl;
    bl.returnbook();
    ul.returnbook(n,i);
    wait();
}
void adminmenu::adduser()
{
    set<int> v;
    bool admin;
    string name,surname,password;
    Date date;
    char c=0;
    cls();
    cout<<"Czy uzytkownik jest administratorem systemu? Y/N"<<endl;
    while(!(Y(c)||N(c)))cin>>c;
    if(Y(c))admin=true;
    else admin=false;
    cout<<"Podaj imie i nazwisko uzytkownika: ";
    cin>>name>>surname;
    cout<<"Podaj date urodzenia: DD MM YYYY"<<endl;
    cin>>date.day>>date.month>>date.year;
    cout<<"Podaj haslo uzytkownika: ";
    cin>>password;
    ul.adduser(admin,name,surname,date,password,v);
}
void adminmenu::addbook()
{
    cls();
    Date date(0,0,0);
    string author, title;
    cout<<"Podaj nazwisko autora: ";
    cin>>author;
    cout<<"Podaj tytu³ ksiazki: ";
    cin.ignore();
    getline(cin,title);
    bl.addbook(0,title,author,date);
}
void adminmenu::usersearch()
{
    cls();
    int n=0,i;
    Date data;
    string s;
    cout<<"1. Wyszukaj uzytkownika po nazwisku"<<endl
        <<"2. Wyszukaj uzytkownika po imieniu"<<endl
        <<"3. Przegladaj liste uzytkownikow po id"<<endl
        <<"4. Anuluj"<<endl;
    while(!(n>0&&n<5))cin>>n;
    switch(n)
    {
    case 1:
        cls();
        cout<<"Podaj nazwisko: ";
        cin>>s;
        cout<<"id  | Imie |  Nazwisko"<<endl;
        for(i=1; i<ul.size(); i++)
        {
            if(ul.surname(i).find(s)!=string::npos&&ul.id(i)!=-1)
            {
                cout<<i<<" | "<<ul.name(i)<<" | "<<ul.surname(i)<<endl;
            }
        }
        wait();
        break;
    case 2:
        cls();
        cout<<"Podaj imie: ";
        cin>>s;
        cout<<"id |  Imie  |  Nazwisko"<<endl;
        for(i=1; i<ul.size(); i++)
        {
            if(ul.name(i).find(s)!=string::npos&&ul.id(i)!=-1)
            {
                cout<<i<<" | "<<ul.name(i)<<" | "<<ul.surname(i)<<endl;
            }
        }
        wait();
        break;
    case 3:
        cls();
        i=1;
        cout<<"id |  Imie  |  Nazwisko"<<endl;
        while(true)
        {
            n=0;
            while(ul.id(i)==-1&&i<ul.size()) i++;
            if(i==ul.size())i=1;
            cout<<i<<" | "<<ul.name(i)<<" | "<<ul.surname(i)<<endl;
            cout<<"1. Nastepny uzytkownik\n2. Wyjdz"<<endl;
            while(!(n>0&&n<3))cin>>n;
            if(n==1) i++;
            else break;
        }
        break;
    case 4:
        return;
    }
}
