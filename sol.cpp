#include "sol.hpp"
#include "constantes.hpp"
#include <iostream>
#include <limits>
#include <cassert>

/**
 * @brief Sol::Sol Constructeur de la classe Sol.
 */
Sol::Sol(){
    mMaxAbscisse = 0;
    mMinAbscisse = 0;
    mMaxOrdonnee = 0;
    mMinOrdonnee = 0;
    mbActif = false;
}

/**
 * @brief Sol::bEstEnUtilisation Fonction déterminant si la fonction sol est activée.
 * @return true si la fonction sol est activée, false sinon.
 */
bool Sol::bEstActive() const{
    return mbActif;
}

/**
 * @brief Sol::modifierActivation Modifie le booléen déterminant si la fonction sol est activé.
 * @param bActif la nouvelle valeur de mbActif.
 */
void Sol::modifierActivation( bool bActif ){
    mbActif = bActif;
}

/**
 * @brief Sol::reinitialiserFonction Fonction de supression des points composants la fonction.
 */
void Sol::reinitialiserFonction(){
    mVectPointFonction . clear();
    miseAJourBoiteEnglobanteFonction();
}

bool Sol::bVerifCollision( float fX, float fY ) const{
    if( bVerifCollisionSolBoiteEnglobante( fX, fY ) )
        return false;

}

/**
 * @brief Sol::bVerifCollisionSolBoiteEnglobante Fonction de test de collision entre la boite englobante de la fonction
 * et le point envoyé en paramètre.
 * @param fX L'abscisse du point à tester.
 * @param fY L'ordonnée du point à tester.
 * @return true si le point se trouve dans la boite englobante de la fonction, false sinon.
 */
bool Sol::bVerifCollisionSolBoiteEnglobante( float fX, float fY )const{
    if( ( fX <= mMaxAbscisse && fX >= mMinAbscisse ) && ( fY <= mMaxOrdonnee && fY >= mMinOrdonnee ) )
        return true;
    return false;
}

/**
 * @brief Sol::bVerifCollision Fonction de test de collision entre la boite englobante de la fonction
 * et le point envoyé en paramètre.
 * @param vect2dA Le Vector2D contenant le point.
 * @return true si le point se trouve dans la boite englobante de la fonction, false sinon.
 */
bool Sol::bVerifCollisionSolBoiteEnglobante( const Vector2D &vect2dA )const{
    return bVerifCollisionSolBoiteEnglobante( vect2dA . mfX, vect2dA . mfY );
}

/**
 * @brief Sol::bVerifCollision
 * @param vect2dA
 * @return
 */
bool Sol::bVerifCollision( const Vector2D &vect2dA )const{
    return bVerifCollision( vect2dA . mfX, vect2dA . mfY );
}

/**
 * @brief Sol::bVerifCoherencePoint Fonction de vérification de l'abscisse du point précédent avec le point à ajouter.
 * @param fX l'abscisse du point à tester.
 * @param fY l'ordonné du point à tester.
 * @return true si le nouveau point est accepté, false sinon.
 */
bool Sol::bVerifCoherencePoint( float fX, float fY )const{
    if( mVectPointFonction . size() == 0 )
        return true;

    //cas ou le dernier point est identique au point à ajouter                                  ;
    if( (  fX - mVectPointFonction[ mVectPointFonction . size() - 1 ] . mfX < ZERO_FLOAT ) &&
        (  fY - mVectPointFonction[ mVectPointFonction . size() - 1 ] . mfY < ZERO_FLOAT ) )
        return false;

    return fX >= mVectPointFonction[ mVectPointFonction . size() - 1 ] . mfX;
}

/**
 * @brief Sol::bVerifCoherencePoint Fonction de vérification de l'abscisse du point précédent avec le point à ajouter.
 * @param vect2dA
 * @return
 */
bool Sol::bVerifCoherencePoint( const Vector2D &vect2dA )const{
    return bVerifCoherencePoint( vect2dA . mfX, vect2dA . mfY );
}


/**
 * @brief Sol::bAjoutPoint Ajout d'un point à la fonction avec 2 variables float.
 */
bool Sol::bAjoutPoint( float fX, float fY ){
    if( ! bVerifCoherencePoint( fX, fY ) )return false;
    mVectPointFonction . push_back( Vector2D( fX, fY ) );
    miseAJourBoiteEnglobanteFonction();
    return true;
}

/**
 * @brief Sol::bAjoutPoint Ajout d'un point à la fonction avec un pair de float.
 */
bool Sol::bAjoutPoint( const Vector2D &pairPointFloat ){
    return bAjoutPoint( pairPointFloat . mfX, pairPointFloat . mfY );
}

/**
 * @brief Sol::bSuprimmerPoint Suppression du point dont le numéro est envoyé en paramètre.
 * @return true si le point a bien été suprimmé, false sinon.
 */
