#include <string.h>
#include "clings.h"

#define STR(x) #x
#define XSTR(x) STR(x)

#define VERSION 3

int main(void)
{
    CHECK(strcmp(STR(bonjour), "bonjour") == 0);
    CHECK(strcmp(XSTR(VERSION), "3") == 0);
    OK("stringification");
    return 0;
}
