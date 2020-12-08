#![no_std]
#![no_main]

psp::module!("PSP-RUST TEST", 1, 0);

mod gfx;

use psp::sys::{SceCtrlData, CtrlButtons, CtrlMode};

pub fn psp_main(){
    psp::enable_home_button();
    // psp::dprintln!("Hello world from Rust!");
    unsafe{
        psp::sys::sceCtrlSetSamplingCycle(0);
        psp::sys::sceCtrlSetSamplingMode(CtrlMode::Analog);

        let ctrl_data = &mut SceCtrlData::default();
        let mut renderer = gfx::Renderer::new();

        let mut rect_x = 0;
        let mut rect_y = 0;

        loop{
            psp::sys::sceCtrlReadBufferPositive(ctrl_data, 1);
            if ctrl_data.buttons.contains(CtrlButtons::UP){
                rect_y -= 1;
            }
            if ctrl_data.buttons.contains(CtrlButtons::DOWN){
                rect_y += 1;
            }
            if ctrl_data.buttons.contains(CtrlButtons::LEFT){
                rect_x -= 1;
            }
            if ctrl_data.buttons.contains(CtrlButtons::RIGHT){
                rect_x += 1;
            }

            renderer.clear(0xFFFFCA82);
            renderer.draw_rect(rect_x, rect_y, 30, 30, 0xFF00FFFF);
            renderer.swap_buffers();
            psp::sys::sceDisplayWaitVblankStart();

            
        }
       
    }
}