#include "customer.h"
#include <graphics.h>
#include <conio.h>
#include<windows.h>
#include<mysql.h>
#include<sstream>
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
int customer::customer_count_login=0;
int customer::counterr=1;
int customer::count_login_pass=0;
int customer::delete_op=1;

void customer::first_window()
{
    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    initwindow(600,400);

    readimagefile("admin_login.jpg", 0, 0, 600, 400);

    settextstyle(9,0,3);
    setcolor(LIGHTCYAN);
    outtextxy(140,50,"      Customer Login     ");

    settextstyle(9,0,2);
    setcolor(LIGHTBLUE);
    outtextxy(40,150,"Account Number: ");

    settextstyle(9,0,1);
    setcolor(LIGHTCYAN);
    outtextxy(130,230,"          Create New Account            ");

    //new account create korar jonno

    char ch;
    int c_customer=7;

    do
    {
        ch=getch();
        switch(ch)
        {
        case 72://upore uthbe
            c_customer--;
            if(c_customer<7)
            {
                c_customer=8;
            }
            settextstyle(9,0,1);
            setcolor(LIGHTCYAN);
            outtextxy(130,230,"          Create New Account          ");
            intro_select(c_customer);
            continue;
        case 80://niche nambe
            c_customer++;
            if(c_customer>8)
            {
                c_customer=7;
            }
            settextstyle(9,0,1);
            setcolor(LIGHTCYAN);
            outtextxy(130,230,"          Create New Account          ");
            intro_select(c_customer);
            continue;
        case 13://enter press korbe
            break;
        }
    }
    while(ch!=13);

    if(c_customer==8)
    {
        closegraph();
        customer_create_new();
    }

    //customer_id er jonno
    int id_temp[15],digit,d_gap=0,i=0,j;
    customer_id=0;
    char dig[3];

    setcolor(0);
    settextstyle(8,0,2);
    outtextxy(290,150," ");

    while(1)
    {
        digit=getch();
        if(digit==13)//enter press korse
            break;
        else if(digit==27)
        {
            closegraph();
            intro();
        }
        else if(digit==9)
        {
            closegraph();
            first_window();
        }
        else if(digit==8 && i==0)
        {
            setcolor(0);
            settextstyle(8,0,2);
            outtextxy(290,150," ");
        }
        else if(digit==8 && i>0)
        {
            i--;
            setcolor(15);
            settextstyle(8,0,2);
            d_gap-=12;
            outtextxy(290+d_gap,150," ");
        }
        else
        {
            id_temp[i]=digit-48;//character array te nitesi
            sprintf(dig,"%d",digit-48);
            setcolor(15);
            settextstyle(8,0,2);
            outtextxy(290+d_gap,150,dig);
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

    int state=0;
    state=mysql_query(con,select_cust_id);//"SELECT customer_id FROM customer_login"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(row[0]==customer_id_in_string)
            {
                closegraph();
                customer_login_pass(customer_id);
            }
        }
        settextstyle(8,0,1);
        outtextxy(160,260,"Invalid Account Number !!");

        getch();
        closegraph();
        customer_count_login++;
        if(customer_count_login<3)
        {
            first_window(); //at least 3 bar chance pabe customer_username r password dui tai thik moto input dewar jonno
        }
        else
        {
            customer_count_login=0;
            intro();
        }
    }
    settextstyle(8,0,1);
    outtextxy(200,240,"Database Error !!");

    getch();
    customer_count_login++;
    if(customer_count_login<3)
    {
        first_window(); //at least 3 bar chance pabe customer_username r password dui tai thik moto input dewar jonno
    }
    else
    {
        customer_count_login=0;
        intro();
    }
}

void customer::customer_menu(int id)
{
    initwindow(800,600);

    readimagefile("admin_menu.jpg",0,0,800,600);

    customer_menu_content();
    menu_toggling(id);

    getch();
}

void customer::menu_toggling(int id)
{
    char ch;
    customer_menu_content();
    customer_menu_select(counterr);
    do
    {
        ch=getch();
        switch(ch)
        {
        case 72://upore uthbe
            counterr--;
            if(counterr==0)
            {
                counterr=5;
            }
            customer_menu_content();
            customer_menu_select(counterr);
            continue;
        case 80://niche nambe
            counterr++;
            if(counterr==6)
            {
                counterr=1;
            }
            customer_menu_content();
            customer_menu_select(counterr);
            continue;
        case 13://enter press korbe
            break;
        }
    }
    while(ch!=13);
    switch(counterr)
    {
    case 1:
        closegraph();
        customer_update_options(id);
        break;
    case 2:
        closegraph();
        customer_view_information(id);
        break;
    case 3:
        closegraph();
        customer_delete_account(id);
        break;
    case 4:
        closegraph();
        customer_transaction(id);
        break;
    case 5:
        closegraph();
        logout();
        intro();
        break;
    }
}

