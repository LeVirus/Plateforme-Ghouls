#ifndef MOTG
#define MOTG

class Moteur;
class Tableau2D;

#include <SFML/Graphics.hpp>
#include <utility>
#include <memory>

struct DisplayComponent;
struct PositionComponent;

/**
 * @class MoteurGraphique
 * @brief Classe de gestion de l'affichage.
 */
class MoteurGraphique{
    private:
        sf::RenderWindow mFenetre;
        sf::Texture textureA, textureNiveau;
        std::vector< std::unique_ptr< sf::Sprite > > mVectSprite;
        sf::View mCamera;
        sf::VertexArray mVertArrayTileMap;
        Moteur *mPtrMemMoteur;
        std::pair< float, float > mPairLimiteDeplacementEcranHG,
        mPairLimiteDeplacementEcranBD;
        std::pair< unsigned int, unsigned int > mPositionCourranteTableauNiveau;
        const std::vector< std::pair< DisplayComponent *, PositionComponent * > > * mVectComponentDisplaySystem;
    public:
        MoteurGraphique();
        void synchroniserNiveau();
        std::pair< float, float > pairGetPosEcran();
        void initialiserVertexArray();
        void initialiser( Moteur *ptrMoteur );
        void initialiserNiveau( unsigned int uiNumNiveau );
        void raffraichirEcran();
        void correctionDeplacementCamera( float &fMoveX, float &fMoveY );
        void deplacerEcran( unsigned char direction, float nombrePixelDeplacement = 5 );
        void positionnerTileMappingEcran();
        void dessinerSpriteECS();
        void deplacerVertArrayEcran( float fPosX, float fPosY );
        bool bDessinerVertArrayNiveau( const Tableau2D &tabNivEcran );
        bool bAfficherTuileEcran( const Tableau2D &tabNivEcran );
        bool bVerifTableauSimilaire( float fPositionEcranX, float fPositionEcranY );
        ~MoteurGraphique();
};

#endif
