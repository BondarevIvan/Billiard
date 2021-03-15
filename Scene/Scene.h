#pragma once
#include "Thing3D.h"

#include <Kinematics/GameObjects.h>

namespace Scene_NS
{
    class Scene : public Thing3D
    {
    public:
        Scene() = delete;
        Scene(double i_widthTable, double i_heightTable);
        Kinematics_NS::Game& game();
    private:
        Kinematics_NS::Game d_game;
    };
}