#include "constantes.hpp"

 HORS_TAB = 255;
 VAL_ERR = 254;
 HAUT = 1;
 GAUCHE = 2;
 BAS = 4;
 DROITE = 8;
            HAUT_GAUCHE = HAUT + GAUCHE; HAUT_DROITE = HAUT + DROITE;
            BAS_GAUCHE = BAS + GAUCHE; BAS_DROITE = BAS + DROITE;
 NBR_TUILE_ECRAN_X = 3; NBR_TUILE_ECRAN_Y = 3; TAILLE_TUILE = 50;
            NBR_TUILE_TILE_MAPPING_X = NBR_TUILE_ECRAN_X + 1; NBR_TUILE_TILE_MAPPING_Y = NBR_TUILE_ECRAN_Y + 1;
 LARGEUR_ECRAN = NBR_TUILE_ECRAN_X * TAILLE_TUILE;
            LONGUEUR_ECRAN = NBR_TUILE_ECRAN_Y * TAILLE_TUILE;
 ZERO_FLOAT = 0.0001f;
