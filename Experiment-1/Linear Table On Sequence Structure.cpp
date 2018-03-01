/* Linear Table On Sequence Structure */
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
typedef struct{  //顺序表（顺序结构）的定义
	ElemType * elem;
	int length;
	int listsize;
}SqList;

status IntiaList(SqList & L);
status DestroyList(SqList & L);
status ClearList(SqList &L);
status ListEmpty(SqList L);
int ListLength(SqList L);
status GetElem(SqList L,int i,ElemType & e);
status LocateElem(SqList L,ElemType e); //简化过
status PriorElem(SqList L,ElemType cur,ElemType & pre_e);
status NextElem(SqList L,ElemType cur,ElemType & next_e);
status ListInsert(SqList & L,int i,ElemType e);
status ListDelete(SqList & L,int i,ElemType & e);
status ListTrabverse(SqList L);  //简化过
status LoadFromFile(char * filename,SqList & L);
status SaveToFile(char * filename,SqList  L); 
/*--------------------------------------------*/
int main(){
  SqList L1,L2;  int op=1;
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
			 if((NextElem(L1,e,ans))) printf("此线性表该元素的后一个元素为:%d\n",ans);
			     else printf("没有此元素！\n"); 
			 getchar();getchar();
			 break;
			 
			 
		   case 10:
		   
		      
			 printf("  请输入你要插入元素的位置：\n");
			 scanf("%d",&i);
			 if(!L1.elem) printf("操作不合法"); 
			 if(i<1||i>L1.length+1)  printf("请输入合法的数据，在0~%d之间",L1.length+1); 
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
			 if(!L1.elem) printf("操作不合法"); 
			 if(i<1||i>L1.length+1)  printf("请输入合法的数据，在0~%d之间",L1.length); 
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
			 if(ListInsert(L2,i,e)) printf("已成功删除！元素为：%d\n",e);
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

status IntiaList(SqList & L){
	//构造一个空的线性表L 
	L.elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    if(!L.elem) exit(OVERFLOW); //存储分配失败 
	L.length=0;                 //空表长度为0 
    L.listsize=LIST_INIT_SIZE;  //初始存储容量 
	return OK;
}

status DestroyList(SqList & L){
	if(!L.elem) return OK;   //L不存在	
	free(L.elem);              //释放内存 
	L.length=0;                //空表长度置零 
	L.listsize=0;              //初始容量置0 
	return OK;
} 

status ClearList(SqList &L){
	if(!L.elem) exit(ERROR); 
	L.length=0;                 //空表长度为0 
    L.listsize=LIST_INIT_SIZE;  //初始存储容量 
	return OK;
} 

status ListEmpty(SqList L){
	if(!L.elem) exit(ERROR); //异常处理 
	if(L.length==0) return TRUE; //空表 
	else return FALSE;           //非空 
} 

int ListLength(SqList L){
	if(!L.elem) exit(ERROR); //异常处理  
	return L.length;
} 

status GetElem(SqList L,int i,ElemType & e){
	if(!L.elem) exit(ERROR); //异常处理  
	if(i>L.length) exit(OVERFLOW);
	e=L.elem[i-1];
	return OK;
}

status LocateElem(SqList L,ElemType e){
	int i=1; //i的初值为第一个元素的位序 
	ElemType *p=L.elem; //p的初值为第1个元素的存储位置 
	if(p==NULL) exit(ERROR); 
	while(i<=L.length&&((*p++)!=e)) ++i;
	if(i<=L.length) return i;
	else return 0;
}

status PriorElem(SqList L,ElemType cur,ElemType & pre_e){
	if(!L.elem) exit(ERROR); 
	for(int i=1;i<L.length;i++){ //从第二个开始遍历 
		if(L.elem[i]==cur){
			pre_e=L.elem[i-1];
			return  OK;  //找到了 
		}
	} 
	return ERROR;  //未找到 
} 

status NextElem(SqList L,ElemType cur,ElemType & next_e){
	if(!L.elem) exit(ERROR);
	for(int i=0;i<L.length-1;i++){
		if(L.elem[i]==cur){
			next_e=L.elem[i+1];
			return  OK;  //找到了 
		}
	} 
	return ERROR;      //未找到 
}

status ListInsert(SqList & L,int i,ElemType e){
	//在顺序线性表L中第i个位置之前插入新的元素e 
	//i的合法位置为1<=i<=ListLength_Sq(L)+1
	if(!L.elem) exit(ERROR);
	if(i<1||i>L.length+1) return ERROR;  //i值不合法 
	if(L.length>=L.listsize){   //当前存储空间已满，增加分配 
		ElemType * newbase =(ElemType *) realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase) exit(OVERFLOW);    //存储分配失败 
		L.elem=newbase;                 //新基址 
		L.listsize+=LISTINCREMENT;      //增加存储容量 
	} 
	ElemType * q=&(L.elem[i-1]);
	for(ElemType *p=&(L.elem[L.length-1]);p>=q;--p) *(p+1) =*p;   //插入位置及之后的元素右移 
	
	*q =e;    //插入e
	++L.length;     //表长增1
	return OK; 
} 

status ListDelete(SqList & L,int i,ElemType & e){
	if(!L.elem) exit(ERROR);
    //在顺序线性表L中删除第i个元素，并用e返回其值
	//i的合法值为1<=i<=ListLength_Sq(L) 
	if((i<1)||(i>L.length)) return ERROR;  //i值不合法 
	ElemType *p=&(L.elem[i-1]);            //p为被删除元素的位置 
	e=*p;                                  //被删除元素的值赋给e 
	ElemType * q=L.elem+L.length-1;        //表尾元素的位置 
	for(++p;p<=q;++p) *(p-1)=*p;           //被删除元素之后的元素左移 
	--L.length;                            //表长减1 
	return OK;
} 

status ListTrabverse(SqList L){
   int i;
   if(!L.elem) exit(ERROR);
   printf("\n-----------all elements -----------------------\n");
   for(i=0;i<L.length;i++) printf("%d ",L.elem[i]);
   printf("\n------------------ end ------------------------\n");
   return L.length;
}

status LoadFromFile(char * filename,SqList & L){
	IntiaList(L);
	FILE  *fp;
	if ((fp=fopen(filename,"r"))==NULL){
		printf("File open error\n ");
		return ERROR;
	}
	while(fread(&L.elem[L.length],sizeof(ElemType),1,fp))
	   L.length++;
	fclose(fp);
	return OK;
}
status SaveToFile(char * filename,SqList  L){
	FILE  *fp;   
	
	//写文件的方法 
	if ((fp=fopen(filename,"w"))==NULL){
		printf("File open error\n ");
		return ERROR;
	}
	fwrite(L.elem,sizeof(ElemType),L.length,fp);
	fclose(fp);
	return OK;
}
