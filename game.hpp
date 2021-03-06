#ifndef LR_SUPERFLAPPYBIRD_GAME_H
#define LR_SUPERFLAPPYBIRD_GAME_H

#include <stdint.h>
#include <random>
#include <vector>
#include <deque>
#include "pipe_pair.hpp"
#include "assets.hpp"
#include "bird.hpp"
#include "input.hpp"
#include "menu.hpp"
#include "save_data.hpp"
#include "engine/audio_mixer.hpp"

enum GameState {
    InGame, InPostGameMenu, InMenu
};

class Game {
public:
    static const char *game_name;
    static const char *game_version;
    static const int game_fps = 50;

    AudioMixer mixer;

    Game(unsigned int screen_width, unsigned int screen_height, std::string core_folder_path, std::string config_folder_path, unsigned int max_players, bool show_wins);

    void GameLoop(double delta_time, std::vector<Input> controller_inputs);

    uint32_t *GetFrameBuffer();

private:
    /// The speed in pixels per second that the screen scrolls at
    double_t scroll_speed = 1;
    /// How many pixels between each pipe
    const int DISTANCE_BETWEEN_PIPES = 100;

    Renderer *screen;
    std::mt19937 rng;
    GameState state;
    Menu *menu;
    SaveData *save_data;
    double distance_travelled = 0;
    Assets *assets;
    std::vector<uint32_t> framebuffer;
    unsigned int screen_width;
    unsigned int screen_height;
    std::deque<PipePair> pipes = {};
    std::vector<Bird *> birds;
    bool show_wins;

    void DrawBackground(Renderer *renderer);

    void DrawGround(Renderer *renderer);

    void DrawScores(Renderer *renderer);

    void generate_pipes(int number);

    bool bird_crashed(Bird *bird);

    bool all_birds_dead();

    void score_all_birds();

    void draw_score(Renderer *renderer, int x, int y, int score);

    /// Draws the players score, their sprite, a background, and optionally their number of wins.
    /// \param renderer The renderer to draw with.
    /// \param x The x position for the score background's top-left corner.
    /// \param y The y position for the score background's top-left corner.
    /// \param score The player's score.
    /// \param bird The texture for the player.
    /// \param bird_frame The frame in that texture to draw.
    /// \param wins The number of wins the player has had, use a negative number to not show scores and have a more compact background.
    void draw_score(Renderer *renderer, int x, int y, int score, Texture *bird, Rect *bird_frame, int wins = -1);

    void NewGame(int num_players);

    /// Transitions the game to the Post Game Menu
    void PostGameMenu();
};


#endif //LR_SUPERFLAPPYBIRD_GAME_H
