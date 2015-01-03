#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<math.h>

int outhzxy3(int x,int y,char *p,int size,int direction,int color)
{   int oldcolor;
    oldcolor=getcolor();
    setcolor(color);
    setfillstyle(SOLID_FILL,color);
    while(*p){
    if(((unsigned char)*p>=0xa1&&(unsigned char)*p<=0xfe)&&
	((unsigned char)*(p+1)>=0xa1&&(unsigned char)*(p+1)<=0xfe))
     {
       disp_hz3(x,y,*p,*(p+1),size,direction,color);
       p+=2;
       if(direction==HORIZ_DIR)
	 x+=size*16+2;
       if(direction==VERT_DIR)
	 y-=size*16+2;
       moveto(x,y);
      }
      else{
      char q[2];
      moveto(x,y);
      *q=*p;*(q+1)='\0';
      outtextxy(x,y+4,q);
      x+=8;p++;
      }
      }
      setcolor(oldcolor);
 }

int  disp_hz3(int left,int top,unsigned char byte1,
	    unsigned char byte2,int size,int direction,int color)
  {
      FILE * cclibfile;
      unsigned char buf[32];
      long p;
      int i,j,x,y,radiumX,radiumY;
      unsigned char mark;

      cclibfile=fopen("CCLIB.DAT","rb");
      if(cclibfile==NULL) {
	 outtextxy(10,10,"Not find CCLIB.DOT!Press any key to exit...");
	 getch();
	 exit(1);
	 }
      if((byte1>=0xa1&&byte1<=0xfe)&&(byte2>=0xa1&&
	       byte2<=0xfe)){
      p=(byte1-0xa1)*0x5e+byte2-0xa1;
      p*=32;
      fseek(cclibfile,(long)p,SEEK_SET);
      fread(buf,sizeof(unsigned char),32,cclibfile);
      fclose(cclibfile);
      if((left+size*16-1)>getmaxx()||(top+size*16-1)>getmaxy())
	      return 0;
      if(size==1){
	 if(direction==HORIZ_DIR){
	     for(i=0,y=top;i<31;i+=2,y++)
		for(mark=0x80,j=0;mark>0;mark=mark>>1,j++){
		   if((buf[i]&mark)!=0)
		     putpixel(left+j,y,color);
		   if((buf[i+1]&mark)!=0)
		     putpixel(left+j+8,y,color);
		 }
	 }
	 if(direction==VERT_DIR){
	    for(i=0,x=left;i<31;i+=2,x++)
	       for(mark=0x80,j=0;mark>0;mark=mark>>1,j++){
		  if((buf[i]&mark)!=0)
		     putpixel(x,top-j,color);
		  if((buf[i+1]&mark)!=0)
		     putpixel(x,top-j-8,color);
	       }
	 }
      return 1;
      }
      if(size==2){
	 radiumX=size/2+1;
	 radiumY=size/2;
       }
       else{
	  radiumX=size/2+1;
	  radiumY=size/2+1;
       }
       if(direction==VERT_DIR){
	  for(i=0,x=left;i<31;i+=2,x+=size)
	      for(mark=0x80,j=0;mark>0;mark=mark>>1,j++){
		 if((buf[i]&mark)!=0)
		   bar(x+size/2,top-j*size-size/2,
                       x+size/2+radiumX,top-j*size-size/2+radiumY);
		 if((buf[i+1]&mark)!=0)
		   bar(x+size/2,top-(j+8)*size-size/2,
                       x+size/2+radiumX,top-(j+8)*size-size/2+radiumY);
		}
	     return 1;
	}
	if(direction==HORIZ_DIR){
	for(i=0,y=top;i<31;i+=2,y+=size)
	   for(mark=0x80,j=0;mark>0;mark=mark>>1,j++){
	      if((buf[i]&mark)!=0)
		   bar(left+j*size+size/2,y+size/2,
		       left+j*size+size/2+radiumX,y+size/2+radiumY);
	      if((buf[i+1]&mark)!=0)
		   bar(left+(j+8)*size+size/2,y+size/2,
		       left+(j+8)*size+size/2+radiumX,y+size/2+radiumY);
	    }
	    return 1;
	}
	}
	fclose(cclibfile);
 }

