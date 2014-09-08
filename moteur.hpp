#ifndef MOT
#define MOT

class Jeu;

#include "moteurgraphique.hpp"
#include "tableau2d.hpp"
#include <utility>

/**
 * @class Moteur
 * @brief Classe contenant tous les modules du moteur.
 * Elle assure la gestion de tous ces modules.
 */
class Moteur{
    private:
        MoteurGraphique mMoteurG;
        Jeu *mPtrMemJeu;
    public:
        Moteur();
        const Tableau2D &recupTabEcran( const float &fPosEcranX, const float &fPosEcranY );
        void synchroniserEcranNiveau(
                std::pair< float, float > &pairPosEcranHG ,
                std::pair< float, float > &pairPosEcranBD );
        void initialiserMoteur( Jeu *ptrJeu );
        void lancer();
        ~Moteur();
};

#endif
