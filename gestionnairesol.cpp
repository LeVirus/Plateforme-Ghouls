#include "gestionnairesol.hpp"
#include "moteurphysique.hpp"
#include "moteur.hpp"
#include "gravitysystem.hpp"
#include <cassert>


/**
 * @brief GestionnaireSol::GestionnaireSol Constructeur de la classe GestionnaireSol.
 */
GestionnaireSol::GestionnaireSol(){
    mVectComponentEntity = NULL;
}

/**
 * @brief GestionnaireSol::liaisonMoteurPhysique Liaison de la classe vers le moteur physique.
 * @param ptrMoteurPhysique Le pointeur vers le moteur physique.
 */
void GestionnaireSol::liaisonMoteurPhysique( MoteurPhysique * ptrMoteurPhysique ){
    mPtrMoteurPhysique = ptrMoteurPhysique;
    assert( mPtrMoteurPhysique && "mPtrMoteurPhysique non instancié." );
}

/**
 * @brief GestionnaireSol::ajoutSol Fonction de création d'une fonction sol vide.
 * Si une case dont l'objet Sol n'est pas activé le nouveau Sol sera attribué à cette case.
 * @return Le numéro de case ou la nouvelle fontion sol a été attribuée.
 */
unsigned int GestionnaireSol::ajoutSol(){
    for( unsigned int i = 0 ; i < mVectSol.size() ; ++i ){
       if( ! mVectSol[ i ] . bEstActive() ){
            mVectSol[ i ] . modifierActivation( true );
            return i;
       }
    }
    mVectSol.push_back( Sol() );
    return mVectEntity.size() - 1;
}

/**
 * @brief GestionnaireSol::suprimmerSol Supression d'une fonction sol dont le numéro est envoyé en paramètre.
 * Une vérification est effectuée concernant l'existance de la fonction sol en question.
 * @param uiNumSol le numéro de la fonction sol à suprimmer.
 */
void GestionnaireSol::suprimmerSol( unsigned int uiNumSol ){
    if( uiNumSol >= mVectSol . size() || ! mVectSol[ uiNumSol ] . bEstActive() )return;
    mVectSol[ uiNumSol ] . reinitialiserFonction();
    mVectSol[ uiNumSol ] . modifierActivation( false );
}

/**
 * @brief GestionnaireSol::calculLiensSolEntites Fonction calculant sur quels fonction sol chaque entité se dirige.
 * Si le pointeur du vector de composants en provenance de GravitySystem est à NULL, sa référence est récupérée.
 */
void GestionnaireSol::calculLiensSolEntites(){
    if( ! mVectComponentEntity ){
        mVectComponentEntity = mPtrMoteurPhysique -> recupPointeurMoteur() -> getECSEngine() . getSystemManager() .
                searchSystemByType < GravitySystem > ( GRAVITY_SYSTEM ) -> getVectComponentGravitySystem();
    }
    assert( mVectComponentEntity && "mVectComponentEntity non instancié." );

}

/**
 * @brief GestionnaireSol::GestionnaireSol Destructeur de la classe GestionnaireSol.
 */
GestionnaireSol::~GestionnaireSol(){

}