void customer::customer_login_pass(int customer_id)
{
    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    initwindow(600,400);

    readimagefile("admin_login.jpg", 0, 0, 600, 400);

    setcolor(LIGHTBLUE);
    settextstyle(9,0,2);
    outtextxy(40,160,"Password: ");

    //customer er password er jonno
    char customer_password_temp[20], chrctr;
    int star_gap=0,i=0,j=0;
    customer_password="";


    setcolor(0);
    settextstyle(8,0,3);
    outtextxy(200,160," ");

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
            customer_login_pass(customer_id);
        }
        else if(chrctr==8 && i==0)
        {
            setcolor(0);
            settextstyle(8,0,3);
            outtextxy(200,160," ");
        }
        else if(chrctr==8 && i>0)
        {
            i--;
            setcolor(15);
            settextstyle(8,0,3);
            star_gap-=20;
            outtextxy(200+star_gap,160," ");
        }
        else
        {
            customer_password_temp[i]=chrctr;//character array te nitesi
            setcolor(15);
            settextstyle(8,0,3);
            outtextxy(200+star_gap,160,"*");
            i++;
            star_gap+=20;//ak star theke next star er gap
        }
    }
    customer_password_temp[i]='\0';
    for(j=0; j<i; j++) //character array theke string e nitesi
    {
        customer_password=customer_password+customer_password_temp[j];
    }

    string customer_id_in_string;
    customer_id_in_string=to_string(customer_id);

    int state=0;
    state=mysql_query(con,select_cust_id_pass);//"SELECT customer_id,customer_password FROM customer_login"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(row[0]==customer_id_in_string)
            {
                if(row[1]==customer_password)
                {
                    closegraph();
                    count_login_pass=0;
                    loading();
                    customer_menu(customer_id);
                }
                else
                {
                    settextstyle(8,0,1);
                    outtextxy(160,260,"Password Incorrect !!");

                    getch();
                    closegraph();
                    count_login_pass++;
                    if(count_login_pass<3)
                    {
                        customer_login_pass(customer_id); //at least 3 bar chance pabe customer_username r password dui tai thik moto input dewar jonno
                    }
                    else
                    {
                        count_login_pass=0;
                        first_window();
                    }
                }
            }
        }
    }
    settextstyle(8,0,1);
    outtextxy(200,240,"Database Error !!");

    getch();
    count_login_pass++;
    if(count_login_pass<3)
    {
        customer_login_pass(customer_id); //at least 3 bar chance pabe customer_username r password dui tai thik moto input dewar jonno
    }
    else
    {
        count_login_pass=0;
        first_window();
    }
}

void customer::customer_create_new()
{
    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    initwindow(1200,700);

    readimagefile("admin_login.jpg", 0, 0, 1200, 700);

    int state;
    char dig[12];
    state=mysql_query(con,select_max_acc_no);//"SELECT MAX(customer_account_no) FROM customers"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(row[0]==NULL)
            {
                customer_id=180041101;
            }
            else
            {
                customer_id=atoi(row[0])+1;
            }
        }
    }

    settextstyle(9,0,3);
    setcolor(LIGHTCYAN);
    outtextxy(300,50,"      Create Account     ");

    //customer_fullname er jonno
p:
    settextstyle(9,0,2);
    setcolor(LIGHTBLUE);
    outtextxy(80,100,"Account Number: ");
    sprintf(dig,"%d",customer_id);
    setcolor(WHITE);
    outtextxy(380,100,dig);

    //customer_fullname er jonno
    settextstyle(9,0,2);
    setcolor(LIGHTBLUE);
    outtextxy(80,150,"Full Name: ");

    char chrctr,str[3],fullname_temp[30];
    int c_gap=0,i=0,j;
    stringstream s;



    setcolor(0);
    settextstyle(8,0,2);
    outtextxy(290,150," ");

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
            customer_create_new();
        }
        else if(chrctr==8 && i==0)
        {
            setcolor(0);
            settextstyle(8,0,2);
            outtextxy(290,150," ");
        }
        else if(chrctr==8 && i>0)
        {
            i--;
            setcolor(15);
            settextstyle(8,0,2);
            c_gap-=14;
            outtextxy(290+c_gap,150," ");
        }
        else
        {
            fullname_temp[i]=chrctr;//character array te nitesi
            sprintf(str,"%c",chrctr);
            setcolor(15);
            settextstyle(8,0,2);
            outtextxy(290+c_gap,150,str);
            i++;
            c_gap+=14;//ak character theke next character er gap
        }
    }
    fullname_temp[i]='\0';
    for(j=0; j<i; j++) //character array theke string e nitesi
    {
        customer_fullname=customer_fullname+fullname_temp[j];
    }
    if(customer_fullname.size()<1)
    {
        settextstyle(9,0,1);
        setcolor(LIGHTRED);
        outtextxy(720,150,"Enter a valid name !!");
        setcolor(0);
        settextstyle(8,0,2);
        outtextxy(290,150," ");
        goto p;
    }

    //customer_address er jonno
q:
    settextstyle(9,0,2);
    setcolor(LIGHTBLUE);
    outtextxy(80,200,"Address: ");

    char address_temp[30];
    c_gap=0;
    i=0;
    string customer_address="";

    setcolor(0);
    settextstyle(8,0,2);
    outtextxy(290,200," ");

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
            customer_create_new();
        }
        else if(chrctr==8 && i==0)
        {
            setcolor(0);
            settextstyle(8,0,2);
            outtextxy(290,200," ");
        }
        else if(chrctr==8 && i>0)
        {
            i--;
            setcolor(15);
            settextstyle(8,0,2);
            c_gap-=14;
            outtextxy(290+c_gap,200," ");
        }
        else
        {
            address_temp[i]=chrctr;//character array te nitesi
            sprintf(str,"%c",chrctr);
            setcolor(15);
            settextstyle(8,0,2);
            outtextxy(290+c_gap,200,str);
            i++;
            c_gap+=14;//ak character theke next character er gap
        }
    }
    address_temp[i]='\0';
    for(j=0; j<i; j++) //character array theke string e nitesi
    {
        customer_address=customer_address+address_temp[j];
    }
    if(customer_address.size()<1)
    {
        settextstyle(9,0,1);
        setcolor(LIGHTRED);
        outtextxy(720,200,"Enter a valid address !!");
        setcolor(0);
        settextstyle(8,0,2);
        outtextxy(290,200," ");
        goto q;
    }

    //customer_dob er jonno
