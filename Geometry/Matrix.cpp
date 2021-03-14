#include "Matrix.h"

#include <iostream>
#include <memory>

namespace Math_NS
{
    static const char* AxisOutOfRange     = "axis out of range";
    static const char* CreateMatrixError  = "impossible create matrix with parameters";
    static const char* SumMatrixError     = "impossible caclulate sum matrix";
    static const char* DiffMatrixError    = "impossible caclulate diff matrix";
    static const char* MultMatrixError    = "impossible caclulate mult matrix";
    static const char* AxisMultError      = "impossible mult axis";
    static const char* NotRectangleValues = "not rectangle values";


    Matrix::Matrix(size_t i_rows, size_t i_columns)
    {
        d_values.resize(i_rows, std::vector<double>(i_columns));
    }

    Matrix::Matrix(size_t i_sizeSide)
    {
        d_values.resize(i_sizeSide, std::vector<double>(i_sizeSide));
        for(size_t i = 0; i != i_sizeSide; ++i)
        {
            d_values[i][i] = 1.;
        }
    }

    Matrix::Matrix(const std::vector<std::vector<double>>& i_values)
        : d_values(i_values)
    {
    }

    Matrix::Matrix(const std::vector<double>& i_values,
                   size_t i_rows,
                   size_t i_columns)
    {
        if (i_values.size() != i_columns * i_rows)
        {
            throw std::runtime_error(CreateMatrixError);
        }
        d_values.resize(i_rows, std::vector<double>(i_columns));
        for(size_t row = 0; row != i_rows; ++row)
        {
            for(size_t column = 0; column != i_columns; ++column)
            {
                d_values[row][column] = i_values[row * i_columns + column];
            }
        }
    }

    const std::vector<double>& Matrix::operator[](int i_id) const
    {
        return d_values[i_id];
    }
    
    std::vector<double>& Matrix::operator[](int i_id)
    {
        return d_values[i_id];
    }

    const std::vector<double>& Matrix::operator()(int i_id) const
    {
        return d_values[i_id];
    }
    
    std::vector<double>& Matrix::operator()(int i_id)
    {
        return d_values[i_id];
    }
    

    Matrix& Matrix::operator*=(const Matrix& i_matrix)
    {
        if (columns() != i_matrix.rows())
        {
            throw std::runtime_error(MultMatrixError);
        }
        Matrix result(rows(), i_matrix.columns());
        for (size_t row = 0; row < result.rows(); ++row)
        {
            for (size_t column = 0; column < result.columns(); ++column)
            {
                for(size_t i = 0; i != (*this)[row].size(); ++i)
                {
                    result[row][column] += 
                                    (*this)[row][i] * i_matrix[i][column];
                }
            }
        }
        return *this = result;
    }


    Matrix& Matrix::operator+=(const Matrix& i_matrix)
    {
        if (i_matrix.columns() != columns() || i_matrix.rows() != rows())
        {
            throw std::runtime_error(SumMatrixError);
        }
        for (size_t row = 0; row!=rows(); ++row)
        {
            for (size_t column = 0; column != columns(); ++column)
            {
                d_values[row][column] += i_matrix[row][column];
            }
        }
        return *this;
    }

    Matrix& Matrix::operator-=(const Matrix& i_matrix)
    {
        if (i_matrix.columns() != columns() || i_matrix.rows() != rows())
        {
            throw std::runtime_error(DiffMatrixError);
        }
        for (size_t row = 0; row!=rows(); ++row)
        {
            for (size_t column = 0; column != columns(); ++column)
            {
                d_values[row][column] -= i_matrix[row][column];
            }
        }
        return *this;
    }
    Matrix Matrix::operator+(const Matrix& i_matrix) const
    {
        auto sum = *this;
        return sum += i_matrix;
    }
    Matrix Matrix::operator-(const Matrix& i_matrix) const
    {
        auto diff = *this;
        return diff -= i_matrix;
    }
    
