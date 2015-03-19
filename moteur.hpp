#ifndef MOT
#define MOT

class Jeu;

#include "moteurgraphique.hpp"
#include "moteurphysique.hpp"
#include "tableau2d.hpp"
#include "engine.hpp"
//#include "jeu.hpp"
#include <utility>

/**
 * @class Moteur
 * @brief Classe contenant tous les modules du moteur.
 * Elle assure la gestion de tous ces modules.
 */
class Moteur{
    private:
        MoteurGraphique mMoteurG;
        MoteurGraphique mMoteurPhysique;
        Jeu *mPtrMemJeu;
        Engine mECSEngine;
    public:
        Moteur();
        Engine & getECSEngine();
        MoteurGraphique & getMoteurGraphique();
        const Tableau2D &recupTabEcran( const float &fPosEcranX, const float &fPosEcranY );
        void synchroniserEcranNiveau( std::pair< float, float > &pairPosEcranHG, std::pair< float, float > &pairPosEcranBD );
        void initialiserMoteur( Jeu *ptrJeu );
        void lancer();
        void chargerEntitesTest();
        const std::pair< unsigned int, unsigned int > &pairUiRetourCaseCourrante( float fPositionEcranX,  float fPositionEcranY );
        ~Moteur();
};

#endif
