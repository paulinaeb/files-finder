#regla para compilar el archivo principal
main: main.c
	gcc main.c -o main -l pthread
