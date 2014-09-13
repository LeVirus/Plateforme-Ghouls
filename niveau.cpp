#include "niveau.hpp"
#include "constantes.hpp"
#include <vector>
#include <iostream>
#include <fstream>
//#include <string>

/**
 * @brief Constructeur de la classe Niveau
 */
Niveau::Niveau(){

}

/**
 * @brief Fonction de chargement d'un niveau
 * en fonction du paramètre. Le niveau est chargé à partir d'un
 * fichier texte.
 * @param uiChoixNiveau : le numéro du niveau a charger
 */
bool Niveau::bInitialiserNiveau( unsigned int &uiChoixNiveau ){
    std::string strMemChemin;
    //création d'un vector temporaire
    std::vector< unsigned char > vectNiveau;
    unsigned int uiMemTile, uiLongueurTab, uiLargeurTab;

    //resize du tableauEcran
    mTabEcran.resize( NBR_TUILE_TILE_MAPPING_X, NBR_TUILE_TILE_MAPPING_Y );

    switch( uiChoixNiveau ){
        case 0:
        //dans Qtcreator le chemin pars de l'executable
            strMemChemin = "../Plateforme/Ressources/niveau0.txt";
            break;
        default:
            return false;
            break;
    }
std::ifstream flux( strMemChemin.c_str(), std::ios::in );
    if( flux ){
        flux >> uiLongueurTab;
        flux >> uiLargeurTab;

        vectNiveau.resize( uiLongueurTab * uiLargeurTab );
        //resize du tableau

        flux >> muiCaseDebutNiveauX;
        flux >> muiCaseDebutNiveauY;
        for( unsigned int i = 0; i < vectNiveau.size() ;++i ){
            flux >> uiMemTile;//recup de la valeur dans un entier
            if( uiMemTile > 255 ){//verif si la valeur rentre dans un char
                std::cerr<<"nombre non conforme pour le tile mapping"<<std::endl;
                break;
            }

            vectNiveau[ i ] = uiMemTile;
        }
        flux.close();  // on ferme le fichier
    }
    else{
        std::cout << "erreur flux init niveau   " << std::endl;
    }
    //envoi du tableau et de sa taille a la classe Tableau2d
    return mTabNiveau.bAttribuerTab( vectNiveau, uiLongueurTab, uiLargeurTab );
}

/**
 * @brief Fonction de vérification de la cohérence de la position
 * du début du Niveau.
 */
void Niveau::verifDebutNiveau(){
    bool retour = false;
    //si la taille de la camera est >= a la taille du niveau
    //début niveau = 0,0
    if( mTabEcran.getLongueur() >= mTabNiveau.getLongueur() ){
        muiCaseDebutNiveauX = 0;
        retour = true;
    }

    if( mTabEcran.getLargeur() >= mTabNiveau.getLargeur() ){
        muiCaseDebutNiveauY = 0;
        retour = true;
    }

    if( !retour ){
    //si début Niveau est dépasse la limite Bas Droite(taille caméra)
    //correction de sa position
    if( muiCaseDebutNiveauX > mTabNiveau.getLongueur() -
            mTabEcran.getLongueur() )
        muiCaseDebutNiveauX =
            mTabNiveau.getLongueur() - mTabEcran.getLongueur() ;

    if( muiCaseDebutNiveauY > mTabNiveau.getLargeur() -
            mTabEcran.getLargeur() )
        muiCaseDebutNiveauY =
            mTabNiveau.getLargeur() - mTabEcran.getLargeur() ;
    }
}

/**
 * @brief mémorisation de la case de début de niveau.
 * @param l'abscisse de la case
 * @param l'ordonnée de la case
 */
void Niveau::modifCaseDebutNiveau( const unsigned int &uiPosX, const unsigned int &uiPosY ){
    muiCaseDebutNiveauY = uiPosY;
    muiCaseDebutNiveauX = uiPosX;
    verifDebutNiveau();
}

/**
 * @brief Fonction d'affichage de la classe niveau.
 * Appel des fonctions affichage des tableau2d.
 */
void Niveau::afficherNivEcran()const{
    std::cout<<"Case début niveau X::  "<<muiCaseDebutNiveauX<<std::endl;
    std::cout<<"Case début niveau Y::  "<<muiCaseDebutNiveauY<<std::endl;
    mTabNiveau.afficherTab();
    mTabEcran.afficherTab();
}

/**
 * @brief Fonction assurant la synchronisation de Niveau et
 * MoteurGraphique.
 * @param pairPosEcranHG les coordonnées de MoteurGraphique
 * à modifier (angle Haut-Gauche)
 * @param pairPosEcranBD les coordonnées de MoteurGraphique
 * à modifier (angle Bas-Droite)
 */
void Niveau::synchroniserEcranNiveau(
        std::pair< float, float > &pairPosEcranHG,
        std::pair< float, float > &pairPosEcranBD ){

    //calcul de la position maximale Droite de la caméra
    //AngleBD auquel on soustrait la taille de la caméra
    int iDistanceX = ( mTabNiveau.getLongueur() - ( muiCaseDebutNiveauX + NBR_TUILE_ECRAN_X/*mTabEcran.getLongueur()*/ ) ) * TAILLE_TUILE,

    iDistanceY = ( mTabNiveau.getLargeur() - ( muiCaseDebutNiveauY + NBR_TUILE_ECRAN_Y/*mTabEcran.getLargeur()*/ ) ) * TAILLE_TUILE;

    //Ecrire limite angle Bas-Droite
    pairPosEcranBD.first = static_cast< float >( iDistanceX );
    pairPosEcranBD.second = static_cast< float >( iDistanceY );

    iDistanceX = muiCaseDebutNiveauX * TAILLE_TUILE * -1;

    iDistanceY = muiCaseDebutNiveauY * TAILLE_TUILE * -1;
    //Ecrire limite angle Haut-Gauche
    pairPosEcranHG.first = static_cast< float >( iDistanceX );
    pairPosEcranHG.second = static_cast< float >( iDistanceY );

}


/**
 * @brief Calcul de la case haut gauche de la portion à
 * envoyer à l'écran, à partir des coordonnées du point haut gauche
 * de l'écran et de la case origine du niveau.
 * Appel de la fonction retour VectEcran avec les coordonnées
 * calculées et renvoi de la portion à l'écran.
 * @param fPositionEcranX l'abscisse de la position de l'écran
 * @param fPositionEcranY l'ordonnée de la position de l'écran
 * @return le vector de la portion à transmettre à l'écran
 */
const Tableau2D &Niveau::retourTabEcran(
        const	float &fPositionEcranX, const float &fPositionEcranY ){

    //recup de la case haut gauche
    mPairRecept = mTabNiveau.getCoordCase( fPositionEcranX,
            fPositionEcranY, muiCaseDebutNiveauX, muiCaseDebutNiveauY );
    /*std::cout << mPairRecept.first << " retourTab  " <<
        mPairRecept.second << std::endl;*/

    //modification du tableau ecran directement ddans la classe
    if( ! mTabEcran.bRecupPortionTab( mTabNiveau, mPairRecept.first,
                mPairRecept.second	) )
        std::cout<<"coordonnées tableau hors limite"<<std::endl;
    return mTabEcran;
}

/**
 * @brief Destructeur de la classe Niveau
 */
Niveau::~Niveau(){

}
