#include <conio.h>
#include<windows.h>
#include<common.h>
#include<admin.h>
#include<customer.h>
#include<mysql.h>
#include<sstream>
#pragma GCC diagnostic ignored "-Wwrite-strings"
#pragma GCC diagnostic ignored "-Wparentheses"
#include<bits/stdc++.h>
#include <graphics.h>
#include <string>
#include <sstream>
using namespace std;

//nicher 4 ta line hochhe global variable
char* ip_address="192.168.0.105";
MYSQL* con;
MYSQL_ROW row;
MYSQL_RES* res;

void intro_select(int val) //Text gula toggling er shomoy boro korbe
{
    switch(val)
    {
    case 1:
        settextstyle(9,0,4);
        setcolor(LIGHTCYAN);
        outtextxy(360,260," Admin ");
        settextstyle(9,0,2);
        outtextxy(330,265,">>");
        break;
    case 2:
        settextstyle(9,0,4);
        setcolor(LIGHTCYAN);
        outtextxy(410,350," Customer ");
        settextstyle(9,0,2);
        outtextxy(380,355,">>");
        break;
    case 6:
        settextstyle(9,0,2);
        setcolor(LIGHTCYAN);
        outtextxy(80,228,"         Create New Account   ");
        settextstyle(9,0,1);
        outtextxy(95,230,">>");
        break;
    case 8:
        settextstyle(9,0,2);
        setcolor(LIGHTCYAN);
        outtextxy(130,228,"         Create New Account   ");
        settextstyle(9,0,1);
        outtextxy(135,230,">>");
        break;
    }
}
void intro_content()
{
    settextstyle(9,0,3);
    setcolor(LIGHTCYAN);
    outtextxy(330,262,"      Admin     ");
    outtextxy(380,355,"      Customer     ");
}

void intro_toggling()//upore niche move korbe
{
    char ch;
    static int count=1;
    intro_content();
    intro_select(count);
    do
    {
        ch=getch();
        switch(ch)
        {
        case 72://upore uthbe
            count--;
            if(count==0)
            {
                count=2;
            }
            intro_content();
            intro_select(count);
            continue;
        case 80://niche nambe
            count++;
            if(count==3)
            {
                count=1;
            }
            intro_content();
            intro_select(count);
            continue;
        case 13://enter press korbe
            break;
        }
    }
    while(ch!=13);

    common *com;

    switch(count)
    {
    case 1:
        {
            com=new admin();
            closegraph();
            com->first_window();
            delete[] com;
            break;
        }

    case 2:
        {
            com=new customer();
            closegraph();
            com->first_window();
            delete[] com;
            break;
        }

    }
}


void intro()
{
    initwindow(1000,700);

    readimagefile("image_login.jpg", 0, 0, 1000, 700);

    intro_content();
    intro_toggling();

    getch();
    closegraph();
}



int main()
{
    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);//amar laptop er IP address, localhost user account er naam, oi user account er password, database er naam, baki value gula default

    if(!con)
    {
        cout<<"Not Connected !!"<<endl;
    }
    else
    {
        cout<<"Connected !!"<<endl;
        intro();
    }
    return 0;
}
