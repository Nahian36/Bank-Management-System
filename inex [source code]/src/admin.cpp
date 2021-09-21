#include "admin.h"
#include <graphics.h>
#include <conio.h>
#include<windows.h>
#include<mysql.h>
#include<sstream>
#include<customer.h>
#pragma GCC diagnostic ignored "-Wwrite-strings"
#pragma GCC diagnostic ignored "-Wparentheses"
#include<bits/stdc++.h>
#include <string>
#include <sstream>

using namespace std;
extern char* ip_address;
extern MYSQL* con;
extern MYSQL_ROW row;
extern MYSQL_RES* res;
void intro();
void intro_select(int);
void intro_content();
void intro_toggling();

//static variable initialize hochhe ekhane
int admin::count_pass=0;
int admin::count_login=0;
int admin::counter=1;
int admin::delete_opt=1;

void admin::first_window()
{
    initwindow(800,400);

    readimagefile("passcode.jpg", 0, 0, 800, 400);

    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    settextstyle(9,0,3);
    setcolor(WHITE);
    outtextxy(280,50,"      Admin     ");

    setcolor(LIGHTBLUE);
    settextstyle(8,0,4);
    outtextxy(100,170,"PASSCODE: ");

    char pass_temp[20], chrctr;
    int i=0, j, star_gap=0, cursor_gap=20;

    string pass="";

    setcolor(0);
    settextstyle(8,0,3);
    outtextxy(320,176," ");
    setcolor(15);
    line(322,195,332,195);

    while(1)
    {
        chrctr=getch();
        if(chrctr=='\r')//enter press korse
            break;
        else if(chrctr==27)
        {
            closegraph();
            intro();
        }
        else if(chrctr==9)
        {
            closegraph();
            first_window();
        }
        else if(chrctr==8 && i==0)
        {
            setcolor(0);
            settextstyle(8,0,3);
            outtextxy(320,176," ");
            setcolor(15);
            line(322,195,332,195);
        }
        else if(chrctr==8 && i>0)
        {
            i--;
            setcolor(15);
            settextstyle(8,0,3);
            star_gap-=20;
            outtextxy(320+star_gap,176," ");
            cursor_gap-=20;
            setcolor(0);
            line(322+cursor_gap,195,332+cursor_gap,195);
            cursor_gap-=20;
            setcolor(15);
            line(322+cursor_gap,195,332+cursor_gap,195);
            cursor_gap+=20;
        }
        else
        {
            pass_temp[i]=chrctr;//character array te nitesi
            setcolor(15);
            settextstyle(8,0,3);
            outtextxy(320+star_gap,176,"*");
            i++;
            star_gap+=20;//ak star theke next star er gap
            line(322+cursor_gap,195,332+cursor_gap,195);
            cursor_gap+=20;
        }
    }
    pass_temp[i]='\0';

    for(j=0; j<i; j++) //character array theke string e nitesi
    {
        pass=pass+pass_temp[j];
    }

    int state=0;
    state=mysql_query(con, select_pass);//"SELECT passcode FROM passcode WHERE serial=1"
    if(!state)
    {
        res=mysql_store_result(con);
        row=mysql_fetch_row(res);
        if(pass==row[0])//user input dewa passcode er sthe original passcode er comparison
        {
            settextstyle(8,0,1);
            outtextxy(200,240,"Password Accepted !!!!!");
            getch();
            closegraph();
            admin_login();
        }
        else
        {
            settextstyle(8,0,1);
            outtextxy(200,240,"Password Incorrect !!!!!");

            getch();
            closegraph();
            count_pass++;
            if(count_pass<3)
            {
                first_window(); //at least 3 bar chance pabe passcode input dewar
            }
            else
            {
                count_pass=0;
                intro();
            }
        }
    }
}

void admin::admin_login()
{
    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    initwindow(600,400);

    readimagefile("admin_login.jpg", 0, 0, 600, 400);

    settextstyle(9,0,3);
    setcolor(LIGHTCYAN);
    outtextxy(140,50,"      Admin Login     ");

    settextstyle(9,0,2);
    setcolor(LIGHTBLUE);
    outtextxy(140,100,"Username: ");

    settextstyle(9,0,1);
    setcolor(LIGHTCYAN);
    outtextxy(80,230,"          Create New Account            ");

    //new account create korar jonno

    char ch;
    int c=5;

    do
    {
        ch=getch();
        switch(ch)
        {
        case 72://upore uthbe
            c--;
            if(c<5)
            {
                c=6;
            }
            settextstyle(9,0,1);
            setcolor(LIGHTCYAN);
            outtextxy(80,230,"          Create New Account            ");
            intro_select(c);
            continue;
        case 80://niche nambe
            c++;
            if(c>6)
            {
                c=5;
            }
            settextstyle(9,0,1);
            setcolor(LIGHTCYAN);
            outtextxy(80,230,"          Create New Account            ");
            intro_select(c);
            continue;
        case 13://enter press korbe
            break;
        }
    }
    while(ch!=13);

    if(c==6)
    {
        closegraph();
        admin_create_new();
    }

    //admin_username er jonno

    char chrctr,str[3],username_temp[30];
    int c_gap=0,i=0,j;
    stringstream s;
    string admin_username="";

    setcolor(0);
    settextstyle(8,0,2);
    outtextxy(290,100," ");

    while(1)
    {
        chrctr=getch();
        if(chrctr=='\r')//enter press korse
            break;
        else if(chrctr==27)
        {
            closegraph();
            first_window();
        }
        else if(chrctr==9)
        {
            closegraph();
            admin_login();
        }
        else if(chrctr==8 && i==0)
        {
            setcolor(0);
            settextstyle(8,0,2);
            outtextxy(290,100," ");
        }
        else if(chrctr==8 && i>0)
        {
            i--;
            setcolor(15);
            settextstyle(8,0,2);
            c_gap-=12;
            outtextxy(290+c_gap,100," ");
        }
        else
        {
            username_temp[i]=chrctr;//character array te nitesi
            sprintf(str,"%c",chrctr);
            setcolor(15);
            settextstyle(8,0,2);
            outtextxy(290+c_gap,100,str);
            i++;
            c_gap+=12;//ak character theke next character er gap
        }
    }
    username_temp[i]='\0';
    for(j=0; j<i; j++) //character array theke string e nitesi
    {
        admin_username=admin_username+username_temp[j];
    }

    int state=0;
    state=mysql_query(con, select_admin_name);//"SELECT admin_name FROM admin_login"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(row[0]==admin_username)
            {
                closegraph();
                admin_login_pass(admin_username);
            }
        }
        settextstyle(8,0,1);
        outtextxy(160,260,"Invalid Username !!");

        getch();
        closegraph();
        count_login++;
        if(count_login<3)
        {
            admin_login(); //at least 3 bar chance pabe admin_username r password dui tai thik moto input dewar jonno
        }
        else
        {
            count_login=0;
            intro();
        }
    }
    settextstyle(8,0,1);
    outtextxy(200,240,"Database Error !!");

    getch();
    count_login++;
    if(count_login<3)
    {
        admin_login(); //at least 3 bar chance pabe admin_username r password dui tai thik moto input dewar jonno
    }
    else
    {
        count_login=0;
        intro();
    }
}

void admin::admin_login_pass(string admin_username)
{
    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    initwindow(600,400);

    readimagefile("admin_login.jpg", 0, 0, 600, 400);

    setcolor(LIGHTBLUE);
    settextstyle(9,0,2);
    outtextxy(140,160,"Password: ");

    //admin er password er jonno

    char chrctr;
    int star_gap=0,i=0,j=0;
    static int count_loginnn=0;
    string admin_password="";

    setcolor(0);
    settextstyle(8,0,3);
    outtextxy(290,160," ");

    while(1)
    {
       chrctr=getch();
        if(chrctr=='\r')//enter press korse
            break;
        else if(chrctr==27)
        {
            closegraph();
            admin_login();
        }
        else if(chrctr==9)
        {
            closegraph();
            admin_login_pass(admin_username);
        }
        else if(chrctr==8 && i==0)
        {
            setcolor(0);
            settextstyle(8,0,3);
            outtextxy(290,160," ");
        }
        else if(chrctr==8 && i>0)
        {
            i--;
            setcolor(15);
            settextstyle(8,0,3);
            star_gap-=20;
            outtextxy(290+star_gap,160," ");
        }
        else
        {
            admin_password_temp[i]=chrctr;//character array te nitesi
            setcolor(15);
            settextstyle(8,0,3);
            outtextxy(290+star_gap,160,"*");
            i++;
            star_gap+=20;//ak star theke next star er gap
        }
    }
    admin_password_temp[i]='\0';
    for(j=0; j<i; j++) //character array theke string e nitesi
    {
        admin_password=admin_password+admin_password_temp[j];
    }

    int state=0;
    state=mysql_query(con, select_admin_name_and_pass);//"SELECT admin_name,admin_password FROM admin_login"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(row[0]==admin_username)
            {
                if(row[1]==admin_password)
                {
                    closegraph();
                    count_loginnn=0;
                    loading();
                    admin_menu();
                }
                else
                {
                    settextstyle(8,0,1);
                    outtextxy(160,260,"Password Incorrect !!");

                    getch();
                    closegraph();
                    count_loginnn++;
                    if(count_loginnn<3)
                    {
                        admin_login_pass(admin_username); //at least 3 bar chance pabe admin_username r password dui tai thik moto input dewar jonno
                    }
                    else
                    {
                        count_loginnn=0;
                        admin_login();
                    }
                }
            }
        }
    }
    settextstyle(8,0,1);
    outtextxy(200,240,"Database Error !!");

    getch();
    count_loginnn++;
    if(count_loginnn<3)
    {
        admin_login_pass(admin_username); //at least 3 bar chance pabe admin_username r password dui tai thik moto input dewar jonno
    }
    else
    {
        count_loginnn=0;
        admin_login();
    }
}


