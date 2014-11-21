#include <stdio.h>


typedef struct ELEMENT circle;
typedef struct ELEMENT* wsk_element;
struct ELEMENT
{
    long unsigned int val; // najmlodszy bit - lfsr_i, kolejny a_i
    wsk_element next;
    wsk_element lfg1;
};

#define max(x, y) x>y ? x : y

int main(int argc, char *argv[])
{
    unsigned long int i, j, k, m;
    long unsigned int l_n=atoi(argv[1]);
    long unsigned int l_m=atoi(argv[2]);
    scanf("%lu %lu %lu", &j, &k, &m);
    circle lfg[k];
    wsk_element act;
    for ( i=0; i<k; i++)
    {
        scanf("%lu", &lfg[i].val);
        lfg[i].val = lfg[i].val%m;
        lfg[i].next = &lfg[(i+1)%k];
        lfg[i].lfg1 = &lfg[(i+k-j)%k];
    }
    act = &lfg[k-1];

    for (i=0; i<l_m; i++)
    {
        act = act->next;
        act->val = max(act->val, act->lfg1->val);
        if ( i >= l_n )
            printf("%lu ", act->val);
    }
    printf("\n");
    return 0;
}
