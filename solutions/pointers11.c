#include <string.h>
#include "clings.h"

const char *plus_longue(const char *const *mots, size_t n)
{
    if (n == 0) return NULL;

    const char *best = mots[0];
    for (size_t i = 1; i < n; i++)
        if (strlen(mots[i]) > strlen(best))
            best = mots[i];
    return best;
}

int main(void)
{
    static const char *const mots[] = {"a", "longue", "xx"};
    static const char *const exaequo[] = {"aa", "bb", "c"};

    CHECK(strcmp(plus_longue(mots, 3), "longue") == 0);
    CHECK(strcmp(plus_longue(exaequo, 3), "aa") == 0);
    CHECK(plus_longue(mots, 0) == NULL);
    OK("mot le plus long");
    return 0;
}
