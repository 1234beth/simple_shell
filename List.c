#include "shell.h"

/**
 * add_node - Add a node to the beginning of the linked list.
 * @head: Address of the pointer to the head node.
 * @str: String to be stored in the node.
 * @num: Index or number associated with the node.
 *
 * This function adds a new node to the beginning of the linked list.
 * If 'str' is not NULL, it duplicates the string and stores it in the node.
 *
 * Return: Address of the newly created node or NULL on failure.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
    list_t *new_head;

    if (!head)
        return (NULL);

    new_head = malloc(sizeof(list_t));
    if (!new_head)
        return (NULL);

    _memset((void *)new_head, 0, sizeof(list_t));
    new_head->num = num;

    if (str)
    {
        new_head->str = _strdup(str);
        if (!new_head->str)
        {
            free(new_head);
            return (NULL);
        }
    }

    new_head->next = *head;
    *head = new_head;
    return (new_head);
}

/**
 * add_node_end - Add a node to the end of the linked list.
 * @head: Address of the pointer to the head node.
 * @str: String to be stored in the node.
 * @num: Index or number associated with the node.
 *
 * This function adds a new node to the end of the linked list.
 * If 'str' is not NULL, it duplicates the string and stores it in the node.
 *
 * Return: Address of the newly created node or NULL on failure.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
    list_t *new_node, *node;

    if (!head)
        return (NULL);

    node = *head;
    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return (NULL);

    _memset((void *)new_node, 0, sizeof(list_t));
    new_node->num = num;

    if (str)
    {
        new_node->str = _strdup(str);
        if (!new_node->str)
        {
            free(new_node);
            return (NULL);
        }
    }

    if (node)
    {
        while (node->next)
            node = node->next;
        node->next = new_node;
    }
    else
        *head = new_node;

    return (new_node);
}

/**
 * print_list_str - Print only the 'str' element of a list_t linked list.
 * @h: Pointer to the first node of the list.
 *
 * This function prints the 'str' element of each node in the linked list.
 *
 * Return: The number of nodes in the list.
 */
size_t print_list_str(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        h = h->next;
        i++;
    }

    return (i);
}

/**
 * delete_node_at_index - Delete a node at a given index.
 * @head: Address of the pointer to the first node.
 * @index: Index of the node to delete.
 *
 * This function deletes a node at the specified index in the linked list.
 *
 * Return: 1 if successful, 0 on failure.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
    list_t *node, *prev_node;
    unsigned int i = 0;

    if (!head || !*head)
        return (0);

    if (!index)
    {
        node = *head;
        *head = (*head)->next;
        free(node->str);
        free(node);
        return (1);
    }

    node = *head;

    while (node)
    {
        if (i == index)
        {
            prev_node->next = node->next;
            free(node->str);
            free(node);
            return (1);
        }
        i++;
        prev_node = node;
        node = node->next;
    }

    return (0);
}

/**
 * free_list - Free all nodes of a linked list.
 * @head_ptr: Address of the pointer to the head node.
 *
 * This function frees all nodes and their associated memory in the linked list.
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
    list_t *node, *next_node, *head;

    if (!head_ptr || !*head_ptr)
        return;

    head = *head_ptr;
    node = head;

    while (node)
    {
        next_node = node->next;
        free(node->str);
        free(node);
        node = next_node;
    }

    *head_ptr = NULL;
}
