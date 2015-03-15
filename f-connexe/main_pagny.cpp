#include <iostream>
#include <fstream>
#include <lemon/list_graph.h>
#include <lemon/lgf_reader.h>

using namespace lemon;
using namespace std;

void f_connexe(ListDigraph &g, ListDigraph::Node noeudDepart, ListDigraph::NodeMap<int> &supp)
{
  ListDigraph::NodeMap<int> plus(g);
  ListDigraph::NodeMap<int> moins(g);
  plus[noeudDepart]=1;
  moins[noeudDepart]=1;

  cout << "depart : " << g.id(noeudDepart) << endl;
  for(ListDigraph::OutArcIt oait(g,noeudDepart) ; oait != INVALID ; ++oait)
    {
      plus[g.target(oait)]=1;
      
    }
  for(ListDigraph::InArcIt iait(g,noeudDepart) ; iait != INVALID ; ++iait)
    {
      moins[g.source(iait)]=1;
    }

  for(ListDigraph::NodeIt nit(g) ; nit != INVALID ; ++nit)
    {
      if(supp[nit]!=1)
	{
	  for(ListDigraph::OutArcIt oait(g,nit) ; oait != INVALID ; ++oait)
	    {
	      if(plus[nit]==1)
		{
		  plus[g.target(oait)]=1;
		}
	    }
	  for(ListDigraph::InArcIt iait(g,nit) ; iait != INVALID ; ++iait)
	    {
	      if(moins[nit]==1)
		{
		  moins[g.source(iait)]=1;
		}
	    }
	}
    }

  for(ListDigraph::NodeIt nit(g) ; nit != INVALID ; ++nit)
    if(plus[nit]==1 && moins[nit]==1)
      {
	cout << g.id(nit) << endl;
	supp[nit]=1;
      }
  cout << "_______________________________________" << endl;
}

int main(void)
{
  ListDigraph g;
  ListDigraph::NodeMap<int> supp(g);
  fstream fimport("mongraphe.lgf", fstream::in);
  digraphReader(g, fimport)
    .run();
  fimport.close();

  
  for(ListDigraph::NodeIt nit(g) ; nit != INVALID ; ++nit)
    supp[nit]=0;

  for(ListDigraph::NodeIt nit(g) ; nit != INVALID ; ++nit)
    if(!supp[nit])
      f_connexe(g,nit,supp);
  
  return 0;
}
