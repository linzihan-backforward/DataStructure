#include<iostream>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include<cstring>
#include<time.h>
#include<windows.h>
using namespace std; 
typedef struct {
	char name[30];
	int age;
	int gender;   //0�����У�1����Ů 
}info;
typedef struct _BitNode{
	int height;
	info data;
	_BitNode* lson,*rson;
}BitNode ,*BitTree; 
void InitAVL(BitTree *root);
void DestroyAVL(BitTree *root);
info SearchAVL(BitTree root,char* x);
int InsertAVL(BitTree *root,info x);
int DeleteAVL(BitTree *root,char* x);
void TraverseAVL(BitTree root);
int getHeight(BitTree root); 
void DestroyNode(BitTree *root);
int Max(int a,int b);
int namebigger(char *a,char *b);
int namesmaller(char *a,char *b);
void zig(BitTree *x);
void zag(BitTree *x);
void zigzag(BitTree *x);
void zagzig(BitTree *x);

/*�������ܣ��ж��������Ƿ���ͬ
  ���������Ƚϵ�����ֵ 
  ����ֵ��0������ͬ��1������ͬ 
*/ 
int IsSamePeople(info a,info b){
	if(strcmp(a.name,b.name)!=0) return 0;
	if(a.age!=b.age) return 0;
	if(a.gender!=b.gender) return 0; //���������ݾ���ͬʱ����Ϊ������ͬ 
	return 1; 
} 
/*�������ܣ�����һ����������
  ���������� root
  ����ֵ�����rootΪ�շ���-1��ֻ��һ���ڵ㷵��0������Ϊ�������߶�+1 
*/
int getHeight(BitTree root){
	if(root!=NULL) return root->height;
	return -1;
}
/*�������ܣ�����ߵ����ֵ
  ���������Ƚϵ�������
  ����ֵ������� 
*/
int Max(int a,int b){
	if(a>b) return a;
	return b;
}
/*�������ܣ��ж�a����b����
  ������ a,b�ַ���
  ����ֵ��a��b���򷵻�1�����򷵻�0 
*/