void admin::admin_create_new()
{
    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    admin_user();
}



void admin::admin_user()
{
    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    initwindow(800,400);

    readimagefile("admin_login.jpg", 0, 0, 800, 400);

    settextstyle(9,0,3);
    setcolor(LIGHTCYAN);
    outtextxy(140,50,"      Create Account     ");

    //admin_username er jonno
    settextstyle(9,0,2);
    setcolor(LIGHTBLUE);
    outtextxy(140,100,"Username: ");

    char chrctr,str[3],username_temp[30];
    int c_gap=0,i=0,j;
    stringstream s;
    string admin_username="";

    setcolor(0);
    settextstyle(8,0,2);
    outtextxy(290,100," ");

    while(1)
    {
        chrctr=getch();
        if(chrctr=='\r')//enter press korse
            break;
        else if(chrctr==27)
        {
            closegraph();
            admin_login();
        }
        else if(chrctr==9)
        {
            closegraph();
            admin_user();
        }
        else if(chrctr==8 && i==0)
        {
            setcolor(0);
            settextstyle(8,0,2);
            outtextxy(290,100," ");
        }
        else if(chrctr==8 && i>0)
        {
            i--;
            setcolor(15);
            settextstyle(8,0,2);
            c_gap-=14;
            outtextxy(290+c_gap,100," ");
        }
        else
        {
            username_temp[i]=chrctr;//character array te nitesi
            sprintf(str,"%c",chrctr);
            setcolor(15);
            settextstyle(8,0,2);
            outtextxy(290+c_gap,100,str);
            i++;
            c_gap+=14;//ak character theke next character er gap
        }
    }
    username_temp[i]='\0';
    for(j=0; j<i; j++) //character array theke string e nitesi
    {
        admin_username=admin_username+username_temp[j];
    }

    if(admin_username.size()<4)
    {
        settextstyle(9,0,1);
        setcolor(LIGHTRED);
        outtextxy(150,250,"Username should have at least 4 characters !!");

        getch();
        closegraph();
        admin_user();
    }

    int state=0;
    state=mysql_query(con, select_admin_name);//"SELECT admin_name FROM admin_login"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(row[0]==admin_username)
            {
                outtextxy(200,250,"Username exists.");
                outtextxy(100,280,"Select different Username !!");

                getch();
                closegraph();
                admin_user();
            }
        }
        closegraph();
        admin_pass(admin_username);
    }
    settextstyle(8,0,1);
    outtextxy(200,240,"Database Error !!");

    closegraph();
    admin_user();
}

void admin::admin_pass(string admin_username)
{
    initwindow(800,400);

    readimagefile("passcode.jpg", 0, 0, 800, 400);

    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    //password er jonno
    setcolor(LIGHTBLUE);
    settextstyle(9,0,2);
    outtextxy(140,160,"Password: ");

    char admin_password_temp[20],chrctr;
    int star_gap=0,i=0,j;
    string admin_password="";

    setcolor(0);
    settextstyle(8,0,3);
    outtextxy(290,160," ");

    while(1)
    {
        chrctr=getch();
        if(chrctr=='\r')//enter press korse
            break;
        else if(chrctr==27)
        {
            closegraph();
            admin_login();
        }
        else if(chrctr==9)
        {
            closegraph();
            admin_create_new();
        }
        else if(chrctr==8 && i==0)
        {
            setcolor(0);
            settextstyle(8,0,3);
            outtextxy(290,160," ");
        }
        else if(chrctr==8 && i>0)
        {
            i--;
            setcolor(15);
            settextstyle(8,0,3);
            star_gap-=20;
            outtextxy(290+star_gap,160," ");
        }
        else
        {
            admin_password_temp[i]=chrctr;//character array te nitesi
            setcolor(15);
            settextstyle(8,0,3);
            outtextxy(290+star_gap,160,"*");
            i++;
            star_gap+=20;//ak star theke next star er gap
        }
    }
    admin_password_temp[i]='\0';
    for(j=0; j<i; j++) //character array theke string e nitesi
    {
        admin_password=admin_password+admin_password_temp[j];
    }

    if(admin_password.size()<8)
    {
        settextstyle(9,0,1);
        setcolor(LIGHTRED);
        outtextxy(150,300,"Password should have at least 8 characters !!");

        getch();
        closegraph();
        admin_pass(admin_username);
    }

    //password confirm korar jonno
    setcolor(LIGHTBLUE);
    settextstyle(9,0,2);
    outtextxy(140,220,"Confirm Password: ");

    char confirm_password_temp[20];
    star_gap=0;
    i=0;
    string confirm_password="";
    stringstream s;

    setcolor(0);
    settextstyle(8,0,3);
    outtextxy(390,220," ");

    while(1)
    {
        chrctr=getch();
        if(chrctr=='\r')//enter press korse
            break;
        else if(chrctr==27)
        {
            closegraph();
            admin_user();
        }
        else if(chrctr==9)
        {
            closegraph();
            admin_pass(admin_username);
        }
        else if(chrctr==8 && i==0)
        {
            setcolor(0);
            settextstyle(8,0,3);
            outtextxy(390,220," ");
        }
        else if(chrctr==8 && i>0)
        {
            i--;
            setcolor(15);
            settextstyle(8,0,3);
            star_gap-=20;
            outtextxy(390+star_gap,220," ");
        }
        else
        {
            confirm_password_temp[i]=chrctr;//character array te nitesi
            setcolor(15);
            settextstyle(8,0,3);
            outtextxy(390+star_gap,220,"*");
            i++;
            star_gap+=20;//ak star theke next star er gap
        }
    }
    confirm_password_temp[i]='\0';
    for(j=0; j<i; j++) //character array theke string e nitesi
    {
        confirm_password=confirm_password+confirm_password_temp[j];
    }

    if(admin_password==confirm_password)
    {
        s<<"INSERT INTO admin_login VALUES('"<<admin_username<<"','"<<admin_password<<"')";
        string query=s.str();
        const char* q=query.c_str();
        int state=0;
        state=mysql_query(con, q);
        if(!state)
        {
            settextstyle(9,0,1);
            setcolor(LIGHTCYAN);
            outtextxy(180,330,"          Account Created !!            ");

            getch();
            closegraph();
            admin_login();
        }
        settextstyle(8,0,1);
        outtextxy(200,240,"Database Error !!");

        getch();
        closegraph();
        admin_pass(admin_username);
    }
    else
    {
        settextstyle(9,0,1);
        setcolor(LIGHTCYAN);
        outtextxy(140,330,"          Password didn't match !!            ");

        getch();
        closegraph();
        admin_pass(admin_username);
    }
}




void admin::admin_menu_select(int val) //Text gula toggling er shomoy boro korbe
{
    switch(val)
    {
    case 1:
        settextstyle(9,0,3);
        setcolor(CYAN);
        outtextxy(110,130,"1. Search Specific Customer  ");
        settextstyle(9,0,2);
        outtextxy(75,130,">>");
        break;
    case 2:
        settextstyle(9,0,3);
        setcolor(CYAN);
        outtextxy(150,180,"2. Search Specific Information  ");
        settextstyle(9,0,2);
        outtextxy(115,180,">>");
        break;
    case 3:
        settextstyle(9,0,3);
        setcolor(CYAN);
        outtextxy(190,230,"3. Delete Any Account  ");
        settextstyle(9,0,2);
        outtextxy(155,230,">>");
        break;
    case 4:
        settextstyle(9,0,3);
        setcolor(CYAN);
        outtextxy(230,280,"4. Deletion Requests or Deleted Accounts ");
        settextstyle(9,0,2);
        outtextxy(195,280,">>");
        break;
    case 5:
        settextstyle(9,0,3);
        setcolor(CYAN);
        outtextxy(270,330,"5. Update Any Account  ");
        settextstyle(9,0,2);
        outtextxy(235,330,">>");
        break;
    case 6:
        settextstyle(9,0,3);
        setcolor(CYAN);
        outtextxy(310,380,"6. View Personal Information  ");
        settextstyle(9,0,2);
        outtextxy(275,380,">>");
        break;
    case 7:
        settextstyle(9,0,3);
        setcolor(CYAN);
        outtextxy(350,430,"7. View Account Balance      ");
        settextstyle(9,0,2);
        outtextxy(315,430,">>");
        break;
    case 8:
        settextstyle(9,0,3);
        setcolor(CYAN);
        outtextxy(390,480,"8. Log Out      ");
        settextstyle(9,0,2);
        outtextxy(355,480,">>");
        break;
    }
}



void admin::admin_menu_content()
{
    settextstyle(9,0,2);
    setcolor(CYAN);
    outtextxy(75,131,"     1. Search Specific Customer       ");
    outtextxy(115,181,"     2. Search Specific Information        ");
    outtextxy(155,231,"     3. Delete Any Account     ");
    outtextxy(195,281,"     4. Deletion Requests or Deleted Accounts       ");
    outtextxy(235,331,"     5. Update Any Account      ");
    outtextxy(275,381,"     6. View Personal Information     ");
    outtextxy(315,431,"     7. View Account Balance    ");
    outtextxy(355,481,"     8. Log Out      ");
}

