#include <iostream>
#include <limits>
#include <vector>

#include "fonction.hpp"
#include "instance_production.hpp"
#include "production.hpp"

// Retourne vrai si le vecteur solution constitue un plan de production valide (sans necessairement etre optimal)
bool SolutionValide(const InstanceProduction& instance, const std::vector<unsigned int>& solution) {
  const unsigned int nb_jours = instance.nb_jours();
  if (solution.size() != nb_jours) {
    std::cerr << "Solution de mauvaise taille" << std::endl;
    return false;
  }
  unsigned int quantite_en_entrepot = 0;
  for (unsigned int i = 0; i < nb_jours; i++) {
    if (solution[i] > instance.production_maximale()) {
      std::cerr << "Production maximale depassee au jour " << i << std::endl;
      return false;
    }
    quantite_en_entrepot += solution[i];
    if (quantite_en_entrepot < instance.demande(i)) {
      std::cerr << "La demande n'est pas satisfaite au jour " << i << std::endl;
      return false;
    }
    quantite_en_entrepot -= instance.demande(i);
    if (quantite_en_entrepot > instance.entreposage_maximal()) {
      std::cerr << "L'entreposage maximale est depassee au jour " << i << std::endl;
      return false;
    }
  }
  return true;
}

// Retourne le cout associe au plan de production donne par le vecteur solution
int CoutSolution(const InstanceProduction& instance, const std::vector<unsigned int>& solution)
{
  assert(SolutionValide(instance, solution));

  int quantite_en_entrepot = 0;
  int cout = 0;
  const int nb_jours = instance.nb_jours();
  for (int jour = 0; jour < nb_jours; jour++) {
    cout += instance.cout_production(solution[jour]);
    quantite_en_entrepot += solution[jour];
    quantite_en_entrepot -= instance.demande(jour);
    cout += instance.cout_entreposage(quantite_en_entrepot);
  }
  return cout;
}

// Algorithme utilise par la fonction ForceBrute pour trouver une solution optimale au probleme.
void ForceBruteRecursive(const InstanceProduction& instance,
			std::vector<unsigned int> & solution_partielle,
			std::vector<unsigned int>& solution
			)
{
  if (solution_partielle.size() == instance.nb_jours()) {
    solution = solution_partielle;
    return;
  }

  assert(solution_partielle.size() < instance.nb_jours());
  
  std::vector<unsigned int> meilleure_solution;
  int cout_meilleure_solution = std::numeric_limits<int>::max();
  
  std::vector<unsigned int> solution_courrante;
  
  unsigned int quantitee_en_entrepot = 0;
  for (unsigned int i = 0; i < solution_partielle.size(); i++) {
    quantitee_en_entrepot += solution_partielle[i];
    assert(quantitee_en_entrepot >= instance.demande(i));
    quantitee_en_entrepot -= instance.demande(i);
  }

  // Soit p la production pour le prochain jour.
  // Nous savons que
  //
  // p <= instance.production_maximale()
  //
  // puisque c'est une contrainte du probleme.
  // De plus, quantitee_en_entrepot + p - demande[solution_partielle.size()] <= instance.entreposage_maximal()
  // car on ne peut pas depasse la quantite a entreposer pour une journe. Nous concluons donc que cette inegalite doit aussi etre
  // satisfaite:
  //
  // p <= instance.entreposage_maximal() + instance.demande()[solution_partielle.size()] - quantitee_en_entrepot
  //
  // Finalement, pour satisfaire la demande, la production doit etre telle que la demande soit satisfaite a la fin de la journee
  // Nous avonc donc cette ingealite
  //
  // p >= instance.demande()[solution_partielle.size()] - quantitee_en_entrepot
  
  const unsigned int demande_pour_aujourdhui = instance.demande(solution_partielle.size());
  const unsigned int production_maximale_pour_aujourdhui =
    std::min(instance.production_maximale(),
	     instance.entreposage_maximal() + demande_pour_aujourdhui - quantitee_en_entrepot);
  const unsigned int production_minimale_pour_aujourdhui =
    (demande_pour_aujourdhui <= quantitee_en_entrepot ? 0 : demande_pour_aujourdhui - quantitee_en_entrepot);

  if (production_minimale_pour_aujourdhui > production_maximale_pour_aujourdhui) {
    solution.clear();
    return;
  }

  for (solution_partielle.push_back(production_minimale_pour_aujourdhui);
       solution_partielle.back() <= production_maximale_pour_aujourdhui;
       solution_partielle.back()++) {
    ForceBruteRecursive(instance, solution_partielle, solution_courrante);
    if (!solution_courrante.empty()) {
      const int cout_solution_courrante = CoutSolution(instance, solution_courrante);
      if (cout_solution_courrante < cout_meilleure_solution) {
	meilleure_solution = solution_courrante;
	cout_meilleure_solution = cout_solution_courrante;
      }
    }
  }
  solution_partielle.pop_back();
  solution.swap(meilleure_solution); 
}
			