int namebigger(char *a,char *b){
	if(strcmp(a,b)>0) return 1; 
	else return 0;
} 
/*�������ܣ��ж�a����b��С 
  ������ a,b�ַ���
  ����ֵ��a��bС�򷵻�1�����򷵻�0 
*/
int namesmaller(char *a,char *b){
	if(strcmp(a,b)<0) return 1; 
	else return 0;
} 
void printNode(info data){
	if(data.age==-1){
		printf("�޴��ˣ�����\n");
		return ;
	}
	printf("%s ",data.name);
	if(data.gender==1) printf("woman ");
	else printf("man ");
	printf("age:%d\n",data.age);
}
/*�������ܣ��Ե����ڵ�����
  �������ڵ� 
  ����ֵ���� 
*/
void zig(BitTree *x){
	BitTree y=(*x)->lson;
	(*x)->lson=y->rson;
	y->rson=(*x);
	(*x)->height=Max(getHeight((*x)->lson),getHeight((*x)->rson))+1;
	y->height=Max(getHeight((*x)),getHeight(y->lson))+1; 
	(*x)=y;
} 
/*�������ܣ��Ե����ڵ�����
  �������ڵ� 
  ����ֵ���� 
*/
void zag(BitTree *x){
	BitTree y=(*x)->rson;
	(*x)->rson=y->lson;
	y->lson=(*x);
	(*x)->height=Max(getHeight((*x)->lson),getHeight((*x)->rson))+1;
	y->height=Max(getHeight((*x)),getHeight(y->rson))+1; 
	(*x)=y;
}
/* �������ܣ��Ե����ڵ��µ������������������
   �������ڵ�
   ����ֵ���� 
*/ 
void zigzag(BitTree *x){
	zig(&((*x)->rson));
	zag(x);
} 
/* �������ܣ��Ե����ڵ��µ������������������
   �������ڵ�
   ����ֵ���µĸ��ڵ� 
*/
void zagzig(BitTree *x){
	zag(&((*x)->lson));
	zig(x);
}
/*�������ܣ������в��ҽڵ�x
  ����������root,�ڵ����ƣ�x
  ����ֵ����
  ���Ӷȣ�O(logn) 
*/ 
info SearchAVL(BitTree root,char* x){
	if(root==NULL){
		info* temp= (info*)malloc(sizeof(info));
		temp->age=-1;
		return *temp;
	} 
	if(namebigger(root->data.name,x)){
		return SearchAVL(root->lson,x);
	}
	else if(namesmaller(root->data.name,x)){
		return SearchAVL(root->rson,x);
	}
	else return root->data;
}
/*�������ܣ��������һ��Ԫ�� 
  ������ ������Ԫ�� 
  ����ֵ�� 1������ӳɹ���0����ʧ�ܣ��Ѵ��ڣ� 
  ���Ӷȣ�O(logn) 
*/
int InsertAVL(BitTree *root,info x){
	int temp=0;
	if((*root)==NULL){//����ڵ�Ϊ��,���ڴ˽ڵ㴦����x��Ϣ
        (*root)=(BitTree )malloc(sizeof(BitNode));
        (*root)->data=x;
        (*root)->height=0;
        (*root)->lson=NULL;(*root)->rson=NULL;
        return 1;
    }

    if(namebigger((*root)->data.name,x.name)){//���xС�ڽڵ��ֵ,�ͼ����ڽڵ���������в���x
        if(InsertAVL(&((*root)->lson),x)) temp=1;
        if(2==getHeight((*root)->lson)-getHeight((*root)->rson)){
            if(namebigger((*root)->lson->data.name,x.name))
                zig(root);
            else
                zagzig(root);
		}
		(*root)->height=Max(getHeight((*root)->lson),getHeight((*root)->rson))+1;
    	if(temp) return 1;
    	else return 0;
    }
    else if(namesmaller((*root)->data.name,x.name)){//���x���ڽڵ��ֵ,�ͼ����ڽڵ���������в���x
        if(InsertAVL(&((*root)->rson),x)) temp=1;
         //����߶�֮��Ϊ2�Ļ���ʧȥ��ƽ��,��Ҫ��ת
        if(2==getHeight((*root)->rson)-getHeight((*root)->lson)) {
            if(namesmaller((*root)->rson->data.name,x.name))
                zag(root);
            else
                zigzag(root);
		}
		(*root)->height=Max(getHeight((*root)->lson),getHeight((*root)->rson))+1;
    	if(temp) return 1;
    	else return 0;
    }
    else 
    	return 0;	
}
/*�������ܣ�ǰ������������� 
  ���������� 
  ����ֵ�� ��
  ���Ӷȣ�O(n) 
*/
void TraverseAVL(BitTree root){
	if(root==NULL) return;
	printNode(root->data);//������ڵ�
	TraverseAVL(root->lson); //���������� 
	TraverseAVL(root->rson);//�ٱ��������� 
} 
/*�������ܣ���ʼ��һ�������� 
  ������ָ�������������ָ���ַ 
  ����ֵ���� 
*/
void InitAVL(BitTree * root){
	(*root)=NULL;
	//(*root)->height=-1;
	//(*root)->lson=NULL;(*root)->rson=NULL;
}
/*�������ܣ�ɾ����������һ���ڵ� 
  ����������root���ڵ�x 
  ����ֵ�� δ�ҵ�����-1��ɾ���ɹ�����0
  ���Ӷȣ�O(logn) 
*/ 
int DeleteAVL(BitTree *root,char* x){
	if((*root)==NULL) 	return -1;//δ�ҵ��˽ڵ� 
	if(namebigger((*root)->data.name,x)){//����������ɾ���ڵ�x 
		DeleteAVL(&((*root)->lson),x);
		if(2==getHeight((*root)->rson)-getHeight((*root)->lson)){
			if((*root)->rson->lson!=NULL&&getHeight((*root)->rson->lson)>getHeight((*root)->rson->rson))
				zigzag(root);
			else zag(root);	
		}
	}
	else if(namesmaller((*root)->data.name,x)){//����������ɾ���ڵ�x 
		DeleteAVL(&((*root)->rson),x);
		if(2==getHeight((*root)->lson)-getHeight((*root)->rson)){
			if((*root)->lson->rson!=NULL&&getHeight((*root)->lson->rson)>getHeight((*root)->lson->lson))
				zagzig(root);
			else zig(root);	
		}
	}
	else{//�ҵ��ڵ�x 
		if((*root)->lson!=NULL&&(*root)->rson!=NULL){
			BitTree temp=(*root)->rson; 
			while(temp->lson!=NULL) temp=temp->lson;
			(*root)->data=temp->data;
			
			DeleteAVL(&((*root)->rson),temp->data.name);
			if(2==getHeight((*root)->lson)-getHeight((*root)->rson)){
				if((*root)->lson->rson!=NULL&&getHeight((*root)->lson->rson)>getHeight((*root)->lson->lson))
					zagzig(root);
				else 
					zig(root);	
			}
		} 
		else{
			BitTree temp=*root;
			if((*root)->lson==NULL)//���Ҷ��ӻ�û�ж��� 
				(*root)=(*root)->rson;
			else if((*root)->rson=NULL)//������� 
				(*root)=(*root)->lson;
			free(temp);		
		}
	} 
	if((*root)==NULL) return 1;
	(*root)->height=Max(getHeight((*root)->lson),getHeight((*root)->rson))+1;
	return 1;
} 
/*�������ܣ��Զ������ڵ�ݹ�ɾ�� 
  ���������ڵ� 
  ����ֵ���� 
*/
void DestroyNode(BitTree *root){
	if(*root==NULL) return ;
	if((*root)->lson!=NULL) DestroyNode(&(*root)->lson);
	if((*root)->rson!=NULL) DestroyNode(&(*root)->rson);
	free(*root);
}
/*�������ܣ����ٶ����� 
  ������ָ�������������ָ���ַ 
  ����ֵ���� 
*/ 
void DestroyAVL(BitTree *root){
	DestroyNode(root);
	*root=NULL; 
} 
 
