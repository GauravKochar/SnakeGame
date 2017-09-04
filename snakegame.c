#include<stdio.h>
#include<conio.h>
#include<malloc.h>

# define width 30
# define height 30

typedef struct node node;
typedef struct FFood food;
struct node
{
	int X;
	int Y;
	char value;
	node* link;
};
struct FFood
{
	int X;
	int Y;
	char value;
};
void setMatrix(char arr[height][width] )
{
	char ch='*',ch1='*',ch2=' ';
	int i,j;

	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			
			if(i==0||i==height-1)
			arr[i][j]=ch1;
			else if(j==0||j==width-1)
			arr[i][j]=ch;
			else
			arr[i][j]=ch2;
			
		}
	}
			
}

void moveValueToMatrix(char arr[height][width],node** ptr,food Food)
{	
	node*ptr2;
			
		ptr2=*ptr;
			while((ptr2)!=NULL)
		{
			arr[(ptr2)->X][(ptr2)->Y]=(ptr2)->value;
			(ptr2)=(ptr2)->link;
		
		}
			arr[Food.X][Food.Y]='@';
	
}

void moveSnakeToScreen(char arr[height][width])
{
	int i,j;
		for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			printf("%c",arr[i][j]);
		}
		printf("\n");
	}
}

food generateFood(char arr[height][width],node** ptr)
{
	food Food;
	node*ptr1;
	Food.X=rand()%(width-2)+1;
	Food.Y=rand()%(height-2)+1;
	Food.value='@';
	
	
	ptr1=*ptr;
	while(ptr1)
	{
		if(ptr1->X==Food.X&&ptr1->Y==Food.Y)
		{
					
					Food.X=srand()%(width-2)+1;
					Food.Y=srand()%(height-2)+1;
		}
			ptr1=ptr1->link;
		
	}

	return Food;

}
void swapValue(node* ptr,int i,int j)
{
	if(ptr==NULL)
	return;
	
	
		int m=(ptr)->X;
		int n=(ptr)->Y;
		(ptr)->X=i;
		(ptr)->Y=j;
		swapValue((ptr)->link,m,n);

	
	
}
void increaseLength(node** tail)
{	
	node* Node=(node*)malloc(sizeof(node));
	Node->value='#';
	Node->link=NULL;
	(*tail)->link=Node;
	Node->X=(*tail)->X;
	Node->Y=(*tail)->Y;
	*tail=Node;
	
	
}
food eatFood(node **head,food Food,char matrix[height][width],node** tail)
{
	food Food1;
	node*ptr=*head;
	
		if((*head)->X==Food.X&&(*head)->Y==Food.Y)
		{
	
			Food1=generateFood(matrix,head);
			increaseLength(tail);
			return Food1;
			
		}

	
}
void checkStrike(node** head)
{
	node*ptr=*head;

	ptr=ptr->link;
	while(ptr)
	{
		if(ptr->X==(*head)->X&&ptr->Y==(*head)->Y)
		{
			system("cls");
			printf("GAMEOVER!!!");
			getch();
			exit(1);
			
		}
		ptr=ptr->link;
	}
	
}


void moveUp(node** ptr)
{

	int m,n;
	
	node*head=*ptr;

	 m=head->X;
	 n=head->Y;

	head->X=head->X-1;
	if(head->X==0)
		head->X=height-1;
	swapValue((*ptr)->link,m,n);

	
}

void moveRight(node** ptr)
{
	
	int m,n;
	node*head=*ptr;
	 m=head->X;
	 n=head->Y;

	head->Y=head->Y+1;
	if(head->Y==height-1)
	{
		head->Y=0;
		head->X=head->X-1;
	}
		
	swapValue((*ptr)->link,m,n);

}
void moveLeft(node** ptr)
{

	int m,n;
	node*head=*ptr;
	 m=head->X;
	 n=head->Y;

	head->Y=head->Y-1;
	if(head->Y==0)
	{
		head->Y=width-1;
		head->X=head->X-1;
	}
		
	swapValue((*ptr)->link,m,n);

	
}
void moveDown(node** ptr)
{
	
	int m,n;
	
	node*head=*ptr;

	 m=head->X;

	 n=head->Y;

	head->X=head->X+1;
	if(head->X==height-1)
		head->X=0;
	swapValue((*ptr)->link,m,n);
	
	
}

void moveSnakeDefault(char ch,node** head)
{
	switch(ch)
		{
			
			case 'w':
						
						moveUp(head);
						break;
						
			case 'a':	
						if(ch!='d')
						moveLeft((head));
						
						break;
						
			case 's':	if(ch!='w')
						
						moveDown((head));
						break;
			case 'd':
						if(ch!='a')
						moveRight((head));
							break;
		
		}
}
void storeMatrixToFile(node** head,food Food)
{
	node*ptr=*head;
	FILE *fp;
	int x,y;
	char c,ch='\n',ch1='$';
	fp=fopen("gauravSnake3.txt","w");
	
	fprintf(fp,"%c %d %d\n",Food.value,Food.X,Food.Y);
	while(ptr)
	{
	
		x=ptr->X;
		y=ptr->Y;
		c=ptr->value;
		fprintf(fp,"%c %d %d\n",c,x,y);  
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
		ptr=ptr->link;
		
	}
	
	fclose(fp);
}
food getMatrixFromFile(node** head,char arr[height][width],node**tail)
{
	int x,y,count=0;
	
	char ch;
	food Food;
	node* temp2;
	char c;

FILE* fptr;
fptr=fopen("gauravSnake3.txt","r");

fscanf(fptr,"%c %d %d",&ch,&x,&y);
Food.X=x;
Food.Y=y;
Food.value=ch;
	c=getc(fptr);

   while(fscanf(fptr,"%c %d %d",&ch,&x,&y)!=EOF)
{
		c=getc(fptr);
		node* temp=(node*)malloc(sizeof(node));
		temp->X=x;
		temp->Y=y;
		temp->value=ch;
		temp->link=NULL;
		if(count==0)
		{
			*head=temp;
			temp2=temp;
			count++;
		}
		else
		{
			temp2->link=temp;
			*tail=temp;
			temp2=temp;
		}	
		
}
	

	setMatrix(arr);

	system("cls");
	moveValueToMatrix(arr,head,Food);
	moveSnakeToScreen(arr);
	return Food;

}


