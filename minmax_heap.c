#include<stdio.h>
#include<math.h>
void build_heap(int *h,int n);
void pushdown(int *h,int i,int n);
void pushdown_min(int* h,int i,int n);
void pushdown_max(int* h,int i,int n);
void insert(int *h,int e,int *n);
void push_up_min(int *h,int i);
void push_up_max(int *h,int i);
void print(int *h,int n);
void remove_min(int *h,int *n);
void remove_max(int *h,int *n);
int minimum(int *h,int n);
int maximum(int *h,int n);
int ksmall(int* h,int e,int n);
int main()
{
	int n;
	scanf("%d",&n);
	int h[n+1];
	h[0]=0;
	for(int i=1;i<=n;i++)
		scanf("%d",&h[i]);
	build_heap(h,n);
//	print_level(h,n);
	int choice=1,element;
	while(choice)
	{	
	printf("\nEnter choice: ");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1: scanf("%d",&element);
				insert(h,element,&n);break;
		case 2: printf("%d",minimum(h,n));break;
		case 3: printf("%d",maximum(h,n));break;
		case 4: remove_min(h,&n);break;
		case 5: remove_max(h,&n);break;
		case 6: printf("Enter k for smallest element ");
				scanf("%d", &element);
				printf(" %d",ksmall(h,element,n));break;
		case 7: print(h,n);break;
		case 8: choice=0;
	}
	}
}

void build_heap(int *h,int n)
{
	for(int i=n/2;i>=1;i--)
	{	
		pushdown(h,i,n);
//		for(int i=1;i<=n;i++)
//		printf("%d ",h[i]);	
//		printf("\n");
	}
}

void pushdown(int *h,int i,int n)
{
	if((int)(floor(log(i)/log(2))) % 2 == 0)
		pushdown_min(h,i,n);
	else
		pushdown_max(h,i,n);
}

void pushdown_min(int* h,int i,int n)
{
	int j=2*i;
	int k=j+1;
	int a,b,c,d;
	a=2*j;b=a+1;
	c=2*k;d=c+1;

	if(a<=n)
	{
		int min[4]={a,b,c,d};
		int m=a;
		for(int x=1;x<4;x++)
			if(min[x]<=n && h[min[x]]<h[m])
				m=min[x];
		if(h[m]<h[i])
		{
			int temp=h[m];
			h[m]=h[i];
			h[i]=temp;
			if(h[m]>h[m/2])
			{
				temp=h[m];
				h[m]=h[m/2];
				h[m/2]=temp;
			}
			pushdown_min(h,m,n);	
		}	
	}
	else  if(j<=n){
		int m=j;
		if(k<=n && h[k]<h[j])
			m=k;
		if(h[m]<h[i])
		{
			int temp=h[m];
			h[m]=h[i];
			h[i]=temp;
		}	
	}

}

void pushdown_max(int* h,int i,int n)
{
	int j=2*i;
	int k=j+1;
	int a,b,c,d;
	a=2*j;b=a+1;
	c=2*k;d=c+1;

	if(a<=n)
	{
		int min[4]={a,b,c,d};
		int m=a;
		for(int x=1;x<4;x++)
			if(min[x]<=n && h[min[x]]>min[m])
				m=min[x];
		if(h[m]>h[i])
		{
			int temp=h[m];
			h[m]=h[i];
			h[i]=temp;
			if(h[m]<h[m/2])
			{
				temp=h[m];
				h[m]=h[m/2];
				h[m/2]=temp;
			}
			pushdown_min(h,m,n);	
		}	
	}
	else  if(j<=n){
		int m=j;
		if(k<=n && h[k]>h[j])
			m=k;
		if(h[m]>h[i])
		{
			int temp=h[m];
			h[m]=h[i];
			h[i]=temp;
		}	
	}

}

void insert(int *h,int e,int *x)
{
	int n=*x;
	int m=n+1;
	h[m]=e;
	if(n+1 != 1)
	{	
		int l=(int)floor(log(n+1)/log(2));
		if(l%2==0)
		{
			if(e>h[m/2])
			{
				int temp=e;
				h[m]=h[m/2];
				h[m/2]=temp;
				push_up_max(h,m/2);
			}
			else
				push_up_min(h,m);
		}
		else
		{
			if(e<h[m/2])
			{
				int temp=e;
				h[m]=h[m/2];
				h[m/2]=temp;
				push_up_min(h,m/2);
			}
			else
				push_up_max(h,m);
		}
		(*x)++;	
	}
}

void push_up_min(int *h,int i)
{
	int j=i/4;
	if(j>=0)
	{
		if(h[i]<h[j])
		{
			int temp=h[i];
			h[i]=h[j];
			h[j]=temp;
			push_up_min(h,j);
		}	
	}	
}

void push_up_max(int *h,int i)
{
	int j=i/4;
	if(j>=0)
	{
		if(h[i]>h[j])
		{
			int temp=h[i];
			h[i]=h[j];
			h[j]=temp;
			push_up_max(h,j);
		}	
	}	
}

int minimum(int *h,int n)
{
	if(n!=0)
		return h[1];
	return -1;
}

int maximum(int *h,int n)
{
	if(n!=0)
	{
		if(n==1)
			return h[1];
		if(n==2)
			return h[2];
		if(n>=3)
		{
			if(h[2]>h[3])
				return h[2];
			else
				return h[3];
		}	
			
	}
    return -1;	
}

void remove_min(int *h,int *n)
{
	int temp=h[1];
	h[1]=h[*n];
	(*n)--;
	pushdown(h,1,*n);
} 

void remove_max(int *h,int *n)
{
	int max=maximum(h,*n);
	if(max!=-1)
	{	
		if(h[1]==max)
		{
			h[1]=h[*n];
			pushdown(h,2,--(*n));
		}
		else
		{
			h[2]=h[*n];
			pushdown(h,3,--(*n));
		}
	}		
}

void print(int *h,int n)
{
	for(int i=1;i<=n;i++)
		printf("%d ",h[i]);
}

int ksmall(int* h,int e,int n)
{
	int h1[n];
	for(int i=1;i<=n;i++)
		h1[i]=h[i];
	for(int i=0;i<(e-1);i++)
		remove_min(h1,&n);
	return h1[1];
}








