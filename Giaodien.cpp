// Xay dung giao dien chuong trinh sau khi chay
#include <iostream>
#include <windows.h>   // d? d?i m�u v� ch?nh console
#include <cstdlib>
using namespace std;

void resizeConsole(int width, int height) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT DisplayArea = {0, 0, static_cast<short>(width), static_cast<short>(height)};
    SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void hienThiGiaoDien() {
    setColor(9); // M�u xanh duong

    cout << R"(  
   ____                      _             _______ _            __      ___            
  / __ \                    | |           |__   __| |           \ \    / (_)           
 | |  | |_   _  __ _ _ __   | |    _   _     | |  | |__  _   _   \ \  / / _  ___ _ __  
 | |  | | | | |/ _` | '_ \  | |   | | | |    | |  | '_ \| | | |   \ \/ / | |/ _ \ '_ \ 
 | |__| | |_| | (_| | | | | | |___| |_| |    | |  | | | | |_| |    \  /  | |  __/ | | |
  \___\_\\__,_|\__,_|_| |_| |______\__, |    |_|  |_| |_|\__,_|     \/   |_|\___|_| |_|
                                    __/ |                                              
                                   |___/    								   
 )" << endl;

    setColor(7); // Reset v? m�u tr?ng
}

int main() {
    // �?t m� h�a v� k�ch thu?c console
    system("chcp 65001 > nul"); // UTF-8 d? tr�nh l?i font
    system("mode con: cols=160 lines=50");
    resizeConsole(160, 50);

    hienThiGiaoDien();

    cout << "\n\nNhan phim bat ky de thoat...";
    cin.get();
    return 0;
}								                                              
