// Constantinescu Delia-Georgiana
// Grupa 313 CA
// Tema 2 PCLP

#include <stdio.h>
#include <stdlib.h>
#define MOD 10007

int mod(int nr)
{	if (nr < 0)
		return nr % MOD + MOD;
	else
		return nr % MOD;
}

//reading the matrix from stdin
int **matrix(int *lines, int *columns)
{
	// reading the dimensions from stdin
	scanf("%d%d", lines, columns);
	//allocating memory and defensive programming
	int **mat = (int **)malloc((*lines) * sizeof(int *));
	if (!mat) {
		printf("Could not allocate memory\n");
		exit(-1);
	}
	for (int i = 0; i < *lines; i++) {
		mat[i] = (int *)malloc((*columns) * sizeof(int));
		if (!mat[i]) {
			printf("Could not allocate memory\n");
			for (int j = 0; j < i; j++)
				free(mat[j]);
			exit(-1);
		}
	}
	// reading the matrix
	for (int i = 0; i < *lines; i++)
		for (int j = 0; j < *columns; j++)
			scanf("%d", &mat[i][j]);
	return mat;
}

// loading a matrix
void load(int ****t, int *k, int **lines, int **columns)
{
	// allocating memory and defensive programming
	if (*k == 0) {
		*t = (int ***)malloc(sizeof(int **));
			if (!*t) {
				printf("Could not allocate memory\n");
				exit(-1);
			}
		*lines = (int *)malloc(sizeof(int));
		if (!*lines) {
			printf("Could not allocate memory\n");
			exit(-1);
		}
		*columns = (int *)malloc(sizeof(int));
		if (!*columns) {
			printf("Could not allocate memory\n");
			exit(-1);
		}
	} else {
		*t = (int ***)realloc(*t, (*k + 1) * sizeof(int **));
		if (!*t) {
			printf("Could not allocate memory\n");
			exit(-1);
		}
		*lines = (int *)realloc(*lines, (*k + 1) * sizeof(int));
		if (!*lines) {
			printf("Could not allocate memory\n");
			exit(-1);
		}
		*columns = (int *)realloc(*columns, (*k + 1) * sizeof(int));
		if (!*columns) {
			printf("Could not allocate memory\n");
			exit(-1);
		}
	}
	//using function matrix() to read a matrix
	(*t)[*k] = matrix(&(*lines)[*k], &(*columns)[*k]);
	(*k)++;
}

// determining the matrix's dimensions
void determine(int *k, int **lines, int **columns)
{
	int index;
	scanf("%d", &index);
	if (index < 0 || index >= *k)
		printf("No matrix with the given index\n");
	else
		printf("%d %d\n", (*lines)[index], (*columns)[index]);
}

// printing the matrix to stdo
void print_matrix(int ****t, int *k, int **lines, int **columns)
{
	int index;
	scanf("%d", &index);
	if (index < 0 || index >= *k) {
		printf("No matrix with the given index\n");
	} else {
		for (int i = 0; i < (*lines)[index]; i++) {
			for (int j = 0; j < (*columns)[index]; j++)
				printf("%d ", (*t)[index][i][j]);
			printf("\n");
		}
	}
}

