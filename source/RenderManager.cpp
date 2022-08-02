#include "RenderManager.hpp"

void RenderManager::Start()
{
    shaderTimeFitter = 0;
}

void RenderManager::FlameUpdate()
{
    shaderTime = *t * (double)GetShaderSpeed() - shaderTimeFitter;

    //Shaderの計算をする
    for (int y = 0; y < pixHeightCount; y++)
    {
        for (int x = 0; x < pixWidthCount; x++)
            PixUpdate(x, y);
    }

    /*float widthMul = SCREEN_WIDTH / pixWidthCount;
    float heightMul = SCREEN_HEIGHT / pixHeightCount;

    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            vec4 color = colors
                [(int)clamp(x / widthMul, 0.f, (float)pixWidthCount)]
                [(int)clamp(y / heightMul, 0.f, (float)pixHeightCount)];

            frameBuffer[x + y * SCREEN_WIDTH] = RGB15((int)(color.x * 31), (int)(color.y * 31), (int)(color.z * 31));
        }
    }*/

    renderCount = renderCount >= 3 ? renderCount : renderCount + 1;
}

void RenderManager::PixUpdate(int x, int y)
{
    //UV座標の計算
    uv.SetAll((double)x / pixWidthCount, 1 - ((double)y / pixHeightCount));

    //Shaderの計算
    colors[x][y] = shaderFuncs[shaderFuncsIndex](uv, shaderTime);

    vec4 color = colors [x][y];
    frameBuffer[x + y * SCREEN_WIDTH] = RGB15((int)(color.x * 30), (int)(color.y * 30), (int)(color.z * 30));
}

float RenderManager::GetShaderSpeed()
{
    return shaderSpeed;
}

void RenderManager::SetShaderSpeed(float speed)
{
    shaderTimeFitter = (*t * speed) - shaderTime;
    shaderSpeed = speed;
}

void RenderManager::SetPixCount(int width, int height)
{
    if (renderCount != 0)
    {
        //TODO:確保済みのメモリは削除させないようにする
        //前に使ってたメモリを消す
        if (colors[0] != nullptr)
        {
            for (int x = 0; x < pixWidthCount; x++)
            {
                delete[] colors[x];
            }
            delete[] colors;
        }

        pixWidthCount = clamp(width, (int)(SCREEN_WIDTH / 15), SCREEN_WIDTH);
        pixHeightCount = clamp(height, (int)(SCREEN_HEIGHT / 15), SCREEN_HEIGHT);

        //メモリを確保する
        colors = new vec4 *[pixWidthCount];
        for (int x = 0; x < pixWidthCount; x++)
            colors[x] = new vec4[pixHeightCount];

        renderCount = 0;
    }
}

int RenderManager::GetPixWidthCount()
{
    return pixWidthCount;
}

int RenderManager::GetPixHeightCount()
{
    return pixHeightCount;
}

int RenderManager::GetShaderFuncsSize()
{
    return shaderFuncsSize;
}

int RenderManager::GetShaderFuncsIndex()
{
    return shaderFuncsIndex;
}

void RenderManager::SetShaderFuncsIndex(int index)
{
    if (renderCount != 0)
    {
        index = clamp(index, 0, shaderFuncsSize);
        shaderFuncsIndex = index;

        renderCount = 0;
    }
}