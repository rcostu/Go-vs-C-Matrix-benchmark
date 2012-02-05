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

void init_matrix (int **matrix, int fils, int cols) {
	int i, j;

	for (i = 0; i < fils; i++) {
		for (j = 0; j < cols; j++) {
			matrix[i][j] = 1;
		}
	}
}

#ifdef DEBUG
void print_matrix (int **matrix, int fils, int cols) {
	int i, j;

	for (i = 0; i < fils; i++) {
		for (j = 0; j < cols; j++) {
			printf("%d ", matrix[i][j]);
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

		// Inicialización de las matrices
		int i;

		int **matrix1 = (int **) calloc(matrix1_fils, sizeof(int*));

		for (i = 0; i < matrix1_fils; i++){
			matrix1[i] = (int *) calloc(matrix1_cols, sizeof(int));
		}

		int **matrix2 = (int **) calloc(matrix2_fils, sizeof(int*));
		for (i = 0; i < matrix2_fils; i++){
			matrix2[i] = (int *) calloc(matrix2_cols, sizeof(int));
		}

		int **matrixR = (int **) malloc(matrix1_fils * sizeof(int*));
		for (i = 0; i < matrix1_fils; i++){
			matrixR[i] = (int *) malloc(matrix2_cols * sizeof(int));
		}

		init_matrix(matrix1, matrix1_fils, matrix1_cols);
		init_matrix(matrix2, matrix2_fils, matrix2_cols);

		// Bucle principal
		int j, k, acum;

		for (j = 0; j < matrix2_cols; j++) {
			for (i = 0; i < matrix1_fils; i++) {
				acum = 0;
				for (k = 0; k < matrix1_cols; k++) {
					acum += matrix1[i][k] * matrix2[k][j];
				}
				matrixR[i][j] = acum;
			}
		}

		#ifdef DEBUG
		print_matrix(matrixR, matrix1_fils, matrix2_cols);
		#endif

		// Liberamos la memoria utilizada
		for (i = 0; i < matrix1_fils; i++) {
			free(matrix1[i]);
		}
		free(matrix1);

		for (i = 0; i < matrix2_fils; i++) {
			free(matrix2[i]);
		}
		free(matrix2);

		for (i = 0; i < matrix1_fils; i++) {
			free(matrixR[i]);
		}
		free(matrixR);

		return 0;
	}

	fprintf(stderr, "Uso: %s filas_matriz1 columnas_matriz1 columnas_matriz2\n", argv[0]);
	return -1;
}

