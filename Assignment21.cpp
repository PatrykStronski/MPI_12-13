#include <stdio.h>
#include "mpi.h"
#include <fstream>
#include<iostream>

#define READ_FILE "fiel21.txt"
#define STR_SIZE 100

using namespace std;

char* generate_random_str(int size) {
	srand(0);
	char* s = new char[size];
	for (int i = 0; i < size-1; i++) {
		s[i] = (char) (65 + rand() % 26);
	}
	return s;
}

int main(int argc, char **argv)
{
	char* to_write = generate_random_str(STR_SIZE);

	ofstream myfile;
  	myfile.open (READ_FILE);
  	myfile << to_write;
  	myfile.close();

	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_File fh;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int batch_size = STR_SIZE/size;
	char *buf = new char[batch_size+1];

	MPI_File_open(MPI_COMM_WORLD, READ_FILE, MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
	MPI_File_set_view(fh, rank * batch_size, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);
	MPI_File_read_all(fh, buf, batch_size, MPI_CHAR, MPI_STATUS_IGNORE);
	
	buf[batch_size] = '\0';
	
	printf("process %d, buf=%s\n", rank, buf);
	MPI_File_close(&fh);
	delete buf;
	MPI_Finalize();
}