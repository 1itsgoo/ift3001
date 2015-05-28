#include <algorithm>
#include <limits>
#include <iostream>

#include "production.hpp"

// Cette fonction prend en entree une instance du probleme de planification de la production et retourne
// dans le vecteur "solution" la quantite qui doit etre produite chaque jour afin de minimiser les couts
// de production et d'entreposage.
void ProductionProgrammationDynamique(const InstanceProduction& instance,
        std::vector<unsigned int>& solution) {
  // Ecrivez votre code ici. Votre algorithme devrait proceder en deux phases:
  //   1) il devrait construire un tableau.
  //   2) il devrait remonter le tableau et ecrire la solution dans vecteur "solution".
  //
  // Vous pouvez declarer de nouvelles fonctions dans le fichier production.cpp, mais vous ne devez pas modifier le fichier production.hpp

    std::vector< std::vector< int > > T = 
        std::vector< std::vector<int> >(instance.nb_jours());

    // Cas de base
    std::vector< int > first_row = 
        std::vector< int >(instance.entreposage_maximal());

    for(int i=0; i <= instance.entreposage_maximal(); i++)
    {
        first_row.push_back(instance.cout_production(instance.demande(0) + i));
    }

    T.push_back(first_row);


    // Remplissage du tableau
    for(int i=1; i < instance.nb_jours(); i++)
    {
        std::vector<int> new_row =
            std::vector<int>(instance.entreposage_maximal());

        for(int j=0; j < instance.entreposage_maximal(); j++)
        {
            std::vector<int> solution_prices =
                std::vector<int>(instance.entreposage_maximal() +
                        instance.demande(i));

            for(int x=0; x <= instance.entreposage_maximal(); i++)
            {
                if(x > instance.entreposage_maximal() || instance.demande(i) - x
                        > instance.production_maximale()) 
                {
                    solution_prices.push_back(std::numeric_limits<int>::max());
                }
                else
                {
                    int solution_price = T.at(i-1).at(x) + 
                        instance.cout_production(instance.demande(i) - x) + 
                        instance.cout_entreposage(x);

                    solution_prices.push_back(solution_price);
                }
            }

            int best_soltn_price = *std::min_element(solution_prices.begin(),
                    solution_prices.end());
            new_row.push_back(best_soltn_price);
        }

        T.push_back(new_row);
    }


    // Print the created table
    for(int i=0; i<T.size(); i++)
    {
        for(int j=0; j<T.at(i).size(); j++)
        {
            std::cout << "| " << T.at(i).at(j) << " ";
        }
        std::cout << "|" << std::endl; 
    }
}
