#define CLINGS_TRACK_ALLOC
#include "clings.h"

int **creer_matrice(size_t lignes, size_t colonnes)
{
    int **m = malloc(lignes * sizeof(*m));
    if (m == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < lignes; i++) {
        m[i] = malloc(colonnes * sizeof(*m[i]));
        if (m[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(m[j]);
            }
            free(m);
            return NULL;
        }
    }
    return m;
}

void liberer_matrice(int **m, size_t lignes)
{
    if (m == NULL) {
        return;
    }
    for (size_t i = 0; i < lignes; i++) {
        free(m[i]);
    }
    free(m);
}

int main(void)
{
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
