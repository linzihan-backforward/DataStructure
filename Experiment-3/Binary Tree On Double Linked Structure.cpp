/* Binary Tree On Double Linked Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status; /*status是函数的类型，其值是函数结果状态代码*/
typedef char ElemType; //数据元素类型定义


int depth, LR;



//数据元素类型定义
typedef  struct BiTNode{
    ElemType          data;
    struct BiTNode    *lchild, *rchild; //左右孩子指针
}BiTNode, *BiTree;
BiTree t1,t2;
typedef struct QNode                    //队列节点，包括一个数据域和一个指针域，数据域为二叉树的指针类型
{
    BiTree data;
    struct QNode *next;
}QNode,*QueuePtr;

typedef struct
{
    QueuePtr front,rear;                //队头、队尾指针 
}LinkQueue;

ElemType e, value, E;
BiTree e1, e2, e3, p;
FILE *fp;

status InitQueue(LinkQueue *Q);         //构造一个空队列
status EnQueue(LinkQueue *Q,BiTree e);  //销毁队列Q，Q不再存在
status QueueEmpty(LinkQueue Q);         //若栈Q为空队列，则返回TURE，否则返回FALSE
status DeQueue(LinkQueue *Q,BiTree *e); //删除队列Q的首元素,并且用e返回其值并返回OK；否则返回ERROR
BiTree GetPoint(BiTree T,ElemType s);      
status InitBiTree(BiTree * T);          //构造空二叉树T
status DestroyBiTree(BiTree * T);       //二叉树T已存在,销毁二叉树T
void CreateBiTree(BiTree * T,char * s);          //先序构造二叉树T
status ClearBiTree(BiTree * T);         //清空二叉树
bool BiTreeEmpty(BiTree T);           //初始条件：二叉树T存在，若T为空二叉树，则返回TRUE,否则返回FALSE.
int BiTreeDepth(BiTree T);           //求二叉树深度
BiTNode Root(BiTree T);                 //返回二叉树的根
ElemType Value(BiTree T, BiTree e);       //返回二叉树结点的值
status Assign(BiTree T, BiTree e, ElemType value);    //给二叉树结点赋值
ElemType Parent(BiTree T,ElemType e);                 //求双亲结点
ElemType LeftChild(BiTree T,ElemType e);              //求左孩子结点
ElemType RightChild(BiTree T,ElemType e);             //求右孩子结点
ElemType LeftSibling(BiTree T,ElemType e);            //求左兄弟结点
ElemType RightSibling(BiTree T,ElemType e);           //求右兄弟结点
status InsertChild(BiTree T,BiTree p,int LR,BiTree c);//插入子树
status DeleteChild(BiTree T,BiTree p,int LR);         //删除子树
status PreOrderTraverse(BiTree T, status (* Visit)(ElemType e));  //先序遍历二叉树
status InOrderTraverse(BiTree T,status (* Visit)(ElemType e));   //中序遍历二叉树
status PostOrderTraverse(BiTree T,status (* Visit)(ElemType e)); //后序遍历二叉树
status LevelOrderTraverse(BiTree T,status (* Visit)(ElemType e)); //层序遍历二叉树
void level(BiTree T, int h, status (* Visit)(ElemType e));
status Print(ElemType e);
int coutTheNode(BiTree T);
BiTree GetPoint(BiTree T,ElemType s); /* 返回二叉树T中指向元素值为s的结点的指针。*/
status SaveToFile(BiTree T); //保存到文件中
status LoadFromFile(BiTree *T); //从文件中读取 
status InitBiTree(BiTree *T)
{
    *T = NULL;//指向根节点的指针初始化为空
    return OK;
}

status DestroyBiTree(BiTree *T)
{
    free(T);//释放根节点的内存 
    return OK;
}

void CreateBiTree(BiTree *T)
{
    //按先序次序输入二叉树中结点的值(一个字符)，空格字符表示空树
    char ch;
	ch= getchar(); 
    if(ch == '$')
    {
        *T = NULL;
    }
    else
    {
        *T = (BiTNode *)malloc(sizeof(BiTNode));
        (*T)->data = ch;  //生成根节点
        CreateBiTree(&((*T)->lchild));//构造左子树
        CreateBiTree(&((*T)->rchild));//构造右子树
    }

}

