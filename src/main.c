#include <vitasdkkern.h>
#include <taihen.h>

static tai_hook_ref_t g_hookrefs[2];
static SceUID         g_hooks[2];

int kscePowerSetDisplayMaxBrightness_patched(int limit) {
    return TAI_CONTINUE(int, g_hookrefs[0], 0x10000);
}

int sub_3E10_patched(int unk, int feature, unsigned int enable) {
    if (feature == 3) // WLAN/COM
        enable = 1;
    return TAI_CONTINUE(int, g_hookrefs[1], unk, feature, enable);
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

    return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args) {

    if (g_hooks[0] >= 0)
        taiHookReleaseForKernel(g_hooks[0], g_hookrefs[0]);
    if (g_hooks[1] >= 0)
        taiHookReleaseForKernel(g_hooks[1], g_hookrefs[1]);

    return SCE_KERNEL_STOP_SUCCESS;
}
