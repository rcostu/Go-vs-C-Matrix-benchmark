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
#include <pthread.h>

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

#define NUM_THREADS 3

// Variables de las matrices
int *matrix1;
int *matrix2;
int *matrixR;

// Variables del número de filas y columnas
int matrix1_fils;
int matrix1_cols;
int matrix2_fils;
int matrix2_cols;

// Lista de threads iniciados
pthread_t *thread_list;

// Variables para controlar la exclusión mutua
pthread_mutex_t mutex;

// Número de peticiones pendietnes
int pending_jobs = 0;

// Estructura del trabajo a realizar
struct job {
	int i;
	struct job *next;
};

// Lista enlazada de peticiones de trabajos.
struct job *job_list = NULL;
struct job *last_job = NULL;

void add_job(int i){
	// Inicializamos la petición que se va a añadir
	struct job *job = malloc(sizeof(struct job));
	job->i = i;
	job->next = NULL;

	// Si no hay peticiones pendientes, la añadimos a la lista y la marcamos como última.
	if(pending_jobs == 0){
		job_list = job;
		last_job = job;
	}
	else{
		// Si hay peticiones pendientes, se añade tras la última y actualizamos que la nueva es la última.
		last_job->next = job;
		last_job = job;
	}

	// Aumentamos el número de peticiones pendientes.
	pending_jobs++;
}

// Función para que los thread puedan coger la primera petición pendiente de la lista.
struct job* get_job(){
	struct job *job = NULL;

	// Si el número de peticiones pendientes es mayor que 0, entonces cogemos la primera petición y es la que devolvemos al thread.
	if(pending_jobs > 0){
		job = job_list;
		job_list = job->next;
		if(job_list == NULL){
			last_job = NULL;
		}
		pending_jobs--;
	}

	// Retornamos la petición calculada anteriormente
	return job;
}

void do_job(struct job *job) {
	int j, k, acum;

	for (j = 0; j < matrix2_cols; j++) {
		acum = 0;
		for (k = 0; k < matrix1_cols; k++) {
			acum += matrix1[job->i * matrix1_cols + k] * matrix2[k * matrix2_cols + j];
		}
		matrixR[job->i * matrix2_cols + j] = acum;
	}
}

void* dispatch_job () {

	struct job *job;

	while(1) {
		pthread_mutex_lock(&mutex);
		job = get_job();
		pthread_mutex_unlock(&mutex);

		if (job) {
			do_job(job);
			free(job);
		}
		else {
			pthread_exit(NULL);
		}
	}
}

/*
 * Función principal
 */
int main (int argc, char **argv) {

	if (argc > 3) {
		printf("\n%s %s %s %s\n", argv[0], argv[1], argv[2], argv[3]);

		matrix1_fils = strtol(argv[1], (char **) NULL, 10);
		matrix1_cols = strtol(argv[2], (char **) NULL, 10);
		matrix2_fils = matrix1_cols;
		matrix2_cols = strtol(argv[3], (char **) NULL, 10);

		// Inicialización de las matrices
		int i;

		matrix1 = (int *) calloc(matrix1_fils * matrix1_cols, sizeof(int));
		matrix2 = (int *) calloc(matrix2_fils * matrix2_cols, sizeof(int));
		matrixR = (int *) malloc(matrix1_fils * matrix2_cols * sizeof(int));

		init_matrix(matrix1, matrix1_fils, matrix1_cols);
		init_matrix(matrix2, matrix2_fils, matrix2_cols);

		// Bucle principal
		for (i = 0; i < matrix1_fils; i++) {
			add_job(i);
		}

		thread_list = malloc(sizeof(int) * NUM_THREADS);
		pthread_mutex_init(&mutex, NULL);

		pthread_attr_t attr;

		pthread_attr_init(&attr);
		pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

		for (i = 0; i < NUM_THREADS; i++) {
			pthread_create(&thread_list[i], &attr, dispatch_job, NULL);
		}

		for (i = 0; i < NUM_THREADS; i++) {
			pthread_join(thread_list[i], NULL);
		}

		#ifdef DEBUG
		print_matrix(matrixR, matrix1_fils, matrix2_cols);
		#endif

		pthread_attr_destroy(&attr);
		pthread_mutex_destroy(&mutex);

		free(thread_list);

		// Liberamos la memoria utilizada
		free(matrix1);
		free(matrix2);
		free(matrixR);

		return 0;
	}

	fprintf(stderr, "Uso: %s filas_matriz1 columnas_matriz1 columnas_matriz2\n", argv[0]);
	return -1;
}

