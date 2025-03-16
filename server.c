#include "minitalk.h"

volatile sig_atomic_t byte = 0;
volatile sig_atomic_t bit_count = 0;


void handle_sigusr1(int sig)
{
    byte = (byte << 1) | 0;
    bit_count++;

    if(bit_count == 8)
    {
        char c = (char)byte;
        write(1, &c, 1);
        byte = 0;
        bit_count = 0;
    }
   // printf("\n");
}

void handle_sigusr2(int sig)
{
    byte = (byte << 1) | 1;
    bit_count++;
    if(bit_count == 8)
    {
        char c = (char)byte;
        write(1, &c, 1);
        byte = 0;
        bit_count = 0;
    }
    //printf("\n");

}


int main()
{
    signal(SIGUSR1, handle_sigusr1);
    signal(SIGUSR2, handle_sigusr2);
    int pid = (int)getpid();
    ft_putstr("Server pid ");
    ft_putnbr(pid);
    ft_putstr("\n");
    while(1)
    {
        pause();
    }
    return (0);
}