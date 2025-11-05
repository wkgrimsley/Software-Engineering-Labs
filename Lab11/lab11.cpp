#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Matrix
{
private:
    int size;
    vector<vector<int>> matrix;

public:
    Matrix(int size, vector<vector<int>> matrix){
        this->matrix = matrix;
        this->size = size;
    }
    ~Matrix(){
        //cout <<"Destructor called for object with size: "<<size<<endl; destructor check
    }
    void printMatrix(){
        for (const auto &row : this->matrix){
            for (int val : row)
                cout << setw(5) << val;
            cout << endl;
        }
    }
    void operator+(Matrix m2){
        int n = this->size;
        vector<vector<int>> resmat(n, vector<int>(n,0));
        Matrix res = Matrix (n, resmat);
        for (int i=0; i<n; ++i){
            for (int j=0; j<n; ++j){
                res.matrix[i][j] = this->matrix[i][j] + m2.matrix[i][j];
            }
        }
        res.printMatrix();
    }
    void operator*(Matrix m2){
        cout << "Multiplying Matrices: ";
        int n = this->size;
        vector<vector<int>> resmat(n, vector<int>(n,0));
        Matrix res = Matrix(n, resmat);
        for (int i=0; i<n; ++i){
            for (int j=0; j<n; ++j){
                int sum=0;
                for (int k=0; k<n; ++k){
                    sum += this->matrix[i][k] * m2.matrix[k][j];
                }
                res.matrix[i][j]=sum;
            }
        }
        
        res.printMatrix();
    }
    void sumDiagonals(){
        cout << "Summing Diagonals: ";
        int primary=0;
        int secondary=0;
        int n = this->size;
        for (int i=0, j=0; i<n; ++i, ++j){
            primary+=this->matrix[i][j];
        }
        int j=n-1;
        for (int i=0; i<n; ++i){
            secondary+=this->matrix[i][i];
            j--;
        }
        cout << "Primary Diagonal Sum: " << primary << endl;
        cout << "Secondary Diagonal Sum: " << secondary << endl;
    }

    void swapRows(int r1=0, int r2=1){
        Matrix A = Matrix(this->size, this->matrix);
        
        cout << "Swapping Rows: ";
        int n = this->size;
        vector<int> C = vector<int>(n);
        if (r1<0||r1>=n||r2<0||r2>=n){
            cout <<"Invalid row indices"<<endl;
            return;
        }
        for (int i=0; i<n; ++i){
            C[i]=A.matrix[r1][i];
            A.matrix[r1][i] = A.matrix[r2][i];
            A.matrix[r2][i]=C[i];
        }
        A.printMatrix();
    }
    void swapCols(int c1=0, int c2=1){
        Matrix A = Matrix(this->size, this->matrix);
        cout << "Swapping Columns: ";
        int n = this->size;
        vector<int> C = vector<int>(n);
        if (c1<0||c1>=n||c2<0||c2>=n){
            cout <<"Invalid column indices"<<endl;
            return;
        }
        for (int i=0; i<n; ++i){
            C[i]=A.matrix[i][c1];
            A.matrix[i][c1] = A.matrix[i][c2];
            A.matrix[i][c2]=C[i];
        }
        A.printMatrix();
    }
    void updateMatrix(int row = 0, int col = 0, int val = 100){
        if (row < 0 || row >= this->size || col < 0 || col >= this->size){
            cout << "Invalid row or column index" << endl;
            return;
        }
        this->matrix[row][col]=val;
        printMatrix();
    }

};


int main(){
    string fname;
    cout << "Enter file name: ";
    cin >> fname;
    vector<vector<int>> A, B;
    int N;
    ifstream inFile(fname);

    if (!inFile){
        cerr << "Error: could not open file " << fname << endl;
        return 0;
    }

    inFile >> N;
    if (N<=0){
        cerr << "Error: Invalid size" << endl;
        return 0;
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
    Matrix m1 = Matrix(N,A);
    Matrix m2 = Matrix(N,B);
    m1.printMatrix();
    m2.printMatrix();
    while(true){
        string choice;
        cout <<"Pick an Option: \n";
        cout <<"1. Add Matrices\n";
        cout <<"2. Multiply Matrices\n";
        cout <<"3. Sum Diagonals\n";
        cout <<"4. Swap Rows\n";
        cout <<"5. Swap Columns\n";
        cout <<"6. Update Matrix\n";
        cout <<"Enter anything else to quit: ";
        cin >> choice;

        if (choice=="1"){
            cout << "Adding matrices...\n";
            m1+m2;
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
                m1*m2;
            }
            else if (decide=="2"){
                cout << "Multiplying matrices...\n";
                m2*m1;
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
                m1.sumDiagonals();
            }
            else if (decide=="2"){
                cout << "Summing Diagonals...\n";
                m2.sumDiagonals();
            }
            cout<<"Exiting summing diagonals...\n";
            
        }
        
        else if (choice=="4"){
            string decide;
            cout <<"Which matrix?\n";
            cout << "1. A\n";
            cout << "2. B\n";
            cout << "Enter anything else to exit: \n";\
            cin >> decide;
            string def;
            cout << "Enter 1 to input your own values. Anything else to use default:  ";
            cin >> def;
            if (def=="1"){
                int r1;
                int r2;
                cout <<"Enter first row to be swapped: ";
                cin >>r1;
                cout <<"Enter second row to be swapped: ";
                cin >>r2;
                if (decide=="1"){
                    cout << "Swapping Rows...\n";
                    m1.swapRows(r1, r2);
                }
                else if (decide=="2"){
                    cout << "Swapping Rows...\n";
                    m2.swapRows(r1, r2);
                }
            }
            else{
                if (decide=="1"){
                    cout << "Swapping Rows...\n";
                    m1.swapRows();
                }
                else if (decide=="2"){
                    cout << "Swapping Rows...\n";
                    m2.swapRows();
                }
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
            string def;
            cout << "Enter 1 to input your own values. Anything else to use default:  ";
            cin >> def;
            if (def=="1"){
                int c1;
                int c2;
                cout <<"Enter first column to be swapped: ";
                cin >>c1;
                cout <<"Enter second column to be swapped: ";
                cin >>c2;
                if (decide=="1"){
                    cout << "Swapping Columns...\n";
                    m1.swapCols(c1, c2);
                }
                else if (decide=="2"){
                    cout << "Swapping Columns...\n";
                    m2.swapCols(c1, c2);
                }
            }
            else{
                if (decide=="1"){
                    cout << "Swapping Columns...\n";
                    m1.swapCols();
                }
                else if (decide=="2"){
                    cout << "Swapping Columns...\n";
                    m2.swapCols();
                }
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
            string def;
            cout << "Enter 1 to input your own values. Anything else to use default:  ";
            cin >> def;
            if (def=="1"){
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
                    cout << "Updating Matrix...\n";
                    m1.updateMatrix(row, col, val);
                }
                else if (decide=="2"){
                    cout << "Updating Matrix...\n";
                    m2.updateMatrix(row, col, val);
                }
            }
            else{
                if (decide=="1"){
                    cout << "Updating Matrix...\n";
                    m1.updateMatrix();
                }
                else if (decide=="2"){
                    cout << "Updating Matrix...\n";
                    m2.updateMatrix();
                }
            }
            cout<<"Matrix Updated...\n";
        }
        
        else{
            break;
        }

    }

    return 0;
}