typedef struct{
	BitTree avlTree;
	int number;
}Set,*set;
set setList[10];
void set_init(set* group);// ��ʼ������ 
void set_destroy(set * group); //���ټ��� 
int set_insert(set * group,info data); //����Ԫ�� 
int set_remove(set* group,info data); //ɾ��Ԫ�� 
set set_intersection(set groupA ,set  groupB); //���ϵĽ� 
set set_union(set groupA ,set  groupB); //���ϵĲ� 
set set_diffrence(set groupA ,set  groupB); //���ϵĲ� 
int set_size(set group); //���ϴ�С 
int set_member(set group ,info data); //�ж�һ��Ԫ���Ƿ�Ϊ���ϳ�Ա 
int set_subset(set groupA ,set  groupB); //�ж�һ�������Ƿ�Ϊ��һ�����ϵ��Ӽ� 
int set_equal(set groupA ,set  groupB); //�ж����������Ƿ���� 
void treemerge(BitTree a,BitTree b,set * p);//���������Ľ��������µļ����� 
void treeadd(BitTree a,set * p);//��һ���������µļ����� 
void set_minus(set groupA ,set  groupB,set*p);//��A�г�ȥB�е�Ԫ�� ���ŵ�p�� 
int tree_subset(BitTree A,set p);//�ж���A��Ԫ���Ƿ���p�� 
void set_Traverse(set group);//����������� 
/*�������ܣ� ��ʼ������
  ������ ����ָ�� 
  ����ֵ���� 
*/
void set_init(set* group){
	(*group)= (set) malloc(sizeof(Set));
	(*group)->avlTree=NULL;
	
	InitAVL(&((*group)->avlTree));
	(*group)->number=0;
}
/*�������ܣ� ���ټ���
  ������ ����ָ�� 
  ����ֵ�� �� 
*/ 
void set_destroy(set * group){
	DestroyAVL(&((*group)->avlTree));
	free(*group);
	*group=NULL;
} 
/*�������ܣ� ����Ԫ��
  ������ ����ָ�� ��Ԫ������ 
  ����ֵ��-1�����Ѿ����ڣ�1�������ɹ� 0����Ƿ����� 
  ���Ӷȣ�O(logn) 
*/ 
int set_insert(set * group,info data){
	if((*group)==NULL) return 0;
	if(InsertAVL(&((*group)->avlTree),data)==1) {
		(*group)->number++;
		return 1;
	}
	else
		return -1; 
} 
/*�������ܣ� ɾ��Ԫ�� 
  ������ ����ָ�� ����Ԫ�� 
  ����ֵ��-1����Ԫ�ز����ڣ�1����ɾ���ɹ� 0����Ƿ����� 
*/ 
int set_remove(set* group,info data){
	if((*group)==NULL) return 0;
	if(DeleteAVL(&((*group)->avlTree),data.name)) {
		(*group)->number--;
		return 1;
	}
	else return -1;

} 
/*�������ܣ����������Ľ��� 
  ������ ��a��b ����p 
  ����ֵ���� 
*/
void treemerge(BitTree a,BitTree b,set * p){
	if(a==NULL) return ;
	info temp;
	temp=SearchAVL(b,a->data.name);
	if((temp.age!=-1)) set_insert(p,temp);
	treemerge(a->lson,b,p);
	treemerge(a->rson,b,p);
} 
/*�������ܣ� ��һ������Ԫ�ؼ��뵽������ 
  ������ ��a������p 
  ����ֵ���� 
*/
void treeadd(BitTree a,set * p){
	if(a==NULL) return ; 
	set_insert(p,a->data);
	treeadd(a->lson,p);
	treeadd(a->rson,p);
} 
/*�������ܣ� ���������ϵĽ��� 
  ������ ����A��B 
  ����ֵ������ �Ƿ��������ؿ�
  ���Ӷȣ�O(n) 
*/ 
set set_intersection(set groupA ,set  groupB){
	set temp; set_init(&temp); 
	if(groupA==NULL||groupB==NULL){
		set_destroy(&temp);
		return temp;
	}
	BitTree treeA =groupA->avlTree;
	BitTree treeB = groupB->avlTree;
	treemerge(treeA,treeB,&temp);
	return temp; 
} 
/*�������ܣ� �������ϵĲ� 
  ������ ����A��B 
  ����ֵ������ �Ƿ��������ؿ�
*/ 
set set_union(set groupA ,set  groupB){
	set temp; set_init(&temp); 
	if(groupA==NULL||groupB==NULL){
		set_destroy(&temp);
		return temp;
	}
	BitTree treeA =groupA->avlTree;
	BitTree treeB = groupB->avlTree;
	treeadd(treeA,&temp);
	treeadd(treeB,&temp);
	return temp;
} 
/*�������ܣ� ���������в�һ����Ԫ�طŵ��¼����� 
  ������ ��A,B ����P 
  ����ֵ���� 
*/ 
void set_minus(BitTree A ,BitTree  B,set* p){
	if(A==NULL) return;
	info temp;temp=SearchAVL(B,A->data.name);
	if(temp.age==-1) set_insert(p,A->data);
	set_minus(A->lson,B,p);
	set_minus(A->rson,B,p);
}
/*�������ܣ� �������ϵĲ� 
  ������ ����A,B 
  ����ֵ��� �Ƿ��������ؿ� 
  ���Ӷȣ�O(n) 
*/ 
set set_diffrence(set groupA ,set  groupB){
	
	set crossgroup=set_intersection(groupA,groupB);
	set temp; set_init(&temp);
	if(groupA==NULL||crossgroup==NULL){
		set_destroy(&temp);
		return temp;
	} 
	BitTree treeA =groupA->avlTree;
	BitTree treeB = crossgroup->avlTree;
	set_minus(treeA,treeB,&temp);
	return temp;
} 
/*�������ܣ� ���ؼ��ϵĴ�С 
  ������ ���� 
  ����ֵ�����ϴ�С ,�Ƿ�����Ϊ-1; 
*/ 
int set_size(set group){
	if(group==NULL) return -1;
	return group->number; 
} 
/*�������ܣ� �ж�Ԫ���Ƿ�Ϊ���ϳ�Ա 
  ������ ����group Ԫ��data 
  ����ֵ����Ϊ1����Ϊ0���Ƿ�����Ϊ-1 
*/ 
int set_member(set group ,info data){
	if (group==NULL) return -1; 
	if(SearchAVL(group->avlTree,data.name).age!=-1) return 1;
	else return 0;
}
/*�������ܣ� �жϼ���A�Ƿ���B���Ӽ� 
  ������ ����A,����B 
  ����ֵ������Ϊ1������Ϊ0; 
*/ 
int tree_subset(BitTree A,set p){
	if(A==NULL) return 1;
	if(SearchAVL(p->avlTree,A->data.name).age==-1) return 0;
	else{
		return tree_subset(A->lson,p)&tree_subset(A->rson,p);
	} 
}
/*�������ܣ� �жϼ���A�Ƿ���B���Ӽ� 
  ������ ����A,����B 
  ����ֵ������Ϊ1������Ϊ0���Ƿ�����Ϊ-1; 
  ���Ӷȣ�O(n) 
*/ 
int set_subset(set groupA ,set  groupB){
	if(groupA==NULL||groupB==NULL) return -1;
	if(tree_subset(groupA->avlTree,groupB)) return 1;
	else return 0;
}
/*�������ܣ� �ж����������Ƿ���� 
  ������ ����A��B 
  ����ֵ�����Ϊ1������Ϊ0���Ƿ�����Ϊ-1 
*/ 
int set_equal(set groupA ,set  groupB){
	if(groupA==NULL||groupB==NULL) return -1;
	if(set_subset(groupA,groupB)==1&&groupA->number==groupB->number) return 1;
	else return 0; 
} 
/*�������ܣ� �������һ������ 
  ������ ����group 
  ����ֵ���� 
*/ 
void set_Traverse(set group){
	printf("����%d��\n",group->number);
	TraverseAVL(group->avlTree);
	//printf("******���*******\n");
}
typedef struct{   //����Ӧ�ò�ṹ���� 
	info Myinfo;
	set Myfriends;
	set Myfans;
	set Myidols;
	//string hobby[5];
}Person,*person;
void init_person(person * ren);//��ʼ��һ����
void destroy_person(person *ren);//ɾ��һ����
int add_friends(person *a,person *b);//a,b�������Ϊ����
int remove_friends(person *a,person *b);//a,b����������
int search_friends(person *a,person *b);//��ѯa��b�Ƿ��Ǻ��� 
int add_fans(person *a,person *b);//a��Ϊb�ķ�˿
int remove_fans(person *a,person *b);//a���b�ķ�˿
int search_fans(person *a,person *b);//��ѯa�ǲ���b�ķ�˿ 
int add_idols(person *a,person *b);//a��Ϊb�Ĺ�ע
int remove_idols(person *a ,person *b);//a�����b�Ĺ�ע 
int search_idols(person *a,person *b);//��ѯa�ǲ���b�Ĺ�ע 
set common_idols(person *a,person *b);//��a��b�Ĺ�ͬ��ע
set common_fans(person *a,person *b);//��a��b�Ĺ�ͬ��˿
set two_degree_friends(person *a);//��a�Ķ��Ⱥ���
void printPerson(person a);//��ӡ���һ���˵���Ϣ 
/*�������ܣ�  ��ʼ��һ���� 
  ������  �ṹָ�� a 
  ����ֵ�� �� 
*/
void init_person(person *a){
	if((*a)!=NULL) destroy_person(a);
	(*a)= (person)malloc(sizeof(Person));
	set_init(&((*a)->Myfriends));
	set_init(&((*a)->Myfans)); 
	set_init(&((*a)->Myidols));  
} 
/*�������ܣ�  ����һ���� 
  ������  �ṹָ�� a 
  ����ֵ�� �� 
*/
void destroy_person(person *ren){
	if((*ren)==NULL)  return ;
	set_destroy(&((*ren)->Myfriends));
	set_destroy(&((*ren)->Myfans));
	set_destroy(&((*ren)->Myidols));
	free(*ren); 
}
/*�������ܣ�  ������˻�Ϊ���ѹ�ϵ 
  ������  ������a��b 
  ����ֵ�� ��ӳɹ�Ϊ1���Ƿ�Ϊ-1 
*/
int add_friends(person *a,person *b){
	if((*a)==NULL||(*b)==NULL) return -1; 
	if(set_insert(&((*a)->Myfriends),(*b)->Myinfo)==1&&set_insert(&((*b)->Myfriends),(*a)->Myinfo)==1) return 1;
	else return 0;
}
/*�������ܣ�  ������˵ĺ��ѹ�ϵ 
  ������  ������a,b 
  ����ֵ�� ����ɹ�Ϊ1�����ʧ��Ϊ0���Ƿ�����Ϊ-1 
*/
int remove_friends(person *a,person *b){
	if((*a)==NULL||(*b)==NULL) return -1;
	if(search_friends(a,b)!=1) return 0;
	if(set_remove(&((*a)->Myfriends),(*b)->Myinfo)==1&&set_remove(&((*b)->Myfriends),(*a)->Myinfo)==1) return 1;
	else return 0;  
} 
/*�������ܣ� ���������Ƿ�Ϊ���ѹ�ϵ 
  ������  ������a,b 
  ����ֵ�� ����Ϊ1����Ϊ0���Ƿ�Ϊ-1 
*/
int search_friends(person *a,person *b){
	if((*a)==NULL||(*b)==NULL) return -1;
	if(set_member((*a)->Myfriends,(*b)->Myinfo)==1) return 1;
	else return 0; 
}
/*�������ܣ�  ���aΪb�ķ�˿ 
  ������  ������a,b 
  ����ֵ�� ��ӳɹ�Ϊ1��ʧ��Ϊ0���Ƿ�Ϊ-1 
*/
int add_fans(person *a,person *b){
	if((*a)==NULL||(*b)==NULL) return -1;
	if(set_insert(&((*b)->Myfans),(*a)->Myinfo)==1&&set_insert(&((*a)->Myidols),(*b)->Myinfo)==1) return 1;
	else return 0;
}
/*�������ܣ�  ���a��b�ķ�˿ 
  ������  ������a,b 
  ����ֵ�� ����ɹ�Ϊ1��ʧ��Ϊ0���Ƿ�Ϊ-1 
*/
int remove_fans(person *a,person *b){
	if((*a)==NULL||(*b)==NULL) return -1;
	if(search_fans(a,b)!=1) return 0; 
	if(set_remove(&((*b)->Myfans),(*a)->Myinfo)==1&&set_remove(&((*a)->Myidols),(*b)->Myinfo)==1) return 1;
	else return 0;
}
/*�������ܣ� ��ѯa�ǲ���b�ķ�˿ 
  ������  ������a,b 
  ����ֵ�� ���򷵻أ����򷵻�0���Ƿ�Ϊ-1 
*/
int search_fans(person *a,person *b){
	if((*a)==NULL||(*b)==NULL) return -1;
	if(set_member((*b)->Myfans,(*a)->Myinfo)==1) return 1;
	else return 0;  
}
/*�������ܣ�  ���aΪb�Ĺ�ע 
  ������  ������a,b 
  ����ֵ�� ��ӳɹ�Ϊ1��ʧ��Ϊ0���Ƿ�Ϊ-1 
*/
int add_idols(person *a,person *b){
	if((*a)==NULL||(*b)==NULL) return -1;
	if(set_insert(&((*b)->Myidols),(*a)->Myinfo)==1&&set_insert(&((*a)->Myfans),(*b)->Myinfo)==1) return 1;
	else return 0;
}
/*�������ܣ�  ���a��b�Ĺ�ע 
  ������  ������a,b 
  ����ֵ�� ����ɹ�Ϊ1��ʧ��Ϊ0���Ƿ�Ϊ-1 
  */ 
