#include "GameObjects.h"

namespace Kinematics_NS
{
    Ball2D::Ball2D(
        const Math_NS::Vector2d& i_position,
        const Math_NS::Vector2d& i_move)
        : d_position(i_position)
        , d_move(i_move)
    {
    }

    Math_NS::Vector2d& Ball2D::position()
    {
        return d_position;
    }

    const Math_NS::Vector2d& Ball2D::position() const
    {
        return d_position;
    }

    Math_NS::Vector2d& Ball2D::move()
    {
        return d_move;
    }

    const Math_NS::Vector2d& Ball2D::move() const
    {
        return d_move;
    }

    Table2D::Table2D(
        const Math_NS::Vector2d& i_firstAngle,
        const Math_NS::Vector2d& i_secondAngle)
        : d_leftDown(i_firstAngle)
        , d_rightUp(i_secondAngle)
    {
        for (int axis = 0; axis < d_leftDown.SizeSpace_; ++axis)
        {
            const auto firstCoordinate = d_leftDown[axis];
            const auto secondCoordinate = d_rightUp[axis];
            d_leftDown[axis] = std::min(firstCoordinate, secondCoordinate);
            d_rightUp[axis] = std::max(firstCoordinate, secondCoordinate);
        }
    }
    
    const Math_NS::Vector2d& Table2D::leftDown() const
    {
        return d_leftDown;
    }

    const Math_NS::Vector2d& Table2D::rightUp() const
    {
        return d_rightUp;
    }

    int Table2D::positionPoint(const Math_NS::Vector2d& i_point) const
    {
        int position = 0;
        if (i_point[0] < d_leftDown[0])
            position |= PositionPointAboutRect::OnLeft;
        if (i_point[0] > d_rightUp[0])
            position |= PositionPointAboutRect::OnRight;
        if (i_point[1] < d_leftDown[1])
            position |= PositionPointAboutRect::Below;
        if (i_point[1] > d_rightUp[1])
            position |= PositionPointAboutRect::Higher;
        return position;
    }

    std::vector<Ball2D>& Game::balls()
    {
        return d_balls;
    }

    const std::vector<Ball2D>& Game::balls() const
    {
        return d_balls;
    }

    Table2D& Game::table()
    {
        return d_table;
    }

    const Table2D& Game::table() const
    {
        return d_table;
    }

}