#include "ShaderDisplayer.hpp"

void ShaderDisplayer::Start()
{
    if (!once)
    {
        layers = HgWAddDoubleLayer(0);
        once = true;
    }
    shaderTimeFitter = 0;
    isFirstRendering = true;
}

void ShaderDisplayer::FlameUpdate()
{
    using namespace std::chrono;

    hiddenLayerID = HgLSwitch(&layers);
    HgLCopy(layers.hidden, layers.display);

    shaderTime = *t * (double)GetShaderSpeed() - shaderTimeFitter;

    //Shaderの計算をする
    for (int x = 0; x < GetPixCount(); x++)
    {
        for (int y = 0; y < GetPixCount(); y++)
        {
            PixUpdate(x, y);
            PixRender(x, y);
        }
    }

    isFirstRendering = false;
}

void ShaderDisplayer::PixUpdate(int x, int y)
{
    //UV座標の計算
    uv.SetAll((double)x / GetPixCount(), (double)y / GetPixCount());
    //Shaderの計算
    colors[1][x][y] = shaderFuncs[shaderFuncsIndex](uv, shaderTime);
}

void ShaderDisplayer::PixRender(int x, int y)
{
    //前回と比べてピクセルの色が変わったかどうか
    if (isFirstRendering || colors[1][x][y] != colors[0][x][y])
    {
        colors[0][x][y] = colors[1][x][y];

        //色を設定してレンダリングする
        HgWSetFillColor(hiddenLayerID, colors[1][x][y].ToHGColor());
        HgWBoxFill(hiddenLayerID, (double)x * pixSize, (double)y * pixSize, pixSize, pixSize, 0);
    }
}

void ShaderDisplayer::IncreasePixCount()
{
    SetPixCount(FindDivisibleNum(WINDOW_SIZE, GetPixCount() + 1, true));
}

void ShaderDisplayer::DecreasePixCount()
{
    SetPixCount(FindDivisibleNum(WINDOW_SIZE, GetPixCount() - 1, false));
}

int ShaderDisplayer::GetPixCount()
{
    return pixCount;
}

float ShaderDisplayer::GetShaderSpeed()
{
    return shaderSpeed;
}

void ShaderDisplayer::SetShaderSpeed(float speed)
{
    shaderTimeFitter = (*t * speed) - shaderTime;
    shaderSpeed = speed;
}

void ShaderDisplayer::SetPixCount(int pixCount)
{
    isFirstRendering = true;

    pixCount = clamp(pixCount, MIN_PIX_COUNT, WINDOW_SIZE);

    //TODO:確保済みのメモリは削除させないようにする
    //前に使ってたメモリを消す
    if (&colors[0][0] != nullptr)
    {
        for (int i = 0; i < GetPixCount(); i++)
        {
            delete[] colors[0][i];
            delete[] colors[1][i];
        }
        delete[] colors[0];
        delete[] colors[1];
    }

    //メモリを確保する
    colors[0] = new vec4 *[pixCount];
    for (int i = 0; i < pixCount; i++)
        colors[0][i] = new vec4[pixCount];
    colors[1] = new vec4 *[pixCount];
    for (int i = 0; i < pixCount; i++)
        colors[1][i] = new vec4[pixCount];

    this->pixCount = pixCount;
    pixSize = (double)WINDOW_SIZE / (double)pixCount;
}

int ShaderDisplayer::FindDivisibleNum(int value, int start, bool isNextNum)
{
    int i = start;
    for (; i < value; i += isNextNum ? 1 : -1)
        if (value % i == 0)
            break;
    return i;
}

int ShaderDisplayer::GetShaderFuncsSize()
{
    return shaderFuncsSize;
}

int ShaderDisplayer::GetShaderFuncsIndex()
{
    return shaderFuncsIndex;
}

void ShaderDisplayer::SetShaderFuncsIndex(int index)
{
    isFirstRendering = true;

    index = clamp(index, 0, shaderFuncsSize);
    shaderFuncsIndex = index;
}

double ShaderDisplayer::GetPixUpdateDeltaTime()
{
    return pixUpdateDeltaTime;
}

double ShaderDisplayer::GetPixRenderDeltaTime()
{
    return pixRenderDeltaTime;
}