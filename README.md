# OS_T1_V13_Oralov

Operatsion tizimlar fanidan topshiriq, 13-variant.
Muallif: Oralov Fayzullo, ISE001-3 guruh

## Tuzilma

```
1-topshiriq/   C asoslari, kompilyatsiya bosqichlari, pointerlar
2-topshiriq/   Funksiyaga pointer va dinamik xotira (malloc/free)
```

## 1-topshiriq

### A qism: kompilyatsiya bosqichlari

```bash
cd 1-topshiriq
gcc -E hello.c -o hello.i   # preprotsessor
gcc -S hello.i -o hello.s   # kompilyator (assembler kodi)
gcc -c hello.s -o hello.o   # assembler (obyekt fayl)
gcc hello.o -o hello        # linker (bajariluvchi fayl)
./hello
```

### B qism: satrdagi so'zlar soni va eng uzun so'z

- 1-masala: so'zlar soni va eng uzun so'z (indekslar bilan)
- 2-masala: `char *eng_uzun(char *s, int *uzunlik)` eng uzun so'z boshiga pointer qaytaradi, so'z `printf("%.*s", uzunlik, p)` bilan chiqariladi

```bash
cd 1-topshiriq
gcc -Wall -Wextra -o main main.c
./main
```

## 2-topshiriq: funksiyaga pointer orqali saralash

Bitta `saralash()` funksiyasiga o'sish, kamayish va modul bo'yicha mezonlar funksiyaga pointer sifatida uzatiladi.

```bash
cd 2-topshiriq
gcc -Wall -Wextra -g -o main main.c
./main
./main < test.txt
```

Valgrind:

```bash
valgrind --leak-check=full ./main < test.txt 2> valgrind.txt
```
