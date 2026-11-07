
#include "raylib.h"
#include <math.h>
#include <stdbool.h>

#define SCREEN_W 960
#define SCREEN_H 540
#define LEVEL_W 4200
#define GROUND_TOP 340
#define GROUND_BOTTOM 510
#define MAX_ENEMIES 12
#define MAX_PICKUPS 8
#define PLAYER_MAX_HP 100
#define COL(r, g, b) ((Color){(r), (g), (b), 255})

typedef enum
{
    STATE_TITLE,
    STATE_PLAY,
    STATE_OVER,
    STATE_WIN
} GameState;
typedef enum
{
    THUG,
    RAPTOR,
    TREX
} EnemyType;

typedef struct
{
    float x, y, z, vz; /* y = depth on the ground plane, z = height in the air */
    int facing;        /* 1 = right, -1 = left */
    int hp;
    int attackTimer, attackCooldown, hurtTimer;
} Player;

typedef struct
{
    bool active;
    EnemyType type;
    float x, y, speed, reach;
    int facing, hp, maxHp, damage;
    int attackTimer, cooldown, hurtTimer;
} Enemy;

typedef struct
{
    bool active;
    float x, y;
} Pickup;

typedef struct
{
    float triggerX;
    int thugs, raptors, trex;
    bool done;
} EnemyWave;

static Player p;
static Enemy enemies[MAX_ENEMIES];
static Pickup pickups[MAX_PICKUPS];
static EnemyWave waves[] = {
    {250, 2, 0, 0, false},
    {800, 3, 1, 0, false},
    {1400, 2, 2, 0, false},
    {2000, 3, 2, 0, false},
    {2700, 4, 3, 0, false},
    {3400, 2, 0, 1, false}, /* boss fight */
};
#define WAVE_COUNT ((int)(sizeof(waves) / sizeof(waves[0])))

static float camX;
static int score, frame;
static GameState state = STATE_TITLE;

/* ------------------------------------------------------------ helpers */
static bool AnyEnemy(void)
{
    for (int i = 0; i < MAX_ENEMIES; i++)
        if (enemies[i].active)
            return true;
    return false;
}

static void DropPickup(float x, float y)
{
    for (int i = 0; i < MAX_PICKUPS; i++)
    {
        if (!pickups[i].active)
        {
            pickups[i] = (Pickup){true, x, y};
            return;
        }
    }
}

static void SpawnEnemy(EnemyType t, int side)
{
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        if (enemies[i].active)
            continue;
        Enemy *e = &enemies[i];
        *e = (Enemy){0};
        e->active = true;
        e->type = t;
        e->x = (side > 0) ? camX + SCREEN_W + 40 : camX - 40;
        e->y = GROUND_TOP + 25 + GetRandomValue(0, GROUND_BOTTOM - GROUND_TOP - 30);
        e->facing = (side > 0) ? -1 : 1;
        switch (t)
        {
        case THUG:
            e->hp = e->maxHp = 30;
            e->speed = 1.4f;
            e->damage = 6;
            e->reach = 45;
            break;
        case RAPTOR:
            e->hp = e->maxHp = 40;
            e->speed = 2.4f;
            e->damage = 8;
            e->reach = 55;
            break;
        case TREX:
            e->hp = e->maxHp = 300;
            e->speed = 1.1f;
            e->damage = 20;
            e->reach = 95;
            break;
        }
        e->cooldown = 30;
        return;
    }
}

static void ResetGame(void)
{
    p = (Player){120, 430, 0, 0, 1, PLAYER_MAX_HP, 0, 0, 0};
    for (int i = 0; i < MAX_ENEMIES; i++)
        enemies[i].active = false;
    for (int i = 0; i < MAX_PICKUPS; i++)
        pickups[i].active = false;
    for (int i = 0; i < WAVE_COUNT; i++)
        waves[i].done = false;
    camX = 0;
    score = 0;
    frame = 0;
}

