#include <iostream>
#include <fstream>
#include <lemon/list_graph.h>
#include <lemon/lgf_reader.h>
#include <queue>
using namespace lemon;
using namespace std;

struct comp{
private:
  ListDigraph &_g;
  ListDigraph::NodeMap<int> &_degre;
public:
  comp(ListDigraph &g, ListDigraph::NodeMap<int> &degre) : _g(g) , _degre(degre) {};
  
  int operator()(ListDigraph::Node a, ListDigraph::Node b){
      if(_degre[a] <_degre [b])
	return 1;
      else
	return 0;
  }
};


int main (void)
{
  ListDigraph g;
  ListDigraph::Node noeudActuel;
  ListDigraph::NodeMap<int> degre(g);
  ListDigraph::NodeMap<int> grund(g);
  queue<ListDigraph::Node> file;
  vector<ListDigraph::Node> tab;
  fstream fimport("test.lgf", fstream::in);
  digraphReader(g, fimport)
    .run();
  fimport.close();


  for(ListDigraph::NodeIt nit(g); nit!=INVALID;++nit)
    {
      degre[nit]=0;
      grund[nit]=-1;
      for(ListDigraph::InArcIt ait(g,nit) ; ait!=INVALID;++ait,degre[nit]++);
      cout << g.id(nit) << " est de degre " << degre[nit] << endl;
      tab.push_back(nit);
   }
 

  sort(tab.begin(),tab.end(),comp(g,degre));
  //cout << "le 1er noeud est " << g.id(tab[0]) << " avec un degre de " << degre[tab[0]] << endl;
  file.push(tab[0]);
  tab.clear();
  
  while(!file.empty())
    {
      noeudActuel=file.front();
      file.pop();
      tab.push_back(noeudActuel);
       for(ListDigraph::OutArcIt oait(g, noeudActuel) ; oait != INVALID ; ++ oait)
	 {
	   file.push(g.target(oait));
	   tab.push_back(g.target(oait));
	 }
    }
  
  int grun, ok;
  while(!tab.empty())
    {
      noeudActuel = tab[tab.size()-1];
      //cout << "je traite le noeud " << g.id(noeudActuel) << endl;
      grun = 0;
      if(grund[noeudActuel]==-1)
	{
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
	}
      tab.erase(tab.begin()+tab.size()-1);
      //cout << "le dernier noeud est  " << g.id(tab[tab.size()-1]) << endl;
    }
  
  return 0;
}
