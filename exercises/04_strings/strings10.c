// `strchr` cherche un caractere dans une chaine et renvoie un pointeur sur sa
// premiere occurrence, ou NULL. Subtilete de la norme : chercher '\0' doit
// renvoyer un pointeur sur le terminateur (donc la fin de chaine), car le
// '\0' fait partie de la chaine.
//
// `ma_strchr` renvoie `const char *`. Complete-la.


// I AM NOT DONE

#include "clings.h"

const char *ma_strchr(const char *s, int c)
{
    /* TODO */
    (void)s;
    (void)c;
    return NULL;
}

int main(void)
{
    const char *ch = "bonjour";
    const char *vide = "";

    // ---------------------------- NE TOUCHE PAS -----------------------------
    CHECK(ma_strchr(ch, 'n') == &ch[2]);
    CHECK(ma_strchr(ch, 'z') == NULL);
    CHECK(ma_strchr(ch, '\0') == &ch[7]);   /* le terminateur */
    CHECK(ma_strchr(vide, 'a') == NULL);
    CHECK(ma_strchr(vide, '\0') == vide);
    OK("strchr a la main");
    return 0;
}
