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
    for(int i=0;i<count/2;++i){
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
	}while(j==k);
    }
    for(int i=count-1;i>0;--i){
	mpq_set(tmp,T[0]);
	mpq_set(T[0],T[i]);
	mpq_set(T[i],tmp);
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
	}while(j==k);
    }

}

void cut_str(char str[])
{
  long int len = strlen(str);
  --len;
  bool fractial = false;
  long int i = len;
  while(i>0){
    if(str[i]=='.'){
	fractial = true;
	break;
    }
    --i;
  }
  if (fractial == true){
      str[len]='\0';
      while (len>=0&&str[len]=='0'){
        str[len]='\0';
        --len;
    }
	if ( str[len]=='.' ) str[len]='\0';
  }
}

int main(){
    mpq_t *tab,num;
    int precision;
    int count=0;
    const int k=10;
    int Ytab[k]={0};
    int tablen=1024*1024;
    tab=(mpq_t*)malloc(tablen*sizeof(mpq_t));
    mpq_init(num);
    mpq_t tmp;
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
	while(i<k){
	    mpq_set_si(tmp,(i*i),100);
	    if(mpq_cmp(tmp,num)>1)break;
	    ++i;
	}
	++Ytab[i-1];
    }
    double V=0;
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
	mpq_set_si(tmpKplus,(i-1),count);
	mpq_sub(tmpKplus,tmpKplus,tab[i]);
	if(mpq_cmp(tmpKminus,Kminus)>0)mpq_set(Kminus,tmpKminus);
	if(mpq_cmp(tmpKplus,Kplus)>0)mpq_set(Kplus,tmpKplus);
    }
    for(int i=0;i<k;++i){
	V+=(Ytab[i]-count/k)*(Ytab[i]-count/k)/(count/k);
    }
    
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
    
    char str_avg[36636];
    
    //gmp_sprintf(str_avg, "%Qf", avarage);
    cut_str(str_avg);
    printf("%s\n", str_avg, strlen(str_avg));
    
    //gmp_sprintf(str_avg, "%.*Ff", precision+1, variance);
    cut_str(str_avg);
    printf("%s\n", str_avg, strlen(str_avg));
    
    //printf("%d\n",period);
    return 0;
}
