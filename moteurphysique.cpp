#include "moteurphysique.hpp"

/**
 * @brief Constructeur de la classe MoteurPhysique.
 */
MoteurPhysique::MoteurPhysique(){
    mPtrMemMoteur = NULL;
}

/**
 * @brief MoteurPhysique::initialiser Fonction créant un liens du moteur physique au moteur général.
 * @param ptrMoteur un pointeur vers Moteur.
 */
void MoteurPhysique::initialiser( Moteur *ptrMoteur ){
    if( ptrMoteur )mPtrMemMoteur = ptrMoteur;
}


/**
 * @brief Destructeur de la classe MoteurPhysique.
 */
MoteurPhysique::~MoteurPhysique(){

}

