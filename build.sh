gcc -Wall main.c -c
gcc -Wall intercalacao.c -c
gcc -Wall quicksortExt.c -c
gcc -Wall ordenaInterno.c -c
gcc main.o intercalacao.o quicksortExt.o ordenaInterno.o -lm -o exe
rm *.o
./exe 1 400 3