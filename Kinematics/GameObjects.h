#pragma once
#include <Geometry/Vector.h>

namespace Kinematics_NS
{
    static const double OneMillimeter = 0.001;
    static const double DiamBall = 68 * OneMillimeter;
    static const double RadiusBall = DiamBall / 2;
    class Ball2D
    {
    public:
        Ball2D() = default;
        Ball2D(
            const Math_NS::Vector2d& i_position,
            const Math_NS::Vector2d& i_move);
        Ball2D(const Ball2D&) = default;

        Math_NS::Vector2d& position();
        const Math_NS::Vector2d& position() const;

        Math_NS::Vector2d& move();
        const Math_NS::Vector2d& move() const;
    private:
        Math_NS::Vector2d d_position;
        Math_NS::Vector2d d_move;
    };

    enum PositionPointAboutRect
    {
        In = 0,
        Higher  = 1 << 0,
        Below   = 1 << 1,
        OnLeft  = 1 << 2,
        OnRight = 1 << 3
    };

    class Table2D
    {
    public:
        Table2D() = default;
        Table2D(
            const Math_NS::Vector2d& i_firstAngle,
            const Math_NS::Vector2d& i_secondAngle);
        Table2D(const Table2D&) = default;
        const Math_NS::Vector2d& leftDown() const;
        const Math_NS::Vector2d& rightUp() const;
        int positionPoint(const Math_NS::Vector2d& i_point) const;
    private:
        Math_NS::Vector2d d_leftDown;
        Math_NS::Vector2d d_rightUp;
    };

    class Game
    {
    public:
        Game() = default;
        std::vector<Ball2D>& balls();
        const std::vector<Ball2D>& balls() const;
        Table2D& table();
        const Table2D& table() const;
    private:
        std::vector<Ball2D> d_balls;
        Table2D d_table;
    };

}