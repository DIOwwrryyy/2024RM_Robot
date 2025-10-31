//
// Created by RM UI Designer
//

#include "ui_default_Ungroup_1.h"
#include "string.h"

#define FRAME_ID 0
#define GROUP_ID 0
#define START_ID 1

ui_string_frame_t ui_default_Ungroup_1;

ui_interface_string_t* ui_default_Ungroup_shot_open = &ui_default_Ungroup_1.option;

void _ui_init_default_Ungroup_1() {
    ui_default_Ungroup_1.option.figure_name[0] = FRAME_ID;
    ui_default_Ungroup_1.option.figure_name[1] = GROUP_ID;
    ui_default_Ungroup_1.option.figure_name[2] = START_ID;
    ui_default_Ungroup_1.option.operate_tpyel = 1;
    ui_default_Ungroup_1.option.figure_tpye = 7;
    ui_default_Ungroup_1.option.layer = 1;
    ui_default_Ungroup_1.option.font_size = 40;
    ui_default_Ungroup_1.option.start_x = 1510;
    ui_default_Ungroup_1.option.start_y = 305;
    ui_default_Ungroup_1.option.color = 6;
    ui_default_Ungroup_1.option.str_length = 10;
    ui_default_Ungroup_1.option.width = 4;
    strcpy(ui_default_Ungroup_shot_open->string, "PRESS_R！");

    ui_proc_string_frame(&ui_default_Ungroup_1);
    SEND_MESSAGE((uint8_t *) &ui_default_Ungroup_1, sizeof(ui_default_Ungroup_1));
}

void _ui_update_default_Ungroup_1() {
    ui_default_Ungroup_1.option.operate_tpyel = 2;

    ui_proc_string_frame(&ui_default_Ungroup_1);
    SEND_MESSAGE((uint8_t *) &ui_default_Ungroup_1, sizeof(ui_default_Ungroup_1));
}

void _ui_remove_default_Ungroup_1() {
    ui_default_Ungroup_1.option.operate_tpyel = 3;

    ui_proc_string_frame(&ui_default_Ungroup_1);
    SEND_MESSAGE((uint8_t *) &ui_default_Ungroup_1, sizeof(ui_default_Ungroup_1));
}