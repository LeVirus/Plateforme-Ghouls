#ifndef SOL_H
#define SOL_H

#include <vector>

/**
 * @brief La classe Sol est représentative d'un espace sur lequel les entités physiques terrestres peuvent
 * demeurer.
 * Cet espace est représenté par plusieurs points formant une fonction obtenue à l'aide de l'interolation linéaire.
 */
class Sol{
    bool mbActif;
    float mMaxAbscisse, mMinAbscisse, mMaxOrdonnee, mMinOrdonnee;
    std::vector< std::pair< float, float > > mVectPointFonction;
    std::vector< float > mVectCohefDirect;
public:
    Sol();
    bool bEstActive()const;
    void modifierActivation( bool bActif );
    void miseAJourBoiteEnglobanteFonction();
    bool ajoutPoint( float fX, float fY );
    bool ajoutPoint( std::pair < float, float > & pairPointFloat );
    bool bAttribuerFonction( std::vector< std::pair < float, float > > &vectFonction );
    bool bSuprimmerPoint( unsigned int uiNumPoint );
    void reinitialiserFonction();

    bool bVerifCollision( float fX, float fY )const;
    bool bVerifCollisionSolBoiteEnglobante( float fX, float fY )const;

    bool bVerifCoherencePoint( float fX , float fY )const;
    void afficherFonction()const;
    bool calculCohefDirectFonction();
    float calculCohefDirectSegment( float fAX , float fAY, float fBX , float fBY );

    ~Sol();
};

#endif // SOL_H
