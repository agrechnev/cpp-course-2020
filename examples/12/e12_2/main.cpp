// Example 12.2 CBLAS, Lapacke
// Created by Oleksiy Grechnyev, IT-JIM 2020

// Documentation : https://software.intel.com/en-us/mkl-developer-reference-c

#include <iostream>
#include <vector>

#include <cblas.h>
#include <lapacke.h>

using namespace std;

//======================================
void printVec(const double *v, int n) {
    for (int i = 0; i < n; ++i) {
        cout << v[i] << " ";
    }
}
//======================================
// Print columnwise matrix of nc columns, nr rows
void printMat(const double *m, int nr, int nc) {
    for (int ir = 0; ir < nr; ++ir) {
        for (int ic = 0; ic < nc; ++ic) {
            cout << m[ic * nr + ir] << " ";
        }
        cout << endl;
    }
}
//======================================

void demoBlas1Dot(){
    cout << "\nDot product demo : cblas_ddot !\n" << endl;

    vector<double> a{2., 3., 7., 2.}; // We can use vector
    double b[] = {1., -1., 1., -2.};  // Or array

    cout << "a = ";
    printVec(a.data(), 4);
    cout << endl;

    cout << "b = ";
    printVec(b, 4);
    cout << endl;

    // Blas always works with pointers !
    int n = 4; // Vector size
    int incx = 1, incy = 1; // Strides of x, y
    double result = cblas_ddot(n, a.data(), incx, b, incy);
    cout << "a.dot(b) = " << result << " , expected = 2" << endl;
}
//======================================

void demoBlas1Amax(){
    cout << "\nMax absolute demo : cblas_idamax !\n" << endl;

    double c[] = {1., -1., 3., 99., -17.0, 100.500, 4., -8., 21. };

    cout << "c = ";
    printVec(c, 9);
    cout << endl;

    int n = 9; // Vector size
    int incx = 1; // Stride of x
    size_t index = cblas_idamax(n, c, incx);
    cout << "index = " << index << ", expected = 5" << endl;
}

//======================================
void demoBlas2dgemv(){
    cout << "\nMatrix-vector product alpha*A*x + beta*y : cblas_dgemv !\n" << endl;

    // The matrix a, 3x2 column-wise !
    //  1 6
    //  2 5
    //  3 4
    double a[]{1, 2, 3, 6, 5, 4};
    cout << "A =" << endl;
    printMat(a, 3, 2);

    double x[]{1, -1};
    cout << "x = ";
    printVec(x, 2);
    cout << endl;

    double y[]{2, 1, -1};
    cout << "y = ";
    printVec(y, 3);
    cout << endl;

    int m = 3, n = 2; // Dimensions of A
    int incx = 1, incy = 1; // Strides of x, y
    int lda = m; // "Leading dimensions" (matrix strides) , equal to rows for column-wise
    double alpha = -1., beta = -2.;
    cout << "alpha = " << alpha << ", beta = " << beta << endl;
    cblas_dgemv(CblasColMajor, CblasNoTrans, m, n, alpha, a, lda, x, incx, beta, y, incy);

    cout << "\nresult = ";
    printVec(y, 3);
    cout << endl;
    cout << "\nexpected = 1 1 3" << endl;
}
//======================================
void demoBlas3dgemm(){
    cout << "\nMatrix-matrix product alpha*A*B + beta*C : cblas_dgemm !\n" << endl;

    // The matrix a, 3x2 column-wise !
    //  1 6
    //  2 5
    //  3 4
    double a[]{1, 2, 3, 6, 5, 4};  // 3x2
    cout << "A =" << endl;
    printMat(a, 3, 2);

    double b[]{1, -1, 2, 0, 0, 2, 1, 1};  // 2x4
    cout << "B =" << endl;
    printMat(b, 2, 4);

    double c[]{0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5}; // 3x4
    cout << "C =" << endl;
    printMat(c, 3, 4);

    int m = 3, k = 2; // Dimensions of A
    int n = 4; // Columns of B
    int lda = m, ldb = k, ldc = m; // "Leading dimensions" (matrix strides) , equal to rows for column-wise
    double alpha = 0.5, beta = 2.0;
    cout << "alpha = " << alpha << ", beta = " << beta << endl;
    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);

    cout << "\nresult =" << endl;
    printMat(c, 3, 4);

    cout << "\nexpected = \n";
    cout << "-1.5 2 7 4.5\n";
    cout << "-0.5 3 6 4.5\n";
    cout << "0.5 4 5 4.5" << endl;
}

//======================================
void demoLapackDgels() {
    int m = 3; // Number of datas
    int n = 2; // Number of funcs

    double a[3][2] = {1., 0., 1., 1., 1., 2.};
    double b[3] = {3., 10., 17.};

    int info = LAPACKE_dgels(LAPACK_ROW_MAJOR,'N',m,n,1,(double *)a,n,(double *)b,1);

    cout << "info = " << info << endl;

    for (int i = 0; i < 2; ++i) {
        cout << b[i] << " ";
    }
    cout << endl;
};
//======================================
int main () {

    cout << "\n============================================\n";
    cout << "BLAS level 1: vector-vector operations " << endl;

    demoBlas1Dot();
    demoBlas1Amax();

    cout << "\n============================================\n";
    cout << "BLAS level 2: matrix-vector operations " << endl;

    demoBlas2dgemv();

    cout << "\n============================================\n";
    cout << "BLAS level 3: matrix-matrix operations " << endl;

    demoBlas3dgemm();

    cout << "\n============================================\n";
    cout << "LAPACK: the REAL linear algebra " << endl;

    demoLapackDgels();

    return 0;
}
