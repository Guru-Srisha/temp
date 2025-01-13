#include <stdio.h>
#include <string.h>
#define dle "DLE"
#define stx "STX"
#define etx "ETX"

int main(){
    char msg[100];
    char stuffedMsg[100];
    char frame[100];
    char receivedFrame[100];
    char destuffedMsg[100];
    int j=0;
    
    printf("Enter the message (a stream of characters): ");
    scanf("%s",msg);

    for(int i=0;i<strlen(msg);i++){
        if(strncmp(&msg[i],dle,3)==0){
            strncpy(&stuffedMsg[j],dle,3);
            j+=3;
        }
        stuffedMsg[j]=msg[i];
        j++;
    }
    stuffedMsg[j]='\0';

    strcpy(frame,"DLESTX");
    strcat(frame,stuffedMsg);
    strcat(frame,"DLEETX");
    printf("Frame to be sent: %s\n",frame);

    printf("Enter the received frame: ");
    scanf("%s",receivedFrame);

    if(strlen(receivedFrame)<12){
        printf("Framing error!\n");
        return 1;
    }
    if(strncmp(receivedFrame,dle stx,6)!= 0 ||
                strncmp(&receivedFrame[strlen(receivedFrame)-6],dle etx,6)!=0){
        printf("Framing error!\n");
        return 1;
    }

    strncpy(destuffedMsg,receivedFrame+6,strlen(receivedFrame)-12);
    destuffedMsg[strlen(receivedFrame)-12]='\0';

    j=0;
    for(int i=0;i<strlen(destuffedMsg);i++){
        if(strncmp(&destuffedMsg[i],dle,3)==0 && strncmp(&destuffedMsg[i+3],dle,3)==0){
            i+=3;
        }
        msg[j]=destuffedMsg[i];
        j++;
    }
    msg[j]='\0';

    printf("De-stuffed message: %s\n",msg);

    return 0;
}
