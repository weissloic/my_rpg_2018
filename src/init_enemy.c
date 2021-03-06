/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** init_enemy
*/

#include "../include/rpg.h"
#include "../include/my.h"

static char *init_ley_and_oratio(window_t *win)
{
    char *name = "ressources/images/";

    if (win->quests->combat == 1) {
        name = my_strcat(name, "Ley.png");
        win->enemy->health = 50;
        win->enemy->actual_health = 50;
        win->enemy->strength = 50;
        sfMusic_stop(win->music->boss_song);
        sfMusic_play(win->music->boss_battle);
    }
    if (win->quests->combat == 2) {
        name = my_strcat(name, "Oratio.png");
        win->enemy->strength = 80;
        win->enemy->health = 80;
        win->enemy->actual_health = 80;
        sfMusic_stop(win->music->boss_song);
        sfMusic_play(win->music->boss_battle);
    }
    return (name);
}

static int set_sprite(window_t *win)
{
    char *str = NULL;

    sfSprite_setTextureRect(win->enemy->sprite->sprite,
    get_rect(297, 56, 30, 30));
    sfSprite_setScale(win->enemy->sprite->sprite, get_pos_float(-4.f, 4.f));
    str = my_strcat(my_itc(win->enemy->actual_health), "/");
    str = my_strcat(str, my_itc(win->enemy->health));
    if (init_text(&win->enemy->text[0], str,
    get_pos_float(400, 10), win->font_berlin) == 84)
        return (84);
    return (0);
}

int init_enemy(window_t *win)
{
    char *name = "ressources/images/";

    name = init_ley_and_oratio(win);
    if (win->quests->combat == 3) {
        name = my_strcat(name, "Glenys.png");
        win->enemy->health = 150;
        win->enemy->actual_health = 150;
        win->enemy->strength = 150;
        sfMusic_stop(win->music->boss_song);
        sfMusic_play(win->music->boss_final);
    }
    if (init_sprite(&win->enemy->sprite[0], name,
    get_pos_float(400, 500)) == 84)
        return (84);
    if (set_sprite(win) == 84)
        return (84);
    return (0);
}