void admin::menu_toggling()
{
    char ch;
    admin_menu_content();
    admin_menu_select(counter);
    do
    {
        ch=getch();
        switch(ch)
        {
        case 72://upore uthbe
            counter--;
            if(counter==0)
            {
                counter=8;
            }
            admin_menu_content();
            admin_menu_select(counter);
            continue;
        case 80://niche nambe
            counter++;
            if(counter==9)
            {
                counter=1;
            }
            admin_menu_content();
            admin_menu_select(counter);
            continue;
        case 13://enter press korbe
            break;
        }
    }
    while(ch!=13);
    switch(counter)
    {
    case 1:
        closegraph();
        admin_search_any_account();
        break;
    case 2:
        closegraph();
        admin_search_any_information();
        break;
    case 3:
        closegraph();
        admin_delete_any_account();
        break;
    case 4:
        closegraph();
        requested_or_deleted_account();
        break;
    case 5:
        closegraph();
        admin_update_any_account();
        break;
    case 6:
        closegraph();
        admin_view_all();
        break;
    case 7:
        closegraph();
        admin_view_balance();
        break;
    case 8:
        closegraph();
        logout();
        intro();
        break;
    }
}



void admin::admin_menu()
{
    initwindow(800,600);

    readimagefile("admin_menu_4.jpg",0,0,800,600);

    admin_menu_content();
    menu_toggling();

    getch();
}



void admin::admin_search_any_account()
{
    initwindow(1000,700);

    readimagefile("passcode.jpg", 0, 0, 1000, 700);

    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);



    int state=0, line_gap=0, side_gap=0;
    state=mysql_query(con, select_cust_acc_no);//"SELECT customer_account_no FROM customers"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(line_gap>=450 && side_gap<800)
            {
                line_gap=0;
                side_gap+=100;
            }
            if(side_gap>800)
            {
                line_gap=0;
                side_gap=0;
                initwindow(1000, 700);
                readimagefile("passcode.jpg", 0, 0, 1000, 700);
            }
            settextstyle(3,0,2);
            setcolor(LIGHTBLUE);
            outtextxy(50,50,"     Existing Account Numbers:       ");

            settextstyle(3,0,1);
            setcolor(WHITE);
            outtextxy(80+side_gap,100+line_gap,row[0]);
            line_gap+=40;
        }
    }
    setcolor(LIGHTBLUE);
    settextstyle(8,0,2);
    outtextxy(100,500,"Account Number: ");

    int id_temp[15],customer_id=0,digit,d_gap=0,i=0,j;
    char dig[3];

    setcolor(0);
    settextstyle(8,0,2);
    outtextxy(300,500," ");

    while(1)
    {
        digit=getch();
        if(digit==13)//enter press korse
            break;
        else if(digit==27)
        {
            closegraph();
            admin_menu();
        }
        else if(digit==9)
        {
            closegraph();
            admin_search_any_account();
        }
        else if(digit==8 && i==0)
        {
            setcolor(0);
            settextstyle(8,0,2);
            outtextxy(300,500," ");
        }
        else if(digit==8 && i>0)
        {
            i--;
            setcolor(15);
            settextstyle(8,0,2);
            d_gap-=12;
            outtextxy(300+d_gap,500," ");
        }
        else
        {
            id_temp[i]=digit-48;//character array te nitesi
            sprintf(dig,"%d",digit-48);
            setcolor(15);
            settextstyle(8,0,2);
            outtextxy(300+d_gap,500,dig);
            i++;
            d_gap+=12;//ak character theke next character er gap
        }
    }
    id_temp[i]='\0';
    for (j=0; j<i; j++) //int array theke normal int e convert kortesi
    {
        customer_id*=10;
        customer_id+=id_temp[j];
    }

    string customer_id_in_string;
    customer_id_in_string=to_string(customer_id);

    state=mysql_query(con, select_all_from_cust);//"SELECT * FROM customers"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(row[0]==customer_id_in_string)
            {
                closegraph();

                initwindow(1000,700);

                readimagefile("passcode.jpg", 0, 0, 1000, 700);

                settextstyle(9,0,1);
                setcolor(CYAN);
                outtextxy(100,150,"Account Number:");
                outtextxy(100,200,"Full Name:");
                outtextxy(100,250,"Username:");
                outtextxy(100,300,"Address:");
                outtextxy(100,350,"Date of Birth:");
                outtextxy(100,400,"Phone Number:");
                outtextxy(100,450,"Created on:");

                settextstyle(9,0,1);
                setcolor(WHITE);
                outtextxy(300,150,row[0]);
                outtextxy(300,200,row[1]);
                outtextxy(300,250,row[2]);
                outtextxy(300,300,row[3]);
                outtextxy(300,350,row[4]);
                outtextxy(300,400,row[5]);
                outtextxy(300,450,row[6]);

                getch();
                closegraph();
                admin_menu();
            }
        }

        setcolor(LIGHTCYAN);
        settextstyle(8,0,2);
        outtextxy(200,550,"Invalid Account Number !!");

        getch();
        closegraph();
        admin_search_any_account();
    }

    settextstyle(8,0,1);
    outtextxy(200,240,"Database Error !!");

    closegraph();
    admin_search_any_account();
}

void admin::admin_search_any_information()
{
    initwindow(800,400);

    readimagefile("passcode.jpg", 0, 0, 800, 400);

    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    setcolor(LIGHTBLUE);
    settextstyle(8,0,2);
    outtextxy(50,180,"Search for: ");

    char search_temp[100],str[3], chrctr;
    int c_gap=0, i=0, j;
    string search_content="";

    setcolor(0);
    settextstyle(8,0,3);
    outtextxy(250,180," ");

    while(1)
    {
        chrctr=getch();
        if(chrctr=='\r')//enter press korse
            break;
        else if(chrctr==27)
        {
            closegraph();
            admin_menu();
        }
        else if(chrctr==9)
        {
            closegraph();
            admin_search_any_information();
        }
        else if(chrctr==8 && i==0)
        {
            setcolor(0);
            settextstyle(8,0,3);
            outtextxy(250,180," ");
        }
        else if(chrctr==8 && i>0)
        {
            i--;
            setcolor(15);
            settextstyle(8,0,3);
            c_gap-=15;
            outtextxy(250+c_gap,180," ");
        }
        else
        {
            search_temp[i]=chrctr;//character array te nitesi
            sprintf(str,"%c",chrctr);
            setcolor(15);
            settextstyle(8,0,3);
            outtextxy(250+c_gap,180,str);
            i++;
            c_gap+=15;//ak character theke next character er gap
        }
    }
    search_temp[i]='\0';
    for(j=0; j<i; j++) //character array theke string e nitesi
    {
        search_content=search_content+search_temp[j];
    }

    closegraph();
    initwindow(1285,780);

    readimagefile("passcode.jpg", 0, 0, 1285, 780);

    int state=0, line_gap=50, flag=0;
    state=mysql_query(con, select_all_from_cust);//"SELECT * FROM customers"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(row[0]==search_content || row[1]==search_content || row[2]==search_content || row[3]==search_content || row[4]==search_content || row[5]==search_content || row[6]==search_content)
            {
                flag=1;
                if(line_gap>=750)
                {
                    line_gap=50;
                    initwindow(1285,780);
                    readimagefile("passcode.jpg", 0, 0, 1285, 780);
                }
                settextstyle(3,0,2);
                setcolor(LIGHTBLUE);
                outtextxy(450,50,"     CUSTOMERS' INFORMATION       ");
                settextstyle(3,0,1);
                setcolor(CYAN);
                outtextxy(10,100,"Account Number");
                outtextxy(180,100,"Full Name");
                outtextxy(380,100,"Username");
                outtextxy(620,100,"Address");
                outtextxy(840,100,"Date of Birth");
                outtextxy(975,100,"Phone Number");
                outtextxy(1150,100,"Created on");

                settextstyle(3,0,1);
                setcolor(WHITE);
                outtextxy(30,100+line_gap,row[0]);
                outtextxy(160,100+line_gap,row[1]);
                outtextxy(340,100+line_gap,row[2]);
                outtextxy(510,100+line_gap,row[3]);
                outtextxy(840,100+line_gap,row[4]);
                outtextxy(980,100+line_gap,row[5]);
                outtextxy(1120,100+line_gap,row[6]);
                line_gap+=40;
            }
        }

        if(flag==0)
        {
            closegraph();
            initwindow(800,600);
            readimagefile("passcode.jpg", 0, 0, 800,600);
            settextstyle(3,0,2);
            setcolor(CYAN);
            outtextxy(300,280,"Information Not Found !!");
            getch();
            closegraph();
            admin_search_any_information();
        }

        getch();
        closegraph();
        admin_menu();

    }

    settextstyle(8,0,1);
    outtextxy(200,240,"Database Error !!");

    closegraph();
    admin_search_any_information();
}

void admin::admin_delete_select(int val) //Text gula toggling er shomoy boro korbe
{
    switch(val)
    {
    case 1:
        settextstyle(9,0,4);
        setcolor(WHITE);
        outtextxy(270,150,"    Yes ");
        settextstyle(9,0,2);
        outtextxy(270,155,">>");
        break;
    case 2:
        settextstyle(9,0,4);
        setcolor(WHITE);
        outtextxy(320,200,"    No ");
        settextstyle(9,0,2);
        outtextxy(320,205,">>");
        break;
    }
}