/* ------------------------------------------------------------ combat */
static void PlayerAttackHit(void)
{
    int dmg = (p.z > 0) ? 16 : 10;
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        Enemy *e = &enemies[i];
        if (!e->active)
            continue;
        float dx = (e->x - p.x) * p.facing;
        if (dx > -15 && dx < 75 && fabsf(e->y - p.y) < 24)
        {
            e->hp -= dmg;
            e->hurtTimer = 16;
            e->attackTimer = 0;
            e->x += p.facing * (e->type == TREX ? 4 : 18);
            score += 10;
            if (e->hp <= 0)
            {
                e->active = false;
                score += (e->type == TREX) ? 1000 : (e->type == RAPTOR) ? 150
                                                                        : 100;
                if (e->type != TREX && GetRandomValue(0, 3) == 0)
                    DropPickup(e->x, e->y);
            }
        }
    }
}

static void UpdatePlayer(void)
{
    float spd = 3.2f;
    if (p.attackTimer > 0 && p.z <= 0)
        spd *= 0.3f;

    float mx = 0, my = 0;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        mx -= 1;
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        mx += 1;
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
        my -= 1;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
        my += 1;
    p.x += mx * spd;
    p.y += my * spd * 0.75f;
    if (mx != 0 && p.attackTimer == 0)
        p.facing = (mx > 0) ? 1 : -1;

    /* jump */
    if (p.z <= 0 && (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_K) || IsKeyPressed(KEY_X)))
        p.vz = 9.5f;
    if (p.z > 0 || p.vz > 0)
    {
        p.vz -= 0.55f;
        p.z += p.vz;
        if (p.z <= 0)
        {
            p.z = 0;
            p.vz = 0;
        }
    }

    /* attack */
    if (p.attackCooldown > 0)
        p.attackCooldown--;
    if (p.hurtTimer > 0)
        p.hurtTimer--;
    if (p.attackTimer > 0)
    {
        p.attackTimer--;
        if (p.attackTimer == 8)
            PlayerAttackHit();
    }
    else if (p.attackCooldown == 0 && (IsKeyPressed(KEY_J) || IsKeyPressed(KEY_Z)))
    {
        p.attackTimer = 14;
        p.attackCooldown = 18;
    }

    if (p.y < GROUND_TOP + 20)
        p.y = GROUND_TOP + 20;
    if (p.y > GROUND_BOTTOM)
        p.y = GROUND_BOTTOM;
}

static void UpdateEnemies(void)
{
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        Enemy *e = &enemies[i];
        if (!e->active)
            continue;
        if (e->hurtTimer > 0)
        {
            e->hurtTimer--;
            continue;
        }
        if (e->cooldown > 0)
            e->cooldown--;

        float dx = p.x - e->x, dy = p.y - e->y;

        if (e->attackTimer > 0)
        {
            e->attackTimer--;
            if (e->attackTimer == 10 && p.hurtTimer == 0 && p.z < 30 &&
                fabsf(dx) < e->reach + 10 && fabsf(dy) < 22)
            {
                p.hp -= e->damage;
                p.hurtTimer = 40;
                p.x += e->facing * 20;
            }
            continue;
        }

        e->facing = (dx >= 0) ? 1 : -1;
        if (fabsf(dx) < e->reach && fabsf(dy) < 16)
        {
            if (e->cooldown == 0)
            {
                e->attackTimer = 20;
                e->cooldown = 80;
            }
        }
        else
        {
            if (fabsf(dx) > e->reach - 10)
                e->x += (dx > 0 ? 1 : -1) * e->speed;
            if (fabsf(dy) > 8)
                e->y += (dy > 0 ? 1 : -1) * e->speed * 0.7f;
        }
        if (e->y < GROUND_TOP + 20)
            e->y = GROUND_TOP + 20;
        if (e->y > GROUND_BOTTOM)
            e->y = GROUND_BOTTOM;
    }
}

static void UpdatePickups(void)
{
    for (int i = 0; i < MAX_PICKUPS; i++)
    {
        if (!pickups[i].active)
            continue;
        if (fabsf(p.x - pickups[i].x) < 28 && fabsf(p.y - pickups[i].y) < 22)
        {
            pickups[i].active = false;
            p.hp += 30;
            if (p.hp > PLAYER_MAX_HP)
                p.hp = PLAYER_MAX_HP;
            score += 50;
        }
    }
}

