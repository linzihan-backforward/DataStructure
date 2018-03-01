/* Linear Table On Linked Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>


#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status; 
typedef int ElemType; //����Ԫ�����Ͷ���


#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct LNode{  //˳���˳��ṹ���Ķ���
	ElemType  data;
	struct LNode *next;
}LNode, *LinkList;
status IntiaList(LinkList & L);

status DestroyList(LinkList & L);
status ClearList(LinkList &L);
status ListEmpty(LinkList L);
int ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType & e);
status LocateElem(LinkList L,ElemType e); //�򻯹�
status PriorElem(LinkList L,ElemType cur,ElemType & pre_e);
status NextElem(LinkList L,ElemType cur,ElemType & next_e);
status ListInsert(LinkList & L,int i,ElemType e);
status ListDelete(LinkList & L,int i,ElemType & e);
status ListTrabverse(LinkList L);  //�򻯹�
status LoadFromFile(char * filename,LinkList & L);
status SaveToFile(char * filename,LinkList  L); 
/*--------------------------------------------*/
int main(){
  LinkList L1,L2;  int op=1;
  ElemType  e,ans;
  int i;
  int option;
  char fileName[20];
  while(op){
	system("cls");	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. IntiaList       7. LocateElem\n");
	printf("    	  2. DestroyList     8. PriorElem\n");
	printf("    	  3. ClearList       9. NextElem \n");
	printf("    	  4. ListEmpty     10. ListInsert\n");
	printf("    	  5. ListLength     11. ListDelete\n");
	printf("    	  6. GetElem       12. ListTrabverse\n");
	printf("    	  0. Exit\n");
	printf("          13.Save           14.Load\n");
	printf("-------------------------------------------------\n");
	printf("    ��ѡ����Ĳ���[0~14]:");
	scanf("%d",&op);
	printf("    ��������Ҫ���������Ա��ţ�1��2��");
	scanf("%d",&option);
	if(option==1){
	    switch(op){
		   case 1:
		   	
		   	
			 if(IntiaList(L1)==OK) printf("���Ա�1�����ɹ���\n");
			     else printf("���Ա�1����ʧ�ܣ�\n");
			 getchar();getchar();
			 break;
			 
			 
		   case 2:
		   	
		   	
			 if(DestroyList(L1)==OK) printf("���Ա�1ɾ���ɹ���\n");
			     else printf("���Ա�1ɾ��ʧ�ܣ�\n");     
			 getchar();getchar();
			 break;
			 
			 
		   case 3: 
		   
		   
			 if(ClearList(L1)==OK) printf("���Ա�1��ճɹ���\n");
			     else printf("���Ա�1���ʧ�ܣ�\n");    
			 getchar();getchar();
			 break;
			 
			 
		   case 4: 
		   
		   
			 if(ListEmpty(L1)==TRUE) printf("�����Ա�Ϊ�գ�\n");
			     else printf("�����Ա�ǿգ�\n");    
			 getchar();getchar();
			 break;
			 
			 
		   case 5:
		   	
		   	
			 int len; 
			 if((len=ListLength(L1))>=0) printf("�����Ա�Ϊ����Ϊ%d��\n",len);
			     else printf("�޴����Ա�\n");    
			 getchar();getchar();
			 break;
			 
			 
		   case 6:
		   	
		   	
			 int i; ElemType  e;
			 printf("  ������Ҫ��ȡ��Ԫ��λ�ã�\n");
			 scanf("%d",&i); 
			 if(GetElem(L1,i,e)) printf("�����Ա��λ�õ�Ԫ��Ϊ:%d\n",e);
			     else printf("��������\n");    
			 getchar();getchar();
			 break;
			 
			 
		   case 7:  
		   
		   
			 int ans;    
			 printf("  ��������Ҫ��ȡ��Ԫ�أ�\n");
			 scanf("%d",&e);
			 if((ans=LocateElem(L1,e))) printf("�����Ա��Ԫ�ص�λ��Ϊ:%d\n",ans);
			     else printf("û�д�Ԫ�أ�\n"); 
			 getchar();getchar();
			 break;
			 
			 
		   case 8:
		   
		        
			 printf("  ��������Ҫ��ȡǰһ��Ԫ�ص�Ԫ�أ�\n");
			 scanf("%d",&e);
			 if((PriorElem(L1,e,ans))) printf("�����Ա��Ԫ�ص�ǰһ��Ԫ��Ϊ:%d\n",ans);
			     else printf("û�д�Ԫ�أ�\n");
			 getchar();getchar();
			 break;
			 
			 
		   case 9:
		        
			 printf("  ��������Ҫ��ȡ��һ��Ԫ�ص�Ԫ�أ�\n");
			 scanf("%d",&e);
			 if(NextElem(L1,e,ans)) printf("�����Ա��Ԫ�صĺ�һ��Ԫ��Ϊ:%d\n",ans);
			     else printf("û�д�Ԫ�أ�\n"); 
			 getchar();getchar();
			 break;
			 
			 
		   case 10:
		   
		      
			 printf("  ��������Ҫ����Ԫ�ص�λ�ã�\n");
			 scanf("%d",&i);
			 if(i<1||i>ListLength(L1)+1)  printf("������Ϸ������ݣ���0~%d֮��",ListLength(L1)+1); 
			 else {
			 	printf("  ��������Ҫ�����Ԫ�أ�\n");
			 	scanf("%d",&e);
			 	if(ListInsert(L1,i,e)) printf("�ѳɹ����룡\n");
			     	else printf("��������\n");
			 }     
			 getchar();getchar();
			 break;
			 
			 
		   case 11:
		   
		    
			 printf("  ��������Ҫɾ��Ԫ�ص�λ�ã�\n");
			 scanf("%d",&i);
			 if(ListDelete(L1,i,e)) printf("�ѳɹ�ɾ����Ԫ��Ϊ��%d\n",e);
			     else printf("��������\n");       
			 getchar();getchar();
			 break;
			 
			 
		   case 12:    
		   
		    
			 if(!ListTrabverse(L1)) printf("���Ա��ǿձ�\n");
			 getchar();getchar();
			 break;
			 
			 
		   case 13:
		   
		        
			 printf("\n������Ҫ������ļ�����\n");
			 scanf("%s",fileName);
			 if(SaveToFile(fileName,L1)) printf("�ѳɹ��������ļ�!");
			 else printf("����ʧ�ܣ�"); 
			 getchar();getchar();
			 break;
			 
			 
		   case 14:
		   
		        
			 printf("\n������Ҫ��ȡ���ļ�����\n");
			 scanf("%s",fileName);
			 if(LoadFromFile(fileName,L1)) printf("�ѳɹ����ļ���ȡ!");
			 else printf("��ȡʧ�ܣ�"); 
			 getchar();getchar();
			 break;
			 
			 
		   case 0:
	         break;
		}//end of switch
	}//end of if
	else if(option==2){
		switch(op){
		   case 1:
		   	
		   	
			 if(IntiaList(L2)==OK) printf("���Ա�2�����ɹ���\n");
			     else printf("���Ա�2����ʧ�ܣ�\n");
			 getchar();getchar();
			 break;
			 
			 
		   case 2:
		   	
		   	
			 if(DestroyList(L2)==OK) printf("���Ա�2ɾ���ɹ���\n");
			     else printf("���Ա�2ɾ��ʧ�ܣ�\n");     
			 getchar();getchar();
			 break;
			 
			 
		   case 3: 
		   
		   
			 if(ClearList(L2)==OK) printf("���Ա�2��ճɹ���\n");
			     else printf("���Ա�2���ʧ�ܣ�\n");    
			 getchar();getchar();
			 break;
			 
			 
		   case 4: 
		   
		   
			 if(ListEmpty(L2)==TRUE) printf("�����Ա�Ϊ�գ�\n");
			     else printf("�����Ա�ǿգ�\n");    
			 getchar();getchar();
			 break;
			 
			 
		   case 5:
		   	
		   	
			 int len; 
			 if((len=ListLength(L2))>=0) printf("�����Ա�Ϊ����Ϊ%d��\n",len);
			     else printf("�޴����Ա�\n");    
			 getchar();getchar();
			 break;
			 
			 
		   case 6:
		   	
		   	
			 int i; ElemType  e;
			 printf("  ������Ҫ��ȡ��Ԫ��λ�ã�\n");
			 scanf("%d",&i); 
			 if(GetElem(L2,i,e)) printf("�����Ա��λ�õ�Ԫ��Ϊ:%d\n",e);
			     else printf("��������\n");    
			 getchar();getchar();
			 break;
			 
			 
		   case 7:  
		   
		   
			 int ans;    
			 printf("  ��������Ҫ��ȡ��Ԫ�أ�\n");
			 scanf("%d",&e);
			 if((ans=LocateElem(L2,e))) printf("�����Ա��Ԫ�ص�λ��Ϊ:%d\n",ans);
			     else printf("û�д�Ԫ�أ�\n"); 
			 getchar();getchar();
			 break;
			 
			 
		   case 8:
		   
		        
			 printf("  ��������Ҫ��ȡǰһ��Ԫ�ص�Ԫ�أ�\n");
			 scanf("%d",&e);
			 if(PriorElem(L2,e,ans)) printf("�����Ա��Ԫ�ص�ǰһ��Ԫ��Ϊ:%d\n",ans);
			     else printf("û�д�Ԫ�أ�\n");
			 getchar();getchar();
			 break;
			 
			 
		   case 9:
		        
			 printf("  ��������Ҫ��ȡ��һ��Ԫ�ص�Ԫ�أ�\n");
			 scanf("%d",&e);
			 if((NextElem(L2,e,ans))) printf("�����Ա��Ԫ�صĺ�һ��Ԫ��Ϊ:%d\n",ans);
			     else printf("û�д�Ԫ�أ�\n"); 
			 getchar();getchar();
			 break;
			 
			 
		   case 10:
		   
		      
			 printf("  ��������Ҫ����Ԫ�ص�λ�ã�\n");
			 scanf("%d",&i);
			 if(i<1||i>ListLength(L2)+1)  printf("������Ϸ������ݣ���0~%d֮��",ListLength(L2)); 
			 else{
			 	printf("  ��������Ҫ�����Ԫ�أ�\n");
			 	scanf("%d",&e);
			 	if(ListInsert(L2,i,e)) printf("�ѳɹ����룡\n");
			     	else printf("��������\n");
			 }     
			 getchar();getchar();
			 break;
			 
			 
		   case 11:
		   
		    
			 printf("  ��������Ҫɾ��Ԫ�ص�λ�ã�\n");
			 scanf("%d",&i);
			 if(ListDelete(L2,i,e)) printf("�ѳɹ�ɾ����Ԫ��Ϊ��%d\n",e);
			     else printf("��������\n");       
			 getchar();getchar();
			 break;
			 
			 
		   case 12:    
		   
		    
			 if(!ListTrabverse(L2)) printf("���Ա��ǿձ�\n");
			 getchar();getchar();
			 break;
			 
			 
		   case 13:
		   
		        
			 printf("\n������Ҫ������ļ�����\n");
			 scanf("%s",fileName);
			 if(SaveToFile(fileName,L2)) printf("�ѳɹ��������ļ�!");
			 else printf("����ʧ�ܣ�"); 
			 getchar();getchar();
			 break;
			 
			 
		   case 14:
		   
		        
			 printf("\n������Ҫ��ȡ���ļ�����\n");
			 scanf("%s",fileName);
			 if(LoadFromFile(fileName,L2)) printf("�ѳɹ����ļ���ȡ!");
			 else printf("��ȡʧ�ܣ�"); 
			 getchar();getchar();
			 break;
			 
			 
		   case 0:
	         break;
		}//end of switch
	}//end of if
	else {
		printf("��������"); 
	}
  }//end of while
  printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
  return 0;
}//end of main()

