#ifndef DEF_MATRIX
#define DEF_MATRIX

#include <iostream>
#include<math.h>
#include <stdexcept>
#include <vector>

template<class TYPE>
class Matrix
{
 private:
    size_t m_rows, m_columns;
    std::vector<TYPE> m_matrix;
 public:
    // constructors
    Matrix() {}
    Matrix(size_t num_rows, size_t num_columns): m_rows(num_rows), m_columns(num_columns), m_matrix(m_rows * m_columns) {}
    // element accessor
    TYPE & operator()(size_t row, size_t column){
        if((row>=m_rows) | (column>=m_columns))
            throw std::out_of_range("Matrix: Element out of range");
        return m_matrix[row * m_columns + column];
    }
    // constant element accessor
    TYPE operator()(size_t row, size_t column) const{  
        if((row>=m_rows) | (column>=m_columns))
            throw std::out_of_range("Matrix: Element out of range");
        return m_matrix[row * m_columns + column];
    }
    // addition operator
    const Matrix<TYPE> operator+(const Matrix<TYPE> & right){
        if ((this->getRows() != right.getRows()) | (this->getColumns() != right.getColumns())){
            throw std::length_error("const Matrix<TYPE> operator+(const Matrix<TYPE> & right): left and right matrices does not have same number of columns and/or rows.");
        }
        Matrix<TYPE> result(m_rows,m_columns);
        for (int i=0; i<this->getRows(); ++i){
            for (int j=0; j<this->getColumns(); ++j){
                result(i,j) = (*this)(i,j)+right(i,j);
            }
        }
        return result;
    }
    // subtraction operator
    const Matrix<TYPE> operator-(const Matrix<TYPE> & right){
        if ((this->getRows() != right.getRows()) | (this->getColumns() != right.getColumns())){
            throw std::length_error("const Matrix<TYPE> operator-(const Matrix<TYPE> & right): left and right matrices does not have same number of columns and/or rows.");
        }
        Matrix<TYPE> result(m_rows,m_columns);
        for (int i=0; i<this->getRows(); ++i){
            for (int j=0; j<this->getColumns(); ++j){
                result(i,j) = (*this)(i,j)-right(i,j);
            }
        }
        return result;
    }
    // multiplication operator
    const Matrix<TYPE> operator*(const Matrix<TYPE> & right){
        if ((this->getRows() != right.getRows()) | (this->getColumns() != right.getColumns())){
            throw std::length_error("const Matrix<TYPE> operator*(const Matrix<TYPE> & right): left and right matrices does not have same number of columns and/or rows.");
        }
        Matrix<TYPE> result(m_rows,m_columns);
        for (int i=0; i<this->getRows(); ++i){
            for (int j=0; j<this->getColumns(); ++j){
                result(i,j) = (*this)(i,j)*right(i,j);
            }
        }
        return result;
    }
    // division operator
    const Matrix<TYPE> operator/(const Matrix<TYPE> & denominator){
        if ((this->getRows() != denominator.getRows()) | (this->getColumns() != denominator.getColumns())){
            throw std::length_error("const Matrix<TYPE> operator/(const Matrix<TYPE> & denominator): numerator and denominator matrices does not have same number of columns and/or rows.");
        }
        Matrix<TYPE> result(m_rows,m_columns);
        for (int i=0; i<this->getRows(); ++i){
            for (int j=0; j<this->getColumns(); ++j){
                if(fabs(denominator(i,j)) > 0)
                    result(i,j) = (*this)(i,j) / denominator(i,j);
                else
                    result(i,j) = 0;
            }
        }
        return result;
    }
    // getter functions
    size_t getRows() const{
        return m_rows;
    }
    size_t getColumns() const{
        return m_columns;
    }
    // stream operator
    friend std::ostream & operator<<(std::ostream & out, const Matrix & in){
        for (int i=0; i<in.getRows(); ++i){
            for (int j=0; j<in.getColumns(); ++j){
                out << in(i,j) << " ";
            }
            out << "\n";
        }
        return out;
    }
};
#endif
