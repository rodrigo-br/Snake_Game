#include "SnakeGame.hpp"
#include <iostream>
#include <SDL2/SDL.h>

#define BOARD_DIM 10
#define HEIGHT BOARD_DIM
#define WIDTH BOARD_DIM * 2.5
#define FILE "./audio.wav"

struct AudioData
{
	Uint8 *pos;
	Uint32 length;
};

void my_audio_call_back(void *userdata, Uint8 *stream, int streamLenght)
{
	AudioData *audio = (AudioData *)userdata;

	if (audio->length == 0)
		return;

	Uint32 lenght = (Uint32)streamLenght;
	lenght = (lenght > audio->length ? audio->length : lenght);
	SDL_memcpy(stream, audio->pos, lenght);

	audio->pos += lenght;
	audio->length -= lenght;
}

int main(void)
{
	initscr();
	refresh();

	noecho();
	curs_set(0);

	SDL_Init(SDL_INIT_AUDIO);
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8 *wavBuffer;

	if (SDL_LoadWAV(FILE, &wavSpec, &wavBuffer, &wavLength) == NULL) {
		std::cerr << "Error loading wav file" << std::endl;
		return 1;
	}

	AudioData audio = { wavBuffer, wavLength };

	wavSpec.callback = my_audio_call_back;
	wavSpec.userdata = &audio;

	SDL_AudioDeviceID deviceID = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);
	if (deviceID == 0) {
		std::cerr << "Error opening audio device" << std::endl;
		return 2;
	}
	SDL_PauseAudioDevice(deviceID, 0);

	SnakeGame snake(HEIGHT, WIDTH);


	while (!snake.is_game_over()) {
		snake.process_input();
		snake.update_state();
		snake.redraw();
	}

	SDL_CloseAudioDevice(deviceID);
	SDL_FreeWAV(wavBuffer);
	SDL_Quit();
	getch();
	endwin();
	return (0);
}
