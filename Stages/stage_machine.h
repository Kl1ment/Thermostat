#ifndef STAGE_MACHINE_H_
#define STAGE_MACHINE_H_

void setup_info_stage();
void setup_settings_stage(unsigned char reset);
void setup_edit_settings_stage();

typedef void (*Loop_stage)(void);
Loop_stage loop_stage;

#include "info_stage.h"
#include "settings_stage.h"
#include "edit_settings_stage.h"


#endif