r:
    settextstyle(9,0,2);
    setcolor(LIGHTBLUE);
    outtextxy(80,250,"Date of Birth: ");
    settextstyle(9,0,1);
    outtextxy(80,270,"[YYYY-MM-DD]");

    char dob_temp[30];
    c_gap=0;
    i=0;
    string customer_dob="";

    setcolor(0);
    settextstyle(8,0,2);
    outtextxy(290,250," ");

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
            customer_create_new();
        }
        else if(chrctr==8 && i==0)
        {
            setcolor(0);
            settextstyle(8,0,2);
            outtextxy(290,250," ");
        }
        else if(chrctr==8 && i>0)
        {
            i--;
            setcolor(15);
            settextstyle(8,0,2);
            c_gap-=14;
            outtextxy(290+c_gap,250," ");
        }
        else
        {
            dob_temp[i]=chrctr;//character array te nitesi
            sprintf(str,"%c",chrctr);
            setcolor(15);
            settextstyle(8,0,2);
            outtextxy(290+c_gap,250,str);
            i++;
            c_gap+=14;//ak character theke next character er gap
        }
    }
    dob_temp[i]='\0';
    for(j=0; j<i; j++) //character array theke string e nitesi
    {
        customer_dob=customer_dob+dob_temp[j];
    }
    if(customer_dob[4]!='-' || customer_dob[7]!='-' || customer_dob.size()<8)
    {
        settextstyle(9,0,1);
        setcolor(LIGHTRED);
        outtextxy(720,250,"         Incorrect Format !!                            ");
        outtextxy(720,275,"Enter again....");
        setcolor(0);
        settextstyle(8,0,2);
        outtextxy(290,250,"           ");
        goto r;
    }
    char year[6];
    for(i=0; i<4; i++)
    {
        year[i]=customer_dob[i];
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
        outtextxy(720,250,"Not allowed for person under 18 years !!");
        setcolor(0);
        settextstyle(8,0,2);
        outtextxy(290,250,"            ");
        goto r;
    }
    char month[4];
    for(i=0; i<2; i++)
    {
        month[i]=customer_dob[i+5];
    }
    month[i]='\0';

    int mn=atoi(month);
    if(mn>12 || mn<1)
    {
        settextstyle(9,0,1);
        setcolor(LIGHTRED);
        outtextxy(720,250,"                     Invalid month !!                    ");
        setcolor(0);
        settextstyle(8,0,2);
        outtextxy(290,250,"            ");
        goto r;
    }

    char day[4];
    for(i=0; i<2; i++)
    {
        day[i]=customer_dob[i+8];
    }
    day[i]='\0';

    int dy=atoi(day);
    if(((mn==4 || mn==6 || mn==9 || mn==11) && (dy>30 || dy<1)) || ((mn==2 && flag==1) && (dy>29 || dy<1)) || ((mn==2 && flag==0) && (dy>28 || dy<1)) || ((mn==1 || mn==3 || mn==5 || mn==7 || mn==8 || mn==10 || mn==12) && (dy>31 || dy<1)))
    {
        settextstyle(9,0,1);
        setcolor(LIGHTRED);
        outtextxy(720,250,"                        Invalid day !!                        ");
        setcolor(0);
        settextstyle(8,0,2);
        outtextxy(290,250,"            ");
        goto r;
    }

    //customer_phone er jonno
s:
    settextstyle(9,0,2);
    setcolor(LIGHTBLUE);
    outtextxy(80,300,"Phone Number: ");

    char phone_temp[30];
    c_gap=0;
    i=0;
    string customer_phone="";

    setcolor(0);
    settextstyle(8,0,2);
    outtextxy(290,300," ");

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
            customer_create_new();
        }
        else if(chrctr==8 && i==0)
        {
            setcolor(0);
            settextstyle(8,0,2);
            outtextxy(290,300," ");
        }
        else if(chrctr==8 && i>0)
        {
            i--;
            setcolor(15);
            settextstyle(8,0,2);
            c_gap-=14;
            outtextxy(290+c_gap,300," ");
        }
        else
        {
            phone_temp[i]=chrctr;//character array te nitesi
            sprintf(str,"%c",chrctr);
            setcolor(15);
            settextstyle(8,0,2);
            outtextxy(290+c_gap,300,str);
            i++;
            c_gap+=14;//ak character theke next character er gap
        }
    }
    phone_temp[i]='\0';
    for(j=0; j<i; j++) //character array theke string e nitesi
    {
        customer_phone=customer_phone+phone_temp[j];
    }
    if(customer_phone.size()!=11 || customer_phone[0]!='0' || customer_phone[1]!='1' || customer_phone[2]=='1' || customer_phone[2]=='2')
    {
        settextstyle(9,0,1);
        setcolor(LIGHTRED);
        outtextxy(720,300,"Enter a valid phone number !!");
        setcolor(0);
        settextstyle(8,0,2);
        outtextxy(290,300,"                 ");
        goto s;
    }

    //customer_balance er jonno
