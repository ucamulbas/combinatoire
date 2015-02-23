#include <iostream>
#include <lemon/list_graph.h>
#include <fstream>
#include <lemon/lgf_writer.h>

using namespace lemon;
using namespace std;

int main (void)
{
  ListGraph g;
  ListGraph::Node a = g.addNode();
  ListGraph::Node b = g.addNode();
  ListGraph::Node d = g.addNode();
  g.addEdge(a,b);
  g.addEdge(b,d);

  for (ListGraph::NodeIt n(g); n != INVALID; ++n) {
    int cnt = 0;
    for (ListGraph::IncEdgeIt e(g, n); e != INVALID; ++e) {
      cout << "je vais de " << g.id(g.u(e)) << " a " << g.id(g.v(e)) << endl;
    }
  }


  return 0;
}
