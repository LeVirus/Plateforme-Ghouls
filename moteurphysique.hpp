#ifndef MOTEURPHYSIQUE_H
#define MOTEURPHYSIQUE_H

class Moteur;

/**
 * @brief La classe MoteurPhysique Gère les intéractions avec tous les éléments physiques de la scène
 * (entités et caractéristiques de la scène).
 */
class MoteurPhysique{
private:
    Moteur *mPtrMemMoteur;
public:
    MoteurPhysique();
    void initialiser( Moteur *ptrMoteur );
    ~MoteurPhysique();
};

#endif // MOTEURPHYSIQUE_H
