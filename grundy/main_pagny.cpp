#include <iostream>
#include <fstream>
#include <vector>
#include <lemon/list_graph.h>
#include <lemon/lgf_reader.h>

using namespace lemon;
using namespace std;

struct comp{
private:
  ListDigraph &_g;
  ListDigraph::NodeMap<int> &_degre;
public:
  comp(ListDigraph &g, ListDigraph::NodeMap<int> &degre) : _g(g) , _degre(degre) {};
  
  int operator()(ListDigraph::Node a, ListDigraph::Node b){
      if(_degre[a] < _degre [b])
	return 1;
      else
	return 0;
  }
};


void grundy (ListDigraph &g, ListDigraph::NodeMap<int> &degre, ListDigraph::NodeMap<int> &grund, vector<ListDigraph::Node> tab)
{
  ListDigraph::Node noeudActuel;
  int grun, ok;
  while(!tab.empty())
    {
      noeudActuel = tab[0];
      cout << "je traite le noeud " << g.id(noeudActuel) << endl;
      grun = 0;
      do
	{
	  ok = 1;
	  for(ListDigraph::OutArcIt oait(g, noeudActuel) ; oait != INVALID ; ++ oait)
	    {
	      if(grund[g.target(oait)]==grun)
		{
		  ok=0;
		  grun++;
		  break;
		}
	    }
	}while(ok!=1);
      grund[noeudActuel]=grun;
      cout << g.id(noeudActuel) << " a un grund de " << grund[noeudActuel] << endl;
      for(ListDigraph::InArcIt iait(g, noeudActuel) ; iait != INVALID ; ++ iait)
	{
	  degre[g.source(iait)]-=1;
	}
      tab.erase(tab.begin());
      sort(tab.begin(),tab.end(),comp(g,degre));
    }
}


int main(void)
{
  ListDigraph g;
  ListDigraph::NodeMap<int> degre(g);
  ListDigraph::NodeMap<int> grund(g);
  vector<ListDigraph::Node> tab;
  vector<ListDigraph::Node> tab2;
  fstream fimport("test.lgf", fstream::in);
  digraphReader(g, fimport)
    .run();
  fimport.close();


  for(ListDigraph::NodeIt nit(g); nit!=INVALID;++nit)
    {
      degre[nit]=0;
      grund[nit]=-1;
      for(ListDigraph::OutArcIt ait(g,nit) ; ait!=INVALID;++ait,degre[nit]++);
      cout << g.id(nit) << " est de degre " << degre[nit] << endl;
      tab.push_back(nit);
   }
 

  sort(tab.begin(),tab.end(),comp(g,degre));
  tab2=tab;

  grundy(g,degre,grund,tab2);

  //tab.erase(tab.begin()+1);
  cout <<"__________________________" << endl;
  for(int i = 0 ; i < tab.size() ; i++)
    cout << g.id(tab[i]) << " a un grund de  " << grund[tab[i]] << endl;
  
  return 0;
}
