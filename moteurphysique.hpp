#ifndef MOTEURPHYSIQUE_H
#define MOTEURPHYSIQUE_H

#include "gestionnairesol.hpp"

class Moteur;

/**
 * @brief La classe MoteurPhysique Gère les intéractions avec tous les éléments physiques de la scène
 * (entités et caractéristiques de la scène).
 */
class MoteurPhysique{
private:
    Moteur *mPtrMemMoteur;
    GestionnaireSol mGestSol;
public:
    MoteurPhysique();
    void initialiser( Moteur *ptrMoteur );
    void initialiserSolTest();
    Moteur *recupPointeurMoteur();
    ~MoteurPhysique();
};

#endif // MOTEURPHYSIQUE_H
