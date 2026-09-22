#include <ctype.h>
#include "clings.h"

size_t compter_mots(const char *s)
{
    size_t mots = 0;
    int dans_mot = 0;

    for (const char *p = s; *p != '\0'; p++) {
        if (isspace((unsigned char)*p)) {
            dans_mot = 0;
        } else if (!dans_mot) {
            dans_mot = 1;
            mots++;
        }
    }
    return mots;
}

int main(void)
{
    CHECK(compter_mots("") == 0);
    CHECK(compter_mots("   ") == 0);
    CHECK(compter_mots("un deux trois") == 3);
    CHECK(compter_mots("  un   deux ") == 2);
    CHECK(compter_mots("mot") == 1);
    OK("compter les mots");
    return 0;
}
