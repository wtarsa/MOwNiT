#include <cmath>
#include "aghMatrix.h"


// Parameter Constructor                                                                                                                                                      
template<typename T>
AGHMatrix<T>::AGHMatrix(const std::vector<std::vector<T>>& mat) 
{
  matrix.resize(mat.size());
  for (unsigned i = 0; i < mat.size(); i++) 
  {
    matrix[i].resize(mat[i].size());
    for(unsigned j = 0; j < mat[i].size(); j++)
    {
      matrix[i][j] = mat[i][j];
    }
  }
  rows = matrix.size();
  cols = matrix[1].size();
}

// Parameter Constructor                                                                                                                                                      
template<typename T>
AGHMatrix<T>::AGHMatrix(unsigned _rows, unsigned _cols, const T& _initial) 
{
  matrix.resize(_rows);
  for (unsigned i=0; i<matrix.size(); i++) 
  {
    matrix[i].resize(_cols, _initial);
  }
  rows = _rows;
  cols = _cols;
}

// Copy Constructor                                                                                                                                                           
template<typename T>
AGHMatrix<T>::AGHMatrix(const AGHMatrix<T>& rhs) 
{
  matrix = rhs.matrix;
  rows = rhs.get_rows();
  cols = rhs.get_cols();
}

// Get the number of rows of the matrix                                                                                                                                       
template<typename T>
unsigned AGHMatrix<T>::get_rows() const 
{
  return this->rows;
}

// Get the number of columns of the matrix                                                                                                                                    
template<typename T>
unsigned AGHMatrix<T>::get_cols() const 
{
  return this->cols;
}

// Assignment Operator                                                                                                                                                        
template<typename T>
AGHMatrix<T>& AGHMatrix<T>::operator=(const AGHMatrix<T>& rhs) 
{
  if (&rhs == this)
    return *this;

  unsigned new_rows = rhs.get_rows();
  unsigned new_cols = rhs.get_cols();

  matrix.resize(new_rows);
  for (unsigned i=0; i<matrix.size(); i++) 
  {
    matrix[i].resize(new_cols);
  }

  for (unsigned i=0; i<new_rows; i++) 
  {
    for (unsigned j=0; j<new_cols; j++) 
    {
      matrix[i][j] = rhs(i, j);
    }
  }
  rows = new_rows;
  cols = new_cols;

  return *this;
}

// Access the individual elements                                                                                                                                             
template<typename T>
T& AGHMatrix<T>::operator()(const unsigned& row, const unsigned& col) 
{
  return this->matrix[row][col];
}

// Access the individual elements (const)                                                                                                                                     
template<typename T>
const T& AGHMatrix<T>::operator()(const unsigned& row, const unsigned& col) const 
{
  return this->matrix[row][col];
}

// Addition of two matrices                                                                                                                                                   
template<typename T>
AGHMatrix<T> AGHMatrix<T>::operator+(const AGHMatrix<T>& rhs) 
{
    AGHMatrix<T> result(rhs);
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            result.matrix[r][c] += matrix[r][c];
        }
    }
    return result;
}

// Left multiplication of this matrix and another                                                                                                                              
template<typename T>
AGHMatrix<T> AGHMatrix<T>::operator*(const AGHMatrix<T>& rhs) 
{
    AGHMatrix<T> result(rows, rhs.cols, 0);
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < rhs.cols; c++){
            for(int i = 0; i < rhs.rows; i++){
                result.matrix[r][c] += matrix[r][i]*rhs.matrix[i][c];
            }
        }
    }
    return result;
}

// Check whether the matrix is symmetric
template<typename T>
bool AGHMatrix<T>::symmetric() {
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            if(matrix[r][c] != matrix[c][r]) return false;
        }
    }
    return true;
}

// Find complementary cofactor of matrix
template<typename T>
AGHMatrix<T> AGHMatrix<T>::complementary_cofactor(unsigned col, unsigned row) {
    AGHMatrix<T> result(this->rows-1, this->cols-1, 0);
    int r_shift = 0;
    int c_shift = 0;
    for(int r = 0; r < this->rows-1; r++){
        if(r == row) r_shift = 1;
        for(int c = 0; c < this->cols-1; c++){
            if(c == col) c_shift = 1;
            result.matrix[r][c] = this->matrix[r+r_shift][c+c_shift];
        }
        c_shift = 0;
    }
    return result;
}

