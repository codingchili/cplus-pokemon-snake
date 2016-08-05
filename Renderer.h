/**
 * @author Robin Duda
 *
 * Renders the game to the screen.
 */

#ifndef CPLUS_POKESNAKE_RENDERER_H
#define CPLUS_POKESNAKE_RENDERER_H


#include "Resources.h"
#include "Game.h"

#define PI 3.14159265

const int RENDER_FPS = 90;
const int MAX_PARTICLES = 30;

const int WALL_SIZE = 16;
const int START_OFFSET = 464;
const int SEGMENT_OFFSET = 2;

const double PARTICLE_SPEED = 1.95;
const double PARTICLE_SPEED_DECAY = 0.0014;
const int PARTICLE_LIFETIME = 90;

const int VIEW_START = 1;
const int VIEW_GAMEPLAY = 2;
const int VIEW_NEXTLEVEL = 3;
const int VIEW_GAMEOVER = 4;
const int VIEW_GAMEWIN = 5;

struct Particle {
    double x;
    double y;
    int lifetime;
    double speed;
    double direction;
    bool alive = false;
};

class Renderer {
private:
    Particle particles[MAX_PARTICLES] = {};
    int tick = 1;
    Resources *resources;
    Game *game;

    void DrawBackground();

    void DrawWalls();

    void DrawPlayer();

    void DrawPokemons();

    void DrawMenu();

    void DrawParticles();

    void StartView();

    void NextLevelView();

    void GameOver();

    void GamePlay();

    void GameWin();

    void DrawGameStats();

    void DrawGameLevel();

    void SpawnParticles();

public:
    Renderer(Game *game, Resources *resources);

    /**
     * Redraws the screen specified by the view id.
     */
    void Update(int view);
};


#endif //CPLUS_POKESNAKE_RENDERER_H
