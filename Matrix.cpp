//
// Created by Max on 26.03.2024.
//

#include "Matrix.h"

const int Matrix::maxSize = 100;

Matrix::Matrix() : matrix(nullptr), rowCount(0), colCount(0),
                   rowSize(0), colSize(0)
{}

Matrix::Matrix(int rowSize, int colSize)
        : matrix(nullptr), rowCount(0), colCount(0),
          rowSize(rowSize), colSize(colSize)
{
    if (rowSize < 0 || colSize < 0)
    {
        cerr << "Error: negative matrix size" << endl;
        this->rowSize = this->colSize = 0;
        return;
    }

    if (rowSize == 0 || colSize == 0)
    {
        this->rowSize = this->colSize = 0;
        return;
    }

    matrix = new int *[rowSize]{};
    for (int i = 0; i < rowSize; i++)
        matrix[i] = new int[colSize]{};
}

Matrix::Matrix(const Matrix &other)
        : matrix(nullptr),
          rowCount(other.rowCount), colCount(other.colCount),
          rowSize(other.rowSize), colSize(other.colSize)
{
    if (rowSize == 0 || colSize == 0)
        return;

    matrix = new int *[rowSize]{};
    for (int i = 0; i < rowCount; i++)
    {
        matrix[i] = new int[colSize]{};
        for (int j = 0; j < colCount; j++)
            matrix[i][j] = other.matrix[i][j];
    }
}

int Matrix::getRowCount() const
{
    return rowCount;
}

int Matrix::getColCount() const
{
    return colCount;
}

int Matrix::getRowSize() const
{
    return rowSize;
}

int Matrix::getColSize() const
{
    return colSize;
}

int Matrix::getMax() const
{
    if (rowCount == 0 || colCount == 0)
    {
        cerr << "Error: cannot find max in empty matrix" << endl;
        return 0;
    }

    int max = matrix[0][0];
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            if (max < matrix[i][j])
                max = matrix[i][j];

    return max;
}

int Matrix::getMin() const
{
    if (rowCount == 0 || colCount == 0)
    {
        cerr << "Error: cannot find min in empty matrix" << endl;
        return 0;
    }

    int min = matrix[0][0];
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            if (min > matrix[i][j])
                min = matrix[i][j];

    return min;
}

int Matrix::getNorm() const
{
    if (rowCount == 0 || colCount == 0)
        return 0;

    return getMax() - getMin();
}

void Matrix::setRowSize(int value)
{
    if (value > maxSize)
    {
        cerr << "Error: too large size passed" << endl;
        return;
    }
    if (value < 0)
    {
        cerr << "Error: cannot set negative size" << endl;
        return;
    }
    if (rowSize == value)
        return;

    if (value == 0)
    {
        for (int i = 0; i < rowSize; i++)
            delete[] matrix[i];
        delete[] matrix;
        matrix = nullptr;

        rowSize = colSize = rowCount = colCount = 0;
        return;
    }

    int **newMatrix = new int *[value]{};
    if (rowSize < value)
    {
        for (int i = 0; i < rowSize; i++)
            newMatrix[i] = matrix[i];
        for (int i = rowSize; i < value; i++)
            newMatrix[i] = new int[colSize]{};
    }
    else
    {
        for (int i = 0; i < value; i++)
            newMatrix[i] = matrix[i];
        for (int i = value; i < rowSize; i++)
            delete matrix[i];
    }
    delete[] matrix;

    rowSize = value;
    matrix = newMatrix;

    if (rowSize < rowCount)
        rowCount = rowSize;
}

void Matrix::setColSize(int value)
{
    if (value > maxSize)
    {
        cerr << "Error: too large size passed" << endl;
        return;
    }
    if (value < 0)
    {
        cerr << "Error: cannot set negative size" << endl;
        return;
    }
    if (colSize == value)
        return;

    if (value == 0)
    {
        for (int i = 0; i < rowSize; i++)
            delete[] matrix[i];
        delete[] matrix;
        matrix = nullptr;

        rowSize = colSize = rowCount = colCount = 0;
        return;
    }

    int minSize = (colSize < value) ? colSize : value;
    for (int i = 0; i < rowSize; i++)
    {
        int *row = new int[value]{};
        for (int j = 0; j < minSize; j++)
            row[j] = matrix[i][j];

        delete[] matrix[i];

        colSize = value;
        matrix[i] = row;
    }

    if (colSize < colCount)
        colCount = colSize;
}

