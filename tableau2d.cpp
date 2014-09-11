#include "tableau2d.hpp"
#include "niveau.hpp"
#include "constantes.hpp"
#include <iostream>

/**
 * @brief Constructeur standart de la classe Tableau2D
 */
Tableau2D::Tableau2D(){
    muiLargeurTab = 0;
    muiLongueurTab = 0;
}

/**
 * @brief Constructeur de la classe Tableau2D
 * Définition de la longueur et de la largeur du tableau
 * @param longueur la longueur du tableau
 * @param largeur la largeur du tableau
 */
Tableau2D::Tableau2D( const unsigned int &longueur, const unsigned int &largeur ){
    resize( longueur, largeur );
}

/**
 * @brief Fonction d'attribution du vector.
 * Vérification si les paramètres uiLongueurTab et uiLargeurTab
 * correspondent à la taille du vector en paramètres.
 * @param vect La référence constante du vector(unsigned char) à
 * attribuer à la classe.
 * @param uiLongueurTab La longueur à attribuer au vector
 * @param uiLargeurTab La largeur à attribuer au vector
 * @return Renvoie false si les paramètres de la longueur et de la
 * largeur ne correspondent pas avec la taille du vector
 * true sinon.
 */
bool Tableau2D::bAttribuerTab( const std::vector< unsigned char > &vect, unsigned int uiLongueurTab, unsigned int uiLargeurTab ){
    if( uiLongueurTab * uiLargeurTab != vect.size() )
        return false;
    resize( uiLongueurTab, uiLargeurTab );
    std::copy ( &vect[ 0 ], &vect[ vect.size() - 1 ], &mVectChar[ 0 ] );
    return true;
}

/**
 * @brief Renvoie une référence constante du vector contenu dans
 * la classe
 * @return La référence constante de mVectChar.
 */
const std::vector< unsigned char > &Tableau2D::getTab()const{
    return mVectChar;
}

/**
 * @brief Fonction de modification de la taille du vector.
 * mise a jour de muiLargeurTab et muiLongueurTab
 * @param longueur La nouvelle longueur du tableau.
 * @param largeur La nouvelle largeur du tableau.
 */
void Tableau2D::resize( const unsigned int &longueur, const unsigned int &largeur ){
    muiLargeurTab = longueur;
    muiLongueurTab = largeur;
    mVectChar.resize( longueur * largeur  );
}

/**
 * @brief Fonction d'affichage console du tableau.
 * L'affichage sera effectué en fonction des propriétés
 * muiLargeurTab et muiLongueurTab.
 */
void Tableau2D::afficherTab()const{
    unsigned int uiMemCaseTab;
    std::cout << "AFFICHAGE" << std::endl;
    std::cout << "Largeur tableau::" << muiLargeurTab <<
        std::endl;
    std::cout << "Longueur tableau::" << muiLongueurTab <<
        std::endl;
    for( unsigned int i = 0; i < mVectChar.size() ; ++i ){
        //conversion char vers int pour l'affichage console
        uiMemCaseTab = mVectChar[i];
        std::cout << uiMemCaseTab << " ";
        //passer a la ligne
        if( i != 0 && 0 == ( i + 1 ) % muiLongueurTab )
            std::cout << std::endl;
    }

}
/**
 * @brief Récupération d'une portion du tableau
 */
bool Tableau2D::bRecupPortionTab(
        const Tableau2D &tab,
        const unsigned int &uiCaseHautGaucheX,
        const unsigned int &uiCaseHautGaucheY ){

    std::vector< unsigned char > tmpVectNiv;
    unsigned int uiPositionVectEcran = 0,
                             uiMemCaseBasDroiteX = uiCaseHautGaucheX +
                                 ( NBR_TUILE_TILE_MAPPING_X - 1 ),
                             uiMemCaseBasDroiteY = uiCaseHautGaucheY +
                                 ( NBR_TUILE_TILE_MAPPING_Y - 1 ),
                             uiTmpLongueurNiveau;

    /*std::cerr<<" var  bRecupPortion "<<uiCaseHautGaucheX<<"  "<<uiCaseHautGaucheY
        <<"  "<<uiMemCaseBasDroiteX<<"  "<<uiMemCaseBasDroiteY<<
        "  "<<muiLongueurTab<<"  "<<muiLargeurTab<<
        std::endl;*/
    //verif des case haut-gauche et bas-droite du rectangle
    if( ( HORS_TAB == tab.getValAt( uiCaseHautGaucheX, uiCaseHautGaucheY ) ) ||
            ( HORS_TAB == tab.getValAt( uiMemCaseBasDroiteX,
                                                            uiMemCaseBasDroiteY ) ) ){
        std::cerr<<"Erreur bRecupPortionTab. coordonnées non valide   "<<uiCaseHautGaucheX<<"  "<<uiCaseHautGaucheY
            <<"  "<<uiMemCaseBasDroiteX<<"  "<<uiMemCaseBasDroiteY<<
            "  "<<muiLongueurTab<<"  "<<muiLargeurTab<<
            std::endl;
        return false;
    }

    tmpVectNiv = tab.getTab();
    //recup de la longueur et de la largeur du tableau de niveau
    uiTmpLongueurNiveau = tab.getLongueur();

    for( unsigned int i = uiCaseHautGaucheY ; i < uiCaseHautGaucheY +
            NBR_TUILE_ECRAN_Y ; ++i ){

        //copie des portions de ligne du tableau du niveau vers
        //le tableau ecran
        unsigned int uiMemPosCurseur =  i * uiTmpLongueurNiveau +
        uiCaseHautGaucheX;

        std::copy ( &tmpVectNiv[ uiMemPosCurseur ],
                &tmpVectNiv[ uiMemPosCurseur + NBR_TUILE_TILE_MAPPING_X ],
                &mVectChar[ uiPositionVectEcran ] );
        uiPositionVectEcran += NBR_TUILE_TILE_MAPPING_X;

    }

    return true;
}

