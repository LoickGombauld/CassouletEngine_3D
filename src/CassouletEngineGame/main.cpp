
#include <CassouletEngineLibrarie/System/Test.h>
#include <CassouletEngineLibrarie/System/Game.h>

int main()
{
    Game game;
    game.Init();

    while (!game.IsOver())
    {
        game.ProcessInput();
        game.Update();
        game.Render();
    }
    return 0;

}
