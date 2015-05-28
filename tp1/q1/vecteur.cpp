#include "vecteur.hpp"

#include <assert.h>

#include <cstddef>

// Constructeur
// Input:
//   capacite: nombre maximum d'entiers que pourra contenir le vecteur
// Complexite: 
//   Theta(1)
Vecteur::Vecteur(int capacite)
  : capacite_(capacite),
    taille_(0),
    entiers_(new int[capacite])
{
  assert(capacite > 0);
}

// Constructeur
// Input:
//   capacite: nombre maximum d'entiers que pourra contenir le vecteur
//   elements_initiaux: un vecteur contenant "capacite" elements que contiendra initialement le vecteur
// Complexite:
//   Theta(capacite)
Vecteur::Vecteur(int capacite, int* elements_initiaux)
  : capacite_(capacite),
    taille_(capacite),
    entiers_(new int[capacite])
{
  assert(capacite > 0);
  assert(elements_initiaux != NULL);

  for (int i = 0; i < capacite; i++)
    entiers_[i] = elements_initiaux[i];
}

// Destructeur
// Complexite:
//   Theta(1)
Vecteur::~Vecteur() {
  delete entiers_;
}

// Retourne l'entier a la position "index". Le premier index est 0.
// Input:
//   index: l'index de l'entier a retourner
// Complexite:
//   Theta(1)
int Vecteur::operator[](int index) const {
  assert(0 <= index && index < taille_);
  return entiers_[index];
}

// Returne vrai si l'instance contient les memes elements que le vecteur autre_vecteur et dans le meme ordre.
// Les vecteurs n'ont pas besoin d'avoir la meme capacite, mais doivent etre de la meme taille.
// Input:
//   autre_vecteur: Un vecteur
// Output:
//   true si les deux vecteurs contiennent les memes elements dans le meme ordre
// Complexite:
//   Pire cas: Theta(taille)
//   Meilleur cas: Theta(1)
bool Vecteur::operator==(const Vecteur& autre_vecteur) const {
  if (taille_ != autre_vecteur.taille())
    return false;
  for (int i = 0; i < taille_; i++) {
    if (entiers_[i] != autre_vecteur[i])
      return false;
  }
  return true;
}

// Retourne le nombre d'entiers dans le vecteur
// Complexite:
//   Theta(1)
int Vecteur::taille() const {
  return taille_;
}

// Ajoute un entier a la fin du vecteur
// Input:
//   entier: l'entier a ajouter
// Complexite:
//   Theta(1)
void Vecteur::ajouteEntier(int entier) {
  assert(taille_ < capacite_);
  entiers_[taille_] = entier;
  taille_++;
}

// Supprime l'entier a la position "index" et decale vers la gauche tous les entiers apres cette position.
// Input
//   index: la position de l'entier a supprimer
// Complexite:
//   Pire cas: ?
//   Meilleur cas: ?
//   Cas moyen: ?
void Vecteur::supprimeEntier(int index) {
  assert(0 <= index && index < taille_);
  for (int i = index + 1; i < taille_; i++) {
    entiers_[i-1] = entiers_[i];
  }
  taille_--;
}

// Supprime plusieurs entiers a la fois
// Input
//   index: Un vecteur d'entier representant les positions des entiers a supprimer
void Vecteur::supprimeEntiers(const Vecteur& index) {
  // Pre-condidtions
  for (int i = 0; i < index.taille(); i++) {
    assert(0 <= index[i] && index[i] < taille_);
  }
  
  bool* masqueSupression = new bool[taille_];
  int* nouveauVecteur = new int[capacite_];

  for(int i=0; i < taille_; i++)
  {
	  masqueSupression[i] = false;
  }

  for (int i=0; i < index.taille(); i++)
  {
	  masqueSupression[index[i]] = true;
  }

  int tailleNouveauVecteur = 0;
  for (int i=0; i < taille_; i++)
  {
	  if(!masqueSupression[i])
	  {
		  nouveauVecteur[tailleNouveauVecteur++] = entiers_[i];
	  }
  }

  delete entiers_;
  delete masqueSupression;

  entiers_ = nouveauVecteur;
  taille_ = tailleNouveauVecteur;
}