void admin::admin_delete_option()
{
    settextstyle(9,0,3);
    setcolor(WHITE);
    outtextxy(270,153,"      Yes  ");
    outtextxy(320,203,"      No ");
}

void admin::admin_delete_choose(int id, int value)//upore niche move korbe
{
    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    char ch;
    admin_delete_option();
    admin_delete_select(delete_opt);
    do
    {
        ch=getch();
        switch(ch)
        {
        case 72://upore uthbe
            delete_opt--;
            if(delete_opt==0)
            {
                delete_opt=2;
            }
            admin_delete_option();
            admin_delete_select(delete_opt);
            continue;
        case 80://niche nambe
            delete_opt++;
            if(delete_opt==3)
            {
                delete_opt=1;
            }
            admin_delete_option();
            admin_delete_select(delete_opt);
            continue;
        case 13://enter press korbe
            break;
        }
    }
    while(ch!=13);

    switch(delete_opt)
    {
    case 1:
    {

        string id_in_string=to_string(id);
        int state,states,statess,statesss,statessss;

        stringstream s;
        stringstream ss;
        stringstream sss;
        stringstream ssss;
        stringstream sssss;
        stringstream ssssss;
        stringstream sssssss;
        statesss=mysql_query(con, select_all_from_cust);//"SELECT * FROM customers"
        if(!statesss)
        {
            res=mysql_store_result(con);
            while(row=mysql_fetch_row(res))
            {
                if(row[0]==id_in_string)
                {
                    ssssss<<"INSERT INTO customer_deleted_information VALUES("<<id<<", '"<<row[1]<<"', '"<<row[2]<<"', '"<<row[3]<<"', '"<<row[4]<<"', '"<<row[5]<<"', '"<<row[6]<<"')";
                    string queryyy=ssssss.str();
                    const char* a=queryyy.c_str();
                    statesss=mysql_query(con, a);
                    break;
                }
            }
        }
        statessss=mysql_query(con, select_all_from_cust_baln);//"SELECT * FROM customer_balance"
        if(!statessss)
        {
            res=mysql_store_result(con);
            while(row=mysql_fetch_row(res))
            {
                if(row[0]==id_in_string)
                {
                    sssssss<<"INSERT INTO customer_deleted_balance VALUES ("<<id<<", '"<<row[1]<<"', '"<<row[2]<<"', '"<<row[3]<<"', '"<<row[4]<<"', '"<<row[5]<<"', '"<<row[6]<<"')";
                    string queryyyy=sssssss.str();
                    const char* b=queryyyy.c_str();
                    statessss=mysql_query(con, b);
                    break;
                }
            }
        }
        s<<"DELETE FROM customers WHERE customer_account_no='"<<id<<"' limit 1";
        ss<<"DELETE FROM customer_login WHERE customer_id='"<<id<<"' limit 1";
        sss<<"DELETE FROM customer_balance WHERE customer_account_no='"<<id<<"' limit 1";
        ssss<<"DELETE FROM customer_delete_request_information WHERE customer_account_no='"<<id<<"' limit 1";
        sssss<<"DELETE FROM customer_delete_request_balance WHERE customer_account_no='"<<id<<"' limit 1";
        string query=s.str();
        string queries=ss.str();
        string queriess=sss.str();
        string queriesss=ssss.str();
        string queriessss=sssss.str();
        const char* q=query.c_str();
        const char* p=queries.c_str();
        const char* o=queriess.c_str();
        const char* n=queriesss.c_str();
        const char* m=queriessss.c_str();
        state=mysql_query(con, q);
        states=mysql_query(con, p);
        statess=mysql_query(con, o);
        mysql_query(con, n);
        mysql_query(con, m);
        if(!state && !states && !statess)
        {
            settextstyle(9,0,2);
            setcolor(LIGHTCYAN);
            outtextxy(200,270,"      Account Deleted !!     ");
        }
        else
        {
            settextstyle(9,0,2);
            setcolor(LIGHTCYAN);
            outtextxy(130,270,"      Account was not deleted !!     ");
        }
        getch();
        closegraph();
        admin_delete_any_account();
    }
    break;
    case 2:
        {
            closegraph();
            if(value==1)
                admin_delete_any_account(); //delete any account option ta theke delete korar shomoy no press korse
            else if(value==2)
                requested_or_deleted_account(); //delete requested account option ta theke delete korar shomoy no press korse
        }
        break;
    }
}

void admin::admin_delete_account(int id, int value)
{
    initwindow(800,400);

    readimagefile("passcode.jpg", 0, 0, 800, 400);

    settextstyle(9,0,2);
    setcolor(LIGHTCYAN);
    outtextxy(150,100,"Are you sure to delete the account ?!");

    admin_delete_option();
    admin_delete_choose(id, value);
}

void admin::admin_delete_any_account()
{
    initwindow(1000,700);

    readimagefile("passcode.jpg", 0, 0, 1000, 700);

    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);



    int state=0, line_gap=0, side_gap=0;
    state=mysql_query(con, select_cust_acc_no);//"SELECT customer_account_no FROM customers"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(line_gap>=450 && side_gap<800)
            {
                line_gap=0;
                side_gap+=100;
            }
            if(side_gap>800)
            {
                line_gap=0;
                side_gap=0;
                initwindow(1000, 700);
                readimagefile("passcode.jpg", 0, 0, 1000, 700);
            }
            settextstyle(3,0,2);
            setcolor(LIGHTBLUE);
            outtextxy(50,50,"     Exixting Account Numbers:       ");

            settextstyle(3,0,1);
            setcolor(WHITE);
            outtextxy(80+side_gap,100+line_gap,row[0]);
            line_gap+=40;
        }
    }
    setcolor(LIGHTBLUE);
    settextstyle(8,0,2);
    outtextxy(100,500,"Account Number: ");

    int id_temp[15],customer_id=0,digit,d_gap=0,i=0,j;
    char dig[3];

    setcolor(0);
    settextstyle(8,0,2);
    outtextxy(300,500," ");

    while(1)
    {
        digit=getch();
        if(digit==13)//enter press korse
            break;
        else if(digit==27)
        {
            closegraph();
            admin_menu();
        }
        else if(digit==9)
        {
            closegraph();
            admin_search_any_account();
        }
        else if(digit==8 && i==0)
        {
            setcolor(0);
            settextstyle(8,0,2);
            outtextxy(300,500," ");
        }
        else if(digit==8 && i>0)
        {
            i--;
            setcolor(15);
            settextstyle(8,0,2);
            d_gap-=12;
            outtextxy(300+d_gap,500," ");
        }
        else
        {
            id_temp[i]=digit-48;//character array te nitesi
            sprintf(dig,"%d",digit-48);
            setcolor(15);
            settextstyle(8,0,2);
            outtextxy(300+d_gap,500,dig);
            i++;
            d_gap+=12;//ak character theke next character er gap
        }
    }
    id_temp[i]='\0';
    for (j=0; j<i; j++) //int array theke normal int e convert kortesi
    {
        customer_id*=10;
        customer_id+=id_temp[j];
    }

    string customer_id_in_string;
    customer_id_in_string=to_string(customer_id);

    closegraph();

    state=mysql_query(con, select_cust_acc_no);//"SELECT customer_account_no FROM customers"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(row[0]==customer_id_in_string)
            {
                admin_delete_account(customer_id,1);
            }
        }

        initwindow(800,400);

        readimagefile("passcode.jpg", 0, 0, 800, 400);

        settextstyle(9,0,2);
        setcolor(LIGHTCYAN);
        outtextxy(150,180,"Invalid Account Number !!");

        getch();
        closegraph();
        admin_delete_any_account();
    }

    initwindow(800,400);

    readimagefile("passcode.jpg", 0, 0, 800, 400);

    settextstyle(8,0,1);
    outtextxy(200,180,"Database Error !!");

    closegraph();
    admin_delete_any_account();
}

void admin::requested_or_deleted_account_select(int val) //acount jara delete korte chay othoba jader account delete hoye gese, tader information
{                                             //Text gula toggling er shomoy boro korbe
    switch(val)
    {
    case 1:
        settextstyle(9,0,3);
        setcolor(LIGHTCYAN);
        outtextxy(360,260," Accounts Requested to Delete ");
        settextstyle(9,0,2);
        outtextxy(325,265,">>");
        break;
    case 2:
        settextstyle(9,0,3);
        setcolor(LIGHTCYAN);
        outtextxy(410,350," Deleted Accounts ");
        settextstyle(9,0,2);
        outtextxy(375,355,">>");
        break;
    }
}

void admin::requested_or_deleted_account_content() //acount jara delete korte chay, tader information
{
    settextstyle(9,0,2);
    setcolor(LIGHTCYAN);
    outtextxy(325,261,"      Accounts Requested to Delete     ");
    outtextxy(375,351,"      Deleted Accounts     ");
}

void admin::requested_or_deleted_account_toggling()//acount jara delete korte chay, tader information
{                                                      //upore niche move korbe
    char ch;
    static int countttttt=1;
    requested_or_deleted_account_content();
    requested_or_deleted_account_select(countttttt);
    do
    {
        ch=getch();
        switch(ch)
        {
        case 72://upore uthbe
            countttttt--;
            if(countttttt==0)
            {
                countttttt=2;
            }
            requested_or_deleted_account_content();
            requested_or_deleted_account_select(countttttt);
            continue;
        case 80://niche nambe
            countttttt++;
            if(countttttt==3)
            {
                countttttt=1;
            }
            requested_or_deleted_account_content();
            requested_or_deleted_account_select(countttttt);
            continue;
        case 27:
            closegraph();
            admin_menu();
            break;
        case 13://enter press korbe
            break;
        }
    }
    while(ch!=13);

    switch(countttttt)
    {
    case 1:
        closegraph();
        account_deletion_request();
        break;
    case 2:
        closegraph();
        deleted_account();
        break;
    }
}

