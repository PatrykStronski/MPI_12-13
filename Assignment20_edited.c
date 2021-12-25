#include <stdio.h>
#include "mpi.h"
#include <string.h>


#define BUFSIZE 100
#define READ_FILE "./filenew.txt"

void save_file(char* to_write) {
	FILE *f = fopen(READ_FILE, "w");
	fputs(to_write, f);
	fclose(f);
}

int main(int argc, char **argv)
{
	int bufsize, rank, num, sum;
	char to_write[10] = "0987654321";
	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_File fh;
	char buf[BUFSIZE];
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_File_open(MPI_COMM_WORLD, READ_FILE, MPI_MODE_RDWR, MPI_INFO_NULL, &fh);
	MPI_File_set_view(fh, 0, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);
	sum = 0;
	
	if(rank == 0) {
		save_file(to_write);
	}

	MPI_Barrier(MPI_COMM_WORLD);

	do {
		MPI_File_read(fh, buf, BUFSIZE, MPI_CHAR, &status);
		MPI_Get_count(&status, MPI_CHAR, &num);
		printf("buf=%s\n", buf);
		sum += num;
	} while (num >= BUFSIZE);
	MPI_File_close(&fh);

	printf("Amount of read characters is %d\n", (int)strlen(buf));

	MPI_Barrier(MPI_COMM_WORLD);

	remove(READ_FILE);

	MPI_Finalize();
}