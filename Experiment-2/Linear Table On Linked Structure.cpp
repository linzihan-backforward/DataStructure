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
typedef int ElemType; //数据元素类型定义


#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct LNode{  //顺序表（顺序结构）的定义
	ElemType  data;
	struct LNode *next;
}LNode, *LinkList;
status IntiaList(LinkList & L);

status DestroyList(LinkList & L);
status ClearList(LinkList &L);
status ListEmpty(LinkList L);
int ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType & e);
status LocateElem(LinkList L,ElemType e); //简化过
status PriorElem(LinkList L,ElemType cur,ElemType & pre_e);
status NextElem(LinkList L,ElemType cur,ElemType & next_e);
status ListInsert(LinkList & L,int i,ElemType e);
status ListDelete(LinkList & L,int i,ElemType & e);
status ListTrabverse(LinkList L);  //简化过
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
	printf("    请选择你的操作[0~14]:");
	scanf("%d",&op);
	printf("    请输入你要操作的线性表编号，1或2：");
	scanf("%d",&option);
	if(option==1){
	    switch(op){
		   case 1:
		   	
		   	
			 if(IntiaList(L1)==OK) printf("线性表1创建成功！\n");
			     else printf("线性表1创建失败！\n");
			 getchar();getchar();
			 break;
			 
			 
		   case 2:
		   	
		   	
			 if(DestroyList(L1)==OK) printf("线性表1删除成功！\n");
			     else printf("线性表1删除失败！\n");     
			 getchar();getchar();
			 break;
			 
			 
		   case 3: 
		   
		   
			 if(ClearList(L1)==OK) printf("线性表1清空成功！\n");
			     else printf("线性表1清空失败！\n");    
			 getchar();getchar();
			 break;
			 
			 
		   case 4: 
		   
		   
			 if(ListEmpty(L1)==TRUE) printf("此线性表为空！\n");
			     else printf("此线性表非空！\n");    
			 getchar();getchar();
			 break;
			 
			 
		   case 5:
		   	
		   	
			 int len; 
			 if((len=ListLength(L1))>=0) printf("此线性表为长度为%d！\n",len);
			     else printf("无此线性表！\n");    
			 getchar();getchar();
			 break;
			 
			 
		   case 6:
		   	
		   	
			 int i; ElemType  e;
			 printf("  请输入要获取的元素位置：\n");
			 scanf("%d",&i); 
			 if(GetElem(L1,i,e)) printf("此线性表该位置的元素为:%d\n",e);
			     else printf("输入有误！\n");    
			 getchar();getchar();
			 break;
			 
			 
		   case 7:  
		   
		   
			 int ans;    
			 printf("  请输入你要获取的元素：\n");
			 scanf("%d",&e);
			 if((ans=LocateElem(L1,e))) printf("此线性表该元素的位置为:%d\n",ans);
			     else printf("没有此元素！\n"); 
			 getchar();getchar();
			 break;
			 
			 
		   case 8:
		   
		        
			 printf("  请输入你要获取前一个元素的元素：\n");
			 scanf("%d",&e);
			 if((PriorElem(L1,e,ans))) printf("此线性表该元素的前一个元素为:%d\n",ans);
			     else printf("没有此元素！\n");
			 getchar();getchar();
			 break;
			 
			 
		   case 9:
		        
			 printf("  请输入你要获取后一个元素的元素：\n");
			 scanf("%d",&e);
			 if(NextElem(L1,e,ans)) printf("此线性表该元素的后一个元素为:%d\n",ans);
			     else printf("没有此元素！\n"); 
			 getchar();getchar();
			 break;
			 
			 
		   case 10:
		   
		      
			 printf("  请输入你要插入元素的位置：\n");
			 scanf("%d",&i);
			 if(i<1||i>ListLength(L1)+1)  printf("请输入合法的数据，在0~%d之间",ListLength(L1)+1); 
			 else {
			 	printf("  请输入你要插入的元素：\n");
			 	scanf("%d",&e);
			 	if(ListInsert(L1,i,e)) printf("已成功插入！\n");
			     	else printf("输入有误！\n");
			 }     
			 getchar();getchar();
			 break;
			 
			 
		   case 11:
		   
		    
			 printf("  请输入你要删除元素的位置：\n");
			 scanf("%d",&i);
			 if(ListDelete(L1,i,e)) printf("已成功删除！元素为：%d\n",e);
			     else printf("输入有误！\n");       
			 getchar();getchar();
			 break;
			 
			 
		   case 12:    
		   
		    
			 if(!ListTrabverse(L1)) printf("线性表是空表！\n");
			 getchar();getchar();
			 break;
			 
			 
		   case 13:
		   
		        
			 printf("\n请输入要保存的文件名：\n");
			 scanf("%s",fileName);
			 if(SaveToFile(fileName,L1)) printf("已成功保存至文件!");
			 else printf("保存失败！"); 
			 getchar();getchar();
			 break;
			 
			 
		   case 14:
		   
		        
			 printf("\n请输入要读取的文件名：\n");
			 scanf("%s",fileName);
			 if(LoadFromFile(fileName,L1)) printf("已成功从文件读取!");
			 else printf("读取失败！"); 
			 getchar();getchar();
			 break;
			 
			 
		   case 0:
	         break;
		}//end of switch
	}//end of if
	else if(option==2){
		switch(op){
		   case 1:
		   	
		   	
			 if(IntiaList(L2)==OK) printf("线性表2创建成功！\n");
			     else printf("线性表2创建失败！\n");
			 getchar();getchar();
			 break;
			 
			 
		   case 2:
		   	
		   	
			 if(DestroyList(L2)==OK) printf("线性表2删除成功！\n");
			     else printf("线性表2删除失败！\n");     
			 getchar();getchar();
			 break;
			 
			 
		   case 3: 
		   
		   
			 if(ClearList(L2)==OK) printf("线性表2清空成功！\n");
			     else printf("线性表2清空失败！\n");    
			 getchar();getchar();
			 break;
			 
			 
		   case 4: 
		   
		   
			 if(ListEmpty(L2)==TRUE) printf("此线性表为空！\n");
			     else printf("此线性表非空！\n");    
			 getchar();getchar();
			 break;
			 
			 
		   case 5:
		   	
		   	
			 int len; 
			 if((len=ListLength(L2))>=0) printf("此线性表为长度为%d！\n",len);
			     else printf("无此线性表！\n");    
			 getchar();getchar();
			 break;
			 
			 
		   case 6:
		   	
		   	
			 int i; ElemType  e;
			 printf("  请输入要获取的元素位置：\n");
			 scanf("%d",&i); 
			 if(GetElem(L2,i,e)) printf("此线性表该位置的元素为:%d\n",e);
			     else printf("输入有误！\n");    
			 getchar();getchar();
			 break;
			 
			 
		   case 7:  
		   
		   
			 int ans;    
			 printf("  请输入你要获取的元素：\n");
			 scanf("%d",&e);
			 if((ans=LocateElem(L2,e))) printf("此线性表该元素的位置为:%d\n",ans);
			     else printf("没有此元素！\n"); 
			 getchar();getchar();
			 break;
			 
			 
		   case 8:
		   
		        
			 printf("  请输入你要获取前一个元素的元素：\n");
			 scanf("%d",&e);
			 if(PriorElem(L2,e,ans)) printf("此线性表该元素的前一个元素为:%d\n",ans);
			     else printf("没有此元素！\n");
			 getchar();getchar();
			 break;
			 
			 
		   case 9:
		        
			 printf("  请输入你要获取后一个元素的元素：\n");
			 scanf("%d",&e);
			 if((NextElem(L2,e,ans))) printf("此线性表该元素的后一个元素为:%d\n",ans);
			     else printf("没有此元素！\n"); 
			 getchar();getchar();
			 break;
			 
			 
		   case 10:
		   
		      
			 printf("  请输入你要插入元素的位置：\n");
			 scanf("%d",&i);
			 if(i<1||i>ListLength(L2)+1)  printf("请输入合法的数据，在0~%d之间",ListLength(L2)); 
			 else{
			 	printf("  请输入你要插入的元素：\n");
			 	scanf("%d",&e);
			 	if(ListInsert(L2,i,e)) printf("已成功插入！\n");
			     	else printf("输入有误！\n");
			 }     
			 getchar();getchar();
			 break;
			 
			 
		   case 11:
		   
		    
			 printf("  请输入你要删除元素的位置：\n");
			 scanf("%d",&i);
			 if(ListDelete(L2,i,e)) printf("已成功删除！元素为：%d\n",e);
			     else printf("输入有误！\n");       
			 getchar();getchar();
			 break;
			 
			 
		   case 12:    
		   
		    
			 if(!ListTrabverse(L2)) printf("线性表是空表！\n");
			 getchar();getchar();
			 break;
			 
			 
		   case 13:
		   
		        
			 printf("\n请输入要保存的文件名：\n");
			 scanf("%s",fileName);
			 if(SaveToFile(fileName,L2)) printf("已成功保存至文件!");
			 else printf("保存失败！"); 
			 getchar();getchar();
			 break;
			 
			 
		   case 14:
		   
		        
			 printf("\n请输入要读取的文件名：\n");
			 scanf("%s",fileName);
			 if(LoadFromFile(fileName,L2)) printf("已成功从文件读取!");
			 else printf("读取失败！"); 
			 getchar();getchar();
			 break;
			 
			 
		   case 0:
	         break;
		}//end of switch
	}//end of if
	else {
		printf("输入有误！"); 
	}
  }//end of while
  printf("欢迎下次再使用本系统！\n");
  return 0;
}//end of main()

