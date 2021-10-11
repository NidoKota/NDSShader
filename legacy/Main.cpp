#include "Main.hpp"

std::chrono::system_clock::time_point sT, eT;
std::string updatePixSS;
double t = 0;
double prevT = 0;
double deltaTime = 0;
double sleepTime = 0;
bool isFPSLimitEnabled = true;
bool isPraying = true;

Delegate flameUpdateDelegate = Delegate();
FPSCounter fpsCounter = FPSCounter(&t, 0.5f);
RenderManager renderManager = RenderManager(&t, CircleShader, RainbowCircleShader, HeartShader, WaveShader, RotationShapesShader, LoadingShader, SpaceShader, BlockShader);
InputManager inputManager = InputManager(HG_U_ARROW, HG_D_ARROW, HG_R_ARROW, HG_L_ARROW, 'q', 'f', 'r', ' ', ',', '.');
DoubleLayerDisplayer infoDisplayer = DoubleLayerDisplayer([](int layerID)
    {
        HgWSetFont(layerID, HG_HB, 15);
        HgWSetColor(layerID, vec4(0.5).ToHGColor());
        HgWText(layerID, 0, WINDOW_SIZE - 15, "FPS : %5.1f", fpsCounter.GetFPS());
    });

int main()
{
    using namespace std::chrono;

    vec4 v = vec4(0.1, 0.2, 0.3, 0.4);
    hgcolor hgc = v.ToHGColor();
    std::cout << v << " -> " << std::hex << hgc << std::endl
              << std::dec;
    //std::cout << hgcolorToRGBA(hgc) << std::endl;
    std::cout << std::hex << (hgc & 0xFF000000) << std::endl;
    std::cout << std::hex << (hgc & 0xFF000000 >> 8) << std::endl;

    HgOpen(WINDOW_SIZE, WINDOW_SIZE);
    //イベントの購読
    fpsCounter.Subscribe(flameUpdateDelegate);
    inputManager.Subscribe(flameUpdateDelegate);
    renderManager.Subscribe(flameUpdateDelegate);
    infoDisplayer.Subscribe(flameUpdateDelegate);

    while (isPraying)
    {
        //FlameUpdate開始前の時間を取得
        sT = system_clock::now();

        //FlameUpdateを呼ぶ
        flameUpdateDelegate.Invoke();
        MainFlameUpdate();

        //DeltaTimeを計算
        deltaTime = duration_cast<milliseconds>(system_clock::now() - sT).count() / 1000.f;

        //FPS数制限が設定されている時
        if (isFPSLimitEnabled)
        {
            //TARGET_FPSが実現した時のdeltaTimeと比べて、Threadを止める時間を決める
            double targetDeltaTime = 1. / (double)TARGET_FPS;
            sleepTime = targetDeltaTime - deltaTime;
            sleepTime = 0 > sleepTime ? 0 : targetDeltaTime < sleepTime ? targetDeltaTime
                                                                        : sleepTime;
            HgSleep(sleepTime);
        }
        else
            sleepTime = 0;

        t += deltaTime + sleepTime;
    }

    return 0;
}

void MainFlameUpdate()
{
    //InputManagerから取得したキー入力によって何をするのか決める
    int shaderIndex = renderManager.GetShaderFuncsIndex();
    int shaderSize = renderManager.GetShaderFuncsSize();
    if (inputManager.GetKeyDown(HG_U_ARROW))
        renderManager.IncreasePixCount();
    if (inputManager.GetKeyDown(HG_D_ARROW))
        renderManager.DecreasePixCount();
    if (inputManager.GetKeyDown(HG_R_ARROW))
        renderManager.SetShaderFuncsIndex(shaderIndex + 1 > shaderSize - 1 ? 0 : shaderIndex + 1);
    if (inputManager.GetKeyDown(HG_L_ARROW))
        renderManager.SetShaderFuncsIndex(shaderIndex - 1 < 0 ? shaderSize - 1 : shaderIndex - 1);
    if (inputManager.GetKeyDown('q'))
        isPraying = false;
    if (inputManager.GetKeyDown('f'))
        isFPSLimitEnabled = !isFPSLimitEnabled;
    if (inputManager.GetKeyDown(' '))
        infoDisplayer.SetActive(!infoDisplayer.GetActive());
    if (inputManager.GetKeyDown(','))
        renderManager.SetShaderSpeed(clamp((float)renderManager.GetShaderSpeed() - 0.25f, 0.f, 10.f));
    if (inputManager.GetKeyDown('.'))
        renderManager.SetShaderSpeed(clamp((float)renderManager.GetShaderSpeed() + 0.25f, 0.f, 10.f));
    if (inputManager.GetKeyDown('r'))
    {
        t = 0;
        renderManager.Start();
        fpsCounter.Start();
    }
}