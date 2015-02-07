#include "moteurgraphique.hpp"
#include "moteur.hpp"
#include "tableau2d.hpp"
#include "constantes.hpp"
#include "displaysystem.hpp"
#include "displaycomponent.hpp"
#include "positioncomponent.hpp"
#include "ECSconstantes.hpp"
#include <iostream>
#include <map>

/**
 * @brief Constructeur de la classe MoteurGraphique
 */
MoteurGraphique::MoteurGraphique(){

}


/**
 * @brief Fonction de création et de configuration des outils
 * d'affichage.
 * Mémorisation du pointeur vers Moteur
 * @param ptrMoteur un pointeur vers Moteur
 */
void MoteurGraphique::initialiser( Moteur *ptrMoteur ){
    if( ptrMoteur )
        mPtrMemMoteur = ptrMoteur;
    mFenetre.create(sf::VideoMode( LARGEUR_ECRAN, LONGUEUR_ECRAN ), "ghouls", sf::Style::Default );

    mCamera.reset( sf::FloatRect( 0, 0, LONGUEUR_ECRAN , LARGEUR_ECRAN ) );
    mFenetre.setView( mCamera );
    mFenetre.setFramerateLimit(60);
    initialiserVertexArray();

    //mettre valeur position courrante hors du tableau
    mPositionCourranteTableauNiveau.first = 100000;
    mPositionCourranteTableauNiveau.second = 100000;
}

/**
 * @brief MoteurGraphique::initialiserNiveau
 * Fonction de chargement des textures et des sprites associés au niveau, dont le numéro est envoyé en paramètre.
 * @param uiNumNiveau le numéro du niveau
 */
void MoteurGraphique::initialiserNiveau( unsigned int uiNumNiveau ){
    switch( uiNumNiveau ){
    case 0:
        if(  !textureNiveau.loadFromFile("../Ressources/gG.jpg")  ) std::cout << "fail load niveau text\n";
        mVectSprite .push_back( std::make_unique< sf::Sprite >() );
        mVectSprite[ 0 ] -> setTexture( textureNiveau );
        mVectSprite[ 0 ] -> setTextureRect( sf::IntRect(0, 0, 100, 100) );// valeur au hasard

        mVectSprite .push_back( std::make_unique< sf::Sprite >() );
        mVectSprite[ 1 ] -> setTexture( textureNiveau );
        mVectSprite[ 1 ] -> setTextureRect( sf::IntRect(10, 270, 100, 100) );// valeur au hasard
        break;
    default:
        break;
    }
}


/**
 * @brief Fonction de configuration du tableau de Vertex destiné à afficher le TileMApping
 */
void MoteurGraphique::initialiserVertexArray(){

    unsigned int uiPosCaseX = 0, uiPosCaseY = 0;

    //détermination du type du tableau de vertex
    mVertArrayTileMap.setPrimitiveType ( sf::Quads );
    mVertArrayTileMap.resize ( NBR_TUILE_TILE_MAPPING_X * NBR_TUILE_TILE_MAPPING_Y * 4 );

    //traitement de toutes les autres cases
    for( unsigned int i = 0 ; i < NBR_TUILE_TILE_MAPPING_X * NBR_TUILE_TILE_MAPPING_Y * 4 ; i += 4 ){
        if( uiPosCaseX == NBR_TUILE_TILE_MAPPING_X ){
            uiPosCaseX = 0;
            uiPosCaseY++;
        }
        mVertArrayTileMap[ i ].position = sf::Vector2f( uiPosCaseX * TAILLE_TUILE, uiPosCaseY * TAILLE_TUILE );
        mVertArrayTileMap[ i + 1 ].position = sf::Vector2f( mVertArrayTileMap[ i ].position.x + TAILLE_TUILE, mVertArrayTileMap[ i ].position.y );
        mVertArrayTileMap[ i + 2 ].position = sf::Vector2f(
                    mVertArrayTileMap[ i ].position.x + TAILLE_TUILE, mVertArrayTileMap[ i ].position.y + TAILLE_TUILE );
        mVertArrayTileMap[ i + 3 ].position = sf::Vector2f( mVertArrayTileMap[ i ].position.x, mVertArrayTileMap[ i ].position.y + TAILLE_TUILE );

        uiPosCaseX++;
    }
}

/**
 * @brief Fonction d'affichage du tableau de Vertex (TileMapping).
 * La fonction calcule la position que doit avoir le rectangle(par rapport à la caméra).
 */
