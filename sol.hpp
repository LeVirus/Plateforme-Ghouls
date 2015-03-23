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
    std::vector< std::pair< float, float > > mVectPointFonction, mVectConstanteFonctionSegment;
    //mVectConstanteFonctionSegment . first ==> a :: . second ==> b ( equation fonction :: y = ax + b )
    std::vector< float > mVectCohefDirect;
    bool bCalculConstanteSegment( unsigned int uiNumSegment );
public:
    Sol();
    bool bEstActive()const;
    void modifierActivation( bool bActif );
    void miseAJourBoiteEnglobanteFonction();
    bool bAjoutPoint( float fX, float fY );
    bool bAjoutPoint( std::pair < float, float > & pairPointFloat );
    bool bAttribuerFonction( std::vector< std::pair < float, float > > &vectFonction );
    bool bSuprimmerPoint( unsigned int uiNumPoint );
    void reinitialiserFonction();

    bool bVerifCollision( float fX, float fY )const;
    bool bVerifCollisionSolBoiteEnglobante( float fX, float fY )const;

    bool bVerifCoherencePoint( float fX , float fY )const;
    void afficherFonction()const;

    bool bCalculConstanteFonction();

    bool bCalculCohefDirectFonction();
    float fCalculCohefDirectSegment( float fAX , float fAY, float fBX , float fBY );

    float fRetourYFonction( float fX );
    float fRetourYSegment( float fX, unsigned int uiNumSegment );
    ~Sol();
};

#endif // SOL_H
