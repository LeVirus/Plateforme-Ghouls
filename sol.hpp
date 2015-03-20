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
public:
    Sol();
    bool bEstActive()const;
    void modifierActivation( bool bActif );
    void miseAJourBoiteEnglobanteFonction();
    void ajoutPoint( float fX, float fY );
    void ajoutPoint( std::pair < float, float > & pairPointFloat );
    bool bAttribuerFonction( std::vector< std::pair < float, float > > &vectFonction );
    bool bSuprimmerPoint();
    void reinitialiserFonction();
    bool bVerifCollision(  )const;
    bool bVerifCoherencePoint( float fX )const;
    void afficherFonction()const;
    ~Sol();
};

#endif // SOL_H
