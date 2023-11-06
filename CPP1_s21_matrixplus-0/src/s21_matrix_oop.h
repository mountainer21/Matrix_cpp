#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <math.h>

#include <cstdio>
#include <exception>
#include <iostream>

class S21Matrix {
 public:
  S21Matrix() noexcept;
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
  ~S21Matrix();

  double &operator()(int i, int j);
  S21Matrix &operator=(const S21Matrix &other);
  bool operator==(const S21Matrix &o) const noexcept;
  double operator()(const int i, const int j) const;
  S21Matrix &operator+=(const S21Matrix &o);
  S21Matrix operator+(const S21Matrix &o) const;
  S21Matrix &operator-=(const S21Matrix &o);
  S21Matrix operator-(const S21Matrix &o) const;
  S21Matrix &operator*=(const S21Matrix &o);
  S21Matrix &operator*=(const double &value);
  S21Matrix operator*(const S21Matrix &o) const;
  friend S21Matrix &operator*(const double num, S21Matrix &matrix);
  friend S21Matrix &operator*(S21Matrix &matrix, const double num);

  int GetRows() const noexcept;
  int GetCols() const noexcept;
  double **GetMatrix() const noexcept;
  double GetValue(int row_index, int col_index) const;
  void SetRows(int rows);
  void SetCols(int cols);
  void SetValue(int row_index, int col_index, double value);
  void InitMatrix();
  void InitMatrixForMaths();
  void InitOtherMatrix();

  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;
  void PrintMatrix() const;
  void Minor(const S21Matrix &matr, S21Matrix &temp, int p, int q,
             int size) const;

 private:
  int rows_;
  int cols_;
  double **matrix_;
  void CreateMatrix();
  void CheckForEqual(const S21Matrix &other) const;
  void CheckNull() const;
  void CheckSquare() const;
  void CheckMul(const S21Matrix &other) const;
};

#endif
