#ifndef TAB2
#define TAB2

#include <vector>
#include <utility>

/**
 * @ class Tableau2D
 * Classe représentative d'un tableau 2 dimensions
 * Est composé d'un vector unidimentionnel
 */
class Tableau2D{
    private:
        std::vector< unsigned char > mVectChar;
        std::pair< int, int > mPairCase;
        unsigned int muiLongueurTab, muiLargeurTab;
    public:
        Tableau2D();
        Tableau2D( const unsigned int &longueur,
                   const unsigned int &largeur );

         std::pair< unsigned int, unsigned int > getCoordCase( const float &fPositionEcranX, const float &fPositionEcranY,
                                                               const unsigned int &uiCaseDebutNivX,const unsigned int &uiCaseDebutNivY );

        bool bAttribuerTab( const std::vector< unsigned char > &vect, unsigned int uiLongueurTab, unsigned int uiLargeurTab );

        const unsigned char &getValAt( const unsigned int &uiCaseX, const unsigned int &uiCaseY )const;

        bool bRecupPortionTab( const Tableau2D &tab, const unsigned int &uiCaseHautGaucheX, const unsigned int &uiCaseHautGaucheY );

        const std::vector< unsigned char > &getTab()const;
        void resize( const unsigned int &longueur, const unsigned int &largeur );

        inline const unsigned int &getLongueur()const{return muiLongueurTab;}
        inline const unsigned int &getLargeur()const{return muiLargeurTab;}
        inline unsigned int getTailleTotale()const{return muiLongueurTab * muiLargeurTab;}

        void afficherTab()const;
        ~Tableau2D();
};

#endif
