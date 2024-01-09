#include "shell.h"

/**
 * add_node - Adds a new node at the beginning of a linked list
 * @head: pointer to the address of the first part of the node
 * @str: string within the list (node)
 * @num: index
 * Return: size of the node/list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_headnode;

	if (!head) /* if (head == NULL) */
		return (NULL);
	new_headnode = malloc(sizeof(list_t));
	if (!new_headnode)
		return (NULL);
	_memset((void *)new_headnode, 0, sizeof(list_t));
	new_headnode->num = num;
	if (str) /* if (str == TRUE || str != NULL) */
	{
		new_headnode->str = _strdup(str);
		if (!new_headnode->str)
		{
			free(new_headnode);
			return (NULL);
		}
	}
	new_headnode->next = *head;
	*head = new_headnode;
	return (new_headnode); /* return (*head) */
}

/**
 * add_node_end - Adds a new node at the end of a linked list
 * @head: pointer to the address of the first part of the node
 * @str: string within the list (node)
 * @num: index
 * Return: size of the node/list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *extra_node, *temp;

	if (!head)
		return (NULL);

	temp = *head;
	extra_node = malloc(sizeof(list_t));
	if (!extra_node)
		return (NULL);
	_memset((void *)extra_node, 0, sizeof(list_t));
	extra_node->num = num;
	if (str)
	{
		extra_node->str = _strdup(str);
		if (!extra_node->str)
		{
			free(extra_node);
			return (NULL);
		}
	}
	if (temp)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = extra_node;
	}
	else
		*head = extra_node;
	return (extra_node);
}

/**
 * delete_node_at_index - Deletes a node at a given index
 * @head: pointer to the address of the first part of the node
 * @index: node index to be removed
 * Return: 1 (Success), 0 (Failure)
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node1, *node2;
	unsigned int n = 0;

	if (!head || !*head) /* because head is a double pointer */
		return (0);

	if (!index) /* if (index == NULL) */
	{
		node1 = *head;
		*head = (*head)->next;
		free(node1->str);
		free(node1);
		return (1);
	}
	node1 = *head; /* Initialise node1 again for new code sec */
	while (node1)
	{
		if (n == index)
		{
			node2->next = node1->next;
			free(node1->str);
			free(node1);
			return (1);
		}
		node2 = node1;
		node1 = node1->next;
		n++;
	}
	return (0);
}

/**
 * print_list_str - Prints ONLY the string (str) element of a list
 * @h: pointer to the head node of the linked list
 * Return: size of node/list
 */
size_t print_list_str(const list_t *h)
{
	size_t metric = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		metric++;
	}
	return (metric);
}

/**
 * free_list - Frees every node within a linked list
 * @head_ptr: pointer to head node address
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *temp = *head_ptr, *new_node;

	if (!head_ptr || !*head_ptr) /* head_ptr is a double pointer */
		return;

	while (temp)
	{
		new_node = temp->next;
		free(temp->str);
		free(temp);
		temp = new_node;
	}
	*head_ptr = NULL; /* head is set to 0 to indicate empty list */
}
