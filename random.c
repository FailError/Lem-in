//int lastZ;
//int izA = 1;
//lastZ = arr->length - 1;
//if(arr->in_array[lastZ - 1]->ant_n)
//{
//ft_printf("L%d-%s", arr->in_array[lastZ - 1]->ant_n, arr->in_array[lastZ]);
//lastZ--;
//}
//while(lastZ != 1)
//{
//
//lastZ--;
//}
//if(*ants_ostatok > arr->expression)
//{
//arr->in_array[izA]->ant_n = *ants_current;
//ft_printf("L%d-%s ", *ants_current, arr->in_array[izA]->name);
//*ants_current += 1;
//*ants_ostatok -= 1;
//arr->in_array[arr->length - 1]->itogo++;
//}
/////проверка expressiona кстати count в z++;










//	i = 0;
//	while(ft_strcmp(w->in_array[i]->name, points->second->name))
//		i++;
//	i += 1;
//	while(w->in_array[i++])
//		a++;

//void push_v_list(t_ways *list_ways, t_ways *new, t_point *points)
//{
//	t_ways *new_path;
//	t_list *list;
//	t_rooms *read_n;
//	char *read_o;
//
//	list = list_ways->way_t;
//
//	read_o = points->second->name;
//	while(list)
//	{
//		read_n = new->way_t->content;
//		if(ft_strcmp(read_n->name, read_o) == 0)
//		{
//
//		}
//		list = list->next;
//	}
//}


//int		reverse_path(t_rooms **queue, int end, t_ways *list_ways)
//{
//	t_rooms *t_reader;
//	t_list	*cur_list;
//
//	t_reader = queue[end];
//	list_ways->way_t = queue[end];
//	cur_list = list_ways->way_t->links;
//	while(t_reader->lvl != 0)
//	{
//		t_reader = cur_list->content;
//		if(t_reader->lvl == list_ways->way_t->lvl - 1)
//		{
//			push_path(&list_ways->way_t, t_reader);
//			t_reader->mark = t_reader->lvl != 0 ? 1 : 0;
//			if(list_ways->way_t->lvl == 0)
//				return (1);
//			cur_list = t_reader->links;
//		}
//		else
//			cur_list = cur_list->next;
//		//end--;
//	}
//	return (0);
//}

//ft_lstadd(&first->links, ft_lstnew2(second));
//ft_lstadd(&second->links, ft_lstnew2(first));

//t_ways		*reverse_path(t_rooms **queue, t_rooms *last, t_list *t_lst) //t_lst - ласт комната
//{
//	t_rooms *t_reader;
//	t_list	*cur_list;
//	t_ways *new;
//	int steps;
//
//	new = (t_ways *) ft_memalloc(sizeof(t_ways));
//	steps = last->lvl; //queue[end]->lvl;
//	new->way_t = last;//queue[end]; ///если реверс пути то first //[0]
//	new->length++;
//	while (steps > 0)
//	{
//		cur_list = new->way_t->links;
//		while (cur_list != NULL)
//		{
//			t_reader = cur_list->content;
//			if (t_reader->lvl == new->way_t->lvl - 1) ///если реверс пути то +1
//			{
//				t_room_add(&new->way_t, t_reader);
//				cur_list = t_reader->links;
//				steps--;
//				new->length++;
//				break ;
//			}
//			cur_list = cur_list->next;
//		}
//	}
//	return (new);
//}

//4
//#Here is the number of lines required: 33
//##start
//A 2 2
//B 1 1
//##end
//Z 8 8
//C 3 3
//D 4 4
//E 5 5
//F 6 6
//G 7 7
//A-D
//A-B
//D-A
//D-E
//B-A
//B-C
//B-G
//E-D
//E-C
//G-B
//G-F
//C-E
//C-B
//C-Z
//F-G
//F-Z
//Z-C
//Z-F
//#Here is the number of lines required: 33