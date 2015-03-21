#include "sol.hpp"
#include "constantes.hpp"
#include <iostream>
#include <limits>

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
 * @brief Sol::bVerifCoherencePoint Fonction de vérification de l'abscisse du point précédent avec le point à ajouter.
 * @param fX l'abscisse du point à tester.
 * @return true si le nouveau point est accepté, false sinon.
 */
bool Sol::bVerifCoherencePoint( float fX, float fY )const{
    if( mVectPointFonction . size() == 0 )
        return true;

    //cas ou le dernier point est identique au point à ajouter                                  ;
    if( (  fX - mVectPointFonction[ mVectPointFonction . size() - 1 ] . first < std::numeric_limits< float >::epsilon() ) &&
        (  fY - mVectPointFonction[ mVectPointFonction . size() - 1 ] . second < std::numeric_limits< float >::epsilon() ) )
        return false;

    return fX >= mVectPointFonction[ mVectPointFonction . size() - 1 ] . first;
}

/**
 * @brief Sol::bAjoutPoint Ajout d'un point à la fonction avec 2 variables float.
 */
bool Sol::bAjoutPoint( float fX, float fY ){
    if( ! bVerifCoherencePoint( fX, fY ) )return false;
    mVectPointFonction . push_back( std::pair < float, float >( fX, fY ) );
    miseAJourBoiteEnglobanteFonction();
    return true;
}

/**
 * @brief Sol::bAjoutPoint Ajout d'un point à la fonction avec un pair de float.
 */
bool Sol::bAjoutPoint( std::pair < float, float > & pairPointFloat ){
    if( ! bVerifCoherencePoint( pairPointFloat . first, pairPointFloat . second ) )return false;
    mVectPointFonction . push_back( std::pair < float, float >( pairPointFloat . first, pairPointFloat . second ) );
    miseAJourBoiteEnglobanteFonction();
    return true;
}

/**
 * @brief Sol::bSuprimmerPoint Suppression du point dont le numéro est envoyé en paramètre.
 * @return true si le point a bien été suprimmé, false sinon.
 */
bool Sol::bSuprimmerPoint( unsigned int uiNumPoint ){
    if( uiNumPoint >= mVectPointFonction . size() )return false;
    mVectPointFonction . erase( mVectPointFonction . begin() + uiNumPoint );
    return true;
}

/**
 * @brief Sol::attribuerFonction Attribution d'un tableau de point à la fonction.
 * @param vectFonction Un tableau de points.
 */
bool Sol::bAttribuerFonction( std::vector< std::pair < float, float > > & vectFonction ){
    if( vectFonction.size() == 0 )return false;

    mVectPointFonction . clear();
    mVectPointFonction . resize( vectFonction.size() );

    for( unsigned int i = 0; i < vectFonction.size() ; ++i ){
        bAjoutPoint( vectFonction[ i ] );
    }
    miseAJourBoiteEnglobanteFonction();
    return true;
}

/**
 * @brief Sol::afficherFonction Affichage des points de la fonction.
 */
void Sol::afficherFonction()const{
    std::cout << "Debut affichage fonction\n";
    for( unsigned int i = 0; i < mVectPointFonction . size() ; ++i ){
        std::cout << "point::" << i << "  " << mVectPointFonction[ i ] . first <<
                     "  " << mVectPointFonction[ i ] . second << "\n";
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
    mMinAbscisse = mVectPointFonction[ 0 ] . first;
    mMaxAbscisse = mVectPointFonction[ mVectPointFonction.size() - 1 ] . first;

    //traitement  ordonnées

    //initialisation des 2 variables à la valeur de l'ordonnée du premier point
    fMaxOrdonnee = mVectPointFonction[ 0 ] . second;
    fMinOrdonnee = mVectPointFonction[ 0 ] . second;

    if( mVectPointFonction . size() == 1 )return;
    for( unsigned int i = 1; i < mVectPointFonction . size() ; ++i ){
        if( fMaxOrdonnee < mVectPointFonction[ i ] . second ){
            fMaxOrdonnee = mVectPointFonction[ i ] . second;
            continue;
        }
        if( fMinOrdonnee > mVectPointFonction[ i ] . second )
            fMinOrdonnee = mVectPointFonction[ i ] . second;
    }

}

/**
 * @brief Sol::calculCohefDirectFonction Fonction calculant les cohéficients directeurs de chaque segment de la fonction.
 * Les résultats sont stockés dans un tableau.
 */
bool Sol::bCalculCohefDirectFonction(){
    if( mVectPointFonction . size() <= 1 )return false;
    mVectCohefDirect . resize( mVectPointFonction . size() - 1 );

    for( unsigned int i = 0; i < mVectCohefDirect . size() - 1 ; ++i ){
        mVectCohefDirect[ i ] = fCalculCohefDirectSegment( mVectPointFonction[ i ] . first, mVectPointFonction[ i ] . second,
                                                     mVectPointFonction[ i + 1 ] . first, mVectPointFonction[ i + 1 ] . second );
    }
    return true;
}

/**
 * @brief calculCohefDirectSegment Calcul du cohéficients directeurs d'un segment donné.
 * @param fAX L'abscisse du premier point du segment.
 * @param fAY L'abscisse du premier point du segment.
 * @param fBX L'abscisse du premier point du segment.
 * @param fBY L'abscisse du premier point du segment.
 * @return La valeur de la derive.
 */
float Sol::fCalculCohefDirectSegment( float fAX , float fAY, float fBX , float fBY ){
    return ( fBY - fAY ) / ( fBX - fAX );
}

/**
 * @brief Sol::fRetourYFonction Calcul du Y de la fonction avec un paramètre X.
 * La fonction va trouver le segment concerné et appeler la fonction fRetourYSegment.
 * @param fX La valeur de X par rapport à la fonction.
 * @return La valeur de Y trouvé à l'aide du X.
 */
float Sol::fRetourYFonction( float fX ){
    if( fX < mVectPointFonction[ 0 ] . first || fX > mVectPointFonction[ mVectPointFonction . size() - 1 ] . first )
        return ERREUR_VALEUR_HORS_LIMITE;
    for( unsigned int i = 1; i < mVectPointFonction . size() ; ++i ){
        if( fX <= mVectPointFonction[ i ] . first )return fRetourYSegment( fX,i - 1 );
    }
    return ERREUR_VALEUR_HORS_LIMITE;
}

/**
 * @brief Sol::fRetourYSegment Calcul du Y de la fonction avec un paramètre X sur le segment envoyé en paramètre.
 * @param fX La valeur de X par rapport à la fonction.
 * @param uiNumSegment Le numéro du segment à tester.
 * @return La valeur de Y trouvé à l'aide du X.
 */
float Sol::fRetourYSegment( float fX, unsigned int uiNumSegment ){
    if( uiNumSegment >= mVectPointFonction . size() - 1 )return ERREUR_VALEUR_HORS_LIMITE;
    else if( fX < mVectPointFonction[ uiNumSegment ] . first || fX > mVectPointFonction[ uiNumSegment + 1 ] . first )
        return ERREUR_VALEUR_HORS_LIMITE;

}

/**
 * @brief Sol::Sol Destructeur de la classe Sol.
 */
Sol::~Sol(){

}

