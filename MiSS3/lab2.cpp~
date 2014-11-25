#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<gmp.h>

#define __NUM_BIT 1024*1024*sizeof(mpz_t)

using namespace std;

void sort(int count, mpq_t* T){
    mpq_t tmp;
    int j,k;
    mpq_init(tmp);
    for(int i=count/2-1;i>=0;--i){
	k=i;
	do{
	    j=k;
	    if(2*j+1<count&&mpq_cmp(T[2*j+1],T[k])>0)
		k=2*j+1;
	    if(2*j+2<count&&mpq_cmp(T[2*j+2],T[k])>0)
		k=2*j+2;
	    mpq_set(tmp,T[j]);
	    mpq_set(T[j],T[k]);
	    mpq_set(T[k],tmp);
	}while(j!=k);
    }
    for(int i=count-1;i>0;--i){
	mpq_set(tmp,T[0]);
	mpq_set(T[0],T[i]);
	mpq_set(T[i],tmp);
	k=0;
	do{
	    j=k;
	    if(2*j+1<i&&mpq_cmp(T[2*j+1],T[k])>0)
		k=2*j+1;
	    if(2*j+2<i&&mpq_cmp(T[2*j+2],T[k])>0)
		k=2*j+2;
	    mpq_set(tmp,T[j]);
	    mpq_set(T[j],T[k]);
	    mpq_set(T[k],tmp);
	}while(j!=k);
    }
}

void cut_str(char str[])
{
  long int len = strlen(str);
  str[--len]='\0';
  while (str[--len]=='0') 
    str[len]='\0';
  if ( str[len]=='.' ) str[len]='\0';
}

int main(int argc, char *argv[]){
    mpq_t *tab,num,tmp;
    long unsigned int precision=atoi(argv[1]);
    int count=0;
    const int k=10;
    int Ytab[k]={0};
    int Ymalp[4]={0};
    int tablen=1024*1024;
    tab=(mpq_t*)malloc(tablen*sizeof(mpq_t));
    mpq_init(num);
    mpq_init(tmp);

    while(gmp_scanf("%Qi",num)!=EOF){
	++count;
	if(tablen==count){
	    tablen*=2;
	    tab=(mpq_t*)realloc(tab,tablen*sizeof(mpq_t));
	}
	mpq_init(tab[count-1]);
	mpq_set(tab[count-1],num);
	int i=1;
	while(i<=k){
	    mpq_set_si(tmp,(i*i),100);
	    if(mpq_cmp(tmp,num)>0)break;
	    ++i;
	}
	++Ytab[i-1];
    }
    
//*********************************************MALPA*********************************************
    mpq_set_si(tmp,1,2); //polowa
    /*for (int i=1; i<count; i+=2)
        Ymalp[(!!(mpq_cmp(tab[i-1], tmp)+1))|((!!(mpq_cmp(tab[i], tmp)+1))<<1)]++;*/
    
    for (int i=1; i<count; i+=2)
    {
      if ( (mpq_cmp(tab[i-1], tmp) >= 0 ))
	if ( mpq_cmp(tab[i], tmp) >=0 )
	  Ymalp[0]++;
	else
	  Ymalp[1]++;
      else
	if ( mpq_cmp(tab[i], tmp) >=0 )
	  Ymalp[2]++;
	else
	  Ymalp[3]++;
    }
//***********************************************************************************************
    mpq_t V;
    mpq_init(V);
    mpq_set_si(V,0,1);
    sort(count,tab);
    mpq_t tmpKminus,tmpKplus,Kminus,Kplus;
    mpq_init(tmpKminus);
    mpq_init(tmpKplus);
    mpq_init(Kminus);
    mpq_init(Kplus);
    mpq_set_si(Kplus,1,count);
    mpq_sub(Kplus,Kplus,tab[0]);
    mpq_set(Kminus,tab[0]);
    for(int i=1;i<count;++i){
	mpq_set_si(tmpKminus,-i,count);
	mpq_add(tmpKminus,tmpKminus,tab[i]);
	mpq_set_si(tmpKplus,(i+1),count);
	mpq_sub(tmpKplus,tmpKplus,tab[i]);
	if(mpq_cmp(tmpKminus,Kminus)>0)mpq_set(Kminus,tmpKminus);
	if(mpq_cmp(tmpKplus,Kplus)>0)mpq_set(Kplus,tmpKplus);
    }
    
    mpq_t pos,pow;
    mpq_init(V);
    mpq_init(pos);
    mpq_init(pow);
    for(int i=0;i<k;++i){
	mpq_set_si(pos,count*(2*i+1),100);
	mpq_set_si(pow,Ytab[i],1);
	mpq_sub(pow,pow,pos);
	mpq_mul(pow,pow,pow);
	mpq_div(pow,pow,pos);	
	//V+=(Ytab[i]-k/count)*(Ytab[i]-k/count)/(k/count);
	mpq_add(V,V,pow);
    }

    /*
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
    }*/
    
    //use gmp_sprintf to create string in order to easier format output???
    char str_avg[1024*1024];
    mpf_t printer;
    mpf_init2(printer,__NUM_BIT);
    
    mpf_set_q(printer,V);
    gmp_sprintf(str_avg, "%.*Ff", precision+1, printer);
    cut_str(str_avg);
    printf("%s\n", str_avg);
    
    mpf_set_q(printer,Kplus);
    gmp_sprintf(str_avg, "%.*Ff", precision+1, printer);
    cut_str(str_avg);
    printf("%s\n", str_avg);

    mpf_set_q(printer,Kminus);
    gmp_sprintf(str_avg, "%.*Ff", precision+1, printer);
    cut_str(str_avg);
    printf("%s\n", str_avg);


    
    
    //MALPY

    
    /*for (int i=1; i<count; i+=2)
    {
      if ( (mpq_cmp(tab[i-1], tmp) >= 0 ))
	if ( mpq_cmp(tab[i], tmp) >=0 )
	  Ymalp[0]++;
	else
	  Ymalp[1]++;
      else
	if ( mpq_cmp(tab[i], tmp) >=0 )
	  Ymalp[2]++;
	else
	  Ymalp[3]++;
      
    }*/
    
//    for ( int i=0; i<4; i++ )
//      printf("  %d   ", Ymalp[i]);
    
    mpq_init(V);
    mpq_init(pos);
    mpq_init(pow);
    for(int i=0;i<4;++i){
	mpq_set_si(pos,count,8);
	mpq_set_si(pow,Ymalp[i],1);
	mpq_sub(pow,pow,pos);
	mpq_mul(pow,pow,pow);
	mpq_div(pow,pow,pos);	
	//V+=(Ytab[i]-k/count)*(Ytab[i]-k/count)/(k/count);
	mpq_add(V,V,pow);
    }
    mpf_set_q(printer,V);
    gmp_sprintf(str_avg, "%.*Ff", precision+1, printer);
    cut_str(str_avg);
    printf("%s\n", str_avg);
    
    //for ( int i=0; i<4; i++ )
    //  printf(" %d ", Ymalp[i]);
    
    int period;
    for(period=1;period<count;++period){
	int isPeriod=true;
	for(int j=period;j<count;++j){
	    if(mpq_cmp(tab[j],tab[j%period])){
		isPeriod=false;
		break;
	    }
	}
	if(isPeriod==true)break;
    }
    
    printf("%d\n",period);
    return 0;
}
