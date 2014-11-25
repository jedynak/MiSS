#include <stdio.h>


typedef struct ELEMENT circle;
typedef struct ELEMENT* wsk_element;
struct ELEMENT
{
    unsigned short val; // najmlodszy bit - lfsr_i, kolejny a_i
    wsk_element next;
    wsk_element prev;
};


int main(int argc, char *argv[])
{
  long unsigned int k;
  long unsigned int lfsr;
  long unsigned int l_n=atoi(argv[1]);
  long unsigned int l_m=atoi(argv[2]);
  long unsigned int i, j, g;
  unsigned short int b_a, b_lfsr;
  long unsigned int mnm;
  unsigned s;
  scanf("%lu", &k);
  circle c_lfsr[k];
  for ( i=1; i<k; i++ )
  {
      c_lfsr[i].prev = &c_lfsr[i-1];
      c_lfsr[i-1].next = &c_lfsr[i];
  }
  c_lfsr[0].prev = &c_lfsr[k-1];
  c_lfsr[k-1].next = &c_lfsr[0];
  wsk_element act = &c_lfsr[0], tmp;
  for ( i=0; i<k; i++ )
  {
      scanf("%hu", &b_a);
      c_lfsr[i].val = b_a<<1;
  }
  for ( i=0; i<k; i++ )
  {
      scanf("%hu", &b_lfsr);
      if ( b_lfsr )
        c_lfsr[i].val |= 1;
  }
  act = &c_lfsr[k-1];
  mnm = 0;
  mnm = ~mnm;
  for (i=l_n; i<l_m; i++)
  {
    lfsr=0;
    for (j=0;j<32;j++)
    {
        act = act->next;
        tmp = act;
        s=0;
        for(g=0; g<k-1; g++)
        {
            tmp = tmp->prev;
            //s=((act->val&0x1)+((tmp->val&0x1)&((tmp->val&0x2)>>1)))&0x1;
            //s = ((act->val&0x1)+((tmp->val&0x1)*((tmp->val&0x2)>>1)))&0x1;
            //act->val = (act->val&0x2)+s;
            //act->val = ((act->val+s)&0x1)|(act->val&~0b1);
            s ^= (((tmp->val&0x2)>>1)&(tmp->val&0x1))&0x1;
            //printf(".%d%d", s, act->val);

        }
        act->val = act->val&~0b1|s&0x1;
        lfsr |= (act->val&0x1)<<j;
    }
    printf("%lu/%lu ", lfsr, mnm);
  }

  return 0;

}
