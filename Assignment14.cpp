#include <stdio.h>
#include "mpi.h"

#define n 1000

using namespace std;

void smod5(void *a, void *b, int *l, MPI_Datatype *type) {
	int i;
	for (i = 0; i < *l; i++)
		((int*)b)[i] = (((int*)a)[i] + ((int*)b)[i]) % 5;
}

void biggest_numb(void *a, void *b, int *l, MPI_Datatype *type) {
	for (int i = 0; i < *l; i++) {
		if (((int*)a)[i] > ((int*)b)[i]) {		
			((int*)b)[i] = ((int*)a)[i];
		}
	}
}

int main(int argc, char **argv)
{
	int rank, size, i;
	int a[n];
	int b[n];
	int m[n];
	int m_reduce;
	MPI_Init(&argc, &argv);
	MPI_Op op, max;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	for (i = 0; i < n; i++) a[i] = i + rank + 1;
	printf("process %d a[0] = %d\n", rank, a[0]);
	MPI_Op_create(&smod5, 1, &op);
	MPI_Reduce(a, b, n, MPI_INT, op , 0, MPI_COMM_WORLD);
	MPI_Op_free(&op);
	if (rank == 0) printf("b[0] = %d\n", b[0]);

	MPI_Op_create(&biggest_numb, 1, &max);
	MPI_Reduce(a, m, n, MPI_INT, max , 0, MPI_COMM_WORLD);
	MPI_Op_free(&max);
	if (rank == 0) cout<<"Max using manually created function is: "<<m[0]<<","<<m[1]<<","<<m[2]<<endl;

	MPI_Reduce(a, b, n, MPI_INT, MPI_MAX , 0, MPI_COMM_WORLD);
	if (rank == 0) cout<<"Max using MPI_MAX is: "<<b[0]<<","<<b[1]<<","<<b[2]<<endl;

	MPI_Finalize();
}