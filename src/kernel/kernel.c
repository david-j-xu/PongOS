#define NULL 0x0

void _start() {
    char* video_memory = (char*)0xb8000;
    video_memory[0] = 'H';
}
