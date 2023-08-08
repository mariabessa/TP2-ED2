gcc -Wall main.c -c
gcc -Wall intercalacao.c -c
gcc -Wall quicksortExt.c -c
gcc -Wall ordenaInterno.c -c
gcc -Wall intercalaSub.c -c
gcc -Wall conversorFita.c -c
gcc main.o intercalacao.o quicksortExt.o ordenaInterno.o intercalaSub.o conversorFita.o -lm -o exe
rm *.o
./exe 2 1000 3