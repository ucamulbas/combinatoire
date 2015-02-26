#include <iostream>
#include <fstream>
#include <lemon/list_graph.h>
#include <lemon/lgf_reader.h>
#include <queue>
using namespace lemon;
using namespace std;


int main (void)
{
  ListGraph g;
  ListGraph::Node noeudActuel;
  ListGraph::NodeMap<int> map(g);
  queue<ListGraph::Node> file;
  fstream fimport("mongraphe.lgf", fstream::in);
  graphReader(g, fimport)
    .nodeMap("couleur", map)
    .run();
  fimport.close();
  
  for(ListGraph::NodeIt n(g) ; n != INVALID ; ++n)
    {
      file.push(n);
      break;
    }
  
  /*
    map = 2: non visite
    map = 1: visite
    map = 0: explore
  */
  while(!file.empty())
    {
      noeudActuel=file.front();
      file.pop();
      cout << "je visite le noeud " << g.id(noeudActuel) << endl;
      if(map[noeudActuel]!=0)
	{
	  for(ListGraph::IncEdgeIt out(g, noeudActuel) ; out != INVALID ; ++out)
	    {
	      if((g.id(g.u(out)) != g.id(noeudActuel)) && map[g.u(out)] == 2)
		{
		  file.push(g.u(out));
		  map[g.u(out)]=1;
		}
	      if((g.id(g.v(out)) != g.id(noeudActuel)) && map[g.v(out)] == 2)
		{
		  file.push(g.v(out));
		  map[g.v(out)]=1;
		}
	    }
	  map[noeudActuel]=0;
	}
    }
  return 0;
}
