#include <Kinematics/Interaction.h>
#include <GL/glut.h>
#include <random>
#include <array>

Kinematics_NS::Game game;

const int ScreenWidth = 800;
const int ScreenHeight = 400;
const double Speed = 50;

void drawBall(const Kinematics_NS::Ball2D& ball,
              const std::array<double, 3>& color)
{
    glBegin(GL_LINE_LOOP);
    glColor3d(color[0], color[1], color[2]);
    int size = 30;
    for (int i = 0; i < 30; ++i)
    {
        const double angle = (i * M_PI * 2) / 30;
        const auto pos = ball.position() + 
            Math_NS::Vector2d({ cos(angle), sin(angle) }) * Kinematics_NS::RadiusBall;
        glVertex2d(pos[0], pos[1]);
        //std::cout << pos[0] << ' ' << pos[1] << std::endl;
    }
    glEnd();
}

Math_NS::Vector2d randomVector(double max)
{
    static std::mt19937 gen(time(0));
    std::uniform_real_distribution<> urd(-max, max);
    return Math_NS::Vector2d({ urd(gen), urd(gen) });
}

Kinematics_NS::Ball2D createRandomBall(const Kinematics_NS::Table2D& table)
{
    Kinematics_NS::Ball2D ball;
    ball.position() = randomVector((table.rightUp())[1]);
    ball.move() = randomVector(0.009);
    return ball;
}

void init()
{
    auto& balls = game.balls();
    for (int i = 0; i < 8; ++i)
    {
        bool collision = false;
        Kinematics_NS::Ball2D ball;
        do
        {
            collision = false;
            ball = createRandomBall(game.table());
            for (int j = 0; j < i; ++j)
                collision |= Kinematics_NS::isCollision(balls[j], ball);
        } while (collision);
        balls.push_back(ball);        
    }
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    for (auto& ball : game.balls())
    {
        drawBall(ball, { 1, 1, 1 });
    }
    glutSwapBuffers();
}

void timer(int)
{
    draw();
    Kinematics_NS::tick(game);
    glutTimerFunc(Speed, timer, 0);
}

int main(int argc, char** argv)
{
    game.table() = Kinematics_NS::Table2D(Math_NS::Vector2d({-0.75, -0.375}),
                   Math_NS::Vector2d({0.75, 0.375}));
    init();

    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(ScreenWidth, ScreenHeight);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Simple Window");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    auto& table = game.table();
    glOrtho(
        table.leftDown()[0], table.rightUp()[0],
        table.rightUp()[1], table.leftDown()[1], -5, 5);

    glutDisplayFunc(draw);
    //glutPassiveMotionFunc(motionFunc);
    //glutMouseFunc(clickOnLeftMouse);
    glutTimerFunc(Speed, timer, 0);
    glutMainLoop();

    return 0;
}