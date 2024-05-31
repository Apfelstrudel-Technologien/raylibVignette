#include "raylib.h"

int main(void)
{
    // Window.
    const int winW = 1500;
    const int winH = 1000;

    InitWindow(winW, winH, "Vignette.");

    // Shader loading & generic preparing.
    Shader shader = LoadShader(0, "vignette.fs");

    int rLoc = GetShaderLocation(shader, "radius");
    int blurLoc = GetShaderLocation(shader, "blur");
    int colLoc = GetShaderLocation(shader, "color");

    float radius = 0.5f;
    float blur = 0.1f;

    Vector3 vColor = {1.0f, 0.2f, 0.4f}; // Vignette color.

    RenderTexture2D vTexture = LoadRenderTexture(winW, winH); // Vignette texture.

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update values.
        if (IsKeyDown(KEY_UP)) radius += 0.01f;
        if (IsKeyDown(KEY_DOWN)) radius -= 0.01f;

        if (IsKeyDown(KEY_RIGHT)) blur += 0.01f;
        if (IsKeyDown(KEY_LEFT)) blur -= 0.01f;

        SetShaderValue(shader, rLoc, &radius, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, blurLoc, &blur, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, colLoc, &vColor, SHADER_UNIFORM_VEC3);

        BeginDrawing();

        ClearBackground(WHITE);

        // Draw vignette.
        BeginShaderMode(shader);
        DrawTextureRec(vTexture.texture, (Rectangle){ 0, 0, vTexture.texture.width, -vTexture.texture.height }, (Vector2){ 0, 0 }, BLANK);
        EndShaderMode();

        // Some information.
        DrawText(TextFormat("Radius: %.2f", radius), 10, 10, 20, BLACK);
        DrawText(TextFormat("Blur: %.2f", blur), 10, 40, 20, BLACK);

        DrawText("Use arrow keys to adjust radius and blur", 10, 70, 20, BLACK);

        // End.
        EndDrawing();
    }

    // Unload everything and close window.
    UnloadShader(shader);
    UnloadRenderTexture(vTexture);

    CloseWindow();

    return 0;
}