status ClearBiTree(BiTree *T){
    if((*T)==NULL)
        return OK;
    else
    {
        ClearBiTree(&(*T)->rchild);//对左子树递归清除 
        ClearBiTree(&(*T)->lchild);//对右子树递归清除
        free(*T);
        return OK;
    }
}

bool BiTreeEmpty(BiTree T){
    if(T == NULL){
        return true;
    }
    else{
        return false;
    }
}

int BiTreeDepth(BiTree T){
    int dept = 0;
    if(T){
        int lchilddepth = BiTreeDepth(T->lchild);
        int rchilddepth = BiTreeDepth(T->rchild);
        dept = lchilddepth >= rchilddepth ? (lchilddepth + 1) : (rchilddepth + 1);
    }
    return dept;
}

BiTNode Root(BiTree T){
    return *T;
}

ElemType Value(BiTree T, BiTree e){
    return e->data;
}

status Assign(BiTree T, BiTree e, ElemType value){
    e->data = value;
    return OK;
}

ElemType Parent(BiTree T,ElemType e){ 
/* 初始条件: 二叉树T存在,e是T中某个结点的元素 */
    /* 操作结果: 若e是T的非根结点,则返回它的双亲,否则返回＂空＂ */
    LinkQueue q;
    BiTree a;
    if(T){ /* 非空树 */
        InitQueue(&q); /* 初始化队列 */
        EnQueue(&q,T); /* 树根入队 */
        while(!QueueEmpty(q)) {/* 队不空 */
            DeQueue(&q,&a); /* 出队,队列元素赋给a */
            if((a->lchild && a->lchild->data==e) || (a->rchild && a->rchild->data==e))
                /* 找到e(是其左或右孩子) */
                return a->data; /* 返回e的双亲的值 */
            else {/* 没找到e,则入队其左右孩子指针(如果非空) */
                if(a->lchild)
                    EnQueue(&q,a->lchild);
                if(a->rchild)
                    EnQueue(&q,a->rchild);
            }
        }
    }
    return ERROR; /* 树空或没找到e */
}

ElemType LeftChild(BiTree T,ElemType e)
{
    BiTree a;
    if(T){
        a=GetPoint(T,e);
        if(a&&a->lchild)
            return a->lchild->data;
    }
    return ERROR;
}
ElemType RightChild(BiTree T,ElemType e)
{
    BiTree a;
    if(T){
        a=GetPoint(T,e);//得到指向e的指针 
        if(a&&a->rchild)
            return a->rchild->data;
    }
    return ERROR;
}
ElemType LeftSibling(BiTree T,ElemType e)
{
    ElemType a;
    BiTree p;
    if(T){
        a=Parent(T,e);
        p=GetPoint(T,a);//得到指向e父节点的指针 
        if(p->lchild&&p->rchild&&p->rchild->data==e)
            return p->lchild->data;
    }
    return ERROR;
}

ElemType RightSibling(BiTree T,ElemType e)
{
    ElemType a;
    BiTree p;
    if(T){
        a=Parent(T,e);
        p=GetPoint(T,a);//得到指向e又节点的指针 
        if(p->lchild&&p->rchild&&p->lchild->data==e)
            return p->rchild->data;
    }
    return ERROR;
}

status InsertChild(BiTree T,BiTree *p,int LR,BiTree c)
{
    if(!c&&!T&&(LR==1||LR==0)) exit(OVERFLOW);
    if(LR==0){  //添加左孩子节点 
        if((*p)->lchild!=NULL) return ERROR;
        (*p)->lchild = c;
    }
    else{  //添加右孩子节点
        if((*p)->rchild!=NULL) return ERROR;
        (*p)->rchild = c;
    }
    return OK;
}

status DeleteChild(BiTree T,BiTree *p,int LR){
    if(T){
        if(!LR){  //删除左孩子节点 
            (*p)->lchild=NULL;
        }
        else{    //删除右孩子节点 
            (*p)->rchild=NULL;
        }
        return OK;
    }
    return ERROR;
}


