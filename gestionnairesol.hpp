#ifndef GESTIONNAIRESOL_H
#define GESTIONNAIRESOL_H

#include "sol.hpp"
#include <vector>

class MoteurPhysique;

struct PositionComponent;
struct MoveableComponent;

/**
 * @brief La classe GestionnaireSol traite le ou les sols d'une scene, représentés par des fonctions.
 */
class GestionnaireSol{
private:
    std::vector< Sol > mVectSol;
    std::vector< unsigned int > mVectAssociationEntiteSol;
    std::vector< std::pair < MoveableComponent *, PositionComponent * > > * mVectComponentEntity;
    MoteurPhysique * mPtrMoteurPhysique;

public:
    GestionnaireSol();
    unsigned int ajoutSol();
    void suprimmerSol( unsigned int uiNumSol );
    void liaisonMoteurPhysique( MoteurPhysique * ptrMoteurPhysique );
    void calculLiensSolEntites();
    void TraitementEntiteSol();
    ~GestionnaireSol();
};

#endif // GESTIONNAIRESOL_H
