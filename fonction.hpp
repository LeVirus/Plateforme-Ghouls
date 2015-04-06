#ifndef FONCTION_H
#define FONCTION_H

#include "vector2D.hpp"

/**
 * @brief La classe FonctionAffine Représente un segment de la classe sol.
 * Elle permet d'éffectuer différents calculs liés aux fonctions.
 */
class SegmentFonction{
private:
    //constante de la fonction y = ax + b
    float mfCstFonctionA, mfCstFonctionB;
    //délimitation du segment
    Vector2D mvect2dPointA, mvect2dPointB;
public:
    SegmentFonction();
    SegmentFonction(  const Vector2D & vect2dA, const Vector2D & vect2dB  );
    bool bAttribuerPointsSegment( const Vector2D & vect2dA, const Vector2D & vect2dB );
    float fRetourYSegment( float fX );
    float fRetourCohefDirectSegment();
    bool bCalculConstanteSegment();
    ~SegmentFonction();
};

#endif // FONCTION_H
