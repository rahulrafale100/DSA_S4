#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct node{
  	char *word;
	struct node *next;
};
struct hash_table{
	struct node *head;
};
int main(){
   struct hash_table T[255];
   for(int i=0;i<255;i++){
   	T[i].head=NULL;
   }
   int n;
   scanf("%d ",&n);
   char string[n][100];
   for(int i=0;i<n;i++){
   	scanf("%[^\n]%*c",string[i]);
   }
   int value;
   for(int i=0;i<n;i++){
   	value=0;
   	int f[26]={0};
   	int len=strlen(string[i]);
   	for(int j=0;j<len;j++){
   		int k=string[i][j]-'a';
   		if(f[k]==0){
   		value+=(1<<k);
		   f[k]=1;}  
	}
	struct node *z;
	z=(struct node*)malloc(sizeof(struct node));
	z->word=(char*)malloc((len+1)*sizeof(char));
	for(int j=0;j<len;j++){
		z->word[j]=string[i][j];
	}
	z->word[len]='\0';
//	printf("%s ",z->word);
	z->next=NULL;
	if(T[value].head==NULL){
		T[value].head=z;
	}
	else{
		struct node *p,*q;
		p=T[value].head;
		q=NULL;
		int x,s=0;
		x=strcmp(p->word,z->word);
		if(x>0){
			z->next=p;
			T[value].head=z;
			s=1;
		}
		if(s==0){
		while(p!=NULL){
	 x=strcmp(p->word,z->word);
	//	printf("%d ",x);
	if(x>0){
		z->next=p;
		q->next=z;
		s=1;
		break;
	}
		q=p;
		p=p->next;
		}
	}
	if(s==0){
		q->next=z;
	}
	}
   }
   for(int i=0;i<255;i++){
   	if(T[i].head==NULL){
   		continue;
	   }
	   struct node *z;
	   z=T[i].head;
	   while(z!=NULL){
	   	printf("%s ",z->word);
	   	z=z->next;
	   }
	   printf("\n");
   }
   return 0;
}
