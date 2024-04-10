//
// Created by Max on 26.03.2024.
//

#ifndef OOP_LAB_2_4_MATRIX_H
#define OOP_LAB_2_4_MATRIX_H


#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

class Matrix
{
private:
    int **matrix;
    int rowCount, colCount, rowSize, colSize;

    static const int maxSize;
public:
    Matrix();

    Matrix(int rowSize, int colSize);

    Matrix(const Matrix &other);

    int getRowCount() const;

    int getColCount() const;

    int getRowSize() const;

    int getColSize() const;

    void setRowSize(int value);

    void setColSize(int value);

    int getMax() const;

    int getMin() const;

    int getNorm() const;

    void addRow(int *row, int size);

    void addCol(int *col, int size);

    void delRow();

    void delRow(int rowIndex);

    void delCol();

    void delCol(int colIndex);

    Matrix &operator=(const Matrix &other);

    Matrix &operator++();

    Matrix &operator--();

    Matrix operator++(int);

    Matrix operator--(int);

    int *operator[](int i);

    const int *operator[](int i) const;

    operator string() const;

    ~Matrix();

    friend ostream &operator<<(ostream &out, const Matrix &m);

    friend istream &operator>>(istream &in, Matrix &m);

    friend bool operator==(const Matrix &m1, const Matrix &m2);

    friend bool operator!=(const Matrix &m1, const Matrix &m2);

    friend bool operator<(const Matrix &m1, const Matrix &m2);

    friend bool operator>(const Matrix &m1, const Matrix &m2);

    friend bool operator<=(const Matrix &m1, const Matrix &m2);

    friend bool operator>=(const Matrix &m1, const Matrix &m2);

    friend Matrix operator-(const Matrix &m1, const Matrix &m2);
};


#endif //OOP_LAB_2_4_MATRIX_H
