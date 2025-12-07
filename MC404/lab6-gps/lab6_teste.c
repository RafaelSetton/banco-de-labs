#include <stdio.h>

int main()
{

    int err = 0, crt = 0;
    for (int i = 10; i < 1000; i++)
    {
        int s = i / 2;
        for (int j = 0; j < 10; j++)
        {
            s = (s + i / s) / 2;
        }
        int diff = s - i / s;
        printf("sqrt(%d) = %d\n", i, s);
        if (diff > 10 || diff < -10)
            err++;
        else
            crt++;
    }

    printf("%d x %d\n", crt, err);
}