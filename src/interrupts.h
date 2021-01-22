#define TIMER_CMP_LOW 0x1A10B010
#define INT_CTRL 0x1A109004
#define CFG_REG_LOW 0x1A10B000
#define INT_STATUS 0x1A101018

int int_ctrl_state;
int button_state;
char button_state_read;
void (*buttonIntHandler)(void);
void (*timerIntHandler)(void);

void initInterrupts() {
    button_state = 0;
    int_ctrl_state = 0;
}

int getButtonState() {
    if (button_state_read == 0) {
        int volatile* p_int_status = (int*)INT_STATUS;
        button_state = *p_int_status;
        button_state_read = 1;
    }

    return button_state;
}
void setTimerInterrupt(int delay, void (*onTimerInt)(void)) {
    timerIntHandler = onTimerInt;

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
void enableButtonInterrupt(void (*onButtonInt)(void)) {
    buttonIntHandler = onButtonInt;
    int volatile* p_int_ctrl = (int*)INT_CTRL;
    int_ctrl_state |= 0b1000000000000000;
    *p_int_ctrl = int_ctrl_state;
}
void disableButtonInterrupt() {
    int volatile* p_int_ctrl = (int*)INT_CTRL;
    int_ctrl_state &= ~0b1000000000000000;
    *p_int_ctrl = int_ctrl_state;
}

void timerInt() {
    timerIntHandler();
    asm("ret");
}
void buttonInt() {
    button_state_read = 0;
    buttonIntHandler();
    asm("ret");
}