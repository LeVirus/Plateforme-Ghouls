#include "jeu.hpp"

/**
 * brief constructeur de la classe Jeu
 */
Jeu::Jeu(){

}

/**
 * brief Fonction de lancement du jeu.
 * Initialisation du premier niveau.
 */
bool Jeu::lancer(){
    unsigned int uiNumNiveau = 0;
    mMoteurPrincipal.initialiserMoteur( this );
    if( ! mNiveau.bInitialiserNiveau( uiNumNiveau ) )
        return false;
    mNiveau.verifDebutNiveau();
//mNiveau.afficherNivEcran();

    mMoteurPrincipal . chargerEntitesTest();

    mMoteurPrincipal . lancer();
    return true;
}

/**
 * brief Récupération du tableau de l'écran courrant à partir de la
 * classe niveau.
 * @return la référence constante du tableau de l'écran.
 */
const Tableau2D &Jeu::recupTabEcran( const float &fPosEcranX, const float &fPosEcranY ){
    return mNiveau.retourTabEcran( fPosEcranX, fPosEcranY );
}

/**
 * @brief Fonction de liaison entre MoteurGraphique et Niveau
 * pour une synchronisation.
 * @param pairPosEcranHG les coordonnées de MoteurGraphique
 * à modifier (angle Haut-Gauche)
 * @param pairPosEcranBD les coordonnées de MoteurGraphique
 * à modifier (angle Bas-Droite)
 */
void Jeu::synchroniserEcranNiveau(
        std::pair< float, float > &pairPosEcranHG,
        std::pair< float, float > &pairPosEcranBD ){

    mNiveau.synchroniserEcranNiveau(
            pairPosEcranHG , pairPosEcranBD );
}

/**
 * @brief Fonction de transfert de la case de la position de l'écran ( coin Haut-Gauche ).
 * @param fPositionEcranX l'abscisse de la position de l'écran
 * @param fPositionEcranY l'ordonnée de la position de l'écran
 * @return La référence constante des coordonnées de la case Haut-Gauche de l'écran
 */
const std::pair< unsigned int, unsigned int > &Jeu::pairUiRetourCaseCourrante( float fPositionEcranX,  float fPositionEcranY ){
    return mNiveau.pairUiRetourCaseCourrante( fPositionEcranX, fPositionEcranY );
}

/**
 * @brief destructeur de la classe Jeu
 */
Jeu::~Jeu(){

}
