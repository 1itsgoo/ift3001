#include <cassert>
#include <iostream>
#include <vector>

#include "ordonnancement.hpp"

// Retourne vrai si le vecteur solution est une solution valide a l'instance du probleme donnee par les vecteurs temps_sortie et echeances.
bool solutionValide(const std::vector<unsigned int>& temps_sortie, const std::vector<unsigned int>& echeances, const std::vector<unsigned int>& solution) {
  // Test si l'instance est valide
  const unsigned int nb_travaux = temps_sortie.size(); // Il y a autant de travaux que de jours
  assert(temps_sortie.size() == echeances.size());
  for (unsigned int i = 0; i < nb_travaux; i++) {
    assert(temps_sortie[i] < nb_travaux);
    assert(echeances[i] < nb_travaux);
  }

  if (solution.size() != nb_travaux) {
    std::cerr << "Certains travaux n'ont pas ete planifies" << std::endl;
    return false;
  }
  std::vector<bool> jour_utilise(nb_travaux, false);
  for (unsigned int i = 0; i < nb_travaux; i++) {
    if (solution[i] < temps_sortie[i]) {
      std::cerr << "Le travail " << i << " est realise trop tot" << std::endl;
      return false;
    }
    if (echeances[i] < solution[i]) {
      std::cerr << "Le travail " << i << " est realise trop tard" << std::endl;
      return false;
    }
    if (jour_utilise[solution[i]]) {
      std::cerr << "Plusieurs travaux s'executent au jour " << solution[i] << std::endl;
      return false;
    }
    jour_utilise[solution[i]] = true;
  }
  return true;    
}

bool testGenerique(const unsigned int* temps_sorties, const unsigned int* echeances, unsigned int nb_travaux) {
  const std::vector<unsigned int> vecteur_temps_sorties(temps_sorties, temps_sorties + nb_travaux);
  const std::vector<unsigned int> vecteur_echeances(echeances, echeances + nb_travaux);

  try {
    std::vector<unsigned int> solution;
    ordonnancement(vecteur_temps_sorties, vecteur_echeances, solution);
    std::cout << "Solution retournee:";
    for (std::vector<unsigned int>::const_iterator i = solution.begin(); i != solution.end(); i++)
      std::cout << " " << *i;
    std::cout << std::endl;
    return solutionValide(vecteur_temps_sorties, vecteur_echeances, solution);
  } catch (...) {
    return false;
  }
}

bool testEnonce(void) {
  const unsigned int sorties[5] = {1, 1, 0, 2, 0};
  const unsigned int echeances[5] = {2, 2, 4, 4, 1};
  return testGenerique(sorties, echeances, 5);
}

bool deuxiemeTest(void) {
  const unsigned int sorties[6] = {0, 0, 1, 1, 2, 2};
  const unsigned int echeances[6] = {5, 5, 4, 4, 3, 3};
  return testGenerique(sorties, echeances, 6);
}

bool echeancesIdentiques(void) {
  const unsigned int sorties[6] = {2, 0, 3, 1, 5, 4};
  const unsigned int echeances[6] = {5, 5, 5, 5, 5, 5};
  return testGenerique(sorties, echeances, 6);
}

bool sortiesIdentiques(void) {
  const unsigned int sorties[6] = {0, 0, 0, 0, 0, 0};
  const unsigned int echeances[6] = {2, 0, 3, 1, 5, 4};
  return testGenerique(sorties, echeances, 6);
}

bool exempleComplexe(void) {
  const unsigned int sorties[8] = {2, 2, 5, 5, 0, 1, 0, 1};
  const unsigned int echeances[8] = {3, 3, 6, 6, 7, 2, 6, 7};
  return testGenerique(sorties, echeances, 8);
}

int main(void) {
  unsigned int total = 0;
  std::cout << "Test de l'enonce\n";
  if (testEnonce()) {
    std::cout << "Resultat: Succes\n";
    total++;
  } else {
    std::cout << "Resultat: Echec\n  -1 point\n";
  }
  std::cout << "------------------------------\n";

  std::cout << "Deuxieme test\n";
  if (deuxiemeTest()) {
    std::cout << "Resultat: Succes\n";
    total++;
  } else {
    std::cout << "Resultat: Echec\n  -1 point\n";
  }
  std::cout << "------------------------------\n";
  
  std::cout << "Test avec echeances identiques\n";
  if (echeancesIdentiques()) {
    std::cout << "Resultat: Succes\n";
    total++;
  } else {
    std::cout << "Resultat: Echec\n  -1 point\n";
  }
  std::cout << "------------------------------\n";
  
  std::cout << "Test avec temps de sortie identiques\n";
  if (sortiesIdentiques()) {
    std::cout << "Resultat: Succes\n";
    total++;
  } else {
    std::cout << "Resultat: Echec\n  -1 point\n";
  }
  std::cout << "------------------------------\n";

  std::cout << "Test complexe\n";
  if (exempleComplexe()) {
    std::cout << "Resultat: Succes\n";
    total++;
  } else {
    std::cout << "Resultat: Echec\n  -1 point\n";
  }

  return 0;
}
