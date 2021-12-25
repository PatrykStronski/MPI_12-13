#include <stdio.h>
#include <string.h>
#include "mpi.h"
int main(int argc, char **argv)
{
	int rank;
	int r = 42;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	char port_name[MPI_MAX_PORT_NAME];
	MPI_Comm intercomm;
	strcpy(port_name, argv[1]);
	MPI_Comm_connect(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	MPI_Send(&r, 1, MPI_INT, 0, 0, intercomm);
	printf("Client sent value %d\n", r);

	MPI_Recv(&r, 1, MPI_INT, 0, 0, intercomm, &status);
	printf("Client received value %d\n", r);

	MPI_Finalize();
	return 0;
}