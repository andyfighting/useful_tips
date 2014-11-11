#include <stdio.h>
#include <stdlib.h>

typedef void *(*data_cmp)(int *,int *);

static void *real_cmp(int *m,int *n)
{
  return (void *)((*m > *n) ? "gt" : "lt");
}

static void *get_cmp_result(data_cmp cmp_int,int *m_data,int *n_data)
{
  return cmp_int(m_data,n_data);
}

int main(int argc,char *argv[])
{
  int a = 9;
  int b = 8;

  printf("a %s b \n",(char *)get_cmp_result(real_cmp,&a,&b));

  return 0;
}
