#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include "gfx.hpp"

PSP_MODULE_INFO("PSP-CPP TEST", 0, 1, 0);

int exit_callback(int arg1, int arg2, void* common){
    sceKernelExitGame();
    return 0;
}

int callbackThread(SceSize args, void* argp) {
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);

    sceKernelSleepThreadCB();
    return 0;
}

void setupCallbacks(){
    int thid = sceKernelCreateThread("update_thread", callbackThread, 0x11, 0xFA0, 0, NULL);
    if (thid >= 0) {
        sceKernelStartThread(thid, 0, NULL);
    }
}

auto main() -> int {
    setupCallbacks();

    GFX::init();

    int rect_x = 0;
    int rect_y = 0;


    // pspDebugScreenInit();
    // pspDebugScreenPrintf("Hello world from CPP");

    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    SceCtrlData ctrlData;
    
    while(true){
        sceCtrlReadBufferPositive(&ctrlData, 1);

        if (ctrlData.Buttons & PSP_CTRL_UP){
            rect_y-=1;
        }
        if (ctrlData.Buttons & PSP_CTRL_DOWN){
            rect_y+=1;
        }
        if (ctrlData.Buttons & PSP_CTRL_LEFT){
            rect_x-=1;
        }
        if (ctrlData.Buttons & PSP_CTRL_RIGHT){
            rect_x+=1;
        }

        GFX::clear(0xFFFFCA82);
        GFX::draw_rect(rect_x, rect_y, 30, 30, 0xFF00FFFF);
        GFX::swap_buffers();
        sceDisplayWaitVblankStart();
    }

}