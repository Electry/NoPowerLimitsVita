#include <vitasdkkern.h>
#include <taihen.h>

static tai_hook_ref_t g_hookrefs[3];
static SceUID         g_hooks[3];

int kscePowerSetDisplayMaxBrightness_patched(int limit) {
    return TAI_CONTINUE(int, g_hookrefs[0], 0x10000);
}

int sub_3E10_patched(int pid, int flags, unsigned int set) {
    if (flags == 3) // WLAN/COM
        set = 1;
    return TAI_CONTINUE(int, g_hookrefs[1], pid, flags, set);
}

int sub_C74_patched(int enable) {
    // calls sub_329C callback in SceCamera,
    // stored by ScePowerForDriver_0xFE35B73D
    return TAI_CONTINUE(int, g_hookrefs[2], 1);
}

void _start() __attribute__ ((weak, alias ("module_start")));
int module_start(SceSize argc, const void *args) {

    tai_module_info_t tai_info;
    tai_info.size = sizeof(tai_module_info_t);
    taiGetModuleInfoForKernel(KERNEL_PID, "ScePower", &tai_info);

    g_hooks[0] = taiHookFunctionExportForKernel(KERNEL_PID, &g_hookrefs[0],
            "ScePower", 0x1590166F, 0x77027B6B, kscePowerSetDisplayMaxBrightness_patched);

    g_hooks[1] = taiHookFunctionOffsetForKernel(KERNEL_PID, &g_hookrefs[1],
            tai_info.modid, 0, 0x3E10, 1, sub_3E10_patched);
    g_hooks[2] = taiHookFunctionOffsetForKernel(KERNEL_PID, &g_hookrefs[2],
            tai_info.modid, 0, 0xC74, 1, sub_C74_patched);

    return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args) {

    if (g_hooks[0] >= 0)
        taiHookReleaseForKernel(g_hooks[0], g_hookrefs[0]);
    if (g_hooks[1] >= 0)
        taiHookReleaseForKernel(g_hooks[1], g_hookrefs[1]);
    if (g_hooks[2] >= 0)
        taiHookReleaseForKernel(g_hooks[2], g_hookrefs[2]);

    return SCE_KERNEL_STOP_SUCCESS;
}
