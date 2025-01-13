#include<stdio.h>
#include<conio.h>

void crc(int msg[]);
int dg=16,dm,dt,data[50],gen[20];
int si[16],so[16],tx;

void main(){
	int i,j,k;
	
	printf("Enter the degree of generator polynomial: ");
	scanf("%d",&dg);
	printf("Enter the generator polynomial: ");
	for(i=dg;i>=0;i--)
	    scanf("%d",&gen[i]);
	printf("Enter the degree of message: ");
	scanf("%d",&dm);
	printf("Enter the message: ");
	for(i=dm;i>=0;i--)
	    scanf("%d",&data[i]);
	    
	dt=dm+dg;
	for(i=0;i<=dm;i++)
	    data[dt-i]=data[dm-i];
	for(i=1;i<=dg;i++)
	    data[dg-i]=0;
	tx=1;
	crc(data);
	
	printf("Enter the received message: ");
	for(i=dt;i>=0;i--)
	    scanf("%d",&data[i]);
	tx=0;
	crc(data);
}

void crc(int msg[]){
	int i,j,k,flag;
	for(i=0;i<dg;i++){
		so[i]=0;
		si[i]=0;
	}
	for(i=dt;i>=0;i--){
		if(gen[0]==1)
		    si[0]=so[dg-1]^msg[i];
		else
		    si[0]=msg[i];
		for(j=1;j<=dg-1;j++)
			if(gen[j]==1)
			    si[j]=so[dg-1]^so[j-1];
			else
			    si[j]=so[j-1];
		printf("\n");
		for(k=dg-1;k>=0;k--){
			so[k]=si[k];
			printf("%d",so[k]);
		}
	}
	
	if(tx){
		printf("CRC code is: ");
		for(k=dg-1;k=0;k--){
			printf("%d",so[k]);
			msg[k]=so[k];
		}
		printf("Message to be transmitted: ");
		for(i=dt;i>=0;i--)
		    printf("%d",msg[i]);
	}
	
	if(!tx){
		flag=0;
		for(i=0;i<=dg-1;i++)
			if(so[i]==1){
				flag=1;
				break;
			}
		if(flag==0)
		    printf("No error!");
		else
		    printf("Error in the received message");
	}
}