int outhzxy1(int x,int y,char *p,int color)
  {
   int oldcolor;
   oldcolor=getcolor();
   setcolor(color);
   while(*p)
      {
	if(((unsigned char)*p>=0xa1&&(unsigned char)*p<=0xfe)&&
	((unsigned char)*(p+1)>=0xa1&&(unsigned char)*(p+1)<=0xfe))
          {
            if((x+16-1)>getmaxx()||(y+16-1)>getmaxy())
            return 0;
            disp_hz1(x,y,*p,*(p+1),color);
            p+=2;
            x+=16+2;
            moveto(x,y);
           }
         else{
           char q[2];
           moveto(x,y);
           *q=*p;*(q+1)='\0';
           settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
           outtextxy(x,y+4,q);
           x+=8+1;p++;
              }
        }
    setcolor(oldcolor);
    return 1;
  }


int disp_hz1(int left,int top,unsigned char byte1,
	     unsigned char byte2,int color)
{
   FILE *cclibfile;
   unsigned char buf[32];
   unsigned char mark;
   long p;
   int x,y,i,j;
   int quma,weima;
   cclibfile=fopen("CCLIB.DAT","rb");
   if(cclibfile==NULL)
     {
      outtextxy(10,10,"Can't open CCLIB.DAT file! Press any key to halt ...");
      exit(1);
     }
   if((byte1>=0xa1&&byte1<=0xfe)&&(byte2>=0xa1&&byte2<=0xfe))
    {
   quma=byte1-0xa0;
   weima=byte2-0xa0;
   p=(quma-1)*94+weima-1;
   p*=32;
   fseek(cclibfile,(long)p,SEEK_SET);
   fread(buf,sizeof(unsigned char),32,cclibfile);
   fclose(cclibfile);
   for(i=0,y=top;i<31;i+=2,y++)
   for(mark=0x80,j=0;mark>0;mark=mark>>1,j++)
        {
	 if((buf[i]&mark)!=0)
         putpixel(left+j,y,color);
         if((buf[i+1]&mark)!=0)
	 putpixel(left+j+8,y,color);
        }
    }
   fclose(cclibfile);
   return 1;
}
     int coordc(int x,int y,double l,double a,double u,int c)
      {
       int i;
       double p,q,x1,y1,x2,x3,y3,y2,b,L;
       a=(a-0.01)*3.1415926548/180.0;
       b=0.197395559;
       L=10.19803903;
       x1=x+l*cos(a);
       y1=y-l*sin(a);
       x2=x1-L*cos(b-a);
       y2=y1-L*sin(b-a);
       x3=x1-L*cos(b+a);
       y3=y1+L*sin(b+a);
       setcolor(c);
       line(x,y,(int)x1,(int)y1);
       if(l<11.0)return;
       moveto((int)x1,(int)y1);
       lineto((int)x2,(int)y2);
       lineto((int)x3,(int)y3);
       lineto((int)x1,(int)y1);
       for(i=0;i<l/u-1;i++)
       {
       p=x+u*cos(a);
       q=y-u*sin(a);
       moveto(p,q);
       lineto(p-1*sin(a),q-1*cos(a));
       x=p;y=q;
       }
       }


    int coord(int x,int y,double l,double a,double u)
      {
       int i;
       double p,q,x1,y1,x2,x3,y3,y2,b,L;
       a=(a-0.01)*3.1415926548/180.0;
       b=0.197395559;
       L=10.19803903;
       x1=x+l*cos(a);
       y1=y-l*sin(a);
       x2=x1-L*cos(b-a);
       y2=y1-L*sin(b-a);
       x3=x1-L*cos(b+a);
       y3=y1+L*sin(b+a);
       setcolor(15);
       line(x,y,(int)x1,(int)y1);
       if(l<11.0)return;
       moveto((int)x1,(int)y1);
       lineto((int)x2,(int)y2);
       lineto((int)x3,(int)y3);
       lineto((int)x1,(int)y1);
       for(i=0;i<l/u-1;i++)
       {
       p=x+u*cos(a);
       q=y-u*sin(a);
       moveto(p,q);
       lineto(p-1*sin(a),q-1*cos(a));
       x=p;y=q;
       }
       }
  coil1(x0,y0,l,h,n,r,p,m)