status IntiaList(LinkList & L){
	//构造一个空的线性表L 
	L = (LinkList)malloc(sizeof (LNode));
    if(!L) exit(OVERFLOW); //存储分配失败 
	L->data=0;                 //第一个元素置为0 
    L->next=NULL;  //指针置空 
	return OK;
}
status DestroyList(LinkList & L){
	if(L==NULL) return OK;   //L不存在	
	LinkList p,q;
	p=L;
	while(p!=NULL){//释放内存
		q=p->next;
		free(p);
		p=q;
	}               
	L=NULL;//第头节点置空 
	return OK;
} 

status ClearList(LinkList &L){
	if(L->next==NULL) return OK;   //L不存在元素节点	
	LinkList p,q;
	p=L->next;
	while(p!=NULL){//释放内存
		q=p->next;
		free(p);
		p=q;
	}               
	L->next=NULL;//第一个节点置空 
	return OK;
} 

status ListEmpty(LinkList L){
	if(L->next) return false;  //存在元素节点 
	else return true;          //不存在元素节点 
} 

int ListLength(LinkList L){
	if(!L) exit(ERROR); //异常处理
	int i=0;
	LinkList p=L->next;//p指向第一个元素节点 
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
	while(j<i&&p){//依次比较，寻找插入位置 
		j++;
		p=p->next;
	} 
	if(j<i||!p) return ERROR;//异常处理 
	e=p->data;
	return OK;
}

