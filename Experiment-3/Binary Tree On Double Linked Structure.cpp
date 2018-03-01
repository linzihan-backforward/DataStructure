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

typedef int status; /*status�Ǻ��������ͣ���ֵ�Ǻ������״̬����*/
typedef char ElemType; //����Ԫ�����Ͷ���


int depth, LR;



//����Ԫ�����Ͷ���
typedef  struct BiTNode{
    ElemType          data;
    struct BiTNode    *lchild, *rchild; //���Һ���ָ��
}BiTNode, *BiTree;
BiTree t1,t2;
typedef struct QNode                    //���нڵ㣬����һ���������һ��ָ����������Ϊ��������ָ������
{
    BiTree data;
    struct QNode *next;
}QNode,*QueuePtr;

typedef struct
{
    QueuePtr front,rear;                //��ͷ����βָ�� 
}LinkQueue;

ElemType e, value, E;
BiTree e1, e2, e3, p;
FILE *fp;

status InitQueue(LinkQueue *Q);         //����һ���ն���
status EnQueue(LinkQueue *Q,BiTree e);  //���ٶ���Q��Q���ٴ���
status QueueEmpty(LinkQueue Q);         //��ջQΪ�ն��У��򷵻�TURE�����򷵻�FALSE
status DeQueue(LinkQueue *Q,BiTree *e); //ɾ������Q����Ԫ��,������e������ֵ������OK�����򷵻�ERROR
BiTree GetPoint(BiTree T,ElemType s);      
status InitBiTree(BiTree * T);          //����ն�����T
status DestroyBiTree(BiTree * T);       //������T�Ѵ���,���ٶ�����T
void CreateBiTree(BiTree * T,char * s);          //�����������T
status ClearBiTree(BiTree * T);         //��ն�����
bool BiTreeEmpty(BiTree T);           //��ʼ������������T���ڣ���TΪ�ն��������򷵻�TRUE,���򷵻�FALSE.
int BiTreeDepth(BiTree T);           //����������
BiTNode Root(BiTree T);                 //���ض������ĸ�
ElemType Value(BiTree T, BiTree e);       //���ض���������ֵ
status Assign(BiTree T, BiTree e, ElemType value);    //����������㸳ֵ
ElemType Parent(BiTree T,ElemType e);                 //��˫�׽��
ElemType LeftChild(BiTree T,ElemType e);              //�����ӽ��
ElemType RightChild(BiTree T,ElemType e);             //���Һ��ӽ��
ElemType LeftSibling(BiTree T,ElemType e);            //�����ֵܽ��
ElemType RightSibling(BiTree T,ElemType e);           //�����ֵܽ��
status InsertChild(BiTree T,BiTree p,int LR,BiTree c);//��������
status DeleteChild(BiTree T,BiTree p,int LR);         //ɾ������
status PreOrderTraverse(BiTree T, status (* Visit)(ElemType e));  //�������������
status InOrderTraverse(BiTree T,status (* Visit)(ElemType e));   //�������������
status PostOrderTraverse(BiTree T,status (* Visit)(ElemType e)); //�������������
status LevelOrderTraverse(BiTree T,status (* Visit)(ElemType e)); //�������������
void level(BiTree T, int h, status (* Visit)(ElemType e));
status Print(ElemType e);
int coutTheNode(BiTree T);
BiTree GetPoint(BiTree T,ElemType s); /* ���ض�����T��ָ��Ԫ��ֵΪs�Ľ���ָ�롣*/
status SaveToFile(BiTree T); //���浽�ļ���
status LoadFromFile(BiTree *T); //���ļ��ж�ȡ 
status InitBiTree(BiTree *T)
{
    *T = NULL;//ָ����ڵ��ָ���ʼ��Ϊ��
    return OK;
}

status DestroyBiTree(BiTree *T)
{
    free(T);//�ͷŸ��ڵ���ڴ� 
    return OK;
}

void CreateBiTree(BiTree *T)
{
    //�������������������н���ֵ(һ���ַ�)���ո��ַ���ʾ����
    char ch;
	ch= getchar(); 
    if(ch == '$')
    {
        *T = NULL;
    }
    else
    {
        *T = (BiTNode *)malloc(sizeof(BiTNode));
        (*T)->data = ch;  //���ɸ��ڵ�
        CreateBiTree(&((*T)->lchild));//����������
        CreateBiTree(&((*T)->rchild));//����������
    }

}

