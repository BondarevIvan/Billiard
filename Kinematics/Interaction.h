#pragma once
#include "GameObjects.h"

namespace Kinematics_NS
{
    bool isCollision(const Ball2D& i_ball1, const Ball2D& i_ball2);
    int isCollision(const Table2D& i_table, Ball2D& i_ball);
    void collisionBalls(Ball2D& i_ball1, Ball2D& i_ball2);
    void collisionWithTable(const Table2D& i_table, Ball2D& i_ball);
    void tick(Game& io_game);
    void moveBall(Ball2D& io_ball);
}