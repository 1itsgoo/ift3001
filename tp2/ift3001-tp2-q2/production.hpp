#ifndef PRODUCTION
#define PRODUCTION

#include <vector>
#include "instance_production.hpp"

// Cette fonction prend en entree une instance du probleme de planification de la production et retourne
// dans le vecteur "solution" la quantite qui doit etre produite chaque jour afin de minimiser les couts
// de production et d'entreposage.
void ProductionProgrammationDynamique(const InstanceProduction& instance, std::vector<unsigned int>& solution);

#endif