    Matrix Matrix::operator*(const Matrix& i_matrix) const
    {
        auto mult = *this;
        return mult *= i_matrix;
    }

    
    size_t Matrix::rows() const
    {
        return d_values.size();
    }
    size_t Matrix::columns() const
    {
        return d_values[0].size();
    }
    
    Matrix rotation3(double i_angle, EAxis i_axis)
    {
        static const size_t SizeMatrix = 3;
        auto c = cos(i_angle);
        auto s = sin(i_angle);
        Matrix result(SizeMatrix);
        for (size_t row = 0; row < SizeMatrix; ++row)
            result[row][row] = c;
        result[i_axis][i_axis] = 1.;
        for (int row = 0; row < EAxis::EA_Count; ++row)
        {
            if (row == i_axis)
                continue;
            for (int column = 0; column < EAxis::EA_Count; ++column)
            {
                if (column == i_axis || column == row)
                    continue;
                result[row][column] = s * (row > column ? 1 : -1) * 
                                        ((i_axis % 2 == 0) ? 1 : -1);
            }
        }
        return result;
    }
    Matrix rotation4(double i_angle, EAxis i_axis)
    {
        const size_t SizeMatrix = 4;
        auto rot3 = rotation3(i_angle, i_axis);
        Matrix result(SizeMatrix);
        for (size_t row = 0; row < rot3.rows(); ++row)
            for (size_t column = 0; column < rot3.columns(); ++column)
                result[row][column] = rot3[row][column];
        return result;
    }
    
    Matrix translation(const Vector3d& i_bias)
    {
        static const size_t SizeMatrix = 4;
        Matrix result(SizeMatrix);
        size_t lastColumnIndex = SizeMatrix - 1;
        for (int i = 0; i < i_bias.SizeSpace_; ++i)
            result[i][lastColumnIndex] = i_bias[i];
        return result;
    }
    Matrix scale3(const Vector3d& i_scales)
    {
        static const size_t SizeMatrix = 3;
        Matrix result(SizeMatrix);
        for (size_t axis = 0; axis < SizeMatrix; ++axis)
            result[axis][axis] = i_scales[axis];
        return result;
    }
    Matrix scale4(const Vector3d& i_scales)
    {
        static const size_t SizeMatrix = 4;
        Matrix result(SizeMatrix);
        for (int axis = 0; axis < i_scales.SizeSpace_; ++axis)
            result[axis][axis] = i_scales[axis];
        return result;
    }
    Matrix scale3(double i_scaleX, double i_scaleY, double i_scaleZ)
    {
        return scale3(Math_NS::Vector3d({
            i_scaleX, i_scaleY, i_scaleZ
        }));
    }
    Matrix scale4(double i_scaleX, double i_scaleY, double i_scaleZ)
    {
        return scale4(Math_NS::Vector3d({
            i_scaleX, i_scaleY, i_scaleZ
        }));
    }
    Vector3d pointTransform(const Matrix& i_matrix,
                            const Vector3d& i_point)
    {
        assert(i_matrix.rows() == CommonSizeSpace &&
               i_matrix.columns() == CommonSizeSpace);
        auto matrixPoint = i_matrix * Matrix(Vector<CommonSizeSpace, double>({
            i_point[Coordinates::X],
            i_point[Coordinates::Y],
            i_point[Coordinates::Z],
                    1.
        }), true);
        return Vector3d({
            matrixPoint(0)[0],
            matrixPoint(1)[0],
            matrixPoint(2)[0]
        });
    }
    Vector3d vectorTransform(const Matrix& i_matrix,
                             const Vector3d& i_vector)
    {
        assert(i_matrix.rows() == CommonSizeSpace &&
               i_matrix.columns() == CommonSizeSpace);
        auto matrixPoint = i_matrix * Matrix(Vector<CommonSizeSpace, double>({
            i_vector[Coordinates::X],
            i_vector[Coordinates::Y],
            i_vector[Coordinates::Z],
                    0.
        }), true);
        return Vector3d({
            matrixPoint(0)[0],
            matrixPoint(1)[0],
            matrixPoint(2)[0]
        });
    }
    
