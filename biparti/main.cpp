#include <iostream>
#include <fstream>
#include <lemon/list_graph.h>
#include <lemon/lgf_writer.h>
#include <lemon/lgf_reader.h>

using namespace lemon;
using namespace std;

bool biparti()
{

  ListGraph g;
  ListGraph::NodeMap<int> tab(g);
  
  fstream fimport("mongraphe.lgf", fstream::in);
  graphReader(g, fimport)
    .nodeMap("couleur", tab)
    .run();
  fimport.close();
  
  int groupe = 0;
  for(ListGraph::EdgeIt e(g); e != INVALID; ++e)
    {

      if(tab[g.u(e)]==2)
	{
	  groupe=0;
	  tab[g.u(e)]=groupe;
	  groupe=!groupe;
	}
      else
	groupe=!tab[g.u(e)];

      if (tab[g.v(e)]==2)
	{
	  tab[g.v(e)]=groupe;
	  groupe=!groupe;
	}

      //cout << "les new id dans tab " << tab[g.id(g.u(e))] << " -> " << tab[g.id(g.v(e))] << endl;

      if(tab[g.v(e)]==tab[g.u(e)] && tab[g.v(e)] != 2)
	{
	  cout << "le graph n'est pas biparti" << endl;
	  return false;
	}
    }
  cout << "le graphe est biparti " << endl;
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
