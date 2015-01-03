#include<ccbp.h>

void menu();
void f1();
void f2();
void f3();

main()
{
  int gd=DETECT,gm;
  initgraph(&gd,&gm,"");
  menu();
}


void menu()
{char m;
 setbkcolor(LIGHTGRAY);
 while(1)
 {
 cleardevice();
 outhzxy3(130,50,"万 年 历 的 查 询 及 打 印",2,0,4);
 outhzxy3(460,430,"新闻一 郑越文",1,0,12);
 outhzxy3(50,120,"1、输 入 年 月 日，查 询 是 星 期 几",1,0,14);
 outhzxy3(50,170,"2、输 入 年 份，查 询 是 否 闰 年",1,0,1);
 outhzxy3(50,220,"3、输 入 年 份，打 印 全 年 日 历",1,0,2);
 outhzxy3(50,270,"4、退 出 程 序",1,0,3);
 outhzxy3(80,320,"请 按 键 选 择（1－4）：",1,0,15);

  m=getch();
  switch(m)
  {
    case '1':f1();break;
    case '2':f2();break;
    case '3':f3();break;
    case '4':exit(0);
    default:continue;
  }
 }

}

void f1()
{
   int a,b,c,d,e,f,g,h,i,s,year,month,day,leap=0,temp=0;
   char y[4],m[2],t[2],*tmd,nnd;
   float sf,yearf,tempf;
   int day1[12]={31,28,31,30,31,30,31,31,30,31,30,31};
   int day2[12]={31,29,31,30,31,30,31,31,30,31,30,31};
 while(1)
 {
   cleardevice();
   setcolor(RED);
   setfillstyle(9,LIGHTGREEN);
   rectangle(90,40,520,90);
   floodfill(100,50,RED);
   outhzxy3(100,50,"输入年月日，查询是星期几",2,0,14);
   outhzxy3(150,120,"请 输 入 年 份:",1,0,1);
   scanf("%d",&year);
   a=year/1000;
   b=(year-1000*a)/100;
   c=(year-1000*a-100*b)/10;
   d=year-1000*a-100*b-10*c;
   sprintf(y,"%c%c%c%c",a+48,b+48,c+48,d+48);
   outhzxy3(300,120,y,1,0,4);
   outhzxy3(150,150,"请 输 入 月 份 :",1,0,1);
   while(1)
        {
         scanf("%d",&month);
         if(month>=1&&month<=12)
           {
              e=month/10;
              f=month-10*e;
              sprintf(m,"%c%c",e+48,f+48);
              break;
            }
         }
   outhzxy3(317,150,m,1,0,4);
   outhzxy3(150,180,"请 输 入 日 子 :",1,0,1);
   while(1)
        {
         scanf("%d",&day);
         if(day>=1&&day<=28)
           {
             g=day/10;
             h=day-10*g;
             sprintf(t,"%c%c",g+48,h+48);
             break;
             sprintf(t,"%c%c",g+48,h+48);
                 break;
                }
          else if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
               if(day>=1&&day<=31)
                 {
                    g=day/10;
                    h=day-10*g;
                    sprintf(t,"%c%c",g+48,h+48);
                    break;
                  }

         else if(month==4||month==6||month==9||month==11)
               if(day>=1&&day<=30)
                 {
                    g=day/10;
                    h=day-10*g;
                    sprintf(t,"%c%c",g+48,h+48);
                    break;
                  }
           else if(month==2&&day==29)
                if((year%4==0&&year%100!=0)||(year%400==0))
                   {
                      leap=1;
                      g=day/10;
                      h=day-10*g;
                      sprintf(t,"%c%c",g+48,h+48);
                      break;
                   }

         }
   outhzxy3(317,180,t,1,0,4);
   sprintf(tmd,"%c%c%c%c 年 %c%c 月%c%c 日 是:",a+48,b+48,c+48,d+48,e+48,f+48,g+48,h+48);
   outhzxy3(150,240,tmd,1,0,6);

   if(leap==0)
       for(i=0;i<month-1;i++)
       temp=temp+day1[i];
   else
       for(i=0;i<month-1;i++)
       temp=temp+day2[i];

   temp=temp+day;
   tempf=(float)temp;
   yearf=(float)year;
   sf=yearf-1+(yearf-1)/4+(yearf-1)/100+(yearf-1)/400+tempf;
   s=(int)sf;
   switch(s%7)
     {
       case 1:outhzxy3(240,270,"星 期 一",2,0,3);break;
       case 2:outhzxy3(240,270,"星 期 二",2,0,3);break;
       case 3:outhzxy3(240,270,"星 期 三",2,0,3);break;
       case 4:outhzxy3(240,270,"星 期 四",2,0,3);break;
       case 5:outhzxy3(240,270,"星 期 五",2,0,3);break;
       case 6:outhzxy3(240,270,"星 期 六",2,0,3);break;
       case 0:outhzxy3(240,270,"星 期 日",2,0,3);break;
     }
   outhzxy3(150,360,"是 否 继 续 查 询 (Y/N) :",1,0,1);
   while(1)
    {
       nnd=getch();
       if(nnd=='y'||nnd=='Y')
       break;
       else if(nnd=='n'||nnd=='N')
       return;
    }
  }


 }

