gcc -Wall main.c -c
gcc -Wall intercalacao.c -c
gcc -Wall quicksortExt.c -c
gcc main.o intercalacao.o quicksortExt.o -o exe
rm *.o
./exe 1 100 3