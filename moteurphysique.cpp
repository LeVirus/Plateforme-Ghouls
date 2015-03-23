#include "moteurphysique.hpp"
#include "moteur.hpp"
#include <iostream>

/**
 * @brief Constructeur de la classe MoteurPhysique.
 */
MoteurPhysique::MoteurPhysique(){
    mPtrMemMoteur = NULL;
}

/**
 * @brief MoteurPhysique::recupPointeurMoteur Renvoie un pointeur vers la classe Moteur.
 * @return Le pointeur de la classe Moteur.
 */
Moteur * MoteurPhysique::recupPointeurMoteur(){
    return mPtrMemMoteur;
}


/**
 * @brief MoteurPhysique::initialiser Fonction créant un liens du moteur physique au moteur général.
 * @param ptrMoteur un pointeur vers Moteur.
 */
void MoteurPhysique::initialiser( Moteur *ptrMoteur ){
    if( ptrMoteur )mPtrMemMoteur = ptrMoteur;
}

/**
 * @brief MoteurPhysique::initialiserSol
 */
void MoteurPhysique::initialiserSolTest(){
    mGestSol . ajoutSol();
    Sol * solTest = mGestSol . recupSol( 0 );
    if( ! solTest )return;

    std::pair< float, float > pairFloat( 0.0, 0.0 );

    if( ! solTest -> bAjoutPoint( pairFloat ) )std::cout << "point non ajouté\n";
    if( ! solTest -> bAjoutPoint( pairFloat ) )std::cout << "point non ajouté\n";
    pairFloat . first = -150.0;
    pairFloat . second = 654.0;
    if( ! solTest -> bAjoutPoint( pairFloat ) )std::cout << "point non ajouté\n";
    pairFloat . first = 150.0;
    pairFloat . second = 654.0;
    if( ! solTest -> bAjoutPoint( pairFloat ) )std::cout << "point non ajouté\n";
    solTest -> afficherFonction();
}


/**
 * @brief Destructeur de la classe MoteurPhysique.
 */
MoteurPhysique::~MoteurPhysique(){

}