int remove_idols(person *a ,person *b){
	if((*a)==NULL||(*b)==NULL) return -1;
	if(search_idols(a,b)!=1) return 0; 
	if(set_remove(&((*b)->Myidols),(*a)->Myinfo)==1&&set_remove(&((*a)->Myfans),(*b)->Myinfo)==1) return 1;
	else return 0;
}
/*�������ܣ� ��ѯa�ǲ���b�Ĺ�ע 
  ������  ������a,b 
  ����ֵ�� ���򷵻أ����򷵻�0���Ƿ�Ϊ-1 
*/ 

int search_idols(person *a,person *b){
	if((*a)==NULL||(*b)==NULL) return -1;
	if(set_member((*b)->Myidols,(*a)->Myinfo)==1) return 1;
	else return 0;  
}
/*�������ܣ�  �������˵Ĺ�ͬ��ע 
  ������  ������a,b 
  ����ֵ�� ��ͬ��ע�ļ��� 
*/
set common_idols(person *a,person *b){
	return set_intersection((*a)->Myidols,(*b)->Myidols); 
}
/*�������ܣ�  �������˵Ĺ�ͬ��˿ 
  ������  ������a,b 
  ����ֵ�� ��ͬ��˿�ļ��� 
*/
set common_fans(person *a,person *b){
	return set_intersection((*a)->Myfans,(*b)->Myfans); 
}


