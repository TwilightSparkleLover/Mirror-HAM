
/*

   AFM v1.1 (w) 2001 by Silpheed/Hitmen, Groepaz/Hitmen  www.hitmen-console.org

   plays standard 4-Channel Protracker Modules (15.290khz Stereo)

   used resources:

   cpu: ~0x20 of 0xe4 Rasterlines = <15% (if all 4 channels active)

   .text section: ~0x1200 bytes
   .bss  section: ~0x0400 bytes

   internal RAM: 0x03000000-0x030003ff  0x0400 bytes mixing buffer
                 0x03000400-            <0x0100 bytes for mixing routines
                                        (exact value returned by afm_install)

                 if your linker script defines a section in internal RAM,
                 exclude 0x03000000-0x030004ff from that.

   Timers 0 and 1, DMA1+2 (for sound stream, always active)
   DMA3 (occasionaly used in mixer)

   NO external libraries required

 */
#ifndef _AFM_H_
#define _AFM_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
   install player/mixer

   you must call this function before calling any other of the
   players routines.

   returns first unused memory location in internal RAM

 */
extern unsigned long afm_install(void);
/*
   init modfile + soundsystem

   modfile must be a pointer to a standard 4-Channel Protracker Module

 */
extern void afm_init(unsigned char* modfile);
/*

    update player+mixing buffers

    you must call this once each frame (timing doesnt matter)

*/
extern void afm_update(void);
/*
    sync sound DMA

    you must call this right at the start of vblank (precise timing required)

*/
extern void afm_sync(void);
/*
    set sound parameters

    vol: 0x00...0x3f    master volume
    chn:                1: mono replay (somewhat louder)
                        any other: stereo replay

*/
extern void afm_sound_param(unsigned long vol,unsigned long chn);
/*
   shutdown the player+stop any sound

   after having called this routine, you must call afm_install before
   calling any other routines of the player.

 */
extern void afm_deinit(void);

#ifdef __cplusplus
}
#endif

#endif /* _AFM_H_ */