static void UpdatePlay(void)
{
    frame++;
    UpdatePlayer();

    bool locked = AnyEnemy();
    if (!locked)
    {
        float target = p.x - SCREEN_W * 0.4f;
        if (target > camX)
            camX = target;
        if (camX > LEVEL_W - SCREEN_W)
            camX = LEVEL_W - SCREEN_W;
    }
    if (p.x < camX + 20)
        p.x = camX + 20;
    float maxX = locked ? camX + SCREEN_W - 20 : LEVEL_W - 20;
    if (p.x > maxX)
        p.x = maxX;

    /* trigger enemy waves as you walk right */
    for (int i = 0; i < WAVE_COUNT; i++)
    {
        if (waves[i].done || p.x < waves[i].triggerX)
            continue;
        waves[i].done = true;
        int n = 0;
        for (int k = 0; k < waves[i].thugs; k++)
            SpawnEnemy(THUG, (n++ % 2) ? -1 : 1);
        for (int k = 0; k < waves[i].raptors; k++)
            SpawnEnemy(RAPTOR, (n++ % 2) ? -1 : 1);
        for (int k = 0; k < waves[i].trex; k++)
            SpawnEnemy(TREX, 1);
    }

    UpdateEnemies();
    UpdatePickups();

    if (p.hp <= 0)
        state = STATE_OVER;
    else if (waves[WAVE_COUNT - 1].done && !AnyEnemy())
        state = STATE_WIN;
}

/* ------------------------------------------------------------ drawing */
static void DrawCentered(const char *text, int y, int size, Color c)
{
    DrawText(text, (SCREEN_W - MeasureText(text, size)) / 2, y, size, c);
}

static void DrawCadillac(float worldX)
{
    int sx = (int)(worldX - camX);
    if (sx < -260 || sx > SCREEN_W + 60)
        return;
    int y = GROUND_TOP + 12;
    Color teal = COL(40, 150, 150), dark = COL(25, 100, 105);
    DrawEllipse(sx + 95, y, 105, 9, Fade(BLACK, 0.3f));
    DrawRectangle(sx, y - 42, 190, 30, teal);
    DrawRectangle(sx + 175, y - 54, 15, 14, teal); /* tail fin */
    DrawRectangle(sx + 40, y - 70, 95, 30, dark);  /* cabin */
    DrawRectangle(sx + 48, y - 64, 36, 18, COL(170, 220, 235));
    DrawRectangle(sx + 90, y - 64, 36, 18, COL(170, 220, 235));
    DrawRectangle(sx - 4, y - 24, 198, 6, COL(220, 220, 220)); /* chrome bumper line */
    DrawCircle(sx + 40, y - 8, 17, BLACK);
    DrawCircle(sx + 40, y - 8, 7, COL(200, 200, 200));
    DrawCircle(sx + 150, y - 8, 17, BLACK);
    DrawCircle(sx + 150, y - 8, 7, COL(200, 200, 200));
}

static void DrawBackground(void)
{
    DrawRectangleGradientV(0, 0, SCREEN_W, GROUND_TOP, COL(70, 40, 100), COL(250, 160, 80));
    DrawCircle(700, 150, 60, COL(255, 220, 140));

    /* far hills (slow parallax) */
    for (int i = -1; i < 8; i++)
    {
        float off = fmodf(camX * 0.2f, 260.0f);
        DrawCircle((int)(i * 260 - off), GROUND_TOP + 40, 150, COL(60, 50, 90));
    }
    /* jungle trees (medium parallax) */
    float scroll = camX * 0.5f;
    int base = (int)(scroll / 170.0f);
    float off = fmodf(scroll, 170.0f);
    for (int i = -1; i < 7; i++)
    {
        int idx = base + i;
        int h = 70 + (idx * 37 & 63);
        int tx = (int)(i * 170 - off);
        DrawRectangle(tx - 8, GROUND_TOP - h, 16, h, COL(70, 45, 30));
        DrawCircle(tx, GROUND_TOP - h, 42, COL(30, 100, 60));
        DrawCircle(tx - 28, GROUND_TOP - h + 14, 30, COL(35, 120, 70));
        DrawCircle(tx + 28, GROUND_TOP - h + 14, 30, COL(35, 120, 70));
    }
    /* ground */
    DrawRectangle(0, GROUND_TOP, SCREEN_W, SCREEN_H - GROUND_TOP, COL(120, 90, 60));
    DrawRectangle(0, GROUND_TOP, SCREEN_W, 10, COL(90, 130, 60));
    for (int i = 0; i < 14; i++)
    {
        int gx = (int)(i * 90 - fmodf(camX, 90.0f));
        DrawRectangle(gx, GROUND_TOP + 40 + (i * 53 % 120), 40, 4, COL(100, 72, 48));
    }
    DrawCadillac(600);
    DrawCadillac(1900);
    DrawCadillac(3300);
}

