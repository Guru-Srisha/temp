#include<stdio.h>
#include<stdlib.h>
#define nodes 4
#define infinity 100

int n;
int dist[nodes][nodes]=
{	
    0,100,10,2,
	100,0,3,4,
	10,3,0,100,
	2,4,100,0
};

void main(){
	int i,s,j,t;
	void shrt();
	printf("Enter the no of nodes: ");
	scanf("%d",&n);
	printf("Enter the source & destination nodes: ");
	scanf("%d %d",&s,&t);
	if(s==t) {
		printf("Source is same as destination, hence the distance is 0.");
		exit(0);
	}
	shrt(s,t);
}

void shrt(int s,int t){
	struct state{
		int predecessor;
		int length;
		enum {per,tent} label;
	}state[nodes];
	int i,k,min;
	struct state*p;
	for(p=&state[0];p<&state[n];p++){
		p->predecessor=-1;
		p->length=infinity;
		p->label=tent;
	}
	state[t].length=0;
	state[t].label=per;
	k=t;
	do{
		for(i=0;i<n;i++)
			if(dist[k][i]!=0 && state[i].label==tent){
				if(state[k].length+dist[k][i]<state[i].length){
					state[i].predecessor=k;
					state[i].length=state[k].length+dist[k][i];
				}
			}
		k=0;
		min=infinity;
		for(i=0;i<n;i++)
			if(state[i].label==tent && state[i].length<min){
				min=state[i].length;
				k=i;
			}
		state[k].label=per;
	}while(k!=s);
	k=s;
	do{
		printf("%d",k);
		if(k!=t)
		    printf("--->");
		k=state[k].predecessor;
	}while(k>=0);
	printf("\nThe total distance is %d",state[s].length);
}
