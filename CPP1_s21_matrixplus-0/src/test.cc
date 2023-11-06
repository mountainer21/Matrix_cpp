#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(S21Matrix, ConstructorDefault) {
  S21Matrix m;
  EXPECT_EQ(m.GetRows(), 0);
  EXPECT_EQ(m.GetCols(), 0);
  EXPECT_EQ(m.GetMatrix(), nullptr);
}

TEST(S21Matrix, ConstructorRowsCols) {
  S21Matrix m(2, 3);
  EXPECT_EQ(m.GetRows(), 2);
  EXPECT_EQ(m.GetCols(), 3);
  EXPECT_NE(m.GetMatrix(), nullptr);
}

TEST(S21Matrix, ConstructorCopy) {
  S21Matrix m1(2, 3);
  m1.SetValue(0, 0, 1.0);
  S21Matrix m2(m1);
  EXPECT_EQ(m2.GetRows(), 2);
  EXPECT_EQ(m2.GetCols(), 3);
  EXPECT_NE(m2.GetMatrix(), nullptr);
  EXPECT_EQ(m2.GetValue(0, 0), 1.0);
}

TEST(S21Matrix, ConstructorMove) {
  S21Matrix m1(2, 3);
  m1.SetValue(0, 0, 1.0);
  S21Matrix m2(std::move(m1));
  EXPECT_EQ(m2.GetRows(), 2);
  EXPECT_EQ(m2.GetCols(), 3);
  EXPECT_NE(m2.GetMatrix(), nullptr);
  EXPECT_EQ(m2.GetValue(0, 0), 1.0);
  EXPECT_EQ(m1.GetRows(), 0);
  EXPECT_EQ(m1.GetCols(), 0);
  EXPECT_EQ(m1.GetMatrix(), nullptr);
}

TEST(S21MatrixTest, DefaultConstructorTest) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.GetRows(), 0);
  EXPECT_EQ(matrix.GetCols(), 0);
  EXPECT_EQ(matrix.GetMatrix(), nullptr);
}

TEST(MatrixConstructorTest, CreateObjectWithValidParameters) {
  S21Matrix matrix(3, 3);
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 3);
}

TEST(MatrixConstructorTest, CreateObjectWithNegativeRows) {
  ASSERT_ANY_THROW(S21Matrix matrix(-1, 3));
}

TEST(MatrixConstructorTest, CreateObjectWithNegativeCols) {
  ASSERT_ANY_THROW(S21Matrix matrix(3, -1));
}

TEST(MatrixConstructorTest, CreateObjectWithZeroRows) {
  ASSERT_ANY_THROW(S21Matrix matrix(0, 3));
}

TEST(MatrixConstructorTest, CreateObjectWithZeroCols) {
  ASSERT_ANY_THROW(S21Matrix matrix(3, 0));
}

TEST(S21MatrixTest, MoveConstructorTest) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 1;
  mat1(0, 1) = 2;
  mat1(1, 0) = 3;
  mat1(1, 1) = 4;
  S21Matrix mat2(std::move(mat1));
  ASSERT_EQ(mat2.GetRows(), 2);
  ASSERT_EQ(mat2.GetCols(), 2);
  ASSERT_EQ(mat2(0, 0), 1);
  ASSERT_EQ(mat2(0, 1), 2);
  ASSERT_EQ(mat2(1, 0), 3);
  ASSERT_EQ(mat2(1, 1), 4);
  ASSERT_EQ(mat1.GetRows(), 0);
  ASSERT_EQ(mat1.GetCols(), 0);
  ASSERT_EQ(mat1.GetMatrix(), nullptr);

  S21Matrix mat3(3, 3);
  mat3(0, 0) = 1;
  mat3(0, 1) = 0;
  mat3(0, 2) = 2;
  mat3(1, 0) = -1;
  mat3(1, 1) = 3;
  mat3(1, 2) = 1;
  mat3(2, 0) = 2;
  mat3(2, 1) = -1;
  mat3(2, 2) = 0;
  S21Matrix mat4(std::move(mat3));
  ASSERT_EQ(mat4.GetRows(), 3);
  ASSERT_EQ(mat4.GetCols(), 3);
  ASSERT_EQ(mat4(0, 0), 1);
  ASSERT_EQ(mat4(0, 1), 0);
  ASSERT_EQ(mat4(0, 2), 2);
  ASSERT_EQ(mat4(1, 0), -1);
  ASSERT_EQ(mat4(1, 1), 3);
  ASSERT_EQ(mat4(1, 2), 1);
  ASSERT_EQ(mat4(2, 0), 2);
  ASSERT_EQ(mat4(2, 1), -1);
  ASSERT_EQ(mat4(2, 2), 0);
  ASSERT_EQ(mat3.GetRows(), 0);
  ASSERT_EQ(mat3.GetCols(), 0);
  ASSERT_EQ(mat3.GetMatrix(), nullptr);
}