t:
    settextstyle(9,0,2);
    setcolor(LIGHTBLUE);
    outtextxy(80,350,"Initial Deposit: ");
    setcolor(15);
    outtextxy(290,350,"Tk.  ");

    char balance_temp[30];
    c_gap=0;
    i=0;
    string customer_balance="";

    setcolor(0);
    settextstyle(8,0,2);
    outtextxy(340,350," ");

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
            customer_create_new();
        }
        else if(chrctr==8 && i==0)
        {
            setcolor(0);
            settextstyle(8,0,2);
            outtextxy(340,350," ");
        }
        else if(chrctr==8 && i>0)
        {
            i--;
            setcolor(15);
            settextstyle(8,0,2);
            c_gap-=14;
            outtextxy(340+c_gap,350," ");
        }
        else
        {
            balance_temp[i]=chrctr;//character array te nitesi
            sprintf(str,"%c",chrctr);
            setcolor(15);
            settextstyle(8,0,2);
            outtextxy(340+c_gap,350,str);
            i++;
            c_gap+=14;//ak character theke next character er gap
        }
    }
    balance_temp[i]='\0';
    for(j=0; j<i; j++) //character array theke string e nitesi
    {
        customer_balance=customer_balance+balance_temp[j];
    }

    double balance=stold(customer_balance);
    if(balance<1500)
    {
        settextstyle(9,0,1);
        setcolor(LIGHTRED);
        outtextxy(720,350,"You have to deposit at least Tk. 1500. !!");
        setcolor(0);
        settextstyle(8,0,2);
        outtextxy(340,350,"             ");
        goto t;
    }

    settextstyle(10,0,4);
    setcolor(LIGHTRED);
    outtextxy(200,500,"Please Note Down Your Account Number !!");
    getch();
    closegraph();
    customer_user(customer_id, customer_fullname, customer_address, customer_dob, customer_phone, customer_balance);

    getch();
}
void customer::customer_user(int customer_id, string customer_fullname, string customer_address, string customer_dob, string customer_phone, string customer_balance)
{
    initwindow(800,400);

    readimagefile("passcode.jpg", 0, 0, 800, 400);

    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    //customer_username er jonno
    settextstyle(9,0,2);
    setcolor(LIGHTBLUE);
    outtextxy(140,150,"Username: ");

    char username_temp[30], chrctr, str[3];
    int c_gap=0,i=0,j;
    string customer_username="";

    setcolor(0);
    settextstyle(8,0,2);
    outtextxy(290,150," ");

    while(1)
    {
        chrctr=getch();
        if(chrctr=='\r')//enter press korse
            break;
        else if(chrctr==27)
        {
            closegraph();
            customer_create_new();
        }
        else if(chrctr==9)
        {
            closegraph();
            customer_user(customer_id, customer_fullname, customer_address, customer_dob, customer_phone, customer_balance);
        }
        else if(chrctr==8 && i==0)
        {
            setcolor(0);
            settextstyle(8,0,2);
            outtextxy(290,150," ");
        }
        else if(chrctr==8 && i>0)
        {
            i--;
            setcolor(15);
            settextstyle(8,0,2);
            c_gap-=14;
            outtextxy(290+c_gap,150," ");
        }
        else
        {
            username_temp[i]=chrctr;//character array te nitesi
            sprintf(str,"%c",chrctr);
            setcolor(15);
            settextstyle(8,0,2);
            outtextxy(290+c_gap,150,str);
            i++;
            c_gap+=14;//ak character theke next character er gap
        }
    }
    username_temp[i]='\0';
    for(j=0; j<i; j++) //character array theke string e nitesi
    {
        customer_username=customer_username+username_temp[j];
    }
    if(customer_username.size()<4)
    {
        settextstyle(9,0,1);
        setcolor(LIGHTRED);
        outtextxy(150,250,"Username should have at least 4 characters !!");

        getch();
        closegraph();
        customer_user(customer_id, customer_fullname, customer_address, customer_dob, customer_phone, customer_balance);
    }

    int state=0;
    state=mysql_query(con,select_cust_username);//"SELECT customer_username FROM customers"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(row[0]==customer_username)
            {
                outtextxy(250,250,"Username exists.");
                outtextxy(200,280,"Select different Username !!");

                getch();
                closegraph();
                customer_user(customer_id, customer_fullname, customer_address, customer_dob, customer_phone, customer_balance);
            }
        }
        closegraph();
        customer_pass(customer_id, customer_fullname, customer_username, customer_address, customer_dob, customer_phone, customer_balance);
    }
    settextstyle(8,0,1);
    outtextxy(200,240,"Database Error !!");

    closegraph();
    customer_user(customer_id, customer_fullname, customer_address, customer_dob, customer_phone, customer_balance);
}

