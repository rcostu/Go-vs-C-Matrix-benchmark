//
//	Práctica de Arquitecturas Multiprocesador
//	Multiplicación de matrices con OpenMP
//
//	Autor: Roberto Costumero Moreno
//	Nº Matrícula: 040268
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_matrix (int *matrix, int fils, int cols) {
	int i, j;

	for (i = 0; i < fils; i++) {
		for (j = 0; j < cols; j++) {
			matrix[i * cols + j] = 1;
		}
	}
}

#ifdef DEBUG
void print_matrix (int *matrix, int fils, int cols) {
	int i, j;

	for (i = 0; i < fils; i++) {
		for (j = 0; j < cols; j++) {
			printf("%d ", matrix[i * cols + j]);
		}
	}
}
#endif

/*
 * Función principal
 */
int main (int argc, char **argv) {

	if (argc > 3) {
		printf("\n%s %s %s %s\n", argv[0], argv[1], argv[2], argv[3]);

		int matrix1_fils = strtol(argv[1], (char **) NULL, 10);
		int matrix1_cols = strtol(argv[2], (char **) NULL, 10);
		int matrix2_fils = matrix1_cols;
		int matrix2_cols = strtol(argv[3], (char **) NULL, 10);

		int *matrix1 = (int *) calloc(matrix1_fils * matrix1_cols, sizeof(int));
		int *matrix2 = (int *) calloc(matrix2_fils * matrix2_cols, sizeof(int));
		int *matrixR = (int *) malloc(matrix1_fils * matrix2_cols * sizeof(int));

		init_matrix(matrix1, matrix1_fils, matrix1_cols);
		init_matrix(matrix2, matrix2_fils, matrix2_cols);

		// Bucle principal
		int i, j, k, acum;

		for (j = 0; j < matrix2_cols; j++) {
			for (i = 0; i < matrix1_fils; i++) {
				acum = 0;
				for (k = 0; k < matrix1_cols; k++) {
					acum += matrix1[i * matrix1_cols + k] * matrix2[k * matrix2_cols + j];
				}
				matrixR[i * matrix2_cols + j] = acum;
			}
		}

		#ifdef DEBUG
		print_matrix(matrixR, matrix1_fils, matrix2_cols);
		#endif

		// Liberamos la memoria utilizada
		free(matrix1);
		free(matrix2);
		free(matrixR);
	}

	return 0;
}

