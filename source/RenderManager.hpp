#pragma once

#include "../include/SrcInclude.hpp"

//シェーダーを表示する
struct RenderManager : public EventHandler
{
    using Func = vec4 (*)(vec4, float);

private:
    std::vector<Func> shaderFuncs;
    uint16 *frameBuffer;
    vec4 **colors;
    vec4 uv;
    double *t;
    double shaderTime;
    double shaderTimeFitter;
    float shaderSpeed;
    int shaderFuncsSize;
    int shaderFuncsIndex;
    int renderCount;
    int pixWidthCount;
    int pixHeightCount;

    void FlameUpdate() override;
    void PixUpdate(int x, int y);

    template <typename First, typename... Rest>
    void RoundUp(const First &first, const Rest &...rest)
    {
        shaderFuncs.push_back(first);
        RoundUp(rest...);
    }

    void RoundUp() {}

public:
    //経過時間が入った変数のポインタと、シェーダー関数のポインタを登録
    //シェーダー関数に対して、UV座標と経過時間を渡し、ピクセルの色を受けとる
    template <typename First, typename... Rest>
    RenderManager(double *t, uint16 *frameBuffer, const First &first, const Rest &...rest)
    {
        this->t = t;
        this->frameBuffer = frameBuffer;
        RoundUp(first, rest...);

        shaderSpeed = 1;
        shaderFuncsSize = shaderFuncs.size();

        renderCount = 1;
        SetPixCount((int)(SCREEN_WIDTH / 7.5), (int)(SCREEN_HEIGHT / 7.5));
    }

    //再度初期化処理を行う
    void Start() override;
    //登録されたシェーダーの個数を取得
    int GetShaderFuncsSize();
    //現在実行されてるシェーダーの要素番号を取得
    int GetShaderFuncsIndex();
    //現在のシェーダーの再生速度を取得
    float GetShaderSpeed();

    void SetPixCount(int width, int height);
    int GetPixWidthCount();
    int GetPixHeightCount();

    //シェーダーの再生速度を変更
    void SetShaderSpeed(float timeScale);
    //シェーダーを切り替える
    void SetShaderFuncsIndex(int index);
    //Shaderの計算にかかった時間を取得
    double GetPixUpdateDeltaTime();
    //ピクセルのレンダリング時間を取得
    double GetPixRenderDeltaTime();
};