void customer::customer_pass(int customer_id, string customer_fullname, string customer_username, string customer_address, string customer_dob, string customer_phone, string customer_balance)
{
    initwindow(800,400);

    readimagefile("passcode.jpg", 0, 0, 800, 400);

    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    //password er jonno
    setcolor(LIGHTBLUE);
    settextstyle(9,0,2);
    outtextxy(140,160,"Password: ");

    char customer_password_temp[20], chrctr;
    int star_gap=0, i=0, j;
    string customer_password="";

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
            customer_user(customer_id, customer_fullname, customer_address, customer_dob, customer_phone, customer_balance);
        }
        else if(chrctr==9)
        {
            closegraph();
            customer_pass(customer_id, customer_fullname, customer_username, customer_address, customer_dob, customer_phone, customer_balance);
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
            customer_password_temp[i]=chrctr;//character array te nitesi
            setcolor(15);
            settextstyle(8,0,3);
            outtextxy(290+star_gap,160,"*");
            i++;
            star_gap+=20;//ak star theke next star er gap
        }
    }
    customer_password_temp[i]='\0';
    for(j=0; j<i; j++) //character array theke string e nitesi
    {
        customer_password=customer_password+customer_password_temp[j];
    }
    if(customer_password.size()<8)
    {
        settextstyle(9,0,1);
        setcolor(LIGHTRED);
        outtextxy(150,300,"Password should have at least 8 characters !!");

        getch();
        closegraph();
        customer_pass(customer_id, customer_fullname, customer_username, customer_address, customer_dob, customer_phone, customer_balance);
    }

    //password confirm korar jonno
    setcolor(LIGHTBLUE);
    settextstyle(9,0,2);
    outtextxy(140,220,"Confirm Password: ");

    char confirm_password_temp[20];
    star_gap=0;
    i=0;
    string confirm_password="";

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
            customer_user(customer_id, customer_fullname, customer_address, customer_dob, customer_phone, customer_balance);
        }
        else if(chrctr==9)
        {
            closegraph();
            customer_pass(customer_id, customer_fullname, customer_username, customer_address, customer_dob, customer_phone, customer_balance);
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


    if(customer_password==confirm_password)
    {
        stringstream s;
        stringstream ss;
        stringstream sss;
        s<<"INSERT INTO customers VALUES("<<customer_id<<", '"<<customer_fullname<<"', '"<<customer_username<<"', '"<<customer_address<<"', '"<<customer_dob<<"', '"<<customer_phone<<"', NOW())";
        ss<<"INSERT INTO customer_login VALUES("<<customer_id<<", '"<<customer_password<<"')";
        sss<<"INSERT INTO customer_balance VALUES ("<<customer_id<<", '"<<customer_fullname<<"', '"<<customer_balance<<"', '0.0', NOW(), '0.0', '')";
        string query=s.str();
        string queries=ss.str();
        string queriess=sss.str();
        const char* q=query.c_str();
        const char* p=queries.c_str();
        const char* o=queriess.c_str();
        int state=0, states=0, statess=0;
        state=mysql_query(con, q);
        states=mysql_query(con, p);
        statess=mysql_query(con, o);
        if(state==0 && states==0 && statess==0)
        {
            settextstyle(9,0,1);
            setcolor(LIGHTCYAN);
            outtextxy(180,330,"          Account Created !!            ");

            getch();
            closegraph();
            first_window();
        }
    }
    else
    {
        settextstyle(9,0,1);
        setcolor(LIGHTCYAN);
        outtextxy(140,300,"          Password didn't match !!            ");

        getch();
        closegraph();
        customer_pass(customer_id, customer_fullname, customer_username, customer_address, customer_dob, customer_phone, customer_balance);
    }
    settextstyle(8,0,1);
    outtextxy(200,240,"Database Error !!");

    closegraph();
    customer_pass(customer_id, customer_fullname, customer_username, customer_address, customer_dob, customer_phone, customer_balance);
}

void customer::customer_menu_select(int val) //Text gula toggling er shomoy boro korbe
{
    switch(val)
    {
    case 1:
        settextstyle(9,0,3);
        setcolor(CYAN);
        outtextxy(90,120,"1. Update Information    ");
        settextstyle(9,0,3);
        outtextxy(50,120,">>");
        break;
    case 2:
        settextstyle(9,0,3);
        setcolor(CYAN);
        outtextxy(140,180,"2. View Information     ");
        settextstyle(9,0,3);
        outtextxy(100,180,">>");
        break;
    case 3:
        settextstyle(9,0,3);
        setcolor(CYAN);
        outtextxy(190,240,"3. Delete Account        ");
        settextstyle(9,0,3);
        outtextxy(150,240,">>");
        break;
    case 4:
        settextstyle(9,0,3);
        setcolor(CYAN);
        outtextxy(240,300,"4. Transaction    ");
        settextstyle(9,0,3);
        outtextxy(200,300,">>");
        break;
    case 5:
        settextstyle(9,0,3);
        setcolor(CYAN);
        outtextxy(290,360,"5. Log Out    ");
        settextstyle(9,0,3);
        outtextxy(250,360,">>");
        break;
    }
}
void customer::customer_menu_content()
{
    settextstyle(9,0,2);
    setcolor(CYAN);
    outtextxy(50,120,"     1. Update Information       ");
    outtextxy(100,180,"     2. View Information        ");
    outtextxy(150,240,"     3. Delete Account          ");
    outtextxy(200,300,"     4. Transaction      ");
    outtextxy(250,360,"     5. Log Out     ");
}

void customer::customer_update_content_select(int val) //Text gula toggling er shomoy boro korbe
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

void customer::customer_update_content()
{
    settextstyle(9,0,2);
    setcolor(CYAN);
    outtextxy(50,120,"     Full Name      ");
    outtextxy(100,180,"     Password       ");
    outtextxy(150,240,"     Address     ");
    outtextxy(200,300,"     Date of Birth      ");
    outtextxy(250,360,"     Phone Number     ");
}

void customer::customer_update_toggling(int id)
{
    char ch;
    static int counterrrr=1;

    customer_update_content();
    customer_update_content_select(counterrrr);
    do
    {
        ch=getch();
        switch(ch)
        {
        case 72://upore uthbe
            counterrrr--;
            if(counterrrr==0)
            {
                counterrrr=5;
            }
            customer_update_content();
            customer_update_content_select(counterrrr);
            continue;
        case 80://niche nambe
            counterrrr++;
            if(counterrrr==6)
            {
                counterrrr=1;
            }
            customer_update_content();
            customer_update_content_select(counterrrr);
            continue;
        case 27:
            closegraph();
            customer_menu(id);
            break;
        case 13://enter press korbe
            break;
        }
    }
    while(ch!=13);

    closegraph();
    customer_update_insert(id, counterrrr);
}

void customer::customer_update_insert(int id, int counterrrr)
{
    initwindow(800,600);

    readimagefile("admin_menu.jpg",0,0,800,600);

    switch(counterrrr)
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
            customer_update_options(id);
        }
        else if(chrctr==9)
        {
            closegraph();
            customer_update_insert(id, counterrrr);
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

    switch(counterrrr)
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
            customer_update_insert(id, counterrrr);
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
            customer_update_insert(id, counterrrr);
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
            customer_update_insert(id, counterrrr);
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
            customer_update_insert(id, counterrrr);
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
            customer_update_insert(id, counterrrr);
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
            customer_update_insert(id, counterrrr);
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
            customer_update_insert(id, counterrrr);
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
            customer_update_insert(id, counterrrr);
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
    customer_menu(id);
}

