#include "mpi.h"
#include <iostream>
#include <string>

using namespace std;

void print_status(int rank, float* a, char* b) {
	cout<<" For rank "<<rank<<" a is ["<<a[0]<<","<<a[1]<<","<<a[2]<<","<<a[3]<<","<<a[4]<<","<<a[5]<<","<<a[6]<<","<<a[7]<<","<<a[8]<<","<<a[9]<<"] and b is ["<<
	b[0]<<","<<b[1]<<","<<b[2]<<","<<b[3]<<","<<b[4]<<","<<b[5]<<","<<b[6]<<","<<b[7]<<","<<b[8]<<","<<b[9]<<"]"<<endl;
}

int main(int argc, char **argv)
{
	int size, rank, position, i;
	float a[10];
	char b[10], buf[100];
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	for (i = 0; i < 10; i++) {
		a[i] = rank + 1.0;
		if (rank == 0) b[i] = 'a';
		else b[i] = 'b';
	}
	print_status(rank, a, b);
	position = 0;
	if (rank == 0) {
		MPI_Pack(a, 10, MPI_FLOAT, buf, 100, &position, MPI_COMM_WORLD);
		MPI_Pack(b, 10, MPI_CHAR, buf, 100, &position, MPI_COMM_WORLD);
		MPI_Bcast(buf, 100, MPI_PACKED, 0, MPI_COMM_WORLD);
	}
	else {
		MPI_Bcast(buf, 100, MPI_PACKED, 0, MPI_COMM_WORLD);
		position = 0;
		MPI_Unpack(buf, 100, &position, a, 10, MPI_FLOAT, MPI_COMM_WORLD);
		MPI_Unpack(buf, 100, &position, b, 10, MPI_CHAR, MPI_COMM_WORLD);
	}
	print_status(rank, a, b);
	MPI_Finalize();
}