TEST(S21MatrixTest, CopyConstructorTest) {
  S21Matrix mat1(2, 2);
  mat1.GetMatrix()[0][0] = 1;
  mat1.GetMatrix()[0][1] = 2;
  mat1.GetMatrix()[1][0] = 3;
  mat1.GetMatrix()[1][1] = 4;
  S21Matrix mat2(mat1);
  ASSERT_EQ(mat2.GetRows(), 2);
  ASSERT_EQ(mat2.GetCols(), 2);
  ASSERT_EQ(mat2.GetMatrix()[0][0], 1);
  ASSERT_EQ(mat2.GetMatrix()[0][1], 2);
  ASSERT_EQ(mat2.GetMatrix()[1][0], 3);
  ASSERT_EQ(mat2.GetMatrix()[1][1], 4);
  ASSERT_NE(mat1.GetMatrix(), mat2.GetMatrix());

  S21Matrix mat3(3, 3);
  mat3.GetMatrix()[0][0] = 1;
  mat3.GetMatrix()[0][1] = 0;
  mat3.GetMatrix()[0][2] = 2;
  mat3.GetMatrix()[1][0] = -1;
  mat3.GetMatrix()[1][1] = 3;
  mat3.GetMatrix()[1][2] = 1;
  mat3.GetMatrix()[2][0] = 2;
  mat3.GetMatrix()[2][1] = -1;
  mat3.GetMatrix()[2][2] = 0;
  S21Matrix mat4(mat3);
  ASSERT_EQ(mat4.GetRows(), 3);
  ASSERT_EQ(mat4.GetCols(), 3);
  ASSERT_EQ(mat4.GetMatrix()[0][0], 1);
  ASSERT_EQ(mat4.GetMatrix()[0][1], 0);
  ASSERT_EQ(mat4.GetMatrix()[0][2], 2);
  ASSERT_EQ(mat4.GetMatrix()[1][0], -1);
  ASSERT_EQ(mat4.GetMatrix()[1][1], 3);
  ASSERT_EQ(mat4.GetMatrix()[1][2], 1);
  ASSERT_EQ(mat4.GetMatrix()[2][0], 2);
  ASSERT_EQ(mat4.GetMatrix()[2][1], -1);
  ASSERT_EQ(mat4.GetMatrix()[2][2], 0);
  ASSERT_NE(mat3.GetMatrix(), mat4.GetMatrix());
}

TEST(S21MatrixTest, GetRowsTest) {
  S21Matrix mat1(2, 2);
  ASSERT_EQ(mat1.GetRows(), 2);

  S21Matrix mat2(3, 4);
  ASSERT_EQ(mat2.GetRows(), 3);
}

TEST(S21MatrixTest, GetColsTest) {
  S21Matrix mat1(2, 2);
  ASSERT_EQ(mat1.GetCols(), 2);

  S21Matrix mat2(3, 4);
  ASSERT_EQ(mat2.GetCols(), 4);
}

TEST(S21MatrixTest, GetMatrixTest) {
  S21Matrix mat1(2, 2);
  mat1.GetMatrix()[0][0] = 1;
  mat1.GetMatrix()[0][1] = 2;
  mat1.GetMatrix()[1][0] = 3;
  mat1.GetMatrix()[1][1] = 4;
  ASSERT_EQ(mat1.GetMatrix()[0][0], 1);
  ASSERT_EQ(mat1.GetMatrix()[0][1], 2);
  ASSERT_EQ(mat1.GetMatrix()[1][0], 3);
  ASSERT_EQ(mat1.GetMatrix()[1][1], 4);

  S21Matrix mat2(3, 3);
  mat2.GetMatrix()[0][0] = 1;
  mat2.GetMatrix()[0][1] = 0;
  mat2.GetMatrix()[0][2] = 2;
  mat2.GetMatrix()[1][0] = -1;
  mat2.GetMatrix()[1][1] = 3;
  mat2.GetMatrix()[1][2] = 1;
  mat2.GetMatrix()[2][0] = 2;
  mat2.GetMatrix()[2][1] = -1;
  mat2.GetMatrix()[2][2] = 0;
  ASSERT_EQ(mat2.GetMatrix()[0][0], 1);
  ASSERT_EQ(mat2.GetMatrix()[0][1], 0);
  ASSERT_EQ(mat2.GetMatrix()[0][2], 2);
  ASSERT_EQ(mat2.GetMatrix()[1][0], -1);
  ASSERT_EQ(mat2.GetMatrix()[1][1], 3);
  ASSERT_EQ(mat2.GetMatrix()[1][2], 1);
  ASSERT_EQ(mat2.GetMatrix()[2][0], 2);
  ASSERT_EQ(mat2.GetMatrix()[2][1], -1);
  ASSERT_EQ(mat2.GetMatrix()[2][2], 0);
}

TEST(S21MatrixTest, SetColsLarger) {
  S21Matrix m(2, 3);
  m.SetValue(0, 0, 1);
  m.SetValue(0, 1, 2);
  m.SetValue(0, 2, 3);
  m.SetValue(1, 0, 4);
  m.SetValue(1, 1, 5);
  m.SetValue(1, 2, 6);

  m.SetCols(4);

  EXPECT_EQ(m.GetRows(), 2);
  EXPECT_EQ(m.GetCols(), 4);
  EXPECT_EQ(m.GetValue(0, 0), 1);
  EXPECT_EQ(m.GetValue(0, 1), 2);
  EXPECT_EQ(m.GetValue(0, 2), 3);
  EXPECT_EQ(m.GetValue(0, 3), 0);
  EXPECT_EQ(m.GetValue(1, 0), 4);
  EXPECT_EQ(m.GetValue(1, 1), 5);
  EXPECT_EQ(m.GetValue(1, 2), 6);
  EXPECT_EQ(m.GetValue(1, 3), 0);
}

TEST(S21MatrixTest, SetColsSmaller) {
  S21Matrix m(2, 3);
  m.SetValue(0, 0, 1);
  m.SetValue(0, 1, 2);
  m.SetValue(0, 2, 3);
  m.SetValue(1, 0, 4);
  m.SetValue(1, 1, 5);
  m.SetValue(1, 2, 6);

  m.SetCols(2);

  EXPECT_EQ(m.GetRows(), 2);
  EXPECT_EQ(m.GetCols(), 2);
  EXPECT_EQ(m.GetValue(0, 0), 1);
  EXPECT_EQ(m.GetValue(0, 1), 2);
  EXPECT_EQ(m.GetValue(1, 0), 4);
  EXPECT_EQ(m.GetValue(1, 1), 5);
}

