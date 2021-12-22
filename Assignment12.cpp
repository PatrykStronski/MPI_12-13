#include <stdio.h>
#include "mpi.h"

using namespace std;

int main(int argc, char **argv) {
	srand(0);
	MPI_Init(&argc, &argv);
	int size, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status stats[4];
	MPI_Request reqs[4];

	int prev = rank - 1;
	int next = rank + 1;
	float rbuf[2];
	float sbuf[2];
	
	if (rank == 0) prev = size - 1;
	if (rank == size - 1) next = 0;
	
	MPI_Recv_init(&rbuf[0], 1, MPI_FLOAT, prev, 5, MPI_COMM_WORLD, &reqs[0]);
	MPI_Recv_init(&rbuf[1], 1, MPI_FLOAT, next, 6, MPI_COMM_WORLD, &reqs[1]);
	MPI_Send_init(&sbuf[0], 1, MPI_FLOAT, prev, 6, MPI_COMM_WORLD, &reqs[2]);
	MPI_Send_init(&sbuf[1], 1, MPI_FLOAT, next, 5, MPI_COMM_WORLD, &reqs[3]);
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			sbuf[j] = (i +1) * 100;
			rbuf[j] = 0;
		} 
		MPI_Startall(4, reqs);
		MPI_Waitall(4, reqs, stats);
		cout<<"Receive buffer is: "<<rbuf[0]<<","<<rbuf[1]<<" for rank "<<rank << " and iteration "<<i<<endl;
	}

	MPI_Request_free(&reqs[0]);
	MPI_Request_free(&reqs[1]);
	MPI_Request_free(&reqs[2]);
	MPI_Request_free(&reqs[3]);

	MPI_Finalize();
}