void Matrix::addRow(int *row, int size)
{
    if (rowCount == maxSize)
    {
        cerr << "Error: cannot add new row, maximum size reached" << endl;
        return;
    }
    if (colCount != size)
    {
        if (colCount == 0)
        {
            colCount = size;
            if (colSize < size)
                setColSize(size);
        }
        else
        {
            cerr << "Error: passed row size is different from other rows"
                 << endl;
            return;
        }
    }

    if (rowSize == rowCount)
        setRowSize(rowSize + 1);

    for (int i = 0; i < colCount; i++)
        matrix[rowCount][i] = row[i];
    rowCount++;
}

void Matrix::addCol(int *col, int size)
{
    if (colCount == maxSize)
    {
        cerr << "Error: cannot add new column, maximum size reached" << endl;
        return;
    }
    if (rowCount != size)
    {
        if (rowCount == 0)
        {
            rowCount = size;
            if (rowSize < size)
                setRowSize(size);
        }
        else
        {
            cerr << "Error: passed col size is different from other cols"
                 << endl;
            return;
        }
    }

    if (colSize == colCount)
        setColSize(colSize + 1);

    for (int i = 0; i < rowCount; i++)
        matrix[i][colCount] = col[i];
    colCount++;
}

void Matrix::delRow()
{
    if (rowCount > 0)
        rowCount--;
}

void Matrix::delRow(int rowIndex)
{
    if (rowIndex < 0 && rowIndex >= rowCount)
    {
        cerr << "Error: row index out of range" << endl;
        return;
    }

    delete[] matrix[rowIndex];
    for (int i = rowIndex; i < rowCount; i++)
        matrix[i] = matrix[i + 1];
    matrix[rowCount] = nullptr;
    rowCount--;
}

void Matrix::delCol()
{
    if (colCount > 0)
        colCount--;
}

void Matrix::delCol(int colIndex)
{
    if (colIndex < 0 && colIndex >= rowCount)
    {
        cerr << "Error: column index out of range" << endl;
        return;
    }

    for (int i = 0; i < rowCount; i++)
        for (int j = colIndex; j < colCount - 1; j++)
            matrix[i][j] = matrix[i][j + 1];
    colCount--;
}

Matrix &Matrix::operator=(const Matrix &other)
{
    if (this == &other)
        return *this;

    for (int i = 0; i < rowCount; i++)
        delete[] matrix[i];
    delete[] matrix;
    matrix = nullptr;

    rowCount = other.rowCount;
    colCount = other.colCount;
    rowSize = other.rowSize;
    colSize = other.colSize;

    if (rowSize == 0 || colSize == 0)
        return *this;

    matrix = new int *[rowSize]{};
    for (int i = 0; i < rowSize; i++)
    {
        matrix[i] = new int[colSize]{};
        for (int j = 0; j < colCount; j++)
            matrix[i][j] = other.matrix[i][j];
    }

    return *this;
}

Matrix &Matrix::operator++()
{
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            ++matrix[i][j];

    return *this;
}

Matrix &Matrix::operator--()
{
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            --matrix[i][j];

    return *this;
}

Matrix Matrix::operator++(int)
{
    Matrix copy = *this;

    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            matrix[i][j]++;

    return copy;
}

Matrix Matrix::operator--(int)
{
    Matrix copy = *this;

    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            matrix[i][j]--;

    return copy;
}

int *Matrix::operator[](int i)
{
    if (i < 0 || i >= rowCount)
    {
        cerr << "Error: index out of range" << endl;
        return nullptr;
    }

    return matrix[i];
}

const int *Matrix::operator[](int i) const
{
    if (i < 0 || i >= rowCount)
    {
        cerr << "Error: index out of range" << endl;
        return nullptr;
    }

    return matrix[i];
}

Matrix::operator string() const
{
    stringstream sout;
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
            sout << setw(5) << matrix[i][j];

        sout << endl;
    }

    return sout.str();
}

