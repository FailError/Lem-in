//t_rooms *ft_push_back(t_rooms *head, char *str)
//{
//	t_rooms *ptr = head;
//	while(ptr->next != NULL)
//		ptr = ptr->next;
//	t_rooms *newnode = ft_create();
//	ptr->next = newnode;
//	newnode->next = NULL;
//	newnode->prev = ptr;
//	head->prev = newnode;
//
//	newnode->name = (char *) malloc(sizeof(char) * 5);
//	ft_strlcat(newnode->name, str, 5);
//	newnode->name[4] = '\0';
//	return (head);
//}



///- work
//5
//#Here is the number of lines required: 33
//##start
//	Qjs3 1 1
//##end
//	Ivv5 2 2
//Pty7 3 3
//Qjs3-Ivv5
//	Qjs3-Pty7
//	Pty7-Ivv5
//#Here is the number of lines required: 33