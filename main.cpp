#include <iostream>
#include "Matrix.h"

using namespace std;

int main()
{
    Matrix m1(20, 20), m2;

    cout << "Matrix input format:" << endl;
    cout << "rowCount colCount" << endl;
    cout << "a11 a12 ... a1n" << endl;
    cout << "a21 a22 ... a2n" << endl;
    cout << "... ... ... ..." << endl;
    cout << "am1 am2 ... amn" << endl << endl;

    cout << "Enter matrix 1 in the specified format:" << endl;
    cin >> m1;
    cout << endl;

    cout << "Enter matrix 2 in the specified format:" << endl;
    cin >> m2;
    cout << endl;

    cout << "Matrix 1:" << endl;
    cout << "row size = " << m1.getRowSize() << endl;
    cout << "row count = " << m1.getRowCount() << endl;
    cout << "col size = " << m1.getColSize() << endl;
    cout << "col count = " << m1.getColCount() << endl;
    cout << "max = " << m1.getMax() << endl;
    cout << "min = " << m1.getMin() << endl;
    cout << "norm = " << m1.getNorm() << endl << endl;

    cout << "Matrix 2:" << endl;
    cout << "row size = " << m2.getRowSize() << endl;
    cout << "row count = " << m2.getRowCount() << endl;
    cout << "col size = " << m2.getColSize() << endl;
    cout << "col count = " << m2.getColCount() << endl;
    cout << "max = " << m2.getMax() << endl;
    cout << "min = " << m2.getMin() << endl;
    cout << "norm = " << m2.getNorm() << endl << endl;

    if (m1.getRowCount() == m2.getRowCount()
        && m2.getColCount() == m2.getColCount())
    {
        if (m1 == m2)
            cout << "matrix 1 is equal to matrix 2" << endl;
        if (m1 != m2)
            cout << "matrix 1 is not equal to matrix 2" << endl;
        if (m1 < m2)
            cout << "Most elements in matrix 1 are less than in matrix 2"
                 << endl;
        if (m1 > m2)
            cout << "Most elements in matrix 1 are more than in matrix 2"
                 << endl;
        if (m1 <= m2)
            cout << "Most elements in matrix 1 are less or equal to "
                    "the elements in matrix 2" << endl;
        if (m1 >= m2)
            cout << "Most elements in matrix 1 are more or equal to "
                    "the elements in matrix 2" << endl;
        cout << endl;

        cout << "Matrix 1 - matrix 2:" << endl;
        cout << m1 - m2 << endl;
    }
    else
        cout << "Cannot compare and subtract matrices with different sizes"
             << endl << endl;

    cout << "Enter a new row to add to the matrix 1 (the same size):" << endl;
    int *row = new int[m1.getColCount()]{};
    for (int i = 0; i < m1.getColCount(); i++)
        cin >> row[i];
    m1.addRow(row, m1.getColCount());
    delete[] row;
    row = nullptr;
    cout << endl;

    int rowIndex;
    cout << "Enter row index to delete from the matrix 1: ";
    cin.get();
    cin >> rowIndex;
    m1.delRow(rowIndex);
    cout << endl;

    cout << "Enter a new col to add to the matrix 2 (the same size):" << endl;
    int *col = new int[m2.getRowCount()]{};
    for (int i = 0; i < m2.getRowCount(); i++)
        cin >> col[i];
    m2.addCol(col, m2.getRowCount());
    delete[] col;
    col = nullptr;
    cout << endl;

    int colIndex;
    cout << "Enter col index to delete from the matrix 2: ";
    cin >> colIndex;
    m2.delCol(colIndex);
    cout << endl;

    cout << "Matrix 1:" << endl;
    cout << m1 << endl;
    cout << "Matrix 2:" << endl;
    cout << m2 << endl;

    m1++;
    --m2;
    cout << "Incremented matrix 1:" << endl;
    cout << m1 << endl;
    cout << "Decremented matrix 2:" << endl;
    cout << m2 << endl;

    return 0;
}
