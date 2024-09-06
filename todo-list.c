#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> // Required for malloc
#include <math.h>
#include <time.h>

typedef struct Item
{
    char name[200];
    char description[200];
    bool completed;
    struct Item *next;
    struct Item *subTask;
} Item;

Item *create_item(char *name, char *description) // function will return an Item struct pointer with the parameters being name str and desc str
{
    Item *item = (Item *)malloc(sizeof(Item)); // allocates empty memory space for the struct on the heap
    if (item == NULL)                          // outputs the error message and exit control if memory allocation fails
    {
        printf("Memory allocation failed!");
        exit(1);
    }

    strncpy(item->name, name, sizeof(item->name) - 1); // strncpy allows the parameter values to be copied into the allocated Item's attributes
    strncpy(item->description, description, sizeof(item->description) - 1);

    item->name[sizeof(item->name) - 1] = '\0'; // stops empty line from cont
    item->description[sizeof(item->description) - 1] = '\0';

    item->completed = false;

    item->next = NULL;    // sets the next pointer to NULL
    item->subTask = NULL; // sets the subTask pointer to NULL

    return item;
}

void link(Item *root, Item *newItem)
{
    Item *currentItem = root;
    while (currentItem->next != NULL)
    {
        currentItem = currentItem->next;
    }
    currentItem->next = newItem;
}

void sub_link(int choice, Item *root, Item *newItem)
{
    Item *currentItem = root->next; // start with the first real item, not root itself
    int count = 1;

    // Traverse to the item where we want to add the sub-item
    while (currentItem != NULL && count < choice)
    {
        currentItem = currentItem->next;
        count++;
    }

    if (currentItem == NULL)
    {
        printf("Invalid choice. No such item exists.\n");
        return;
    }

    // If there's no sub-task list, create a new one
    if (currentItem->subTask == NULL)
    {
        currentItem->subTask = newItem;
    }
    else
    {
        // If there's already a sub-task list, append the new sub-task
        link(currentItem->subTask, newItem);
    }
}

void display(Item *root)
{
    Item *currentItem = root->next;
    int count = 1;

    while (currentItem != NULL)
    {
        printf("%d: Name ---> %s | Description ---> %s\n", count, currentItem->name, currentItem->description);

        // Display sub-tasks if they exist
        if (currentItem->subTask != NULL)
        {
            Item *currentSub = currentItem->subTask;
            int subCount = 1; // Add numbering for sub-tasks
            while (currentSub != NULL)
            {
                printf("\tSub-task %d: Name ---> %s | Description ---> %s\n", subCount, currentSub->name, currentSub->description);
                currentSub = currentSub->next;
                subCount++;
            }
        }
        currentItem = currentItem->next;
        count++;
    }
}

void mark(Item *root, int choice)
{
    Item *currentItem = root->next;
    int count = 1;
    while (currentItem != NULL)
    {
        if (choice < count)
        {
            printf("The choice is not a number in the list!");
            break;
        }

        if (count == choice)
        {
            currentItem->completed = !currentItem->completed;
            break;
        }
        currentItem = currentItem->next;
        count++;
    }
    if (choice > count)
    {
        printf("The choice is not a number in the list!");
    }
}

int main()
{
    printf("Todo List\n");

    int choice = 0;
    char name[200];
    char description[200];
    int markedChoice;

    // Proper initialization of root
    Item *root = create_item("root", "root todo item");

    while (choice != 5)
    {
        printf("\n\nPick an option:\n1. View todo list.\n2. Create a todo item.\n3. Create todo sub-items.\n4. Tick off todo items.\n5. Exit.\nEnter single INT here:\t");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            display(root);
            break;

        case 2:
            printf("\nEnter name of todo item:\t");
            scanf("%s", name);
            printf("Enter description of todo item:\t");
            scanf("%s", description);

            Item *item = create_item(name, description);
            link(root, item);

            printf("Successfully added %s to the todo list!\n", name);
            break;

        case 3:
            printf("\nEnter name of todo item:\t");
            scanf("%s", name);
            printf("Enter description of todo item:\t");
            scanf("%s", description);

            Item *subItem = create_item(name, description);

            printf("Choose parent item for the sub task:\t");
            scanf("%d", &choice);

            sub_link(choice, root, subItem);

            break;

        case 4:
            printf("Enter the number of the todo list item you want to mark as complete/incomplete:\t");
            scanf("%d", &markedChoice);
            mark(root, markedChoice);
            break;

        case 5:
            printf("Exiting program.\n");
            break;

        default:
            printf("Invalid choice, please try again.\n");
            break;
        }
    }
    return 0;
}
