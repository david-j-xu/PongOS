int main() {
    char* video_memory = (char*)0xb8000;
    video_memory[0] = 'H';

    return 0;
}