# OS_T1_V13_Oralov

Operatsion tizimlar fani, 1-topshiriq, 13-variant.
Muallif: Oralov Fayzullo, ISE001-3 guruh

## Masala sharti

### 1-topshiriq. C tili asoslari, kompilyatsiya va pointerlar

**A qism.** "Hello World" dasturini 4 bosqichda alohida kompilyatsiya qilish (gcc -E, -S, -c, linking). Hosil bo'lgan .i, .s, .o fayllar va bajariluvchi fayl haqida qisqacha izoh berish.

**B qism, 13-variant.**

- **1-masala (C asoslari):** satrdagi so'zlar sonini va eng uzun so'zni toping.
- **2-masala (pointerlar):** `char *eng_uzun(char *s, int *uzunlik)` funksiyasini yozing. U eng uzun so'z boshiga pointer qaytarsin, so'z shu pointer orqali `printf("%.*s", uzunlik, p)` bilan chiqarilsin.

Talablar: har bir masala alohida funksiya bilan yechiladi, ma'nosiz kiritishlar xabar bilan rad etiladi, satr `fgets` bilan o'qiladi va oxiridagi `'\n'` olib tashlanadi. 2-masalada kamida bitta o'zgaruvchining manzili `%p` bilan chiqariladi. `malloc` ishlatilmaydi, satr statik massivda saqlanadi.

### 2-topshiriq. Pointerlar va dinamik xotira (malloc/free)

Funksiyaga pointer yordamida bitta saralash funksiyasiga o'sish, kamayish va modul bo'yicha tartiblash mezonlarini uzating.

Talablar: massiv o'lchami dastur ishlayotganda kiritiladi, xotira faqat dinamik ajratiladi, har bir `malloc` natijasi `NULL` ga tekshiriladi, oxirida barcha xotira bo'shatiladi va `valgrind --leak-check=full` natijasida `All heap blocks were freed -- no leaks are possible` qatori chiqadi.

## Kompilyatsiya va ishga tushirish

```bash
# 1-topshiriq, A qism
cd 1-topshiriq
gcc -E hello.c -o hello.i
gcc -S hello.i -o hello.s
gcc -c hello.s -o hello.o
gcc hello.o -o hello
./hello

# 1-topshiriq, B qism
gcc -Wall -Wextra -o main main.c
./main

# 2-topshiriq
cd ../2-topshiriq
gcc -Wall -Wextra -g -o main main.c
./main < test.txt
valgrind --leak-check=full ./main < test.txt 2> valgrind.txt
```
