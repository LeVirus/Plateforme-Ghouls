#ifndef NIV
#define NIV

#include "tableau2d.hpp"
#include <utility>

/**
 * @class Niveau
 * @brief Classe contenant toutes les informations concernant un niveau.
 * A l'initialisation du niveau un fichier texte va être lu pour charger ce dernier.
 * Elle envoi quant on lui demande les donnees des éléments à afficher au moteur.
 */
class Niveau{
    private:
        unsigned int //muiLargeurTabNiveau, muiLongueurTabNiveau,
            muiCaseDebutNiveauX, muiCaseDebutNiveauY;
        //std::vector<unsigned char> mVectTabNiveau, mVectTabEcran;
        std::pair< unsigned int, unsigned int > mPairRecept;
        Tableau2D mTabNiveau, mTabEcran;
    public:
        Niveau();
        void afficherNivEcran()const;
        const Tableau2D &retourTabEcran( const float &fPositionEcranX, const float &fPositionEcranY );
        void synchroniserEcranNiveau(
                std::pair< float, float > &pairPosEcranHG,
                std::pair< float, float > &pairPosEcranBD );
        void verifDebutNiveau();
        bool bInitialiserNiveau( unsigned int &uiChoixNiveau );
        void afficherTab()const;
        void modifCaseDebutNiveau( const unsigned int &uiPosX, const unsigned int &uiPosY );
        ~Niveau();
};

#endif