int x0,y0,l,h,n,r,p,m;
{
int i;
setcolor(n);
setfillstyle(1,m);
bar(x0,y0,x0+l,y0+h);
for(i=0;i<p;i++)
{
arc(x0+l,y0+3*r+6*r*i,-90,90,r);
line(x0+l,y0+4*r+6*r*i,x0,y0+7*r+6*r*i);
arc(x0,y0+8*r+6*r*i,90,270,r);
line(x0,y0+2*r,x0-50,y0+2*r);

}
arc(x0+l,y0+3*r+6*r*i,-90,90,r);
line(x0+l,y0+4*r+6*r*i,x0,y0+7*r+6*r*i);
line(x0,y0+7*r+6*r*i,x0-50,y0+7*r+6*r*i);
arc(x0-50,y0+7*r+6*r*i,0,360,3);
arc(x0-50,y0+2*r,0,360,3);
}
coil2(x0,y0,l,h,n,r,p,m)
int x0,y0,l,h,n,r,p,m;
{
int i;
setcolor(m);
setfillstyle(1,n);
bar(x0,y0,x0+h,y0+l);
for(i=0;i<p;i++)
{
arc(x0+2*r+6*r*i,y0,0,180,r);
line(x0+3*r+6*r*i,y0,x0+6*r+6*r*i,y0+l);
arc(x0+7*r+6*r*i,y0+l,180,360,r);
line(x0+2*r,y0+l,x0+2*r,y0+50+l);

}
arc(x0+2*r+6*r*i,y0,0,180,r);
line(x0+3*r+6*r*i,y0,x0+6*r+6*r*i,y0+l);
line(x0+6*r+6*r*i,y0+l,x0+6*r+6*r*i,y0+50+l);
arc(x0+6*r+6*r*i,y0+50+l,0,360,3);
arc(x0+2*r,y0+50+l,0,360,3);
}


  coil3(x0,y0,l,h,m,r,p,n)
 int x0,y0,l,h,m,r,p,n;

{

int i;

setcolor(n);
setfillstyle(1,m);
bar(x0,y0,x0+l,y0+h);

for(i=0;i<p;i++)
{
arc(x0,y0+2*r+6*r*i,90,270,r);
line(x0,y0+3*r+6*r*i,x0+l,y0+6*r+6*r*i);
arc(x0+l,y0+7*r+6*r*i,-90,90,r);
line(x0+l,y0+2*r,x0+50+l,y0+2*r);

}
arc(x0,y0+2*r+6*r*i,90,270,r);
line(x0,y0+3*r+6*r*i,x0+l,y0+6*r+6*r*i);
line(x0+l,y0+6*r+6*r*i,x0+50+l,y0+6*r+6*r*i);
arc(x0+50+l,y0+6*r+6*r*i,0,360,3);
arc(x0+50+l,y0+2*r,0,360,3);
}