status LocateElem(LinkList L,ElemType e){
	int i=0;
	LinkList p=L->next;
	while(p){
		i++;//下标递增 
		if(p->data==e){//找到元素 
			return i;
		}
		p=p->next;
	} 
	return 0;
}

status PriorElem(LinkList L,ElemType cur,ElemType & pre_e){
	LinkList p=L->next;
	while(p->next!=NULL&&p->next->data!=cur){ //依次寻找 
		p=p->next;
	} 
	if(p->next==NULL) return ERROR;   //异常处理
	pre_e=p->data;     //找到了 
	return OK; 
} 

status NextElem(LinkList L,ElemType cur,ElemType & next_e){
	
	LinkList p=L->next;
	while(p->next!=NULL&&p->data!=cur){
		p=p->next;
	} 
	if(p->next==NULL) return ERROR;   //未找到，异常处理
	next_e=p->next->data;
	return OK; 
}

status ListInsert(LinkList & L,int i,ElemType e){
	LinkList p,newone;
	int j=1;
	p=L;
	while(j<i&&p){ //依次寻找 
		j++;
		p=p->next;
	}
	if(!p){
		return ERROR;   //异常处理 
	}
	newone = (LinkList)malloc(sizeof(LNode));
	if(newone==NULL){
		exit(OVERFLOW); 
	} 
	newone->data=e;
	newone ->next= p->next;   //新节点的后继为老节点的后继 
	p->next= newone;          //老节点的后继为新节点
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
		return ERROR;      //第i个元素不存在 
	}
	q=p->next;
	p->next=q->next;       //将p的后继设为q的后继 
	e=q->data;             //读取q的数据 
	free(q);               //释放内存 
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
	
	//写文件的方法 
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