TEST(S21MatrixTest, MulMatrixThrowsException) {
  S21Matrix m1(2, 3);
  S21Matrix m2(4, 6);

  ASSERT_ANY_THROW(m1.MulMatrix(m2));
}

TEST(Actions, Transpose) {
  auto test1 = S21Matrix(2, 2);
  test1(0, 0) = 3;
  test1(0, 1) = 1;
  test1(1, 0) = 20;
  test1(1, 1) = -2;
  test1 = test1.Transpose();
  EXPECT_EQ(test1(0, 0), 3);
  EXPECT_EQ(test1(0, 1), 20);
  EXPECT_EQ(test1(1, 0), 1);
  EXPECT_EQ(test1(1, 1), -2);
}

TEST(Actions, Determinant) {
  auto test1 = S21Matrix(2, 2);
  test1(0, 0) = 73;
  test1(0, 1) = 16;
  test1(1, 0) = 0;
  test1(1, 1) = -4;
  EXPECT_EQ(test1.Determinant(), -292);
  test1(0, 0) = 3;
  test1(0, 1) = 5;
  test1(1, 0) = -8;
  test1(1, 1) = -4;
  EXPECT_EQ(test1.Determinant(), 28);
  test1(0, 0) = 2;
  test1(0, 1) = -5;
  test1(1, 0) = 1;
  test1(1, 1) = -2;
  EXPECT_EQ(test1.Determinant(), 1);
  test1(0, 0) = 13;
  test1(0, 1) = 5;
  test1(1, 0) = 13;
  test1(1, 1) = 0;
  EXPECT_EQ(test1.Determinant(), -65);
}

TEST(Actions, Determinant_5x5) {
  int size = 5;
  S21Matrix m(size, size);

  m(0, 1) = 6;
  m(0, 2) = -2;
  m(0, 3) = -1;
  m(0, 4) = 5;
  m(1, 3) = -9;
  m(1, 4) = -7;
  m(2, 1) = 15;
  m(2, 2) = 35;
  m(3, 1) = -1;
  m(3, 2) = -11;
  m(3, 3) = -2;
  m(3, 4) = 1;
  m(4, 0) = -2;
  m(4, 1) = -2;
  m(4, 2) = 3;
  m(4, 4) = -2;

  double res = m.Determinant();
  ASSERT_NEAR(res, 2480, 1e-6);
}

TEST(Actions, Determinant3x3) {
  auto test1 = S21Matrix(3, 3);
  test1(0, 0) = 5;
  test1(0, 1) = 2;
  test1(0, 2) = 1;
  test1(1, 0) = 2;
  test1(1, 1) = 3;
  test1(1, 2) = 2;
  test1(2, 0) = 3;
  test1(2, 1) = 4;
  test1(2, 2) = 5;
  EXPECT_EQ(test1.Determinant(), 26);
}

TEST(Actions, Inverse) {
  auto test1 = S21Matrix(2, 2);
  test1(0, 0) = 3;
  test1(0, 1) = 1;
  test1(1, 0) = 2;
  test1(1, 1) = -2;
  test1 = test1.InverseMatrix();
  EXPECT_EQ(test1(0, 0), 0.25);
  EXPECT_EQ(test1(0, 1), 0.125);
  EXPECT_EQ(test1(1, 0), 0.25);
  EXPECT_EQ(test1(1, 1), -0.375);
}

TEST(Actions, CalcComplements3x3) {
  const int rows = 3;
  const int cols = 3;

  S21Matrix given(rows, cols);
  S21Matrix expected(rows, cols);

  expected(0, 0) = 0;
  expected(0, 1) = 10;
  expected(0, 2) = -20;
  expected(1, 0) = 4;
  expected(1, 1) = -14;
  expected(1, 2) = 8;
  expected(2, 0) = -8;
  expected(2, 1) = -2;
  expected(2, 2) = 4;

  given(0, 0) = 1;
  given(0, 1) = 2;
  given(0, 2) = 3;
  given(1, 0) = 0;
  given(1, 1) = 4;
  given(1, 2) = 2;
  given(2, 0) = 5;
  given(2, 1) = 2;
  given(2, 2) = 1;

  S21Matrix res = given.CalcComplements();
  ASSERT_TRUE(res == expected);
}

TEST(Actions, CalcComplementsTest) {
  S21Matrix matrix1(1, 1);
  matrix1(0, 0) = 5;
  S21Matrix expected1(1, 1);
  expected1(0, 0) = 1;
  EXPECT_EQ(matrix1.CalcComplements(), expected1);

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;
  S21Matrix expected2(2, 2);
  expected2(0, 0) = 4;
  expected2(0, 1) = -3;
  expected2(1, 0) = -2;
  expected2(1, 1) = 1;

  EXPECT_EQ(matrix2.CalcComplements(), expected2);

  S21Matrix matrix3(2, 3);
  ASSERT_ANY_THROW(matrix3.CalcComplements());
}

TEST(S21MatrixTest, CalcComplementsTest) {
  S21Matrix matrix1(1, 1);
  matrix1(0, 0) = 5;
  S21Matrix expected1(1, 1);
  expected1(0, 0) = 1;
  EXPECT_EQ(matrix1.CalcComplements(), expected1);

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;
  S21Matrix expected2(2, 2);
  expected2(0, 0) = 4;
  expected2(0, 1) = -3;
  expected2(1, 0) = -2;
  expected2(1, 1) = 1;
  EXPECT_EQ(matrix2.CalcComplements(), expected2);

  S21Matrix matrix3(3, 3);
  matrix3(0, 0) = 6;
  matrix3(0, 1) = 1;
  matrix3(0, 2) = 1;
  matrix3(1, 0) = 4;
  matrix3(1, 1) = -2;
  matrix3(1, 2) = 5;
  matrix3(2, 0) = 2;
  matrix3(2, 1) = 8;
  matrix3(2, 2) = 7;
  S21Matrix expected3(3, 3);
  expected3(0, 0) = -54;
  expected3(0, 1) = -18;
  expected3(0, 2) = 36;
  expected3(1, 0) = 1;
  expected3(1, 1) = 40;
  expected3(1, 2) = -46;
  expected3(2, 0) = 7;
  expected3(2, 1) = -26;
  expected3(2, 2) = -16;
  EXPECT_EQ(matrix3.CalcComplements(), expected3);
}