status IntiaList(LinkList & L){
	//����һ���յ����Ա�L 
	L = (LinkList)malloc(sizeof (LNode));
    if(!L) exit(OVERFLOW); //�洢����ʧ�� 
	L->data=0;                 //��һ��Ԫ����Ϊ0 
    L->next=NULL;  //ָ���ÿ� 
	return OK;
}
status DestroyList(LinkList & L){
	if(L==NULL) return OK;   //L������	
	LinkList p,q;
	p=L;
	while(p!=NULL){//�ͷ��ڴ�
		q=p->next;
		free(p);
		p=q;
	}               
	L=NULL;//��ͷ�ڵ��ÿ� 
	return OK;
} 

status ClearList(LinkList &L){
	if(L->next==NULL) return OK;   //L������Ԫ�ؽڵ�	
	LinkList p,q;
	p=L->next;
	while(p!=NULL){//�ͷ��ڴ�
		q=p->next;
		free(p);
		p=q;
	}               
	L->next=NULL;//��һ���ڵ��ÿ� 
	return OK;
} 

status ListEmpty(LinkList L){
	if(L->next) return false;  //����Ԫ�ؽڵ� 
	else return true;          //������Ԫ�ؽڵ� 
} 

int ListLength(LinkList L){
	if(!L) exit(ERROR); //�쳣����
	int i=0;
	LinkList p=L->next;//pָ���һ��Ԫ�ؽڵ� 
	while(p){
		i++;
		p=p->next;
	}  
	return i;
} 
status GetElem(LinkList L,int i,ElemType & e){
	int j=1;
	LinkList p;
	p=L->next;
	while(j<i&&p){//���αȽϣ�Ѱ�Ҳ���λ�� 
		j++;
		p=p->next;
	} 
	if(j<i||!p) return ERROR;//�쳣���� 
	e=p->data;
	return OK;
}

