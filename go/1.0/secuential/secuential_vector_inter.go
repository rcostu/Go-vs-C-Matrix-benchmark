package main

import (
	"fmt"
	"flag"
	"strconv"
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

func main () {

	flag.Parse()

	if (flag.NArg() > 2) {
		fmt.Printf("\nsecuencial_vector_inter %s %s %s\n", flag.Arg(0), flag.Arg(1), flag.Arg(2))

		matrix1_fils,_ := strconv.Atoi(flag.Arg(0))
		matrix1_cols,_ := strconv.Atoi(flag.Arg(1))
		matrix2_fils := matrix1_cols;
		matrix2_cols,_ := strconv.Atoi(flag.Arg(2))

		matrix1 := make([]int, matrix1_fils * matrix1_cols)
		matrix2 := make([]int, matrix2_fils * matrix2_cols)
		matrixR := make([]int, matrix1_fils * matrix2_cols)

		init_matrix(&matrix1, matrix1_fils, matrix1_cols)
		init_matrix(&matrix2, matrix2_fils, matrix2_cols)

		// Bucle principal
		var acum int

		for j := 0; j < matrix2_cols; j++ {
			for i := 0; i < matrix1_fils; i++ {
				acum = 0
				for k := 0; k < matrix1_cols; k++ {
					acum += matrix1[i * matrix1_cols + k] * matrix2[k * matrix2_cols + j]
				}
				matrixR[i * matrix2_cols + j] = acum
			}
		}

		//print_matrix(&matrixR, matrix1_fils, matrix2_cols)
	}
}

