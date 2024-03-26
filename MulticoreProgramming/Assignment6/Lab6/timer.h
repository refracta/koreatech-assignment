#define ENTRY(key, name) key,

#define TIMER_LIST \
    ENTRY(TIMER_DATA_TRANSFER_H2D, "Data Transfer Time (Host > Device)") \
    ENTRY(TIMER_DATA_TRANSFER_D2H, "Data Transfer Time (Device > Host)") \
    ENTRY(TIMER_HOST, "Timer host") \
    ENTRY(TIMER_OMP, "Timer omp") \
    ENTRY(TIMER_KERNEL_BASIC, "Timer Basic") \
    ENTRY(TIMER_KERNEL_RR, "Timer RR") \
    ENTRY(TIMER_KERNEL_RC, "Timer RC") \
    ENTRY(TIMER_KERNEL_CR, "Timer CR") \
    ENTRY(TIMER_KERNEL_CC, "Timer CC") \
    ENTRY(TIMER_KERNEL_CC_V_FINAL, "Timer CC_V_FINAL") \
    ENTRY(TIMER_LIST_SIZE, "")

enum TimerType {
    TIMER_LIST
    #undef ENTRY
};

#define ENTRY(key, name) char* key##_NAME = (char *) name;
TIMER_LIST
#undef ENTRY

#define ENTRY(key, name) key##_NAME,
char* TIMER_NAME_LIST[] = {
        TIMER_LIST
#undef ENTRY
};