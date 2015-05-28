#ifndef INSTANCE_PRODUCTION
#define INSTANCE_PRODUCTION

#include <algorithm>
#include <cassert>
#include <vector>
#include "fonction.hpp"

// Cette classe encode les parametres du probleme de planification de la prodution.

class InstanceProduction {
private:
  unsigned int production_maximale_;
  unsigned int entreposage_maximal_;
  std::vector<unsigned int> demande_;
  Fonction* cout_production_;
  Fonction* cout_entreposage_;
public:
  InstanceProduction(unsigned int production_maximale,         // Quantite maximale pouvant etre produite en une journee (P dans l'enonce du travail)
		     unsigned int entreposage_maximal,	       // Quantite maximale pouvant etre entreposee en une journee (E dans l'enonce du travail)
		     const std::vector<unsigned int>& demande, // Quantite devant etre livree pour chaque jours (vecteur d dans l'enonce du travail)
		     Fonction* cout_production,                // Fonction calculant le cout de produire x produits (c dans l'enonce du travail)
		     Fonction* cout_entreposage)	       // Fonction calculant le cout d'entreposer x produits (f dans l'enonce du travail)
    : production_maximale_(production_maximale),
      entreposage_maximal_(entreposage_maximal),
      demande_(demande),
      cout_production_(cout_production),
      cout_entreposage_(cout_entreposage)
  {
    assert(production_maximale > 0);
    assert(!demande.empty());
    assert(cout_production);
    assert(cout_entreposage);
  }

  // Retourne la production maximale permise pour une journee (P dans l'enonce du travail)
  unsigned int production_maximale() const {
    return production_maximale_;
  }

  // Retourne la quantitee maximale pouvant etre entreposee pour une journeee (E dans l'enonce du travail)
  unsigned int entreposage_maximal() const {
    return entreposage_maximal_;
  }

  // Retourne la demande maximale permise pour une journee (D dans l'enonce du travail)
  unsigned int demande_maximale() const {
    return *std::max_element(demande_.begin(), demande_.end());
  }

  // Retourne la quantite de produit demande a un jour donne
  unsigned int demande(int jour) const {
    return demande_.at(jour);
  }

  // Nombre de jours de production
  unsigned int nb_jours() const {
    return demande_.size();
  }

  // La fonction de cout de production (c dans l'enonce)
  int cout_production(int production_pour_une_journee) const {
    return cout_production_->evaluer(production_pour_une_journee);
  }

  // La fonction de cout d'entreposage (f dans l'enonce)
  int cout_entreposage(int quantite_entreposee_pour_une_journee) const {
    return cout_entreposage_->evaluer(quantite_entreposee_pour_une_journee);
  }
};

#endif
