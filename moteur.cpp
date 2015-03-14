#include "moteur.hpp"
#include "constantes.hpp"
#include "jeu.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

#include "positioncomponent.hpp"
#include "inputcomponent.hpp"
#include "displaycomponent.hpp"
#include "behaviorcomponent.hpp"
#include "moveablecomponent.hpp"
#include "displaysystem.hpp"
#include "inputsystem.hpp"
#include "iasystem.hpp"

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
    return mECSEngine;
}

/**
 * @brief Boucle principalle du moteur.
 * Traitement des touches pressée et des modules du moteur.
 */
void Moteur::lancer(){
    unsigned char cDirection, ucTmpCmpt = 0;
    mMoteurG.synchroniserNiveau();

    InputComponent * inputComp = mECSEngine . getComponentManager() . searchComponentByType< InputComponent >( 1, INPUT_COMPONENT );
    if( ! inputComp ) std::cout << "erreur inputComp NULL\n";
    do{

        ucTmpCmpt++;
        if( ucTmpCmpt > 10 )ucTmpCmpt = 0;

        if( ucTmpCmpt == 1 ){//TMP
            cDirection = 0;
            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )break;

            //si haut est presse OU bas
            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ){
                cDirection += HAUT;
                if( inputComp ){
                    inputComp -> mBitsetInput[ MOVE_UP ] = true;
                }
            }
            else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ){
                cDirection += BAS;
                if( inputComp ){
                    inputComp -> mBitsetInput[ MOVE_DOWN ] = true;
                }
            }
            //si droite est presse OU gauche
            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ){
                cDirection += DROITE;
                if( inputComp ){
                    inputComp -> mBitsetInput[ MOVE_RIGHT ] = true;
                }
            }
            else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) ){
                cDirection += GAUCHE;
                if( inputComp ){
                    inputComp -> mBitsetInput[ MOVE_LEFT ] = true;
                }
            }

            if( cDirection != 0 )mMoteurG.deplacerEcran( cDirection );

            mECSEngine .execIteration();
            mMoteurG.raffraichirEcran();
        }

    }while( true );
}

/**
 * @brief Moteur::chargerEntitesTest
 * Chargement d'entité par défaut pour le test.
 */
void Moteur::chargerEntitesTest(){
    ComponentManager & compMan = mECSEngine.getComponentManager();
    mECSEngine.AddEntity();
    mECSEngine.AddEntity();
    mECSEngine.bAddComponentToEntity( 0, DISPLAY_COMPONENT );
    mECSEngine.bAddComponentToEntity( 0, POSITION_COMPONENT );
    mECSEngine.bAddComponentToEntity( 0, BEHAVIOR_COMPONENT );
    mECSEngine.bAddComponentToEntity( 0, MOVEABLE_COMPONENT );

    mECSEngine.bAddComponentToEntity( 1, DISPLAY_COMPONENT );
    mECSEngine.bAddComponentToEntity( 1, POSITION_COMPONENT );
    mECSEngine.bAddComponentToEntity( 1, MOVEABLE_COMPONENT );
    mECSEngine.bAddComponentToEntity( 1, INPUT_COMPONENT );

    if( ! mECSEngine.getSystemManager().bAddSystem( DISPLAY_SYSTEM ) ) std::cout << "Echec DisplaySystem non ajouté\n" ;
    if( ! mECSEngine.getSystemManager().bAddSystem( IA_SYSTEM ) ) std::cout << "Echec BehaviorSystem non ajouté\n" ;
    if( ! mECSEngine.getSystemManager().bAddSystem( INPUT_SYSTEM ) ) std::cout << "Echec InputSystem non ajouté\n" ;
    if( ! mECSEngine.getSystemManager().bAddSystem( GRAVITY_SYSTEM ) ) std::cout << "Echec InputSystem non ajouté\n" ;

    //mECSEngine.displayVectEntity();
    compMan . updateComponentFromEntity();


    //mECSEngine . getSystemManager() . searchSystemByType < DisplaySystem > ( DISPLAY_SYSTEM ) -> refreshEntity();
    //mECSEngine . getSystemManager() . searchSystemByType < IASystem > ( IA_SYSTEM ) -> refreshEntity();


    //ENTITE 0==========================================================
    PositionComponent * posComp = compMan . searchComponentByType< PositionComponent >( 0, POSITION_COMPONENT );
    if( posComp ){
        posComp -> mfPositionX = 100;
        posComp -> mfPositionY = 50;
    }
    DisplayComponent * dispComp = compMan . searchComponentByType< DisplayComponent >( 0, DISPLAY_COMPONENT );
    if( dispComp ){
        dispComp -> muiNumSprite = 0;
    }
    BehaviorComponent * behavComp = compMan . searchComponentByType< BehaviorComponent >( 0, BEHAVIOR_COMPONENT );
    if( behavComp ){
        //behavComp -> muiTypeBehavior = RING;
        //behavComp -> muiTypeBehavior = SINUSOIDAL;
        behavComp -> muiTypeBehavior = ROUND_TRIP;
    }

    MoveableComponent * moveComp = compMan . searchComponentByType< MoveableComponent >( 0, MOVEABLE_COMPONENT );
    if( moveComp ){
        moveComp -> mfVelocite = 3;
        moveComp -> mVectFCustumVar[ 0 ] = 200;
        moveComp -> mVectFCustumVar[ 1 ] = 30;
        //moveComp -> mbTerrestrial = false;
    }

    //ENTITE 1==========================================================
    PositionComponent * posCompA = compMan . searchComponentByType< PositionComponent >( 1, POSITION_COMPONENT );
    if( posCompA ){
        posCompA -> mfPositionX = 0;
        posCompA -> mfPositionY = 0;
    }
    DisplayComponent * dispCompA = compMan . searchComponentByType< DisplayComponent >( 1, DISPLAY_COMPONENT );
    if( dispCompA ){
        dispCompA -> muiNumSprite = 1;
    }

    MoveableComponent * moveCompA = compMan . searchComponentByType< MoveableComponent >( 1, MOVEABLE_COMPONENT );
    if( moveCompA ){
        moveCompA -> mfVelocite = 5;
        moveCompA -> mbTerrestrial = true;
    }

    mECSEngine.getSystemManager().searchSystemByType< IASystem >( IA_SYSTEM ) ->  initMoveable( behavComp, posComp, moveComp );
    //InputSystem * inputSystem = mECSEngine.getSystemManager().searchSystemByType< InputSystem >( INPUT_SYSTEM );



    mECSEngine.execIteration();

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
