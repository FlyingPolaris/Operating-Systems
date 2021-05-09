#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAGE_SIZE 256
#define FRAME_SIZE 256
#define PAGE_ENTRIES_NUM 256
#define FRAME_ENTRIES_NUM 256
#define TLB_ENTRIES_NUM 16

typedef struct
{
    int latest_used;
    int page_number;
    int frame_number;
} TLB;

typedef struct
{
    int valid;
    int frame_number;
} PAGE;

typedef struct
{
    int latest_used;
    char data[PAGE_SIZE];
} FRAME;

TLB tlb[TLB_ENTRIES_NUM];
PAGE pagetable[PAGE_ENTRIES_NUM];
FRAME memory[FRAME_ENTRIES_NUM];

char address_filename[20];
int clk;

void tlb_update(int page_number, int frame_number)
{
    int min_time = __INT_MAX__;
    int min_tlb_number = -1;
    for (int i = 0; i < TLB_ENTRIES_NUM;++i)
    {
        if(tlb[i].latest_used < min_time)
        {
            min_time = tlb[i].latest_used;
            min_tlb_number = i;
        }
    }
    tlb[min_tlb_number].frame_number = frame_number;
    tlb[min_tlb_number].page_number = page_number;
    tlb[min_tlb_number].latest_used = clk;
}

void init()
{
    for (int i = 0; i < TLB_ENTRIES_NUM;++i)
    {
        tlb[i].frame_number = tlb[i].page_number = tlb[i].latest_used = -1;
    }
    for (int i = 0; i < PAGE_ENTRIES_NUM;++i)
    {
        pagetable[i].frame_number = -1;
        pagetable[i].valid = 0;
    }
    for (int i = 0; i < FRAME_ENTRIES_NUM;++i)
    {
        memory[i].latest_used = -1;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Error! Please input the name of the address file!\n");
        return -1;
    }

    strcpy(address_filename, argv[1]);

    FILE *addresses = fopen(address_filename, "r");
    FILE *backing_store = fopen("BACKING_STORE.bin", "rb");
    FILE *out = fopen("out.txt", "w");

    int logical_address = 0;
    int pagefault, tlb_miss;
    double pagefault_number = 0, tlb_hit_number = 0;
    int page_offset, page_number, frame_number;
    int physical_address = 0;
    int value;

    init();
    clk = 0;

    fscanf(addresses, "%d", &logical_address);
    while (!feof(addresses))
    {
        clk++;
        pagefault = tlb_miss = 1;
        page_offset = logical_address & 0xff;
        page_number = (logical_address >> 8) & 0xff;

        for (int i = 0; i < TLB_ENTRIES_NUM; ++i)
        {
            if (tlb[i].page_number == page_number)
            {
                tlb_hit_number++;
                tlb_miss = pagefault = 0;
                frame_number = tlb[i].frame_number;
                tlb[i].latest_used = clk;
                memory[frame_number].latest_used = clk;
                break;
            }
        }

        if (tlb_miss && pagetable[page_number].valid == 1)
        {
            pagefault = 0;
            frame_number = pagetable[page_number].frame_number;
            tlb_update(page_number, frame_number);
            memory[frame_number].latest_used = clk;
        }
        else if (pagefault)
        {
            pagefault_number++;
            pagetable[page_number].valid = 1;
            int min_time = __INT_MAX__;
            int min_frame_number = -1;
            for (int i = 0; i < FRAME_ENTRIES_NUM; ++i)
            {
                if (memory[i].latest_used < min_time)
                {
                    min_time = memory[i].latest_used;
                    min_frame_number = i;
                }
            }
            for (int i = 0; i < PAGE_ENTRIES_NUM; ++i)
            {
                if (pagetable[i].frame_number == min_frame_number && pagetable[i].valid == 1)
                {
                    pagetable[i].valid = 0;
                    break;
                }
            }
            memory[min_frame_number].latest_used = clk;
            fseek(backing_store, page_number * PAGE_SIZE, SEEK_SET);
            fread(memory[min_frame_number].data, sizeof(char), FRAME_SIZE, backing_store);

            frame_number = pagetable[page_number].frame_number = min_frame_number;
            tlb_update(page_number, frame_number);
        }
        physical_address = frame_number * FRAME_SIZE + page_offset;
        value = memory[frame_number].data[page_offset];
        fprintf(out, "Virtual address: %d Physical address: %d Value: %d\n", logical_address, physical_address, value);
        fscanf(addresses, "%d", &logical_address);
    }
    fclose(out);
    fclose(addresses);
    fclose(backing_store);

    printf("TLB hit rate is %f, page fault rate is %f.\n", tlb_hit_number/clk, pagefault_number/clk);

    return 0;
}