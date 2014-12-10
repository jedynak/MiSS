#include <stdio.h>
#include <fstream>

double f(double x, double t) 
{
    return -x*x*x*(t+1);
}


double runge_kutta3(double x, double t, double h)
{
	double k1,k2,k3;
	k1 = h * f(x,t);
	k2 = h * f(x + k1/2,t+h/2);
	k3 = h * f(x-k1+2*k2,t+h);
	return x + (k1 + 4*k2 + k3)/6;
}

int main()
{
    double e, x0, x;
    double i;

    printf("Wpisz wartosc poczatkowa i krok\n", e);
    scanf("%lf %lf", &x0, &e);
    //printf("   %lf\n", e);

    x = x0;
    std::ofstream file;
    file.open ("plot");
    printf("%lf %lf\n", 0, x);
    file<<0<<" "<<x<<std::endl;

    for ( i=e; i<=1; i+=e )
    {	
        x = runge_kutta3(x,i,e);
        printf("%lf %lf\n", i, x);
        file<<i<<" "<<x<<std::endl;
    }
    file.close();
    

    return 0;
}
