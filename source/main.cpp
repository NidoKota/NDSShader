#include "main.hpp"

double t = 0;
double deltaTime = 0;
uint16 *frameBuffer = (uint16 *)0x06800000;
Delegate updateDelegate = Delegate();
RenderManager renderManager = RenderManager(&t, frameBuffer, RainbowCircleShader, HeartShader, WaveShader, RotationShapesShader, LoadingShader, SpaceShader, BlockShader);
FPSCounter fpsCounter = FPSCounter(&t, 0.5f);
std::chrono::system_clock::time_point sT, eT;
std::stringstream ss;

int main(void)
{
    consoleDemoInit();
    powerOn(POWER_ALL);
    videoSetMode(MODE_FB0);
    vramSetBankA(VRAM_A_LCD);

    renderManager.Subscribe(updateDelegate);
    fpsCounter.Subscribe(updateDelegate);

    while (1)
    {
        using namespace std::chrono;
        //sT = system_clock::now();

        swiWaitForVBlank();
        scanKeys();

        updateDelegate.Invoke();

        int shaderIndex = renderManager.GetShaderFuncsIndex();
        int shaderSize = renderManager.GetShaderFuncsSize();

        if (keysDown() & KEY_A)
        {
            renderManager.SetShaderFuncsIndex(shaderIndex + 1 > shaderSize - 1 ? 0 : shaderIndex + 1);
            iprintf("\x1b[%d;%dH%s", 0, 0, "A");
        }
        else if (keysDown() & KEY_B)
        {
            renderManager.SetShaderFuncsIndex(shaderIndex - 1 < 0 ? shaderSize - 1 : shaderIndex - 1);
            iprintf("\x1b[%d;%dH%s", 0, 0, "B");
        }
        else if (keysDown() & KEY_UP)
        {
            renderManager.SetPixCount(
                renderManager.GetPixWidthCount() + (int)(SCREEN_WIDTH / 15),
                renderManager.GetPixHeightCount() + (int)(SCREEN_HEIGHT / 15));

            iprintf("\x1b[%d;%dH%s", 0, 0, "UP");
        }
        else if (keysDown() & KEY_DOWN)
        {
            renderManager.SetPixCount(
                renderManager.GetPixWidthCount() - (int)(SCREEN_WIDTH / 15),
                renderManager.GetPixHeightCount() - (int)(SCREEN_HEIGHT / 15));

            iprintf("\x1b[%d;%dH%s", 0, 0, "DOWN");
        }

        ss << "Time " << t << "\nDTime " << deltaTime << "\nFPS " << fpsCounter.GetFPS();
        iprintf("\x1b[%d;%dH%s", 1, 0, ss.str().c_str());
        ss.str("");

        deltaTime = 0.5; //duration_cast<milliseconds>(system_clock::now() - sT).count() / 1000.0;
        t += deltaTime;
    }
    return 0;
}