#define TIMER_CMP_LOW 0x1A10B010
#define INT_CTRL 0x1A109004
#define CFG_REG_LOW 0x1A10B000
#define INT_STATUS 0x1A101018
#define LED_STATUS 0x1A120000

int int_ctrl_state = 0;

int getButtonState() {
    int volatile* p_int_status = (int*)INT_STATUS;
    return *p_int_status;
}
void setLedStatus(int value) {
    int volatile* p_led_status = (int*)LED_STATUS;
    *p_led_status = value;
}
void setTimerInterrupt(int delay) {
    int volatile* p_timer_cmp_low = (int*)TIMER_CMP_LOW;
    *p_timer_cmp_low = delay;
 
    int volatile* p_int_ctrl = (int*)INT_CTRL;
    int_ctrl_state |= 0b10000000000;
    *p_int_ctrl = int_ctrl_state;

    int volatile* p_cfg_reg_low = (int*)CFG_REG_LOW;
    *p_cfg_reg_low = 0b010101;
}
void disableTimerInterrupt() {
    int volatile* p_int_ctrl = (int*)INT_CTRL;
    int_ctrl_state &= ~0b10000000000;
    *p_int_ctrl = int_ctrl_state;
}
void enableButtonInterrupt() {
    int volatile* p_int_ctrl = (int*)INT_CTRL;
    int_ctrl_state |= 0b1000000000000000;
    *p_int_ctrl = int_ctrl_state;
}
void disableButtonInterrupt() {
    int volatile* p_int_ctrl = (int*)INT_CTRL;
    int_ctrl_state &= ~0b1000000000000000;
    *p_int_ctrl = int_ctrl_state;
}
