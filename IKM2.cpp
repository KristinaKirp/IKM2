#include "Header.h"

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    ballGame gameSession;
    gameSession.run();

    return 0;
}

