#ifndef SOL_H
#define SOL_H

#include <vector>
#include "vector2D.hpp"

/**
 * @brief La classe Sol est représentative d'un espace sur lequel les entités physiques terrestres peuvent
 * demeurer.
 * Cet espace est représenté par plusieurs points formant une fonction obtenue à l'aide de l'interpolation linéaire.
 */
class Sol{
    bool mbActif;
    float mMaxAbscisse, mMinAbscisse, mMaxOrdonnee, mMinOrdonnee;
    std::vector< Vector2D > mVectPointFonction;
    //mVectConstanteFonctionSegment . first ==> a :: . second ==> b ( equation fonction :: y = ax + b )
public:
    Sol();
    bool bEstActive()const;
    void modifierActivation( bool bActif );
    void miseAJourBoiteEnglobanteFonction();
    bool bAjoutPoint( float fX, float fY );
    bool bAjoutPoint( Vector2D & pairPointFloat );
    bool bAttribuerFonction( std::vector< Vector2D > &vectFonction );
    bool bSuprimmerPoint( unsigned int uiNumPoint );
    void reinitialiserFonction();

    bool bVerifCollision( float fX, float fY )const;
    bool bVerifCollisionSolBoiteEnglobante( float fX, float fY )const;

    bool bVerifCoherencePoint( const Vector2D &vect2dA )const;
    void afficherFonction()const;

    bool bCalculConstanteFonction();

    bool bCalculCohefDirectFonction();
    float fCalculCohefDirectSegment( float fAX , float fAY, float fBX , float fBY );

    float fRetourYFonction( float fX );
    float fRetourYSegment( float fX, unsigned int uiNumSegment );
    ~Sol();
};

#endif // SOL_H
