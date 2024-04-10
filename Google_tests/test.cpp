//
// Created by Max on 26.03.2024.
//

#include "gtest/gtest.h"
#include "../Matrix.h"

TEST(MatrixTestSuite, MatrixTest)
{
    Matrix m1(2, 3), m2(2, 3);

    int *row = new int[3]{1, 2, 3};
    m1.addRow(row, 3);
    row[0] = 4;
    row[1] = 5;
    row[2] = 6;
    m1.addRow(row, 3);
    row[0] = 7;
    row[1] = 8;
    row[2] = 9;
    m1.addRow(row, 3);

    row[0] = row[1] = row[2] = 1;
    m2.addRow(row, 3);
    m2.addRow(row, 3);
    m2.addRow(row, 3);

    delete[] row;

    Matrix m = m1 - m2;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(m[i][j], i * 3 + j);
}
