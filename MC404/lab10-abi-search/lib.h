typedef struct Node
{
    int val1, val2;
    struct Node *next;
} Node;

int linked_list_search(Node *head_node, int val);
void puts(const char *str);
char *gets(char *str);
int atoi(const char *str);
char *itoa(int value, char *str, int base);
void exit(int code);