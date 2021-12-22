#include <cstdlib>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iostream>

#define ENTITIES_NUMBER 5

using namespace std;

int ret_0(){
    return 0;
}

vector<vector<int>> gen_training_matrix(int matrix_size){
    vector<vector<int>> ret(matrix_size);
    for (int i = 0; i < matrix_size; i++) {
        vector<int> row(matrix_size);
        for (int j = 0; j < matrix_size; j++) {
            row[j] = 1;
        }
        ret[i] = row;
    }
    return ret;
}

vector<vector<int>> gen_random_matrix(int matrix_size){
    vector<vector<int>> ret(matrix_size);
    for (int i = 0; i < matrix_size; i++) {
        vector<int> row(matrix_size);
        srand(int(time(nullptr)));
        generate(row.begin(), row.end(), rand);
        ret[i] = row;
    }
    return ret;
}

vector<vector<int>> gen_empty_matrix(int matrix_size){
    vector<vector<int>> ret(matrix_size);
    for (int i = 0; i < matrix_size; i++) {
        vector<int> row(matrix_size);
        srand(int(time(nullptr)));
        generate(row.begin(), row.end(), ret_0);
        ret[i] = row;
    }
    return ret;
}

int main(int argc, char **argv)
{
	
	vector<vector<int>> mat1 = gen_training_matrix(ENTITIES_NUMBER);
    vector<vector<int>> mat2 = gen_training_matrix(ENTITIES_NUMBER);
    vector<vector<int>> res = gen_empty_matrix(ENTITIES_NUMBER);
	
	// matrix multiplication	
	for (int i = 0; i < ENTITIES_NUMBER; i++)
        for (int j = 0; j < ENTITIES_NUMBER; j++)
            for (int k = 0; k < ENTITIES_NUMBER; k++)
                res[i][j] += mat1[i][k] * mat2[k][j];

	for (int i = 0; i < ENTITIES_NUMBER; i++) {
        for (int j = 0; j < ENTITIES_NUMBER; j++) 
            cout<<res[i][j]<<',';
        cout<<endl;
    }
}