// cropping the matrix
void crop(int ****t, int *k, int **lines, int **columns)
{
	int index;
	scanf("%d", &index);
	if (index < 0 || index >= *k) {
		printf("No matrix with the given index\n");
	} else {
		int *coords_l, *coords_c;
		int l, c;
		// reading the cropping coordinates and allocating memory
		scanf("%d", &l);
		coords_l = (int *)malloc(l * sizeof(int));
		if (!coords_l) {
			printf("Could not allocate memory\n");
			exit(-1);
		}
		for (int i = 0; i < l; i++)
			scanf("%d", &coords_l[i]);
		scanf("%d", &c);
		coords_c = (int *)malloc(c * sizeof(int));
		if (!coords_c) {
			printf("Could not allocate memory\n");
			exit(-1);
		}
		for (int i = 0; i < c; i++)
			scanf("%d", &coords_c[i]);
		// cropping the matrix using an auxiliary variable
		int **aux;
		aux = (int **)malloc(l * sizeof(int *));
		if (!aux) {
			printf("Could not allocate memory\n");
			exit(-1);
		}
		for (int i = 0; i < l; i++) {
			aux[i] = (int *)malloc(c * sizeof(int));
			if (!aux[i]) {
				printf("Could not allocate memory\n");
				for (int j = 0; j < i; j++)
					free(aux[j]);
				exit(-1);
			}
		}
		//printf("%d\n", aux[0][0]);
		for (int i = 0; i < l; i++)
			for (int j = 0; j < c; j++)
				aux[i][j] = (*t)[index][coords_l[i]][coords_c[j]];
		for (int i = l; i < (*lines)[index]; i++)
			free((*t)[index][i]);
		for (int i = 0; i < l; i++)
			(*t)[index][i] = (int *)realloc((*t)[index][i], c * sizeof(int));
		for (int i = 0; i < l; i++)
			for (int j = 0; j < c; j++)
				(*t)[index][i][j] = aux[i][j];
		(*lines)[index] = l;
		(*columns)[index] = c;
		for (int i = 0; i < l; i++)
			free(aux[i]);
		free(aux);
		free(coords_l);
		free(coords_c);
	}
}

// multiplying 2 matrices
void multiply(int ****t, int *k, int **lines, int **columns)
{
	int index1, index2;
	scanf("%d%d", &index1, &index2);
	if (index1 >= *k || index1 < 0 || index2 >= *k || index2 < 0) {
		printf("No matrix with the given index\n");
	} else {
		if ((*columns)[index1] != (*lines)[index2]) {
			printf("Cannot perform matrix multiplication\n");
		} else {
			// allocating memory and defensive programming
			int **result;
			result = (int **)malloc((*lines)[index1] * sizeof(int *));
			if (!result) {
				printf("Could not allocate memory\n");
				exit(-1);
			}
			for (int i = 0; i < (*lines)[index1]; i++) {
				result[i] = (int *)malloc((*columns)[index2] * sizeof(int));
				if (!result[i]) {
					printf("Could not allocate memory\n");
					for (int j = 0; j < i; j++)
						free(result[j]);
					exit(-1);
				}
			}
			// matrix multiplication
			for (int i = 0; i < (*lines)[index1]; i++) {
				for (int j = 0; j < (*columns)[index2]; j++) {
					result[i][j] = 0;
					for (int x = 0; x < (*columns)[index1]; x++) {
						int tmp = 0;
						tmp += mod((*t)[index1][i][x]);
						tmp *= mod((*t)[index2][x][j]);
						tmp = mod(tmp);
						result[i][j] += tmp;
						result[i][j] = mod(result[i][j]);
					}
					result[i][j] = mod(result[i][j]);
				}
			}
			// reallocating memory and loading the result
			*t = (int ***)realloc(*t, (*k + 1) * sizeof(int **));
			if (!*t) {
				printf("Could not allocate memory\n");
				exit(-1);
			}
			*lines = (int *)realloc(*lines, (*k + 1) * sizeof(int));
			if (!*lines) {
				printf("Could not allocate memory\n");
				exit(-1);
			}
			*columns = (int *)realloc(*columns, (*k + 1) * sizeof(int));
			if (!*columns) {
				printf("Could not allocate memory\n");
				exit(-1);
			}
			(*t)[*k] = result;
			(*lines)[*k] = (*lines)[index1];
			(*columns)[*k] = (*columns)[index2];
			(*k)++;
		}
	}
}

// calculating the sum of the elements of a given matrix
int sum(int **mat, int n, int m)
{
	int s = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			s = mod(s);
			s += mod(mat[i][j]);
			s = mod(s);
		}
	return mod(s);
}

// sorting the matrices according to their element sums
void sort(int ****t, int *k, int **lines, int **columns)
{
	for (int i = 0; i < *k - 1; i++) {
		for (int j = i + 1; j < *k; j++) {
			int x = sum((*t)[i], (*lines)[i], (*columns)[i]);
			int y = sum((*t)[j], (*lines)[j], (*columns)[j]);
			if (x > y) {
				int **aux = (*t)[i];
				(*t)[i] = (*t)[j];
				(*t)[j] = aux;
				int aux_lines = (*lines)[i];
				(*lines)[i] = (*lines)[j];
				(*lines)[j] = aux_lines;
				int aux_columns = (*columns)[i];
				(*columns)[i] = (*columns)[j];
				(*columns)[j] = aux_columns;
			}
		}
	}
}