void presskey(node** head,char matrix[height][width],food Food,node** tail)
{
	
char ch='a',ch1;
	while(1)
	{
	
		switch(ch1=getch())
		{
			
			case 'w':
						if(ch!='s')
						{
						moveUp(head);
						ch=ch1;	
						}
						break;
						
			case 'a':	
						if(ch!='d')
						{
						moveLeft((head));
						ch=ch1;
						}
						break;
						
			case 's':	if(ch!='w')
						{
						moveDown((head));
						ch=ch1;
						}
						break;
			case 'd':
						if(ch!='a')
						{
						moveRight((head));
						ch=ch1;
						}
						break;
						
			case 'x':
			case'X':
						storeMatrixToFile(head,Food);
						printf("Your Game Has been saved");
							exit(1);
						
					
			default:	
						moveSnakeDefault(ch,head);
						
						
		}
		
		system("cls");
		setMatrix(matrix);
		
	
		Food=eatFood(head,Food,matrix,tail);
		
		moveValueToMatrix(matrix,head,Food);
		moveSnakeToScreen(matrix);
		checkStrike(head);	
		
	}
}


void CreateSnake(node** head,node** tail)
{
	
	node* Node=(node*)malloc(sizeof(node));

	Node->value='A';
	Node->X=11;
	Node->Y=4;
		*head=Node;
	
		
	
		
	node* Node1=(node*)malloc(sizeof(node));
	Node1->value='#';
	Node1->X=11;
	Node1->Y=5;
	Node->link=Node1;
	
	node* Node2=(node*)malloc(sizeof(node));
	Node2->value='#';
	Node2->X=11;
	Node2->Y=6;
	Node1->link=Node2;
	
	node* Node3=(node*)malloc(sizeof(node));
	Node3->value='#';
	Node3->X=11;
	Node3->Y=7;
	Node2->link=Node3;
	
	node* Node4=(node*)malloc(sizeof(node));
	Node4->value='#';
	Node4->X=11;
	Node4->Y=8;
	Node3->link=Node4;
	
	Node4->link=NULL;
	*tail=Node4;


	
}

void main()
{
	int i,j;
	char ch;
	node* Head=NULL;
	node* Tail=NULL;
	node*ptr;
	food Food,Food2;
	char matrix[height][width];
	printf("DO you want to play a New Game or Old one...... Press N for New and O for Old.\n");
	scanf("%c",&ch);
	switch(ch)
	{
		case 'n':
		case 'N':
			CreateSnake(&Head,&Tail);
			
			setMatrix(matrix);
			Food=generateFood(matrix,&Head);
				
			moveValueToMatrix(matrix,&Head,Food);
			moveSnakeToScreen(matrix);	
		
			presskey(&Head,matrix,Food,&Tail);	
	
			break;
		case 'o':
		case 'O':
		
		Food2=getMatrixFromFile(&Head,matrix,&Tail);
	
			presskey(&Head,matrix,Food2,&Tail);
		break;
		
		default:
			printf("Enter correct option");
			
			
	}
	
	
	



getch();


			
	
}
/*void LinkingInNodes(node** Node,char c,node** temp,FILE* fp)
{
	if(c==EOF)
		return ;
		
			(*Node)->value=c;
			c=getc(fp);
			c=getc(fp);
			(*Node)->X=(int)c-48;
			
			c=getc(fp);
			c=getc(fp);
			(*Node)->Y=(int)c-48;
			
			(*Node)->link=*temp;
			c=getc(fp);
			c=getc(fp);
			
			node*temp1=(node*)malloc(sizeof(node));
			
			//temp1=NULL;
		
			LinkingInNodes(temp,c,&temp1,fp);
		
		
}

void getMatrixFromFile(node** head1)
{

	int i,j;
	food Food;
	Food.X=8;
	Food.Y=8;
	Food.value='@';
node* head=(node*)malloc(sizeof(node));
node* temp=(node*)malloc(sizeof(node));

	char arr[height][width];
	char c;
	FILE *fp;
	fp=fopen("gauravSnake3.txt","r");
	c=getc(fp);
	if(c!=EOF)
	{
		*head1=head;
	LinkingInNodes(&head, c,&temp,fp);
	setMatrix(arr);
	system("cls");
	moveValue(arr,head1);
	moveSnakeToScreen(arr);
	}
	

}*/


