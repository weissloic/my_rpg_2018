/*
** EPITECH PROJECT, 2019
** Untitled (Workspace)
** File description:
** display
*/

#include "../include/rpg.h"
#include "../include/my.h"

ptr_func *init_func(void)
{
    static ptr_func ptr_choose[] = {
        {MAINMENU, &init_menu, &draw_scene, &global_event, &destroy_scene},
        {HEROES, &init_choose_heroes, &draw_scene, &global_event, &destroy_scene},
        {HOW_TO_PLAY, &init_how_to_play, &draw_scene, &global_event, &destroy_scene},
        {OPTIONS, &init_options, &draw_scene, &global_event, &destroy_scene},
        {GAME, &init_game, &draw_scene, &global_event, &destroy_scene},
        {HOUSE, &init_house, &draw_scene, &global_event, &destroy_scene},
    };
    return (ptr_choose);
}

void display(window_t *win)
{
    ptr_func *ptr_choose = init_func();
    win = ptr_choose[win->actual_page].start(win);

    while (sfRenderWindow_isOpen(win->window)) {
        if (win->page != win->actual_page) {
            printf("ok1\n");
            win = ptr_choose[win->actual_page].end(win);
            printf("ok2\n");
            win = ptr_choose[win->page].start(win);
            printf("ok3\n");
            win->actual_page = win->page;
        }
        printf("okay1\n");
        while (sfRenderWindow_pollEvent(win->window, &win->event))
            ptr_choose[win->actual_page].event(win);
        printf("okay2\n");
        win = ptr_choose[win->actual_page].draw(win);
        printf("okay3\n");
        if (win->actual_page == HEROES) {
            win->move_time = sfClock_getElapsedTime(win->move);
            win->seconds = win->move_time.microseconds / 1000000.0;
            move_sprites(win, 48);
        }
    }
}