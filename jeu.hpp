#ifndef JEU
#define JEU

#include "niveau.hpp"
#include "moteur.hpp"

/**
 * @class Jeu
 * @brief Classe racine du système.
 * Elle englobe directement ou non toutes les autres classes.
 * Elle établie les liens entre les différents modules.
 */
class Jeu{
    private:
        Niveau mNiveau;
        Moteur mMoteurPrincipal;
    public:
        Jeu();
        const Tableau2D &recupTabEcran( const float &fPosEcranX, const float &fPosEcranY );
        void synchroniserEcranNiveau(
                std::pair< float, float > &pairPosEcranHG ,
                std::pair< float, float > &pairPosEcranBD );
        bool lancer();
        ~Jeu();
};

#endif