void customer::customer_update_options(int id)
{
    initwindow(800,600);

    readimagefile("admin_menu.jpg",0,0,800,600);

    customer_update_content();
    customer_update_toggling(id);

    getch();
}

void customer::customer_view_information(int id)
{
    initwindow(1000,700);

    readimagefile("passcode.jpg", 0, 0, 1000, 700);

    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    settextstyle(9,0,3);
    setcolor(LIGHTBLUE);
    outtextxy(350,50,"      INFORMATION       ");
    settextstyle(9,0,1);
    setcolor(CYAN);
    outtextxy(100,150,"Account Number:");
    outtextxy(100,200,"Full Name:");
    outtextxy(100,250,"Username:");
    outtextxy(100,300,"Address:");
    outtextxy(100,350,"Date of Birth:");
    outtextxy(100,400,"Phone Number:");
    outtextxy(100,450,"Created on:");
    outtextxy(100,500,"Account Balance:");
    outtextxy(100,550,"Last Deposit:");
    outtextxy(580,550,"on");
    outtextxy(100,600,"Last Withdraw:");
    outtextxy(580,600,"on");

    string id_in_string=to_string(id);

    int state=0, states=0;
    state=mysql_query(con,select_all_from_cust);//"SELECT * FROM customers"

    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(row[0]==id_in_string)
            {
                settextstyle(9,0,1);
                setcolor(WHITE);
                outtextxy(300,150,row[0]);
                outtextxy(300,200,row[1]);
                outtextxy(300,250,row[2]);
                outtextxy(300,300,row[3]);
                outtextxy(300,350,row[4]);
                outtextxy(300,400,row[5]);
                outtextxy(300,450,row[6]);
            }
        }
        states=mysql_query(con,select_all_from_cust_balance);//"SELECT * FROM customer_balance"
        if(!states)
        {
            res=mysql_store_result(con);
            while(row=mysql_fetch_row(res))
            {
                if(row[0]==id_in_string)
                {
                    settextstyle(9,0,1);
                    setcolor(WHITE);
                    outtextxy(300,500,"Tk.  ");
                    outtextxy(340,500,row[2]);
                    outtextxy(300,550,"Tk.  ");
                    outtextxy(340,550,row[3]);
                    outtextxy(620,550,row[4]);
                    outtextxy(300,600,"Tk.  ");
                    outtextxy(340,600,row[5]);
                    outtextxy(620,600,row[6]);
                }
            }
        }

        getch();
        closegraph();
        customer_menu(id);
    }

    settextstyle(8,0,1);
    outtextxy(200,240,"Database Error !!");

    closegraph();
    customer_view_information(id);
}

void customer::delete_select(int val) //Text gula toggling er shomoy boro korbe
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

void customer::delete_option()
{
    settextstyle(9,0,3);
    setcolor(WHITE);
    outtextxy(270,153,"      Yes  ");
    outtextxy(320,203,"      No ");
}

void customer::delete_choose(int id)//upore niche move korbe
{
    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    char ch;
    delete_option();
    delete_select(delete_op);
    do
    {
        ch=getch();
        switch(ch)
        {
        case 72://upore uthbe
            delete_op--;
            if(delete_op==0)
            {
                delete_op=2;
            }
            delete_option();
            delete_select(delete_op);
            continue;
        case 80://niche nambe
            delete_op++;
            if(delete_op==3)
            {
                delete_op=1;
            }
            delete_option();
            delete_select(delete_op);
            continue;
        case 13://enter press korbe
            break;
        }
    }
    while(ch!=13);

    switch(delete_op)
    {
    case 1:
        {
            stringstream ssss;
            stringstream sssss;
            string id_in_string=to_string(id);
            int state,states;
            state=mysql_query(con,select_all_from_cust);//"SELECT * FROM customers"
            if(!state)
            {
                res=mysql_store_result(con);
                while(row=mysql_fetch_row(res))
                {
                    if(row[0]==id_in_string)
                    {
                        ssss<<"INSERT INTO customer_delete_request_information VALUES("<<id<<", '"<<row[1]<<"', '"<<row[2]<<"', '"<<row[3]<<"', '"<<row[4]<<"', '"<<row[5]<<"', '"<<row[6]<<"')";
                        string queryyy=ssss.str();
                        const char* a=queryyy.c_str();
                        state=mysql_query(con, a);
                        break;
                    }
                }
            }
            states=mysql_query(con,select_all_from_cust_balance);//"SELECT * FROM customer_balance"
            if(!states)
            {
                res=mysql_store_result(con);
                while(row=mysql_fetch_row(res))
                {
                    if(row[0]==id_in_string)
                    {
                        sssss<<"INSERT INTO customer_delete_request_balance VALUES ("<<id<<", '"<<row[1]<<"', '"<<row[2]<<"', '"<<row[3]<<"', '"<<row[4]<<"', '"<<row[5]<<"', '"<<row[6]<<"')";
                        string queryyyy=sssss.str();
                        const char* b=queryyyy.c_str();
                        states=mysql_query(con, b);
                        break;
                    }
                }
            }

            if(!state && !states)
            {
                settextstyle(9,0,2);
                setcolor(LIGHTCYAN);
                outtextxy(200,270,"      Account will be deleted soon !!     ");

                getch();
                closegraph();
                first_window();
            }
            else
            {
                settextstyle(9,0,2);
                setcolor(LIGHTCYAN);
                outtextxy(100,270,"      Already requested earlier to delete the account  !!     ");

                getch();
                closegraph();
                customer_menu(id);
            }
        }
        break;
    case 2:
        closegraph();
        customer_menu(id);
        break;
    }
}

