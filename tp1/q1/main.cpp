#include "vecteur.hpp"
#include <iostream>

#define GROSSE_VALEUR 100000

bool grosTest() {
	try {
		Vecteur v(GROSSE_VALEUR);
		Vecteur vecteurSupression(GROSSE_VALEUR / 5);

		for(int i = 0; i < GROSSE_VALEUR; i++)
		{
			v.ajouteEntier(i);
			if(i % 5 == 0)
			{
				vecteurSupression.ajouteEntier(i);
			}
		}

		v.supprimeEntiers(vecteurSupression);


		return true;
	} catch (...) {
		return false;
	}
}

bool testSimple() {
  try {
    Vecteur v(10);		//  Vecteur contenant 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    for (int i = 0; i < 10; i++) {
      v.ajouteEntier(i);
    }

    int contenu_de_index[3] = {7, 3, 5};
    Vecteur index(3, contenu_de_index);		//  Vecteur contenant 7, 3, 5
    v.supprimeEntiers(index);

    int contenu_de_solution[7] = {0, 1, 2, 4, 6, 8, 9};
    Vecteur solution(7, contenu_de_solution);

    return v == solution;
  } catch(...) {
    return false;
  }
}

bool grandesValeurs() {
  try {
    int contenu_de_v[6] = {2, -1, 0x80000000, 0x7FFFFFFF, 42, -2};
    Vecteur v(6, contenu_de_v);

    int contenu_de_index[3] = {0, 4};
    Vecteur index(3, contenu_de_index);
    v.supprimeEntiers(index);

    int contenu_de_solution[4] = {-1, 0x80000000, 0x7FFFFFFF, -2};
    Vecteur solution(4, contenu_de_solution);

    return v == solution;
  } catch(...) {
    return false;
  }
}

bool doublons() {
  try {
    Vecteur v(10);		//  Vecteur contenant 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    for (int i = 0; i < 10; i++) {
      v.ajouteEntier(i);
    }

    // Notez que l'index 3 parrait deux fois dans le vecteur
    int contenu_de_v[4] = {7, 3, 5, 3};
    Vecteur index(4, contenu_de_v);		//  Vecteur contenant 7, 3, 5, 3
    v.supprimeEntiers(index);
    if (v.taille() != 7)
      return false;

    int contenu_de_solution[7] = {0, 1, 2, 4, 6, 8, 9};
    Vecteur solution(7, contenu_de_solution);

    return v == solution;
  } catch(...) {
    return false;
  }
}

bool vecteurVide() {
  try {
    Vecteur v(10);		//  Vecteur contenant 0, 1, 2, 3, 4
    for (int i = 0; i < 5; i++) {
      v.ajouteEntier(i);
    }

    Vecteur index(1);		//  Vecteur vide (de taille 0 et de capacite 1)
    v.supprimeEntiers(index);

    int contenu_de_solution[5] = {0, 1, 2, 3, 4};
    Vecteur solution(5, contenu_de_solution);

    return v == solution;
  } catch(...) {
    return false;
  }
}

int main(int argc, const char** argv) {
  int nb_success = 0;
  if (testSimple())
    nb_success++;
  if (grandesValeurs())
    nb_success++;
  if (doublons())
    nb_success++;
  if (vecteurVide())
    nb_success++;
  if (grosTest())
	nb_success++;

  std::cout << nb_success << " / 5" << std::endl;
}
