#include <iostream>
#include <fstream>
#include <vector>
#include <lemon/list_graph.h>
#include <lemon/lgf_reader.h>
#include <lemon/lgf_writer.h>

using namespace lemon;
using namespace std;

ListGraph g;
ListGraph::EdgeMap<int> degre(g);

void kruskal(ListGraph &g, ListGraph::NodeMap<int> &represent, ListGraph::EdgeMap<int> &degre, vector<ListGraph::Edge> tab)
{

  for(ListGraph::EdgeIt nit(g) ; nit != INVALID ; ++nit)
    degre[nit]=0;

  for(int i = tab.size() - 1 ; i >= 0 ; i--)
    {
      if(represent[g.u(tab[i])] != represent[g.v(tab[i])])
	{
	  degre[tab[i]]=1;
	  for(ListGraph::NodeIt propage(g) ; propage != INVALID ; ++propage)
	    {
	      if(represent[propage]==represent[g.v(tab[i])])
		represent[propage]=represent[g.u(tab[i])];
	    }
	}
    }
}

bool compar (ListGraph::Edge a, ListGraph::Edge b)
{
  if(degre[a] > degre [b])
    return 1;
  else
    return 0;
}

int main(void)
{
  ListGraph::NodeMap<int> represent(g);
  vector<ListGraph::Edge> tab;
  int i, size;
  fstream fimport("graph.lgf", fstream::in);
  graphReader(g, fimport)
    .nodeMap("represent", represent)
    .edgeMap("value", degre)
    .run();
  fimport.close();

  /*
    Parcour et triage des edges
  */
  for(ListGraph::EdgeIt eit(g) ; eit != INVALID ; ++eit)
	tab.push_back(eit);

  
  sort(tab.begin(),tab.end(),compar);

  
  kruskal(g,represent,degre,tab);

  cout << "les edges choisi sont:" << endl;

  for(ListGraph::EdgeIt eit(g) ; eit != INVALID ; ++eit)
    {
      if(degre[eit]==1)
	cout << g.id(eit) << " : " << g.id(g.u(eit)) << " -> " << g.id(g.v(eit)) << endl;
    }
  
  return 0;
}
