#define CLINGS_TRACK_ALLOC
#include <string.h>
#include "clings.h"

int main(void)
{
    char *buf = malloc(16);
    CHECK(buf != NULL);
    strcpy(buf, "salut");

    size_t n = strlen(buf);
    char premier = buf[0];

    free(buf);
    buf = NULL;

    CHECK(n == 5);
    CHECK(premier == 's');
    CHECK(buf == NULL);
    free(buf);                  /* buf vaut NULL : inoffensif */
    CHECK_NO_LEAK();
    OK("aucun acces apres liberation");
    return 0;
}