// Retourne le plan de production optimal d'une instance donnee.
void ForceBrute(const InstanceProduction& instance, std::vector<unsigned int>& solution) {
  std::vector<unsigned int> solution_partielle;
  ForceBruteRecursive(instance, solution_partielle, solution);
}

bool TestA() {
  try {
    // Creation de l'instance
    const int nb_jours = 3;
    unsigned int demande[] = {1, 1, 1};
    FonctionLineaire cout_production(1, 0);  // p(x) = x
    FonctionLineaire cout_entreposage(1, 0); // f(x) = x
    const unsigned int production_maximale = 3;
    const unsigned int entreposage_maximal = 3;
    InstanceProduction instance(production_maximale,
				entreposage_maximal,
				std::vector<unsigned int>(demande, demande + nb_jours),
				&cout_production,
				&cout_entreposage);

    // Resolution de l'instance
    std::vector<unsigned int> solution_programmation_dynamique;
    ProductionProgrammationDynamique(instance, solution_programmation_dynamique);

    // Verification de la solution
    if (!SolutionValide(instance, solution_programmation_dynamique))
      return false;		// Solution invalide!
    unsigned int solution[nb_jours] = {1, 1, 1}; // Solution optimale
    std::vector<unsigned int> vecteur_solution(solution, solution + nb_jours);
    return CoutSolution(instance, solution_programmation_dynamique) == CoutSolution(instance, vecteur_solution);
  } catch (...) {
    return false;
  }
}

bool TestB() {
  try {
    // Creation de l'instance
    const int nb_jours = 3;
    unsigned int demande[] = {1, 3, 1};
    FonctionBatonHockey cout_production(2, 2);  // p(x) = 2 * max(x - 2, 0)
    FonctionBatonHockey cout_entreposage(2, 2); // f(x) = 2 * max(x - 2, 0)
    const unsigned int production_maximale = 3;
    const unsigned int entreposage_maximal = 2;
    InstanceProduction instance(production_maximale,
				entreposage_maximal,
				std::vector<unsigned int>(demande, demande + nb_jours),
				&cout_production,
				&cout_entreposage);

    // Resolution de l'instance
    std::vector<unsigned int> solution_programmation_dynamique;
    ProductionProgrammationDynamique(instance, solution_programmation_dynamique);

    // Verification de la solution
    if (!SolutionValide(instance, solution_programmation_dynamique))
      return false;		// Solution invalide!
    unsigned int solution[nb_jours] = {2, 2, 1}; // Solution optimale
    std::vector<unsigned int> vecteur_solution(solution, solution + nb_jours);
    return CoutSolution(instance, solution_programmation_dynamique) == CoutSolution(instance, vecteur_solution);
  } catch (...) {
    return false;
  }
}

