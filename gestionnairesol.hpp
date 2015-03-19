#ifndef GESTIONNAIRESOL_H
#define GESTIONNAIRESOL_H

#include "sol.hpp"
#include <vector>

class MoteurPhysique;

struct PositionComponent;
struct MoveableComponent;
struct DisplayComponent;

/**
 * @brief La classe GestionnaireSol traite le ou les sols d'une scene, représentés par des fonctions.
 */
class GestionnaireSol{
private:
    std::vector< Sol > mVectSol;
    std::vector< unsigned int > mVectAssociationEntiteSol;
    std::vector< std::pair < MoveableComponent *, PositionComponent * > > * mPtrVectComponentGravitySystem;
    std::vector< std::pair< DisplayComponent *, PositionComponent * > > * mPtrVectComponentDisplaySystem;
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
