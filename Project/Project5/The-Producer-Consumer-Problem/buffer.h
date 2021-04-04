typedef int buffer_item;
#define BUFFER_SIZE 5

void init();

int insert_item(buffer_item item);

int remove_item(buffer_item *item);
