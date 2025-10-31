//
// Created by RM UI Designer
//

#include "ui_default_Ungroup_3.h"
#include "usart.h"

#define FRAME_ID 0
#define GROUP_ID 0
#define START_ID 3
#define OBJ_NUM 1
#define FRAME_OBJ_NUM 1

CAT(ui_, CAT(FRAME_OBJ_NUM, _frame_t)) ui_default_Ungroup_3;
ui_interface_number_t *ui_default_Ungroup_cap_Volt = (ui_interface_number_t *)&(ui_default_Ungroup_3.data[0]);

void _ui_init_default_Ungroup_3() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_default_Ungroup_3.data[i].figure_name[0] = FRAME_ID;
        ui_default_Ungroup_3.data[i].figure_name[1] = GROUP_ID;
        ui_default_Ungroup_3.data[i].figure_name[2] = i + START_ID;
        ui_default_Ungroup_3.data[i].operate_tpyel = 1;
    }
    for (int i = OBJ_NUM; i < FRAME_OBJ_NUM; i++) {
        ui_default_Ungroup_3.data[i].operate_tpyel = 0;
    }

    ui_default_Ungroup_cap_Volt->figure_tpye = 5;
    ui_default_Ungroup_cap_Volt->layer = 0;
//    ui_default_Ungroup_cap_Volt->font_size = 50;
    ui_default_Ungroup_cap_Volt->start_x = 1731;
    ui_default_Ungroup_cap_Volt->start_y = 407;
    ui_default_Ungroup_cap_Volt->color = 1;
    ui_default_Ungroup_cap_Volt->number = 8345;
    ui_default_Ungroup_cap_Volt->width = 5;


    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_default_Ungroup_3);
    SEND_MESSAGE((uint8_t *) &ui_default_Ungroup_3, sizeof(ui_default_Ungroup_3));
}

void _ui_update_default_Ungroup_3() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_default_Ungroup_3.data[i].operate_tpyel = 2;
    }

    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_default_Ungroup_3);
    SEND_MESSAGE((uint8_t *) &ui_default_Ungroup_3, sizeof(ui_default_Ungroup_3));
}

void _ui_remove_default_Ungroup_3() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_default_Ungroup_3.data[i].operate_tpyel = 3;
    }

    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_default_Ungroup_3);
    SEND_MESSAGE((uint8_t *) &ui_default_Ungroup_3, sizeof(ui_default_Ungroup_3));
}
