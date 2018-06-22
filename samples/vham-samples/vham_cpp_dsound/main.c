/*********************************************************************************
 * Includes
 ********************************************************************************/
// Basically, first, as on top of all HAM files, the most
// important include is the mygba.h, which contains all the
// macro definitions, and the HAMlib function prototypes.
#include "mygba.h"

/*********************************************************************************
 * Defines
 ********************************************************************************/
// Set the master mixer frequency (maximum bitrate)
// Note that not all values guarantee clickless playback
// please choose from one of these values:
// 5733  Hz   6689 Hz  10512 Hz   11467 Hz
// 13379 Hz  18157 Hz  20068 Hz   21024 Hz
// 26757 Hz  31536 Hz  36314 Hz   40136 Hz
// 42048 Hz  54471 Hz
#define MIXER_FREQ 26757


/*********************************************************************************
 * Global Variables
 ********************************************************************************/
bool g_NewFrame=FALSE;
u8   g_CpuTime=0;
u32  g_Frames=0;
// pointers to sample data converted using the wav2gba tool
extern const WaveData _binary_bfly_raw_start;
extern const WaveData _binary_sound2_raw_start;


/*********************************************************************************
 * Prototypes
 ********************************************************************************/
void vblFunc(void);


/*********************************************************************************
 * Program entry point
 ********************************************************************************/
int main(void)
{
   sample_info *mysample[2];
   
   // Initialize HAMlib
   // Then we call the single most important function of ham, ham_Init .
   // This function must be called first thing when working with HAMlib,
   // because all ham_* functions will only work correctly after this has been called.
   // Behaviour of HAMlib is undefined if you comment this out.
   ham_Init();

    // Init the Text display system on the bg of your choice
    // This function must be called if you want to use HAMlibs text display system.
    // After calling this, you can use ham_DrawText and ham_SetTextCol.
    ham_InitText(0);

    // Draws Text. Be aware that this function is SLOW.
    // It should only be used for debug purposes.
	ham_DrawText(2,2, "HAM direct sound example");
   	ham_DrawText(2,4, "Mixer   freq: %6d",MIXER_FREQ);
   	ham_DrawText(2,16,"Press Up/down/left/right");
   	ham_DrawText(2,17,"to change the bitrates");
   	ham_DrawText(2,18,"and A to mix another sound");
   
	// Initializes the ham Direct Sound mixer.
    // To ensure click less playback, set your Mixer to a frequency outlined above.
    // Other frequencies might play back fine, but these are safer to use, the ones
    // above fit the timing of the GBA best. After you Initialized your Mixer, you must
    // call ham_SyncMixer in your VBL handler, at the very top, and also ham_UpdateMixer
    // once per frame, where does not matter.
	ham_InitMixer(MIXER_FREQ);


	// Use this function to initialize a Sample for later playing using ham_PlaySample.
    // The parameters are quite easy to figure out, just make sure your data pointer
    // actually points to a raw, 8bit, mono signed sound sample.
	mysample[0] =  ham_InitSample((u8*)_binary_bfly_raw_start.data,  // the pointer to your RAW 8bit signed sound data
                   _binary_bfly_raw_start.size,                      // the length of the sound data, in bytes
                   _binary_bfly_raw_start.freq>>10);                 // the bitrate of the sound data, in Hz

	mysample[1] =  ham_InitSample((u8*)_binary_sound2_raw_start.data,// the pointer to your RAW 8bit signed sound data
                   _binary_sound2_raw_start.size,                    // the length of the sound data, in bytes
                   _binary_sound2_raw_start.freq>>10);               // the bitrate of the sound data, in Hz

    // Will, once activated, trigger the specified interrupt,
    // and then call the function specified
    ham_StartIntHandler(INT_TYPE_VBL,         // The Interrupts ID you want to start.
                        (void *)&vblFunc);    // The adress of a function that should be called when the interrupt is fired


    // Loop
	while(1)
	{
        // New Frame?
        if(g_NewFrame)
        {
            if(F_VCNT_CURRENT_SCANLINE==0)
            {
                // Use this function to mix new sound data once per frame,
                // which will get played on the next call to ham_SyncMixer .
                // You must invoke this function once per frame, where does not really matter.
                ham_UpdateMixer();

                //see how much CPU time has passed
                g_CpuTime=F_VCNT_CURRENT_SCANLINE;
                g_CpuTime=g_CpuTime*0.44;

                // now see if we want to do some pitch shifting
                if(F_CTRLINPUT_DOWN_PRESSED)
                {
                    mysample[0]->bitrate-=10;
                    ham_ChangeSampleBitrate(mysample[0],mysample[0]->bitrate);
                }

                if(F_CTRLINPUT_UP_PRESSED)
                {
                    mysample[0]->bitrate+=10;
                    ham_ChangeSampleBitrate(mysample[0],mysample[0]->bitrate);
                }

                if(F_CTRLINPUT_LEFT_PRESSED)
                {
                    mysample[1]->bitrate-=10;
                    ham_ChangeSampleBitrate(mysample[1],mysample[1]->bitrate);
                }

                if(F_CTRLINPUT_RIGHT_PRESSED)
                {
                    mysample[1]->bitrate+=10;
                    ham_ChangeSampleBitrate(mysample[1],mysample[1]->bitrate);
                }

                // now check if A was pressed
                if(F_CTRLINPUT_A_PRESSED)
                {	
                    //if sample not already playing
                    if(!mysample[1]->playing)
                    ham_PlaySample(mysample[1]);
                }

                // if sample not already playing
                if(!mysample[0]->playing)
                {
                    //start playing the sample
                    ham_PlaySample(mysample[0]);
                }

                // Draws Text. Be aware that this function is SLOW.
                // It should only be used for debug purposes.
                ham_DrawText(2,8,  "Sample  freq: %6d",mysample[0]->bitrate);
                ham_DrawText(2,9,  "Sample2 freq: %6d",mysample[1]->bitrate);
                ham_DrawText(2,14,"CPU percent: %6d",g_CpuTime);

                g_NewFrame=FALSE;
            }
        }
    }
}

/*********************************************************************************
 * vblFunc(void)
 *
 * This function is called whenever the GBA is about
 * to draw a new picture onto the screen.
 ********************************************************************************/
void vblFunc(void)
{
	//Sync mixer, this should always be
	//called right at the VBL Start
	ham_SyncMixer();

	g_Frames++;
	g_NewFrame=TRUE;
}
