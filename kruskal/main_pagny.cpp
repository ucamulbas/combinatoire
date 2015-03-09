#include <iostream>
#include <fstream>
#include <vector>
#include <lemon/list_graph.h>
#include <lemon/lgf_reader.h>
#include <lemon/lgf_writer.h>

using namespace lemon;
using namespace std;


void kruskal(ListGraph &g, ListGraph::NodeMap<int> &represent, ListGraph::EdgeMap<int> &degre, vector<ListGraph::Edge> tab)
{

  for(ListGraph::EdgeIt nit(g) ; nit != INVALID ; ++nit)
    degre[nit]=0;

  for(int i = tab.size() - 1 ; i >= 0 ; i--)
    {
      cout << "je test l'edge " << g.id(tab[i]) << endl;
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

int main(void)
{
  ListGraph g;
  ListGraph::NodeMap<int> represent(g);
  ListGraph::EdgeMap<int> degre(g);
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
    {
      if(!tab.size())
	tab.push_back(eit);
      else
	{
	  size = tab.size();
	  for(i = 0 ; i < size ; i++)
	    {
	      if(degre[tab[i]] < degre[eit])
		{
		  tab.push_back(tab[size-1]);
		  for(int j = size ; j > i ; j--)
		      tab[j]=tab[j-1];
		  tab[i]=eit;
		  break;
		}
	    }
	  if(i==tab.size())
	    tab.push_back(eit);
      	}
    }

  cout << "mon tableau" << endl;
 for(int i = tab.size() - 1 ; i >= 0 ; i--)
   cout << degre[tab[i]] << endl;
 cout <<"fin du tableau"<<endl;
 
  kruskal(g,represent,degre,tab);

  cout << "les edges choisi sont:" << endl;

  for(ListGraph::EdgeIt eit(g) ; eit != INVALID ; ++eit)
    {
      if(degre[eit]==1)
	cout << g.id(eit) << " : " << g.id(g.u(eit)) << " -> " << g.id(g.v(eit)) << endl;
    }
  
  return 0;
}