void f2()
{
  int a,b,c,d,year;
  char y[4],*t,nnd;
  while(1)
  {
   cleardevice();
   setcolor(RED);
   setfillstyle(9,LIGHTCYAN);
   rectangle(90,40,520,90);
   floodfill(100,50,RED);
   outhzxy3(100,50,"输 入 年，查 询 是 否 闰 年",2,0,1);
   outhzxy3(150,120,"请 输 入 年 份:",1,0,1);
   scanf("%d",&year);
   a=year/1000;
   b=(year-1000*a)/100;
   c=(year-1000*a-100*b)/10;
   d=year-1000*a-100*b-10*c;
   sprintf(y,"%c%c%c%c",a+48,b+48,c+48,d+48);
   outhzxy3(300,120,y,1,0,4);
   if((year%4==0&&year%100!=0)||(year%400==0))
     {
       sprintf(t,"%c %c %c %c 年 是 闰 年",a+48,b+48,c+48,d+48);
       outhzxy3(180,300,t,2,0,4);
     }
   else
      {
       sprintf(t,"%c %c %c %c 年 不 是 闰 年",a+48,b+48,c+48,d+48);
       outhzxy3(180,220,t,2,0,6);
      }

   outhzxy3(150,360,"是 否 继 续 查 询 (Y/N) :",1,0,1);
   while(1)
    {
       nnd=getch();
       if(nnd=='y'||nnd=='Y')
       break;
       else if(nnd=='n'||nnd=='N')
       return;
    }

   }

 }

void f3()
{
   int a,b,c,d,g,h,s,i,j,k,x,year,week,leap=0;
   char *y,*t,*temp,nnd;
   float yearf,sf;
   int day[12]={31,28,31,30,31,30,31,31,30,31,30,31};

   while(1)
   {
     cleardevice();
     outhzxy3(130,10,"请 输 入 年 份 :",1,0,2);
     scanf("%d",&year);
     a=year/1000;
     b=(year-1000*a)/100;
     c=(year-1000*a-100*b)/10;
     d=year-1000*a-100*b-10*c;
     sprintf(y,"%c%c%c%c",a+48,b+48,c+48,d+48);
     outhzxy3(280,10,y,1,0,4);

     if((year%4==0&&year%100!=0)||(year%400==0))
       {leap=0;day[1]=29;}
     else
       {leap=0;day[1]=28;}

     yearf=(float)year;
     sf=yearf-1+(yearf-1)/4+(yearf-1)/100+(yearf-1)/400+1;
     s=(int)sf;
     week=s%7;

     for(i=0;i<12;i++)
      {
          j=0;
          setviewport(5+160*(i%4),50+130*(i/4),155+160*(i%4),170+130*(i/4),0);
          if(i==0)
          k=12;
          else if(i==7)
          k=13;
          else if(i==1)
          k=14;
          else
          k=i;

          outhzxy3(10,10,"日一二 三四五 六",1,0,4);
          for(x=0;x<day[i];x++)
            {
                g=(x+1)/10;
                h=(x+1)-10*g;
                sprintf(t,"%c%c",g+48,h+48);

                if(week==7)
                  {j++;week=0;}


                outhzxy3(10+20*week,25+10*j,t,1,0,k);
                week++;
            }
         sprintf(temp,"%d",i+1);
         settextstyle(0,0,2);
         setcolor(WHITE);
         outtextxy(50,90,temp);
         settextstyle(0,0,1);
         outhzxy3(80,90,"月",1,0,1);


      }
     setviewport(0,0,639,479,0);
     outhzxy3(240,430,"是 否 继 续 查 询 (Y/N) :",1,0,2);
     while(1)
    {
       nnd=getch();
       if(nnd=='y'||nnd=='Y')
       break;
       else if(nnd=='n'||nnd=='N')
       return;
    }
   }

 }


