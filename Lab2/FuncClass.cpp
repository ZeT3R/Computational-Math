//
// Created by Sergey on 08.11.2020.
//
#include "FuncClass.h"

#define TwoPi  6.28318530717958648
const double eps=1e-6;





double pow(double a, double n){
    double result = 1;
    int i = 0;
    while (i < n){
        result *= a;
        i++;
    }
    return result;
}



double abs(double x){
    if(x >= 0)
        return x;
    else
        return x - 2 * x;
}


double cos(double x)
{
    double n = 1.0;
    double sum = 0.0;
    int i = 1;

    do
    {
        sum += n;
        n *= -1.0 * x * x / ((2 * i - 1) * (2 * i));
        i++;
    }
    while (abs(n) > eps);

    return sum;
}



double sqrt(int x) {
    if (x==0) return 0;
    int left = 1;
    int right = x/2 + 1;
    double res;

    while (left <= right) {
        int mid = left + ((right-left)/2);
        if (mid<=x/mid){
            left = mid+1;
            res=mid;
        }
        else {
            right=mid-1;
        }
    }

    return res;
}




void CSqrt(double x, double y, double &a, double &b) // returns:  a+i*b = sqrt(x+i*y)
{
    double r  = sqrt(x*x+y*y);
    if( y==0 )
    {
        r = sqrt(r);
        if(x>=0)
        {
            a=r;
            b=0;
        }
        else
        {
            a=0;
            b=r;
        }
    }
    else
    {       // y != 0
        a = sqrt(0.5*(x+r));
        b = 0.5*y/a;
    }
}

#define SWAP(a,b) {t=b; b=a; a=t;}


void dblSort3( double &a, double &b, double &c) // make: a <= b <= c
{
    double t;
    if( a>b )
    SWAP(a,b);  // now a<=b
    if( c<b )
    {
        SWAP(b,c);          // now a<=b, b<=c
        if( a>b )
        SWAP(a,b);// now a<=b
    }
}


double Func::N4Step(double &x, double a, double b, double c, double d)
{
    double fxs= ((4*x+3*a)*x+2*b)*x+c;  // f'(x)
    if( fxs==0 )
        return 0.;
    double fx = (((x+a)*x+b)*x+c)*x+d;  // f(x)
    return x - fx/fxs;
}


double Func::SolveP4(double *&x, double a, double b, double c, double d)
{

    double d1 = d + 0.25*a*( 0.25*b*a - 3./64*a*a*a - c);
    double c1 = c + 0.5*a*(0.25*a*a - b);
    double b1 = b - 0.375*a*a;
    int res = SolveP4De(x, b1, c1, d1);
    if( res==4)
    {
        x[0]-= a/4;
        x[1]-= a/4;
        x[2]-= a/4;
        x[3]-= a/4;
    }
    else if (res==2)
    {
        x[0]-= a/4;
        x[1]-= a/4;
        x[2]-= a/4;
    }
    else
    {
        x[0]-= a/4;
        x[2]-= a/4;
    }
    // one Newton step for each real root:
    if( res>0 )
    {
        x[0] = N4Step(x[0], a,b,c,d);
        x[1] = N4Step(x[1], a,b,c,d);
    }
    if( res>2 )
    {
        x[2] = N4Step(x[2], a,b,c,d);
        x[3] = N4Step(x[3], a,b,c,d);
    }
    return res;
}


int Func::SolveP4De(double *&x, int b, int c, int d)
{

    int res3 = SolveP3(x, 2*b, b*b-4*d, -c*c);  // solve resolvent
    // by Viet theorem:  x1*x2*x3=-c*c not equals to 0, so x1!=0, x2!=0, x3!=0
    if( res3>1 )    // 3 real roots,
    {
        dblSort3(x[0], x[1], x[2]); // sort roots to x[0] <= x[1] <= x[2]
        // Note: x[0]*x[1]*x[2]= c*c > 0
        if( x[0] > 0) // all roots are positive
        {
            double sz1 = sqrt(x[0]);
            double sz2 = sqrt(x[1]);
            double sz3 = sqrt(x[2]);
            // Note: sz1*sz2*sz3= -c (and not equal to 0)
            if( c>0 )
            {
                x[0] = (-sz1 -sz2 -sz3)/2;
                x[1] = (-sz1 +sz2 +sz3)/2;
                x[2] = (+sz1 -sz2 +sz3)/2;
                x[3] = (+sz1 +sz2 -sz3)/2;
                return 4;
            }
            // now: c<0
            x[0] = (-sz1 -sz2 +sz3)/2;
            x[1] = (-sz1 +sz2 -sz3)/2;
            x[2] = (+sz1 -sz2 -sz3)/2;
            x[3] = (+sz1 +sz2 +sz3)/2;
            return 4;
        } // if( x[0] > 0) // all roots are positive
        // now x[0] <= x[1] < 0, x[2] > 0
        // two pair of comlex roots
        double sz1 = sqrt(-x[0]);
        double sz2 = sqrt(-x[1]);
        double sz3 = sqrt( x[2]);

        if( c>0 )   // sign = -1
        {
            x[0] = -sz3/2;
            x[1] = ( sz1 -sz2)/2;       // x[0]±i*x[1]
            x[2] =  sz3/2;
            x[3] = (-sz1 -sz2)/2;       // x[2]±i*x[3]
            return 0;
        }
        // now: c<0 , sign = +1
        x[0] =   sz3/2;
        x[1] = (-sz1 +sz2)/2;
        x[2] =  -sz3/2;
        x[3] = ( sz1 +sz2)/2;
        return 0;
    } // if( res3>1 )   // 3 real roots,
    // now resoventa have 1 real and pair of compex roots
    // x[0] - real root, and x[0]>0,
    // x[1]±i*x[2] - complex roots,
    double sz1 = sqrt(x[0]);
    double szr, szi;
    CSqrt(x[1], x[2], szr, szi);  // (szr+i*szi)^2 = x[1]+i*x[2]
    if( c>0 )   // sign = -1
    {
        x[0] = -sz1/2-szr;          // 1st real root
        x[1] = -sz1/2+szr;          // 2nd real root
        x[2] = sz1/2;
        x[3] = szi;
        return 2;
    }
    // now: c<0 , sign = +1
    x[0] = sz1/2-szr;           // 1st real root
    x[1] = sz1/2+szr;           // 2nd real root
    x[2] = -sz1/2;
    x[3] = szi;
    return 2;
}


int Func::SolveP3(double *&x,int a,int b,int c)
{
    double a2 = a*a;
    double q  = (a2 - 3*b)/9;
    double r  = (a*(2*a2-9*b) + 27*c)/54;
    double r2 = r*r;
    double q3 = q*q*q;
    double A,B;
    if(r2<q3)
    {
        double t=r/sqrt(q3);
        if( t<-1) t=-1;
        if( t> 1) t= 1;
        t=acos(t);
        a/=3; q=-2*sqrt(q);
        x[0]=q*cos(t/3)-a;
        x[1]=q*cos((t+TwoPi)/3)-a;
        x[2]=q*cos((t-TwoPi)/3)-a;
        return(3);
    }
    else
    {
        A =-pow(abs(r)+sqrt(r2-q3),1./3);
        if( r<0 ) A=-A;
        B = A==0? 0 : B = q/A;

        a/=3;
        x[0] =(A+B)-a;
        x[1] =-0.5*(A+B)-a;
        x[2] = 0.5*sqrt(3.)*(A-B);
        if(abs(x[2])<eps)
        {
            x[2]=x[1];
            return(2);
        }
        return(1);
    }
}