void customer::customer_delete_account(int id)
{
    initwindow(800,400);

    readimagefile("passcode.jpg", 0, 0, 800, 400);

    settextstyle(9,0,2);
    setcolor(LIGHTCYAN);
    outtextxy(150,100,"Are you sure to delete the account ?!");

    delete_option();
    delete_choose(id);
}

void common::logout()
{
    int x=190,i,y=440;
    initwindow(640,500);

    setcolor(3);
    rectangle(185,155,445,185); //console e uporer hollow rectangle ta

    setcolor(3);
    rectangle(185,235,445,265); //console e nicher hollow rectangle ta

    setcolor(WHITE);
    settextstyle(9,0,3);
    //settextstyle(font,direction of text,size of letters)
    outtextxy(190,200,"LOGGING OUT !!");

    setcolor(11);
    settextstyle(4,0,2);
    outtextxy(200,240,"PLEASE WAIT");

    for(i=0; i<=125; i++)
    {
        delay(25);
        line(x,240,x,260); //console e nicher loading line ta
        line(y,160,y,180); //console e uporer loading line ta
        //last er 2 ta line na likhe ebhabeo likha jaito
        //line(x+=2,240,x,260)
        //line(y-=2,160,y,180
        y-=2;
        x+=2;
    }

    setcolor(15);
    settextstyle(8,0,1);
    outtextxy(152,300,"PRESS ANY KEY TO CONTINUE.... ");

    getch();
    closegraph();
}

void customer::balance_select(int val) //Text gula toggling er shomoy boro korbe
{
    switch(val)
    {
    case 1:
        settextstyle(9,0,3);
        setcolor(LIGHTCYAN);
        outtextxy(360,260," Deposit ");
        settextstyle(9,0,2);
        outtextxy(325,265,">>");
        break;
    case 2:
        settextstyle(9,0,3);
        setcolor(LIGHTCYAN);
        outtextxy(410,350," Withdraw ");
        settextstyle(9,0,2);
        outtextxy(375,355,">>");
        break;
    }
}

void customer::balance_content()
{
    settextstyle(9,0,2);
    setcolor(LIGHTCYAN);
    outtextxy(325,261,"      Deposit     ");
    outtextxy(375,351,"      Withdraw     ");
}

void customer::balance_toggling(int customer_id)//upore niche move korbe
{
    char ch;
    static int countttt=1;
    balance_content();
    balance_select(countttt);
    do
    {
        ch=getch();
        switch(ch)
        {
        case 72://upore uthbe
            countttt--;
            if(countttt==0)
            {
                countttt=2;
            }
            balance_content();
            balance_select(countttt);
            continue;
        case 80://niche nambe
            countttt++;
            if(countttt==3)
            {
                countttt=1;
            }
            balance_content();
            balance_select(countttt);
            continue;
        case 27:
            closegraph();
            customer_menu(customer_id);
            break;
        case 13://enter press korbe
            break;
        }
    }
    while(ch!=13);

    switch(countttt)
    {
    case 1:
        closegraph();
        customer_balance_deposit(customer_id);
        break;
    case 2:
        closegraph();
        customer_balance_withdraw(customer_id);
        break;
    }
}

void customer::customer_balance_deposit(int customer_id)
{
    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    initwindow(600,400);

    readimagefile("admin_login.jpg", 0, 0, 600, 400);

    settextstyle(9,0,2);
    setcolor(LIGHTCYAN);
    outtextxy(100,80," Money Deposit ");
    setcolor(LIGHTBLUE);
    outtextxy(40,150,"Amount of Money: ");
    outtextxy(290,150,"Tk.  ");

    //money deposit korar jonno
    char chrctr,str[3],balance_temp[30];
    int c_gap=0,i=0,j;

    stringstream s;
    stringstream ss;
    string balance="";

    setcolor(0);
    settextstyle(8,0,2);
    outtextxy(340,150," ");

    while(1)
    {
        chrctr=getch();
        if(chrctr=='\r')//enter press korse
            break;
        else if(chrctr==27)
        {
            closegraph();
            customer_transaction(customer_id);
        }
        else if(chrctr==9)
        {
            closegraph();
            customer_balance_deposit(customer_id);
        }
        else if(chrctr==8 && i==0)
        {
            setcolor(0);
            settextstyle(8,0,2);
            outtextxy(340,150," ");
        }
        else if(chrctr==8 && i>0)
        {
            i--;
            setcolor(15);
            settextstyle(8,0,2);
            c_gap-=14;
            outtextxy(340+c_gap,150," ");
        }
        else
        {
            balance_temp[i]=chrctr;//character array te nitesi
            sprintf(str,"%c",chrctr);
            setcolor(15);
            settextstyle(8,0,2);
            outtextxy(340+c_gap,150,str);
            i++;
            c_gap+=14;//ak character theke next character er gap
        }
    }
    balance_temp[i]='\0';
    for(j=0; j<i; j++) //character array theke string e nitesi
    {
        balance=balance+balance_temp[j];
    }
    double deposit_balance, current_balance;
    deposit_balance=stold(balance);

    string customer_id_in_string, current_balance_in_sring;
    customer_id_in_string=to_string(customer_id);

    int state=0;
    state=mysql_query(con,select_all_from_cust_balance);//"SELECT * FROM customer_balance"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(row[0]==customer_id_in_string)
            {
                current_balance=stold(row[2]);
                current_balance+=deposit_balance;
                current_balance_in_sring=to_string(current_balance);
                ss<<"UPDATE customer_balance SET current_balance='"<<current_balance_in_sring<<"', last_deposit_amount='"<<balance<<"', last_deposit_date= NOW() WHERE customer_account_no='"<<customer_id<<"'";
                string query=ss.str();
                const char* q=query.c_str();
                int state;
                state=mysql_query(con, q);
                if(!state)
                {
                    settextstyle(9,0,1);
                    setcolor(LIGHTCYAN);
                    outtextxy(60,200,"      Money Deposited Successfully !!     ");

                    getch();
                    closegraph();
                    customer_menu(customer_id);
                }
                else
                {
                    settextstyle(9,0,1);
                    setcolor(LIGHTCYAN);
                    outtextxy(60,200,"      Money was not Deposited !!     ");

                    getch();
                    closegraph();
                    customer_transaction(customer_id);
                }
            }
        }
        settextstyle(8,0,1);
        outtextxy(160,260,"Invalid Account Number !!");

        getch();
        closegraph();
        customer_transaction(customer_id);
    }
    settextstyle(8,0,1);
    outtextxy(200,240,"Database Error !!");

    getch();
    closegraph();
    customer_transaction(customer_id);
}