void admin::requested_or_deleted_account()
{
    initwindow(1000,700);

    readimagefile("image_login.jpg", 0, 0, 1000, 700);

    requested_or_deleted_account_content();
    requested_or_deleted_account_toggling();

    getch();
    closegraph();
}

void admin::delete_request_account_select(int val) //account jara delete korte chay, tader information
{                                             //Text gula toggling er shomoy boro korbe
    switch(val)
    {
    case 1:
        settextstyle(9,0,3);
        setcolor(LIGHTCYAN);
        outtextxy(360,200," Personal Information ");
        settextstyle(9,0,2);
        outtextxy(325,205,">>");
        break;
    case 2:
        settextstyle(9,0,3);
        setcolor(LIGHTCYAN);
        outtextxy(410,290," Balance Information ");
        settextstyle(9,0,2);
        outtextxy(375,295,">>");
        break;
    case 3:
        settextstyle(9,0,3);
        setcolor(LIGHTCYAN);
        outtextxy(460,380," Delete Requested Account ");
        settextstyle(9,0,2);
        outtextxy(425,385,">>");
        break;
    }
}

void admin::delete_request_account_content() //account jara delete korte chay, tader information
{
    settextstyle(9,0,2);
    setcolor(LIGHTCYAN);
    outtextxy(325,201,"      Personal Information     ");
    outtextxy(375,291,"      Balance Information     ");
    outtextxy(425,381,"      Delete Requested Account     ");
}

void admin::delete_request_account_toggling()//account jara delete korte chay, tader information
{                                                      //upore niche move korbe
    char ch;
    static int counttttt=1;
    delete_request_account_content();
    delete_request_account_select(counttttt);
    do
    {
        ch=getch();
        switch(ch)
        {
        case 72://upore uthbe
            counttttt--;
            if(counttttt==0)
            {
                counttttt=3;
            }
            delete_request_account_content();
            delete_request_account_select(counttttt);
            continue;
        case 80://niche nambe
            counttttt++;
            if(counttttt==4)
            {
                counttttt=1;
            }
            delete_request_account_content();
            delete_request_account_select(counttttt);
            continue;
        case 27:
            closegraph();
            requested_or_deleted_account();
            break;
        case 13://enter press korbe
            break;
        }
    }
    while(ch!=13);

    switch(counttttt)
    {
    case 1:
        closegraph();
        delete_request_account_personal_information();
        break;
    case 2:
        closegraph();
        delete_request_account_balance_information();
        break;
    case 3:
        closegraph();
        delete_request_account_delete();
        break;
    }
}

void admin::delete_request_account_personal_information() //jara account delete korte chay, tader personal information
{

    initwindow(1285,780);

    readimagefile("passcode.jpg", 0, 0, 1285, 780);

    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    int state=0, line_gap=50;
    state=mysql_query(con, select_all_from_cust_del_info);//"SELECT * FROM customer_delete_request_information"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(line_gap>=750)
            {
                line_gap=50;
                initwindow(1285,780);
                readimagefile("passcode.jpg", 0, 0, 1285, 780);
            }
            settextstyle(3,0,2);
            setcolor(LIGHTBLUE);
            outtextxy(450,50,"     CUSTOMERS' INFORMATION       ");
            settextstyle(3,0,1);
            setcolor(CYAN);
            outtextxy(10,100,"Account Number");
            outtextxy(180,100,"Full Name");
            outtextxy(380,100,"Username");
            outtextxy(620,100,"Address");
            outtextxy(840,100,"Date of Birth");
            outtextxy(975,100,"Phone Number");
            outtextxy(1150,100,"Created on");

            settextstyle(3,0,1);
            setcolor(WHITE);
            outtextxy(30,100+line_gap,row[0]);
            outtextxy(160,100+line_gap,row[1]);
            outtextxy(340,100+line_gap,row[2]);
            outtextxy(510,100+line_gap,row[3]);
            outtextxy(840,100+line_gap,row[4]);
            outtextxy(980,100+line_gap,row[5]);
            outtextxy(1120,100+line_gap,row[6]);
            line_gap+=40;
        }
        getch();
        closegraph();
        account_deletion_request();
    }

    settextstyle(8,0,1);
    outtextxy(200,240,"Database Error !!");

    closegraph();
    delete_request_account_personal_information();
}

void admin::delete_request_account_balance_information() ////jara account delete korte chay, tader balance information
{

    initwindow(1285,780);

    readimagefile("passcode.jpg", 0, 0, 1285, 780);

    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    int state=0,line_gap=50;
    state=mysql_query(con, select_all_from_cust_del_baln);//"SELECT * FROM customer_delete_request_balance"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(line_gap>=750)
            {
                line_gap=50;
                initwindow(1285,780);
                readimagefile("passcode.jpg", 0, 0, 1285, 780);
            }
            settextstyle(3,0,2);
            setcolor(LIGHTBLUE);
            outtextxy(300,50,"     CUSTOMERS' ACCOUNT BALANCE       ");
            settextstyle(3,0,1);
            setcolor(CYAN);
            outtextxy(10,100,"Account Number");
            outtextxy(180,100,"Full Name");
            outtextxy(360,100,"Balance");
            outtextxy(520,100,"Last Deposited Amount");
            outtextxy(740,100,"Last Deposited Date");
            outtextxy(905,100,"Last Withdrawal Amount");
            outtextxy(1100,100,"Last Withdrawal Date");

            settextstyle(3,0,1);
            setcolor(WHITE);
            outtextxy(330,100+line_gap,"Tk.  ");
            outtextxy(540,100+line_gap,"Tk.  ");
            outtextxy(925,100+line_gap,"Tk.  ");
            outtextxy(30,100+line_gap,row[0]);
            outtextxy(160,100+line_gap,row[1]);
            outtextxy(355,100+line_gap,row[2]);
            outtextxy(565,100+line_gap,row[3]);
            outtextxy(740,100+line_gap,row[4]);
            outtextxy(950,100+line_gap,row[5]);
            outtextxy(1100,100+line_gap,row[6]);
            line_gap+=40;
        }
        getch();
        closegraph();
        account_deletion_request();
    }

    settextstyle(8,0,1);
    outtextxy(200,240,"Database Error !!");

    closegraph();
    delete_request_account_balance_information();
}

void admin::delete_request_account_delete()
{
    initwindow(1000,700);

    readimagefile("passcode.jpg", 0, 0, 1000, 700);

    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);



    int state=0, line_gap=0, side_gap=0;
    state=mysql_query(con, select_cust_acc_from_del);//"SELECT customer_account_no FROM customer_delete_request_information"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(line_gap>=450 && side_gap<800)
            {
                line_gap=0;
                side_gap+=100;
            }
            if(side_gap>800)
            {
                line_gap=0;
                side_gap=0;
                initwindow(1000, 700);
                readimagefile("passcode.jpg", 0, 0, 1000, 700);
            }
            settextstyle(3,0,2);
            setcolor(LIGHTBLUE);
            outtextxy(50,50,"     Requested Account Numbers:       ");

            settextstyle(3,0,1);
            setcolor(WHITE);
            outtextxy(80+side_gap,100+line_gap,row[0]);
            line_gap+=40;
        }
    }
    setcolor(LIGHTBLUE);
    settextstyle(8,0,2);
    outtextxy(100,500,"Account Number: ");

    int id_temp[15],customer_id=0,digit,d_gap=0,i=0,j;
    char dig[3];

    setcolor(0);
    settextstyle(8,0,2);
    outtextxy(300,500," ");

    while(1)
    {
        digit=getch();
        if(digit==13)//enter press korse
            break;
        else if(digit==27)
        {
            closegraph();
            admin_menu();
        }
        else if(digit==9)
        {
            closegraph();
            delete_request_account_delete();
        }
        else if(digit==8 && i==0)
        {
            setcolor(0);
            settextstyle(8,0,2);
            outtextxy(300,500," ");
        }
        else if(digit==8 && i>0)
        {
            i--;
            setcolor(15);
            settextstyle(8,0,2);
            d_gap-=12;
            outtextxy(300+d_gap,500," ");
        }
        else
        {
            id_temp[i]=digit-48;//character array te nitesi
            sprintf(dig,"%d",digit-48);
            setcolor(15);
            settextstyle(8,0,2);
            outtextxy(300+d_gap,500,dig);
            i++;
            d_gap+=12;//ak character theke next character er gap
        }
    }
    id_temp[i]='\0';
    for (j=0; j<i; j++) //int array theke normal int e convert kortesi
    {
        customer_id*=10;
        customer_id+=id_temp[j];
    }

    string customer_id_in_string;
    customer_id_in_string=to_string(customer_id);

    closegraph();

    state=mysql_query(con, select_cust_acc_from_del);//"SELECT customer_account_no FROM customer_delete_request_information"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(row[0]==customer_id_in_string)
            {
                admin_delete_account(customer_id,2);
            }
        }

        initwindow(800,400);

        readimagefile("passcode.jpg", 0, 0, 800, 400);

        settextstyle(9,0,2);
        setcolor(LIGHTCYAN);
        outtextxy(150,180,"Invalid Account Number !!");

        getch();
        closegraph();
        delete_request_account_delete();
    }

    initwindow(800,400);

    readimagefile("passcode.jpg", 0, 0, 800, 400);

    settextstyle(8,0,1);
    outtextxy(200,180,"Database Error !!");

    closegraph();
    delete_request_account_delete();
}