static void DrawFighter(float x, float y, float z, int facing, Color body, Color hat, int attackTimer)
{
    int sx = (int)(x - camX), gy = (int)y, by = gy - (int)z;
    Color skin = COL(224, 172, 105), pants = COL(40, 60, 130);
    DrawEllipse(sx, gy, 22, 7, Fade(BLACK, 0.35f));
    DrawRectangle(sx - 12, by - 26, 10, 26, pants);
    DrawRectangle(sx + 2, by - 26, 10, 26, pants);
    DrawRectangle(sx - 14, by - 62, 28, 38, body);
    DrawCircle(sx, by - 72, 11, skin);
    DrawRectangle(sx - 13, by - 82, 26, 6, hat);
    DrawRectangle(sx - 9, by - 90, 18, 9, hat);
    if (attackTimer > 0)
    {
        if (z > 0)
        { /* flying kick */
            DrawRectangle(facing > 0 ? sx : sx - 46, by - 24, 46, 10, pants);
        }
        else
        { /* punch */
            DrawRectangle(facing > 0 ? sx + 8 : sx - 48, by - 56, 40, 10, skin);
        }
    }
    else
    {
        DrawRectangle(facing > 0 ? sx + 8 : sx - 14, by - 58, 6, 24, skin);
    }
}

static void DrawDino(const Enemy *e)
{
    float s = (e->type == TREX) ? 1.9f : 1.0f;
    int sx = (int)(e->x - camX), gy = (int)e->y, f = e->facing;
    Color body = (e->type == TREX) ? COL(80, 115, 55) : COL(60, 160, 95);
    if (e->hurtTimer > 0 && (e->hurtTimer / 2) % 2)
        body = WHITE;

    DrawEllipse(sx, gy, 34 * s, 8 * s, Fade(BLACK, 0.35f));
    DrawLineEx((Vector2){sx - 8 * s, gy - 22 * s}, (Vector2){sx - 12 * s, (float)gy}, 6 * s, body);
    DrawLineEx((Vector2){sx + 8 * s, gy - 22 * s}, (Vector2){sx + 12 * s, (float)gy}, 6 * s, body);
    DrawLineEx((Vector2){sx - f * 20 * s, gy - 30 * s}, (Vector2){sx - f * 54 * s, gy - 16 * s}, 8 * s, body);
    DrawEllipse(sx, gy - 32 * s, 26 * s, 15 * s, body);

    float hx = sx + f * 24 * s, hy = gy - 46 * s;
    DrawLineEx((Vector2){sx + f * 14 * s, gy - 36 * s}, (Vector2){hx, hy}, 9 * s, body);
    int open = (e->attackTimer > 0) ? (int)(9 * s) : (int)(2 * s);
    float hw = 26 * s;
    int hl = (int)((f > 0) ? hx - 4 * s : hx - hw + 4 * s);
    DrawRectangle(hl, (int)(hy - 8 * s), (int)hw, (int)(9 * s), body);
    DrawRectangle(hl, (int)(hy + 1 * s) + open, (int)hw, (int)(5 * s), body);
    DrawCircle((int)(hx + f * 2 * s), (int)(hy - 5 * s), 2.5f * s, YELLOW);

    if (e->type != TREX)
    {
        int top = gy - 70;
        DrawRectangle(sx - 20, top, 40, 5, COL(60, 0, 0));
        DrawRectangle(sx - 20, top, 40 * e->hp / e->maxHp, 5, COL(220, 50, 50));
    }
}

static void DrawEnemy(const Enemy *e)
{
    if (e->type == THUG)
    {
        Color body = COL(190, 60, 60);
        if (e->hurtTimer > 0 && (e->hurtTimer / 2) % 2)
            body = WHITE;
        DrawFighter(e->x, e->y, 0, e->facing, body, COL(30, 30, 30), e->attackTimer);
        int sx = (int)(e->x - camX), top = (int)e->y - 105;
        DrawRectangle(sx - 20, top, 40, 5, COL(60, 0, 0));
        DrawRectangle(sx - 20, top, 40 * e->hp / e->maxHp, 5, COL(220, 50, 50));
    }
    else
    {
        DrawDino(e);
    }
}

