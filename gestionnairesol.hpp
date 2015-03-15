#ifndef GESTIONNAIRESOL_H
#define GESTIONNAIRESOL_H

#include "sol.hpp"
#include <vector>

class MoteurPhysique;

/**
 * @brief La classe GestionnaireSol traite le ou les sols d'une scene, représentés par des fonctions.
 */
class GestionnaireSol{
private:
    std::vector< Sol > mVectSol;
    MoteurPhysique * mPtrMoteurPhysique;
public:
    GestionnaireSol();
    void ajoutSol();
    void suprimmerSol();
    void liaisonMoteurPhysique( MoteurPhysique * ptrMoteurPhysique );
    void TraitementEntiteeSol();
    ~GestionnaireSol();
};

#endif // GESTIONNAIRESOL_H
