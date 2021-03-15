#include "Interaction.h"

#include <functional>

namespace
{
    const double RadiusBallSqr = Kinematics_NS::RadiusBall * Kinematics_NS::RadiusBall;
    const double DiamBallSqr = Kinematics_NS::DiamBall * Kinematics_NS::DiamBall;
}

namespace Kinematics_NS
{
    bool isCollision(const Ball2D& i_ball1, const Ball2D& i_ball2)
    {
        return (i_ball1.position() - i_ball2.position()).modSqr() < DiamBallSqr;
    }

    int isCollision(const Table2D& i_table, Ball2D& i_ball)
    {
        const auto DiagonalBBox = Math_NS::Vector2d({ RadiusBall, RadiusBall });
        return i_table.positionPoint(i_ball.position() - DiagonalBBox) |
               i_table.positionPoint(i_ball.position() + DiagonalBBox);
    }

    void recalculateDirection(Ball2D& i_ball1, Ball2D& i_ball2)
    {
        if (!isCollision(i_ball1, i_ball2))
            return;
        const auto ox = (i_ball2.position() - i_ball1.position()).normalize();
        const auto projX1 = i_ball1.move() * ox;
        const auto projX2 = i_ball2.move() * ox;
        i_ball1.move() += ox * (projX2 - projX1);
        i_ball2.move() += ox * (projX1 - projX2);
    }

    void pushAway(Ball2D& i_ball1, Ball2D& i_ball2)
    {
        const double Eps = 0.000001;
        const auto dir12 = (i_ball2.position() - i_ball1.position()).normalize();
        const auto dir21 = -dir12;
        const auto collisionDist = (i_ball2.position() - i_ball1.position()).mod() - DiamBall;
        if (collisionDist > 0)
            return;
        i_ball1.position() += dir12 * (collisionDist / 2);
        i_ball2.position() += dir21 * (collisionDist / 2);
    }

    void collisionBalls(Ball2D& i_ball1, Ball2D& i_ball2)
    {
        recalculateDirection(i_ball1, i_ball2);
        pushAway(i_ball1, i_ball2);
    }

    using Checker = std::function<bool(const Math_NS::Vector2d&)>;

    void shake(
        Math_NS::Vector2d& io_point, 
        const Checker& i_checker,
        const Math_NS::Vector2d& i_direction,
        double i_leftOfRange, double i_rightOfRange)
    {
        double left = i_leftOfRange;
        double right = i_rightOfRange;
        const auto translation = [=](double length)
        {
            return io_point + i_direction * length;
        };
        static const auto Eps = 0.00001;
        while (right - left > Eps)
        {
            auto middle = (left + right) / 2;
            const auto newPosition = translation(middle);
            if (i_checker(newPosition))
                right = middle;
            else
                left = middle;
        }
        io_point = translation(right);
    }

    void changeDirection(const Table2D& i_table, Ball2D& i_ball)
    {
        const Math_NS::Vector2d diag({ 
            Kinematics_NS::RadiusBall,
            Kinematics_NS::RadiusBall });
        int collisionType = 0;
        collisionType |= i_table.positionPoint(i_ball.position() - diag);
        collisionType |= i_table.positionPoint(i_ball.position() + diag);        
        if (collisionType & PositionPointAboutRect::UpDown)
            i_ball.move()[1] *= -1;
        if (collisionType & PositionPointAboutRect::LeftRight)
            i_ball.move()[0] *= -1;
    }

    void collisionWithTable(const Table2D& i_table, Ball2D& i_ball)
    {
        changeDirection(i_table, i_ball);
        std::unordered_map<PositionPointAboutRect, Math_NS::Vector2d> ShakeDirs = {
            { PositionPointAboutRect::Below, Math_NS::Vector2d({ 0, 1 }) },
            { PositionPointAboutRect::Higher, Math_NS::Vector2d({ 0, -1 }) },
            { PositionPointAboutRect::OnLeft, Math_NS::Vector2d({ 1, 0 }) },
            { PositionPointAboutRect::OnRight, Math_NS::Vector2d({ -1, 0 }) }
        };
        const Math_NS::Vector2d diag({ 
            Kinematics_NS::RadiusBall,
            Kinematics_NS::RadiusBall });
        const auto resolveCollision = [&](PositionPointAboutRect conflict, double dirDiag)
        {
            shake(i_ball.position(), [=](const Math_NS::Vector2d& pos)
            {
                return !(i_table.positionPoint(pos + diag * dirDiag) & conflict);
            }, ShakeDirs[conflict], 0., DiamBall);
        };
        resolveCollision(PositionPointAboutRect::Below, -1);
        resolveCollision(PositionPointAboutRect::Higher, 1);
        resolveCollision(PositionPointAboutRect::OnLeft, -1);
        resolveCollision(PositionPointAboutRect::OnRight, 1);
    }

    void moveBall(Ball2D& io_ball)
    {
        io_ball.position() += io_ball.move();
    }

    void tick(Game& io_game)
    {
        auto& balls = io_game.balls();

        for (auto& ball : balls)
            moveBall(ball);

        for (size_t ball1 = 0; ball1 < balls.size(); ++ball1)
            for (size_t ball2 = ball1 + 1; ball2 < balls.size(); ++ball2)
                collisionBalls(balls[ball1], balls[ball2]);

        for (auto& ball : balls)
            collisionWithTable(io_game.table(), ball);
    }

}