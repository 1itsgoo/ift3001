// Tests unitaires pour la Question 4 du Travail 1
// Ces tests representent un sous-ensemble des tests qui seront executes a la correction.

#include "algorithmes.hpp"

#include <iostream>
#include <vector>

// Retourne vrai si l'algorithme diviser pour regner et l'algorithme de force brute retournent des solutions equivalentes.
bool memeSolution(const std::vector<int>& prix) {
    const std::pair<int, int> solution_force_brute = forceBrute(prix);
    const std::pair<int, int> solution_diviser_pour_regner = diviserPourRegner(prix);
    return prix[solution_force_brute.second] - prix[solution_force_brute.first] == prix[solution_diviser_pour_regner.second] - prix[solution_diviser_pour_regner.first];

}

// L'exemple de l'enonce
bool exempleEnonce() {
  int prix_valeurs[] = {10, 4, 6, 8, 2, 5, 3, 9, 1};
  std::vector<int> prix_vecteur(prix_valeurs, prix_valeurs + 9);

  std::pair<int,int> soltn = forceBrute(prix_vecteur);

  std::cout << "Solution force brute: " << soltn.first << "," << soltn.second << std::endl;

  soltn = diviserPourRegner(prix_vecteur);

  std::cout << "Solution diviser: " << soltn.first << "," << soltn.second << std::endl;

  return memeSolution(prix_vecteur);
}

// Des prix ascendants
bool prixAscendants() {
  int prix_valeurs[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  std::vector<int> prix_vecteur(prix_valeurs, prix_valeurs + 9);
  return memeSolution(prix_vecteur);
}

// Des prix descendants
bool prixDescendants() {
  int prix_valeurs[] = {8, 7, 6, 5, 4, 3, 2, 1, 0};
  std::vector<int> prix_vecteur(prix_valeurs, prix_valeurs + 9);
  return memeSolution(prix_vecteur);
}

// Un exemple ou plus d'une solution est possible
bool plusieursSolutions() {
  int prix_valeurs[] = {1, 2, 1, 2, 1, 2, 1, 2};
  std::vector<int> prix_vecteur(prix_valeurs, prix_valeurs + 8);
  return memeSolution(prix_vecteur);
}

// Petit exemple 1
bool petitExempleA() {
  int prix_valeurs[] = {4, 1, 2, 0};
  std::vector<int> prix_vecteur(prix_valeurs, prix_valeurs + 4);
  return memeSolution(prix_vecteur);
}

// Petit exemple 2
bool petitExempleB() {
  int prix_valeurs[] = {1, 4, 2, 0};
  std::vector<int> prix_vecteur(prix_valeurs, prix_valeurs + 4);
  return memeSolution(prix_vecteur);
}

// Petit exemple 3
bool petitExempleC() {
  int prix_valeurs[] = {1, 4, 2, 8};
  std::vector<int> prix_vecteur(prix_valeurs, prix_valeurs + 4);
  return memeSolution(prix_vecteur);
}

int main(int argc, const char** argv) {
  int nb_success = 0;
  if (exempleEnonce())
    nb_success++;
  if (prixAscendants())
    nb_success++;
  if (prixDescendants())
    nb_success++;
  if (plusieursSolutions())
    nb_success++;
  if (petitExempleA())
    nb_success++;
  if (petitExempleB())
    nb_success++;
  if (petitExempleC())
    nb_success++;
  

  std::cout << nb_success << " / 7" << std::endl;
  return 0;
}
