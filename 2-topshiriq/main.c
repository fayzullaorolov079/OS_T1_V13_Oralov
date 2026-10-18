/*
 * 2-topshiriq, 13-variant
 * Funksiyaga pointer yordamida bitta saralash funksiyasiga o'sish, kamayish
 * va modul bo'yicha tartiblash mezonlarini uzatish.
 * Massiv o'lchami dastur ishlayotganda kiritiladi, xotira malloc bilan ajratiladi.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

/* ---------- Taqqoslash funksiyalari (mezonlar) ----------
   Har biri a va b ni taqqoslaydi: a b dan keyin turishi kerak bo'lsa
   musbat son, aks holda 0 yoki manfiy son qaytaradi. */

int osish(int a, int b)            /* kichigi oldinda */
{
    return a - b;
}

int kamayish(int a, int b)         /* kattasi oldinda */
{
    return b - a;
}

int modul(int a, int b)            /* ishorasiz qiymati kichigi oldinda */
{
    return abs(a) - abs(b);
}

/* Ikki elementni pointerlar orqali almashtiradi */
void almashtir(int *x, int *y)
{
    int t = *x;
    *x = *y;
    *y = t;
}

/* Bitta saralash funksiyasi (pufakcha usuli). Qaysi tartibda saralash
   taqqos parametri orqali beriladi - bu funksiyaga pointer. */
void saralash(int *a, int n, int (*taqqos)(int, int))
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (taqqos(a[j], a[j + 1]) > 0)
                almashtir(&a[j], &a[j + 1]);
}

void chiqar(const char *nom, int *a, int n)
{
    printf("%-10s:", nom);
    for (int i = 0; i < n; i++)
        printf(" %d", a[i]);
    printf("\n");
}

/* Elementlar sonini o'qiydi, natija n pointeri orqali qaytadi */
int olcham_oqi(int *n)
{
    printf("Elementlar soni (1..%d): ", MAX_N);
    if (scanf("%d", n) != 1) {
        printf("Xato: son kiritilmadi.\n");
        return 0;
    }
    if (*n < 1 || *n > MAX_N) {
        printf("Xato: elementlar soni 1 va %d oralig'ida bo'lishi kerak.\n", MAX_N);
        return 0;
    }
    return 1;
}

int main(void)
{
    int n;
    if (!olcham_oqi(&n))
        return 1;

    int *asl = malloc(n * sizeof(int));          /* kiritilgan massiv */
    if (asl == NULL) {
        printf("Xato: xotira ajratilmadi.\n");
        return 1;
    }
    int *b = malloc(n * sizeof(int));            /* saralash uchun nusxa */
    if (b == NULL) {
        printf("Xato: xotira ajratilmadi.\n");
        free(asl);
        return 1;
    }

    printf("%d ta butun son kiriting: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &asl[i]) != 1) {
            printf("Xato: faqat butun sonlar kiriting.\n");
            free(b);
            free(asl);
            return 1;
        }
    }

    /* Mezonlar jadvali: nomi va funksiyaga pointer */
    const char *nomlar[3] = { "O'sish", "Kamayish", "Modul" };
    int (*mezonlar[3])(int, int) = { osish, kamayish, modul };

    printf("\n");
    chiqar("Asl massiv", asl, n);
    for (int m = 0; m < 3; m++) {
        for (int i = 0; i < n; i++)              /* har gal asl massivdan nusxa */
            b[i] = asl[i];
        saralash(b, n, mezonlar[m]);              /* mezon pointer orqali uzatiladi */
        chiqar(nomlar[m], b, n);
    }

    printf("\nosish funksiyasi manzili: %p\n", (void *)osish);
    printf("asl massiv manzili:       %p\n", (void *)asl);

    free(b);
    free(asl);
    b = NULL;
    asl = NULL;
    printf("Xotira bo'shatildi.\n");
    return 0;
}