bool Sol::bSuprimmerPoint( unsigned int uiNumPoint ){
    if( uiNumPoint >= mVectPointFonction . size() )return false;
    mVectPointFonction . erase( mVectPointFonction . begin() + uiNumPoint );
    miseAJourBoiteEnglobanteFonction();
    return true;
}

/**
 * @brief Sol::attribuerFonction Attribution d'un tableau de point à la fonction.
 * @param vectFonction Un tableau de points.
 */
bool Sol::bAttribuerFonction( std::vector< Vector2D > &vectFonction ){
    if( vectFonction.size() == 0 )return false;

    mVectPointFonction . clear();
    mVectPointFonction . resize( vectFonction.size() );

    for( unsigned int i = 0; i < vectFonction.size() ; ++i ){
        bAjoutPoint( vectFonction[ i ] );
    }
    miseAJourBoiteEnglobanteFonction();
    synchroniserSegmentsPoints();
    return true;
}

/**
 * @brief Sol::synchroniserSegmentsPoints Création des segments de la fonction en fonction des points.
 */
void Sol::synchroniserSegmentsPoints(){
    mVectSegmentFonction . clear();
    mVectSegmentFonction . resize( mVectPointFonction . size() - 1 );
    for( unsigned int i = 0; i < mVectSegmentFonction.size() ; ++i ){
        mVectSegmentFonction[ i ] . bAttribuerPointsSegment( mVectPointFonction[ i ], mVectPointFonction[ i + 1 ] );
    }
}


/**
 * @brief Sol::afficherFonction Affichage des points de la fonction.
 */
void Sol::afficherFonction()const{
    std::cout << "Debut affichage fonction\n";
    for( unsigned int i = 0; i < mVectPointFonction . size() ; ++i ){
        std::cout << "point::" << i << "  " << mVectPointFonction[ i ] . mfX <<
                     "  " << mVectPointFonction[ i ] . mfY << "\n";
    }
    std::cout << "Fin affichage fonction\n";
}

/**
 * @brief Sol::miseAJourBoiteEnglobanteFonction Calcul des extrémités de la fonction en fonction du premier et du dernier point.
 */
void Sol::miseAJourBoiteEnglobanteFonction(){
    float fMaxOrdonnee, fMinOrdonnee;

    if( mVectPointFonction . size() == 0 ){
        mMaxAbscisse = 0;
        mMinAbscisse = 0;
        mMaxOrdonnee = 0;
        mMinOrdonnee = 0;
        return;
    }

    //traitement abscisses
    mMinAbscisse = mVectPointFonction[ 0 ] . mfX;
    mMaxAbscisse = mVectPointFonction[ mVectPointFonction.size() - 1 ] . mfX;

    //traitement  ordonnées

    //initialisation des 2 variables à la valeur de l'ordonnée du premier point
    fMaxOrdonnee = mVectPointFonction[ 0 ] . mfY;
    fMinOrdonnee = mVectPointFonction[ 0 ] . mfY;

    if( mVectPointFonction . size() == 1 )return;
    for( unsigned int i = 1; i < mVectPointFonction . size() ; ++i ){
        if( fMaxOrdonnee < mVectPointFonction[ i ] . mfY ){
            fMaxOrdonnee = mVectPointFonction[ i ] . mfY;
            continue;
        }
        if( fMinOrdonnee > mVectPointFonction[ i ] . mfY )
            fMinOrdonnee = mVectPointFonction[ i ] . mfY;
    }

}

/**
 * @brief Sol::fRetourYFonction Calcul du Y de la fonction avec un paramètre X.
 * La fonction va trouver le segment concerné et appeler la fonction fRetourYSegment.
 * Les fonctions bCalculCohefDirectFonction et bCalculConstanteFonction doivent avoir été appelée antérieurement.
 * @param fX La valeur de X par rapport à la fonction.
 * @return La valeur de Y trouvé à l'aide du X.
 */
float Sol::fRetourYFonction( float fX ){
    assert( ! ( fX < mMinAbscisse || fX > mMaxAbscisse ) && "Point hors limite de la fonction." );

    for( unsigned int i = 1; i < mVectPointFonction . size() ; ++i ){
        if( fX <= mVectPointFonction[ i ] . mfX )return mVectSegmentFonction[ i - 1 ] .fRetourYSegment( fX );
    }
    assert( false && "Point hors limite de la fonction." );
    return 0;//erreur
}

/**
 * @brief Sol::bCalculConstanteFonction Fonction calculant et mémorisant les constantes a et b des fonctions "y = ax + b".
 * Ces fonctions correspondant a chaque segment de la fonction.
 * @return false si la fonction ne comporte qu'un seul ou aucun point, true si le calcul a bien été effectué.
 */
void Sol::bCalculConstanteFonction(){
    for( unsigned int i = 0; i < mVectSegmentFonction . size() - 1 ; ++i ){
        mVectSegmentFonction[ i ] . bCalculConstanteSegment();
    }
}



/**
 * @brief Sol::Sol Destructeur de la classe Sol.
 */
Sol::~Sol(){

}

