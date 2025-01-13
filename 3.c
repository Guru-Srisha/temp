#include <stdio.h>
#define KEY_SHIFT 3

int main(){
    char plainText[100],cipherText[100],decrText[100];
    
    printf("Enter the plain text to encrypt: ");
    scanf("%s",plainText);
    
    for(int i=0;*(plainText+i)!='\0';i++){
        if(*(plainText+i)>='a'&&*(plainText+i)<='w'||*(plainText+i)>='A'&&*(plainText+i)<='W'){
            *(cipherText+i)=*(plainText+i)+KEY_SHIFT;
        }else if(*(plainText+i)>='x'&&*(plainText+i)<='z'||*(plainText+i)>='X'&&*(plainText+i)<='Z'){
            *(cipherText+i)=*(plainText+i)+KEY_SHIFT-26;
        }else{
            *(cipherText+i)=*(plainText+i)+KEY_SHIFT;
        }
    }
    
    printf("Cipher text: %s\n",cipherText);
    
    printf("Enter the cipher text to decrypt: ");
    scanf("%s",cipherText);

    for(int i=0;*(cipherText+i)!='\0';i++){
        if(*(cipherText+i)>='d'&&*(cipherText+i)<='z'||*(cipherText+i)>='D'&&*(cipherText+i)<='Z'){
            *(decrText+i)=*(cipherText+i)-KEY_SHIFT;
        }else if(*(cipherText+i)>='a'&&*(cipherText+i)<='c'||*(cipherText+i)>='A'&&*(cipherText+i)<='C'){
            *(decrText+i)=*(cipherText+i)-KEY_SHIFT+26;
        }else{
            *(decrText+i)=*(cipherText+i)-KEY_SHIFT;
        }
    }
    
    printf("Decypted text: %s",decrText);
    
    return 0;
}
