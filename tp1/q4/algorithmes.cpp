#include "algorithmes.hpp"

#include <algorithm>
#include <assert.h>
#include <limits>
#include <iostream>

// Retourne une paire d'entiers (i, j) tel que i <= j et prix[j] - prix[i] est maximal.
//
// Input:
//   prix: un vecteur d'entiers correspondant aux prix
// Output:
//   Deux entiers dont le premier repr�sente le moment de l'achat et le deuxieme et le moment de la vente.
// Complexite:
//   Theta(n^2) dans tous les cas
std::pair<int, int> forceBrute(const std::vector<int>& prix) {
  assert(!prix.empty());
  
  int achat = 0;
  int vente = 0;
  for (unsigned int i = 0; i < prix.size() - 1; i++) {
    for (unsigned int j = i + 1; j < prix.size(); j++) {
      if (prix[j] - prix[i] > prix[vente] - prix[achat]) {
	achat = (int)i;
	vente = (int)j;
      }
    }
  }
  assert(achat <= vente);
  return std::pair<int, int>(achat, vente);
}

std::pair<int,int> combine(const std::vector<int>& prix,
		const std::pair<int,int>& lhs, const std::pair<int,int>& rhs,
		std::pair<int,int>& min_max)
{
	// update the solution if needed
	  if(prix[rhs.second] - prix[lhs.first] > prix[min_max.second] - prix[min_max.first])
	  {
		  min_max.second = rhs.second;
		  min_max.first = lhs.first;

		  std::cout << "Changing solution to " << lhs.first << " " << rhs.second << std::endl;
	  }

	  // compute where the min and max are
	  int min = prix[rhs.first] < prix[lhs.first] ? rhs.first : lhs.first;
	  int max = prix[rhs.second] > prix[lhs.second] ? rhs.second : lhs.second;

	  return std::pair<int,int>(min,max);
}

std::pair<int,int> recurse(const std::vector<int>& prix, int debut, int fin, std::pair<int,int>& min_max)
{
  // Ad hoc
  if(debut == fin - 1)
  {
	  return std::pair<int,int>(debut,debut);
  }

  int point_milieu = (fin - debut) / 2 + debut;

  std::cout << "---" << debut << point_milieu << fin << std::endl;

  std::pair<int,int> leftResult = recurse(prix, debut, point_milieu, min_max);
  std::pair<int,int> rightResult = recurse(prix, point_milieu, fin, min_max);

  return combine(prix, leftResult, rightResult, min_max);
}

// Retourne une paire d'entiers (i, j) tel que i <= j et prix[j] - prix[i] est maximal.
//
// Input:
//   prix: un vecteur d'entiers correspondant aux prix
// Output:
//   Deux entiers dont le premier repr�sente le moment de l'achat et le deuxieme et le moment de la vente.
// Complexite:
//   Theta(n) en pire cas (ou dans tous les cas)
std::pair<int, int> diviserPourRegner(const std::vector<int>& prix) {
  assert(!prix.empty());

  std::pair<int,int> min_max = std::pair<int,int>(0,0);

  recurse(prix, 0, prix.size(), min_max);
  std::cout << "---" << std::endl;
  return min_max;
}