coil4(x0,y0,l,h,n,r,p,m)
int x0,y0,l,h,n,r,p,m;
{
int i;
setcolor(m);
rectangle(x0,y0,x0+l,y0+h);
setcolor(n);
for(i=0;i<p;i++)
{
arc(x0,y0+2*r+6*r*i,90,270,r);
line(x0,y0+3*r+6*r*i,x0+l,y0+6*r+6*r*i);
arc(x0+l,y0+7*r+6*r*i,-90,90,r);
line(x0+l,y0+2*r,x0+50+l,y0+2*r);

}
arc(x0,y0+2*r+6*r*i,90,270,r);
line(x0,y0+3*r+6*r*i,x0+l,y0+6*r+6*r*i);
line(x0+l,y0+6*r+6*r*i,x0+50+l,y0+6*r+6*r*i);
arc(x0+50+l,y0+6*r+6*r*i,0,360,3);
arc(x0+50+l,y0+2*r,0,360,3);
}
coil5(x0,y0,l,h,n,r,p,m)
int x0,y0,l,h,n,r,p,m;
{
int i;
setcolor(m);
rectangle(x0,y0,x0+l,y0+h);
setcolor(n);
for(i=0;i<p;i++)
{
arc(x0,y0+7*r+6*r*i,90,270,r);
line(x0+l,y0+r+6*r*i,x0,y0+6*r+6*r*i);
arc(x0+l,y0+6*r+6*r*i,-90,90,r);
line(x0+l,y0+r,x0+40+l,y0+r);

}
arc(x0,y0+7*r+6*r*i,90,270,r);
line(x0,y0+6*r+6*r*i,x0+l,y0+r+6*r*i);
line(x0+l,y0+6*r+6*r*i,x0+40+l,y0+6*r+6*r*i);
arc(x0+40+l,y0+6*r+6*r*i,0,360,3);
arc(x0+40+l,y0+r,0,360,3);

}
coil6(x0,y0,l,h,n,r,p,m)
int x0,y0,l,h,n,r,p,m;
{
int i;
setcolor(m);
setfillstyle(1,n);
bar(x0,y0,x0+l,y0+h);
for(i=0;i<p;i++)
{
arc(x0+l,y0+9*r+6*r*i,-90,90,r);
line(x0+l,y0+4*r+6*r*i,x0,y0+7*r+6*r*i);
arc(x0,y0+8*r+6*r*i,90,270,r);
line(x0+l,y0+4*r,x0+l+50,y0+4*r);

}
arc(x0,y0+8*r+6*r*i,90,270,r);
line(x0+l,y0+4*r+6*r*i,x0,y0+7*r+6*r*i);
line(x0+l,y0+9*r+6*r*i,x0+l+50,y0+9*r+6*r*i);
arc(x0+l+50,y0+9*r+6*r*i,0,360,3);
arc(x0+l+50,y0+4*r,0,360,3);

}

 int jtd(x,y,a,g,p,k,w)
{
float x1,x2,x3,y1,y2,y3,g1,b;
g1=g*2*3.1415926/360;
b=a*p;
x1=x+a*sin(g1);
y1=y+a*cos(g1);
x2=x+b*cos(g1);
y2=y-b*sin(g1);
x3=x-a*sin(g1);
y3=y-a*cos(g1);
setlinestyle(0,4,w);
setcolor(k);
line(x1,y1,x2,y2);
line(x2,y2,x3,y3);
setcolor(k);
line(x1,y1,x3,y3);
 }

 int wood_b(int x,int y,int L,int H,double a)
       {
       double b=a*3.1415926/180.0;
       double s=sin(b);
       double c=cos(b);
       double A=L*s;
       double B=L*c;
       double C=H*s;
       double D=H*c;
       moveto(x,y);
       linerel((int)B,-(int)A);
       linerel(-(int)C,-(int)D);
       linerel(-(int)B,(int)A);
       lineto(x,y);
       }

    int inclined_p(int x,int y,int R,double a)
       {
       double b=a*3.1415926/180.0;
       double L=R*cos(b);
       double h=R*sin(b);
       moveto(x,y);
       linerel((int)L,0);
       linerel(0,-(int)h);
       lineto(x,y);
       return;
       }
    int arrowhead(int x,int y,double r,double a)
      {
       double x1,y1,x2,x3,y3,y2,b,L;
       a=a*3.141592655/180.0;
       b=0.197395559;
       L=10.19803903;
       x1=x+r*cos(a);
       y1=y-r*sin(a);
       x2=x1-L*cos(b-a);
       y2=y1-L*sin(b-a);
       x3=x1-L*cos(b+a);
       y3=y1+L*sin(b+a);
       line(x,y,(int)x1,(int)y1);
       if(r<11.0)return;
       moveto((int)x1,(int)y1);
       lineto((int)x2,(int)y2);
       lineto((int)x3,(int)y3);
       lineto((int)x1,(int)y1);
       }
    int arrowh(int x,int y,int x1,int y1)
       {
	double r,a,b,L,x2,x3,y2,y3;
	int X=x-x1,Y=y-y1;
	r=hypot((double)X,(double)Y);
	a=atan2((double)Y,(double)X);
        b=0.197395559;
        L=10.19803903;
	x2=x1+L*cos(b+a);
	y2=y1+L*sin(b+a);
	x3=x1+L*cos(b-a);
	y3=y1-L*sin(b-a);
        line(x,y,(int)x1,(int)y1);
        if(r<11.0)return;
        moveto((int)x1,(int)y1);
        lineto((int)x2,(int)y2);
        lineto((int)x3,(int)y3);
        lineto((int)x1,(int)y1);
       }

