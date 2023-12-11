# include <iostream>
# include <pthread.h>
# include <vector>
using namespace std;

const int size = 3;



class Matrix{
    private:
    int rows;
    int cols;
    vector<vector<int>> matrix;

    public:
    Matrix(int rows, int cols){
        this->rows = rows;
        this->cols = cols;
        this->matrix = vector<vector<int>>(rows, vector<int>(cols, 0));
    }

    void setValue(int row, int col, int value){
        matrix[row][col] = value;
    }

    int getValue(int row, int col){
        return matrix[row][col];
    }

    int getRows() const{
        return rows;
    }

    int getCols() const{
        return cols;
    }

    void init(){
        for(auto& v : matrix){
            for(auto& i : v){
                i = 0;
            }
        }
    }
};




class ThreadData{
    public:
    Matrix* A;
    Matrix* B;
    Matrix* C;
    int row;
    int col;

    ThreadData(Matrix* A, Matrix* B, Matrix* C, int row, int col){
        this->A = A;
        this->B = B;
        this->C = C;
        this->row = row;
        this->col = col;
    }
};

void* matrixAddition(void* threadData){
    ThreadData* data = static_cast<ThreadData*>(threadData);
    int row = data->row;
    for(int j=0;j<data->A->getCols();j++){
        data->C->setValue(row, j, data->A->getValue(row, j) + data->B->getValue(row, j));

    }
    pthread_exit(NULL);
    return nullptr;
}

void* matrixSubtraction(void* threadData){
    ThreadData* data = static_cast<ThreadData*>(threadData);
    int row = data->row;
    for(int j=0;j<data->A->getRows();j++){
        data->C->setValue(row, j, data->A->getValue(row, j) - data->B->getValue(row, j));

    }
    pthread_exit(NULL);
    return nullptr;
}

void* matrixMultiplication(void* threadData){
    ThreadData* data = static_cast<ThreadData*>(threadData);
    int row = data->row;
    int col = data->col;

    for(int k=0;k<data->A->getRows();k++){
        data->C->setValue(row, col, data->C->getValue(row, col) + data->A->getValue(row, k) * data->B->getValue(k, col));
    }
    pthread_exit(NULL);
    return nullptr;
}






int main(){
    

    Matrix* A = new Matrix(size, size);
    Matrix* B = new Matrix(size, size);
    Matrix* C = new Matrix(size, size);

    cout << "Enter the value of the first matrix ::" << endl;
    int value = 0;
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            cin >> value;
            A->setValue(i, j, value);
        }
    }

    cout << "Enter the value of the second matrix ::" << endl;

    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            cin >> value;
            B->setValue(i, j, value);
        }
    }

    while(true){
        cout << "Select the operation you want to perform ::" << endl;
        cout << "1. Addition" << endl;
        cout << "2. Subtraction" << endl;
        cout << "3. Multiplication" << endl;
        cout << "4. Exit" << endl;
        int option = 0;
        cin >> option;
        if(option == 1){
            pthread_t threads[size];
            ThreadData* threadData[size];

            for(int i=0;i<size;i++){
                threadData[i] = new ThreadData(A, B, C, i, 0);
                pthread_create(&threads[i], NULL, matrixAddition, static_cast<void*>(threadData[i]));
            }

            for(int i=0;i<size;i++){
                pthread_join(threads[i], NULL);
            }


            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    cout << C->getValue(i, j) << " ";
                }
                cout << endl;
            }
            C->init();
        } else if(option == 2){
            pthread_t threads[size];
            ThreadData* threadData[size];

            for(int i=0;i<size;i++){
                threadData[i] = new ThreadData(A, B, C, i, 0);
                pthread_create(&threads[i], NULL, matrixSubtraction, static_cast<void*>(threadData[i]));
            }

            for(int i=0;i<size;i++){
                pthread_join(threads[i], NULL);
            }

            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    cout << C->getValue(i, j) << " ";
                }
                cout << endl;
            }
            C->init();

        } else if(option == 3){
            pthread_t threads[size * size];
            ThreadData* threadData;

            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    threadData = new ThreadData(A, B, C, i, j);
                    pthread_create(&threads[i], NULL, matrixMultiplication, static_cast<void*>(threadData));
                }
            }

            for(int i=0;i<(size * size);i++){
                pthread_join(threads[i], NULL);
            }

            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    cout << C->getValue(i, j) << " ";
                }
                cout << endl;
            }
            C->init();

        } else if(option == 4){
            break;
        } else {
            cout << "Invalid option" << endl;
        }

    }


    
   


   

    return 0;

}