#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char address_filename[20];

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Error! Please input the name of the address file!\n");
        return -1;
    }

    strcpy(address_filename, argv);

    FILE *addresses = fopen(address_filename, "r");
    int log_address = 0;
    while (!feof(addresses))
    {
        fscanf(addresses, "%d", &log_address);
    }

    return 0;
}