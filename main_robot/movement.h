/* movement.h
 *
 * This file is part of the Epitech Msc2 2023 ESP project.
 *
 */

void set_motor_forward();
void set_motor_backwards();
void set_motor_stop();
void set_motor_right();
void set_motor_left();

void set_motor_speed(int lspeed, int rspeed);
int watch();

void movement_tick();

void setup_movement();