void MoteurGraphique::positionnerTileMappingEcran(){
    int memPosX, memPosY;
    std::pair< float, float > pairPosEcran = pairGetPosEcran();

    //traitement abscisses
    memPosX = static_cast< int >( pairPosEcran.first ) % TAILLE_TUILE;
    if( memPosX < 0 ){
        //récupération de la valeur absolue pour pouvoir soustraire cette valeur à la position de l'écarn
        memPosX = -1 * ( -32 - memPosX );
    }
    //traitement ordonnées
    memPosY = static_cast< int >( pairPosEcran.second ) % TAILLE_TUILE;
    if( memPosY < 0 ){
        memPosY = -1 * ( -32 - memPosY );
    }

    //déplacement du tableau
    deplacerVertArrayEcran( pairPosEcran.first - memPosX, pairPosEcran.second - memPosY );

}

/**
 * @brief Fonction qui positionne tous les vertex (TileMapping) par rapport au coordonnées envoyées en argument.
 * Le point [0] est pris pour référence.
 * @param fPosX La nouvelle position du tableau de vertex abscisses
 * @param fPosY La nouvelle position du tableau de vertex ordonnées
 */
void MoteurGraphique::deplacerVertArrayEcran( float fPosX, float fPosY ){
    fPosX = fPosX - mVertArrayTileMap[ 0 ].position.x;
    fPosY = fPosY - mVertArrayTileMap[ 0 ].position.y;
    for( unsigned int i = 0; i < mVertArrayTileMap.getVertexCount() ; i++ ){
        mVertArrayTileMap[ i ].position.x += fPosX;
        mVertArrayTileMap[ i ].position.y += fPosY;
    }
}


/**
 * @brief Fonction d'affichage du jeu
 * Récupération du tableau de l'écran courrant.
 */
void MoteurGraphique::raffraichirEcran(){
    bool erreur = false, bTableauIdentique;
    std::pair< float, float > pairCoordEcran = pairGetPosEcran();
    bTableauIdentique = bVerifTableauSimilaire( pairCoordEcran.first, pairCoordEcran.second );
    //std::cerr << pairCoordEcran.first << "coors ecran" << pairCoordEcran.second << std::endl;

    if( mPtrMemMoteur ){
        //si la position actuelle est la même que la position précédente on garde le même tableau
        if( ! bTableauIdentique ){
            //recup du tableau de Niveau
            const Tableau2D &tabEcran = mPtrMemMoteur->recupTabEcran( pairCoordEcran.first, pairCoordEcran.second );
            //tabEcran.afficherTab();//affichage console

            if( ! bDessinerVertArrayNiveau( tabEcran ) ){
                std::cerr<<"Erreur bDessinerVertArrayNiveau"<<std::endl;
                erreur = true;
            }
            else{
                positionnerTileMappingEcran();
            }
        }
        if( ! erreur ){
            mFenetre.clear( sf::Color::Black );
            mFenetre.setView( mCamera );

            //positionnerTileMappingEcran();
            mFenetre.draw( mVertArrayTileMap, &textureA );
            dessinerSpriteECS();

            mFenetre.display();
        }
    }
}

/**
 * @brief MoteurGraphique::dessinerSpriteDisplaySystem
 * La fonction récupère les données concernant l'affichage des éléments de DisplaySystem(ECS).
 * A l'aide de ces données les sprites correspondants sont affichés.
 */
void MoteurGraphique::dessinerSpriteECS(){
    //récupération du conteneur de composants nécéssaires a l'affichage
    const std::map< DisplayComponent *, PositionComponent * > & MapContainerSprite = mPtrMemMoteur -> getECSEngine() .
            getSystemManager() . searchSystemByType < DisplaySystem > ( DISPLAY_SYSTEM ) -> getMapComponentDisplaySystem() ;
     mPtrMemMoteur -> getECSEngine() .
                getSystemManager() . searchSystemByType < DisplaySystem > ( DISPLAY_SYSTEM ) ->displaySystem();
    std::cout << MapContainerSprite .size() << "\n";

    for( std::map< DisplayComponent *, PositionComponent * >::const_iterator it = MapContainerSprite.begin() ; it != MapContainerSprite.end() ; it++ ){
        //ce fonctionnement est temporaire
        DisplayComponent *ptrDisplayComp = ( *it) . first;
        PositionComponent *ptrPositionComp = ( *it) . second;
        std::cout << ptrDisplayComp -> muiNumSprite << "\n";
        std::cout << ptrPositionComp -> mfPositionX << "Y  " << ptrPositionComp -> mfPositionY <<"\n";
    }
}

