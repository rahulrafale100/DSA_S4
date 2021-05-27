#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
	char *word;
	struct node *next;
};
struct hash_table{
	struct node *head;
};
int main(){
	int n;
	scanf("%d ",&n);
	char string[1000];
	scanf("%[^\n]%*c",string);
	struct hash_table T[n];
	for(int i=0;i<n;i++){
		T[i].head=NULL;
	}
	int len=strlen(string);
	char word[300][100];
	int cnt=0,j=0;
	for(int i=0;i<len;i++){
	    if(string[i]==' ' ||string[i]=='\0'){
			cnt++;
			j=0;
		}
		else{
			word[cnt][j]=string[i];
			j++;
		}
	}
	for(int i=0;i<=cnt;i++){
		int f=0;
		for(int j=0;j<i;j++){
		int p=strcmp(word[i],word[j]);
		if(p==0){
			f=1;
		}
		}
		if(f==0){
			int x=strlen(word[i]);
			int hash_value=(x*x)%n;
			struct node *z;
			z=(struct node*)malloc(sizeof(struct node));
			z->word=(char*)malloc((x+1)*sizeof(char));
			int d=0;
			for(int j=0;j<x;j++){
			z->word[j]=word[i][j];
		}
		z->word[x]='\0';
		z->next=NULL;
		if(T[hash_value].head==NULL)
		T[hash_value].head=z;
		else{
			struct node *w;
			w=T[hash_value].head;
			while(w->next!=NULL){
				w=w->next;
			}
			w->next=z;
		}
	    }
		}
		for(int i=0;i<n;i++){
			printf("%d:",i);
			if(T[i].head==NULL)
			printf("null\n");
			else{
				struct node *z;
				z=T[i].head;
				while(z!=NULL){
					printf("%s",z->word);
					z=z->next;
					if(z!=NULL)
					printf("-");
				}
				printf("\n");
			}
		}
	}
