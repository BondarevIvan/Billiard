#pragma once
#include "Vector.h"

#include <unordered_map>
#include <memory>

namespace Math_NS
{
    static const int CommonSizeSpace = 4;
    class Matrix
    {
    public:
        template<int SizeSpace>
        Matrix(const Vector<SizeSpace, double>& i_point,
               bool i_isColumn = true);
        template<int SizeSpace>
        Matrix(const std::vector<Vector<SizeSpace, double>>& i_rows);
        Matrix(size_t i_rows, size_t i_columns);
        // identity
        Matrix(size_t i_sizeSide);
        Matrix(const std::vector<std::vector<double>>& i_values);
        Matrix(const std::vector<double>& i_values,
               size_t i_rows, 
               size_t i_columns);

        Matrix(const Matrix&) = default;

        const std::vector<double>& operator[](int i_id) const;
        std::vector<double>& operator[](int i_id);

        const std::vector<double>& operator()(int i_id) const;
        std::vector<double>& operator()(int i_id);

        Matrix& operator*=(const Matrix& i_matrix);
        Matrix& operator+=(const Matrix& i_matrix);
        Matrix& operator-=(const Matrix& i_matrix);

        Matrix operator+(const Matrix& i_matrix) const;
        Matrix operator-(const Matrix& i_matrix) const;
        Matrix operator*(const Matrix& i_matrix) const;

        size_t rows() const;
        size_t columns() const;

        bool operator!=(const Matrix& i_matrix) const;
        bool operator==(const Matrix& i_matrix) const;
    private:
        std::vector<std::vector<double>> d_values;
    };

    template<int SizeSpace>
    Matrix::Matrix(const Vector<SizeSpace, double>& i_point, bool i_isColumn)
    {
        if (i_isColumn)
            d_values = std::vector<std::vector<double>>(SizeSpace, std::vector<double>(1));
        else
            d_values = std::vector<std::vector<double>>(1, std::vector<double>(SizeSpace));
        for(int i = 0; i != SizeSpace; ++i)
        {
            if (i_isColumn)
            {
                d_values[i][0] = i_point[i];
            } else
            {
                d_values[0][i] = i_point[i];
            }
        }
    }

    template<int SizeSpace>
    Matrix::Matrix(const std::vector<Vector<SizeSpace, double>>& i_rows)
    {
        for (const auto& row : i_rows)
        {
            d_values.push_back({
                row.values().begin(), row.values().end()
            });
        }
    }


    enum EAxis
    {
        EA_X,
        EA_Y,
        EA_Z,
        EA_Count
    };
    

    Matrix rotation3(double i_angle, EAxis i_axis);
    Matrix rotation4(double i_angle, EAxis i_axis);
    Matrix translation(const Vector3d& i_bias);

    Matrix scale3(const Vector3d& i_scales);
    Matrix scale4(const Vector3d& i_scales);

    Matrix scale3(double i_scaleX, double i_scaleY, double i_scaleZ);
    Matrix scale4(double i_scaleX, double i_scaleY, double i_scaleZ);

    Vector3d pointTransform(const Matrix& i_matrix,
                            const Vector3d& i_point);
    Vector3d vectorTransform(const Matrix& i_matrix,
                             const Vector3d& i_vector);
    std::ostream& operator<<(std::ostream& o_out,
                             const Math_NS::Matrix& i_matrix);
    bool inverse(const Matrix& i_matrix, Matrix* o_inverse = nullptr);

    Matrix rotationByAxis(double i_angle, const Vector3d& i_axis);

    void rotateVector(
        double i_angle,
        const Vector3d& i_axis,
        Vector3d& io_point);

    static const Matrix Identity4 = Matrix(4);
    static const Matrix Identity3 = Matrix(3);
}