int pxsbxxy(int x,int y,double F1,double F2,double a,int C1,int C2,int C3)
    {
    double Fx,F2x,Fy;
    double Fjiao;
    int C=getcolor();
    double b=a*3.141592655/180.0;
    F2x=x+F2*cos(b);
    Fx=F1+F2x;
    Fy=y-F2*sin(b);
    setcolor(C1);
    arrowhead(x,y,(int)F1,0.0);
    setcolor(C2);
    arrowhead(x,y,(int)F2,a);
    if(F2>20.0&&F1>20.0)
    arc(x,y,0,a,20);
    setcolor(C3);
    arrowh(x,y,(int)Fx,(int)Fy);
    if(hypot((Fx-x),(Fy-y))>25.0&&F1>25.0) {
       Fjiao=atan2(F2*sin(b),Fx-x)*57.29577951;
       arc(x,y,0,(int)Fjiao,25);
     };
    setcolor(C);
    setlinestyle(1,0,1);
    line((int)F2x,(int)Fy,(int)Fx,(int)Fy);
    line(x+(int)F1,y,(int)Fx,(int)Fy);
    setlinestyle(0,0,1);
    }




int spring(int x0,int y0,int x,int y,double r,int n)
   {
   int i,k=1;
   double dx=((double)x-(double)x0)/2.0/n, dy=((double)y0-(double)y)/2.0/n;
   double a=atan2((double)(y0-y),(double)(x-x0));
   double dxr=r*cos(a+1.570796327), dyr=r*sin(a+1.570796327);
   double X[20],Y[20];
   if(n>20)exit(0);
   for(i=0;i<n;i++){
      X[i]=x0+(2*i+1)*dx+k*dxr;
      Y[i]=y0-(2*i+1)*dy-k*dyr;
      k=-k;
   };
   moveto(x0,y0);
   for(i=0;i<n;i++)
   lineto((int)X[i],(int)Y[i]);
   lineto(x,y);
   }

int square(int x,int y,int m,int n,int d)
    {
    int i;
    setlinestyle(1,0,1);
    for(i=0;i<=m;i++)line(x,y+d*i,x+d*n,y+d*i);
    for(i=0;i<=n;i++)line(x+d*i,y,x+d*i,y+d*m);
    }

int refrac_light(int x,int y,double r,double a,double B)
      {
       double x1,y1,x2,x3,y3,y2,b,L,x0,y0;
       a=a*3.141592655/180.0;
       b=0.197395559;
       L=10.19803903;
       x0=x+r*cos(a);
       y0=y-r*sin(a);
       x1=x+r*B*cos(a);
       y1=y-r*B*sin(a);
       x2=x1-L*cos(b-a);
       y2=y1-L*sin(b-a);
       x3=x1-L*cos(b+a);
       y3=y1+L*sin(b+a);
       line(x,y,(int)x0,(int)y0);
       if(r<11.0)return;
       moveto((int)x1,(int)y1);
       lineto((int)x2,(int)y2);
       lineto((int)x3,(int)y3);
       lineto((int)x1,(int)y1);
       }

