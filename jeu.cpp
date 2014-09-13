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
    mMoteurPrincipal.lancer();
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
 * @brief destructeur de la classe Jeu
 */
Jeu::~Jeu(){

}