status LocateElem(LinkList L,ElemType e){
	int i=0;
	LinkList p=L->next;
	while(p){
		i++;//�±���� 
		if(p->data==e){//�ҵ�Ԫ�� 
			return i;
		}
		p=p->next;
	} 
	return 0;
}

status PriorElem(LinkList L,ElemType cur,ElemType & pre_e){
	LinkList p=L->next;
	while(p->next!=NULL&&p->next->data!=cur){ //����Ѱ�� 
		p=p->next;
	} 
	if(p->next==NULL) return ERROR;   //�쳣����
	pre_e=p->data;     //�ҵ��� 
	return OK; 
} 

status NextElem(LinkList L,ElemType cur,ElemType & next_e){
	
	LinkList p=L->next;
	while(p->next!=NULL&&p->data!=cur){
		p=p->next;
	} 
	if(p->next==NULL) return ERROR;   //δ�ҵ����쳣����
	next_e=p->next->data;
	return OK; 
}

status ListInsert(LinkList & L,int i,ElemType e){
	LinkList p,newone;
	int j=1;
	p=L;
	while(j<i&&p){ //����Ѱ�� 
		j++;
		p=p->next;
	}
	if(!p){
		return ERROR;   //�쳣���� 
	}
	newone = (LinkList)malloc(sizeof(LNode));
	if(newone==NULL){
		exit(OVERFLOW); 
	} 
	newone->data=e;
	newone ->next= p->next;   //�½ڵ�ĺ��Ϊ�Ͻڵ�ĺ�� 
	p->next= newone;          //�Ͻڵ�ĺ��Ϊ�½ڵ�
	return OK; 
} 

