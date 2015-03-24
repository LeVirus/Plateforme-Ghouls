#include "gestionnairesol.hpp"
#include "moteurphysique.hpp"
#include "moteur.hpp"
#include "gravitysystem.hpp"
#include "moveablecomponent.hpp"
#include "groundcomponent.hpp"
#include "displaysystem.hpp"
#include <cassert>


/**
 * @brief GestionnaireSol::GestionnaireSol Constructeur de la classe GestionnaireSol.
 */
GestionnaireSol::GestionnaireSol(){
    mPtrVectComponentGravitySystem = nullptr;
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
 * @brief GestionnaireSol::memPositionEntites Mémorisation des positions des entités qui interagissent avec le sol à un
 * instant t.
 */
void GestionnaireSol::memPositionEntites(){
    mVectPositionPrecedantesEntites . resize( mPtrVectComponentGravitySystem -> size() );
    for( unsigned int i = 0 ; i < mPtrVectComponentGravitySystem . size() ; ++i ){
        mVectPositionPrecedantesEntites[ i ] . first = std::get< 1 >( ( * mPtrVectComponentGravitySystem )[ i ] ) . mfPositionX +
        std::get< 2 >( ( * mPtrVectComponentGravitySystem )[ i ] ) . mfGroundCollisionPositionX;

        mVectPositionPrecedantesEntites[ i ] . second = std::get< 1 >( ( * mPtrVectComponentGravitySystem )[ i ] ) . mfPositionY +
        std::get< 2 >( ( * mPtrVectComponentGravitySystem )[ i ] ) . mfGroundCollisionPositionY;
    }
}

/**
 * @brief GestionnaireSol::traitementEntitesChutesSols Réajustement de la position des entités qui entre en collision avec le sol.
 * La fonction vérifie si les entités ne sont pas sur le sol, et si elle se dirige vers le bas.
 */
void GestionnaireSol::traitementEntitesChutesSols(){
    for( unsigned int i = 0 ; i < mVectPositionPrecedantesEntites . size(); ++i ){

    }
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
    mVectSol . push_back( Sol() );
    return mVectSol . size() - 1;
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

    float fPointCollisionSolX, fPointCollisionSolY;
    unsigned int uiNumSprite;

    if( ! mPtrVectComponentGravitySystem ){
        mPtrVectComponentGravitySystem = mPtrMoteurPhysique -> recupPointeurMoteur() -> getECSEngine() . getSystemManager() .
                searchSystemByType < GravitySystem > ( GRAVITY_SYSTEM ) -> getVectTupleComponentGravitySystem();
    }
    assert( mPtrVectComponentGravitySystem && "mPtrVectComponentGravitySystem non instancié." );

    for( unsigned int i = 0; i < ( * mPtrVectComponentGravitySystem ) . size() ; ++i ){

        //si GroundComponent n'est pas initialisé
        //récupération du point de collision avec le sol de l'entité
        if( ! std::get< 2 >( ( * mPtrVectComponentGravitySystem )[ i ] ) -> mbInit ){
            uiNumSprite = std::get< 3 >( ( * mPtrVectComponentGravitySystem )[ i ] ) -> muiNumSprite;
            mPtrMoteurPhysique -> recupPointeurMoteur() -> getMoteurGraphique() .
                    tmpRecupValeurPositionCollisionSol( uiNumSprite, fPointCollisionSolX, fPointCollisionSolY );
            std::get< 2 >( ( * mPtrVectComponentGravitySystem )[ i ] ) -> mfGroundCollisionPositionX = fPointCollisionSolX;
            std::get< 2 >( ( * mPtrVectComponentGravitySystem )[ i ] ) -> mfGroundCollisionPositionY = fPointCollisionSolY;
        }

        //mVectSol[ j ] . bVerifCollision(  );
        //implémenter la vérification de collisions avec le sol
    }

}

/**
 * @brief GestionnaireSol::definirPointCollisionSol Fonction TEMPORAIRE de calcul du point de collision à utiliser pour les
 * interactions avec le sol.
 * @param uiNumSprite Le numéro du sprite de l'entité.
 * @param fPointX L'abscisse du point sur lequel sera mémorisé la position de collision avec le sol.
 * @param fPointY L'ordonnée du point sur lequel sera mémorisé la position de collision avec le sol.
 */
void GestionnaireSol::tmpDefinirPointCollisionSol( unsigned int uiNumSprite, float & fPointX, float & fPointY ){
    mPtrMoteurPhysique -> recupPointeurMoteur() -> getMoteurGraphique() .
            tmpRecupValeurPositionCollisionSol( uiNumSprite, fPointX, fPointY );
    fPointX /= 2;

    //a modifier pour placer les points de collisions avec le sol à des positions paramétrables
}

/**
 * @brief GestionnaireSol::recupSol Fonction renvoyant une référence vers le Sol dont le numéro est envoyé en paramètre.
 * @param uiNumSol le numéro du Sol à récupérer.
 * @return Une référence vers le Sol demandé.
 */
Sol * GestionnaireSol::recupSol( unsigned int uiNumSol ){
    if( uiNumSol > mVectSol.size() )return nullptr;

    return & mVectSol[ uiNumSol ];
}


/**
 * @brief GestionnaireSol::GestionnaireSol Destructeur de la classe GestionnaireSol.
 */
GestionnaireSol::~GestionnaireSol(){

}

