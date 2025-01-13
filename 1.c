#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main(){
    int c=0;
    char stuffdata[100];
    char data[100];
    char flag[]="01111110";
    char sentframe[100];
    char receivdata[100];
    char destuffdata[100];
    char temp[100];
    int j=0;
    
    printf("Enter the data (a stream of 0s and 1s): ");
    scanf("%s",data);
    
    for(int i=0;i<strlen(data);i++){
        stuffdata[j]=data[i];
        if(data[i]=='1'){
            c++;
        }else{
            c=0;
        }
        if(c==5){
            j++;
            stuffdata[j]='0';
            c=0;
        }
        j++;
    }
    stuffdata[j]='\0';
    printf("Stuffed data: %s\n",stuffdata);
    
    strcpy(sentframe,flag);
    strcat(sentframe,stuffdata);
    strcat(sentframe,flag);
    printf("Frame to be sent: %s\n",sentframe);

    printf("Enter the received frame: ");
    scanf("%s",receivdata);
    
    if(strlen(receivdata)<16){
        printf("Framing error!");
        exit(0);
    }
    for(int i=0;i<8;i++){
        temp[i]=receivdata[i];
    }
    temp[8]='\0';
    if(strcmp(temp,flag)!=0){
        printf("Framing error!");
        exit(0);
    }
    for(int i=0;i<8;i++){
        temp[i]=receivdata[strlen(receivdata)+i-8];
    }
    temp[8]='\0';
    if(strcmp(temp,flag)!=0){
        printf("Framing error!");
        exit(0);
    }
    
    strncpy(destuffdata,receivdata+8,strlen(receivdata)-16);
    destuffdata[strlen(receivdata)-16]='\0';
    
    c=0;
    j=0;
    for(int i=0;i<strlen(destuffdata);i++){
        data[j]=destuffdata[i];
        if(destuffdata[i]=='1'){
            c++;
        }else{
            c=0;
        }
        if(c==5){
            i++;
            c=0;
        }
        j++;
    }
    data[j]='\0';
    printf("De-stuffed data: %s\n",data);
}
