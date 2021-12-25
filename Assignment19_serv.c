#include <stdio.h>
#include "mpi.h"
int main(int argc, char **argv)
{
	int r;
	MPI_Init(&argc, &argv);
	char port_name[MPI_MAX_PORT_NAME];
	MPI_Status status;
	MPI_Comm intercomm;
	MPI_Open_port(MPI_INFO_NULL, port_name);
	printf("\nportname: %s\n", port_name);
	MPI_Comm_accept(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);

	r = 25;
	MPI_Send(&r, 1, MPI_INT, 0, 0, intercomm);
	printf("Server sent value %d\n", r);

	MPI_Recv(&r, 1, MPI_INT, 0, 0, intercomm, &status);
	printf("Server received value %d\n", r);

	MPI_Comm_free(&intercomm);
	MPI_Close_port(port_name);

	MPI_Finalize();
	return 0;
}