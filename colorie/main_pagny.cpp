#include <iostream>
#include <fstream>
#include <vector>
#include <lemon/list_graph.h>
#include <lemon/lgf_reader.h>

using namespace lemon;
using namespace std;


int main(void)
{
  ListGraph g;
  ListGraph::Node noeudActuel;
  ListGraph::NodeMap<int> couleur(g);
  ListGraph::NodeMap<int> degre(g);
  vector<ListGraph::Node> tab;
  int deg, i, size, couleurActuel = 1, adj;
   fstream fimport("mongraphe.lgf", fstream::in);
  graphReader(g, fimport)
    .nodeMap("couleur", couleur)
    .run();
    fimport.close();


    test(g, couleur);

    
  /*
    Pour chaque noeud, je compte son nombre de voisin et
    on range le noeud dans tab dans l'ordre decroissant en fonction
    de son nombre de voisin
  */
  for(ListGraph::NodeIt nit(g) ; nit != INVALID ; ++nit)
    {
      deg = 0;
      for(ListGraph::IncEdgeIt eit(g, nit) ; eit != INVALID ; ++eit)
	deg++;
      degre[nit]=deg;
      cout << g.id(nit) << " : " << degre[nit] << endl;
      if(!tab.size())
	tab.push_back(nit);
      else
	{
	  size = tab.size();
	  for(i = 0 ; i < size ; i++)
	    {
	      if(degre[tab[i]] < degre[nit])
		{
		  tab.push_back(tab[size-1]);
		  for(int j = size ; j > i ; j--)
		    tab[j]=tab[j-1];
		  tab[i]=nit;
		}
	    }
	  if(i==tab.size())
	    tab.push_back(nit);
	}
    }
  
  for(int i = 0 ; i < tab.size() ; i++)
    {
      noeudActuel = tab[i];
      if(couleur[noeudActuel]==-1)
       	{
	  couleur[noeudActuel]=couleurActuel;
	  if(i!=tab.size()-1)
	    {
	      for(int j = i + 1 ; j < tab.size() ; j++)
		{
		  adj=0;
		  if(couleur[tab[j]]==-1)
		    {
		      for(ListGraph::IncEdgeIt it(g,tab[j]) ; it != INVALID ; ++it)
			{
			  if((g.id(g.u(it)) == g.id(noeudActuel)) || (g.id(g.v(it)) == g.id(noeudActuel)))
			    {
			      adj=1;
			      break;
			    }
			  else
			    {
			      for(ListGraph::IncEdgeIt it(g,tab[j]) ; it != INVALID ; ++it)
				{
				  if(couleur[g.target(it)]==couleurActuel)
				    {
				      adj=1;
				      break;
				    }
				}
			    }
			}
		      if(!adj)
			{
			  couleur[tab[j]]=couleurActuel;
			}
		    }
		}
	    }
	  couleurActuel++;
	 }
    }

  cout << "il faut " << couleurActuel-1 << " couleur pour ce graph " << endl;
  for(ListGraph::NodeIt n(g) ; n != INVALID ; ++n)
    cout << g.id(n) << " couleur : " << couleur[n] << endl;

  return 0;
}