person personList[505];

/*�������ܣ�  ��һ���˵Ķ��Ⱥ��� 
  ������  һ����a 
  ����ֵ�� a�����ж��Ⱥ��ѹ��ɵļ��� 
*/
set two_degree_friends(person *a){
	set temp; set_init(&temp);
	set one_degree_friendss=(*a)->Myfriends;
	for(int i=0;i<505;i++){
		if(personList[i]==NULL) 
			continue;
		if(search_friends(&personList[i],a)==1) {
			temp=set_union(temp,personList[i]->Myfriends);
		}
	}
	set_remove(&temp,(*a)->Myinfo);
	return temp;
} 
/*�������ܣ�  ���һ���� 
  ������  һ����a 
  ����ֵ�� void 
*/
void printPerson(person a){
	if(a==NULL) return ;
	printf("�����ǣ�%s �Ա��ǣ�",a->Myinfo.name);
	if(a->Myinfo.gender==0) printf("�� ");
	else printf("Ů ");
	printf("�����ǣ�%d\n",a->Myinfo.age);
	if(a->Myfriends->number>0){
		printf("Ta�ĺ��Ѱ�����\n");
		 set_Traverse(a->Myfriends); 
	}
	else printf("Taû�к���\n"); 
	if(a->Myfans->number>0){
		printf("Ta�ķ�˿������\n");
		 set_Traverse(a->Myfans); 
	}
	else printf("Taû�з�˿\n");
	if(a->Myidols->number>0){
		printf("Ta�Ĺ�ע������\n");
		 set_Traverse(a->Myidols); 
	}
	else printf("Taû�й�ע\n");  
	printf("******���*******\n");
}	
int op=1;
/*�������ܣ�  ��ӡ���г�Ա��Ϣ 
  ������  void 
  ����ֵ�� ���г�Ա���� 
*/
int print_now_person(){
	int ans=0; 
	for(int i=0;i<505;i++){
		if(personList[i]==NULL) continue;
		ans=i+1;
		printf("��%dλ�û�Ϊ : %s\n",ans,personList[i]->Myinfo.name);
	} 
	if(ans==0){
		printf("��ǰ�����û�����\n");
	}
	return ans;
}
/*�������ܣ�  ���һλ�û� 
  ������  void 
  ����ֵ�� void 
*/
void Insert_A_Person(){
	printf("�����û��������£�\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	info temp;
	printf("�������û�������ע�ⲻҪ������û������ظ���\n");
	scanf("%s",temp.name);
	printf("�������û��Ա�0�����У�1����Ů��\n");
	scanf("%d",&temp.gender);
	printf("�������û����䣬0~99֮�䣺\n");
	scanf("%d",&temp.age);
	for(int i=0;i<505;i++){
		if(personList[i]==NULL) continue;
		if(strcmp(personList[i]->Myinfo.name,temp.name)==0){
			printf("�����Ѵ��ڣ������²���\n");
			return ; 
		}
	}
	if(temp.gender!=0&&temp.gender!=1){
		printf("�Ա�������������²���\n");
		return ;
	}
	if(temp.age<0||temp.age>99){
		printf("����������������²���\n");
		return ;
	}
	init_person(&personList[now]);
	personList[now]->Myinfo=temp;
	printf("��ӳɹ�!\n"); 
}
/*�������ܣ�  ɾ��һλ�û� 
  ������  void 
  ����ֵ�� void 
*/
void Delete_A_Person(){
	printf("�����û��������£�\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	int del;
	printf("������Ҫɾ�����û���ţ�����1--%d֮�䣩\n",now);
	scanf("%d",&del);
	if(del<1||del>now){
		printf("����������������²���\n");
		return ;
	} 
	for(int i=0;i<now;i++){
		if(i+1==del) continue;
		if(search_fans(&personList[del-1],&personList[i])==1) remove_fans(&personList[del-1],&personList[i]);
		if(search_friends(&personList[del-1],&personList[i])==1) remove_friends(&personList[del-1],&personList[i]);
		if(search_idols(&personList[del-1],&personList[i])==1) remove_idols(&personList[del-1],&personList[i]);
	}printf("******\n");
	destroy_person(&personList[del-1]);
	for(int i=del;i<now;i++) 
		personList[i-1]=personList[i];
	personList[now-1]=NULL;	
	printf("ɾ���ɹ���\n");
}
/*�������ܣ�  ���������˵ĺ��ѹ�ϵ 
  ������  void 
  ����ֵ�� void 
*/
void Make_Friends(){
	printf("�����û��������£�\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	int per1,per2;
	printf("��������λ�û��ı�ţ�\n�û�1��\n");
	scanf("%d",&per1);
	printf("�û�2��\n");
	scanf("%d",&per2);
	if(per1<1||per1>now||per2<1||per2>now){
		printf("����������������²���\n");
		return ;
	} 
	if(search_friends(&personList[per1-1],&personList[per2-1])==1){
		printf("����λ�Ѿ��Ǻ����ˣ���\n");
		return ;
	}
	else{
		if(add_friends(&personList[per1-1],&personList[per2-1])==1) printf("�����ɹ�����\n");
		else printf("����ʧ�ܣ���\n");
		return ;
	}
}
/*�������ܣ�  ɾ�������˵ĺ��ѹ�ϵ 
  ������  void 
  ����ֵ�� void 
*/
void Remove_Friends(){
	printf("�����û��������£�\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	int per1,per2;
	printf("��������λ�û��ı�ţ�\n�û�1��\n");
	scanf("%d",&per1);
	printf("�û�2��\n");
	scanf("%d",&per2);
	if(per1<1||per1>now||per2<1||per2>now){
		printf("����������������²���\n");
		return ;
	} 
	if(search_friends(&personList[per1-1],&personList[per2-1])!=1){
		printf("����λ�����Ǻ��ѣ���\n");
		return ;
	}
	else{
		if(remove_friends(&personList[per1-1],&personList[per2-1])==1) printf("�����ɹ�����\n");
		else printf("����ʧ�ܣ���\n");
		return ;
	}
} 
/*�������ܣ�  ��ѯ�������ǲ��Ǻ��� 
  ������  void 
  ����ֵ�� void 
*/
void Search_Friends(){
	printf("�����û��������£�\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	int per1,per2;
	printf("��������λ�û��ı�ţ�\n�û�1��\n");
	scanf("%d",&per1);
	printf("�û�2��\n");
	scanf("%d",&per2);
	if(per1<1||per1>now||per2<1||per2>now){
		printf("����������������²���\n");
		return ;
	} 
	if(search_friends(&personList[per1-1],&personList[per2-1])!=1){
		printf("����λ�����Ǻ��ѣ���\n");
		return ;
	}
	else{
		printf("����λȷʵ�Ǻ��ѣ���\n");
		return ;
	} 
}
/*�������ܣ�  ���һ����Ϊ��һ���ķ�˿ 
  ������  void 
  ����ֵ�� void 
*/
void Add_A_Fans(){
	printf("�����û��������£�\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	int per1,per2;
	printf("��������λ�û��ı�ţ�\n�û�1������˿��\n");
	scanf("%d",&per1);
	printf("�û�2����ż��\n");
	scanf("%d",&per2);
	if(per1<1||per1>now||per2<1||per2>now){
		printf("����������������²���\n");
		return ;
	} 
	if(search_fans(&personList[per1-1],&personList[per2-1])==1){
		printf("Ta�Ѿ���Ta�ķ�˿�ˣ���\n");
		return ;
	}
	else{
		if(add_fans(&personList[per1-1],&personList[per2-1])==1) printf("�����ɹ�����\n");
		else printf("����ʧ�ܣ���\n");
		return ;
	}
}
/*�������ܣ�  ���һ����Ϊ��һ���ķ�˿ 
  ������  void 
  ����ֵ�� void 
*/
void Remove_Fans(){
	printf("�����û��������£�\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	int per1,per2;
	printf("��������λ�û��ı�ţ�\n�û�1������˿��\n");
	scanf("%d",&per1);
	printf("�û�2����ż��\n");
	scanf("%d",&per2);
	if(per1<1||per1>now||per2<1||per2>now){
		printf("����������������²���\n");
		return ;
	} 
	if(search_fans(&personList[per1-1],&personList[per2-1])!=1){
		printf("Ta������Ta�ķ�˿����\n");
		return ;
	}
	else{
		if(remove_fans(&personList[per1-1],&personList[per2-1])==1) printf("�����ɹ�����\n");
		else printf("����ʧ�ܣ���\n");
		return ;
	}
} 
/*�������ܣ�  ��ѯһ�����ǲ�����һ���ķ�˿ 
  ������  void 
  ����ֵ�� void 
*/
void Search_Fans(){
	printf("�����û��������£�\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	int per1,per2;
	printf("��������λ�û��ı�ţ�\n�û�1������˿��\n");
	scanf("%d",&per1);
	printf("�û�2����ż��\n");
	scanf("%d",&per2);
	if(per1<1||per1>now||per2<1||per2>now){
		printf("����������������²���\n");
		return ;
	} 
	if(search_fans(&personList[per1-1],&personList[per2-1])!=1){
		printf("Ta������Ta�ķ�˿����\n");
		return ;
	}
	else{
		printf("Taȷʵ��Ta�ķ�˿����\n");
		return ;
	} 
}
/*�������ܣ�  ��ѯ�����˵Ĺ�ͬ��˿ 
  ������  void 
  ����ֵ�� void 
*/
void Commom_Fans(){
	printf("�����û��������£�\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	int per1,per2;
	printf("��������λ�û��ı�ţ�\n�û�1��\n");
	scanf("%d",&per1);
	printf("�û�2��\n");
	scanf("%d",&per2);
	if(per1<1||per1>now||per2<1||per2>now){
		printf("����������������²���\n");
		return ;
	} 
	printf("���ǵĹ�ͬ��˿�������£�\n");
	set_Traverse(common_fans(&personList[per1-1],&personList[per2-1]));
	return ;
}
/*�������ܣ�  ��ѯ�����˵Ĺ�ͬ��ע 
  ������  void 
  ����ֵ�� void 
*/
void Commom_Idols(){
	printf("�����û��������£�\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	int per1,per2;
	printf("��������λ�û��ı�ţ�\n�û�1��\n");
	scanf("%d",&per1);
	printf("�û�2��\n");
	scanf("%d",&per2);
	if(per1<1||per1>now||per2<1||per2>now){
		printf("����������������²���\n");
		return ;
	} 
	printf("���ǵĹ�ͬ��ע�������£�\n");
	set_Traverse(common_idols(&personList[per1-1],&personList[per2-1]));
	return ;
}
/*�������ܣ�  ��ѯ��һ���˵Ķ��Ⱥ��� 
  ������  void 
  ����ֵ�� void 
*/
void TwoDFriends(){
	printf("�����û��������£�\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	int per1;
	printf("������Ҫ��ѯ���û��ı�ţ�\n");
	scanf("%d",&per1);
	if(per1<1||per1>now){
		printf("����������������²���\n");
		return ;
	} 
	printf("��Ta�Ķ��Ⱥ��Ѱ������£�\n");
	set_Traverse(two_degree_friends(&personList[per1-1]));
	return ;
}
/*�������ܣ� ��ѯ�û��Ƿ������ϲ�� 
  ������  �û���ţ�ϲ�� 
  ����ֵ�� 1���У�0��û�� 
*/
/*HaveThisHobby(int per1,string temp){
	for(int i=0;i<5;i++){
		if(personList[per1]->hobby[i]==temp) return 1;
	} 
	return 0;
}
/*�������ܣ� Ϊһ���û�����ϲ�� 
  ������  void 
  ����ֵ�� void 
*/
/*void AddHobby(){
	printf("�����û��������£�\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	int per1;
	printf("��������λ�û��ı��\n");
	scanf("%d",&per1);
	int t=-1;
	for(int i=0;i<5;i++){
		cout<<personList[per1]->hobby[i].size()<<endl;
		cout<<personList[per1]->hobby[i]<<endl;
		if(personList[per1]->hobby[i]!="") t=i; 
	}
		
	if(t==4){
		printf("�����Ѿ�����̫��İ��ã�\n");
		return;
	}
	cout<<"endad"<<endl;
	printf("����������ϲ���ǣ�\n");
	for(int i=t+1;i<5;i++){
		string temp;
		cin>>temp;
		if(HaveThisHobby(per1,temp)) {
			printf("���Ѿ�����������ã�\n");
			i--;continue;
		}
		if(i==4){
			printf("�����Ѿ�����̫��İ��ã�\n");
			return;
		}
		if(temp=="") break ;
		personList[per1]->hobby[i]=temp;
	}
	printf("���ӳɹ���\n");
}
/*�������ܣ� Ϊһ���û�ɾ��ϲ�� 
  ������  void 
  ����ֵ�� void 
*/
/*void RemoveHobby(){
	printf("�����û��������£�\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	int per1;
	printf("��������λ�û��ı��\n");
	scanf("%d",&per1);
	int t=-1;
	for(int i=0;i<5;i++)
		if(personList[per1]->hobby[i]!="") t=i; 
	if(t==-1){
		printf("���˻�û�а��ã�\n");
		return;
	}
	printf("���İ������£�\n");
	for(int i=0;i<=t;i++)
		cout<<personList[per1]->hobby[i]<<endl;
	printf("��������Ҫɾ���İ��ã�\n");
	string temp;
	cin>>temp;
	if(HaveThisHobby(per1,temp)==0){
		printf("��������\n");
		return ; 
	} 
	for(int i=0;i<=t;i++)
		if(personList[per1]->hobby[i]==temp)  personList[per1]->hobby[i]="";
	for(int i=1;i<=t;i++){
		if(personList[per1]->hobby[i-1]==""){
			personList[per1]->hobby[i-1]=personList[per1]->hobby[i];
			personList[per1]->hobby[i]="";
		}
	}
	printf("ɾ���ɹ���\n");
}




/*�������ܣ�  ������д�뵽�ļ��� 
  ������  void 
  ����ֵ�� void 
*/
void SaveToFile(){
	FILE* fp ;
	info temp;
	temp.age=-1; 
	if ((fp=fopen("data.txt","w"))==NULL){
		printf("File open error\n ");
		return ;
	} 
	int ans=0; 
	for(int i=0;i<505;i++){
		if(personList[i]==NULL) continue;
		ans=i+1;
		//cout<<ans<<endl; 
		if(fwrite(&(personList[i]->Myinfo),sizeof(info),1,fp)==1){ 
			fprintf(fp,"\n"); 
			cout<<personList[i]->Myinfo.name<<" "<<personList[i]->Myinfo.age<<" "<<personList[i]->Myinfo.gender<<endl;
		} 
	} 
	cout<<ans<<endl;
	int zero=0;
	fwrite((&temp),sizeof(info),1,fp);
	for(int i=1;i<=ans;i++)
		for(int j=1;j<=ans;j++){
			if(search_friends(&personList[i-1],&personList[j-1])==1) {
				fwrite(&i,sizeof(int),1,fp);
				fwrite(&j,sizeof(int),1,fp);	
			}
		}
	fwrite(&zero,sizeof(int),1,fp);
	for(int i=1;i<=ans;i++)
		for(int j=1;j<=ans;j++){
			if(search_fans(&personList[i-1],&personList[j-1])==1) {
				fwrite(&i,sizeof(int),1,fp);
				fwrite(&j,sizeof(int),1,fp);	
			}
		}
	fwrite(&zero,sizeof(int),1,fp);
	fclose(fp);
	printf("�ѳɹ����棡����\n");	
}
/*�������ܣ�  ���ļ��ж�ȡ���� 
  ������  void 
  ����ֵ�� void 
*/
void LoadFromFile(){
	FILE* fp ; 
	if ((fp=fopen("data.txt","r"))==NULL){
		printf("File open error\n ");
		return ;
	} 
	int ans=0; 
	init_person(&personList[ans]);
	//cout<<"eeasd"<<endl;
	while(1){
		if(fread(&(personList[ans]->Myinfo),sizeof(info),1,fp)==0){
			cout<<personList[ans]->Myinfo.gender<<endl;
			break;
		}
		else fscanf(fp,"\n");
		if(personList[ans]->Myinfo.age==-1) {cout<<personList[ans]->Myinfo.age<<endl;
			destroy_person(&personList[ans]);
			personList[ans]=NULL;
			break;	
		}
		ans++;
		init_person(&personList[ans]);
		//cout<<ans<<endl;
	}
	int a,b;
	while(fread(&a,sizeof(int),1,fp)){
		if(a==0) break;
		fread(&b,sizeof(int),1,fp);
		add_friends(&personList[a-1],&personList[b-1]);
	}
	while(fread(&a,sizeof(int),1,fp)){
		if(a==0) break;
		fread(&b,sizeof(int),1,fp);
		add_fans(&personList[a-1],&personList[b-1]);
	}
	fclose(fp);
	printf("��ȡ�ɹ�������\n");
}
int random(int m){
	return rand()%m;
}
void randData(){
	char tempp[21]; 
	for(int i=0;i<=19;i++){
		int r=random(52);
		if(r<26) tempp[i]='A'+r; 
		else tempp[i]='a'+r-26;
	}
	tempp[20]='\0';
	printf("%s\n",tempp);
	int sex=random(2);
	int age=random(30)+10;
	
	int now=print_now_person();
	//printf("--------------------------------\n");
	info temp;
	//printf("�������û�������ע�ⲻҪ������û������ظ���\n");
	strcpy(temp.name,tempp);
	//printf("�������û��Ա�0�����У�1����Ů��\n");
	temp.gender=sex;
	//printf("�������û����䣬0~99֮�䣺\n");
	temp.age=age;
	for(int i=0;i<505;i++){
		if(personList[i]==NULL) continue;
		if(strcmp(personList[i]->Myinfo.name,temp.name)==0){
			printf("�����Ѵ��ڣ������²���\n");
			return ; 
		}
	}
	if(temp.gender!=0&&temp.gender!=1){
		printf("�Ա�������������²���\n");
		return ;
	}
	if(temp.age<0||temp.age>99){
		printf("����������������²���\n");
		return ;
	}
	init_person(&personList[now]);
	personList[now]->Myinfo=temp;
	printf("��ӳɹ�!\n"); 
}
int main(){
	while(op){
		system("cls");	printf("\n\n");
		printf("                   ΢����ע����˿�����Ѽ�����ϵͳ \n");
		printf("---------------------------------------------------------------------------------\n");
		printf("    	           1. InsertPerson������һ���û���       \n");
		printf("    	           2. DeletePerson��ɾ��һ���û���     \n");
		printf("    	           3. MakeFriend  �������û��������ѹ�ϵ��     \n");
		printf("    	           4. ReliveFriend�������û�������ѹ�ϵ��    \n");
		printf("    	           5. SearchFriend����ѯ�����û��Ƿ�Ϊ���ѹ�ϵ��    \n");
		printf("    	           6. Add_A_Fans  ��һ���û���Ϊ��һ���û��ķ�˿�� \n");
		printf("    	           7. Relive_AFans��һ���û�ȡ����Ϊ��һ���ķ�˿��  \n");
		printf("    	           8. SearchFans  ����ѯһ���û��Ƿ�����һ���ķ�˿��  \n");
		printf("    	           9. Common_Fans ����ѯ�����û��Ĺ�ͬ��˿��  \n");
		printf("    	           10. Commom_idols����ѯ�����û��Ĺ�ͬ��ע��  \n");
		printf("    	           11. Friend's_Friends����ѯһλ�û��Ķ��Ⱥ��ѣ�  \n");
		//printf("    	           12. AddHobby��Ϊһ���û����һ��ϲ�ã�  \n");
		//printf("    	           13. RemoveHobby��ɾ��һ���û���ϲ�ã�  \n");
		//printf("    	           14. CommonHobby���������û��Ĺ�ͬϲ�ã�  \n");
		printf("    	           0. Exit\n");
		printf("                   15.Save�������ݱ��浽�ļ���   16.Load�����ļ��ж�ȡ���ݣ�\n");
		printf("---------------------------------------------------------------------------------\n");
		printf("                  ��ѡ����Ĳ���[0~16]:");
		scanf("%d",&op);
	    switch(op){
		   case 1:
		   	
		   	
			 Insert_A_Person();
			 getchar();getchar();
			 break;
			 
			 
		   case 2:
		   	
		   	 Delete_A_Person();
			      
			 getchar();getchar();
			 break;
			 
			 
		   case 3: 
		   
		   	 Make_Friends();
			   
			 getchar();getchar();
			 break;
			 
			 
		   case 4: 
		   
		   
			 Remove_Friends();   
			 getchar();getchar();
			 break;
			 
			 
		   case 5:
		   	
		   	
			 Search_Friends();   
			 getchar();getchar();
			 break;
			 
			 
		   case 6:
		   	
		   	
			 Add_A_Fans();    
			 getchar();getchar();
			 break;
			 
			 
		   case 7:  
		   
		   
			 Remove_Fans(); 
			 getchar();getchar();
			 break;
			 
			 
		   case 8:
		   
		        
			 Search_Fans(); 
			 getchar();getchar();
			 break;
			 
			 
		   case 9:
		        
			 Commom_Fans(); 
			 getchar();getchar();
			 break;
			 
			 
		   case 10:
		   
		      
			 Commom_Idols();
			 getchar();getchar();
			 break;
			 
			 
		   case 11:
		   
		        
			 TwoDFriends(); 
			 getchar();getchar();
			 break;
			 
			case 12:
		   
		        
			 //AddHobby(); 
			 getchar();getchar();
			 break;
			 
			 case 13:
		   
		        
			 //RemoveHobby();
			 getchar();getchar();
			 break;
			 
			 case 14:
		   		srand(time(0));
		      for(int i=1;i<=300;i++){
		      	
		      	randData();
			  }
			  for(int i=1;i<=300;i++){
			  	for(int j=0;j<30;j++){
			  		int t=random(300)+1;
			  		add_friends(&personList[i-1],&personList[t-1]);
				  }
			  }
			  for(int i=1;i<=300;i++){
			  	for(int j=0;j<30;j++){
			  		int t=random(300)+1;
			  		add_fans(&personList[i-1],&personList[t-1]); 
				  }
			  }	  
			  
			 //CommonHobby();
			 getchar();getchar();
			 break;	 
		   
		   
		   case 15:
		   
		        
			 SaveToFile();
			 getchar();getchar();
			 break;
			 
		   case 16:
		   
		        
			 LoadFromFile();
			 getchar();getchar();
			 break;	 
			 
		   case 0:
		   	 printf("��лʹ�ñ�ϵͳ����\n");
	         break;
		}//end of switch
	} 
	return 0;
}
