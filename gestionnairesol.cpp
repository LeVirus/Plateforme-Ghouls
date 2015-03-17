#include "gestionnairesol.hpp"
#include "moteurphysique.hpp"
#include "moteur.hpp"
#include "gravitysystem.hpp"

/**
 * @brief GestionnaireSol::GestionnaireSol Constructeur de la classe GestionnaireSol.
 */
GestionnaireSol::GestionnaireSol(){
    mVectComponentEntity = mPtrMoteurPhysique -> recupPointeurMoteur() -> getECSEngine() . getSystemManager() .
            searchSystemByType < GravitySystem > ( GRAVITY_SYSTEM ) -> getVectComponentGravitySystem();
}

/**
 * @brief GestionnaireSol::recupVectComponent récupération du vector de component nécessaire
 * pour le traitement des collisions avec le sol.
 */
void GestionnaireSol::recupVectComponent(){
    if( ! mPtrMoteurPhysique )return;
    //mVectComponentEntity = mPtrMoteurPhysique -> recupPointeurMoteur() -> getECSEngine() . getSystemManager() .
      //      searchSystemByType < GravitySystem > ( GRAVITY_SYSTEM ) -> getVectComponentGravitySystem();
}

/**
 * @brief GestionnaireSol::GestionnaireSol Destructeur de la classe GestionnaireSol.
 */
GestionnaireSol::~GestionnaireSol(){

}