TEST(Actions, Complements) {
  auto test1 = S21Matrix(2, 2);
  test1(0, 0) = 3;
  test1(0, 1) = 1;
  test1(1, 0) = 20;
  test1(1, 1) = -2;
  auto test2 = test1.CalcComplements();
  EXPECT_EQ(test2(0, 0), -2);
  EXPECT_EQ(test2(0, 1), -20);
  EXPECT_EQ(test2(1, 0), -1);
  EXPECT_EQ(test2(1, 1), 3);
}

TEST(S21MatrixTest, InverseMatrixTest) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 1;
  mat1(0, 1) = 2;
  mat1(1, 0) = 3;
  mat1(1, 1) = 4;
  S21Matrix inv_mat1 = mat1.InverseMatrix();
  S21Matrix expected1(2, 2);
  expected1(0, 0) = -2;
  expected1(0, 1) = 1;
  expected1(1, 0) = 1.5;
  expected1(1, 1) = -0.5;
  ASSERT_TRUE(inv_mat1 == expected1);

  S21Matrix mat3(3, 3);
  mat3(0, 0) = 1;
  mat3(0, 1) = 2;
  mat3(0, 2) = 3;
  mat3(1, 0) = 4;
  mat3(1, 1) = 5;
  mat3(1, 2) = 6;
  mat3(2, 0) = 7;
  mat3(2, 1) = 8;
  mat3(2, 2) = 9;
  ASSERT_ANY_THROW(mat3.InverseMatrix());
}

TEST(S21MatrixTest, OperatorPlusEqualTest) {
  S21Matrix mat1(2, 2);
  mat1.GetMatrix()[0][0] = 1;
  mat1.GetMatrix()[0][1] = 2;
  mat1.GetMatrix()[1][0] = 3;
  mat1.GetMatrix()[1][1] = 4;
  S21Matrix mat2(2, 2);
  mat2.GetMatrix()[0][0] = 2;
  mat2.GetMatrix()[0][1] = 4;
  mat2.GetMatrix()[1][0] = 6;
  mat2.GetMatrix()[1][1] = 8;
  mat1 += mat2;
  ASSERT_EQ(mat1.GetMatrix()[0][0], 3);
  ASSERT_EQ(mat1.GetMatrix()[0][1], 6);
  ASSERT_EQ(mat1.GetMatrix()[1][0], 9);
  ASSERT_EQ(mat1.GetMatrix()[1][1], 12);

  S21Matrix mat3(3, 3);
  mat3.GetMatrix()[0][0] = 1;
  mat3.GetMatrix()[0][1] = 0;
  mat3.GetMatrix()[0][2] = 2;
  mat3.GetMatrix()[1][0] = -1;
  mat3.GetMatrix()[1][1] = 3;
  mat3.GetMatrix()[1][2] = 1;
  mat3.GetMatrix()[2][0] = 2;
  mat3.GetMatrix()[2][1] = -1;
  mat3.GetMatrix()[2][2] = 0;
  S21Matrix mat4(3, 3);
  mat4.GetMatrix()[0][0] = 1;
  mat4.GetMatrix()[0][1] = -1;
  mat4.GetMatrix()[0][2] = 0;
  mat4.GetMatrix()[1][0] = 2;
  mat4.GetMatrix()[1][1] = 1;
  mat4.GetMatrix()[1][2] = -2;
  mat4.GetMatrix()[2][0] = 0;
  mat4.GetMatrix()[2][1] = -1;
  mat4.GetMatrix()[2][2] = 1;
  mat3 += mat4;
  ASSERT_EQ(mat3.GetMatrix()[0][0], 2);
  ASSERT_EQ(mat3.GetMatrix()[0][1], -1);
  ASSERT_EQ(mat3.GetMatrix()[0][2], 2);
  ASSERT_EQ(mat3.GetMatrix()[1][0], 1);
  ASSERT_EQ(mat3.GetMatrix()[1][1], 4);
  ASSERT_EQ(mat3.GetMatrix()[1][2], -1);
  ASSERT_EQ(mat3.GetMatrix()[2][0], 2);
  ASSERT_EQ(mat3.GetMatrix()[2][1], -2);
  ASSERT_EQ(mat3.GetMatrix()[2][2], 1);
}

TEST(S21MatrixTest, OperatorPlusTest) {
  S21Matrix mat1(2, 2);
  mat1.GetMatrix()[0][0] = 1;
  mat1.GetMatrix()[0][1] = 2;
  mat1.GetMatrix()[1][0] = 3;
  mat1.GetMatrix()[1][1] = 4;
  S21Matrix mat2(2, 2);
  mat2.GetMatrix()[0][0] = 2;
  mat2.GetMatrix()[0][1] = 4;
  mat2.GetMatrix()[1][0] = 6;
  mat2.GetMatrix()[1][1] = 8;
  S21Matrix res = mat1 + mat2;
  ASSERT_EQ(res.GetMatrix()[0][0], 3);
  ASSERT_EQ(res.GetMatrix()[0][1], 6);
  ASSERT_EQ(res.GetMatrix()[1][0], 9);
  ASSERT_EQ(res.GetMatrix()[1][1], 12);

  S21Matrix mat3(3, 3);
  mat3.GetMatrix()[0][0] = 1;
  mat3.GetMatrix()[0][1] = 0;
  mat3.GetMatrix()[0][2] = 2;
  mat3.GetMatrix()[1][0] = -1;
  mat3.GetMatrix()[1][1] = 3;
}