void customer::customer_balance_withdraw(int customer_id)
{
    con=mysql_init(0);
    con=mysql_real_connect(con, ip_address, "nahian", "nahian", "inex", 0, NULL, 0);

    initwindow(600,400);

    readimagefile("admin_login.jpg", 0, 0, 600, 400);

    settextstyle(9,0,2);
    setcolor(LIGHTCYAN);
    outtextxy(100,80," Money Withdraw ");
    setcolor(LIGHTBLUE);
    outtextxy(40,150,"Amount of Money: ");
    outtextxy(290,150,"Tk.  ");

    //money withdraw korar jonno
    char chrctr,str[3],balance_temp[30];
    int c_gap=0,i=0,j;

    stringstream s;
    stringstream ss;
    string balance="";

    setcolor(0);
    settextstyle(8,0,2);
    outtextxy(340,150," ");

    while(1)
    {
        chrctr=getch();
        if(chrctr=='\r')//enter press korse
            break;
        else if(chrctr==27)
        {
            closegraph();
            customer_transaction(customer_id);
        }
        else if(chrctr==9)
        {
            closegraph();
            customer_balance_withdraw(customer_id);
        }
        else if(chrctr==8 && i==0)
        {
            setcolor(0);
            settextstyle(8,0,2);
            outtextxy(340,150," ");
        }
        else if(chrctr==8 && i>0)
        {
            i--;
            setcolor(15);
            settextstyle(8,0,2);
            c_gap-=14;
            outtextxy(340+c_gap,150," ");
        }
        else
        {
            balance_temp[i]=chrctr;//character array te nitesi
            sprintf(str,"%c",chrctr);
            setcolor(15);
            settextstyle(8,0,2);
            outtextxy(340+c_gap,150,str);
            i++;
            c_gap+=14;//ak character theke next character er gap
        }
    }
    balance_temp[i]='\0';
    for(j=0; j<i; j++) //character array theke string e nitesi
    {
        balance=balance+balance_temp[j];
    }
    double withdraw_balance, current_balance;
    withdraw_balance=stold(balance);

    string customer_id_in_string, current_balance_in_sring;
    customer_id_in_string=to_string(customer_id);

    int state=0;
    state=mysql_query(con,select_all_from_cust_balance );//"SELECT * FROM customer_balance"
    if(!state)
    {
        res=mysql_store_result(con);
        while(row=mysql_fetch_row(res))
        {
            if(row[0]==customer_id_in_string)
            {
                current_balance=stold(row[2]);
                if(current_balance>=withdraw_balance)
                    current_balance-=withdraw_balance;
                else
                {
                    settextstyle(9,0,1);
                    setcolor(LIGHTCYAN);
                    outtextxy(60,200,"      Insufficient Money !!     ");

                    getch();
                    closegraph();
                    customer_balance_withdraw(customer_id);
                }
                current_balance_in_sring=to_string(current_balance);
                ss<<"UPDATE customer_balance SET current_balance='"<<current_balance_in_sring<<"', last_withdraw_amount='"<<balance<<"', last_withdraw_date= NOW() WHERE customer_account_no='"<<customer_id<<"'";
                string query=ss.str();
                const char* q=query.c_str();
                int state;
                state=mysql_query(con, q);
                if(!state)
                {
                    settextstyle(9,0,1);
                    setcolor(LIGHTCYAN);
                    outtextxy(60,200,"      Money Withdrawn Successfully !!     ");

                    getch();
                    closegraph();
                    customer_menu(customer_id);
                }
                else
                {
                    settextstyle(9,0,1);
                    setcolor(LIGHTCYAN);
                    outtextxy(60,200,"      Money was not Withdrawn !!     ");

                    getch();
                    closegraph();
                    customer_transaction(customer_id);
                }
            }
        }
        settextstyle(8,0,1);
        outtextxy(160,260,"Invalid Account Number !!");

        getch();
        closegraph();
        customer_transaction(customer_id);
    }
    settextstyle(8,0,1);
    outtextxy(200,240,"Database Error !!");

    getch();
    closegraph();
    customer_transaction(customer_id);
}

void customer::customer_transaction(int customer_id)
{
    initwindow(1000,700);

    readimagefile("image_login.jpg", 0, 0, 1000, 700);

    balance_content();
    balance_toggling(customer_id);

    getch();
    closegraph();
}