/**
 * @brief Fonction calculant la case correspondante aux coordonnées
 * de l'écran (coin haut gauche).
 * @param fPositionEcranX l'abscisse de la position de l'écran
 * @param fPositionEcranY l'ordonnée de la position de l'écran
 * @param uiCaseDebutNivX l'abscisse de la case debut niveau
 * @param uiCaseDebutNivY l'ordonnée de la case debut niveau
 * @return coordonnées de la case correspondante
 */
std::pair< unsigned int, unsigned int > Tableau2D::getCoordCase( const float &fPositionEcranX, const float &fPositionEcranY,
                                                                 const unsigned int &uiCaseDebutNivX, const unsigned int &uiCaseDebutNivY ){

    //calcul du reste
    //verif si la case debut niveau est bien dans le tableau
    if( HORS_TAB == getValAt( uiCaseDebutNivX, uiCaseDebutNivY ) ){
        mPairCase.first = 100000;
        return mPairCase;
    }

    //la position 0,0 de l'écran correspond aux coordonnées du coin
    //haut gauche de la case du début du niveau
    int iPosCaseX = fPositionEcranX / TAILLE_TUILE,
            iModCaseX = static_cast< int >( fPositionEcranX ) % TAILLE_TUILE,
            iPosCaseY = fPositionEcranY / TAILLE_TUILE,
            iModCaseY = static_cast< int >( fPositionEcranY ) % TAILLE_TUILE;
    //conversion de la valeur trouvée avec la division vers la case
    //du tableau
    iPosCaseX += uiCaseDebutNivX;
    if( iModCaseX < 0 )
        iPosCaseX--;


    iPosCaseY += uiCaseDebutNivY;

    if( iModCaseY < 0 )
        iPosCaseY--;

    /*std::cerr<<"  getCoordCase  "<<iPosCaseX<<"  "<<
        "  "<<iPosCaseY<<"  "<<iModCaseX<<"  "<<iModCaseY<<
        std::endl;*/

    mPairCase.first = iPosCaseX ;
    mPairCase.second = iPosCaseY ;

    //verif si la case trouvée est dans le tableau
    if( HORS_TAB == getValAt( iPosCaseX , iPosCaseY ) ){
        mPairCase.first = 100000;
    }

    //static_cast< unsigned int > ( iPosCaseY )

    return mPairCase;
}

/**
 * @brief Récupération de la valeur a un endroit du
 * tableau donné en argument(X,Y)
 * envoie en référence constante.
 * @param uiCaseX Abscisse de la case
 * @param uiCaseY Ordonnée de la case
 * @return La valeur de la case
 */
const unsigned char &Tableau2D::getValAt( const unsigned int &uiCaseX, const unsigned int &uiCaseY )const{
    if( uiCaseX > muiLongueurTab || uiCaseY > muiLargeurTab ){
        std::cout<<"getValAt Tableau2D Hors tab  "<<uiCaseX<<"  "<<muiLongueurTab<<"  "<<uiCaseY<<"  "<<muiLargeurTab<<std::endl;
        return HORS_TAB;
    }
    //std::cout<< uiCaseX << "   " << uiCaseY <<std::endl;
    return mVectChar[ uiCaseX + uiCaseY * muiLargeurTab ];
}

/**
 * @brief Destructeur de la classe Tableau2D
 */
Tableau2D::~Tableau2D(){

}
