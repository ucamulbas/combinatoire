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

int main(void)
{
  ListDigraph g;
  ListDigraph::NodeMap<int> degre(g);
  vector<ListDigraph::Node> tab;
  fstream fimport("test.lgf", fstream::in);
  digraphReader(g, fimport)
    .run();
  fimport.close();
 for(ListDigraph::NodeIt nit(g); nit!=INVALID;++nit)
   {
     degre[nit]=0;
     tab.push_back(nit);
   }
 
  for(ListDigraph::NodeIt nit(g); nit!=INVALID;++nit){
    for(ListDigraph::OutArcIt ait(g,nit) ; ait!=INVALID;++ait,degre[nit]++);
    cout << g.id(nit) << " est de degre " << degre[nit] << endl;
  }

  sort(tab.begin(),tab.end(),comp(g,degre));

  
  cout <<"__________________________" << endl;
  for(int i = 0 ; i < tab.size() ; i++)
    cout << g.id(tab[i]) << " est de degre " << degre[tab[i]] << endl;
  
  return 0;
}