TEST(S21MatrixTest, OperatorRoundBracketsTest) {
  S21Matrix mat(2, 2);
  mat(0, 0) = 1;
  mat(0, 1) = 2;
  mat(1, 0) = 3;
  mat(1, 1) = 4;
  ASSERT_EQ(mat(0, 0), 1);
  ASSERT_EQ(mat(0, 1), 2);
  ASSERT_EQ(mat(1, 0), 3);
  ASSERT_EQ(mat(1, 1), 4);
}

TEST(S21MatrixTest, OperatorMultiply) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  S21Matrix result = matrix1 * matrix2;

  EXPECT_EQ(result(0, 0), 19.0);
  EXPECT_EQ(result(0, 1), 22.0);
  EXPECT_EQ(result(1, 0), 43.0);
  EXPECT_EQ(result(1, 1), 50.0);
}

TEST(S21MatrixTest, OperatorSubtract) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  S21Matrix result = matrix1 - matrix2;

  EXPECT_EQ(result(0, 0), -4.0);
  EXPECT_EQ(result(0, 1), -4.0);
  EXPECT_EQ(result(1, 0), -4.0);
  EXPECT_EQ(result(1, 1), -4.0);

  S21Matrix matrix3(3, 2);
  matrix3(0, 0) = 1.0;
  matrix3(0, 1) = 2.0;
  matrix3(1, 0) = 3.0;
  matrix3(1, 1) = 4.0;
  matrix3(2, 0) = 5.0;
  matrix3(2, 1) = 6.0;

  S21Matrix matrix4(3, 2);
  matrix4(0, 0) = 7.0;
  matrix4(0, 1) = 8.0;
  matrix4(1, 0) = 9.0;
  matrix4(1, 1) = 10.0;
  matrix4(2, 0) = 11.0;
  matrix4(2, 1) = 12.0;

  S21Matrix result2 = matrix3 - matrix4;

  EXPECT_EQ(result2(0, 0), -6.0);
  EXPECT_EQ(result2(0, 1), -6.0);
  EXPECT_EQ(result2(1, 0), -6.0);
  EXPECT_EQ(result2(1, 1), -6.0);
  EXPECT_EQ(result2(2, 0), -6.0);
  EXPECT_EQ(result2(2, 1), -6.0);
}

TEST(S21MatrixTest, OperatorIndexing) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  EXPECT_EQ(matrix(0, 0), 1.0);
  EXPECT_EQ(matrix(0, 1), 2.0);
  EXPECT_EQ(matrix(1, 0), 3.0);
  EXPECT_EQ(matrix(1, 1), 4.0);

  S21Matrix matrix2(3, 3);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(0, 2) = 3.0;
  matrix2(1, 0) = 4.0;
  matrix2(1, 1) = 5.0;
  matrix2(1, 2) = 6.0;
  matrix2(2, 0) = 7.0;
  matrix2(2, 1) = 8.0;
  matrix2(2, 2) = 9.0;

  EXPECT_EQ(matrix2(0, 0), 1.0);
  EXPECT_EQ(matrix2(0, 1), 2.0);
  EXPECT_EQ(matrix2(0, 2), 3.0);
  EXPECT_EQ(matrix2(1, 0), 4.0);
  EXPECT_EQ(matrix2(1, 1), 5.0);
  EXPECT_EQ(matrix2(1, 2), 6.0);
  EXPECT_EQ(matrix2(2, 0), 7.0);
  EXPECT_EQ(matrix2(2, 1), 8.0);
  EXPECT_EQ(matrix2(2, 2), 9.0);
}

TEST(S21MatrixTest, SetRowsLarger) {
  S21Matrix m(2, 3);
  m.SetValue(0, 0, 1);
  m.SetValue(0, 1, 2);
  m.SetValue(0, 2, 3);
  m.SetValue(1, 0, 4);
  m.SetValue(1, 1, 5);
  m.SetValue(1, 2, 6);

  m.SetRows(4);

  EXPECT_EQ(m.GetRows(), 4);
  EXPECT_EQ(m.GetCols(), 3);
  EXPECT_EQ(m.GetValue(0, 0), 1);
  EXPECT_EQ(m.GetValue(0, 1), 2);
  EXPECT_EQ(m.GetValue(0, 2), 3);
  EXPECT_EQ(m.GetValue(1, 0), 4);
  EXPECT_EQ(m.GetValue(1, 1), 5);
  EXPECT_EQ(m.GetValue(1, 2), 6);
  EXPECT_EQ(m.GetValue(2, 0), 0);
  EXPECT_EQ(m.GetValue(2, 1), 0);
  EXPECT_EQ(m.GetValue(2, 2), 0);
  EXPECT_EQ(m.GetValue(3, 0), 0);
  EXPECT_EQ(m.GetValue(3, 1), 0);
  EXPECT_EQ(m.GetValue(3, 2), 0);
}

TEST(S21MatrixTest, SetRowsSmaller) {
  S21Matrix m(2, 3);
  m.SetValue(0, 0, 1);
  m.SetValue(0, 1, 2);
  m.SetValue(0, 2, 3);
  m.SetValue(1, 0, 4);
  m.SetValue(1, 1, 5);
  m.SetValue(1, 2, 6);

  m.SetRows(1);

  EXPECT_EQ(m.GetRows(), 1);
  EXPECT_EQ(m.GetCols(), 3);
  EXPECT_EQ(m.GetValue(0, 0), 1);
  EXPECT_EQ(m.GetValue(0, 1), 2);
  EXPECT_EQ(m.GetValue(0, 2), 3);
}

