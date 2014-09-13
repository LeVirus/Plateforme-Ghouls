#include "moteur.hpp"
#include "jeu.hpp"
#include "constantes.hpp"
#include <SFML/Graphics.hpp>

/**
 * @brief Constructeur de la classe moteur
 */
Moteur::Moteur(){

}

/**
 * @brief Fonction d'initialisation de tous les modules du moteur.
 * Mémorisation du pointeur vers Jeu
 * @param ptrJeu Un pointeur vers Jeu
 */
void Moteur::initialiserMoteur( Jeu *ptrJeu ){
    if( ptrJeu )
        mPtrMemJeu = ptrJeu;
    mMoteurG.initialiser( this );
}

/**
 * @brief Boucle principalle du moteur.
 * Traitement des touches pressée et des modules du moteur.
 */
void Moteur::lancer(){
    unsigned char cDirection, ucTmpCmpt = 0;
    mMoteurG.synchroniserNiveau();
    do{

        ucTmpCmpt++;
        if( ucTmpCmpt > 10 )ucTmpCmpt = 0;

        if( ucTmpCmpt == 1 ){//TMP
            cDirection = 0;
            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )break;

            //si haut est presse OU bas
            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
                cDirection += HAUT;
            else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
                cDirection += BAS;
            //si droite est presse OU gauche
            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
                cDirection += DROITE;
            else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
                cDirection += GAUCHE;

            if( cDirection != 0 )mMoteurG.deplacerEcran( cDirection );
            mMoteurG.raffraichirEcran();
        }
    }while( true );
}

/**
 * @brief Fonction de liaison entre MoteurGraphique et Niveau
 * pour une synchronisation.
 * @param pairPosEcranHG les coordonnées de MoteurGraphique
 * à modifier (angle Haut-Gauche)
 * @param pairPosEcranBD les coordonnées de MoteurGraphique
 * à modifier (angle Bas-Droite)
 */
void Moteur::synchroniserEcranNiveau(
        std::pair< float, float > &pairPosEcranHG,
        std::pair< float, float > &pairPosEcranBD ){

    mPtrMemJeu->synchroniserEcranNiveau(
                pairPosEcranHG , pairPosEcranBD );

}

/**
 * @brief Recuperation du tableau de l'écran
 * @return référence constante du tableau en provenance de Niveau
 */
const Tableau2D &Moteur::recupTabEcran( const float &fPosEcranX, const float &fPosEcranY ){
    return mPtrMemJeu->recupTabEcran( fPosEcranX, fPosEcranY );
}

/**
 * @brief Destructeur de la classe moteur
 */
Moteur::~Moteur(){

}
