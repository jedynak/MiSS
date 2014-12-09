#include <stdio.h>
#include <fstream>

double f(double x, double t) //pierwsza pochodna
{
    return x*x-t;
}

double fp(double x, double t) //druga pochodna
{
    return 2*x;
}


int main()
{
    double e, x0, x;
    double xp;	//pochodna x
    double i;

    printf("Wpisz wartosc poczatkowa i krok\n", e);
    scanf("%lf %lf", &x0, &e);
    //printf("   %lf\n", e);

    x = x0;
    std::ofstream file;
    file.open ("plot");
    printf("%lf %lf\n", 0, x);
    file<<0<<" "<<x<<std::endl;
    xp = 0; 

    for ( i=e; i<=1; i+=e )
    {
        xp = xp - f(x, i)/fp(x, i);	
        x = x + xp *e;
        printf("%lf %lf\n", i, x);
        file<<i<<" "<<x<<std::endl;
    }
    file.close();
    

    return 0;
}
