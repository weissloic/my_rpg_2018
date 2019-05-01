/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** callback_play
*/

#include "../include/rpg.h"
#include "../include/my.h"

static void check_new_game(window_t *win)
{
    if (win->page == HEROES) {
        win->quests->quete_done = 15;
        display_text_in_textbox(win->quests);
        win->quests->sprite[1].depth = -1;
        win->quests->quete_done = 0;
        win->quests->combat = 0;
        save_quests(win);
        for (int i = 0; i < 15; i++)
            win->inv->items[i].name = NULL;
        save_inventory(win);
        win->player->last_pos = get_pos_float(930, 600);
        win->no_saves = 1;
        save_config_player(win);
    }
}

void play_game(window_t *win)
{
    sfMusic_play(win->music->button_sound);
    sfMusic_play(win->music->town_song);
    check_new_game(win);
    win->player = parser_player(win->player, "ressources/text/config_player");
    win->page = win->player->last_page;
    init_inventory(win->inv);
    init_player(win->player);
    if (set_player(win) == 84)
        win->error = 84;
    init_objects(win->objects, win->inv);
    init_quests(win->quests);
    if (win->quests->quete_done < 5)
        win->quests->combat = 0;
    sfText_setString(win->text->str, "\n");
    sfMusic_stop(win->music->menu_song);
}