#include <iostream>

int main()
{
    int res = system("python gen_image.py");
    if (res != 0)
        printf("Exit code was: %d", res);

    return 0;
}