status PreOrderTraverse(BiTree T, status (* Visit)(ElemType e)){//先序遍历
    if(T){//若二叉树不为空
        if(Visit(T->data))
            if(PreOrderTraverse(T->lchild, Visit))//先序遍历左子树
                if(PreOrderTraverse(T->rchild, Visit)) //先序遍历右子树
                    return OK;
        return 0;
    }
    else return OK;

}

status InOrderTraverse(BiTree T,status (* Visit)(ElemType e)){
    if(T){
        if(InOrderTraverse(T->lchild,Visit))  //中序遍历访问 
            if(Visit(T->data))
                if(InOrderTraverse(T->rchild,Visit))
                    return 1;
        return 0;
    }else return 1;
}

status PostOrderTraverse(BiTree T,status (* Visit)(ElemType e)){
    if(T){
        if(PostOrderTraverse(T->lchild,Visit))     //后序遍历访问 
            if(PostOrderTraverse(T->rchild,Visit))
                if(Visit(T->data))
                    return 1;
        return 0;
    }else return 1;
}


void level(BiTree T, int h, status (* Visit)(ElemType e)){
    if(T){
        if(h==1)
            Visit(T->data);  //节点为指定值 
        else{
            level(T->lchild,h-1, Visit);   //节点深度小于指定值 
            level(T->rchild,h-1, Visit);
        }
    }
}

status LevelOrderTraverse(BiTree T,status (* Visit)(ElemType e)){
    if(T){
    	int h=BiTreeDepth(T);
    	int i;
    	for(i=1;i<=h;i++){
        	level(T,i, Visit); //对深度为指定值的节点进行遍历访问 
    	}
		return OK;

    }else return ERROR;
}

status Print(ElemType e){
    printf("%c", e);
    return OK;
}

status InitQueue(LinkQueue *Q){ 
/* 构造一个空队列Q */
    (*Q).front=(*Q).rear=(QueuePtr)malloc(sizeof(QNode));
    if(!(*Q).front)
        exit(OVERFLOW);
    (*Q).front->next=NULL;
    return OK;
}
status EnQueue(LinkQueue *Q,BiTree e){ 
/* 插入元素e为Q的新的队尾元素 */
    QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
    if(!p) /* 存储分配失败 */
        exit(OVERFLOW);
    p->data=e;
    p->next=NULL;
    (*Q).rear->next=p;
    (*Q).rear=p;
    return OK;
}
status QueueEmpty(LinkQueue Q){ /* 若Q为空队列,则返回TRUE,否则返回FALSE */
    if(Q.front==Q.rear)
        return TRUE;
    else
        return FALSE;
}
status DeQueue(LinkQueue *Q,BiTree *e){ /* 若队列不空,删除Q的队头元素,用e返回其值,并返回OK,否则返回ERROR */
    QueuePtr p;
    if((*Q).front==(*Q).rear)
        return ERROR;
    p=(*Q).front->next;
    *e=p->data;
    (*Q).front->next=p->next;
    if((*Q).rear==p)
        (*Q).rear=(*Q).front;
    free(p);
    return OK;
}

