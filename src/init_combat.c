/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** init_combat
*/

#include "../include/rpg.h"
#include "../include/my.h"

static int init_buttons(window_t *win)
{
    sfVector2f size = get_pos_float(400, 100);
    int order_button[] = {FLECHE, FLECHE, FLECHE};
    int pos_x[] = {1600, 1600, 1600};
    int pos_y[] = {200, 300, 400};

    for (int i = 0; i < win->scene[COMBAT].nb_button; i++) {
        set_next_buttons(&win->scene[COMBAT].button[i], win->rect_buttons,
        order_button[i]);
        if (init_button(&win->scene[COMBAT].button[i],
        get_pos_float(pos_x[i], pos_y[i]),
        size, win->texture_button) == 84)
            return (84);
        sfRectangleShape_setSize(win->scene[COMBAT].button[i].shape,
        get_pos_float(100, 100));
    }
    win->scene[COMBAT].button[0].callback = &basic_attack;
    win->scene[COMBAT].button[1].callback = &special_attack;
    win->scene[COMBAT].button[2].callback = &stats_attack;
    return (0);
}

static void init_sprites_basic(window_t *win)
{
    sfSprite_setTextureRect(win->scene[COMBAT].sprite[0].sprite,
    get_rect(297, 56, 30, 30));
    sfSprite_setScale(win->scene[COMBAT].sprite[0].sprite,
    get_pos_float(4, 4));
    sfSprite_setScale(win->scene[COMBAT].sprite[6].sprite,
    get_pos_float(4, 4));
    sfSprite_setScale(win->scene[COMBAT].sprite[1].sprite,
    get_pos_float(0.2, 0.2));
    sfSprite_setScale(win->scene[COMBAT].sprite[2].sprite,
    get_pos_float(0.2, 0.2));
    win->scene[COMBAT].nb_sprite = 7;
    win->scene[COMBAT].sprite[0].depth = 1;
    win->scene[COMBAT].sprite[1].depth = 1;
    win->scene[COMBAT].sprite[2].depth = 1;
    win->scene[COMBAT].sprite[3].depth = 0;
    win->scene[COMBAT].sprite[4].depth = 0;
    win->scene[COMBAT].sprite[5].depth = 0;
    win->scene[COMBAT].sprite[6].depth = 1;
    win->scene[COMBAT].sprite[7].depth = -1;
}

static int init_sprites_other(window_t *win)
{
    if (init_sprite(&win->scene[COMBAT].sprite[3],
    "ressources/images/background_fight.png", get_pos_float(0, 0)) == 84)
        return (84);
    if (init_sprite(&win->scene[COMBAT].sprite[4],
    "ressources/images/platform_fight.png", get_pos_float(260, 570)) == 84)
        return (84);
    if (init_sprite(&win->scene[COMBAT].sprite[5],
    "ressources/images/platform_fight.png", get_pos_float(1490, 570)) == 84)
        return (84);
    if (init_sprite(&win->scene[COMBAT].sprite[6],
    "ressources/images/sword.png", get_pos_float(1440, 100)) == 84)
        return (84);
    if (init_sprite(&win->scene[COMBAT].sprite[7],
    "ressources/images/test_fight.png", get_pos_float(0, 0)) == 84)
        return (84);
    return (0);
}

static int init_sprites(window_t *win)
{
    char *skin = NULL;

    skin = my_strcat("ressources/images/", win->player->name);
    skin = my_strcat(skin, ".png");
    if (init_sprite(&win->scene[COMBAT].sprite[0], skin,
    get_pos_float(1500, 500)) == 84)
        return (84);
    if (init_sprite(&win->scene[COMBAT].sprite[1],
    "ressources/images/heart.png", get_pos_float(1440, 20)) == 84)
        return (84);
    if (init_sprite(&win->scene[COMBAT].sprite[2],
    "ressources/images/heart.png", get_pos_float(340, 20)) == 84)
        return (84);
    if (init_sprites_other(win) == 84)
        return (84);
    init_sprites_basic(win);
    return (0);
}

window_t *init_combat(window_t *win)
{
    char *str = NULL;

    if (set_struct(win, 3, 2, 8) == 84)
        return (NULL);
    win->combat_clock = sfClock_create();
    if (init_buttons(win) == 84)
        return (NULL);
    if (init_sprites(win) == 84)
        return (NULL);
    str = my_strcat(my_itc(win->player->actual_health), "/");
    str = my_strcat(str, my_itc(win->player->health));
    if (init_text(&win->scene[COMBAT].text[0], str,
    get_pos_float(1500, 10), win->font_berlin) == 84)
        return (NULL);
    if (init_text(&win->scene[COMBAT].text[1], my_itc(win->player->strength),
    get_pos_float(1500, 100), win->font_berlin) == 84)
        return (NULL);
    if (init_enemy(win) == 84)
        return (NULL);
    return (win);
}