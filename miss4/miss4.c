#include <stdio.h>

double f(double x, double t) //pierwsza pochodna
{
    return x*x-t;
}

double fp(double x) //druga pochodna
{
    return 2*x;
}


int main()
{
    double e, x0, x;
    double i;

    scanf("%lf %lf", &x0, &e);
    //printf("   %lf\n", e);

    x = x0;
    for ( i=0; i<1; i+=e )
    {
        x = x - f(x, i)/fp(x);
        printf("%lf %lf\n", i, x);
    }

    return 0;
}