status ListDelete(LinkList & L,int i,ElemType & e){
	LinkList p,q;
	int j=1;
	p=L;
	while(j<i&&p!=NULL){
		j++;
		p=p->next;
	}
	if(p==NULL){
		return ERROR;      //��i��Ԫ�ز����� 
	}
	q=p->next;
	p->next=q->next;       //��p�ĺ����Ϊq�ĺ�� 
	e=q->data;             //��ȡq������ 
	free(q);               //�ͷ��ڴ� 
	return OK; 
} 

status ListTrabverse(LinkList L){
   if(L->next==NULL) return ERROR;
   LinkList p= L->next; 
   printf("\n-----------all elements -----------------------\n");
	while(p!=NULL){
   	 printf("%d ",p->data);
   	 p=p->next;
	}
   printf("\n------------------ end ------------------------\n");
   return OK;
}

status LoadFromFile(char * filename,LinkList & L){
	IntiaList(L);
	FILE  *fp;
	if ((fp=fopen(filename,"r"))==NULL){
		printf("File open error\n ");
		return ERROR;
	}
	//L->next=(LinkList) malloc(sizeof(LNode));
	LinkList p=L;
	int temp;
	while((fread(&temp,sizeof(ElemType),1,fp))){
		p->next=(LinkList)malloc(sizeof(LNode));
		p=p->next;
		p->data=temp;
		p->next=NULL;	
	} 
	fclose(fp);
	return OK;
}
status SaveToFile(char * filename,LinkList  L){
	FILE  *fp;   
	
	//д�ļ��ķ��� 
	if ((fp=fopen(filename,"w"))==NULL){
		printf("File open error\n ");
		return ERROR;
	}
	LinkList p=L->next;
	if(!p) return ERROR;
	while(p){
		fwrite(&(p->data),sizeof(ElemType),1,fp);
		p=p->next;
	}
	fclose(fp);
	return OK;
}