status ClearBiTree(BiTree *T){
    if((*T)==NULL)
        return OK;
    else
    {
        ClearBiTree(&(*T)->rchild);//���������ݹ���� 
        ClearBiTree(&(*T)->lchild);//���������ݹ����
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
/* ��ʼ����: ������T����,e��T��ĳ������Ԫ�� */
    /* �������: ��e��T�ķǸ����,�򷵻�����˫��,���򷵻أ��գ� */
    LinkQueue q;
    BiTree a;
    if(T){ /* �ǿ��� */
        InitQueue(&q); /* ��ʼ������ */
        EnQueue(&q,T); /* ������� */
        while(!QueueEmpty(q)) {/* �Ӳ��� */
            DeQueue(&q,&a); /* ����,����Ԫ�ظ���a */
            if((a->lchild && a->lchild->data==e) || (a->rchild && a->rchild->data==e))
                /* �ҵ�e(��������Һ���) */
                return a->data; /* ����e��˫�׵�ֵ */
            else {/* û�ҵ�e,����������Һ���ָ��(����ǿ�) */
                if(a->lchild)
                    EnQueue(&q,a->lchild);
                if(a->rchild)
                    EnQueue(&q,a->rchild);
            }
        }
    }
    return ERROR; /* ���ջ�û�ҵ�e */
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
        a=GetPoint(T,e);//�õ�ָ��e��ָ�� 
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
        p=GetPoint(T,a);//�õ�ָ��e���ڵ��ָ�� 
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
        p=GetPoint(T,a);//�õ�ָ��e�ֽڵ��ָ�� 
        if(p->lchild&&p->rchild&&p->lchild->data==e)
            return p->rchild->data;
    }
    return ERROR;
}

status InsertChild(BiTree T,BiTree *p,int LR,BiTree c)
{
    if(!c&&!T&&(LR==1||LR==0)) exit(OVERFLOW);
    if(LR==0){  //������ӽڵ� 
        if((*p)->lchild!=NULL) return ERROR;
        (*p)->lchild = c;
    }
    else{  //����Һ��ӽڵ�
        if((*p)->rchild!=NULL) return ERROR;
        (*p)->rchild = c;
    }
    return OK;
}

status DeleteChild(BiTree T,BiTree *p,int LR){
    if(T){
        if(!LR){  //ɾ�����ӽڵ� 
            (*p)->lchild=NULL;
        }
        else{    //ɾ���Һ��ӽڵ� 
            (*p)->rchild=NULL;
        }
        return OK;
    }
    return ERROR;
}


status PreOrderTraverse(BiTree T, status (* Visit)(ElemType e)){//�������
    if(T){//����������Ϊ��
        if(Visit(T->data))
            if(PreOrderTraverse(T->lchild, Visit))//�������������
                if(PreOrderTraverse(T->rchild, Visit)) //�������������
                    return OK;
        return 0;
    }
    else return OK;

}

status InOrderTraverse(BiTree T,status (* Visit)(ElemType e)){
    if(T){
        if(InOrderTraverse(T->lchild,Visit))  //����������� 
            if(Visit(T->data))
                if(InOrderTraverse(T->rchild,Visit))
                    return 1;
        return 0;
    }else return 1;
}

status PostOrderTraverse(BiTree T,status (* Visit)(ElemType e)){
    if(T){
        if(PostOrderTraverse(T->lchild,Visit))     //����������� 
            if(PostOrderTraverse(T->rchild,Visit))
                if(Visit(T->data))
                    return 1;
        return 0;
    }else return 1;
}


void level(BiTree T, int h, status (* Visit)(ElemType e)){
    if(T){
        if(h==1)
            Visit(T->data);  //�ڵ�Ϊָ��ֵ 
        else{
            level(T->lchild,h-1, Visit);   //�ڵ����С��ָ��ֵ 
            level(T->rchild,h-1, Visit);
        }
    }
}

status LevelOrderTraverse(BiTree T,status (* Visit)(ElemType e)){
    if(T){
    	int h=BiTreeDepth(T);
    	int i;
    	for(i=1;i<=h;i++){
        	level(T,i, Visit); //�����Ϊָ��ֵ�Ľڵ���б������� 
    	}
		return OK;

    }else return ERROR;
}

status Print(ElemType e){
    printf("%c", e);
    return OK;
}

