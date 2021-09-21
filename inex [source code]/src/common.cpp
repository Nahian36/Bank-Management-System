#include "common.h"
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
#include<admin.h>
#include<customer.h>

void common::loading()
{
    int x=190,i,y=440;
    load=0;
    initwindow(640,500);

    setcolor(3);
    rectangle(185,155,445,185); //console e uporer hollow rectangle ta

    setcolor(3);
    rectangle(185,235,445,265); //console e nicher hollow rectangle ta

    setcolor(WHITE);
    settextstyle(9,0,3);
    //settextstyle(font,direction of text,size of letters)
    outtextxy(240,200,"LOADING !!");

    setcolor(11);
    settextstyle(4,0,2);
    outtextxy(220,240,"PLEASE WAIT");

    for(i=0; i<=100; i++)
    {
        delay(25);

        sprintf(dig,"%d",load);//windows BGI e print korar jonno
        load++;
        settextstyle(4,0,1);
        outtextxy(280,161, dig);
        outtextxy(328,161, "%");

        line(x,240,x,260); //console e nicher loading line ta
        line(y,160,y,180); //console e uporer loading line ta
        //last er 2 ta line na likhe ebhabeo likha jaito
        //line(x+=2,240,x,260)
        //line(y-=2,160,y,180

        y-=2;
        x+=2;
    }

    for(i=0; i<=24; i++)
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