    std::ostream& operator<<(std::ostream& o_out, const Math_NS::Matrix& i_matrix)
    {
        for (size_t row = 0; row < i_matrix.rows(); ++row)
        {
            for (size_t column = 0; column < i_matrix.columns(); ++column)
                o_out << i_matrix[row][column] << ' ';
            o_out << std::endl;
        }
        return o_out;
    }
    bool inverse(const Matrix& i_matrix, Matrix* o_inverse)
    {
        if (i_matrix.rows() != i_matrix.columns())
            return false;
        auto size = i_matrix.rows();
        Matrix inv(size);
        Matrix copy = i_matrix;
        auto add = [](int i_from, 
                      int i_to, 
                      double i_coef,
                      Matrix& io_matrix)
        {
            for (size_t i = 0; i < io_matrix.columns(); ++i)
            {
                io_matrix[i_to][i] += io_matrix[i_from][i] * i_coef;
            }
        };
        auto norm = [](int i_row, Matrix& io_matrix)
        {
            double coef = 1. / io_matrix[i_row][i_row];
            for (size_t i = 0; i < io_matrix.columns(); ++i)
                io_matrix[i_row][i] *= coef;
            return coef;
        };
        auto zero = [](double i_value)
        {
            return std::abs(i_value) < 
                            std::numeric_limits<double>::epsilon();
        };
        for (size_t step = 0; step < size; ++step)
        {
            bool isNull = true;
            for (size_t row = step; row < size; ++row)
            {
                if (zero(copy[row][step]))
                    continue;
                isNull = false;
                std::swap(copy[row], copy[step]);
                std::swap(inv[row], inv[step]);
                break;
            }
            if (isNull)
                return false;
            auto coef = norm(step, copy);
            for (auto& el : inv[step])
                el *= coef;
            for (size_t row = step + 1; row < size; ++row)
            {
                add(step, row, -copy[row][step], inv);
                add(step, row, -copy[row][step], copy);
            }
        }
        for (int step = size - 1; step >= 0; --step)
        {
            for (int row = step - 1; row >= 0; --row)
            {
                add(step, row, -copy[row][step], inv);
                add(step, row, -copy[row][step], copy);
            }
        }

        if (o_inverse)
            *o_inverse = inv;
        return true;
    }

    bool Matrix::operator!=(const Matrix& i_matrix) const
    {
        if (i_matrix.rows() != rows() || i_matrix.columns() != columns())
            return true;
        for (size_t row = 0; row < rows(); ++row)
            for (size_t column = 0; column < columns(); ++column)
                if (std::abs(d_values[row][column] - 
                             i_matrix[row][column]) >
                    std::numeric_limits<double>::epsilon())
                    return true;
        return false;
    }
    bool Matrix::operator==(const Matrix& i_matrix) const
    {
        return !(*this != i_matrix);
    }

    Matrix rotationByAxis(double i_angle, const Vector3d& i_axis)
    {
        auto c = cos(i_angle);
        auto s = sin(i_angle);
        auto x = i_axis.norm()[Coordinates::X];
        auto y = i_axis.norm()[Coordinates::Y];
        auto z = i_axis.norm()[Coordinates::Z];
        return Matrix({
            { c + (1 - c) * x * x, (1 - c) * x * y - s * z,
                                   (1 - c) * x * z + s * y },

            { (1 - c) * y * x + s * z, c + (1 - c) * y * y,
                                       (1 - c) * y * z - s * x },

            { (1 - c) * z * z - s * y, (1 - c) * z * y + s * x,
                                       c + (1 - c) * z * z }
        });
    }

    void rotateVector(
        double i_angle,
        const Vector3d& i_axis,
        Vector3d& io_point)
    {
        auto rotationMatrix = rotationByAxis(i_angle, i_axis);
        auto resultRotate = rotationMatrix * 
                            Matrix(io_point.vectorValues(), 3, 1);
        io_point = Vector3d({
            resultRotate[0][0],
            resultRotate[1][0],
            resultRotate[2][0]
        });
    }

}