/**
 * @brief Fonction qui dessine en fonction du tableau reçu de Niveau
 * La partie du niveau à afficher.
 * @param tabNivEcran Le tableau 2d de la partie du Niveau àœ
 * afficher.
 * @return si les valeurs de tabNivEcran sont valide
 * false sinon.
 */
bool MoteurGraphique::bDessinerVertArrayNiveau( const Tableau2D &tabNivEcran ){
    bool retour = true;
    unsigned int uiCoordBlockX, uiCoordBlockY, uiCoordTabX = 0, uiCoordTabY = 0;
    for( unsigned int i = 0; i < mVertArrayTileMap.getVertexCount() ; i+=4 ){

        if( uiCoordTabX == NBR_TUILE_TILE_MAPPING_X ){
            uiCoordTabY++;
            uiCoordTabX = 0;
        }

        //récupération de la valeur de la case correspondante a i
        switch( tabNivEcran.getValAt( uiCoordTabX, uiCoordTabY ) ){
        case BLOCK_A:
            uiCoordBlockX = 60;
            uiCoordBlockY = 142;
            break;
        case BLOCK_B:
            uiCoordBlockX = 35;
            uiCoordBlockY = 118;
            break;
        case BLOCK_C:
            uiCoordBlockX = 74;
            uiCoordBlockY = 91;
            break;
        case BLOCK_D:
            uiCoordBlockX = 140;
            uiCoordBlockY = 149;
            break;
        default:
            retour = false;
            tabNivEcran.afficherTab();
            break;
            //Erreur tableau
        }

        if( ! retour )break;

        mVertArrayTileMap[ i ].texCoords = sf::Vector2f( uiCoordBlockX, uiCoordBlockY );
        mVertArrayTileMap[ i + 1 ].texCoords = sf::Vector2f( uiCoordBlockX + TAILLE_TUILE, uiCoordBlockY );
        mVertArrayTileMap[ i + 2 ].texCoords = sf::Vector2f( uiCoordBlockX + TAILLE_TUILE, uiCoordBlockY  + TAILLE_TUILE );
        mVertArrayTileMap[ i + 3 ].texCoords = sf::Vector2f( uiCoordBlockX, uiCoordBlockY + TAILLE_TUILE ) ;

        uiCoordTabX++;

    }
    return retour;
}

/**
 * @brief Fonction renvoyant un pair contenant la position de l'angle
 * Haut-Gauche de la caméra.
 * @return les coordonnées de coin Haut-Gauche de l'écran.
 */
std::pair< float, float > MoteurGraphique::pairGetPosEcran(){
    std::pair< float, float > pairCoordEcran;
    pairCoordEcran.first = mCamera.getCenter().x -
            mCamera.getSize ().x/2 ;
    pairCoordEcran.second = mCamera.getCenter().y -
            mCamera.getSize ().y/2 ;
    return pairCoordEcran;
}

/**
 * @brief Fonction d'affichage des tuiles sur l'écran
 * à partir du tableau de niveau.
 * Une v?rification du tableau est faite au pr?allable.
 * @param tabNivEcran Le tableau 2d en provenance de Niveau.
 * @return true si le tableau envoy? est compatible false
 * sinon.
 */
/*bool bAfficherTuileEcran( const Tableau2D &tabNivEcran ){

    }*/


/**
 * @brief Fonction de défilement de l'écran.
 * Appel de la fonction correctionDeplacementCamera.
 * @param direction désigne les choix parmis les 8 directions
 * @param nombrePixel le nombre de pixel de déplacement
 */
void MoteurGraphique::deplacerEcran( unsigned char direction,
                                     float nombrePixelDeplacement ){

    float fMoveX = 0, fMoveY = 0;

    //si position ecran actuelle == la limite du niveau( coordonnées que la caméra ne doit pas dépacer )
    if( direction & HAUT )
        fMoveY = -1 * nombrePixelDeplacement;

    if( direction & DROITE )
        fMoveX = nombrePixelDeplacement;

    if( direction & GAUCHE )
        fMoveX = -1 * nombrePixelDeplacement;

    if( direction & BAS )
        fMoveY = nombrePixelDeplacement;

    correctionDeplacementCamera( fMoveX, fMoveY );
    mCamera.move( fMoveX, fMoveY );
}

