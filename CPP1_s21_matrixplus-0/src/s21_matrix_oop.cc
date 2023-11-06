#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Rows or columns is less or equal 0");
  }
  CreateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  CreateMatrix();
  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}

void S21Matrix::CreateMatrix() {
  this->matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) {
    this->matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::CheckForEqual(const S21Matrix &other) const {
  CheckNull();
  other.CheckNull();
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::runtime_error("Error: sizes are not equal");
  }
}

void S21Matrix::CheckNull() const {
  if (rows_ <= 0 || cols_ <= 0 || matrix_ == nullptr) {
    throw std::runtime_error("Error: matrix is null");
  }
}

void S21Matrix::CheckSquare() const {
  CheckNull();
  if (rows_ != cols_) {
    throw std::invalid_argument("Error: matrix is not square");
  }
}

void S21Matrix::CheckMul(const S21Matrix &other) const {
  CheckNull();
  other.CheckNull();
  if (rows_ != other.cols_) {
    throw std::runtime_error("Error: impossible to multiply");
  }
}

int S21Matrix::GetRows() const noexcept { return rows_; }

int S21Matrix::GetCols() const noexcept { return cols_; }

double S21Matrix::GetValue(int row_index, int col_index) const {
  if (row_index < 0 || row_index >= rows_ || col_index < 0 ||
      col_index >= cols_) {
    throw std::out_of_range("Invalid row or column index!");
  }
  return matrix_[row_index][col_index];
}

double **S21Matrix::GetMatrix() const noexcept { return matrix_; }

void S21Matrix::SetRows(int rows) {
  if (rows <= 0) throw std::invalid_argument("Rows is less or equal 0");
  int tmp = rows < rows_ ? rows : rows_;
  S21Matrix temp(rows, cols_);
  for (int i = 0; i < tmp; i++) {
    for (int j = 0; j < temp.cols_; j++) {
      temp.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  *this = temp;
}

void S21Matrix::SetCols(int cols) {
  if (cols <= 0) throw std::invalid_argument("Columns is less or equal 0");
  int tmp = cols < cols_ ? cols : cols_;
  S21Matrix temp(rows_, cols);
  for (int i = 0; i < temp.rows_; i++) {
    for (int j = 0; j < tmp; j++) {
      temp.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  *this = temp;
}

void S21Matrix::SetValue(int row_index, int col_index, double value) {
  if (row_index < 0 || row_index >= rows_ || col_index < 0 ||
      col_index >= cols_) {
    throw std::out_of_range("Rows or columns is less or equal 0");
  }
  matrix_[row_index][col_index] = value;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  CheckNull();
  other.CheckNull();
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-07) {
          return false;
        }
      }
    }
    return true;
  }
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  CheckNull();
  other.CheckNull();
  CheckForEqual(other);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] += other.matrix_[i][j];
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  CheckNull();
  other.CheckNull();
  CheckForEqual(other);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] -= other.matrix_[i][j];
}

void S21Matrix::MulNumber(const double num) {
  CheckNull();
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] *= num;
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  CheckNull();
  other.CheckNull();
  CheckMul(other);
  S21Matrix res(rows_, other.cols_);
  for (int i = 0; i < res.rows_; i++) {
    for (int y = 0; y < res.cols_; y++) {
      for (int k = 0, m = 0; m < cols_ && k < res.cols_; k++) {
        res.matrix_[i][y] =
            res.matrix_[i][y] + (matrix_[i][k] * other.matrix_[k][y]);
      }
    }
  }
  *this = res;
}

S21Matrix S21Matrix::Transpose() const {
  CheckNull();
  S21Matrix other(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      other.matrix_[j][i] = matrix_[i][j];
    }
  }
  return other;
}

double S21Matrix::Determinant() const {
  CheckNull();
  CheckSquare();
  double det = 0.0;
  int sign = 1;
  if (rows_ == 1) return matrix_[0][0];
  if (rows_ == 2)
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  S21Matrix temp(rows_ - 1, rows_ - 1);
  for (int i = 0; i < rows_; i++) {
    Minor(*this, temp, 0, i, rows_);
    det += sign * matrix_[0][i] * temp.Determinant();
    sign *= -1;
  }
  return det;
}

void S21Matrix::Minor(const S21Matrix &matr, S21Matrix &temp, int p, int q,
                      int size) const {
  int out_rows = 0;
  for (int i = 0; i < size - 1; i++) {
    if (i == p) out_rows = 1;
    int out_columns = 0;
    for (int j = 0; j < size - 1; j++) {
      if (j == q) out_columns = 1;
      temp.matrix_[i][j] = matr.matrix_[i + out_rows][j + out_columns];
    }
  }
}

S21Matrix S21Matrix::CalcComplements() const {
  CheckNull();
  CheckSquare();
  if (rows_ == 1) {
    S21Matrix result(1, 1);
    result.matrix_[0][0] = 1;
    return result;
  }
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix temp(rows_ - 1, cols_ - 1);
      Minor(*this, temp, i, j, rows_);
      result.matrix_[i][j] = temp.Determinant() * pow(-1, i + j);
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  CheckSquare();
  if (fabs(Determinant()) < 1e-06) throw std::logic_error("Determinant is 0");
  S21Matrix tran = CalcComplements().Transpose();
  S21Matrix res(rows_, cols_);
  for (auto i = 0; i < rows_; i++)
    for (auto j = 0; j < cols_; j++)
      res.matrix_[i][j] = tran.matrix_[i][j] / Determinant();
  return res;
}

double &S21Matrix::operator()(int i, int j) {
  if (i > rows_ || i < 0 || j > cols_ || j < 0)
    throw std::out_of_range("Incorrect input, index is out of range");
  return matrix_[i][j];
}

double S21Matrix::operator()(const int i, const int j) const {
  if (i > rows_ || i < 0 || j > cols_ || j < 0)
    throw std::out_of_range("Incorrect input, index is out of range");
  return matrix_[i][j];
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &o) {
  SumMatrix(o);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &o) const {
  S21Matrix res{*this};
  return res += o;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &o) {
  SubMatrix(o);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &o) const {
  S21Matrix res{*this};
  return res -= o;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &o) {
  MulMatrix(o);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double &value) {
  MulNumber(value);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &o) const {
  S21Matrix res{*this};
  return res *= o;
}

bool S21Matrix::operator==(const S21Matrix &o) const noexcept {
  return EqMatrix(o);
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new double *[rows_];
    for (int i = 0; i < rows_; ++i) {
      matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

S21Matrix &operator*(const double num, S21Matrix &matrix) {
  matrix.MulNumber(num);
  return matrix;
}

S21Matrix &operator*(S21Matrix &matrix, const double num) {
  matrix.MulNumber(num);
  return matrix;
}
