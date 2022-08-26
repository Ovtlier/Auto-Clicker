// Author: Rodney Boyce

#include "stdio.h"
#include "Windows.h"
#include "time.h"

DWORD WINAPI ThreadFunc(void* data);
void mouseClick();
int delayBetweenClicks();
int delayBetweenUpDown();

int main(void) {
    srand(time(NULL));
    Sleep(1000);
    HANDLE thread1 = CreateThread(NULL, 0, ThreadFunc, NULL, 4, NULL);
    int isSuspended = 1;
    while (TRUE) {
        if ((GetAsyncKeyState(VK_MBUTTON) & 0x8000) && isSuspended) {
            printf("Autoclicker: ON\n");
            isSuspended = 0;
            ResumeThread(thread1);
            Sleep(5000);
        } else if ((GetAsyncKeyState(VK_MBUTTON) & 0x8000) && !isSuspended) {
            printf("Autoclicker: OFF\n");
            isSuspended = 1;
            SuspendThread(thread1);
            Sleep(5000);
        }
        Sleep(1);
    }

/*    while (TRUE) {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            printf("Autoclicker: ON\n");
            int keepLooping = TRUE;
            while (keepLooping) {
                mouseClick();
                int sleepDuration = delayBetweenClicks();
                for (int i = 0; i < sleepDuration; i++) {
                    printf("Sleeping...    %d\n", i);
                    if (GetAsyncKeyState(VK_MBUTTON) & 0x8000) {
                        keepLooping = FALSE;
                        break;
                    }
                }
            }
        }
    }
*/

}

DWORD WINAPI ThreadFunc(void *data) {
    while (TRUE) {
        mouseClick();
        Sleep(delayBetweenClicks());
    }
    return 0;
}

void mouseClick() {
    INPUT inputClick = {0};

    inputClick.type = INPUT_MOUSE;
    inputClick.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &inputClick, sizeof(inputClick));

    ZeroMemory(&inputClick, sizeof(inputClick));

    delayBetweenUpDown();

    inputClick.type = INPUT_MOUSE;
    inputClick.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &inputClick, sizeof(inputClick));
}

int random(int min, int max){
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

int delayBetweenClicks() {
    int num = 0;

    int probability = random(0, 1000);
    if (probability < 100) {
        if (probability < 1) {
            num = random(2000, 20000);
        } else {
            num = random(1000, 2000);
        }
    } else if (probability < 200) {
        num = random(500, 1000);
    } else {
        num = random(200, 500);
    }
    printf("Delay: %d\n", num);
    return num;
}

int delayBetweenUpDown() {
    int num = 0;
    int probability = random(0, 1000);
    if (probability > 900) {
        num = random(45, 59);
    } else if (probability < 100) {
        num = random(81, 150);
    } else {
        num = random(60, 80);
    }
    return num;
}