/**
* @brief Fonction de vérification de similitude entre la case Haut-Gauche(caméra) courrante et en mémoire.
* @param fPositionEcranX l'abscisse de la position de l'écran
* @param fPositionEcranY l'ordonnée de la position de l'écran
* @return true si la position est la même false sinon.
*/
bool MoteurGraphique::bVerifTableauSimilaire( float fPositionEcranX, float fPositionEcranY ){
    std::pair< unsigned int, unsigned int > pairUiTmpPosEcran = mPtrMemMoteur->pairUiRetourCaseCourrante( fPositionEcranX, fPositionEcranY );
    bool bRetour = pairUiTmpPosEcran == mPositionCourranteTableauNiveau;
    if( ! bRetour ){//si position non identique
        mPositionCourranteTableauNiveau = pairUiTmpPosEcran;
    }
    return bRetour;
}

/**
 * @brief Fonction de correction de dépassement éventuel des limites
 * du niveau.
 * @param &fMoveX Le nombre de pixels abscisse dont l'écran doit se déplacer.
 * @param &fMoveY La nombre de pixels ordonnée dont l'écran doit se déplacer.
 */
void MoteurGraphique::correctionDeplacementCamera(
        float &fMoveX, float &fMoveY ){

    bool bAppliquerOp = false;
    float fMemX, fMemY;
    //coordonnées écran avant déplacement
    std::pair< float, float > pairCoordEcran = pairGetPosEcran();
    //recup nouvelle coordonnées aprés déplacement
    fMemX = pairCoordEcran.first + fMoveX;
    fMemY = pairCoordEcran.second + fMoveY;
    //pour les pair stockant des coordonnées first ==> X
    //second ==> Y

    //si la caméra dépace par la gauche
    if( fMoveX < 0 && fMemX < mPairLimiteDeplacementEcranHG.first ){
        fMemX = mPairLimiteDeplacementEcranHG.first - pairCoordEcran.first;
        //fMemX = mPairLimiteDeplacementEcranHG.first;
        fMoveX = 0.00;
        bAppliquerOp = true;
    }
    //si la caméra dépace par la droite
    else if( fMemX > mPairLimiteDeplacementEcranBD.first ){
        fMemX = mPairLimiteDeplacementEcranBD.first - pairCoordEcran.first;
        //fMemX = mPairLimiteDeplacementEcranBD.first;
        fMoveX = 0.00;
        bAppliquerOp = true;
    }

    if( bAppliquerOp ){
        mCamera.move( fMemX, 0 );
        bAppliquerOp = false;
    }

    //si la caméra dépace par le haut
    if( fMoveY < 0 && fMemY < mPairLimiteDeplacementEcranHG.second ){
        fMemY = mPairLimiteDeplacementEcranHG.second - pairCoordEcran.second;
        //fMemY = mPairLimiteDeplacementEcranHG.second;
        fMoveY = 0.00;
        bAppliquerOp = true;
    }
    //si la caméra dépace par le bas
    else if( fMemY > mPairLimiteDeplacementEcranBD.second ){
        fMemY = mPairLimiteDeplacementEcranBD.second - pairCoordEcran.second;
        //fMemY = mPairLimiteDeplacementEcranBD.second;
        fMoveY = 0.00;
        bAppliquerOp = true;
    }

    if( bAppliquerOp ){
        mCamera.move( 0, fMemY );
    }
}

/**
 * @brief Fonction de mise a jour de la limite que l'écran ne doit
 * pas dépasser.
 */
void MoteurGraphique::synchroniserNiveau(){

    std::pair< float, float > pairTmpLimBD, pairTmpLimHG;
    mPtrMemMoteur->synchroniserEcranNiveau(
                pairTmpLimHG, pairTmpLimBD );

    mPairLimiteDeplacementEcranHG = pairTmpLimHG;
    mPairLimiteDeplacementEcranBD = pairTmpLimBD;
    if( ! textureA.loadFromFile("../Plateforme-Ghouls/Ressources/DK.png"))
        std::cerr << "erreur synchroniserNiveau, chargement texture " << std::endl;
}


/**
 * @brief Destructeur de la classe MoteurGraphique
 */
MoteurGraphique::~MoteurGraphique(){

}
