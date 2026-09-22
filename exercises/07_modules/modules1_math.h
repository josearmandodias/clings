/* Un header contient des DÉCLARATIONS, pas des définitions.
 *
 * Deux choses manquent ici :
 *   1. les gardes d'inclusion (#ifndef / #define / #endif), sans quoi une
 *      double inclusion redéclarerait tout ;
 *   2. les prototypes de cube() et compteur_appels().
 */

int carre(int x);
