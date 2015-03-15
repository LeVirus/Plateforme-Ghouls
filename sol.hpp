#ifndef SOL_H
#define SOL_H

#include <vector>

/**
 * @brief La classe Sol est représentative d'un espace sur lequel les entités physiques terrestres peuvent
 * demeurer.
 * Cet espace est représenté par plusieurs points formant une fonction obtenue à l'aide de l'interolation linéaire.
 */
class Sol{
    float mMaxAbscisse, mMinAbscisse, mMaxOrdonnee, mMinOrdonnee;
    std::vector< float > mVectFloatFonction;
public:
    Sol();
    ~Sol();
};

#endif // SOL_H