TEST(S21MatrixTest, OperatorRoundBracketsTestAssert) {
  S21Matrix m(2, 3);
  m.SetValue(0, 0, 1);
  m.SetValue(0, 1, 2);
  m.SetValue(0, 2, 3);
  m.SetValue(1, 0, 4);
  m.SetValue(1, 1, 5);
  m.SetValue(1, 2, 6);
  ASSERT_EQ(m(0, 0), 1);
  ASSERT_EQ(m(0, 1), 2);
}

TEST(S21MatrixTest, ConstIndexingAfterModification) {
  S21Matrix m(2, 3);
  m.SetValue(0, 0, 1);
  m.SetValue(1, 2, 6);

  EXPECT_EQ(m(0, 0), 1);
  EXPECT_EQ(m(1, 2), 6);
}

TEST(S21MatrixTest, OperatorThrowsExceptionWhenIndexIsOutOfRange) {
  S21Matrix matrix(2, 2);
  matrix.SetValue(0, 0, 1);
  matrix.SetValue(0, 1, 2);
  matrix.SetValue(1, 0, 3);
  matrix.SetValue(1, 1, 4);
  const S21Matrix matrix2 = matrix;
  EXPECT_EQ(matrix2(1, 1), 4);
  EXPECT_EQ(matrix2(1, 0), 3);
  ASSERT_ANY_THROW(matrix(3, 1));
  ASSERT_ANY_THROW(matrix2(3, 1));
  ASSERT_ANY_THROW(matrix2(-1, 1));
  ASSERT_ANY_THROW(matrix2(1, 4));
  ASSERT_ANY_THROW(matrix2(1, -1));
}

TEST(S21Matrix, GetRows) {
  S21Matrix m(2, 3);
  EXPECT_EQ(m.GetRows(), 2);
}

TEST(S21Matrix, GetCols) {
  S21Matrix m(2, 3);
  EXPECT_EQ(m.GetCols(), 3);
}

TEST(S21Matrix, GetValue) {
  S21Matrix m(2, 3);
  m.SetValue(0, 1, 1.0);
  EXPECT_EQ(m.GetValue(0, 1), 1.0);
}

TEST(S21Matrix, GetMatrix) {
  S21Matrix m(2, 3);
  double **matrix = m.GetMatrix();
  EXPECT_NE(matrix, nullptr);
  matrix[0][1] = 1.0;
  EXPECT_EQ(m.GetValue(0, 1), 1.0);
}

TEST(S21Matrix, SetRows) {
  S21Matrix m(2, 3);
  m.SetRows(3);
  EXPECT_EQ(m.GetRows(), 3);
}

TEST(S21Matrix, SetCols) {
  S21Matrix m(2, 3);
  m.SetCols(4);
  EXPECT_EQ(m.GetCols(), 4);
}

TEST(S21Matrix, SetValue) {
  S21Matrix m(2, 3);
  m.SetValue(0, 1, 1.0);
  EXPECT_EQ(m.GetValue(0, 1), 1.0);
}

TEST(S21Matrix, EqMatrix) {
  S21Matrix m1(2, 3);
  m1.SetValue(0, 0, 1.0);
  S21Matrix m2(2, 3);
  m2.SetValue(0, 0, 1.0);
  EXPECT_TRUE(m1.EqMatrix(m2));
}

