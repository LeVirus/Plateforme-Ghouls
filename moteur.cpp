#include "moteur.hpp"
#include "constantes.hpp"
#include "jeu.hpp"
#include <SFML/Graphics.hpp>

#include "positioncomponent.hpp"
#include "displaycomponent.hpp"
#include "displaysystem.hpp"

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
 * @brief Moteur::getECSEngine
 * Renvoie une référence vers Engine (ECS).
 * @return Une référence vers Engine.
 */
Engine & Moteur::getECSEngine(){
    return mEngine;
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
 * @brief Moteur::chargerEntitesTest
 * Chargement d'entité par défaut pour le test.
 */
void Moteur::chargerEntitesTest(){
    Engine engine;
    ComponentManager & compMan = engine.getComponentManager();
    engine.AddEntity();
    engine.AddEntity();
    engine.bAddComponentToEntity( 1, DISPLAY_COMPONENT );
    engine.bAddComponentToEntity( 1, POSITION_COMPONENT );
    engine.bAddComponentToEntity( 2, DISPLAY_COMPONENT );
    engine.bAddComponentToEntity( 2, POSITION_COMPONENT );
    engine.getSystemManager().bAddSystem( DISPLAY_SYSTEM ); // std::cout << "sdf" << std::endl;
    compMan . updateComponentFromEntity();
    PositionComponent * posComp = compMan . searchComponentByType< PositionComponent >( 1, POSITION_COMPONENT );
    if( posComp ){
        posComp -> mfPositionX = 100;
        posComp -> mfPositionY = 158;
    }
    PositionComponent * posComp2 = compMan . searchComponentByType< PositionComponent >( 2, POSITION_COMPONENT );
    if( posComp2 ){
        posComp2 -> mfPositionX = 10;
        posComp2 -> mfPositionY = 298;
    }
    DisplayComponent * dispComp = compMan . searchComponentByType< DisplayComponent >( 1, DISPLAY_COMPONENT );
    if( dispComp ){
        dispComp -> muiNumSprite = 3;
    }
    DisplayComponent * dispComp2 = compMan . searchComponentByType< DisplayComponent >( 2, DISPLAY_COMPONENT );
    if( dispComp2 ){
        dispComp2 -> muiNumSprite = 8;
    }

    engine.execIteration();

}

/**
 * @brief Fonction de liaison entre MoteurGraphique et Niveau
 * pour une synchronisation.
 * @param pairPosEcranHG les coordonnées de MoteurGraphique
 * à modifier (angle Haut-Gauche)
 * @param pairPosEcranBD les coordonnées de MoteurGraphique
 * à modifier (angle Bas-Droite)
 */
void Moteur::synchroniserEcranNiveau( std::pair< float, float > &pairPosEcranHG, std::pair< float, float > &pairPosEcranBD ){

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
 * @brief Fonction de transfert de la case de la position de l'écran ( coin Haut-Gauche ).
 * @param fPositionEcranX l'abscisse de la position de l'écran
 * @param fPositionEcranY l'ordonnée de la position de l'écran
 * @return La référence constante des coordonnées de la case Haut-Gauche de l'écran
 */
const std::pair< unsigned int, unsigned int > &Moteur::pairUiRetourCaseCourrante( float fPositionEcranX,  float fPositionEcranY ){
    return mPtrMemJeu->pairUiRetourCaseCourrante( fPositionEcranX, fPositionEcranY );
}

/**
 * @brief Destructeur de la classe moteur
 */
Moteur::~Moteur(){

}
