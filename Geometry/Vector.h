#pragma once
#include <array>
#include <vector>
#include <cassert>
#include <cmath>
#include <iostream>

namespace Math_NS
{
    enum class Coordinates
    {
        X,
        Y,
        Z
    };

    template<int SizeSpace, class DoubleType>
    class Vector
    {
    public:
        const int SizeSpace_ = SizeSpace;
        using DoubleType_ = DoubleType;
        Vector() = default;
        Vector(const std::vector<DoubleType>& i_values);
        Vector(const Vector& i_vector);
        DoubleType& operator[](int i_id);
        DoubleType operator[](int i_id) const;

        DoubleType& operator[](Coordinates i_coordinate);
        DoubleType operator[](Coordinates i_coordinate) const;

        DoubleType operator*(const Vector& i_other) const;

        Vector& operator*=(DoubleType i_coef);
        Vector& operator/=(DoubleType i_coef);
        Vector& operator+=(DoubleType i_coef);
        Vector& operator-=(DoubleType i_coef);

        Vector& operator+=(const Vector& i_other);
        Vector& operator-=(const Vector& i_other);

        Vector operator*(DoubleType i_coef) const;
        Vector operator/(DoubleType i_coef) const;
        Vector operator+(DoubleType i_coef) const;
        Vector operator-(DoubleType i_coef) const;

        Vector operator+(const Vector& i_other) const;
        Vector operator-(const Vector& i_other) const;

        Vector& operator=(const Vector& i_vector);

        Vector& normalize();
        Vector norm() const;

        DoubleType modSqr() const;
        DoubleType mod() const;

        Vector operator-() const;
        
        template<class DType>
        operator Vector<SizeSpace, DType>() const
        {
            std::vector<DType> coordinates;
            coordinates.reserve(SizeSpace);
            for (auto coord : d_coordinates)
                coordinates.push_back(coord);
            return Vector<SizeSpace, DType>(coordinates);
        }

        const std::array<DoubleType, SizeSpace>& values() const;

        bool operator==(const Vector& i_other) const;
        bool operator!=(const Vector& i_other) const;
        std::vector<double> vectorValues() const;
    private:
        std::array<DoubleType, SizeSpace> d_coordinates;
    };

    template<int SizeSpace, class DoubleType>
    Vector<SizeSpace, DoubleType>::Vector(
        const std::vector<DoubleType>& i_values)
    {
        d_coordinates.fill(DoubleType{});
        for (size_t i = 0; i < i_values.size() && i < SizeSpace; ++i)
            d_coordinates[i] = i_values[i];
    }

    template<int SizeSpace, class DoubleType>
    Vector<SizeSpace, DoubleType>::Vector(const Vector& i_vector)
        : d_coordinates(i_vector.d_coordinates)
    {
    }

    template<int SizeSpace, class DoubleType>
    DoubleType& Vector<SizeSpace, DoubleType>::operator[](int i_id)
    {
        assert(i_id >= 0 && i_id < SizeSpace);
        return d_coordinates[i_id];
    }

    template<int SizeSpace, class DoubleType>
    DoubleType Vector<SizeSpace, DoubleType>::operator[](int i_id) const
    {
        assert(i_id >= 0 && i_id < SizeSpace);
        return d_coordinates[i_id];
    }

    template<int SizeSpace, class DoubleType>
    DoubleType& Vector<SizeSpace, DoubleType>::operator[](
        Coordinates i_coordinate)
    {
        return (*this)[int(i_coordinate)];
    }

    template<int SizeSpace, class DoubleType>
    DoubleType Vector<SizeSpace, DoubleType>::operator[](
        Coordinates i_coordinate) const
    {
        return (*this)[int(i_coordinate)];
    }


    template<int SizeSpace, class DoubleType>
    DoubleType Vector<SizeSpace, DoubleType>::operator*(
        const Vector& i_other) const
    {
        DoubleType sum{};
        for (int i = 0; i < SizeSpace; ++i)
            sum += i_other[i] * d_coordinates[i];
        return sum;
    }

