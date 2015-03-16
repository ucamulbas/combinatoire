#include <iostream>
#include <fstream>
#include <stack>
#include <lemon/list_graph.h>
#include <lemon/lgf_reader.h>

using namespace lemon;
using namespace std;

void f_connexe(ListDigraph &g, ListDigraph::Node noeudDepart, ListDigraph::NodeMap<int> &supp)
{
  ListDigraph::NodeMap<int> plus(g);
  ListDigraph::NodeMap<int> moins(g);
  ListDigraph::Node nit;
  plus[noeudDepart]=1;
  moins[noeudDepart]=1;
  stack<ListDigraph::Node> pile;

  cout << "depart : " << g.id(noeudDepart) << endl;
  pile.push(noeudDepart);
  while(!pile.empty())
    {
      nit=pile.top();
      pile.pop();
      if(supp[nit]!=1)
	{
	  for(ListDigraph::OutArcIt oait(g,nit) ; oait != INVALID ; ++oait)
	    {
	      if(plus[nit]==1 && !plus[g.target(oait)])
		{
		  plus[g.target(oait)]=1;
		  pile.push(g.target(oait));
		}
	    }
	  for(ListDigraph::InArcIt iait(g,nit) ; iait != INVALID ; ++iait)
	    {
	      if(moins[nit]==1 && !moins[g.source(iait)])
		{
		  moins[g.source(iait)]=1;
		  pile.push(g.source(iait));
		}
	    }
	}
    }

  for(ListDigraph::NodeIt nite(g) ; nite != INVALID ; ++nite)
    if(plus[nite]==1 && moins[nite]==1)
      {
	cout << g.id(nite) << endl;
	supp[nite]=1;
      }
  cout << "_______________________________________" << endl;
}

int main(void)
{
  ListDigraph g;
  ListDigraph::NodeMap<int> supp(g);
  fstream fimport("test.lgf", fstream::in);
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