//tansposing a matrix
void transpose(int ****t, int *k, int **lines, int **columns)
{
	int index;
	scanf("%d", &index);
	if (index < 0 || index >= *k) {
		printf("No matrix with the given index\n");
	} else {
		int **transp;
		// allocating memory
		transp = (int **)malloc((*columns)[index] * sizeof(int *));
		if (!transp) {
			printf("Could not allocate memory\n");
			exit(-1);
		}
		for (int i = 0; i < (*columns)[index]; i++) {
			transp[i] = (int *)malloc((*lines)[index] * sizeof(int));
			if (!transp[i]) {
				printf("Could not allocate memory\n");
				for (int j = 0; j < i; j++)
					free(transp[j]);
				exit(-1);
			}
		}
		// transposing the matrix
		for (int i = 0; i < (*lines)[index]; i++)
			for (int j = 0; j < (*columns)[index]; j++)
				transp[j][i] = (*t)[index][i][j];
		for (int i = 0; i < (*lines)[index]; i++)
			free((*t)[index][i]);
		free((*t)[index]);
		(*t)[index] = transp;
		int aux = (*lines)[index];
		(*lines)[index] = (*columns)[index];
		(*columns)[index] = aux;
	}
}

// freeing a matrix from the memory
void free_mat(int ****t, int *k, int **lines, int **columns)
{	int index;
	scanf("%d", &index);
	if (index < 0 || index >= *k) {
		printf("No matrix with the given index\n");
	} else {
		//moving each matrix to the left
		for (int i = index; i < *k - 1; i++) {
			int **aux = (*t)[i];
			(*t)[i] = (*t)[i + 1];
			(*t)[i + 1] = aux;
			int aux2 = (*lines)[i];
			(*lines)[i] = (*lines)[i + 1];
			(*lines)[i + 1] = aux2;
			int aux3 = (*columns)[i];
			(*columns)[i] = (*columns)[i + 1];
			(*columns)[i + 1] = aux3;
		}
	//reallocating the memory
		for (int i = 0; i < (*lines)[*k - 1]; i++)
			free((*t)[*k - 1][i]);
		free((*t)[*k - 1]);
		(*k)--;
		*lines = (int *)realloc(*lines, *k * sizeof(int));
		*columns = (int *)realloc(*columns, *k * sizeof(int));
		if (!*t) {
			printf("Could not allocate memory\n");
			for (int j = 0; j < *k - 1; j++)
				free(t[j]);
			exit(-1);
		}
	}
}

//freeing all resources
void quit(int ****t, int *k, int **lines, int **columns)
{
	for (int i = 0; i < *k; i++) {
		for (int j = 0; j < (*lines)[i]; j++)
			free((*t)[i][j]);
		free((*t)[i]);
	}
	free(*t);
	free(*lines);
	free(*columns);
}

int main(void)
{
	char code;
	int ***t, *lines, *columns, k = 0;
	scanf("%c", &code);
	while (code != 'Q') {
		switch (code) {
		case 'L':
			load(&t, &k, &lines, &columns);
			break;
		case 'D':
			determine(&k, &lines, &columns);
			break;
		case 'P':
			print_matrix(&t, &k, &lines, &columns);
			break;
		case 'C':
			crop(&t, &k, &lines, &columns);
			break;
		case 'M':
			multiply(&t, &k, &lines, &columns);
			break;
		case 'O':
			sort(&t, &k, &lines, &columns);
			break;
		case 'T':
			transpose(&t, &k, &lines, &columns);
			break;
		case 'F':
			if (k == 1) {
				quit(&t, &k, &lines, &columns);
				k--;
			} else {
				free_mat(&t, &k, &lines, &columns);
			}
			break;
		default:
			printf("Unrecognized command\n");
			break;
		}
		scanf("%c", &code);
		while (code < 'A' || code > 'Z')
			scanf("%c", &code);
	}
	if (k > 0)
		quit(&t, &k, &lines, &columns);
	return 0;
}