static void DrawPlayer(void)
{
    if (p.hurtTimer > 0 && (p.hurtTimer / 3) % 2)
        return; /* blink while invulnerable */
    DrawFighter(p.x, p.y, p.z, p.facing, COL(230, 130, 40), COL(150, 100, 40), p.attackTimer);
}

static void DrawHUD(void)
{
    DrawRectangle(18, 18, 258, 28, BLACK);
    int w = 254 * p.hp / PLAYER_MAX_HP;
    if (w < 0)
        w = 0;
    DrawRectangle(20, 20, w, 24, p.hp > 30 ? COL(80, 200, 80) : COL(220, 60, 60));
    DrawText("JACK", 22, 50, 20, WHITE);
    DrawText(TextFormat("SCORE %06d", score), SCREEN_W - 230, 20, 26, YELLOW);

    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        if (enemies[i].active && enemies[i].type == TREX)
        {
            DrawText("TYRANT REX", SCREEN_W / 2 - 80, 20, 20, WHITE);
            DrawRectangle(SCREEN_W / 2 - 152, 46, 304, 18, BLACK);
            DrawRectangle(SCREEN_W / 2 - 150, 48, 300 * enemies[i].hp / enemies[i].maxHp, 14, COL(220, 50, 50));
        }
    }
    if (!AnyEnemy() && !waves[WAVE_COUNT - 1].done && (frame % 60) < 40)
        DrawText("GO >>", SCREEN_W - 140, 70, 36, WHITE);
}

/* ------------------------------------------------------------ main */
int main(void)
{
    InitWindow(SCREEN_W, SCREEN_H, "Xenozoic Rumble");
    SetTargetFPS(60);
    ResetGame();

    while (!WindowShouldClose())
    {
        if (state == STATE_PLAY)
            UpdatePlay();
        else if (IsKeyPressed(KEY_ENTER))
        {
            ResetGame();
            state = STATE_PLAY;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawBackground();

        if (state != STATE_TITLE)
        {
            for (int i = 0; i < MAX_PICKUPS; i++)
            {
                if (!pickups[i].active)
                    continue;
                int sx = (int)(pickups[i].x - camX), gy = (int)pickups[i].y;
                DrawCircle(sx, gy - 10, 10, COL(170, 80, 40));
                DrawRectangle(sx + 4, gy - 22, 4, 12, COL(240, 230, 210));
            }
            for (int i = 0; i < MAX_ENEMIES; i++)
                if (enemies[i].active && enemies[i].y <= p.y)
                    DrawEnemy(&enemies[i]);
            DrawPlayer();
            for (int i = 0; i < MAX_ENEMIES; i++)
                if (enemies[i].active && enemies[i].y > p.y)
                    DrawEnemy(&enemies[i]);
            DrawHUD();
        }

        if (state == STATE_TITLE)
        {
            DrawRectangle(0, 0, SCREEN_W, SCREEN_H, Fade(BLACK, 0.55f));
            DrawCentered("XENOZOIC RUMBLE", 120, 64, COL(255, 200, 60));
            DrawCentered("Jack vs. the poachers and their dinosaurs", 200, 24, WHITE);
            DrawCentered("Move: WASD / Arrows     Punch: J / Z     Jump: K / X / Space", 290, 22, WHITE);
            DrawCentered("Press ENTER to start", 380, 30, YELLOW);
        }
        else if (state == STATE_OVER)
        {
            DrawRectangle(0, 0, SCREEN_W, SCREEN_H, Fade(BLACK, 0.6f));
            DrawCentered("GAME OVER", 180, 64, COL(230, 60, 60));
            DrawCentered(TextFormat("Score: %06d", score), 270, 30, WHITE);
            DrawCentered("Press ENTER to try again", 340, 26, YELLOW);
        }
        else if (state == STATE_WIN)
        {
            DrawRectangle(0, 0, SCREEN_W, SCREEN_H, Fade(BLACK, 0.5f));
            DrawCentered("YOU WIN!", 170, 64, COL(255, 200, 60));
            DrawCentered("The Tyrant Rex is down. The jungle is safe.", 255, 26, WHITE);
            DrawCentered(TextFormat("Final score: %06d", score), 300, 30, WHITE);
            DrawCentered("Press ENTER to play again", 360, 26, YELLOW);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}