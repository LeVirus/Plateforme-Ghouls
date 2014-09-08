#include "moteurgraphique.hpp"
#include "moteur.hpp"
#include "tableau2d.hpp"
#include "constantes.hpp"
#include <iostream>

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
    mFenetre.setView( mCamera );
    mFenetre.setFramerateLimit(60);
    initialiserVertexArray();
}

/**
 * @brief Fonction de configuration du tableau de Vertex destiné à afficher le TileMApping
 */
void MoteurGraphique::initialiserVertexArray(){

    //détermination du type du tableau de vertex
    mVertArrayTileMap.setPrimitiveType ( sf::Quads );
    mVertArrayTileMap.resize ( NBR_TUILE_ECRAN_X * NBR_TUILE_ECRAN_Y * 4 );

    //initialisation de la premiere case a partir de 0,0
    mVertArrayTileMap[ 0 ].position = sf::Vector2f(0, 0);
    mVertArrayTileMap[ 1 ].position = sf::Vector2f( TAILLE_TUILE, 0 );
    mVertArrayTileMap[ 2 ].position = sf::Vector2f( TAILLE_TUILE, TAILLE_TUILE );
    mVertArrayTileMap[ 3 ].position = sf::Vector2f( 0, TAILLE_TUILE );

    //traitement de toutes les autres cases
    for( unsigned int i = 4 ; i < NBR_TUILE_ECRAN_X * NBR_TUILE_ECRAN_Y * 4 ; i += 4 ){
        mVertArrayTileMap[ i ].position = sf::Vector2f( mVertArrayTileMap[ i - 3 ].position );
        mVertArrayTileMap[ i + 1 ].position =
                sf::Vector2f( TAILLE_TUILE * ( i % NBR_TUILE_ECRAN_X + 1 ), TAILLE_TUILE * ( i / NBR_TUILE_ECRAN_X ) );
        mVertArrayTileMap[ i + 2 ].position =
                sf::Vector2f( TAILLE_TUILE * ( i % NBR_TUILE_ECRAN_X + 1 ), TAILLE_TUILE * ( i / NBR_TUILE_ECRAN_X + 1 ) );
        mVertArrayTileMap[ i + 3 ].position = sf::Vector2f( mVertArrayTileMap[ i - 2 ].position );

    }
}

/**
 * @brief Fonction d'affichage du jeu
 * Récupération du tableau de l'écran courrant.
 */
void MoteurGraphique::raffraichirEcran(){
    bool erreur = false;
    std::pair< float, float > pairCoordEcran = pairGetPosEcran();
    //std::cerr << pairCoordEcran.first << "coors ecran" << pairCoordEcran.second << std::endl;

    if( mPtrMemMoteur ){
        //recup du tableau de Niveau
        const Tableau2D &tabEcran = mPtrMemMoteur->recupTabEcran( pairCoordEcran.first, pairCoordEcran.second );
        //tabEcran.afficherTab();//affichage console

        if( ! bDessinerVertArrayNiveau( tabEcran ) ){
            std::cerr<<"Erreur bDessinerVertArrayNiveau"<<std::endl;
        erreur = true;
        }
        /*if( ! bDessinerVertArrayNiveau( tabEcran ) ){
            std::cerr<<"Erreur bDessinerVertArrayNiveau"<<std::endl;
        erreur = true;
        }*/
        if( ! erreur ){
            mFenetre.clear(sf::Color::Black);
                    mFenetre.draw(mVertArrayTileMap, &textureA);
                    mFenetre.display();
        }
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
    unsigned int uiCoordBlockX, uiCoordBlockY;//uiCoordTabX = 0, uiCoordTabY = 0;
    for(unsigned int i = 0; i < tabNivEcran.getTailleTotale() ; ++i){
        //récupération de la valeur de la case correspondante a i
        switch( tabNivEcran.getValAt( i % tabNivEcran.getLongueur(), i / tabNivEcran.getLongueur() ) ){
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

    }
    return retour;
}

/**
 * @brief Fonction renvoyant un pair contenant la position de l'angle
 * Haut-Gauche de l'écran.
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
    switch( direction ){//a modifier insérer les opérations logiques
    case HAUT:
        fMoveY = -1 * nombrePixelDeplacement;
        break;
    case DROITE:
        fMoveX = nombrePixelDeplacement;
        break;
    case GAUCHE:
        fMoveX = -1 * nombrePixelDeplacement;
        break;
    case BAS:
        fMoveY = nombrePixelDeplacement;
        break;
    }
    correctionDeplacementCamera( fMoveX, fMoveY );
    mCamera.move( fMoveX, fMoveY );
}

/**
 * @brief Fonction de correction de dépassement éventuel des limites
 * du niveau.
 * @param &fMoveX La position de l'écran abscisse aprés le déplacement
 * @param &fMoveY La position de l'écran ordonnée aprés le déplacement
 */
void MoteurGraphique::correctionDeplacementCamera(
        float &fMoveX, float &fMoveY ){

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
        fMoveX = ( mPairLimiteDeplacementEcranHG.first - pairCoordEcran.first ) * -1;
    }
    //si la caméra dépace par la droite
    else if( fMemX > mPairLimiteDeplacementEcranBD.first ){
        fMoveX = ( pairCoordEcran.first - mPairLimiteDeplacementEcranBD.first ) * -1;
    }


    //si la caméra dépace par le haut
    if( fMoveY < 0 && fMemY < mPairLimiteDeplacementEcranHG.second ){
        fMoveY = ( mPairLimiteDeplacementEcranHG.second - pairCoordEcran.second ) * -1;
    }
    //si la caméra dépace par le bas
    else if( fMemY > mPairLimiteDeplacementEcranBD.second ){
        fMoveY = ( pairCoordEcran.second - mPairLimiteDeplacementEcranBD.second ) * -1;
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
    if( ! textureA.loadFromFile("../Plateforme/Ressources/DK.png"))
        std::cerr << "erreur synchroniserNiveau, chargement texture " << std::endl;
}


/**
 * @brief Destructeur de la classe MoteurGraphique
 */
MoteurGraphique::~MoteurGraphique(){

}
