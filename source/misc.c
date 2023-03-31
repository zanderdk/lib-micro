#include "misc.h"

void assign_to_core(int core_id) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);
    if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpuset) != 0){
        error(EXIT_FAILURE, -1, "assign to specifi core failed.");
    }
}