// Find determinant of matrix using Laplace expansion
template<typename T>
T AGHMatrix<T>::find_determinant(AGHMatrix<T> rhs, unsigned size) {
    T result = 0;
    if(size == 1) return rhs.matrix[0][0];
    if(size == 2) {
        return rhs.matrix[0][0]*rhs.matrix[1][1]-
               rhs.matrix[0][1]*rhs.matrix[1][0];
    }
    for(int col = 0; col < size; col++){
        result += pow(-1, col+2) * rhs.matrix[0][col] * find_determinant(rhs.complementary_cofactor(col, 0), size-1);
    }
    return result;
}

template<typename T>
AGHMatrix<T> AGHMatrix<T>::transpose() {
    AGHMatrix<T> result(cols, rows, 0);
    for(int r = 0; r < cols; r++){
        for(int c = 0; c < rows; c++){
            result.matrix[r][c] = matrix[c][r];
        }
    }
    return result;
}

template<typename T>
void AGHMatrix<T>::LU_decomposition(AGHMatrix<T> &L, AGHMatrix<T> &U) {
    for(int i = 0; i < rows; i++){
        L.matrix[i][i] = 1;
    }
    for(int i = rows; i > 0; i--){ // for each row and column
        for(int c = cols-i; c < cols; c++){ // row in U matrix
            U.matrix[rows-i][c] = 1;
            double tmp = 0;
            for(int j = 0; j < cols; j++){ // multiplication
                if(j == rows-i) U.matrix[rows-i][c] *= U.matrix[j][c];
                else tmp += L.matrix[rows-i][j]*U.matrix[j][c];
            }
            U.matrix[rows-i][c] = (matrix[rows-i][c]-tmp)/U.matrix[rows-i][c];
        }

        for(int r = rows-i; r < rows; r++){ // col in L matrix
            L.matrix[r][cols-i] = 1;
            double tmp = 0;
            for(int j = 0; j < cols; j++){ // multiplication
                if(j == cols-i) L.matrix[r][cols-i] *= U.matrix[j][cols-i];
                else tmp += L.matrix[r][j]*U.matrix[j][cols-i];
            }
            L.matrix[r][cols-i] = (matrix[r][cols-i]-tmp)/L.matrix[r][cols-i];
        }
    }
}

template<typename T>
void AGHMatrix<T>::cholesky_decomposition(AGHMatrix<T> &L, AGHMatrix<T> &LT) {
    for(int i = 0; i < rows; i++){
        for(int j = 0; j <= i; j++){
            double tmp = 0;
            if(i == j){
                for(int k = 0; k < j; k++){
                    tmp += pow(L.matrix[j][k], 2);
                }
                L.matrix[j][j] = sqrt(matrix[j][i] - tmp);
            }
            else{
                for(int k = 0; k < j; k++){
                    tmp += (L.matrix[i][k]*L.matrix[j][k]);
                }
                L.matrix[i][j] = (matrix[i][j] - tmp)/L.matrix[j][j];
            }
        }
    }
    LT = L.transpose();
}

template<typename T>
AGHMatrix<T> AGHMatrix<T>::gauss_elimination() {
    AGHMatrix result(rows, 1, 0);
    for (int i = 0; i < rows; i++) {                    //Pivotisation
        for (int k = i + 1; k < rows; k++) {
            if (abs(matrix[i][i]) < abs(matrix[k][i])) {
                for (int j = 0; j <= rows; j++) {
                    double temp = matrix[i][j];
                    matrix[i][j] = matrix[k][j];
                    matrix[k][j] = temp;
                }
            }
        }
    }

    for (int i = 0; i < rows - 1; i++) {            
        for (int k = i + 1; k < rows; k++) {
            double t = matrix[k][i] / matrix[i][i];
            for (int j = 0; j <= rows; j++)
                matrix[k][j] = matrix[k][j] - t*matrix[i][j];
        }
    }

    for (int i = rows-1;i>=0;i--){
        result.matrix[i][0]=matrix[i][rows];
        for (int j=i+1;j<rows;j++) {
            if (j != i) result.matrix[i][0] = result.matrix[i][0] - matrix[i][j] *result.matrix[j][0];
        }
        result.matrix[i][0]=result.matrix[i][0]/matrix[i][i];
    }

}


// Printing matrix                                                                                                                        
template<typename T>
std::ostream& operator<<(std::ostream& stream, const AGHMatrix<T>& matrix) 
{
  for (int i=0; i<matrix.get_rows(); i++) 
  { 
    for (int j=0; j<matrix.get_cols(); j++) 
    {
        stream << matrix(i,j) << ", ";
    }
    stream << std::endl;
  }
    stream << std::endl;
}

