/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** init_text
*/

#include "../include/rpg.h"
#include "../include/my.h"

static char *open_fd(int *fd, int actual, int quete_done, int *opened)
{
    char *str = NULL;

    fd[0] = open("ressources/text/script_paroles", O_RDONLY);
    if (fd[0] < 0)
        return (NULL);
    while (actual < quete_done) {
        opened[0]++;
        str = get_next_line(fd[0]);
        if (str == NULL || str[0] == '\0')
            actual++;
    }
    return (str);
}

static char *check_fd(int *fd, int quete_done)
{
    static int opened = 0;
    int actual = 0;
    char *str = NULL;

    if (fd[0] == 0)
        str = open_fd(fd, actual, quete_done, &opened);
    if (opened == 0 || str == NULL || str[0] == '\0')
        str = get_next_line(fd[0]);
    if (opened != 0)
        opened = 0;
    return (str);
}

static char *get_str(quest_t *quest)
{
    static int fd = 0;

    if (quest->quete_done == 15) {
        fd = get_fd(fd);
        if (fd < 0)
            return (NULL);
        return ("special");
    }
    return (check_fd(&fd, quest->quete_done));
}

void display_text_in_textbox(quest_t *quest)
{
    char *str = NULL;
    sfUint32 *unistr;
    sfVector2f pos;

    str = get_str(quest);
    if (str != NULL && my_strcmp(str, "special") == 0)
        return;
    pos = sfSprite_getPosition(quest->sprite[1].sprite);
    quest->sprite[1].depth = 1;
    sfText_setCharacterSize(quest->text[1].str, 30);
    str_to_unicode(str, &unistr);
    if (str == NULL || str[0] == '\0' || unistr == NULL || unistr[0] == '\0')
        quest->quete_done++;
    else
        sfText_setUnicodeString(quest->text[1].str, unistr);
    sfText_setPosition(quest->text[1].str, get_pos_float(pos.x + 20,
    pos.y + 20));
}

int init_text(text_t *text, char *display, sfVector2f pos, sfFont *font)
{
    if (text == NULL || font == NULL)
        return (84);
    text->str = sfText_create();
    if (text->str == NULL)
        return (84);
    sfText_setFont(text->str, font);
    sfText_setColor(text->str, sfWhite);
    sfText_setCharacterSize(text->str, 50);
    sfText_setString(text->str, display);
    sfText_setPosition(text->str, pos);
    return (0);
}