int reflec_light(int x,int y,double r,double a,double B)
      {
       double x1,y1,x2,x3,y3,y2,b,L,x0,y0;
       a=a*3.141592655/180.0;
       b=0.197395559;
       L=10.19803903;
       x0=x+r*cos(a);
       y0=y-r*sin(a);
       x1=x+r*B*cos(a);
       y1=y-r*B*sin(a);
       x2=x1+L*cos(b-a);
       y2=y1+L*sin(b-a);
       x3=x1+L*cos(b+a);
       y3=y1-L*sin(b+a);
       line(x,y,(int)x0,(int)y0);
       if(r<11.0)return;
       moveto((int)x1,(int)y1);
       lineto((int)x2,(int)y2);
       lineto((int)x3,(int)y3);
       lineto((int)x1,(int)y1);
       }

int light(int x,int y,int x0,int y0,double B)
      {
       double x1,y1,x2,x3,y3,y2,b=0.197395559,L=10.19803903;
       double r, a;
       int X,Y;
       X=x-x0,Y=y-y0;
       r=hypot((double)X,(double)Y);
       a=atan2((double)Y,(double)X);
       x1=x-r*B*cos(a);
       y1=y-r*B*sin(a);
       x2=x1+L*cos(b-a);
       y2=y1-L*sin(b-a);
       x3=x1+L*cos(b+a);
       y3=y1+L*sin(b+a);
       line(x,y,(int)x0,(int)y0);
       if(r<11.0)return;
       moveto((int)x1,(int)y1);
       lineto((int)x2,(int)y2);
       lineto((int)x3,(int)y3);
       lineto((int)x1,(int)y1);
       }


int magnet_f(int x1,int y1,int x2,int y2,double B)
    {
        double dx;
        int i,j,k=0;
        setlinestyle(1,0,1);
	rectangle(x1,y1,x2,y2);
        setlinestyle(0,0,1);
	if(B>=0.)
		{dx=sqrt(B);
		 k=0;
		}
	else
		{dx=sqrt(-B);
		k=1;
		}
	for(i=-30;i<30;i++){
		for(j=-40;j<40;j++){
			if(dx>1.0e-5){
				double X=40.*(double)j/dx+(double)(x1+x2-4)/2.;
				double Y=40.*(double)i/dx+(double)(y1+y2-4)/2.;
				if(x1<(int)X&&(int)X<x2-4&&y1<(int)Y&&(int)Y<y2-4)
					if(k==0)outtextxy((int)X,(int)Y,"x");
					else   outtextxy((int)X,(int)Y-2,".");
				}

			}
		}
     }

  int electric_f(int x1,int y1,int x2,int y2,double E,int n)
    {
        double dx;
        int i;
        setlinestyle(1,0,1);
	rectangle(x1,y1,x2,y2);
        setlinestyle(0,0,1);
	if(E>=0.)dx=sqrt(E);
	else return;
	for(i=-40;i<40;i++){
        	if(dx>1.0e-5){
			double X=40.*(double)i/dx+(double)(x1+x2)/2.;
			double Y=40.*(double)i/dx+(double)(y1+y2)/2.;
			if(y1<(int)Y-4&&(int)Y<y2-4){
				if(n==0)arrowh(x1+2,(int)Y,x2-2,(int)Y);
				if(n==2)arrowh(x2-2,(int)Y,x1+2,(int)Y);
			        }
                        if(x1<(int)X-4&&(int)X<x2-4){
                                if(n==1)arrowh((int)X,y2-2,(int)X,y1+2);
                                if(n==3)arrowh((int)X,y1+2,(int)X,y2-2);
              			}
                 }
	}
     }








