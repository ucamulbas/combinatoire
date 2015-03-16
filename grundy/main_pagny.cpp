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
  ListDigraph::NodeMap<int> &_init;
public:
  comp(ListDigraph &g, ListDigraph::NodeMap<int> &degre, ListDigraph::NodeMap<int> &init ) : _g(g) , _degre(degre) , _init(init)  {};
  
  int operator()(ListDigraph::Node a, ListDigraph::Node b){
    if(!_init[a] && !_init[b])
      if(_degre[a] < _degre [b])
	return 1;
      else
	return 0;
  }
};

int main(void)
{
  ListDigraph g;
  ListDigraph::NodeMap<int> degre(g);
  ListDigraph::NodeMap<int> init(g);
  vector<ListDigraph::Node> tab;
  fstream fimport("test.lgf", fstream::in);
  digraphReader(g, fimport)
    .run();
  fimport.close();
  for(ListDigraph::NodeIt nit(g); nit!=INVALID;++nit)
    {
      degre[nit]=0;
      init[nit]=0;
      for(ListDigraph::OutArcIt ait(g,nit) ; ait!=INVALID;++ait,degre[nit]++);
      cout << g.id(nit) << " est de degre " << degre[nit] << endl;
      tab.push_back(nit);
   }
 

  sort(tab.begin(),tab.end(),comp(g,degre,init));

  tab.erase(tab.begin()+1);
  cout <<"__________________________" << endl;
  for(int i = 0 ; i < tab.size() ; i++)
    cout << g.id(tab[i]) << " est de degre " << degre[tab[i]] << endl;
  
  return 0;
}