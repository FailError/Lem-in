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