    template<int SizeSpace, class DoubleType>
    Vector<SizeSpace, DoubleType>&
    Vector<SizeSpace, DoubleType>::operator*=(DoubleType i_coef)
    {
        for (auto& el : d_coordinates)
            el *= i_coef;
        return *this;
    }

    template<int SizeSpace, class DoubleType>
    Vector<SizeSpace, DoubleType>&
    Vector<SizeSpace, DoubleType>::operator/=(DoubleType i_coef)
    {
        assert(std::fabs(i_coef) >
                         std::numeric_limits<DoubleType>::epsilon());
        return *this *= (1. / i_coef);
    }

    template<int SizeSpace, class DoubleType>
    Vector<SizeSpace, DoubleType>&
    Vector<SizeSpace, DoubleType>::operator+=(DoubleType i_coef)
    {
        for (auto& el : d_coordinates)
            el += i_coef;
        return d_coordinates;
    }
    template<int SizeSpace, class DoubleType>
    Vector<SizeSpace, DoubleType>&
    Vector<SizeSpace, DoubleType>::operator-=(DoubleType i_coef)
    {
        return *this += (-i_coef);
    }

    template<int SizeSpace, class DoubleType>
    Vector<SizeSpace, DoubleType>&
    Vector<SizeSpace, DoubleType>::operator+=(const Vector& i_other)
    {
        for (int i = 0; i < SizeSpace; ++i)
            d_coordinates[i] += i_other[i];
        return *this;
    }

    template<int SizeSpace, class DoubleType>
    Vector<SizeSpace, DoubleType>&
    Vector<SizeSpace, DoubleType>::operator-=(const Vector& i_other)
    {
        for (int i = 0; i < SizeSpace; ++i)
            d_coordinates[i] -= i_other[i];
        return *this;
    }

    template<int SizeSpace, class DoubleType>
    Vector<SizeSpace, DoubleType>
    Vector<SizeSpace, DoubleType>::operator*(DoubleType i_coef) const
    {
        auto result = *this;
        return result *= i_coef;
    }

    template<int SizeSpace, class DoubleType>
    Vector<SizeSpace, DoubleType>
    Vector<SizeSpace, DoubleType>::operator/(DoubleType i_coef) const
    {
        auto result = *this;
        return result /= i_coef;
    }

    template<int SizeSpace, class DoubleType>
    Vector<SizeSpace, DoubleType>
    Vector<SizeSpace, DoubleType>::operator+(DoubleType i_coef) const
    {
        auto result = *this;
        return result += i_coef;
    }

    template<int SizeSpace, class DoubleType>
    Vector<SizeSpace, DoubleType>
    Vector<SizeSpace, DoubleType>::operator-(DoubleType i_coef) const
    {
        auto result = *this;
        return result -= i_coef;
    }

    template<int SizeSpace, class DoubleType>
    Vector<SizeSpace, DoubleType>
    Vector<SizeSpace, DoubleType>::operator+(const Vector& i_other) const
    {
        auto result = *this;
        return result += i_other;
    }

    template<int SizeSpace, class DoubleType>
    Vector<SizeSpace, DoubleType>
    Vector<SizeSpace, DoubleType>::operator-(const Vector& i_other) const
    {
        auto result = *this;
        return result -= i_other;
    }


    template<int SizeSpace, class DoubleType>
    Vector<SizeSpace, DoubleType>&
    Vector<SizeSpace, DoubleType>::normalize()
    {
        if (this->modSqr() < std::numeric_limits<double>::epsilon())
            return *this;
        return *this /= this->mod();
    }

    template<int SizeSpace, class DoubleType>
    Vector<SizeSpace, DoubleType>
    Vector<SizeSpace, DoubleType>::norm() const
    {
        if (this->modSqr() < std::numeric_limits<double>::epsilon())
            return *this;
        return *this / this->mod();
    }

    template<int SizeSpace, class DoubleType>
    DoubleType Vector<SizeSpace, DoubleType>::modSqr() const
    {
        return *this * *this;
    }