void admin::account_deletion_request()
{
    initwindow(1000,700);

    readimagefile("image_login.jpg", 0, 0, 1000, 700);

    delete_request_account_content();
    delete_request_account_toggling();

    getch();
    closegraph();
}

void admin::deleted_account_select(int val) //acount jara delete korte chay, tader information
{                                             //Text gula toggling er shomoy boro korbe
    switch(val)
    {
    case 1:
        settextstyle(9,0,3);
        setcolor(LIGHTCYAN);
        outtextxy(360,200," Personal Information ");
        settextstyle(9,0,2);
        outtextxy(325,205,">>");
        break;
    case 2:
        settextstyle(9,0,3);
        setcolor(LIGHTCYAN);
        outtextxy(410,290," Balance Information ");
        settextstyle(9,0,2);
        outtextxy(375,295,">>");
        break;
    case 3:
        settextstyle(9,0,3);
        setcolor(LIGHTCYAN);
        outtextxy(460,380," Hard Delete ");
        settextstyle(9,0,2);
        outtextxy(425,385,">>");
        break;
    }
}

void admin::deleted_account_content() //acount jara delete korte chay, tader information
{
    settextstyle(9,0,2);
    setcolor(LIGHTCYAN);
    outtextxy(325,201,"      Personal Information     ");
    outtextxy(375,291,"      Balance Information     ");
    outtextxy(425,381,"      Hard Delete     ");
}

void admin::deleted_account_toggling()//acount jara delete korte chay, tader information
{                                                      //upore niche move korbe
    char ch;
    static int countttttt=1;
    deleted_account_content();
    deleted_account_select(countttttt);
    do
    {
        ch=getch();
        switch(ch)
        {
        case 72://upore uthbe
            countttttt--;
            if(countttttt==0)
            {
                countttttt=3;
            }
            deleted_account_content();
            deleted_account_select(countttttt);
            continue;
        case 80://niche nambe
            countttttt++;
            if(countttttt==4)
            {
                countttttt=1;
            }
            deleted_account_content();
            deleted_account_select(countttttt);
            continue;
        case 27:
            closegraph();
            requested_or_deleted_account();
            break;
        case 13://enter press korbe
            break;
        }
    }
    while(ch!=13);

    switch(countttttt)
    {
    case 1:
        closegraph();
        deleted_account_personal_information();
        break;
    case 2:
        closegraph();
        deleted_account_balance_information();
        break;
    case 3:
        closegraph();
        hard_delete_account();
        break;
    }
}

void admin::deleted_account_personal_information() //jara account delete korte chay, tader personal information
{

    initwindow(1285,780);

    readimagefile("passcode.jpg", 0, 0, 1285, 780);

    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    int state=0, line_gap=50;
    state=mysql_query(con, select_all_from_deltd_info);//"SELECT * FROM customer_deleted_information"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(line_gap>=750)
            {
                line_gap=50;
                initwindow(1285,780);
                readimagefile("passcode.jpg", 0, 0, 1285, 780);
            }
            settextstyle(3,0,2);
            setcolor(LIGHTBLUE);
            outtextxy(450,50,"     CUSTOMERS' INFORMATION       ");
            settextstyle(3,0,1);
            setcolor(CYAN);
            outtextxy(10,100,"Account Number");
            outtextxy(180,100,"Full Name");
            outtextxy(380,100,"Username");
            outtextxy(620,100,"Address");
            outtextxy(840,100,"Date of Birth");
            outtextxy(975,100,"Phone Number");
            outtextxy(1150,100,"Created on");

            settextstyle(3,0,1);
            setcolor(WHITE);
            outtextxy(30,100+line_gap,row[0]);
            outtextxy(160,100+line_gap,row[1]);
            outtextxy(340,100+line_gap,row[2]);
            outtextxy(510,100+line_gap,row[3]);
            outtextxy(840,100+line_gap,row[4]);
            outtextxy(980,100+line_gap,row[5]);
            outtextxy(1120,100+line_gap,row[6]);
            line_gap+=40;
        }
        getch();
        closegraph();
        deleted_account();
    }

    settextstyle(8,0,1);
    outtextxy(200,240,"Database Error !!");

    closegraph();
    deleted_account_personal_information();
}

void admin::deleted_account_balance_information() ////jara account delete korte chay, tader balance information
{

    initwindow(1285,780);

    readimagefile("passcode.jpg", 0, 0, 1285, 780);

    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    int state=0,line_gap=50;
    state=mysql_query(con, select_all_from_deltd_baln);//"SELECT * FROM customer_deleted_balance"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(line_gap>=750)
            {
                line_gap=50;
                initwindow(1285,780);
                readimagefile("passcode.jpg", 0, 0, 1285, 780);
            }
            settextstyle(3,0,2);
            setcolor(LIGHTBLUE);
            outtextxy(300,50,"     CUSTOMERS' ACCOUNT BALANCE       ");
            settextstyle(3,0,1);
            setcolor(CYAN);
            outtextxy(10,100,"Account Number");
            outtextxy(180,100,"Full Name");
            outtextxy(360,100,"Balance");
            outtextxy(520,100,"Last Deposited Amount");
            outtextxy(740,100,"Last Deposited Date");
            outtextxy(905,100,"Last Withdrawal Amount");
            outtextxy(1100,100,"Last Withdrawal Date");

            settextstyle(3,0,1);
            setcolor(WHITE);
            outtextxy(330,100+line_gap,"Tk.  ");
            outtextxy(540,100+line_gap,"Tk.  ");
            outtextxy(925,100+line_gap,"Tk.  ");
            outtextxy(30,100+line_gap,row[0]);
            outtextxy(160,100+line_gap,row[1]);
            outtextxy(355,100+line_gap,row[2]);
            outtextxy(565,100+line_gap,row[3]);
            outtextxy(740,100+line_gap,row[4]);
            outtextxy(950,100+line_gap,row[5]);
            outtextxy(1100,100+line_gap,row[6]);
            line_gap+=40;
        }
        getch();
        closegraph();
        deleted_account();
    }

    settextstyle(8,0,1);
    outtextxy(200,240,"Database Error !!");

    closegraph();
    deleted_account_balance_information();
}

void admin::hard_delete_account()
{
    initwindow(1000,700);

    readimagefile("passcode.jpg", 0, 0, 1000, 700);

    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);



    int state=0, line_gap=0, side_gap=0;
    state=mysql_query(con, select_acc_no_from_deltd_info);//"SELECT customer_account_no FROM customer_deleted_information"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(line_gap>=450 && side_gap<800)
            {
                line_gap=0;
                side_gap+=100;
            }
            if(side_gap>800)
            {
                line_gap=0;
                side_gap=0;
                initwindow(1000, 700);
                readimagefile("passcode.jpg", 0, 0, 1000, 700);
            }
            settextstyle(3,0,2);
            setcolor(LIGHTBLUE);
            outtextxy(50,50,"     Deleted Account Numbers:       ");

            settextstyle(3,0,1);
            setcolor(WHITE);
            outtextxy(80+side_gap,100+line_gap,row[0]);
            line_gap+=40;
        }
    }
    setcolor(LIGHTBLUE);
    settextstyle(8,0,2);
    outtextxy(100,500,"Account Number: ");

    int id_temp[15],customer_id=0,digit,d_gap=0,i=0,j;
    char dig[3];

    setcolor(0);
    settextstyle(8,0,2);
    outtextxy(300,500," ");

    while(1)
    {
        digit=getch();
        if(digit==13)//enter press korse
            break;
        else if(digit==27)
        {
            closegraph();
            deleted_account();
        }
        else if(digit==9)
        {
            closegraph();
            hard_delete_account();
        }
        else if(digit==8 && i==0)
        {
            setcolor(0);
            settextstyle(8,0,2);
            outtextxy(300,500," ");
        }
        else if(digit==8 && i>0)
        {
            i--;
            setcolor(15);
            settextstyle(8,0,2);
            d_gap-=12;
            outtextxy(300+d_gap,500," ");
        }
        else
        {
            id_temp[i]=digit-48;//character array te nitesi
            sprintf(dig,"%d",digit-48);
            setcolor(15);
            settextstyle(8,0,2);
            outtextxy(300+d_gap,500,dig);
            i++;
            d_gap+=12;//ak character theke next character er gap
        }
    }
    id_temp[i]='\0';
    for (j=0; j<i; j++) //int array theke normal int e convert kortesi
    {
        customer_id*=10;
        customer_id+=id_temp[j];
    }

    string customer_id_in_string;
    customer_id_in_string=to_string(customer_id);

    closegraph();

    state=mysql_query(con, select_acc_no_from_deltd_info);//"SELECT customer_account_no FROM customer_deleted_information"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(row[0]==customer_id_in_string)
            {
                permanent_delete_account(customer_id);
            }
        }

        initwindow(800,400);

        readimagefile("passcode.jpg", 0, 0, 800, 400);

        settextstyle(9,0,2);
        setcolor(LIGHTCYAN);
        outtextxy(150,180,"Invalid Account Number !!");

        getch();
        closegraph();
        hard_delete_account();
    }

    initwindow(800,400);

    readimagefile("passcode.jpg", 0, 0, 800, 400);

    settextstyle(8,0,1);
    outtextxy(200,180,"Database Error !!");

    closegraph();
    hard_delete_account();
}

