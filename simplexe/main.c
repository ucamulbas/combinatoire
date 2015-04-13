#include <stdio.h>
#include <stdlib.h>


struct tableau
{
  float *tab;
  int sizex;
  int sizey;
  int xp,yp;
};
typedef struct tableau tab;



int choixPivot(tab *tab)
{
  int x, y, yt;
  int res=-54, tmp;
  int num, dem;
  for(x=0;x<tab->sizex-1;x++)
    if(tab->tab[(3*tab->sizex)+x]>0)
      break;

  if(x>=tab->sizex-1)
    return 0;

  tab->xp=x;
  num=tab->tab[(0*tab->sizex)+tab->sizex-1];
  dem=tab->tab[(0*tab->sizex)+tab->xp];
  if(dem > 0)
    {
      res = num/dem;
      yt=0;
    }
  for(y=1;y<tab->sizey-1;y++)
    {
      num=tab->tab[(y*tab->sizex)+tab->sizex-1];
      dem=tab->tab[(y*tab->sizex)+tab->xp];
      if(dem > 0)
	{
	  tmp = num/dem;
	  if(tmp<res && res > 0)
	    {
	      res=tmp;
	      yt=y;
	    }
	  if(res==-54)
	    {
	      res=tmp;
	      yt=y;
	    }
	  
	}
    }
  tab->yp=yt;
  printf("le pivot est en (%d ; %d)et est %.f\n", tab->xp, tab->yp,tab->tab[(tab->yp*tab->sizex)+tab->xp]);
  return 1;
}

void maj1(tab *tab)
{
  int x,y;
  for(y=0;y<tab->sizey;y++)
    for(x=0;x<tab->sizex;x++)
      if(x!=tab->xp && y!=tab->yp)
	tab->tab[(y*tab->sizex)+x]-=(tab->tab[(y*tab->sizex)+tab->xp]*tab->tab[(tab->yp*tab->sizex)+x])/tab->tab[(tab->yp*tab->sizex)+tab->xp];

  for(x=0;x<tab->sizex;x++)
    if(x!=tab->xp)
      tab->tab[(tab->yp*tab->sizex)+x]/=tab->tab[(tab->yp*tab->sizex)+tab->xp];

   for(y=0;y<tab->sizey;y++)
    if(y!=tab->yp)
      tab->tab[(y*tab->sizex)+tab->xp]=0;

   tab->tab[(tab->yp*tab->sizex)+tab->xp]=1;


}


int main(void)
{
  tab tab;
  tab.sizey=4;
  tab.sizex=6;
  tab.tab=malloc(tab.sizey*tab.sizex* sizeof *tab.tab);


  tab.tab[(0*tab.sizex)+0]=1;
  tab.tab[(0*tab.sizex)+1]=0;
  tab.tab[(0*tab.sizex)+2]=1;
  tab.tab[(0*tab.sizex)+3]=0;
  tab.tab[(0*tab.sizex)+4]=0;
  tab.tab[(0*tab.sizex)+5]=6;

  tab.tab[(1*tab.sizex)+0]=1;
  tab.tab[(1*tab.sizex)+1]=2;
  tab.tab[(1*tab.sizex)+2]=0;
  tab.tab[(1*tab.sizex)+3]=1;
  tab.tab[(1*tab.sizex)+4]=0;
  tab.tab[(1*tab.sizex)+5]=16;

  tab.tab[(2*tab.sizex)+0]=3;
  tab.tab[(2*tab.sizex)+1]=2;
  tab.tab[(2*tab.sizex)+2]=0;
  tab.tab[(2*tab.sizex)+3]=0;
  tab.tab[(2*tab.sizex)+4]=1;
  tab.tab[(2*tab.sizex)+5]=24;

  tab.tab[(3*tab.sizex)+0]=12;
  tab.tab[(3*tab.sizex)+1]=18;
  tab.tab[(3*tab.sizex)+2]=0;
  tab.tab[(3*tab.sizex)+3]=0;
  tab.tab[(3*tab.sizex)+4]=0;
  tab.tab[(3*tab.sizex)+5]=0;
  

  int x,y;
  for(y=0;y<tab.sizey;y++)
    {
      printf("\n");
      for(x=0;x<tab.sizex;x++)
	printf("%.2f ", tab.tab[(y*tab.sizex)+x]);
    }
  printf("\n");
  while(choixPivot(&tab))
    {
      maj1(&tab);
      for(y=0;y<tab.sizey;y++)
	{
	  printf("\n");
	  for(x=0;x<tab.sizex;x++)
	    printf("%.2f ", tab.tab[(y*tab.sizex)+x]);
	}
      printf("\n");
    }

 
 
}