Matrix::~Matrix()
{
    if (!matrix)
        return;

    for (int i = 0; i < rowSize; i++)
        delete[] matrix[i];
    delete[] matrix;
}

ostream &operator<<(ostream &out, const Matrix &m)
{
    out << (string) m;
    return out;
}

istream &operator>>(istream &in, Matrix &m)
{
    int rowCount, colCount;
    in >> rowCount >> colCount;
    if (rowCount > m.rowSize)
        m.setRowSize(rowCount);
    if (colCount > m.colSize)
        m.setColSize(colCount);
    m.rowCount = m.colCount = 0;

    int *row = new int[colCount]{};
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
            in >> row[j];
        m.addRow(row, colCount);
    }
    delete[] row;

    return in;
}

bool operator==(const Matrix &m1, const Matrix &m2)
{
    if (m1.rowCount != m2.rowCount || m1.colCount != m2.colCount)
    {
        cerr << "Error: cannot compare matrices with different sizes"
             << endl;
        return false;
    }

    for (int i = 0; i < m1.rowCount; i++)
        for (int j = 0; j < m1.colCount; j++)
            if (m1[i][j] != m2[i][j])
                return false;

    return true;
}

bool operator!=(const Matrix &m1, const Matrix &m2)
{
    return !(m1 == m2);
}

bool operator<(const Matrix &m1, const Matrix &m2)
{
    if (m1.rowCount != m2.rowCount || m1.colCount != m2.colCount)
    {
        cerr << "Error: cannot compare matrices with different sizes"
             << endl;
        return false;
    }

    int countLess = 0;
    for (int i = 0; i < m1.rowCount; i++)
        for (int j = 0; j < m1.colCount; j++)
            if (m1[i][j] < m2[i][j])
                countLess++;

    return countLess > m1.rowCount * m2.rowCount / 2;
}

bool operator>(const Matrix &m1, const Matrix &m2)
{
    if (m1.rowCount != m2.rowCount || m1.colCount != m2.colCount)
    {
        cerr << "Error: cannot compare matrices with different sizes"
             << endl;
        return false;
    }

    int countMore = 0;
    for (int i = 0; i < m1.rowCount; i++)
        for (int j = 0; j < m1.colCount; j++)
            if (m1[i][j] > m2[i][j])
                countMore++;

    return countMore > m1.rowCount * m2.rowCount / 2;
}

bool operator<=(const Matrix &m1, const Matrix &m2)
{
    if (m1.rowCount != m2.rowCount || m1.colCount != m2.colCount)
    {
        cerr << "Error: cannot compare matrices with different sizes"
             << endl;
        return false;
    }

    int countLessOrEqual = 0;
    for (int i = 0; i < m1.rowCount; i++)
        for (int j = 0; j < m1.colCount; j++)
            if (m1[i][j] <= m2[i][j])
                countLessOrEqual++;

    return countLessOrEqual > m1.rowCount * m2.rowCount / 2;
}

bool operator>=(const Matrix &m1, const Matrix &m2)
{
    if (m1.rowCount != m2.rowCount || m1.colCount != m2.colCount)
    {
        cerr << "Error: cannot compare matrices with different sizes"
             << endl;
        return false;
    }

    int countMoreOrEqual = 0;
    for (int i = 0; i < m1.rowCount; i++)
        for (int j = 0; j < m1.colCount; j++)
            if (m1[i][j] >= m2[i][j])
                countMoreOrEqual++;

    return countMoreOrEqual > m1.rowCount * m2.rowCount / 2;
}

Matrix operator-(const Matrix &m1, const Matrix &m2)
{
    if (m1.rowCount != m2.rowCount || m1.colCount != m2.colCount)
    {
        cerr << "Error: cannot subtract matrices with different sizes"
             << endl;
        return Matrix();
    }

    Matrix m(m1.rowCount, m1.colCount);
    int *row = new int[m1.colCount]{};
    for (int i = 0; i < m1.rowCount; i++)
    {
        for (int j = 0; j < m1.colCount; j++)
            row[j] = m1[i][j] - m2[i][j];

        m.addRow(row, m1.colCount);
    }
    delete[] row;

    return m;
}
