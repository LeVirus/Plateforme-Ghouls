#include "constantes.hpp"

 const unsigned char HORS_TAB = 255;
 const unsigned char VAL_ERR = 254;
 const unsigned char HAUT = 1;
 const unsigned char GAUCHE = 2;
 const unsigned char BAS = 4;
 const unsigned char DROITE = 8;
 const unsigned char HAUT_GAUCHE = HAUT + GAUCHE;
 const unsigned char HAUT_DROITE = HAUT + DROITE;
 const unsigned char BAS_GAUCHE = BAS + GAUCHE;
 const unsigned char BAS_DROITE = BAS + DROITE;

 const unsigned int NBR_TUILE_ECRAN_X = 3;
 const unsigned int NBR_TUILE_ECRAN_Y = 3;
 const unsigned int TAILLE_TUILE = 50;
 const unsigned int NBR_TUILE_TILE_MAPPING_X = NBR_TUILE_ECRAN_X + 1;
 const unsigned int NBR_TUILE_TILE_MAPPING_Y = NBR_TUILE_ECRAN_Y + 1;
 const unsigned int LARGEUR_ECRAN = NBR_TUILE_ECRAN_X * TAILLE_TUILE;
 const unsigned int LONGUEUR_ECRAN = NBR_TUILE_ECRAN_Y * TAILLE_TUILE;
 const float ZERO_FLOAT = 0.0001f;
