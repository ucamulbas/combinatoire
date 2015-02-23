#include <iostream>
#include <lemon/list_graph.h>
#include <fstream>
#include <lemon/lgf_writer.h>
#include <queue>

using namespace lemon;
using namespace std;

int main (void)
{
  queue<ListGraph::Node> file;
  ListGraph g;
  ListGraph::Node actuel;
  ListGraph::Node a = g.addNode();
  ListGraph::Node b = g.addNode();
  ListGraph::Node d = g.addNode();
  g.addEdge(a,b);
  g.addEdge(b,d);

   for (ListGraph::NodeIt n(g); n != INVALID; ++n)
     {
       file.push(n);
       break;
     }
   while(file.size()!=0)
     {
       actuel=file.front();
       file.pop();
       for (ListGraph::IncEdgeIt e(g, actuel); e != INVALID; ++e) {
	 cout << "je vais de " << g.id(g.u(e)) << " a " << g.id(g.v(e)) << endl;
       }
     }


  return 0;
}
