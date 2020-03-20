#include <iostream>

int main()
{
    int res = system("python gen.py");
    if (res != 0)
        printf("Exit code was: %d", res);

    return 0;
}