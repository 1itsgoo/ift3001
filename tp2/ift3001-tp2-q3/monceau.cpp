// Ce fichier n'est qu'un rappel d'utilisation des monceaux. Vous
// n'avez pas a le compiler, ni a l'utiliser.
//
// Ce code est ecrit en C++ 11.

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

// Imprime un triplet d'entiers
std::ostream& operator<<(std::ostream& os, const std::tuple<int, int, int> t) {
  os << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << ")";
  return os;
}

// Imprime un vecteur
template <class InputIterator>
void imprime_vecteur(const std::string& message, InputIterator first, InputIterator last) {
  std::cout << message << std::endl;
  for (InputIterator i = first; i != last; i++)
    std::cout << *i << " ";
  std::cout << std::endl;
}

void monceau() {
  int donnees[8] = {3, 6, 2, 0, 24, 12, 68, 42};
  std::vector<int> monceau(donnees, donnees + 8);

  // La fonction std::make_heap modifie le vecteur afin qu'il satisfasse les proprietes du monceau.
  imprime_vecteur("Monceau avant sa creation", monceau.begin(), monceau.end());
  std::make_heap(monceau.begin(), monceau.end()); // Theta(n) ou n = monceau.size()
  imprime_vecteur("Monceau apres sa creation", monceau.begin(), monceau.end());

  // Pour ajouter un element au monceau
  monceau.push_back(100); // Theta(1)  (analyse amortie)
  std::push_heap(monceau.begin(), monceau.end()); // Theta(log n) en pire cas
  imprime_vecteur("Apres l'ajout de 100", monceau.begin(), monceau.end());

  // Pour extraire la racine du monceau
  std::pop_heap(monceau.begin(), monceau.end()); // Place la racine a la fin du vecteur et retablie les proprietes du monceau. Pire cas: Theta(log n)
  int element_extrait = monceau.back();		 // L'element extrait est a la fin du vecteur. Theta(1)
  monceau.pop_back();				 // On retire le dernier element du vecuteur. Theta(1)  (analyse amortie)
  imprime_vecteur("Apres l'extraction de la racine", monceau.begin(), monceau.end());

  // Voici les memes operations, mais pour un monceau inverse
  std::make_heap(monceau.begin(), monceau.end(), std::greater<int>());
  imprime_vecteur("Apres la creation d'un monceau inverse", monceau.begin(), monceau.end());
  monceau.push_back(1);
  std::push_heap(monceau.begin(), monceau.end(), std::greater<int>());
  imprime_vecteur("Apres l'ajout de 1", monceau.begin(), monceau.end());
  std::pop_heap(monceau.begin(), monceau.end(), std::greater<int>());
  element_extrait = monceau.back();
  monceau.pop_back();
  imprime_vecteur("Apres l'extraction de la racine 10", monceau.begin(), monceau.end());

  // Vous pouvez construire des monceau de tuples. L'opérateur < entre
  // deux tuples compare les premieres entrees des tuples. Si elles
  // sont identiques, alors ce sont les deuxiemes entrees qui sont
  // comparees.
  std::vector<std::tuple<int, int, int> > monceau_tuples;
  monceau_tuples.push_back(std::make_tuple(1, 2, 3));
  monceau_tuples.push_back(std::make_tuple(2, 3, 1));
  monceau_tuples.push_back(std::make_tuple(3, 1, 2));
  monceau_tuples.push_back(std::make_tuple(3, 2, 1));
  imprime_vecteur("Monceau de tuple avant sa creation", monceau_tuples.begin(), monceau_tuples.end());
  std::make_heap(monceau_tuples.begin(), monceau_tuples.end());
  imprime_vecteur("Monceau de tuple apres sa creation", monceau_tuples.begin(), monceau_tuples.end());
  // ...
}

int main(void) {
  monceau();
  return 0;
}
