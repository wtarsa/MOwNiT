#pragma once
#include <vector>
#include <iostream>

template <typename T>
class AGHMatrix
{
private:
    std::vector<std::vector<T>> matrix;
    unsigned rows;
    unsigned cols;
    AGHMatrix<T> complementary_cofactor(unsigned col, unsigned row);

public:
    AGHMatrix(const std::vector<std::vector<T>>& matrix);
    AGHMatrix(unsigned _rows, unsigned _cols, const T& _initial);
    AGHMatrix(const AGHMatrix<T>& rhs);
    virtual ~AGHMatrix() = default;

    // Operator overloading, for "standard" mathematical matrix operations                                                                                                                                                          
    AGHMatrix<T>& operator=(const AGHMatrix<T>& rhs);

    // Matrix mathematical operations                                                                                                                                                                                               
    AGHMatrix<T> operator+(const AGHMatrix<T>& rhs);
    AGHMatrix<T> operator*(const AGHMatrix<T>& rhs);

    // Access the individual elements                                                                                                                                                                                               
    T& operator()(const unsigned& row, const unsigned& col);
    const T& operator()(const unsigned& row, const unsigned& col) const;
    
    // Printing matrix
    std::ostream& operator<<(const AGHMatrix<T>& matrix);

    // Access the row and column sizes                                                                                                                                                                                              
    unsigned get_rows() const;
    unsigned get_cols() const;

    // Check whether the matrix is symmetric
    bool symmetric();

    // Find determinant
    static T find_determinant(AGHMatrix<T> rhs, unsigned size);

    AGHMatrix<T> transpose();

};

#include "aghMatrix.cpp"
