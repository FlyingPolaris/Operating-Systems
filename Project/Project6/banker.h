#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 4

int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

int request_resources(int num, int request[]);
int release_resources(int num, int release[]);
int read_file();
int check_safe(int allocation[][NUMBER_OF_RESOURCES], int need[][NUMBER_OF_RESOURCES], int available[]);
void print_resources();