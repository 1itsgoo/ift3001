#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// Vous pouvez inclure d'autres librairies, pourvu qu'elles proviennent de la STL.
class DisjointSetNode {
  public:
  int m_id = -1;
  DisjointSetNode* m_parent = NULL;
  int m_sortie = -1;
  int m_echeance = -1;

  DisjointSetNode() {}

  DisjointSetNode(int id, DisjointSetNode* parent, int sortie, int echeance)
    : m_id(id), m_parent(parent), m_sortie(sortie), m_echeance(echeance)
  { }
};

vector< DisjointSetNode > countingSort(vector<DisjointSetNode> input)
{
    vector< vector< DisjointSetNode > > countArray = 
      vector< vector < DisjointSetNode > >(input.size());

    // On peut utiliser input.size() ici parce que l'etendue des valeurs
    // possibles est la meme que l'etendue des jours, donc le nombre de jours.
    for (unsigned int i=0;i<input.size();i++)
    {
      countArray[input[i].m_echeance].push_back(input[i]);
    }

    vector< DisjointSetNode > output = vector< DisjointSetNode >(input.size());
    int outputindex=0;
    for (unsigned int j=0;j<input.size();j++)
    {
        while (countArray[j].size() != 0)
        {
            output[outputindex++] = countArray[j].back();
            countArray[j].pop_back();
        }
    }

    return output;
}

DisjointSetNode* trouver(DisjointSetNode* node) 
{
  DisjointSetNode* currentNode = node;
  while(currentNode->m_parent != NULL)
  {
    currentNode = currentNode->m_parent;
  }
  // Compression de l'arbre.
  DisjointSetNode* representantNode = currentNode;
  currentNode = node;
  while(node != representantNode)
  {
    DisjointSetNode* t = currentNode->m_parent;
    currentNode->m_parent = representantNode;
    node = t;
  }

  // On retourne pas tout à fait le noeud représentant, la date qu'il
  // représente.
  return representantNode;
}

void fusionner(DisjointSetNode* lhs, DisjointSetNode* rhs,
    vector<DisjointSetNode>& representants)
{
  // Attention, quand il s'agit de représentants, on se sert de m_echeance pour
  // compter la cardinalite de l'ensemble.
  //representants[lhs].m_parent = &(representants[rhs]);

  if(lhs->m_echeance > rhs->m_echeance)
  {
    rhs->m_parent = lhs;
    lhs->m_sortie = rhs->m_sortie;
    lhs->m_echeance += rhs->m_echeance;
  }
  else
  {
    lhs->m_parent = rhs;
    rhs->m_echeance += lhs->m_echeance;
  }
}

void printVector( const vector< DisjointSetNode >& input)
{
  for(unsigned int i=0; i < input.size(); i++)
  {
    std::cout << input[i].m_id << 
      ": (" << input[i].m_sortie << ", " << input[i].m_echeance << "), ";
  }
  std::cout << std::endl;
}

// Calcule l'ordonnancement des travaux.
// Entrees:
//   temps_sortie: le travail i peut commencer au jour temps_sortie[i]
//   echeances: le travail i peut se faire au plus tard au jour echeances[i]
// Sortie:
//   solution: le travail i se realise au jour solution[i]
void ordonnancement(const std::vector<unsigned int>& temps_sortie, 
        const std::vector<unsigned int>& echeances, 
        std::vector<unsigned int>& solution) 
{
  const unsigned int nb_travaux = temps_sortie.size(); // Il y a autant de jours que de travaux.
  assert(echeances.size() == nb_travaux);
  for (unsigned int i = 0; i < nb_travaux; i++) {
    assert(temps_sortie[i] < nb_travaux);
    assert(echeances[i] < nb_travaux);
  }
  
  // Inserez votre code ici.
  
  // On crée les structures de données qui nous seront utiles.
  std::vector< DisjointSetNode > travaux;
  for(unsigned int i=0; i < nb_travaux; i++)
  {
    travaux.push_back(DisjointSetNode(i, NULL, temps_sortie[i], echeances[i]));
  }

  // On trie ce tableau en utilisant le tri par dénombrement. Comme l'étendue
  // des valeurs à trier est la même que le nombre de jour, ce tri se fait en
  // O(n).
  travaux = countingSort(travaux);

  // On initialise les ensembles disjoints. On a un ensemble par jour de sortie dans
  // l'état initial. À terme les ensembles représenteront "l'ensemble des
  // travaux qui peuvent minimalement être faits à la journée n selon la
  // solution qu'on a trouvé jusqu'à present".

  vector<DisjointSetNode> representants = vector<DisjointSetNode>();
  // On met des placeholder dans le tableau des représentants, pour être certain
  // qu'il y a un représentant par jour.
  for(unsigned int i=0; i < nb_travaux; i++)
  {
    representants.push_back(DisjointSetNode(0, NULL, i, 0));
  }

  vector<DisjointSetNode*> pRepresentants = 
      vector<DisjointSetNode*>(nb_travaux, NULL);
  for(unsigned int i=0; i < nb_travaux; i++)
  {
    pRepresentants[i] = &(representants[i]);
  }

  for(unsigned int i = 0; i < nb_travaux; i++)
  {
    travaux[i].m_parent = &(representants[travaux[i].m_sortie]);
    // ATTENTION: on se sert de m_echeance pour encoder le nombre de noeuds 
    // représentés, dans le cas où le noeud est un des
    // représentants-placeholders.
    representants[travaux[i].m_sortie].m_echeance++;
  }

  // On itère sur la liste de travaux, classé en ordre croissant de date de
  // remise. Le travaux le plus petit est effectué le jour indiqué par
  // l'ensemble dont il fait partie. Ensuite on fusionne l'ensemble dont il
  // faisait partie avec l'ensemble représentant le jour suivant. En effet les
  // travaux qui pouvaient être minimalement être effectués au jour n doivent
  // maintenant être effectués plus tard, parce qu'on a déjà choisi un travail
  // au jour n.
  solution = vector<unsigned int>(nb_travaux);
  for(unsigned int i=0; i < nb_travaux; i++)
  {
    DisjointSetNode* representant = trouver(&travaux[i]);
    unsigned int jourMinimum = representant->m_sortie;
    solution[travaux[i].m_id] = jourMinimum;
    if(jourMinimum + 1 < nb_travaux)
    {
      fusionner(representant, &representants[jourMinimum + 1], representants);
    }
  }
}