TEST(S21Matrix, EqMatrixFalse) {
  S21Matrix m1(2, 3);
  m1.SetValue(0, 0, 1.0);
  S21Matrix m2(2, 3);
  m2.SetValue(0, 0, 2.0);
  EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(S21Matrix, EqMatrixFalse2) {
  S21Matrix m1(2, 3);
  m1.SetValue(0, 0, 1.0);
  S21Matrix m2(2, 2);
  m2.SetValue(0, 0, 1.0);
  EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(S21Matrix, SumMatrix) {
  S21Matrix m1(2, 3);
  m1.SetValue(0, 0, 1.0);
  S21Matrix m2(2, 3);
  m2.SetValue(0, 1, 2.0);
  m1.SumMatrix(m2);
  EXPECT_EQ(m1.GetValue(0, 0), 1.0);
  EXPECT_EQ(m1.GetValue(0, 1), 2.0);
}

TEST(S21Matrix, SubMatrix) {
  S21Matrix m1(2, 3);
  m1.SetValue(0, 0, 1.0);
  S21Matrix m2(2, 3);
  m2.SetValue(0, 1, 2.0);
  m1.SubMatrix(m2);
  S21Matrix m3(4, 3);
  S21Matrix m4;
  EXPECT_EQ(m1.GetValue(0, 0), 1.0);
  EXPECT_EQ(m1.GetValue(0, 1), -2.0);
  ASSERT_ANY_THROW(m1.SubMatrix(m3));
  ASSERT_ANY_THROW(m1.SubMatrix(m4));
  ASSERT_ANY_THROW(m1.GetValue(0, -1));
  ASSERT_ANY_THROW(m1.SetValue(0, -1, 1));
}

TEST(S21MatrixTest, MulNumberTest) {
  S21Matrix matrix1(2, 3);
  matrix1.SetValue(0, 0, 1);
  matrix1.SetValue(0, 1, 2);
  matrix1.SetValue(0, 2, 3);
  matrix1.SetValue(1, 0, 4);
  matrix1.SetValue(1, 1, 5);
  matrix1.SetValue(1, 2, 6);
  matrix1.MulNumber(2);
  EXPECT_EQ(matrix1.GetValue(0, 0), 2);
  EXPECT_EQ(matrix1.GetValue(0, 1), 4);
  EXPECT_EQ(matrix1.GetValue(0, 2), 6);
  EXPECT_EQ(matrix1.GetValue(1, 0), 8);
  EXPECT_EQ(matrix1.GetValue(1, 1), 10);
  EXPECT_EQ(matrix1.GetValue(1, 2), 12);

  S21Matrix matrix2(2, 2);
  matrix2.SetValue(0, 0, 1);
  matrix2.SetValue(0, 1, 2);
  matrix2.SetValue(1, 0, 3);
  matrix2.SetValue(1, 1, 4);
  matrix2.MulNumber(-2);
  EXPECT_EQ(matrix2.GetValue(0, 0), -2);
  EXPECT_EQ(matrix2.GetValue(0, 1), -4);
  EXPECT_EQ(matrix2.GetValue(1, 0), -6);
  EXPECT_EQ(matrix2.GetValue(1, 1), -8);
}

TEST(Test, operator_mulNumbereq) {
  S21Matrix B(3, 4);
  S21Matrix A(3, 4);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(0, 3) = 4;
  B(1, 0) = 5;
  B(1, 1) = 6;
  B(1, 2) = 7;
  B(1, 3) = 8;
  B(2, 0) = 9;
  B(2, 1) = 10;
  B(2, 2) = 11;
  B(2, 3) = 12;

  A(0, 0) = 2;
  A(0, 1) = 4;
  A(0, 2) = 6;
  A(0, 3) = 8;
  A(1, 0) = 10;
  A(1, 1) = 12;
  A(1, 2) = 14;
  A(1, 3) = 16;
  A(2, 0) = 18;
  A(2, 1) = 20;
  A(2, 2) = 22;
  A(2, 3) = 24;

  B *= 2;
  EXPECT_EQ(1, B == A);
}
TEST(Test, mulMatrixeq) {
  S21Matrix B(2, 2);
  S21Matrix A(2, 2);
  S21Matrix expected(2, 2);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 5;
  B(1, 1) = 6;

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 5;
  A(1, 1) = 6;

  expected(0, 0) = 11;
  expected(0, 1) = 14;
  expected(1, 0) = 35;
  expected(1, 1) = 46;

  B *= A;
  EXPECT_EQ(1, B == expected);
}
TEST(Test, operator_mulMatrix) {
  S21Matrix B(2, 2);
  S21Matrix A(2, 2);
  S21Matrix expected(2, 2);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 5;
  B(1, 1) = 6;

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 5;
  A(1, 1) = 6;

  expected(0, 0) = 11;
  expected(0, 1) = 14;
  expected(1, 0) = 35;
  expected(1, 1) = 46;

  B = B * A;
  EXPECT_EQ(1, B == expected);
}

TEST(S21MatrixTest, TransposeTest) {
  S21Matrix matrix1(2, 3);
  matrix1.SetValue(0, 0, 1);
  matrix1.SetValue(0, 1, 2);
  matrix1.SetValue(0, 2, 3);
  matrix1.SetValue(1, 0, 4);
  matrix1.SetValue(1, 1, 5);
  matrix1.SetValue(1, 2, 6);
  S21Matrix result1 = matrix1.Transpose();
  EXPECT_EQ(result1.GetRows(), 3);
  EXPECT_EQ(result1.GetCols(), 2);
  EXPECT_EQ(result1.GetValue(0, 0), 1);
  EXPECT_EQ(result1.GetValue(0, 1), 4);
  EXPECT_EQ(result1.GetValue(1, 0), 2);
  EXPECT_EQ(result1.GetValue(1, 1), 5);
  EXPECT_EQ(result1.GetValue(2, 0), 3);
  EXPECT_EQ(result1.GetValue(2, 1), 6);

  S21Matrix matrix2(3, 3);
  matrix2.SetValue(0, 0, 1);
  matrix2.SetValue(0, 1, 2);
  matrix2.SetValue(0, 2, 3);
  matrix2.SetValue(1, 0, 4);
  matrix2.SetValue(1, 1, 5);
  matrix2.SetValue(1, 2, 6);
  matrix2.SetValue(2, 0, 7);
  matrix2.SetValue(2, 1, 8);
  matrix2.SetValue(2, 2, 9);
  S21Matrix result2 = matrix2.Transpose();
  EXPECT_EQ(result2.GetRows(), 3);
  EXPECT_EQ(result2.GetCols(), 3);
  EXPECT_EQ(result2.GetValue(0, 0), 1);
  EXPECT_EQ(result2.GetValue(0, 1), 4);
  EXPECT_EQ(result2.GetValue(0, 2), 7);
  EXPECT_EQ(result2.GetValue(1, 0), 2);
  EXPECT_EQ(result2.GetValue(1, 1), 5);
  EXPECT_EQ(result2.GetValue(1, 2), 8);
  EXPECT_EQ(result2.GetValue(2, 0), 3);
  EXPECT_EQ(result2.GetValue(2, 1), 6);
  EXPECT_EQ(result2.GetValue(2, 2), 9);
}

TEST(S21MatrixTest, DeterminantOneByOne) {
  S21Matrix m(1, 1);
  m.SetValue(0, 0, 2.0);
  EXPECT_DOUBLE_EQ(m.Determinant(), 2.0);
}

TEST(S21MatrixTest, DeterminantTwoByTwo) {
  S21Matrix m(2, 2);
  m.SetValue(0, 0, 1.0);
  m.SetValue(0, 1, 2.0);
  m.SetValue(1, 0, 3.0);
  m.SetValue(1, 1, 4.0);
  EXPECT_DOUBLE_EQ(m.Determinant(), -2.0);
}

TEST(S21MatrixTest, DeterminantFourByFour) {
  S21Matrix m(4, 4);
  m.SetValue(0, 0, 1.0);
  m.SetValue(0, 1, 2.0);
  m.SetValue(0, 2, 3.0);
  m.SetValue(0, 3, 4.0);
  m.SetValue(1, 0, 0.0);
  m.SetValue(1, 1, 1.0);
  m.SetValue(1, 2, 2.0);
  m.SetValue(1, 3, 3.0);
  m.SetValue(2, 0, 0.0);
  m.SetValue(2, 1, 0.0);
  m.SetValue(2, 2, 1.0);
  m.SetValue(2, 3, 2.0);
  m.SetValue(3, 0, 0.0);
  m.SetValue(3, 1, 0.0);
  m.SetValue(3, 2, 0.0);
  m.SetValue(3, 3, 1.0);
  EXPECT_DOUBLE_EQ(m.Determinant(), 1.0);
}

TEST(S21MatrixTest, MinorTwoByTwo) {
  S21Matrix m(2, 2);
  m.SetValue(0, 0, 1.0);
  m.SetValue(0, 1, 2.0);
  m.SetValue(1, 0, 3.0);
  m.SetValue(1, 1, 4.0);

  S21Matrix temp(1, 1);
  m.Minor(m, temp, 0, 1, 2);

  EXPECT_EQ(temp.GetRows(), 1);
  EXPECT_EQ(temp.GetCols(), 1);
  EXPECT_DOUBLE_EQ(temp.GetValue(0, 0), 3.0);
}

// // Test the Minor function with a 3x3 matrix
// TEST(S21MatrixTest, MinorThreeByThree) {
//   S21Matrix m(3, 3);
//   m.SetValue(0, 0, 1.0);
//   m.SetValue(0, 1, 2.0);
//   m.SetValue(0, 2, 3.0);
//   m.SetValue(1, 0, 4.0);
//   m.SetValue(1, 1, 5.0);
//   m.SetValue(1, 2, 6.0);
//   m.SetValue(2, 0, 7.0);
//   m.SetValue(2, 1, 8.0);
//   m.SetValue(2, 2, 9.0);

//   S21Matrix temp(2, 2);
//   m.Minor(m, temp, 1, 2, 3);

//   EXPECT_EQ(temp.GetRows(), 2);
//   EXPECT_EQ(temp.GetCols(), 2);
//   EXPECT_DOUBLE_EQ(temp.GetValue(0, 0), 1.0);
//   EXPECT_DOUBLE_EQ(temp.GetValue(0, 1), 3.0);
//   EXPECT_DOUBLE_EQ(temp.GetValue(1, 0), 7.0);
//   EXPECT_DOUBLE_EQ(temp.GetValue(1, 1), 9.0);
// }

TEST(S21MatrixTest, MinorFourByFour) {
  S21Matrix m(4, 4);
  m.SetValue(0, 0, 1.0);
  m.SetValue(0, 1, 2.0);
  m.SetValue(0, 2, 3.0);
  m.SetValue(0, 3, 4.0);
  m.SetValue(1, 0, 5.0);
  m.SetValue(1, 1, 6.0);
  m.SetValue(1, 2, 7.0);
  m.SetValue(1, 3, 8.0);
  m.SetValue(2, 0, 9.0);
  m.SetValue(2, 1, 10.0);
  m.SetValue(2, 2, 11.0);
  m.SetValue(2, 3, 12.0);
  m.SetValue(3, 0, 13.0);
  m.SetValue(3, 1, 14.0);
  m.SetValue(3, 2, 15.0);
  m.SetValue(3, 3, 16.0);

  S21Matrix temp(3, 3);
  m.Minor(m, temp, 1, 1, 4);

  EXPECT_EQ(temp.GetRows(), 3);
  EXPECT_EQ(temp.GetCols(), 3);
  EXPECT_DOUBLE_EQ(temp.GetValue(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(temp.GetValue(0, 1), 3.0);
  EXPECT_DOUBLE_EQ(temp.GetValue(0, 2), 4.0);
  EXPECT_DOUBLE_EQ(temp.GetValue(1, 0), 9.0);
  EXPECT_DOUBLE_EQ(temp.GetValue(1, 1), 11.0);
  EXPECT_DOUBLE_EQ(temp.GetValue(1, 2), 12.0);
  EXPECT_DOUBLE_EQ(temp.GetValue(2, 0), 13.0);
  EXPECT_DOUBLE_EQ(temp.GetValue(2, 1), 15.0);
  EXPECT_DOUBLE_EQ(temp.GetValue(2, 2), 16.0);
}

TEST(Test, invers_test) {
  S21Matrix result(3, 3);
  result(0, 0) = 0;
  result(0, 1) = 1;
  result(0, 2) = -0.75;
  result(1, 0) = -0.5;
  result(1, 1) = 3;
  result(1, 2) = -2;
  result(2, 0) = 0.5;
  result(2, 1) = -3.5;
  result(2, 2) = 2.5;

  S21Matrix R(3, 3);
  R(0, 0) = 8;
  R(0, 1) = 2;
  R(0, 2) = 4;
  R(1, 0) = 4;
  R(1, 1) = 6;
  R(1, 2) = 6;
  R(2, 0) = 4;
  R(2, 1) = 8;
  R(2, 2) = 8;

  S21Matrix result_inverse(3, 3);
  result_inverse = R.InverseMatrix();
  EXPECT_EQ(1, result == result_inverse);
}

TEST(S21MatrixTest, OperatorMulNumberLeft) {
  S21Matrix mat(2, 3);
  mat.SetValue(1, 2, 3.14);
  S21Matrix result = 2.0 * mat;
  EXPECT_EQ(result.GetValue(1, 2), 6.28);
}

TEST(S21MatrixTest, OperatorMulNumberRight) {
  S21Matrix mat(2, 3);
  mat.SetValue(1, 2, 3.14);
  S21Matrix result = mat * 2.0;
  EXPECT_EQ(result.GetValue(1, 2), 6.28);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
