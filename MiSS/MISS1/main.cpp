#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<gmp.h>

#define __NUM_BIT 1024*1024*sizeof(mpz_t)

using namespace std;

void cut_str(char str[])
{
  long int len = strlen(str);
  str[--len]='\0';
  while (str[--len]=='0') 
    str[len]='\0';
  if ( str[len]=='.' ) str[len]='\0';
}

int main(){
    mpz_t *tab,sum,num,sumOfSquares,square;
    mpf_t avarage,variance,floatSquare,floatSum,floatSumOfSquares;
    int precision;
    int count=0;
    int tablen=1024*1024;
    tab=(mpz_t*)malloc(tablen*sizeof(mpz_t));
    mpz_init2(sum, __NUM_BIT);
    mpz_set_ui(sum,0);
    mpz_init2(num, __NUM_BIT);
    mpz_init2(sumOfSquares, __NUM_BIT);
    mpf_init2(floatSum, __NUM_BIT);
    mpf_init2(floatSumOfSquares, __NUM_BIT);
    mpf_init2(variance, __NUM_BIT);
    mpf_init2(floatSquare, __NUM_BIT);
    mpf_init2(avarage, __NUM_BIT);
    mpz_init2(sum, __NUM_BIT);
    mpz_init2(square, __NUM_BIT);
    gmp_scanf("%d",&precision);
    while(gmp_scanf("%Zd",num)!=EOF){
	++count;
	if(tablen==count){
	    tablen*=2;
	    tab=(mpz_t*)realloc(tab,tablen*sizeof(mpz_t));
	}
	mpz_init_set(tab[count-1],num);
	
	mpz_add(sum,sum,num);
	mpz_mul(square,num,num);
	mpz_add(sumOfSquares,sumOfSquares,square);
    }
    mpf_set_z(floatSum,sum);
    mpf_set_z(floatSumOfSquares,sumOfSquares);
    //avarage=sum/count;
    mpf_div_ui(avarage,floatSum,count);
    mpf_mul(floatSquare,avarage,avarage);
    mpf_div_ui(variance,floatSumOfSquares,count);
    //variance=sumOfSquares/count-avarage*avarage;
    mpf_sub(variance,variance,floatSquare);
    
    int period;
    for(period=1;period<count;++period){
	int isPeriod=true;
	for(int j=period;j<count;++j){
	    if(mpz_cmp(tab[j],tab[j%period])){
		isPeriod=false;
		break;
	    }
	}
	if(isPeriod==true)break;
    }
    
    //use gmp_sprintf to create string in order to easier format output???
    char str_avg[36636];
    //gmp_printf("%.*Ff\n", precision, avarage);
    
    gmp_sprintf(str_avg, "%.*Ff", precision+1, avarage);
    cut_str(str_avg);
    printf("%s\n", str_avg, strlen(str_avg));
    
    //gmp_printf("%.*Ff\n", precision+1, variance);
    gmp_sprintf(str_avg, "%.*Ff", precision+1, variance);
    cut_str(str_avg);
    printf("%s\n", str_avg, strlen(str_avg));
    
    printf("%d\n",period);
    return 0;
}
