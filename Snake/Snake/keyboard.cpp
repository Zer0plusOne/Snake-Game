#include <Windows.h>

//Function to check if W is pressed
bool IsWPressed() {
    return GetAsyncKeyState('W') & 0x8000;
}

//Function to check if A is pressed
bool IsAPressed() {
    return GetAsyncKeyState('A') & 0x8000;
}

//Function to check if S is pressed
bool IsSPressed() {
    return GetAsyncKeyState('S') & 0x8000;
}

//Function to check if D is pressed
bool IsDPressed() {
    return GetAsyncKeyState('D') & 0x8000;
}