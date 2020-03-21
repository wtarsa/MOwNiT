#include "aghMatrix.h"
#include <iostream>
#include <iomanip>

int main() 
{
    // initialize matrices using init value
    AGHMatrix<double> mat1(5, 5, 1.2);
    AGHMatrix<double> mat2(5, 5, 2.8);

    // Uncomment when implemented
    std::cout << "addition test" << std::endl;
    AGHMatrix<double> mat3 = mat1 + mat2;
     std::cout << mat3;

    // initialize matrix using specified values
    std::vector<std::vector<double>> init { { 1.0, 2.0, 3.0 }, 
                                            { 4.0, 5.0, 6.0 }, 
                                            { 7.0, 8.0, 9.0 } };

    AGHMatrix<double> mat4(init);
    std::cout << mat4;
    //multiplication test
    std::vector<std::vector<double>> init2 { { 9.0, 6.0 },
                                             { 3.0, 7.0 },
                                             { 2.0, 1.0 } };

    std::vector<std::vector<double>> init3 { { 1.0, 4.0, 6.0 },
                                             { 8.0, 2.0, 4.0 } };

    AGHMatrix<double> mat5(init2);
    AGHMatrix<double> mat6(init3);
    AGHMatrix<double> mat7 = mat5 * mat6;
    std::cout << "multiplication test" << std::endl;
    std::cout << mat7;

    //zadanie2
    std::vector<std::vector<double>> init4 { { 2.0, 1.0, 3.0 },
                                             { 1.0, 6.0, 7.0 },
                                             { 3.0, 7.0, 9.0 } };
    AGHMatrix<double> mat8(init4);
    std::cout << "is the matrix symmetric: ";
    std::cout << mat8.symmetric() << std::endl;

    // it's private method now
    //std::cout << "complement test: \n";
    //std::cout << mat4.complementary_cofactor(0, 0) << std::endl;

    std::vector<std::vector<double>> init5 { { 0.0, 1.0, 2.0, 7.0 },
                                             { 1.0, 2.0, 3.0, 4.0 },
                                             { 5.0, 6.0, 7.0, 8.0 },
                                             {-1.0, 1.0,-1.0, 1.0 } }; // wynik -64
    std::vector<std::vector<double>> init6 { { 5.0, 3.0, 2.0 },
                                            { 2.0,-1.0, 1.0 },
                                            { 0.0, 4.0,-1.0 } }; // wynik 7

    AGHMatrix<double> mat9(init5);
    AGHMatrix<double> mat10(init6);
    std::cout << "determinant test: \n";
    std::cout << mat9.find_determinant(mat9, mat9.get_cols()) << std::endl;
    std::cout << mat10.find_determinant(mat10, mat10.get_cols()) << std::endl;

    std::vector<std::vector<double>> init7 { { 2.0, 3.0, 1.0, 4.0 },
                                             {-1.0, 2.0, 0.0, 1.0 },
                                             { 2.0, 2.0, 0.0, 1.0 } }; // wynik -64
    AGHMatrix<double> mat11(init7);
    std::cout << mat11.transpose() << std::endl;

    //zadanie3
    std::vector<std::vector<double>> init_LU {{ 5.0, 3.0, 2.0 },
                                              { 1.0, 2.0, 0.0 },
                                              { 3.0, 0.0, 4.0 }};

    AGHMatrix<double> mat_LU(init_LU);
    AGHMatrix<double> L(mat_LU.get_rows(), mat_LU.get_cols(), 0);
    AGHMatrix<double> U(mat_LU.get_rows(), mat_LU.get_cols(), 0);
    mat_LU.LU_decomposition(L, U);
    std::cout << std::fixed;
    std::cout << std::setprecision(2) << L << std::endl;
    std::cout << std::setprecision(2) << U << std::endl;

    //zadanie4
    std::vector<std::vector<double>> init_cholesky {{ 4.0, 12.0, -16.0 },
                                                    { 12.0, 37.0, -43.0 },
                                                    { -16.0, -43.0, 98.0 }};
    AGHMatrix<double> mat_cholesky(init_cholesky);
    AGHMatrix<double> L_cholesky(mat_cholesky.get_rows(), mat_cholesky.get_cols(), 0);
    AGHMatrix<double> LT_cholesky(mat_cholesky.get_rows(), mat_cholesky.get_cols(), 0);
    mat_cholesky.cholesky_decomposition(L_cholesky, LT_cholesky);
    std::cout << std::fixed;
    std::cout << std::setprecision(2) << L_cholesky << std::endl;
    std::cout << std::setprecision(2) << LT_cholesky << std::endl;
    return 0;
}