/*
HAM Direct Sound simple demonstration
*/

#include "mygba.h"

// Set the master mixer frequency (maximum bitrate)
// Note that not all values guarantee clickless playback
// please choose from one of these values:
// 5733  Hz   6689 Hz  10512 Hz   11467 Hz
// 13379 Hz  18157 Hz  20068 Hz   21024 Hz
// 26757 Hz  31536 Hz  36314 Hz   40136 Hz
// 42048 Hz  54471 Hz

#define MIXER_FREQ 26757

bool newframe=FALSE;
u8 cputime=0;
u32 frames=0;

// pointers to sample data converted using the wav2gba tool
extern const WaveData _binary_bfly_raw_start;
extern const WaveData _binary_sound2_raw_start;



// this function gets called once / frame 
void VblFunc(void)
{
	//Sync mixer, this should always be 
	//called right at the VBL Start
	ham_SyncMixer();

	frames++;
	newframe=TRUE;
}

// main entry point of the application
int main(void)
{
	sample_info *mysample[2];
   
	// Initialize HAMlib
	ham_Init();
	ham_InitText(0);

	ham_DrawText(2,2, "HAM direct sound example");
   	ham_DrawText(2,4, "Mixer   freq: %6d",MIXER_FREQ);
   	ham_DrawText(2,16,"Press Up/down/left/right");
   	ham_DrawText(2,17,"to change the bitrates");
   	ham_DrawText(2,18,"and A to mix another sound");
   
	// Initalize the Sound Mixing at 20068 Hz
	ham_InitMixer(MIXER_FREQ);

	// Start VBL processing
	ham_StartIntHandler(INT_TYPE_VBL,&VblFunc);

	// Set up the Samples
	mysample[0] =  ham_InitSample((u8*)_binary_bfly_raw_start.data,
                   _binary_bfly_raw_start.size,
                   _binary_bfly_raw_start.freq>>10);
	mysample[1] =  ham_InitSample((u8*)_binary_sound2_raw_start.data,
                   _binary_sound2_raw_start.size,
                   _binary_sound2_raw_start.freq>>10);

	while(1)
	{
		if(newframe)
		{
			if(F_VCNT_CURRENT_SCANLINE==0)
			{
				//update the mixer once per frame
				ham_UpdateMixer();         
				
				//see how much CPU time has passed
				cputime=F_VCNT_CURRENT_SCANLINE;
				cputime=cputime*0.44;
				
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

				//now check if A was pressed
				if(F_CTRLINPUT_A_PRESSED)
				{	
					//if sample not already playing
					if(!mysample[1]->playing)
						ham_PlaySample(mysample[1]);
				}

				//if sample not already playing
				if(!mysample[0]->playing)
				{
					//start playing the sample
					ham_PlaySample(mysample[0]);
				}
				//and print some info on whats going on
				ham_DrawText(2,8,  "Sample  freq: %6d",mysample[0]->bitrate);
				ham_DrawText(2,9,  "Sample2 freq: %6d",mysample[1]->bitrate);
				
				ham_DrawText(2,14,"CPU percent: %6d",cputime);
				
				newframe=FALSE;

			}
		}
	}    
}

