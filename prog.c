#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
struct my_node{
	struct my_node *prev;
	int info;
	struct my_node *next;
};
typedef struct my_node node;
void add_first(node**, node**, int);
void add_last(node**, node**, int);
void add_before(node**, node**, int, int);
void add_after(node**, node**, int, int);
void display(node*);
void del_first(node**, node**);
void del_last(node**, node**);
void del_node(node**, node**, int);
int main()
{
	node *start=NULL, *end=NULL;
	int n,item,loc;
	do{
		system("cls");
		printf("1. Add First\n");
		printf("2. Add Last\n");
		printf("3. Add Before\n");
		printf("4. Add After\n");
		printf("5. Del First\n");
		printf("6. Del Last\n");
		printf("7. Del Node\n");
		printf("8. Display\n");
		printf("0. Exit\n");
		printf("Enter Your choice:");
		scanf("%d",&n);
		switch(n)
		{
			case 1:
				printf("Enter item:");
				scanf("%d",&item);
				add_first(&start,&end,item);
				getch();
				break;
			case 2:
				printf("Enter item:");
				scanf("%d",&item);
				add_last(&start,&end,item);
				getch();
				break;
			case 3:
				printf("Enter item and location:");
				scanf("%d%d",&item,&loc);
				add_before(&start,&end,item,loc);
				getch();
				break;
			case 4:
				printf("Enter item and location:");
				scanf("%d%d",&item,&loc);
				add_after(&start,&end,item,loc);
				getch();
				break;
			case 8:
				display(start);
				getch();
				break;
			case 5:
				del_first(&start,&end);
				getch();
				break;
			case 6:
				del_last(&start,&end);
				getch();
				break;
			case 7:
				printf("Enter item to delete:");
				scanf("%d",&item);
				del_node(&start,&end,item);
				getch();
				break;
			case 0:
				break;
			default:
				printf("invalid choice:");
				getch();
		}
	}while(n!=0);
	
}
void add_first(node **start,node **end,int item)
{
	node *New;
	New=(node*)malloc(sizeof(node));
	if(New==NULL)
	{
		printf("Overflow");
		return;
	}
	New->info=item;
	New->prev=NULL;
	New->next=*start;
	if(*start==NULL)
		*end=New;
	else
		(*start)->prev=New;
	*start=New;
}
void add_last(node **start,node **end,int item)
{
	node *New,*ptr;
	if(*start==NULL)
	{
		add_first(start,end,item);
		return;
	}
	New=(node*)malloc(sizeof(node));
	if(New==NULL)
	{
		printf("Overflow");
		return;
	}
	New->info=item;
	New->next=NULL;
	ptr->next=*end;
	(*end)->next=New;
	*end=New;
}
void add_before(node **start,node **end,int item,int loc)
{
	node *New, *ptr;
	if(*start==NULL)
	{
		printf("List is empty");
		return;
	}
	if((*start)->info==loc)
	{
		add_first(start,end,item);
		return;
	}
	ptr=*start;
	while(ptr!=NULL && ptr->info!=loc)
	{
		ptr=ptr->next;
	}
	if(ptr==NULL)
	{
		printf("Loc not found");
		return;
	}
	New=(node*)malloc(sizeof(node));
	if(New==NULL)
	{
		printf("Overflow");
		return;
	}
	New->info=item;
	New->next=ptr;
	New->prev=ptr->prev;
	ptr->prev->next=New;
	ptr->prev=New;
}
void add_after(node **start,node **end,int item,int loc)
{
	node *New, *ptr;
	ptr=*start;
	while(ptr!=NULL && ptr->info!=loc)
	{
		ptr=ptr->next;
	}
	if(ptr==NULL)
	{
		printf("Loc not found");
		return;
	}
	New=(node*)malloc(sizeof(node));
	if(New==NULL)
	{
		printf("Overflow");
		return;
	}
	New->info=item;
	New->next=ptr->next;
	New->prev=ptr;
	ptr->next->prev=New;
	ptr->next=New;
}
void display(node *start)
{
	node *ptr;
	if(start==NULL)
	{
		printf("List is Empty");
		return;
	}
	ptr=start;
	while(ptr!=NULL)
	{
		printf("%d\t",ptr->info);
		ptr=ptr->next;
	}
}

void del_first(node **start,node **end)
{
	node *ptr;
	if(*start==NULL)
	{
		printf("Underflow");
		return ;
	}
	ptr=*start;
	if((*start)->next==NULL)
	{
		*start=*end=NULL;
	}
	{
		*start=(*start)->next;
		(*start)->prev=NULL;
	}
	printf("%d deleted",ptr->info);
	free(ptr);
}

void del_last(node **start,node **end)
{
	node *ptr;
	if(*start==NULL)
	{
		printf("Underflow");
		return;
	}
	ptr=*end;
	if((*start)->next==NULL)
	{
		*start=*end=NULL;
	}
	else
	{
		*end=(*end)->prev;
		(*end)->next=NULL;
	}
	printf("%d deleted",ptr->info);
	free(ptr);
}

void del_node(node **start,node **end, int item)
{
	node *ptr;
	if(*start==NULL)
	{
		printf("Underflow");
		return;
	}
	if((*start)->info==item)
	{
		del_first(start,end);
		return;
	}
	if((*end)->info==item)
	{
		del_last(start,end);
		return;
	}
	ptr=(*start)->next;
	while(ptr!=*end && ptr->info!=item)
	{
		ptr=ptr->next;
	}
	if(ptr==*end)
	{
		printf("Item not found");
		return;
	}
	ptr->next->prev=ptr->prev;
	ptr->prev->next=ptr->next;
	printf("%d deleted",ptr->info);
	free(ptr);
}