void admin::permanent_delete_account(int customer_id)
{
    initwindow(800,400);

    readimagefile("passcode.jpg", 0, 0, 800, 400);

    settextstyle(9,0,2);
    setcolor(LIGHTCYAN);
    outtextxy(150,100,"Are you sure to delete the account ?!");

    admin_delete_option();
    permanent_delete_choose(customer_id);
}

void admin::permanent_delete_choose(int id)
{
    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    char ch;
    static int delete_opttt=1;
    admin_delete_option();
    admin_delete_select(delete_opttt);
    do
    {
        ch=getch();
        switch(ch)
        {
        case 72://upore uthbe
            delete_opttt--;
            if(delete_opttt==0)
            {
                delete_opttt=2;
            }
            admin_delete_option();
            admin_delete_select(delete_opttt);
            continue;
        case 80://niche nambe
            delete_opttt++;
            if(delete_opttt==3)
            {
                delete_opttt=1;
            }
            admin_delete_option();
            admin_delete_select(delete_opttt);
            continue;
        case 13://enter press korbe
            break;
        }
    }
    while(ch!=13);

    switch(delete_opttt)
    {
    case 1:
    {
        string id_in_string=to_string(id);
        int state,states;
        stringstream s;
        stringstream ss;
        s<<"DELETE FROM customer_deleted_information WHERE customer_account_no='"<<id<<"' limit 1";
        ss<<"DELETE FROM customer_deleted_balance WHERE customer_account_no='"<<id<<"' limit 1";
        string query=s.str();
        string queries=ss.str();
        const char* q=query.c_str();
        const char* p=queries.c_str();
        state=mysql_query(con, q);
        states=mysql_query(con, p);
        if(!state && !states)
        {
            settextstyle(9,0,2);
            setcolor(LIGHTCYAN);
            outtextxy(200,270,"      Account Deleted Permanently !!     ");
        }
        else
        {
            settextstyle(9,0,2);
            setcolor(LIGHTCYAN);
            outtextxy(130,270,"      Account was not deleted !!     ");
        }
        getch();
        closegraph();
        requested_or_deleted_account();
    }
    break;
    case 2:
        closegraph();
        requested_or_deleted_account();
        break;
    }
}

void admin::deleted_account()
{
    initwindow(1000,700);

    readimagefile("image_login.jpg", 0, 0, 1000, 700);

    deleted_account_content();
    deleted_account_toggling();

    getch();
    closegraph();
}

void admin::admin_update_content_select(int val) //Text gula toggling er shomoy boro korbe
{
    switch(val)
    {
    case 1:
        settextstyle(9,0,3);
        setcolor(CYAN);
        outtextxy(80,120,"Full Name      ");
        settextstyle(9,0,3);
        outtextxy(50,120,"->");
        break;
    case 2:
        settextstyle(9,0,3);
        setcolor(CYAN);
        outtextxy(130,180,"Password       ");
        settextstyle(9,0,3);
        outtextxy(100,180,"->");
        break;
    case 3:
        settextstyle(9,0,3);
        setcolor(CYAN);
        outtextxy(180,240,"Address     ");
        settextstyle(9,0,3);
        outtextxy(150,240,"->");
        break;
    case 4:
        settextstyle(9,0,3);
        setcolor(CYAN);
        outtextxy(230,300,"Date of Birth     ");
        settextstyle(9,0,3);
        outtextxy(200,300,"->");
        break;
    case 5:
        settextstyle(9,0,3);
        setcolor(CYAN);
        outtextxy(280,360,"Phone Number    ");
        settextstyle(9,0,3);
        outtextxy(250,360,"->");
        break;
    }
}

void admin::admin_update_content()
{
    settextstyle(9,0,2);
    setcolor(CYAN);
    outtextxy(50,120,"     Full Name      ");
    outtextxy(100,180,"     Password       ");
    outtextxy(150,240,"     Address     ");
    outtextxy(200,300,"     Date of Birth      ");
    outtextxy(250,360,"     Phone Number     ");
}

void admin::admin_update_toggling(int id)
{
    char ch;
    static int counterrr=1;
    admin_update_content();
    admin_update_content_select(counterrr);
    do
    {
        ch=getch();
        switch(ch)
        {
        case 72://upore uthbe
            counterrr--;
            if(counterrr==0)
            {
                counterrr=5;
            }
            admin_update_content();
            admin_update_content_select(counterrr);
            continue;
        case 80://niche nambe
            counterrr++;
            if(counterrr==6)
            {
                counterrr=1;
            }
            admin_update_content();
            admin_update_content_select(counterrr);
            continue;
        case 27:
            closegraph();
            admin_update_any_account();
            break;
        case 13://enter press korbe
            break;
        }
    }
    while(ch!=13);

    closegraph();
    admin_update_insert(id, counterrr);
}

void admin::admin_update_insert(int id, int counterrr)
{
    initwindow(800,600);

    readimagefile("admin_menu.jpg",0,0,800,600);

    switch(counterrr)
    {
    case 1:
    {
        settextstyle(9,0,2);
        setcolor(LIGHTBLUE);
        outtextxy(140,280,"Full Name: ");
    }
    break;
    case 2:
    {
        settextstyle(9,0,2);
        setcolor(LIGHTBLUE);
        outtextxy(140,280,"Password: ");
    }
    break;
    case 3:
    {
        settextstyle(9,0,2);
        setcolor(LIGHTBLUE);
        outtextxy(140,280,"Address: ");
    }
    break;
    case 4:
    {
        settextstyle(9,0,2);
        setcolor(LIGHTBLUE);
        outtextxy(80,280,"Date of Birth: ");
        settextstyle(9,0,1);
        outtextxy(80,300,"[YYYY-MM-DD]");
    }
    break;
    case 5:
    {
        settextstyle(9,0,2);
        setcolor(LIGHTBLUE);
        outtextxy(80,280,"Phone Number: ");
    }
    break;
    }

    char content_temp[30], chrctr, str[3];
    int c_gap=0,i=0,j;
    string content="";

    setcolor(0);
    settextstyle(8,0,2);
    outtextxy(290,280," ");

    while(1)
    {
        chrctr=getch();
        if(chrctr=='\r')//enter press korse
            break;
        else if(chrctr==27)
        {
            closegraph();
            admin_update_options(id);
        }
        else if(chrctr==9)
        {
            closegraph();
            admin_update_insert(id, counterrr);
        }
        else if(chrctr==8 && i==0)
        {
            setcolor(0);
            settextstyle(8,0,2);
            outtextxy(290,280," ");
        }
        else if(chrctr==8 && i>0)
        {
            i--;
            setcolor(15);
            settextstyle(8,0,2);
            c_gap-=14;
            outtextxy(290+c_gap,280," ");
        }
        else
        {
            content_temp[i]=chrctr;//character array te nitesi
            sprintf(str,"%c",chrctr);
            setcolor(15);
            settextstyle(8,0,2);
            outtextxy(290+c_gap,280,str);
            i++;
            c_gap+=14;//ak character theke next character er gap
        }
    }
    content_temp[i]='\0';
    for(j=0; j<i; j++) //character array theke string e nitesi
    {
        content=content+content_temp[j];
    }

    string id_in_string=to_string(id);

    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    stringstream s;

    switch(counterrr)
    {
    case 1:
    {
        if(content.size()<1)
        {
            settextstyle(9,0,1);
            setcolor(LIGHTRED);
            outtextxy(200,340,"Enter a valid name !!");
            getch();
            closegraph();
            admin_update_insert(id, counterrr);
        }
        s<<"UPDATE customers SET customer_full_name='"<<content<<"' WHERE customer_account_no='"<<id<<"'";
    }
    break;
    case 2:
    {
        if(content.size()<8)
        {
            settextstyle(9,0,1);
            setcolor(LIGHTRED);
            outtextxy(200,420,"Password should have at least 8 characters !!");

            getch();
            closegraph();
            admin_update_insert(id, counterrr);
        }
        s<<"UPDATE customer_login SET customer_password='"<<content<<"' WHERE customer_id='"<<id<<"'";
    }
    break;
    case 3:
    {
        if(content.size()<1)
        {
            settextstyle(9,0,1);
            setcolor(LIGHTRED);
            outtextxy(200,340,"Enter a valid address !!");
            getch();
            closegraph();
            admin_update_insert(id, counterrr);
        }
        s<<"UPDATE customers SET customer_address='"<<content<<"' WHERE customer_account_no='"<<id<<"'";
    }
    break;
    case 4:
    {
        if(content[4]!='-' || content[7]!='-' || content.size()<8)
        {
            settextstyle(9,0,1);
            setcolor(LIGHTRED);
            outtextxy(140,360,"         Incorrect Format !!                            ");
            outtextxy(140,385,"Enter again....");
            getch();
            closegraph();
            admin_update_insert(id, counterrr);
        }
        char year[6];
        for(i=0; i<4; i++)
        {
            year[i]=content[i];
        }
        year[i]='\0';
        int yr=atoi(year);

        int flag=0;
        if (((yr%4==0) && (yr%100!=0)) || (yr%400==0))
            flag=1;

        time_t theTime = time(NULL);
        struct tm *aTime = localtime(&theTime);
        int current_year = aTime->tm_year + 1900;
        if(current_year-yr<18)
        {
            settextstyle(9,0,1);
            setcolor(LIGHTRED);
            outtextxy(140,360,"Not allowed for person under 18 years !!");
            getch();
            closegraph();
            admin_update_insert(id, counterrr);
        }
        char month[4];
        for(i=0; i<2; i++)
        {
            month[i]=content[i+5];
        }
        month[i]='\0';

        int mn=atoi(month);
        if(mn>12 || mn<1)
        {
            settextstyle(9,0,1);
            setcolor(LIGHTRED);
            outtextxy(140,360,"                     Invalid month !!                    ");
            getch();
            closegraph();
            admin_update_insert(id, counterrr);
        }

        char day[4];
        for(i=0; i<2; i++)
        {
            day[i]=content[i+8];
        }
        day[i]='\0';

        int dy=atoi(day);
        if(((mn==4 || mn==6 || mn==9 || mn==11) && (dy>30 || dy<1)) || ((mn==2 && flag==1) && (dy>29 || dy<1)) || ((mn==2 && flag==0) && (dy>28 || dy<1)) || ((mn==1 || mn==3 || mn==5 || mn==7 || mn==8 || mn==10 || mn==12) && (dy>31 || dy<1)))
        {
            settextstyle(9,0,1);
            setcolor(LIGHTRED);
            outtextxy(140,360,"                        Invalid day !!                        ");
            getch();
            closegraph();
            admin_update_insert(id, counterrr);
        }
        s<<"UPDATE customers SET customer_date_of_birth='"<<content<<"' WHERE customer_account_no='"<<id<<"'";
    }
    break;
    case 5:
    {
        if(content.size()!=11 || content[0]!='0' || content[1]!='1' || content[2]=='1' || content[2]=='2')
        {
            settextstyle(9,0,1);
            setcolor(LIGHTRED);
            outtextxy(140,340,"Enter a valid phone number !!");
            getch();
            closegraph();
            admin_update_insert(id, counterrr);
        }
        s<<"UPDATE customers SET customer_phone_number='"<<content<<"' WHERE customer_account_no='"<<id<<"'";
    }
    break;
    }

    string query=s.str();
    const char* q=query.c_str();
    int state;
    state=mysql_query(con, q);
    if(!state)
    {
        settextstyle(9,0,2);
        setcolor(LIGHTCYAN);
        outtextxy(200,350,"      Account Updated !!     ");
    }
    else
    {
        settextstyle(9,0,2);
        setcolor(LIGHTCYAN);
        outtextxy(200,350,"      Account was not updated !!     ");
    }

    getch();
    closegraph();
    admin_update_any_account();
}

