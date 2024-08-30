#include <libc.h>
#include <pthread.h>

void    *allo(void *param)
{
    while (1)
    {
        printf("enter n : ");
        int n;scanf("%d", &n);
        if (n == 0)
            break ;
    }
    return NULL;
}

int main()
{
    pthread_t t;
    pthread_create(&t, NULL, (void *)allo, NULL);
    pthread_join(t, NULL);
    printf("hna\n");
}