status InitQueue(LinkQueue *Q){ 
/* ����һ���ն���Q */
    (*Q).front=(*Q).rear=(QueuePtr)malloc(sizeof(QNode));
    if(!(*Q).front)
        exit(OVERFLOW);
    (*Q).front->next=NULL;
    return OK;
}
status EnQueue(LinkQueue *Q,BiTree e){ 
/* ����Ԫ��eΪQ���µĶ�βԪ�� */
    QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
    if(!p) /* �洢����ʧ�� */
        exit(OVERFLOW);
    p->data=e;
    p->next=NULL;
    (*Q).rear->next=p;
    (*Q).rear=p;
    return OK;
}
status QueueEmpty(LinkQueue Q){ /* ��QΪ�ն���,�򷵻�TRUE,���򷵻�FALSE */
    if(Q.front==Q.rear)
        return TRUE;
    else
        return FALSE;
}
status DeQueue(LinkQueue *Q,BiTree *e){ /* �����в���,ɾ��Q�Ķ�ͷԪ��,��e������ֵ,������OK,���򷵻�ERROR */
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

BiTree GetPoint(BiTree T,ElemType s){ /* ���ض�����T��ָ��Ԫ��ֵΪs�Ľ���ָ�롣*/
    LinkQueue q;
    BiTree a;
    if(T) /* �ǿ��� */
    {
        InitQueue(&q); /* ��ʼ������ */
        EnQueue(&q,T); /* �������� */
        while(!QueueEmpty(q)) /* �Ӳ��� */
        {
            DeQueue(&q,&a); /* ����,����Ԫ�ظ���a */
            if(a->data==s)
                return a;
            if(a->lchild) /* ������ */
                EnQueue(&q,a->lchild); /* ������� */
            if(a->rchild) /* ���Һ��� */
                EnQueue(&q,a->rchild); /* ����Һ��� */
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
    //�������������������н���ֵ(һ���ַ�)���ո��ַ���ʾ����
    char ch;
	fread(&ch,sizeof(ElemType),1,fp); 
    if(ch == '$')
    {
        *T = NULL;
    }
    else
    {
        *T = (BiTNode *)malloc(sizeof(BiTNode));
        (*T)->data = ch;  //���ɸ��ڵ�
        //printf("%c ",(*T)->data);
        LoadFromFile(&((*T)->lchild));//����������
        LoadFromFile(&((*T)->rchild));//����������
    }

}
status SaveToFile(BiTree T){
	char temp='$';
	if((T)!=NULL) {
		printf("%c ",T->data);
		fwrite(&((T)->data),sizeof(ElemType),1,fp);
	}
	if(T->lchild!=NULL) SaveToFile(((T)->lchild));//����������
	else fwrite(&temp,sizeof(ElemType),1,fp);
	if(T->rchild!=NULL) SaveToFile(((T)->rchild));//����������
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
	printf("                                       �����������˵�                        \n");
	printf("------------------------------------------------------------------------------------------\n");
	printf("    	  1. InitBiTree����ʼ���ն�������       11. LeftChild����ڵ����ӣ�\n");
	printf("    	  2. DestroyBiTree�����ٶ�������        12. RightChild����ڵ��Һ��ӣ�\n");
	printf("    	  3. CreatBiTree�����򴴽���������      13. LeftSibling����ڵ����ֵܣ�\n");
	printf("    	  4. ClearBiTree����ն�������          14. RightSibling����ڵ����ֵܣ�\n");
	printf("    	  5. BiTreeEmpty���ж϶������Ƿ�Ϊ�գ�  15. InsertChild  ������������\n");
	printf("    	  6. BiTreeDepth�����������ȣ�        16. DeleteChild  ��ɾ��������\n");
	printf("    	  7. Root       �����ض������ĸ���      17. PreOrderTraverse  �����������\n");
	printf("    	  8. Value      �����ؽڵ��ֵ��        18. inOrderTraverse   �����������\n");
	printf("    	  9. Assign     �����ڵ㸳ֵ��          19. PostOrderTraverse �����������\n");
	printf("    	  10. Parent   �����׽ڵ㣩           20. LevelOrderTraverse������������\n");
	printf("    	  0. Exit      ���˳�ϵͳ��\n");
	printf("          21.Save      �������������浽�ļ���   22.Load             �����ļ��ж�ȡ��������   \n");
	printf("--------------------------------------------------------------------------------------------\n");
	printf("    ��ѡ����Ĳ���[0~20]:");
	scanf("%d",&op);
	    switch(op){
		   case 1:
		   	
		   	
			 if(InitBiTree(&t1)==OK) printf("������1�����ɹ���\n");
			     else printf("������1����ʧ�ܣ�\n");
			 getchar();getchar();
			 break;
			 
			 
		   case 2:
		   	
		   	
			 if(DestroyBiTree(&t1)==OK) printf("������1ɾ���ɹ���\n");
			     else printf("������1ɾ��ʧ�ܣ�\n");     
			 getchar();getchar();
			 break;
			 
			 
		   case 3: 
		   	 stringleng=0;
		   	 getchar();
		   	 printf("��������Ҫ�������ַ�����\n");
			 CreateBiTree(&t1);	 
			//if(coutTheNode(t1)!=stringleng) {
			// 	printf("�����ַ����Ƿ�");
			//	DestroyBiTree(&t1);  
			//}
			//else 
			printf("������1�����ɹ���\n");   
			 getchar();getchar();
			 break;
			 
			 
		   case 4: 
		   
		   
			 if(ClearBiTree(&t1)==OK) printf("�˶���������գ�\n");
			     else printf("��ճ���\n");    
			 getchar();getchar();
			 break;
			 
			 
		   case 5:
		   	
		   	 
			 if(BiTreeEmpty(t1)) printf("�˶�����Ϊ�գ�\n");
			     else printf("�˶������ǿ�\n");    
			 getchar();getchar();
			 break;
			 
			 
		   case 6:
		   	
		   	 int ans;
			 if(t1!=NULL&&(ans=BiTreeDepth(t1))) printf("�˶��������Ϊ:%d\n",ans);
			 else printf("��������\n");    
			 getchar();getchar();
			 break;
			 
			 
		   case 7:  
		   
		      
			 BiTNode rt; 
			 if(t1!=NULL){     //��������ʱ��ȡ�� 
			 	rt=Root(t1);
			 	printf("�˸��ڵ��ֵΪ��%c\n",rt.data);
			 }
			 else printf("��������\n");
			 getchar();getchar();
			 break;
			 
			 
		   case 8:
		   
		      
			 printf("��������Ҫ��ȡ�ڵ��ֵ��\n");getchar();
			 scanf("%c",&temp);
			 thisnode = GetPoint(t1,temp); //�õ�ֵΪtemp1�Ľڵ�
			 if(t1!=NULL&&thisnode!=NULL) printf("�ýڵ�Ԫ��Ϊ��%c\n",Value(t1,thisnode));
			 else printf("��������\n");
			 getchar();getchar();
			 break;
			 
			 
		   case 9:
		        
			 char temp1;   
			 printf("��������Ҫ�޸ĵĽڵ��ֵ��\n");getchar();
			 scanf("%c",&temp1);
			 printf("�������޸ĺ��ֵ��\n");getchar(); 
			 scanf("%c",&temp);
			 thisnode =GetPoint(t1,temp1);  //�õ�ֵΪtemp1�Ľڵ� 
			 if(t1!=NULL&&thisnode!=NULL) printf("�޸ĳɹ�%d\n",Assign(t1,thisnode,temp));
			 else printf("��������\n");
			 getchar();getchar();
			 break;
			 
			 
		   case 10:
		    
			 printf("  ��������Ҫ��ѯ��Ԫ�أ�\n"); getchar();
			 scanf("%c",&temp);
			 if(t1!=NULL&&(ans=Parent(t1,temp))!=ERROR)  printf("��˫�׽ڵ��ֵΪ��%c\n",ans); 
			 else {
			 	if(t1==NULL) printf("��������\n");
			 	else printf("δ�ҵ��ýڵ����˫�ף�\n");
			 }     
			 getchar();getchar();
			 break;
			 
			 
		   case 11:
		   
		    
			 printf("  ��������Ҫ��ѯ��Ԫ�أ�\n"); getchar();
			 scanf("%c",&temp);
			 if(t1!=NULL&&(ans=LeftChild(t1,temp))!=ERROR)  printf("�����ӽڵ��ֵΪ��%c\n",ans); 
			 else {
			 	if(t1==NULL) printf("��������\n");
			 	else printf("δ�ҵ��ýڵ�������ӣ�\n");
			 }     
			 getchar();getchar();
			 break;
			 
			 
		   case 12:    
		   
		    
			 printf("  ��������Ҫ��ѯ��Ԫ�أ�\n"); getchar();
			 scanf("%c",&temp);
			 if(t1!=NULL&&(ans=RightChild(t1,temp))!=ERROR)  printf("���Һ��ӽڵ��ֵΪ��%c\n",ans); 
			 else {
			 	if(t1==NULL) printf("��������\n");
			 	else printf("δ�ҵ��ýڵ�����Һ��ӣ�\n");
			 }     
			 getchar();getchar();
			 break;
			 
			 
		   case 13:
		   
		         
			 printf("  ��������Ҫ��ѯ��Ԫ�أ�\n"); getchar();
			 scanf("%c",&temp);
			 if(t1!=NULL&&(ans=LeftSibling(t1,temp))!=ERROR)  printf("�����ֵܽڵ��ֵΪ��%c\n",ans); 
			 else {
			 	if(t1==NULL) printf("��������\n");
			 	else printf("δ�ҵ��ýڵ�������ֵܣ�\n");
			 }     
			 getchar();getchar();
			 break;
			 
			 
		   case 14:
		   
		         
			 printf("  ��������Ҫ��ѯ��Ԫ�أ�\n"); getchar();
			 scanf("%c",&temp);
			 if(t1!=NULL&&(ans=RightSibling(t1,temp))!=ERROR)  printf("�����ֵܽڵ��ֵΪ��%c\n",ans); 
			 else {
			 	if(t1==NULL) printf("��������\n");
			 	else printf("δ�ҵ��ýڵ�������ֵܣ�\n");
			 }     
			 getchar();getchar();
			 break;
			 
			 
			 
		   case 15: 
		     
		   	 printf("����������嵽��������������0��1�ң�\n");
			 scanf("%d",&lorr);
			 printf("��������Ҫ����Ľڵ㣺\n"); getchar();
			 scanf("%c",&temp);getchar();
			 printf("��������������ֵ��\n"); 
			 CreateBiTree(&t2);
			 tempnode=GetPoint(t1,temp);
			 if(lorr==0){
				 
				 if(t1!=NULL&&t2!=NULL&&InsertChild(t1,&tempnode,lorr,t2)) printf("����ɹ���\n");
				 else printf("��������!\n"); 
			 }
			 else{
				 if(t1!=NULL&&InsertChild(t1,&tempnode,lorr,t2)) printf("����ɹ���\n");
				 else printf("��������!\n"); 
			 }
			 getchar();getchar();
	         break; 
	         
	         
		   case 16: 
		   	 printf("����������ɾ����������������0��1�ң�\n");
			 scanf("%d",&lorr);
			 printf("���������ɾ�������Ľڵ㣺\n");getchar();
			 scanf("%c",&temp);
			 thisnode = GetPoint(t1,temp);
			 printf("%c\n",thisnode->data); 
			 if(lorr==0){
				 if(t1!=NULL&&thisnode!=NULL&&thisnode->lchild!=NULL&&DeleteChild(t1,&thisnode,lorr)) printf("ɾ���ɹ���\n");
				 else printf("��������!\n"); 
			 }
			 else{
				 if(t1!=NULL&&tempnode!=0&&thisnode->rchild!=NULL&&DeleteChild(t1,&thisnode,lorr)) printf("ɾ���ɹ���\n");
				 else printf("��������!\n"); 
			 }
			 getchar(); getchar();
	         break;
	         
	      
		   case 17:
		   	 if(t1!=NULL&&PreOrderTraverse(t1,Print)) printf("\n�����ɹ���\n");
			 else printf("����ʧ�ܻ��������\n"); 
			 getchar();getchar();
	         break; 
	         
	       case 18:
		   	 if(t1!=NULL&&InOrderTraverse(t1,Print)) printf("\n�����ɹ���\n");
			 else printf("����ʧ�ܻ��������\n");
			 getchar();getchar();
	         break;
		   case 19:
		   	 if(t1!=NULL&&PostOrderTraverse(t1,Print)) printf("\n�����ɹ���\n");
			 else printf("����ʧ�ܻ��������\n");
			 getchar();getchar();
	         break;
		   case 20:
		   	 if(t1!=NULL&&LevelOrderTraverse(t1,Print)) printf("\n�����ɹ���\n");
			 else printf("����ʧ�ܻ��������\n");
			 getchar();getchar();
	         break; 
	       case 21:
		   
		        
			 printf("\n������Ҫ������ļ�����\n");
			 scanf("%s",fileName);
			 if ((fp=fopen(fileName,"w"))==NULL){
				printf("File open error\n ");
				return ERROR;
			 } 
			 SaveToFile(t1);
			 printf("�ѳɹ��������ļ�!");
			 fclose(fp);
			 getchar();getchar();
			 break;
			 
			 
		   case 22:
		   
		        
			 printf("\n������Ҫ��ȡ���ļ�����\n");
			 scanf("%s",fileName);
			 if ((fp=fopen(fileName,"r"))==NULL){
				printf("File open error\n ");
				return ERROR;
			}
			else{
				LoadFromFile(&t1); 
				printf("�ѳɹ����ļ���ȡ!"); 
			}
			 fclose(fp);
			 getchar();getchar();
			 break;
		   case 0:
	         break;
		}//end of switch
  }//end of while
  printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
  return 0;
}//end of main()
