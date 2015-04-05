#include "moteurphysique.hpp"
#include "constantes.hpp"
#include "moteur.hpp"
#include "vector2D.hpp"
#include <iostream>
#include <cassert>

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
 * @brief MoteurPhysique::initialiserSol TMP
 */
void MoteurPhysique::initialiserSolTest(){
    mGestSol . ajoutSol();
    Sol * solTest = mGestSol . recupSol( 0 );
    assert( solTest && "solTest non instancié\n" );

    Vector2D vect2dPoint( ZERO_FLOAT, ZERO_FLOAT );

    if( ! solTest -> bAjoutPoint( vect2dPoint ) )std::cout << "point non ajouté\n";
    if( ! solTest -> bAjoutPoint( vect2dPoint ) )std::cout << "point non ajouté\n";
    vect2dPoint . mfX = -150.0;
    vect2dPoint . mfY = 654.0;
    if( ! solTest -> bAjoutPoint( vect2dPoint ) )std::cout << "point non ajouté\n";
    vect2dPoint . mfX = 150.0;
    vect2dPoint . mfY = 654.0;
    if( ! solTest -> bAjoutPoint( vect2dPoint ) )std::cout << "point non ajouté\n";
    solTest -> afficherFonction();
}


/**
 * @brief Destructeur de la classe MoteurPhysique.
 */
MoteurPhysique::~MoteurPhysique(){

}