BiTree GetPoint(BiTree T,ElemType s){ /* 返回二叉树T中指向元素值为s的结点的指针。*/
    LinkQueue q;
    BiTree a;
    if(T) /* 非空树 */
    {
        InitQueue(&q); /* 初始化队列 */
        EnQueue(&q,T); /* 根结点入队 */
        while(!QueueEmpty(q)) /* 队不空 */
        {
            DeQueue(&q,&a); /* 出队,队列元素赋给a */
            if(a->data==s)
                return a;
            if(a->lchild) /* 有左孩子 */
                EnQueue(&q,a->lchild); /* 入队左孩子 */
            if(a->rchild) /* 有右孩子 */
                EnQueue(&q,a->rchild); /* 入队右孩子 */
        }
    }
    return NULL;
}
int coutTheNode(BiTree T){
	int cnt=1;
	if(T->lchild) cnt+=coutTheNode(T->lchild);
	if(T->rchild) cnt+=coutTheNode(T->rchild);
	return cnt;
}
status LoadFromFile(BiTree *T)
{
    //按先序次序输入二叉树中结点的值(一个字符)，空格字符表示空树
    char ch;
	fread(&ch,sizeof(ElemType),1,fp); 
    if(ch == '$')
    {
        *T = NULL;
    }
    else
    {
        *T = (BiTNode *)malloc(sizeof(BiTNode));
        (*T)->data = ch;  //生成根节点
        //printf("%c ",(*T)->data);
        LoadFromFile(&((*T)->lchild));//构造左子树
        LoadFromFile(&((*T)->rchild));//构造右子树
    }

}
status SaveToFile(BiTree T){
	char temp='$';
	if((T)!=NULL) {
		printf("%c ",T->data);
		fwrite(&((T)->data),sizeof(ElemType),1,fp);
	}
	if(T->lchild!=NULL) SaveToFile(((T)->lchild));//构造左子树
	else fwrite(&temp,sizeof(ElemType),1,fp);
	if(T->rchild!=NULL) SaveToFile(((T)->rchild));//构造右子树
	else fwrite(&temp,sizeof(ElemType),1,fp);
}
/*--------------------------------------------*/
int main(){
  int op=1;
  ElemType  e,ans;
  int i;
  int option;
  char fileName[20];
  int lorr; char temp; 
  BiTree thisnode ; 
  BiTree newnode;
  BiTree tempnode;
  int stringleng;
  while(op){
	system("cls");	printf("\n\n");
	printf("                                       二叉树操作菜单                        \n");
	printf("------------------------------------------------------------------------------------------\n");
	printf("    	  1. InitBiTree（初始化空二叉树）       11. LeftChild（求节点左孩子）\n");
	printf("    	  2. DestroyBiTree（销毁二叉树）        12. RightChild（求节点右孩子）\n");
	printf("    	  3. CreatBiTree（先序创建二叉树）      13. LeftSibling（求节点左兄弟）\n");
	printf("    	  4. ClearBiTree（清空二叉树）          14. RightSibling（求节点右兄弟）\n");
	printf("    	  5. BiTreeEmpty（判断二叉树是否为空）  15. InsertChild  （插入子树）\n");
	printf("    	  6. BiTreeDepth（求二叉树深度）        16. DeleteChild  （删除子树）\n");
	printf("    	  7. Root       （返回二叉树的根）      17. PreOrderTraverse  （先序遍历）\n");
	printf("    	  8. Value      （返回节点的值）        18. inOrderTraverse   （中序遍历）\n");
	printf("    	  9. Assign     （给节点赋值）          19. PostOrderTraverse （后序遍历）\n");
	printf("    	  10. Parent   （求父亲节点）           20. LevelOrderTraverse（层序子树）\n");
	printf("    	  0. Exit      （退出系统）\n");
	printf("          21.Save      （将二叉树保存到文件）   22.Load             （从文件中读取二叉树）   \n");
	printf("--------------------------------------------------------------------------------------------\n");
	printf("    请选择你的操作[0~20]:");
	scanf("%d",&op);
	    switch(op){
		   case 1:
		   	
		   	
			 if(InitBiTree(&t1)==OK) printf("二叉树1创建成功！\n");
			     else printf("二叉树1创建失败！\n");
			 getchar();getchar();
			 break;
			 
			 
		   case 2:
		   	
		   	
			 if(DestroyBiTree(&t1)==OK) printf("二叉树1删除成功！\n");
			     else printf("二叉树1删除失败！\n");     
			 getchar();getchar();
			 break;
			 
			 
		   case 3: 
		   	 stringleng=0;
		   	 getchar();
		   	 printf("请输入你要建树的字符串：\n");
			 CreateBiTree(&t1);	 
			//if(coutTheNode(t1)!=stringleng) {
			// 	printf("输入字符串非法");
			//	DestroyBiTree(&t1);  
			//}
			//else 
			printf("二叉树1构建成功！\n");   
			 getchar();getchar();
			 break;
			 
			 
		   case 4: 
		   
		   
			 if(ClearBiTree(&t1)==OK) printf("此二叉树已清空！\n");
			     else printf("清空出错！\n");    
			 getchar();getchar();
			 break;
			 
			 
		   case 5:
		   	
		   	 
			 if(BiTreeEmpty(t1)) printf("此二叉树为空！\n");
			     else printf("此二叉树非空\n");    
			 getchar();getchar();
			 break;
			 
			 
		   case 6:
		   	
		   	 int ans;
			 if(t1!=NULL&&(ans=BiTreeDepth(t1))) printf("此二叉树深度为:%d\n",ans);
			 else printf("操作有误！\n");    
			 getchar();getchar();
			 break;
			 
			 
		   case 7:  
		   
		      
			 BiTNode rt; 
			 if(t1!=NULL){     //当树存在时再取根 
			 	rt=Root(t1);
			 	printf("此根节点的值为：%c\n",rt.data);
			 }
			 else printf("操作有误！\n");
			 getchar();getchar();
			 break;
			 
			 
		   case 8:
		   
		      
			 printf("请输入你要获取节点的值：\n");getchar();
			 scanf("%c",&temp);
			 thisnode = GetPoint(t1,temp); //得到值为temp1的节点
			 if(t1!=NULL&&thisnode!=NULL) printf("该节点元素为：%c\n",Value(t1,thisnode));
			 else printf("操作有误！\n");
			 getchar();getchar();
			 break;
			 
			 
		   case 9:
		        
			 char temp1;   
			 printf("请输入你要修改的节点的值：\n");getchar();
			 scanf("%c",&temp1);
			 printf("请输入修改后的值：\n");getchar(); 
			 scanf("%c",&temp);
			 thisnode =GetPoint(t1,temp1);  //得到值为temp1的节点 
			 if(t1!=NULL&&thisnode!=NULL) printf("修改成功%d\n",Assign(t1,thisnode,temp));
			 else printf("操作有误！\n");
			 getchar();getchar();
			 break;
			 
			 
		   case 10:
		    
			 printf("  请输入你要查询的元素：\n"); getchar();
			 scanf("%c",&temp);
			 if(t1!=NULL&&(ans=Parent(t1,temp))!=ERROR)  printf("其双亲节点的值为：%c\n",ans); 
			 else {
			 	if(t1==NULL) printf("操作有误！\n");
			 	else printf("未找到该节点或无双亲！\n");
			 }     
			 getchar();getchar();
			 break;
			 
			 
		   case 11:
		   
		    
			 printf("  请输入你要查询的元素：\n"); getchar();
			 scanf("%c",&temp);
			 if(t1!=NULL&&(ans=LeftChild(t1,temp))!=ERROR)  printf("其左孩子节点的值为：%c\n",ans); 
			 else {
			 	if(t1==NULL) printf("操作有误！\n");
			 	else printf("未找到该节点或无左孩子！\n");
			 }     
			 getchar();getchar();
			 break;
			 
			 
		   case 12:    
		   
		    
			 printf("  请输入你要查询的元素：\n"); getchar();
			 scanf("%c",&temp);
			 if(t1!=NULL&&(ans=RightChild(t1,temp))!=ERROR)  printf("其右孩子节点的值为：%c\n",ans); 
			 else {
			 	if(t1==NULL) printf("操作有误！\n");
			 	else printf("未找到该节点或无右孩子！\n");
			 }     
			 getchar();getchar();
			 break;
			 
			 
		   case 13:
		   
		         
			 printf("  请输入你要查询的元素：\n"); getchar();
			 scanf("%c",&temp);
			 if(t1!=NULL&&(ans=LeftSibling(t1,temp))!=ERROR)  printf("其左兄弟节点的值为：%c\n",ans); 
			 else {
			 	if(t1==NULL) printf("操作有误！\n");
			 	else printf("未找到该节点或无左兄弟！\n");
			 }     
			 getchar();getchar();
			 break;
			 
			 
		   case 14:
		   
		         
			 printf("  请输入你要查询的元素：\n"); getchar();
			 scanf("%c",&temp);
			 if(t1!=NULL&&(ans=RightSibling(t1,temp))!=ERROR)  printf("其右兄弟节点的值为：%c\n",ans); 
			 else {
			 	if(t1==NULL) printf("操作有误！\n");
			 	else printf("未找到该节点或无右兄弟！\n");
			 }     
			 getchar();getchar();
			 break;
			 
			 
			 
		   case 15: 
		     
		   	 printf("请输入你想插到左还是右子树：（0左1右）\n");
			 scanf("%d",&lorr);
			 printf("请输入你要插入的节点：\n"); getchar();
			 scanf("%c",&temp);getchar();
			 printf("请输入你想插入的值：\n"); 
			 CreateBiTree(&t2);
			 tempnode=GetPoint(t1,temp);
			 if(lorr==0){
				 
				 if(t1!=NULL&&t2!=NULL&&InsertChild(t1,&tempnode,lorr,t2)) printf("插入成功！\n");
				 else printf("操作有误!\n"); 
			 }
			 else{
				 if(t1!=NULL&&InsertChild(t1,&tempnode,lorr,t2)) printf("插入成功！\n");
				 else printf("操作有误!\n"); 
			 }
			 getchar();getchar();
	         break; 
	         
	         
		   case 16: 
		   	 printf("请输入你想删除左还是右子树：（0左1右）\n");
			 scanf("%d",&lorr);
			 printf("请输入进行删除操作的节点：\n");getchar();
			 scanf("%c",&temp);
			 thisnode = GetPoint(t1,temp);
			 printf("%c\n",thisnode->data); 
			 if(lorr==0){
				 if(t1!=NULL&&thisnode!=NULL&&thisnode->lchild!=NULL&&DeleteChild(t1,&thisnode,lorr)) printf("删除成功！\n");
				 else printf("操作有误!\n"); 
			 }
			 else{
				 if(t1!=NULL&&tempnode!=0&&thisnode->rchild!=NULL&&DeleteChild(t1,&thisnode,lorr)) printf("删除成功！\n");
				 else printf("操作有误!\n"); 
			 }
			 getchar(); getchar();
	         break;
	         
	      
		   case 17:
		   	 if(t1!=NULL&&PreOrderTraverse(t1,Print)) printf("\n遍历成功！\n");
			 else printf("遍历失败或操作有误！\n"); 
			 getchar();getchar();
	         break; 
	         
	       case 18:
		   	 if(t1!=NULL&&InOrderTraverse(t1,Print)) printf("\n遍历成功！\n");
			 else printf("遍历失败或操作有误！\n");
			 getchar();getchar();
	         break;
		   case 19:
		   	 if(t1!=NULL&&PostOrderTraverse(t1,Print)) printf("\n遍历成功！\n");
			 else printf("遍历失败或操作有误！\n");
			 getchar();getchar();
	         break;
		   case 20:
		   	 if(t1!=NULL&&LevelOrderTraverse(t1,Print)) printf("\n遍历成功！\n");
			 else printf("遍历失败或操作有误！\n");
			 getchar();getchar();
	         break; 
	       case 21:
		   
		        
			 printf("\n请输入要保存的文件名：\n");
			 scanf("%s",fileName);
			 if ((fp=fopen(fileName,"w"))==NULL){
				printf("File open error\n ");
				return ERROR;
			 } 
			 SaveToFile(t1);
			 printf("已成功保存至文件!");
			 fclose(fp);
			 getchar();getchar();
			 break;
			 
			 
		   case 22:
		   
		        
			 printf("\n请输入要读取的文件名：\n");
			 scanf("%s",fileName);
			 if ((fp=fopen(fileName,"r"))==NULL){
				printf("File open error\n ");
				return ERROR;
			}
			else{
				LoadFromFile(&t1); 
				printf("已成功从文件读取!"); 
			}
			 fclose(fp);
			 getchar();getchar();
			 break;
		   case 0:
	         break;
		}//end of switch
  }//end of while
  printf("欢迎下次再使用本系统！\n");
  return 0;
}//end of main()