    template<int SizeSpace, class DoubleType>
    DoubleType Vector<SizeSpace, DoubleType>::mod() const
    {
        return sqrt(modSqr());
    }

    template<int SizeSpace, class DoubleType> 
    Vector<SizeSpace, DoubleType>& 
    Vector<SizeSpace, DoubleType>::operator=(const Vector<SizeSpace, DoubleType>& i_vector)
    {
        for (int i = 0; i < SizeSpace; ++i)
            d_coordinates[i] = i_vector[i];
        return *this;
    }


    using Vector3d = Vector<3, double>;
    using Vector3f = Vector<3, float>;
    using Vector3i = Vector<3, int>;
    using Vector2d = Vector<2, double>;
    using Vector2f = Vector<2, float>;
    using Vector2i = Vector<2, int>;
    
    template<class DoubleType1, class DoubleType2>
    Vector<3, DoubleType1> operator^(const Vector<3, DoubleType1>& i_left,
                                    const Vector<3, DoubleType2>& i_right)
    {
        const auto& ax = i_left[0], ay = i_left[1], az = i_left[2];
        const auto& bx = i_right[0], by = i_right[1], bz = i_right[2];
        return Vector<3, DoubleType1>({
            ay * bz - az * by,
            az * bx - ax * bz,
            ax * by - ay * bx
        });
    }

    template<int SizeSpace, class DoubleType>    
    Vector<SizeSpace, DoubleType>
    Vector<SizeSpace, DoubleType>::operator-() const
    {
        return *this * (-1.);
    }

    template<int SizeSpace, class DoubleType>
    const std::array<DoubleType, SizeSpace>&
    Vector<SizeSpace, DoubleType>::values() const
    {
        return d_coordinates;
    }

    template<class DoubleType>
    Vector<3, DoubleType> xAxis()
    {
        return Vector<3, DoubleType>({
            DoubleType(1.), DoubleType{}, DoubleType{}
        });
    }

    template<class DoubleType>
    Vector<3, DoubleType> yAxis()
    {
        return Vector<3, DoubleType>({
            DoubleType{}, DoubleType(1.), DoubleType{}
        });
    }

    template<class DoubleType>
    Vector<3, DoubleType> zAxis()
    {
        return Vector<3, DoubleType>({
            DoubleType{}, DoubleType{}, DoubleType(1.)
        });
    }

    template<int SizeSpace, class DoubleType>
    std::vector<double> Vector<SizeSpace, DoubleType>::vectorValues() const
    {
        return std::vector<double>(
            d_coordinates.begin(),
            d_coordinates.end());
    }

    template<int SizeSpace, class DoubleType>
    bool Vector<SizeSpace, DoubleType>::operator==(
        const Vector<SizeSpace, DoubleType>& i_other) const
    {
        return (*this - i_other).modSqr() <
                std::numeric_limits<DoubleType_>::epsilon();
    }

    template<int SizeSpace, class DoubleType>
    bool Vector<SizeSpace, DoubleType>::operator!=(
        const Vector<SizeSpace, DoubleType>& i_other) const
    {
        return !(*this == i_other);
    }

    template<int SizeSpace, class DoubleType>
    bool isCollinear(
        const Vector<SizeSpace, DoubleType>& i_first,
        const Vector<SizeSpace, DoubleType>& i_second)
    {
        const auto unitFirst = i_first.norm();
        const auto unitSecond = i_second.norm();
        if (unitFirst == Vector<SizeSpace, DoubleType>{})
            return true;
        if (unitSecond == Vector<SizeSpace, DoubleType>{})
            return true;
        return unitFirst == unitSecond || unitSecond == -unitFirst;
    }

    template<int SizeSpace, class DoubleType>
    bool isOrthogonal(
        const Vector<SizeSpace, DoubleType>& i_first,
        const Vector<SizeSpace, DoubleType>& i_second)
    {
        return std::abs(i_first * i_second) < std::numeric_limits<double>::epsilon();
    }

}