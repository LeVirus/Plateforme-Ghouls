#ifndef MOTG
#define MOTG

class Moteur;
class Tableau2D;

#include <SFML/Graphics.hpp>
#include <utility>

/**
 * @class MoteurGraphique
 * @brief Classe de gestion de l'affichage.
 */
class MoteurGraphique{
    private:
        sf::RenderWindow mFenetre;
        sf::Texture textureA;
        sf::View mCamera;
        sf::VertexArray mVertArrayTileMap;
        Moteur *mPtrMemMoteur;
        std::pair< float, float > mPairLimiteDeplacementEcranHG,
        mPairLimiteDeplacementEcranBD;
    public:
        MoteurGraphique();
        void synchroniserNiveau();
        std::pair< float, float > pairGetPosEcran();
        void initialiserVertexArray();
        void initialiser( Moteur *ptrMoteur );
        void raffraichirEcran();
        void correctionDeplacementCamera( float &fMoveX,
                                          float &fMoveY );
        void deplacerEcran( unsigned char direction, float nombrePixelDeplacement = 5 );
        void positionnerTileMappingEcran();
        void deplacerVertArrayEcran( float fPosX, float fPosY );
        bool bDessinerVertArrayNiveau( const Tableau2D &tabNivEcran );
        bool bAfficherTuileEcran( const Tableau2D &tabNivEcran );
        ~MoteurGraphique();
};

#endif
