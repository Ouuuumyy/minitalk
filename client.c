#include "minitalk.h"


void send_signal(int bit, pid_t server_pid)
{
    if(bit == 0)
        if(kill(server_pid, SIGUSR1))
        {
            ft_putstr("Error: failed to send SIGUSR1.\n");
            exit(1);
        }
    if(bit == 1)
        if(kill(server_pid, SIGUSR2))
        {
            ft_putstr("Error: failed to send SIGUSR2.\n");
            exit(1);
        }
}
void send_new_line(int bit, pid_t server_pid)
{
    char c;
    int j;

    c = '\n';
    j = 7;
    while(j >= 0)
    {
        bit = (c >> j) & 1;
        send_signal(bit, server_pid);
        usleep(500);
        j--;
    }
}
void send_crypted_message(char *message, pid_t server_pid)
{
    int i;
    int j;
    int bit;
    char c;

    i = 0;
  
    bit = 0;
    while(message[i])
    {
        c = message[i];
        j = 7;
        while(j >= 0)
        {
            bit = (c >> j) & 1;
            send_signal(bit, server_pid);
            usleep(500);
            j--;
        }
        i++;
    }
    send_new_line(bit, server_pid);
}

int main(int ac, char **av)
{
    int i;

    i = 0;
    if(ac != 3)
    {
        printf("Enter: <program name> <server pid> <message>\n");
        return (1);
    }
    pid_t server_pid = ft_atoi(av[1]);
    if(server_pid < 0 && server_pid > 99999)
    {
        ft_putstr("Error: inavalid server PID.\n");
        exit (1);
    }
    char *message = av[2];
    send_crypted_message(message, server_pid);
    return 0;
}

