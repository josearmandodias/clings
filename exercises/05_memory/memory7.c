// Une matrice dynamique, c'est un tableau de pointeurs, dont chaque pointeur
// designe une ligne allouee a part : deux niveaux de malloc, donc deux niveaux
// de free.
//
// `creer_matrice` alloue `lignes` lignes de `colonnes` int et renvoie le
// tableau de pointeurs (ou NULL en cas d'echec). `liberer_matrice` libere tout.
//
// Si une allocation echoue en cours de route, libere ce qui a deja ete alloue :
// pas de fuite, meme sur le chemin d'erreur.


// I AM NOT DONE

#define CLINGS_TRACK_ALLOC
#include "clings.h"

int **creer_matrice(size_t lignes, size_t colonnes)
{
    /* TODO */
    (void)lignes;
    (void)colonnes;
    return NULL;
}

void liberer_matrice(int **m, size_t lignes)
{
    /* TODO */
    (void)m;
    (void)lignes;
}

int main(void)
{
    // ---------------------------- NE TOUCHE PAS -----------------------------
    int **m = creer_matrice(2, 3);
    CHECK(m != NULL);

    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 3; j++) {
            m[i][j] = (int)(i * 3 + j);
        }
    }
    CHECK(m[0][0] == 0);
    CHECK(m[1][2] == 5);

    liberer_matrice(m, 2);
    CHECK_NO_LEAK();
    OK("matrice dynamique");
    return 0;
}
