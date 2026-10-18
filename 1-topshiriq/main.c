/*
 * 1-topshiriq, 13-variant
 * 1-masala: satrdagi so'zlar sonini va eng uzun so'zni topish (indekslar bilan).
 * 2-masala: char *eng_uzun(char *s, int *uzunlik) - eng uzun so'z boshiga
 *           pointer qaytaradi, uzunlik pointer orqali qaytadi; so'z shu pointer
 *           orqali printf("%.*s", uzunlik, p) bilan chiqariladi.
 * malloc ishlatilmaydi: satr statik massivda saqlanadi.
 */
#include <stdio.h>
#include <string.h>

#define MAX 100

/* Belgi bo'shliqmi (probel yoki tab)? */
int bosh_joymi(char c)
{
    return c == ' ' || c == '\t';
}

/* ===================== 1-masala ===================== */

/* So'zlar sonini sanaydi. So'z boshi: bo'shliq bo'lmagan belgi,
   undan oldin esa bo'shliq yoki satr boshi turibdi. */
int sozlar_soni(char s[])
{
    int soni = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (!bosh_joymi(s[i]) && (i == 0 || bosh_joymi(s[i - 1])))
            soni++;
    }
    return soni;
}

/* Eng uzun so'zni indekslar bilan topadi. Eng uzun so'z boshining
   indeksini qaytaradi, uzunligini esa max_uz pointeri orqali beradi. */
int eng_uzun_indeks(char s[], int *max_uz)
{
    int i = 0, bosh = 0;
    *max_uz = 0;

    while (s[i] != '\0') {
        while (bosh_joymi(s[i]))          /* bo'shliqlarni o'tkazib yuborish */
            i++;
        int boshi = i, uz = 0;
        while (s[i] != '\0' && !bosh_joymi(s[i])) {   /* so'z uzunligini sanash */
            uz++;
            i++;
        }
        if (uz > *max_uz) {               /* yangi eng uzun so'z */
            *max_uz = uz;
            bosh = boshi;
        }
    }
    return bosh;
}

/* ===================== 2-masala ===================== */

/* Xuddi shu ish, lekin faqat pointerlar bilan.
   Eng uzun so'z boshiga pointer qaytaradi, uzunlikni *uzunlik ga yozadi. */
char *eng_uzun(char *s, int *uzunlik)
{
    char *p = s;            /* satr bo'ylab yuradigan pointer */
    char *eng = s;          /* eng uzun so'z boshi */
    *uzunlik = 0;

    while (*p != '\0') {
        while (bosh_joymi(*p))
            p++;
        char *boshi = p;    /* joriy so'z boshi */
        while (*p != '\0' && !bosh_joymi(*p))
            p++;
        int uz = (int)(p - boshi);        /* pointerlar ayirmasi = so'z uzunligi */
        if (uz > *uzunlik) {
            *uzunlik = uz;
            eng = boshi;
        }
    }
    return eng;
}

int main(void)
{
    char s[MAX];

    /* --- Kiritish va tekshirish --- */
    printf("Satr kiriting (ko'pi bilan %d belgi): ", MAX - 2);
    if (fgets(s, MAX, stdin) == NULL) {
        printf("Xato: satr kiritilmadi.\n");
        return 1;
    }
    char *yangi_qator = strchr(s, '\n');
    if (yangi_qator == NULL) {
        printf("Xato: satr juda uzun.\n");
        return 1;
    }
    *yangi_qator = '\0';                  /* oxiridagi '\n' ni olib tashlash */

    int soni = sozlar_soni(s);
    if (soni == 0) {
        printf("Xato: satrda birorta ham so'z yo'q.\n");
        return 1;
    }

    /* --- 1-masala --- */
    int max_uz;
    int bosh = eng_uzun_indeks(s, &max_uz);
    printf("\n1-masala (indekslar bilan):\n");
    printf("  So'zlar soni: %d\n", soni);
    printf("  Eng uzun so'z: ");
    for (int i = bosh; i < bosh + max_uz; i++)
        putchar(s[i]);
    printf(" (%d ta harf, indeks %d dan boshlanadi)\n", max_uz, bosh);

    /* --- 2-masala --- */
    int uzunlik;
    char *p = eng_uzun(s, &uzunlik);
    printf("\n2-masala (pointerlar bilan):\n");
    printf("  Eng uzun so'z: %.*s (%d ta harf)\n", uzunlik, p, uzunlik);
    printf("  satr boshi:    s = %p\n", (void *)s);
    printf("  so'z boshi:    p = %p\n", (void *)p);
    printf("  p - s = %d (so'z satrning shu indeksidan boshlanadi)\n", (int)(p - s));
    printf("  uzunlik o'zgaruvchisi manzili: %p\n", (void *)&uzunlik);
    return 0;
}
