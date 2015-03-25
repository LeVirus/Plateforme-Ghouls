#ifndef GESTIONNAIRESOL_H
#define GESTIONNAIRESOL_H

#include "sol.hpp"
#include <vector>

class MoteurPhysique;

struct PositionComponent;
struct MoveableComponent;
struct DisplayComponent;
struct GroundComponent;

/**
 * @brief La classe GestionnaireSol traite le ou les sols d'une scene, représentés par des fonctions.
 */
class GestionnaireSol{
private:
    std::vector< Sol > mVectSol;
    std::vector< unsigned int > mVectAssociationEntiteSol;
    std::vector< std::tuple< MoveableComponent *, PositionComponent *, GroundComponent *, DisplayComponent *, unsigned int > >
        * mPtrVectComponentGravitySystem;
    std::vector< std::pair< float, float > > mVectPositionPrecedantesEntites;
    MoteurPhysique * mPtrMoteurPhysique;

public:
    GestionnaireSol();
    void tmpDefinirPointCollisionSol( unsigned int uiNumSprite, float & fPointX, float & fPointY );

    void memPositionEntites();
    void traitementEntitesChutesSols();

    unsigned int ajoutSol();
    void suprimmerSol( unsigned int uiNumSol );
    void liaisonMoteurPhysique( MoteurPhysique * ptrMoteurPhysique );
    void calculLiensSolEntites();
    Sol * recupSol( unsigned int uiNumSol );
    ~GestionnaireSol();
};

#endif // GESTIONNAIRESOL_H
