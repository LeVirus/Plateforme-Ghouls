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
 * @brief GestionnaireSol::ajoutSol Fonction de création d'une fonction sol vide.
 * @return Le numéro de case ou la nouvelle fontion sol a été attribuée.
 */
unsigned int GestionnaireSol::ajoutSol(){
    unsigned int uiRetour;
    for( unsigned int i = 0 ; i < mVectSol.size() ; ++i ){
       if( ! mVectSol[ i ] . bEstActive() ){
            mVectSol[ i ] . modifierActivation( true );
            uiRetour = i;
       }
    }
    mVectEntity.push_back( Entity( mVectEntity.size() ) );
    return mVectEntity.size() - 1;
}

/**
 * @brief GestionnaireSol::suprimmerSol Supression d'une fonction sol dont le numéro est envoyé en paramètre.
 * @param uiNumSol le numéro de la fonction sol à suprimmer.
 */
void GestionnaireSol::suprimmerSol( unsigned int uiNumSol ){

}

/**
 * @brief GestionnaireSol::GestionnaireSol Destructeur de la classe GestionnaireSol.
 */
GestionnaireSol::~GestionnaireSol(){

}

