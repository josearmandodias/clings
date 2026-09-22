#define CLINGS_TRACK_ALLOC
#include <string.h>
#include "clings.h"

int main(void)
{
    char *original = malloc(8);
    CHECK(original != NULL);
    strcpy(original, "abc");

    char *copie = original;
    CHECK(strcmp(copie, "abc") == 0);

    free(original);

    free(NULL);                 /* liberer NULL est inoffensif */
    CHECK_NO_LEAK();
    OK("un seul proprietaire, un seul free");
    return 0;
}
