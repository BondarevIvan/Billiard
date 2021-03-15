#include "Scene.h"

namespace Scene_NS
{
    Scene::Scene(double i_widthTable, double i_heightTable)
    {
        const Math_NS::Vector2d leftDown({
            -i_widthTable / 2,
            -i_heightTable / 2
        });
        const auto rightUp = -leftDown;
        d_game.table() = Kinematics_NS::Table2D{ leftDown, rightUp };
    }
    Kinematics_NS::Game& Scene::game()
    {
        return d_game;
    }
}