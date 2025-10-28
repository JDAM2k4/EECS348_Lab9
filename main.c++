#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

// Type alias for readability
using Matrix = vector<vector<int>>;

// 1. Read matrices from file
bool readMatricesFromFile(const string& filename, Matrix& A, Matrix& B, int& N) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << filename << endl;
        return false;
    }

    file >> N;
    if (N <= 0) {
        cerr << "Error: Invalid matrix size." << endl;
        return false;
    }

    A.assign(N, vector<int>(N));
    B.assign(N, vector<int>(N));

    // Read matrix A
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            file >> A[i][j];

    // Read matrix B
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            file >> B[i][j];

    file.close();
    return true;
}

// Helper: Print matrix neatly
void printMatrix(const Matrix& M) {
    for (const auto& row : M) {
        for (int val : row)
            cout << setw(4) << val;
        cout << '\n';
    }
    cout << endl;
}

// 2. Add two matrices
Matrix addMatrices(const Matrix& A, const Matrix& B) {
    int N = A.size();
    Matrix result(N, vector<int>(N, 0));

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            result[i][j] = A[i][j] + B[i][j];

    return result;
}

// 3. Multiply two matrices
Matrix multiplyMatrices(const Matrix& A, const Matrix& B) {
    int N = A.size();
    Matrix result(N, vector<int>(N, 0));

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                result[i][j] += A[i][k] * B[k][j];

    return result;
}

// 4. Sum of diagonals (main + secondary)
void sumOfDiagonals(const Matrix& M) {
    int N = M.size();
    int mainSum = 0, secondarySum = 0;

    for (int i = 0; i < N; ++i) {
        mainSum += M[i][i];
        secondarySum += M[i][N - i - 1];
    }

    cout << "Main diagonal sum: " << mainSum << endl;
    cout << "Secondary diagonal sum: " << secondarySum << endl;
}

// 5. Swap two rows
void swapRows(Matrix& M, int r1, int r2) {
    int N = M.size();
    if (r1 >= 0 && r2 >= 0 && r1 < N && r2 < N) {
        swap(M[r1], M[r2]);
        cout << "Rows " << r1 << " and " << r2 << " swapped successfully.\n";
        printMatrix(M);
    } else {
        cout << "Invalid row indices.\n";
    }
}

// 6. Swap two columns
void swapCols(Matrix& M, int c1, int c2) {
    int N = M.size();
    if (c1 >= 0 && c2 >= 0 && c1 < N && c2 < N) {
        for (int i = 0; i < N; ++i)
            swap(M[i][c1], M[i][c2]);
        cout << "Columns " << c1 << " and " << c2 << " swapped successfully.\n";
        printMatrix(M);
    } else {
        cout << "Invalid column indices.\n";
    }
}

// 7. Update an element in the matrix
void updateMatrix(Matrix& M, int row, int col, int newVal) {
    int N = M.size();
    if (row >= 0 && col >= 0 && row < N && col < N) {
        M[row][col] = newVal;
        cout << "Updated matrix element at (" << row << "," << col << ") to " << newVal << endl;
        printMatrix(M);
    } else {
        cout << "Invalid indices.\n";
    }
}

// Main function
int main() {
    Matrix A, B;
    int N;
    string filename;

    cout << "Enter the input file name: ";
    cin >> filename;

    if (!readMatricesFromFile(filename, A, B, N)) {
        return 1;
    }

    cout << "\nMatrix A:\n";
    printMatrix(A);
    cout << "Matrix B:\n";
    printMatrix(B);

    int choice;
    do {
        cout << "\n==== Matrix Operations Menu ====\n";
        cout << "1. Add matrices (A + B)\n";
        cout << "2. Multiply matrices (A * B)\n";
        cout << "3. Sum of diagonals (Matrix A)\n";
        cout << "4. Swap rows (Matrix A)\n";
        cout << "5. Swap columns (Matrix A)\n";
        cout << "6. Update an element (Matrix A)\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1: {
                Matrix sum = addMatrices(A, B);
                cout << "Result (A + B):\n";
                printMatrix(sum);
                break;
            }
            case 2: {
                Matrix prod = multiplyMatrices(A, B);
                cout << "Result (A * B):\n";
                printMatrix(prod);
                break;
            }
            case 3:
                sumOfDiagonals(A);
                break;
            case 4: {
                int r1, r2;
                cout << "Enter two row indices to swap (0-based): ";
                cin >> r1 >> r2;
                swapRows(A, r1, r2);
                break;
            }
            case 5: {
                int c1, c2;
                cout << "Enter two column indices to swap (0-based): ";
                cin >> c1 >> c2;
                swapCols(A, c1, c2);
                break;
            }
            case 6: {
                int row, col, val;
                cout << "Enter row index, column index, and new value: ";
                cin >> row >> col >> val;
                updateMatrix(A, row, col, val);
                break;
            }
            case 0:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
