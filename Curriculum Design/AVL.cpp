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
	int gender;   //0代表男，1代表女 
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

/*函数功能：判断两个人是否相同
  参数：待比较的两个值 
  返回值：0代表不相同，1代表相同 
*/ 
int IsSamePeople(info a,info b){
	if(strcmp(a.name,b.name)!=0) return 0;
	if(a.age!=b.age) return 0;
	if(a.gender!=b.gender) return 0; //当三个数据均相同时才认为两人相同 
	return 1; 
} 
/*函数功能：返回一棵树的树高
  参数：树根 root
  返回值：如果root为空返回-1，只有一个节点返回0，否则为其子树高度+1 
*/
int getHeight(BitTree root){
	if(root!=NULL) return root->height;
	return -1;
}
/*函数功能：求二者的最大值
  参数：待比较的两个数
  返回值：大的数 
*/
int Max(int a,int b){
	if(a>b) return a;
	return b;
}
/*函数功能：判定a串比b串大
  参数： a,b字符串
  返回值：a比b大则返回1，否则返回0 
*/

int namebigger(char *a,char *b){
	if(strcmp(a,b)>0) return 1; 
	else return 0;
} 
/*函数功能：判定a串比b串小 
  参数： a,b字符串
  返回值：a比b小则返回1，否则返回0 
*/
int namesmaller(char *a,char *b){
	if(strcmp(a,b)<0) return 1; 
	else return 0;
} 
void printNode(info data){
	if(data.age==-1){
		printf("无此人！！！\n");
		return ;
	}
	printf("%s ",data.name);
	if(data.gender==1) printf("woman ");
	else printf("man ");
	printf("age:%d\n",data.age);
}
/*函数功能：对单个节点右旋
  参数：节点 
  返回值：空 
*/
void zig(BitTree *x){
	BitTree y=(*x)->lson;
	(*x)->lson=y->rson;
	y->rson=(*x);
	(*x)->height=Max(getHeight((*x)->lson),getHeight((*x)->rson))+1;
	y->height=Max(getHeight((*x)),getHeight(y->lson))+1; 
	(*x)=y;
} 
/*函数功能：对单个节点左旋
  参数：节点 
  返回值：空 
*/
void zag(BitTree *x){
	BitTree y=(*x)->rson;
	(*x)->rson=y->lson;
	y->lson=(*x);
	(*x)->height=Max(getHeight((*x)->lson),getHeight((*x)->rson))+1;
	y->height=Max(getHeight((*x)),getHeight(y->rson))+1; 
	(*x)=y;
}
/* 函数功能：对单个节点下的子树完成右旋再左旋
   参数：节点
   返回值：空 
*/ 
void zigzag(BitTree *x){
	zig(&((*x)->rson));
	zag(x);
} 
/* 函数功能：对单个节点下的子树完成左旋再右旋
   参数：节点
   返回值：新的根节点 
*/
void zagzig(BitTree *x){
	zag(&((*x)->lson));
	zig(x);
}
/*函数功能：在树中查找节点x
  参数：树根root,节点名称：x
  返回值：空
  复杂度：O(logn) 
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
/*函数功能：给树添加一个元素 
  参数： 树根，元素 
  返回值： 1代表添加成功，0代表失败（已存在） 
  复杂度：O(logn) 
*/
int InsertAVL(BitTree *root,info x){
	int temp=0;
	if((*root)==NULL){//如果节点为空,就在此节点处加入x信息
        (*root)=(BitTree )malloc(sizeof(BitNode));
        (*root)->data=x;
        (*root)->height=0;
        (*root)->lson=NULL;(*root)->rson=NULL;
        return 1;
    }

    if(namebigger((*root)->data.name,x.name)){//如果x小于节点的值,就继续在节点的左子树中插入x
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
    else if(namesmaller((*root)->data.name,x.name)){//如果x大于节点的值,就继续在节点的右子树中插入x
        if(InsertAVL(&((*root)->rson),x)) temp=1;
         //如果高度之差为2的话就失去了平衡,需要旋转
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
/*函数功能：前序序遍历二叉树 
  参数：树根 
  返回值： 无
  复杂度：O(n) 
*/
void TraverseAVL(BitTree root){
	if(root==NULL) return;
	printNode(root->data);//输出根节点
	TraverseAVL(root->lson); //遍历左子树 
	TraverseAVL(root->rson);//再遍历右子树 
} 
/*函数功能：初始化一个二叉树 
  参数：指向二叉树树根的指针地址 
  返回值：无 
*/
void InitAVL(BitTree * root){
	(*root)=NULL;
	//(*root)->height=-1;
	//(*root)->lson=NULL;(*root)->rson=NULL;
}
/*函数功能：删除二叉树的一个节点 
  参数：树根root，节点x 
  返回值： 未找到返回-1，删除成功返回0
  复杂度：O(logn) 
*/ 
int DeleteAVL(BitTree *root,char* x){
	if((*root)==NULL) 	return -1;//未找到此节点 
	if(namebigger((*root)->data.name,x)){//在左子树内删除节点x 
		DeleteAVL(&((*root)->lson),x);
		if(2==getHeight((*root)->rson)-getHeight((*root)->lson)){
			if((*root)->rson->lson!=NULL&&getHeight((*root)->rson->lson)>getHeight((*root)->rson->rson))
				zigzag(root);
			else zag(root);	
		}
	}
	else if(namesmaller((*root)->data.name,x)){//在右子树内删除节点x 
		DeleteAVL(&((*root)->rson),x);
		if(2==getHeight((*root)->lson)-getHeight((*root)->rson)){
			if((*root)->lson->rson!=NULL&&getHeight((*root)->lson->rson)>getHeight((*root)->lson->lson))
				zagzig(root);
			else zig(root);	
		}
	}
	else{//找到节点x 
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
			if((*root)->lson==NULL)//有右儿子或没有儿子 
				(*root)=(*root)->rson;
			else if((*root)->rson=NULL)//有左儿子 
				(*root)=(*root)->lson;
			free(temp);		
		}
	} 
	if((*root)==NULL) return 1;
	(*root)->height=Max(getHeight((*root)->lson),getHeight((*root)->rson))+1;
	return 1;
} 
/*函数功能：对二叉树节点递归删除 
  参数：根节点 
  返回值：空 
*/
void DestroyNode(BitTree *root){
	if(*root==NULL) return ;
	if((*root)->lson!=NULL) DestroyNode(&(*root)->lson);
	if((*root)->rson!=NULL) DestroyNode(&(*root)->rson);
	free(*root);
}
/*函数功能：销毁二叉树 
  参数：指向二叉树树根的指针地址 
  返回值：空 
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
void set_init(set* group);// 初始化集合 
void set_destroy(set * group); //销毁集合 
int set_insert(set * group,info data); //插入元素 
int set_remove(set* group,info data); //删除元素 
set set_intersection(set groupA ,set  groupB); //集合的交 
set set_union(set groupA ,set  groupB); //集合的并 
set set_diffrence(set groupA ,set  groupB); //集合的差 
int set_size(set group); //集合大小 
int set_member(set group ,info data); //判断一个元素是否为集合成员 
int set_subset(set groupA ,set  groupB); //判断一个集合是否为另一个集合的子集 
int set_equal(set groupA ,set  groupB); //判断两个集合是否相等 
void treemerge(BitTree a,BitTree b,set * p);//求两棵树的交并插入新的集合中 
void treeadd(BitTree a,set * p);//将一棵树插入新的集合中 
void set_minus(set groupA ,set  groupB,set*p);//在A中除去B中的元素 并放到p中 
int tree_subset(BitTree A,set p);//判断树A中元素是否都在p中 
void set_Traverse(set group);//遍历输出集合 
/*函数功能： 初始化集合
  参数： 集合指针 
  返回值：空 
*/
void set_init(set* group){
	(*group)= (set) malloc(sizeof(Set));
	(*group)->avlTree=NULL;
	
	InitAVL(&((*group)->avlTree));
	(*group)->number=0;
}
/*函数功能： 销毁集合
  参数： 集合指针 
  返回值： 空 
*/ 
void set_destroy(set * group){
	DestroyAVL(&((*group)->avlTree));
	free(*group);
	*group=NULL;
} 
/*函数功能： 插入元素
  参数： 集合指针 ，元素数据 
  返回值：-1代表已经存在，1代表插入成功 0代表非法操作 
  复杂度：O(logn) 
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
/*函数功能： 删除元素 
  参数： 集合指针 数据元素 
  返回值：-1代表元素不存在，1代表删除成功 0代表非法操作 
*/ 
int set_remove(set* group,info data){
	if((*group)==NULL) return 0;
	if(DeleteAVL(&((*group)->avlTree),data.name)) {
		(*group)->number--;
		return 1;
	}
	else return -1;

} 
/*函数功能：求两棵树的交集 
  参数： 树a，b 集合p 
  返回值：空 
*/
void treemerge(BitTree a,BitTree b,set * p){
	if(a==NULL) return ;
	info temp;
	temp=SearchAVL(b,a->data.name);
	if((temp.age!=-1)) set_insert(p,temp);
	treemerge(a->lson,b,p);
	treemerge(a->rson,b,p);
} 
/*函数功能： 将一棵树中元素加入到集合中 
  参数： 树a，集合p 
  返回值：空 
*/
void treeadd(BitTree a,set * p){
	if(a==NULL) return ; 
	set_insert(p,a->data);
	treeadd(a->lson,p);
	treeadd(a->rson,p);
} 
/*函数功能： 求两个集合的交集 
  参数： 集合A，B 
  返回值：交集 非法操作返回空
  复杂度：O(n) 
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
/*函数功能： 求两集合的并 
  参数： 集合A，B 
  返回值：并集 非法操作返回空
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
/*函数功能： 将两棵树中不一样的元素放到新集合中 
  参数： 树A,B 集合P 
  返回值：空 
*/ 
void set_minus(BitTree A ,BitTree  B,set* p){
	if(A==NULL) return;
	info temp;temp=SearchAVL(B,A->data.name);
	if(temp.age==-1) set_insert(p,A->data);
	set_minus(A->lson,B,p);
	set_minus(A->rson,B,p);
}
/*函数功能： 求两集合的差 
  参数： 集合A,B 
  返回值：差集 非法操作返回空 
  复杂度：O(n) 
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
/*函数功能： 返回集合的大小 
  参数： 集合 
  返回值：集合大小 ,非法操作为-1; 
*/ 
int set_size(set group){
	if(group==NULL) return -1;
	return group->number; 
} 
/*函数功能： 判断元素是否为集合成员 
  参数： 集合group 元素data 
  返回值：是为1，否为0，非法操作为-1 
*/ 
int set_member(set group ,info data){
	if (group==NULL) return -1; 
	if(SearchAVL(group->avlTree,data.name).age!=-1) return 1;
	else return 0;
}
/*函数功能： 判断集合A是否是B的子集 
  参数： 集合A,集合B 
  返回值：是则为1，不是为0; 
*/ 
int tree_subset(BitTree A,set p){
	if(A==NULL) return 1;
	if(SearchAVL(p->avlTree,A->data.name).age==-1) return 0;
	else{
		return tree_subset(A->lson,p)&tree_subset(A->rson,p);
	} 
}
/*函数功能： 判断集合A是否是B的子集 
  参数： 集合A,集合B 
  返回值：是则为1，不是为0，非法操作为-1; 
  复杂度：O(n) 
*/ 
int set_subset(set groupA ,set  groupB){
	if(groupA==NULL||groupB==NULL) return -1;
	if(tree_subset(groupA->avlTree,groupB)) return 1;
	else return 0;
}
/*函数功能： 判断两个集合是否相等 
  参数： 集合A，B 
  返回值：相等为1，否则为0，非法操作为-1 
*/ 
int set_equal(set groupA ,set  groupB){
	if(groupA==NULL||groupB==NULL) return -1;
	if(set_subset(groupA,groupB)==1&&groupA->number==groupB->number) return 1;
	else return 0; 
} 
/*函数功能： 遍历输出一个集合 
  参数： 集合group 
  返回值：空 
*/ 
void set_Traverse(set group){
	printf("共：%d人\n",group->number);
	TraverseAVL(group->avlTree);
	//printf("******完毕*******\n");
}
typedef struct{   //定义应用层结构：人 
	info Myinfo;
	set Myfriends;
	set Myfans;
	set Myidols;
	//string hobby[5];
}Person,*person;
void init_person(person * ren);//初始化一个人
void destroy_person(person *ren);//删除一个人
int add_friends(person *a,person *b);//a,b互相添加为好友
int remove_friends(person *a,person *b);//a,b互相解除好友
int search_friends(person *a,person *b);//查询a，b是否是好友 
int add_fans(person *a,person *b);//a成为b的粉丝
int remove_fans(person *a,person *b);//a解除b的粉丝
int search_fans(person *a,person *b);//查询a是不是b的粉丝 
int add_idols(person *a,person *b);//a成为b的关注
int remove_idols(person *a ,person *b);//a解除是b的关注 
int search_idols(person *a,person *b);//查询a是不是b的关注 
set common_idols(person *a,person *b);//求a和b的共同关注
set common_fans(person *a,person *b);//求a和b的共同粉丝
set two_degree_friends(person *a);//求a的二度好友
void printPerson(person a);//打印输出一个人的信息 
/*函数功能：  初始化一个人 
  参数：  结构指针 a 
  返回值： 空 
*/
void init_person(person *a){
	if((*a)!=NULL) destroy_person(a);
	(*a)= (person)malloc(sizeof(Person));
	set_init(&((*a)->Myfriends));
	set_init(&((*a)->Myfans)); 
	set_init(&((*a)->Myidols));  
} 
/*函数功能：  销毁一个人 
  参数：  结构指针 a 
  返回值： 空 
*/
void destroy_person(person *ren){
	if((*ren)==NULL)  return ;
	set_destroy(&((*ren)->Myfriends));
	set_destroy(&((*ren)->Myfans));
	set_destroy(&((*ren)->Myidols));
	free(*ren); 
}
/*函数功能：  添加两人互为朋友关系 
  参数：  两个人a，b 
  返回值： 添加成功为1，非法为-1 
*/
int add_friends(person *a,person *b){
	if((*a)==NULL||(*b)==NULL) return -1; 
	if(set_insert(&((*a)->Myfriends),(*b)->Myinfo)==1&&set_insert(&((*b)->Myfriends),(*a)->Myinfo)==1) return 1;
	else return 0;
}
/*函数功能：  解除两人的好友关系 
  参数：  两个人a,b 
  返回值： 解除成功为1，解除失败为0，非法操作为-1 
*/
int remove_friends(person *a,person *b){
	if((*a)==NULL||(*b)==NULL) return -1;
	if(search_friends(a,b)!=1) return 0;
	if(set_remove(&((*a)->Myfriends),(*b)->Myinfo)==1&&set_remove(&((*b)->Myfriends),(*a)->Myinfo)==1) return 1;
	else return 0;  
} 
/*函数功能： 查找两人是否为好友关系 
  参数：  两个人a,b 
  返回值： 是则为1，否为0，非法为-1 
*/
int search_friends(person *a,person *b){
	if((*a)==NULL||(*b)==NULL) return -1;
	if(set_member((*a)->Myfriends,(*b)->Myinfo)==1) return 1;
	else return 0; 
}
/*函数功能：  添加a为b的粉丝 
  参数：  两个人a,b 
  返回值： 添加成功为1，失败为0，非法为-1 
*/
int add_fans(person *a,person *b){
	if((*a)==NULL||(*b)==NULL) return -1;
	if(set_insert(&((*b)->Myfans),(*a)->Myinfo)==1&&set_insert(&((*a)->Myidols),(*b)->Myinfo)==1) return 1;
	else return 0;
}
/*函数功能：  解除a是b的粉丝 
  参数：  两个人a,b 
  返回值： 解除成功为1，失败为0，非法为-1 
*/
int remove_fans(person *a,person *b){
	if((*a)==NULL||(*b)==NULL) return -1;
	if(search_fans(a,b)!=1) return 0; 
	if(set_remove(&((*b)->Myfans),(*a)->Myinfo)==1&&set_remove(&((*a)->Myidols),(*b)->Myinfo)==1) return 1;
	else return 0;
}
/*函数功能： 查询a是不是b的粉丝 
  参数：  两个人a,b 
  返回值： 是则返回，否则返回0，非法为-1 
*/
int search_fans(person *a,person *b){
	if((*a)==NULL||(*b)==NULL) return -1;
	if(set_member((*b)->Myfans,(*a)->Myinfo)==1) return 1;
	else return 0;  
}
/*函数功能：  添加a为b的关注 
  参数：  两个人a,b 
  返回值： 添加成功为1，失败为0，非法为-1 
*/
int add_idols(person *a,person *b){
	if((*a)==NULL||(*b)==NULL) return -1;
	if(set_insert(&((*b)->Myidols),(*a)->Myinfo)==1&&set_insert(&((*a)->Myfans),(*b)->Myinfo)==1) return 1;
	else return 0;
}
/*函数功能：  解除a是b的关注 
  参数：  两个人a,b 
  返回值： 解除成功为1，失败为0，非法为-1 
  */ 
int remove_idols(person *a ,person *b){
	if((*a)==NULL||(*b)==NULL) return -1;
	if(search_idols(a,b)!=1) return 0; 
	if(set_remove(&((*b)->Myidols),(*a)->Myinfo)==1&&set_remove(&((*a)->Myfans),(*b)->Myinfo)==1) return 1;
	else return 0;
}
/*函数功能： 查询a是不是b的关注 
  参数：  两个人a,b 
  返回值： 是则返回，否则返回0，非法为-1 
*/ 

int search_idols(person *a,person *b){
	if((*a)==NULL||(*b)==NULL) return -1;
	if(set_member((*b)->Myidols,(*a)->Myinfo)==1) return 1;
	else return 0;  
}
/*函数功能：  求两个人的共同关注 
  参数：  两个人a,b 
  返回值： 共同关注的集合 
*/
set common_idols(person *a,person *b){
	return set_intersection((*a)->Myidols,(*b)->Myidols); 
}
/*函数功能：  求两个人的共同粉丝 
  参数：  两个人a,b 
  返回值： 共同粉丝的集合 
*/
set common_fans(person *a,person *b){
	return set_intersection((*a)->Myfans,(*b)->Myfans); 
}


person personList[505];

/*函数功能：  求一个人的二度好友 
  参数：  一个人a 
  返回值： a的所有二度好友构成的集合 
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
/*函数功能：  输出一个人 
  参数：  一个人a 
  返回值： void 
*/
void printPerson(person a){
	if(a==NULL) return ;
	printf("名字是：%s 性别是：",a->Myinfo.name);
	if(a->Myinfo.gender==0) printf("男 ");
	else printf("女 ");
	printf("年龄是：%d\n",a->Myinfo.age);
	if(a->Myfriends->number>0){
		printf("Ta的好友包括：\n");
		 set_Traverse(a->Myfriends); 
	}
	else printf("Ta没有好友\n"); 
	if(a->Myfans->number>0){
		printf("Ta的粉丝包括：\n");
		 set_Traverse(a->Myfans); 
	}
	else printf("Ta没有粉丝\n");
	if(a->Myidols->number>0){
		printf("Ta的关注包括：\n");
		 set_Traverse(a->Myidols); 
	}
	else printf("Ta没有关注\n");  
	printf("******完毕*******\n");
}	
int op=1;
/*函数功能：  打印现有成员信息 
  参数：  void 
  返回值： 现有成员个数 
*/
int print_now_person(){
	int ans=0; 
	for(int i=0;i<505;i++){
		if(personList[i]==NULL) continue;
		ans=i+1;
		printf("第%d位用户为 : %s\n",ans,personList[i]->Myinfo.name);
	} 
	if(ans==0){
		printf("当前还无用户！！\n");
	}
	return ans;
}
/*函数功能：  添加一位用户 
  参数：  void 
  返回值： void 
*/
void Insert_A_Person(){
	printf("现有用户数据如下：\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	info temp;
	printf("请输入用户姓名，注意不要与存在用户姓名重复：\n");
	scanf("%s",temp.name);
	printf("请输入用户性别，0代表男，1代表女：\n");
	scanf("%d",&temp.gender);
	printf("请输入用户年龄，0~99之间：\n");
	scanf("%d",&temp.age);
	for(int i=0;i<505;i++){
		if(personList[i]==NULL) continue;
		if(strcmp(personList[i]->Myinfo.name,temp.name)==0){
			printf("输入已存在，请重新操作\n");
			return ; 
		}
	}
	if(temp.gender!=0&&temp.gender!=1){
		printf("性别输入错误，请重新操作\n");
		return ;
	}
	if(temp.age<0||temp.age>99){
		printf("年龄输入错误，请重新操作\n");
		return ;
	}
	init_person(&personList[now]);
	personList[now]->Myinfo=temp;
	printf("添加成功!\n"); 
}
/*函数功能：  删除一位用户 
  参数：  void 
  返回值： void 
*/
void Delete_A_Person(){
	printf("现有用户数据如下：\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	int del;
	printf("请输入要删除的用户编号：（在1--%d之间）\n",now);
	scanf("%d",&del);
	if(del<1||del>now){
		printf("编号输入有误，请重新操作\n");
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
	printf("删除成功！\n");
}
/*函数功能：  增添两个人的好友关系 
  参数：  void 
  返回值： void 
*/
void Make_Friends(){
	printf("现有用户数据如下：\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	int per1,per2;
	printf("请输入两位用户的编号：\n用户1：\n");
	scanf("%d",&per1);
	printf("用户2：\n");
	scanf("%d",&per2);
	if(per1<1||per1>now||per2<1||per2>now){
		printf("编号输入有误，请重新操作\n");
		return ;
	} 
	if(search_friends(&personList[per1-1],&personList[per2-1])==1){
		printf("这两位已经是好友了！！\n");
		return ;
	}
	else{
		if(add_friends(&personList[per1-1],&personList[per2-1])==1) printf("操作成功！！\n");
		else printf("操作失败！！\n");
		return ;
	}
}
/*函数功能：  删除两个人的好友关系 
  参数：  void 
  返回值： void 
*/
void Remove_Friends(){
	printf("现有用户数据如下：\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	int per1,per2;
	printf("请输入两位用户的编号：\n用户1：\n");
	scanf("%d",&per1);
	printf("用户2：\n");
	scanf("%d",&per2);
	if(per1<1||per1>now||per2<1||per2>now){
		printf("编号输入有误，请重新操作\n");
		return ;
	} 
	if(search_friends(&personList[per1-1],&personList[per2-1])!=1){
		printf("这两位还不是好友！！\n");
		return ;
	}
	else{
		if(remove_friends(&personList[per1-1],&personList[per2-1])==1) printf("操作成功！！\n");
		else printf("操作失败！！\n");
		return ;
	}
} 
/*函数功能：  查询两个人是不是好友 
  参数：  void 
  返回值： void 
*/
void Search_Friends(){
	printf("现有用户数据如下：\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	int per1,per2;
	printf("请输入两位用户的编号：\n用户1：\n");
	scanf("%d",&per1);
	printf("用户2：\n");
	scanf("%d",&per2);
	if(per1<1||per1>now||per2<1||per2>now){
		printf("编号输入有误，请重新操作\n");
		return ;
	} 
	if(search_friends(&personList[per1-1],&personList[per2-1])!=1){
		printf("这两位还不是好友！！\n");
		return ;
	}
	else{
		printf("这两位确实是好友！！\n");
		return ;
	} 
}
/*函数功能：  添加一个人为另一个的粉丝 
  参数：  void 
  返回值： void 
*/
void Add_A_Fans(){
	printf("现有用户数据如下：\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	int per1,per2;
	printf("请输入两位用户的编号：\n用户1：（粉丝）\n");
	scanf("%d",&per1);
	printf("用户2：（偶像）\n");
	scanf("%d",&per2);
	if(per1<1||per1>now||per2<1||per2>now){
		printf("编号输入有误，请重新操作\n");
		return ;
	} 
	if(search_fans(&personList[per1-1],&personList[per2-1])==1){
		printf("Ta已经是Ta的粉丝了！！\n");
		return ;
	}
	else{
		if(add_fans(&personList[per1-1],&personList[per2-1])==1) printf("操作成功！！\n");
		else printf("操作失败！！\n");
		return ;
	}
}
/*函数功能：  解除一个人为另一个的粉丝 
  参数：  void 
  返回值： void 
*/
void Remove_Fans(){
	printf("现有用户数据如下：\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	int per1,per2;
	printf("请输入两位用户的编号：\n用户1：（粉丝）\n");
	scanf("%d",&per1);
	printf("用户2：（偶像）\n");
	scanf("%d",&per2);
	if(per1<1||per1>now||per2<1||per2>now){
		printf("编号输入有误，请重新操作\n");
		return ;
	} 
	if(search_fans(&personList[per1-1],&personList[per2-1])!=1){
		printf("Ta还不是Ta的粉丝！！\n");
		return ;
	}
	else{
		if(remove_fans(&personList[per1-1],&personList[per2-1])==1) printf("操作成功！！\n");
		else printf("操作失败！！\n");
		return ;
	}
} 
/*函数功能：  查询一个人是不是另一个的粉丝 
  参数：  void 
  返回值： void 
*/
void Search_Fans(){
	printf("现有用户数据如下：\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	int per1,per2;
	printf("请输入两位用户的编号：\n用户1：（粉丝）\n");
	scanf("%d",&per1);
	printf("用户2：（偶像）\n");
	scanf("%d",&per2);
	if(per1<1||per1>now||per2<1||per2>now){
		printf("编号输入有误，请重新操作\n");
		return ;
	} 
	if(search_fans(&personList[per1-1],&personList[per2-1])!=1){
		printf("Ta还不是Ta的粉丝！！\n");
		return ;
	}
	else{
		printf("Ta确实是Ta的粉丝！！\n");
		return ;
	} 
}
/*函数功能：  查询两个人的共同粉丝 
  参数：  void 
  返回值： void 
*/
void Commom_Fans(){
	printf("现有用户数据如下：\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	int per1,per2;
	printf("请输入两位用户的编号：\n用户1：\n");
	scanf("%d",&per1);
	printf("用户2：\n");
	scanf("%d",&per2);
	if(per1<1||per1>now||per2<1||per2>now){
		printf("编号输入有误，请重新操作\n");
		return ;
	} 
	printf("他们的共同粉丝包括如下：\n");
	set_Traverse(common_fans(&personList[per1-1],&personList[per2-1]));
	return ;
}
/*函数功能：  查询两个人的共同关注 
  参数：  void 
  返回值： void 
*/
void Commom_Idols(){
	printf("现有用户数据如下：\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	int per1,per2;
	printf("请输入两位用户的编号：\n用户1：\n");
	scanf("%d",&per1);
	printf("用户2：\n");
	scanf("%d",&per2);
	if(per1<1||per1>now||per2<1||per2>now){
		printf("编号输入有误，请重新操作\n");
		return ;
	} 
	printf("他们的共同关注包括如下：\n");
	set_Traverse(common_idols(&personList[per1-1],&personList[per2-1]));
	return ;
}
/*函数功能：  查询两一个人的二度好友 
  参数：  void 
  返回值： void 
*/
void TwoDFriends(){
	printf("现有用户数据如下：\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	int per1;
	printf("请输入要查询的用户的编号：\n");
	scanf("%d",&per1);
	if(per1<1||per1>now){
		printf("编号输入有误，请重新操作\n");
		return ;
	} 
	printf("他Ta的二度好友包括如下：\n");
	set_Traverse(two_degree_friends(&personList[per1-1]));
	return ;
}
/*函数功能： 查询用户是否有这个喜好 
  参数：  用户编号，喜好 
  返回值： 1则有，0则没有 
*/
/*HaveThisHobby(int per1,string temp){
	for(int i=0;i<5;i++){
		if(personList[per1]->hobby[i]==temp) return 1;
	} 
	return 0;
}
/*函数功能： 为一个用户增添喜好 
  参数：  void 
  返回值： void 
*/
/*void AddHobby(){
	printf("现有用户数据如下：\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	int per1;
	printf("请输入这位用户的编号\n");
	scanf("%d",&per1);
	int t=-1;
	for(int i=0;i<5;i++){
		cout<<personList[per1]->hobby[i].size()<<endl;
		cout<<personList[per1]->hobby[i]<<endl;
		if(personList[per1]->hobby[i]!="") t=i; 
	}
		
	if(t==4){
		printf("此人已经有了太多的爱好！\n");
		return;
	}
	cout<<"endad"<<endl;
	printf("请输入它的喜好们：\n");
	for(int i=t+1;i<5;i++){
		string temp;
		cin>>temp;
		if(HaveThisHobby(per1,temp)) {
			printf("它已经有了这个爱好！\n");
			i--;continue;
		}
		if(i==4){
			printf("此人已经有了太多的爱好！\n");
			return;
		}
		if(temp=="") break ;
		personList[per1]->hobby[i]=temp;
	}
	printf("增加成功！\n");
}
/*函数功能： 为一个用户删除喜好 
  参数：  void 
  返回值： void 
*/
/*void RemoveHobby(){
	printf("现有用户数据如下：\n"); 
	int now=print_now_person();
	printf("--------------------------------\n");
	int per1;
	printf("请输入这位用户的编号\n");
	scanf("%d",&per1);
	int t=-1;
	for(int i=0;i<5;i++)
		if(personList[per1]->hobby[i]!="") t=i; 
	if(t==-1){
		printf("此人还没有爱好！\n");
		return;
	}
	printf("他的爱好如下：\n");
	for(int i=0;i<=t;i++)
		cout<<personList[per1]->hobby[i]<<endl;
	printf("请输入你要删除的爱好：\n");
	string temp;
	cin>>temp;
	if(HaveThisHobby(per1,temp)==0){
		printf("输入有误！\n");
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
	printf("删除成功！\n");
}




/*函数功能：  将数据写入到文件中 
  参数：  void 
  返回值： void 
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
	printf("已成功保存！！！\n");	
}
/*函数功能：  从文件中读取数据 
  参数：  void 
  返回值： void 
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
	printf("读取成功！！！\n");
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
	//printf("请输入用户姓名，注意不要与存在用户姓名重复：\n");
	strcpy(temp.name,tempp);
	//printf("请输入用户性别，0代表男，1代表女：\n");
	temp.gender=sex;
	//printf("请输入用户年龄，0~99之间：\n");
	temp.age=age;
	for(int i=0;i<505;i++){
		if(personList[i]==NULL) continue;
		if(strcmp(personList[i]->Myinfo.name,temp.name)==0){
			printf("输入已存在，请重新操作\n");
			return ; 
		}
	}
	if(temp.gender!=0&&temp.gender!=1){
		printf("性别输入错误，请重新操作\n");
		return ;
	}
	if(temp.age<0||temp.age>99){
		printf("年龄输入错误，请重新操作\n");
		return ;
	}
	init_person(&personList[now]);
	personList[now]->Myinfo=temp;
	printf("添加成功!\n"); 
}
int main(){
	while(op){
		system("cls");	printf("\n\n");
		printf("                   微博关注、粉丝、好友集管理系统 \n");
		printf("---------------------------------------------------------------------------------\n");
		printf("    	           1. InsertPerson（新增一名用户）       \n");
		printf("    	           2. DeletePerson（删除一名用户）     \n");
		printf("    	           3. MakeFriend  （两名用户建立好友关系）     \n");
		printf("    	           4. ReliveFriend（两名用户解除好友关系）    \n");
		printf("    	           5. SearchFriend（查询两名用户是否为好友关系）    \n");
		printf("    	           6. Add_A_Fans  （一名用户成为另一名用户的粉丝） \n");
		printf("    	           7. Relive_AFans（一名用户取消成为另一名的粉丝）  \n");
		printf("    	           8. SearchFans  （查询一名用户是否是另一名的粉丝）  \n");
		printf("    	           9. Common_Fans （查询两个用户的共同粉丝）  \n");
		printf("    	           10. Commom_idols（查询两个用户的共同关注）  \n");
		printf("    	           11. Friend's_Friends（查询一位用户的二度好友）  \n");
		//printf("    	           12. AddHobby（为一个用户添加一个喜好）  \n");
		//printf("    	           13. RemoveHobby（删除一个用户的喜好）  \n");
		//printf("    	           14. CommonHobby（求两个用户的共同喜好）  \n");
		printf("    	           0. Exit\n");
		printf("                   15.Save（将数据保存到文件）   16.Load（从文件中读取数据）\n");
		printf("---------------------------------------------------------------------------------\n");
		printf("                  请选择你的操作[0~16]:");
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
		   	 printf("感谢使用本系统！！\n");
	         break;
		}//end of switch
	} 
	return 0;
}