bool TestC() {
  try {
    // Creation de l'instance
    const int nb_jours = 3;
    unsigned int demande[] = {1, 3, 1};
    FonctionBatonHockey cout_production(2, 2);  // p(x) = 2 * max(x - 2, 0)
    FonctionLineaire cout_entreposage(3, 0); // f(x) = 3 * x
    const unsigned int production_maximale = 3;
    const unsigned int entreposage_maximal = 2;
    InstanceProduction instance(production_maximale,
				entreposage_maximal,
				std::vector<unsigned int>(demande, demande + nb_jours),
				&cout_production,
				&cout_entreposage);

    // Resolution de l'instance
    std::vector<unsigned int> solution_programmation_dynamique;
    ProductionProgrammationDynamique(instance, solution_programmation_dynamique);

    // Verification de la solution
    if (!SolutionValide(instance, solution_programmation_dynamique))
      return false;		// Solution invalide!
    unsigned int solution[nb_jours] = {1, 3, 1}; // Solution optimale
    std::vector<unsigned int> vecteur_solution(solution, solution + nb_jours);
    return CoutSolution(instance, solution_programmation_dynamique) == CoutSolution(instance, vecteur_solution);
  } catch (...) {
    return false;
  }
}

bool TestD() {
  try {
    // Creation de l'instance
    const int nb_jours = 10;
    unsigned int demande[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 10};
    FonctionCarre cout_production;  // p(x) = x^2
    FonctionLineaire cout_entreposage(0, 0); // f(x) = 0
    const unsigned int production_maximale = 10;
    const unsigned int entreposage_maximal = 10;
    InstanceProduction instance(production_maximale,
				entreposage_maximal,
				std::vector<unsigned int>(demande, demande + nb_jours),
				&cout_production,
				&cout_entreposage);

    // Resolution de l'instance
    std::vector<unsigned int> solution_programmation_dynamique;
    ProductionProgrammationDynamique(instance, solution_programmation_dynamique);

    // Verification de la solution
    if (!SolutionValide(instance, solution_programmation_dynamique))
      return false;		// Solution invalide!
    unsigned int solution[nb_jours] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; // Solution optimale
    std::vector<unsigned int> vecteur_solution(solution, solution + nb_jours);
    return CoutSolution(instance, solution_programmation_dynamique) == CoutSolution(instance, vecteur_solution);
  } catch (...) {
    return false;
  }
}

bool TestE() {
  try {
    // Creation de l'instance
    const int nb_jours = 10;
    unsigned int demande[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 10};
    FonctionLineaire cout_production(1, 0);  // p(x) = x
    FonctionCarre cout_entreposage;	     // f(x) = x^2
    const unsigned int production_maximale = 3;
    const unsigned int entreposage_maximal = 10;
    InstanceProduction instance(production_maximale,
				entreposage_maximal,
				std::vector<unsigned int>(demande, demande + nb_jours),
				&cout_production,
				&cout_entreposage);

    // Resolution de l'instance
    std::vector<unsigned int> solution_programmation_dynamique;
    ProductionProgrammationDynamique(instance, solution_programmation_dynamique);
    ForceBrute(instance, solution_programmation_dynamique);

    // Verification de la solution
    if (!SolutionValide(instance, solution_programmation_dynamique))
      return false;		// Solution invalide!
    unsigned int solution[nb_jours] = {0, 0, 0, 0, 0, 0, 1, 3, 3, 3}; // Solution optimale
    std::vector<unsigned int> vecteur_solution(solution, solution + nb_jours);
    return CoutSolution(instance, solution_programmation_dynamique) == CoutSolution(instance, vecteur_solution);
  } catch (...) {
    return false;
  }
}

int main(void) {
  std::cout << "Test A: " << TestA() << std::endl;
  std::cout << "Test B: " << TestB() << std::endl;
  std::cout << "Test C: " << TestC() << std::endl;
  std::cout << "Test D: " << TestD() << std::endl;
  std::cout << "Test E: " << TestE() << std::endl;
  return 0;
}
