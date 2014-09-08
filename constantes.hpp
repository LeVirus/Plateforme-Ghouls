#ifndef CST
#define CST

const unsigned char HORS_TAB = 255, VAL_ERR = 254;
const unsigned char HAUT = 1, GAUCHE = 2, BAS = 4, DROITE = 8,
            HAUT_GAUCHE = HAUT + GAUCHE, HAUT_DROITE = HAUT + DROITE,
            BAS_GAUCHE = BAS + GAUCHE, BAS_DROITE = BAS + DROITE;
const unsigned int NBR_TUILE_ECRAN_X = 3, NBR_TUILE_ECRAN_Y = 3, TAILLE_TUILE = 32;
const unsigned int LARGEUR_ECRAN = 500,//NBR_TUILE_ECRAN_X * TAILLE_TUILE,
            LONGUEUR_ECRAN = 500;//NBR_TUILE_ECRAN_Y * TAILLE_TUILE;
enum{ BLOCK_A, BLOCK_B, BLOCK_C, BLOCK_D };

#endif
