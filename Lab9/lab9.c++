#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

//opens file from user and parses, creating 2 matrices with vectors
bool getMatrices(const string &filename, vector<vector<int>> &A, vector<vector<int>> &B, int &N){
    ifstream inFile(filename);

    if (!inFile){
        cerr << "Error: could not open file " << filename << endl;
        return false;
    }

    inFile >> N;
    if (N<=0){
        cerr << "Error: Invalid size" << endl;
        return false;
    }

    A.assign(N, vector<int>(N));
    B.assign(N, vector<int>(N));

    for (int i=0; i<N; ++i)
        for (int j=0; j<N; ++j)
            inFile >> A[i][j];

    for (int i=0; i<N; ++i)
        for (int j=0; j<N; ++j)
            inFile >> B[i][j];
    inFile.close();
    return true;

}
//function to print the matrix
void printMatrix(const vector<vector<int>> &M){
    for (const auto &row : M){
        for (int val : row)
            cout << setw(5) << val;
        cout << endl;
    }
}
//iterate through each index and add the 2 matrices
void addMatrices(const vector<vector<int>> &A, const vector<vector<int>> &B){
    int N = A.size();
    vector<vector<int>> C(N, vector<int>(N,0));

    for (int i=0; i<N; ++i){
        for (int j=0; j<N; ++j){
            C[i][j]=A[i][j]+B[i][j];
        }
    }
    printMatrix(C);
}
//use multiplying matrices formula to multiply matrices
void multiplyMatrices(const vector<vector<int>> &A, const vector<vector<int>> &B){
    int N = A.size();
    vector<vector<int>> C(N, vector<int>(N,0));

    for (int i = 0; i<N; ++i){
        for (int j=0; j<N; ++j){
            int sum=0;
            for (int k=0; k<N; ++k){
                sum+=A[i][k]*B[k][j];
            }
            C[i][j]=sum;
        }
    }
    printMatrix(C);
}
//sum the primary and secondary diagonals
void sumDiagonals(const vector<vector<int>> &A){
    int primary = 0;
    int secondary = 0;
    int N = A.size();
    for (int i=0, j=0; i<N; ++i, ++j){
        primary+=A[i][j];
    }
    int j=N-1;
    for (int i=0; i<N; ++i){
        secondary+=A[i][j];
        j--;
    }
    cout << "Primary Diagonal Sum: " << primary << endl;
    cout << "Secondary Diagonal Sum: " << secondary << endl;
}
//swap row 1 and row 2 in a matrix
void swapRows(vector<vector<int>> &A, int r1, int r2){

    int N = A.size();
    vector<int> C = vector<int>(N);
    if (r1<0 || r1>=N || r2<0 || r2>=N){
        cout << "Invalid row indices" << endl;
        return;
    }
    for (int i=0; i<N; ++i){
        C[i] = A[r1][i];
        A[r1][i] = A[r2][i];
        A[r2][i]=C[i];
    }
    printMatrix(A);
}
//swap col  and col 2 in a matrix
void swapCols(vector<vector<int>> &A, int c1, int c2){

    int N = A.size();
    vector<int> C = vector<int>(N);
    if (c1<0 || c1>=N || c2<0 || c2>=N){
        cout << "Invalid col indices" <<endl;
        return;
    }
    for (int i=0; i<N; ++i){
        C[i] = A[i][c1];
        A[i][c1] = A[i][c2];
        A[i][c2] = C[i];
    }
    printMatrix(A);
}
//update a row index and col index with a value in a matrix
void updateMatrix(vector<vector<int>> &A, int row, int col, int val){
    
    if (row<0 || row>=A.size() || col<0 || col>=A.size()){
        cout << "Invalid row or column index" << endl;
        return;
    }
    A[row][col] = val;
    printMatrix(A);
}
//put everything together
int main(){
    string fname;
    cout << "Enter file name: ";
    cin >> fname;
    vector<vector<int>> A, B;
    int N;
    getMatrices(fname, A, B, N);

    while(true){
        string choice;
        cout <<"Pick an Option: \n";
        cout <<"1. Add Matrices\n";
        cout <<"2. Multiply Matrices\n";
        cout <<"3. Sum Diagonals\n";
        cout <<"4. Swap Rows\n";
        cout <<"5. Swap Columns\n";
        cout <<"6. Update Matrix\n";
        cout <<"Enter anything else to quit";
        cin >> choice;

        if (choice=="1"){
            cout << "Adding matrices...\n";
            addMatrices(A, B);
        }
        
        else if (choice=="2"){
            string decide;
            cout << "Which order? \n";
            cout << "1. A*B\n";
            cout << "2. B*A\n";
            cout << "Enter anything else to exit\n";
            cin >> decide;
            if (decide=="1"){
                cout << "Multiplying matrices...\n";
                multiplyMatrices(A, B);
            }
            else if (decide=="2"){
                cout << "Multiplying matrices...\n";
                multiplyMatrices(B,A);
            }
            cout<<"Exiting multiplication...\n";
        }
        
        else if (choice=="3"){
            string decide;
            cout <<"Which matrix?\n";
            cout << "1. A\n";
            cout << "2. B\n";
            cout << "Enter anything else to exit\n";\
            cin >> decide;
            if (decide=="1"){
                cout << "Summing Diagonals...\n";
                sumDiagonals(A);
            }
            else if (decide=="2"){
                cout << "Summing Diagonals...\n";
                sumDiagonals(B);
            }
            cout<<"Exiting summing diagonals...\n";
            
        }
        
        else if (choice=="4"){
            string decide;
            cout <<"Which matrix?\n";
            cout << "1. A\n";
            cout << "2. B\n";
            cout << "Enter anything else to exit\n";\
            cin >> decide;
            int r1;
            int r2;
            cout <<"Enter first row to be swapped: ";
            cin >>r1;
            cout <<"Enter second row to be swapped: ";
            cin >>r2;
            if (decide=="1"){
                cout << "Swapping Rows...\n";
                swapRows(A, r1, r2);
            }
            else if (decide=="2"){
                cout << "Swapping Rows...\n";
                swapRows(B, r1, r2);
            }
            cout<<"Exiting swapping rows...\n";
        }
        
        else if (choice=="5"){
            string decide;
            cout <<"Which matrix?\n";
            cout << "1. A\n";
            cout << "2. B\n";
            cout << "Enter anything else to exit\n";\
            cin >> decide;
            int c1;
            int c2;
            cout <<"Enter first column to be swapped: ";
            cin >>c1;
            cout <<"Enter second column to be swapped: ";
            cin >>c2;
            if (decide=="1"){
                cout << "Swapping Columns...\n";
                swapCols(A, c1, c2);
            }
            else if (decide=="2"){
                cout << "Swapping Columns...\n";
                swapCols(B, c1, c2);
            }
            cout<<"Exiting swapping columns...\n";
        }
        
        else if (choice=="6"){
            string decide;
            cout <<"Which matrix?\n";
            cout << "1. A\n";
            cout << "2. B\n";
            cout << "Enter anything else to exit\n";\
            cin >> decide;
            int row;
            int col;
            int val;
            cout <<"Enter row index to be updated: ";
            cin >>row;
            cout <<"Enter column index to be updated: ";
            cin >>col;
            cout <<"Enter value: ";
            cin >>val;
            if (decide=="1"){
                cout << "Swapping Columns...\n";
                updateMatrix(A, row, col, val);
            }
            else if (decide=="2"){
                cout << "Swapping Columns...\n";
                updateMatrix(B, row, col, val);
            }
            cout<<"Exiting swapping columns...\n";
        }
        
        else{
            break;
        }

    }

    return 0;
}

