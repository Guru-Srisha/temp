#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

int main(){
    char txt[50],kw[10],kw1[10],temp,txt1[10][10],encr[10][10],decr[10][10];
    int len,lenm,lenk,order[10],i,j,k,temp1,c=0,r,b,count;
    
    printf("Enter the message to be encrypted: ");
    scanf("%s",txt);
    lenm=strlen(txt);
    printf("Enter the keyword: ");
    scanf("%s",kw);
    lenk=strlen(kw);
    strcpy(kw1,kw);
    
    for(i=0;i<lenk;i++)
        order[i]=i;
        
    for(i=0;i<lenk;i++)
        for(j=0;j<lenk;j++){
            if(kw1[j]>kw1[i]){
                temp=kw1[j];
                kw1[j]=kw1[i];
                kw1[i]=temp;
                temp1=order[j];
                order[j]=order[i];
                order[i]=temp1;
            }
        }
    printf("Order of letters after sorting: ");
    for(i=0;i<lenk;i++)
        printf("%d",order[i]);
        
    r=lenm/lenk;
    b=lenm%lenk;
    if(b!=0)
        r++;
       
    count=0;
    for(i=0;i<r;i++){
        for(j=0;j<lenk&&count<=lenm;j++)
            txt1[i][j]=txt[count++];
        if(count>lenm){
            while(b!=lenk){
                txt1[i][b]='a'+c++;
                b++;
            }
        }
    }
    
    printf("The encrypted message: ");
    for(k=0;k<lenk;k++){
        for(i=0;i<r;i++){
            j=order[k];
            encr[i][k]=txt1[i][j];
            printf("%c",encr[i][k]);
        }
    }
    
    printf("Enter the keyword: ");
    scanf("%s",kw1);
    if(strcmp(kw,kw1)){
        printf("Wrong key!!");
        exit(0);
    }
    
    for(i=0;i<lenk;i++){
        j=order[i];
        for(k=0;k<r;k++)
            decr[k][j]=encr[k][i];
    }
    printf("The original message is: ");
    for(i=0;i<r;i++)
        for(j=0;j<lenk;j++){
            if(((i*lenk)+j)==lenm){
                break;
            }
            printf("%c",decr[i][j]);
        }

    return 0;
}
