#include <iostream>
#include <fstream>
#include <stack>
#include <lemon/list_graph.h>
#include <lemon/lgf_reader.h>

using namespace lemon;
using namespace std;

bool biparti()
{
  stack<ListGraph::Node> pile;
  ListGraph g;
  ListGraph::NodeMap<int> tab(g);
  ListGraph::Node noeudActuel;

  fstream fimport("mongraphe.lgf", fstream::in);
  graphReader(g, fimport)
    .nodeMap("couleur", tab)
    .run();
  fimport.close();
  
  int groupe = 0;
  for(ListGraph::NodeIt it(g); it!=INVALID;++it)
    {
      pile.push(it);
      break;
    }

  while(!pile.empty())
    {
      noeudActuel = pile.top();
      pile.pop();
      if(tab[noeudActuel]==2)
	{
	  cout << "je colorie " << g.id(noeudActuel) << " en " << groupe << endl;
	  tab[noeudActuel]=groupe;
	  groupe=!groupe;
	}
      else
	groupe=!tab[noeudActuel];
      for(ListGraph::IncEdgeIt it(g, noeudActuel); it != INVALID ; ++it)
	{
	  if(tab[g.target(it)]==2)
	    {
	      pile.push(g.target(it));
	      tab[g.target(it)]=groupe;
	    }
	  if(tab[noeudActuel]==tab[g.target(it)])
	    {
	      cout << "le graph n'est pas biparti " << endl;
	      return false;
	    }
	}
    }


  cout << "le graphe est biparti " << endl;
  for(ListGraph::NodeIt it(g);it!=INVALID;++it)
    cout << "id: " << g.id(it) << " couleur: " << tab[it] << endl;
  return true;
}


int main()
{
  bool bip;
 
  // ListGraph::Node d1 = g.addNode();
  // ListGraph::Node d2 = g.addNode();
  // ListGraph::Node g1 = g.addNode();
  // ListGraph::Node g2 = g.addNode();
  // ListGraph::Edge e = g.addEdge(d1, g1);
  // g.addEdge(g1,d2);
  // g.addEdge(g2,d2);
  // g.addEdge(g2,d1);
 
  //cout << "d1 "<< g.id(d1) << " d2 " << g.id(d2) << " g1 " << g.id(g1) << " g2 " << g.id(g2) << endl;
  // tab[d1]=2;
  // tab[d2]=2;
  // tab[g1]=2;
  // tab[g2]=2;

  // fstream fexport("mongraphe.lgf", fstream::out);
  // graphWriter(g, fexport)
  //   .nodeMap("couleur", tab)
  //   .run();
  // fexport.close();

  bip=biparti();
  cout << bip << endl;
  return 0;
}
