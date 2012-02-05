package main

import (
	"fmt"
	"flag"
	"strconv"
	"runtime"
	"os"
)

func init_matrix (matrix *[]int, fils int, cols int) {
	for i := 0; i < fils; i++ {
		for j := 0; j < cols; j++ {
			(*matrix)[i * cols + j] = 1;
		}
	}
}

func print_matrix (matrix *[]int, fils int, cols int) {
	for i := 0; i < fils; i++ {
		for j := 0; j < cols; j++ {
			fmt.Printf("%d ", (*matrix)[i * cols + j]);
		}
	}
}

const NUM_THREADS = 3

var (
	matrix1 []int;
	matrix2 []int;
	matrixR []int;

	matrix1_fils int;
	matrix1_cols int;
	matrix2_fils int;
	matrix2_cols int;

	pending_jobs = 0
)

type struct_job struct {
	i int
	next *struct_job
}

var (
	job_list *struct_job = nil;
	last_job *struct_job = nil;

	ch, chm chan int
)

func add_job (i int) {
	var job *struct_job = new(struct_job);
	job.i = i
	job.next = nil

	if pending_jobs == 0 {
		job_list = job
		last_job = job
	} else {
		last_job.next = job
		last_job = job
	}

	pending_jobs++
}

func get_job () (job *struct_job) {
	if pending_jobs > 0 {
		job = job_list
		job_list = job.next
		if job_list == nil {
			last_job = nil
		}
		pending_jobs--
	} else {
		job = nil
	}

	return job
}

func do_job (job *struct_job) {
	var acum int

	for j := 0; j < matrix2_cols; j++ {
		acum = 0
		for k := 0; k < matrix1_cols; k++ {
			acum += matrix1[job.i * matrix1_cols + k] * matrix2[k * matrix2_cols + j]
		}
		matrixR[job.i * matrix2_cols + j] = acum
	}
}

func dispatch_job () {
	var job *struct_job

	for {
		if pending_jobs > 0 {
			chm <- 1
			job = get_job()
			<-chm

			do_job(job)
		} else {
			ch <- 1
			runtime.Goexit()
		}
	}
}

func main () {
	flag.Parse()

	if (flag.NArg() > 2) {
		fmt.Printf("\ngo_vector_sistema_fila %s %s %s\n", flag.Arg(0), flag.Arg(1), flag.Arg(2))

		runtime.GOMAXPROCS(NUM_THREADS)

		matrix1_fils,_ = strconv.Atoi(flag.Arg(0))
		matrix1_cols,_ = strconv.Atoi(flag.Arg(1))
		matrix2_fils = matrix1_cols;
		matrix2_cols,_ = strconv.Atoi(flag.Arg(2))

		matrix1 = make([]int, matrix1_fils * matrix1_cols)
		matrix2 = make([]int, matrix2_fils * matrix2_cols)
		matrixR = make([]int, matrix1_fils * matrix2_cols)

		init_matrix(&matrix1, matrix1_fils, matrix1_cols)
		init_matrix(&matrix2, matrix2_fils, matrix2_cols)

		// Bucle principal
		for i := 0; i < matrix1_fils; i++ {
			add_job(i);
		}

		ch = make(chan int, 1)
		chm = make(chan int, 1)

		for i := 0; i < NUM_THREADS; i++ {
			go dispatch_job();
		}

		for i := 0; i < NUM_THREADS; i++ {
			<-ch
		}

		//print_matrix(&matrixR, matrix1_fils, matrix2_cols)

		return
	}

	fmt.Fprintf(os.Stderr, "Uso: go_vector_sistema_fila filas_matriz1 columnas_matriz1 columnas matrix2\n");
	return
}