void admin::admin_update_options(int id)
{
    initwindow(800,600);

    readimagefile("admin_menu.jpg",0,0,800,600);

    admin_update_content();
    admin_update_toggling(id);

    getch();
}

void admin::admin_update_any_account()
{
    initwindow(1000,700);

    readimagefile("passcode.jpg", 0, 0, 1000, 700);

    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);



    int state=0, line_gap=0, side_gap=0;
    state=mysql_query(con, select_cust_acc_no);//"SELECT customer_account_no FROM customers"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(line_gap>=450 && side_gap<800)
            {
                line_gap=0;
                side_gap+=100;
            }
            if(side_gap>800)
            {
                line_gap=0;
                side_gap=0;
                initwindow(1000, 700);
                readimagefile("passcode.jpg", 0, 0, 1000, 700);
            }
            settextstyle(3,0,2);
            setcolor(LIGHTBLUE);
            outtextxy(50,50,"     Exixting Account Numbers:       ");

            settextstyle(3,0,1);
            setcolor(WHITE);
            outtextxy(80+side_gap,100+line_gap,row[0]);
            line_gap+=40;
        }
    }
    setcolor(LIGHTBLUE);
    settextstyle(8,0,2);
    outtextxy(100,500,"Account Number: ");

    int id_temp[15],customer_id=0,digit,d_gap=0,i=0,j;
    char dig[3];

    setcolor(0);
    settextstyle(8,0,2);
    outtextxy(300,500," ");

    while(1)
    {
        digit=getch();
        if(digit==13)//enter press korse
            break;
        else if(digit==27)
        {
            closegraph();
            admin_menu();
        }
        else if(digit==9)
        {
            closegraph();
            admin_update_any_account();
        }
        else if(digit==8 && i==0)
        {
            setcolor(0);
            settextstyle(8,0,2);
            outtextxy(300,500," ");
        }
        else if(digit==8 && i>0)
        {
            i--;
            setcolor(15);
            settextstyle(8,0,2);
            d_gap-=12;
            outtextxy(300+d_gap,500," ");
        }
        else
        {
            id_temp[i]=digit-48;//character array te nitesi
            sprintf(dig,"%d",digit-48);
            setcolor(15);
            settextstyle(8,0,2);
            outtextxy(300+d_gap,500,dig);
            i++;
            d_gap+=12;//ak character theke next character er gap
        }
    }
    id_temp[i]='\0';
    for (j=0; j<i; j++) //int array theke normal int e convert kortesi
    {
        customer_id*=10;
        customer_id+=id_temp[j];
    }

    string customer_id_in_string;
    customer_id_in_string=to_string(customer_id);

    closegraph();

    state=mysql_query(con, select_cust_acc_no);//"SELECT customer_account_no FROM customers"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(row[0]==customer_id_in_string)
            {
                admin_update_options(customer_id);
            }
        }

        initwindow(800,400);

        readimagefile("passcode.jpg", 0, 0, 800, 400);

        settextstyle(9,0,2);
        setcolor(LIGHTCYAN);
        outtextxy(150,180,"Invalid Account Number !!");

        getch();
        closegraph();
        admin_update_any_account();
    }

    initwindow(800,400);

    readimagefile("passcode.jpg", 0, 0, 800, 400);

    settextstyle(8,0,1);
    outtextxy(200,180,"Database Error !!");

    closegraph();
    admin_update_any_account();
}

void admin::admin_view_all()
{
    initwindow(1285,780);

    readimagefile("passcode.jpg", 0, 0, 1285, 780);

    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    int state=0, line_gap=50;
    state=mysql_query(con, select_all_from_cust);//"SELECT * FROM customers"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(line_gap>=750)
            {
                line_gap=50;
                initwindow(1285,780);
                readimagefile("passcode.jpg", 0, 0, 1285, 780);
            }
            settextstyle(3,0,2);
            setcolor(LIGHTBLUE);
            outtextxy(450,50,"     CUSTOMERS' INFORMATION       ");
            settextstyle(3,0,1);
            setcolor(CYAN);
            outtextxy(10,100,"Account Number");
            outtextxy(180,100,"Full Name");
            outtextxy(380,100,"Username");
            outtextxy(620,100,"Address");
            outtextxy(840,100,"Date of Birth");
            outtextxy(975,100,"Phone Number");
            outtextxy(1150,100,"Created on");

            settextstyle(3,0,1);
            setcolor(WHITE);
            outtextxy(30,100+line_gap,row[0]);
            outtextxy(160,100+line_gap,row[1]);
            outtextxy(340,100+line_gap,row[2]);
            outtextxy(510,100+line_gap,row[3]);
            outtextxy(840,100+line_gap,row[4]);
            outtextxy(980,100+line_gap,row[5]);
            outtextxy(1120,100+line_gap,row[6]);
            line_gap+=40;
        }
        getch();
        closegraph();
        admin_menu();
    }

    settextstyle(8,0,1);
    outtextxy(200,240,"Database Error !!");

    closegraph();
    admin_view_all();
}

void admin::admin_view_balance()
{
    initwindow(1285,780);

    readimagefile("passcode.jpg", 0, 0, 1285, 780);

    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    int state=0,line_gap=50;
    state=mysql_query(con, select_all_from_cust_baln);//"SELECT * FROM customer_balance"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(line_gap>=750)
            {
                line_gap=50;
                initwindow(1285,780);
                readimagefile("passcode.jpg", 0, 0, 1285, 780);
            }
            settextstyle(3,0,2);
            setcolor(LIGHTBLUE);
            outtextxy(300,50,"     CUSTOMERS' ACCOUNT BALANCE       ");
            settextstyle(3,0,1);
            setcolor(CYAN);
            outtextxy(10,100,"Account Number");
            outtextxy(180,100,"Full Name");
            outtextxy(360,100,"Balance");
            outtextxy(520,100,"Last Deposited Amount");
            outtextxy(740,100,"Last Deposited Date");
            outtextxy(905,100,"Last Withdrawal Amount");
            outtextxy(1100,100,"Last Withdrawal Date");

            settextstyle(3,0,1);
            setcolor(WHITE);
            outtextxy(330,100+line_gap,"Tk.  ");
            outtextxy(540,100+line_gap,"Tk.  ");
            outtextxy(925,100+line_gap,"Tk.  ");
            outtextxy(30,100+line_gap,row[0]);
            outtextxy(160,100+line_gap,row[1]);
            outtextxy(355,100+line_gap,row[2]);
            outtextxy(565,100+line_gap,row[3]);
            outtextxy(740,100+line_gap,row[4]);
            outtextxy(950,100+line_gap,row[5]);
            outtextxy(1100,100+line_gap,row[6]);
            line_gap+=40;
        }
        getch();
        closegraph();
        admin_menu();
    }

    settextstyle(8,0,1);
    outtextxy(200,240,"Database Error !!");

    closegraph();
    admin_view_balance();
}




