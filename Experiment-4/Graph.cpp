#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2


//Status是函数的类型，其值是函数结果状态代码
typedef int Status;

typedef int QElemType;

typedef struct QNode{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front,rear; //队头、队尾指针
}LinkQueue;

Status InitQueue(LinkQueue *Q){
    //构造一个空队列Q
	(*Q).front = (*Q).rear = (QueuePtr)malloc(sizeof(QNode));
	if(!(*Q).front) exit(OVERFLOW);
	(*Q).front->next = NULL;
	return OK;
}

Status QueueEmpty(LinkQueue Q){//若Q为空队列,则返回TRUE,否则返回FALSE
	if(Q.front == Q.rear) return TRUE;
	else return FALSE;
}

Status EnQueue(LinkQueue *Q, QElemType e){//插入元素e为Q的新的队尾元素    
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if(!p) //存储分配失败
		exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	(*Q).rear->next = p;
	(*Q).rear = p;
	return OK;
}

Status DeQueue(LinkQueue *Q, QElemType *e){ //若队列不空,删除Q的队头元素,用e返回其值,并返回OK,否则返回ERROR
	QueuePtr p;
	if((*Q).front == (*Q).rear)
		return ERROR;
	p = (*Q).front->next;
	*e = p->data;
	(*Q).front->next = p->next;
	if((*Q).rear == p)
		(*Q).rear = (*Q).front;
	free(p);
	return OK;
}

typedef int Boolean;

#define MAX_VERTEX_NUM 20 //最大顶点数
#define MAX_VERNAME_LEN 10 //顶点名称最大长度

//数据元素类型定义
typedef char VertexType[MAX_VERNAME_LEN];
typedef int InfoType;

typedef struct ArcNode{
	int adjvex;               //该弧所指向的顶点位置
	struct ArcNode * nextarc; //指向下一条弧的指针
	InfoType *info;           //该弧相关信息的指针
}ArcNode;

typedef struct VNode{
	ArcNode * firstarc;      //指向第一条依附该顶点的弧的指针
	VertexType data;         //顶点信息
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct{
	AdjList vertices;
	int vexnum, arcnum;       //图的当前顶点数和弧数
	int kind;                 //图的种类标志
}ALGraph;

Status CreateGraph(ALGraph * G);//按V和VR的定义构造图G  
Status DestroyGraph(ALGraph * G);//销毁图G   
int LocateVex(ALGraph G, VertexType u);//若u在图G中存在，返回顶点u的位置序号，否则返回-1 
int FirstAdjVex(ALGraph G, VertexType v);//返回v的第一个邻接顶点，如果v没有邻接顶点，返回空
int NextAdjVex(ALGraph G, VertexType v, VertexType w);//返回v的（相对于w）下一个邻接顶点，如果w是最后一个邻接顶点，返回空。
Status InsertVex(ALGraph * G, VertexType v);//在图G中增加新顶点v
Status DeleteVex(ALGraph * G, VertexType v);//在图G中删除顶点v和与v相关的弧
Status InsertArc(ALGraph * G, VertexType v, VertexType w);//在图G中增加弧<v,w>，如果图G是无向图，还需要增加<w,v>
Status DeleteArc(ALGraph * G, VertexType v, VertexType w);//在图G中删除弧<v,w>，如果图G是无向图，还需要删除<w,v>
Status DFSTraverse(ALGraph G, Status (*visit)(VertexType a));//对图G进行深度优先搜索遍历 
Status BFSTraverse(ALGraph G, Status (*visit)(VertexType a));//对图G进行广度优先搜索遍历
int OutDegree(VNode * i);//计算图G第i个定点的出度
Status SaveGraph(ALGraph G);//保存
Status LoadGraph(ALGraph * G);//读取
Status Visit(VertexType a);//输出a
Boolean visited[MAX_VERTEX_NUM]; 
  //访问标志数组
Status (*VisitFunc)(VertexType a);
  //函数变量

/*返回值： Status 成功则返回OK
*函数功能： 构造图G*/
Status CreateGraph(ALGraph * G)
{
	int i,j,k;
	int w; //权值W
	VertexType va,vb;//弧尾Va，弧头Vb
	ArcNode *p;
	printf("请输入图的3项基本信息：\n类型(0-有向图, 1-有向网, 2-无向图, 3-无向网): ");
	//输图类型
	scanf("%d",&(*G).kind);
	while ((*G).kind < 0 || (*G).kind > 3){
		printf("输入值非法！请重输: ");
		scanf("%d",&(*G).kind);
	}
	//输顶点数
	printf("顶点数（%d以内）: ", MAX_VERTEX_NUM);
	scanf("%d", &(*G).vexnum);
	while ((*G).vexnum < 0 || (*G).vexnum > MAX_VERTEX_NUM){
		printf("输入值非法！请重输: ");
		scanf("%d",&(*G).vexnum);
	}
	//输边数
	printf("弧(边)数: ");
	scanf("%d", &(*G).arcnum);
	printf("请输入%d个顶点的名称或值(%d个字符以内,空格分开):\n", (*G).vexnum, MAX_VERNAME_LEN);
	for (i = 0; i < (*G).vexnum; i++) {//输入各顶点信息
		getchar();
		scanf("%s",(*G).vertices[i].data);
		(*G).vertices[i].firstarc = NULL;
	}
	if ((*G).kind % 2) {//1、3为网
		printf("请按序输入弧(边)权值W、弧尾Va和弧头Vb(空格分开):\n   W Va Vb\n");
	}
	else {//0、2为图
		printf("请按序输入弧(边)的弧尾Va和弧头Vb(空格分开):\n   Va Vb\n");
	}
	for (k = 0; k < (*G).arcnum; k++) {//构造邻接表
		printf("%d: ", k+1);
		if ((*G).kind % 2) {//网
			scanf("%d%s%s", &w, va, vb);
		}
		else {//图
			scanf("%s%s", va, vb);
		}
		i = LocateVex(*G, va); //弧尾
		j = LocateVex(*G, vb); //弧头
		if (i == -1 || j == -1){//顶点不存在
			printf("顶点不存在！请重输！\n");
			k--;
			continue;
		}
		p = (ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex = j;
		if ((*G).kind % 2){//网
			p->info = (int *)malloc(sizeof(int));
			*(p->info) = w;
		}
		else  {//图
			p->info = NULL;
		}
		p->nextarc = (*G).vertices[i].firstarc; //插在表头
		(*G).vertices[i].firstarc = p;

		//无向图或无向网还需逆向的
		if((*G).kind >= 2){
			p = (ArcNode*)malloc(sizeof(ArcNode));
			p->adjvex = i;
			if ((*G).kind == 3) {//无向网
				p->info = (int*)malloc(sizeof(int));
				*(p->info) = w;
			}
			else {//无向图
				p->info = NULL;
			}
			p->nextarc = (*G).vertices[j].firstarc; //插在表头
			(*G).vertices[j].firstarc = p;
		}
	}
	return OK;
}

/*返回值：  Status 成功则返回OK
*函数功能： 销毁图G*/
Status DestroyGraph(ALGraph *G){
	int i;
	ArcNode * p, * q;
	for(i = 0; i < (*G).vexnum; i++){
		p=(*G).vertices[i].firstarc;
		while(p){
			q = p->nextarc;
			if((*G).kind % 2) {//网
				free(p->info);
			}
			free(p);
			p = q;
		}
	}
	(*G).vexnum = 0;
	(*G).arcnum = 0;
	(*G).kind = -1;//以-1代表图不存在
	return OK;
}
/*返回值： int
*函数功能： 若u在图G中存在，返回顶点u的位置序号，否则返回-1*/
int LocateVex(ALGraph G, VertexType u)
{
	int i;
	for(i = 0; i < G.vexnum; i++){
		if(strcmp(u,G.vertices[i].data) == 0){ //名称相同 
			return i;
		}
	}
	return -1;//未找到则返回-1
}

/*返回值： int
*函数功能： 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1*/
int FirstAdjVex(ALGraph G, VertexType v)
{
	ArcNode *p;
	int v1;
	v1 = LocateVex(G,v);//获取v在图G中的序号v1
	if (v1 == -1){
		return -2;
	}
	p = G.vertices[v1].firstarc;
	if (p){
		return p->adjvex;
	}
	else{
		return -1;
	}
}

/*返回值： int
*函数功能： 返回v的(相对于w的)下一个邻接顶点的序号，
*			若w是v的最后一个邻接点,则返回-1*/
int NextAdjVex(ALGraph G,VertexType v,VertexType w){
	ArcNode *p;
	int v1, w1;
	v1 = LocateVex(G,v); //获取v在图G中的序号v1
	w1 = LocateVex(G,w); //获取w在图G中的序号w1
	if (v1 == -1){//顶点不存在
		return(-2);
	}
	if (w1 == -1){//邻接点不存在
		return(-3);
	}
	p = G.vertices[v1].firstarc;
	while (p && p->adjvex != w1){//指针p不空且所指表结点不是w
		p = p->nextarc;
	}
	//没找到w或w是最后一个邻接点
	if(!p || !p->nextarc){
		return -1;
	}
	else{//返回v的(相对于w的)下一个邻接顶点的序号
		return p->nextarc->adjvex;
	}
}
/*返回值：  Status
*函数功能： 在图G中增加新顶点v*/
Status InsertVex(ALGraph *G, VertexType v){
	if((*G).vexnum == MAX_VERTEX_NUM){//顶点数达最大值
		return ERROR;
	}
	//构造新顶点
	strcpy((*G).vertices[(*G).vexnum].data, v);
	(*G).vertices[(*G).vexnum].firstarc=NULL;
	(*G).vexnum++; //图G的顶点数加1
	return OK;
 }

/*返回值：  Status 成功返回OK
*函数功能： 删除G中顶点v及其相关的弧*/

Status DeleteVex(ALGraph *G, VertexType v){
	int i, j;
	ArcNode *p, *q;
	j = LocateVex(*G, v); //获取顶点v的序号
	if(j == -1) {//v不是图G的顶点
		return ERROR;
	}
	//删除以v为出度的弧或边
    p = (*G).vertices[j].firstarc;
	while(p){
		q = p;
		p = p->nextarc;
		if((*G).kind%2) {//网
			free(q->info);
		}
		free(q);
		(*G).arcnum--; //弧或边数减1
	}

	//重新排列顶点
	(*G).vexnum--; //顶点数减1
	for(i = j; i < (*G).vexnum; i++) //顶点v后面的顶点前移
	{
		(*G).vertices[i] = (*G).vertices[i+1];
	}

	//删除以v为入度的弧或边且修改弧所指顶点位置值
	for(i = 0; i < (*G).vexnum; i++){
		p = (*G).vertices[i].firstarc; //指向第1条弧或边
		while(p){ //有弧或边
			if(p->adjvex == j){//该弧指向被删结点
				if(p == (*G).vertices[i].firstarc){ //待删结点是第1个结点
					(*G).vertices[i].firstarc = p->nextarc;
					if((*G).kind%2) {//网
						free(p->info);
					}
					free(p);
					p = (*G).vertices[i].firstarc;
					if((*G).kind < 2){//有向图需再减一次
						(*G).arcnum--; //弧或边数减1
					}
				}
				else{
					q->nextarc = p->nextarc;
					if((*G).kind % 2) {//网
						free(p->info);
					}
					free(p);
					p = q->nextarc;
					if((*G).kind < 2){//有向需再减一次
						(*G).arcnum--; //弧或边数减1
					}
				}
			}
			else{//该弧不指向被删结点

				if(p->adjvex > j){//该弧所指元素位置序号在删除顶点之后
					p->adjvex--;//更改弧所指顶点位置序号
				}
				q = p;
				p = p->nextarc;//分析下一条弧
			}
		}
	}
	return OK;
}

/*返回值：  Status 成功返回OK；
*函数功能：在图G中增加弧<v,w>，如果图G是无向图，还需要增加<w,v>*/
Status InsertArc(ALGraph *G,VertexType v,VertexType w){
	ArcNode *p;
	int w1, i, j;
	i = LocateVex(*G, v); //获取v位置序号
	j = LocateVex(*G, w); //获取w位置序号
	if(i == -1 || j == -1){//未找到相应顶点
		return ERROR;
	}

	//建立弧v-w
	(*G).arcnum++;
	if((*G).kind % 2){ //网要输权值
		printf("请输入弧(边)%s->%s的权值: ", v, w);
		scanf("%d", &w1);
	}
	p=(ArcNode*)malloc(sizeof(ArcNode));
	p->adjvex = j;
	if((*G).kind % 2) {//网
		p->info = (int *)malloc(sizeof(int));
		*(p->info) = w1;
	}
	else{
		p->info=NULL;
	}
	p->nextarc = (*G).vertices[i].firstarc;
	(*G).vertices[i].firstarc = p;

	//无向图需要再建立弧w-v
	if((*G).kind >= 2){
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = i;
		if((*G).kind == 3) {//无向网
			p->info = (int*)malloc(sizeof(int));
			*(p->info) = w1;
		}
		else{
			p->info = NULL;
		}
		p->nextarc = (*G).vertices[j].firstarc;
		(*G).vertices[j].firstarc = p;
	}
	return OK;
}

/*返回值：  Status 成功返回OK；
*函数功能： 在图G中删除弧<v,w>，如果图G是无向图，还需要删除<w,v>*/
Status DeleteArc(ALGraph * G,VertexType v,VertexType w){
	ArcNode *p, *q;
	int i, j;
	i = LocateVex(*G, v); //顶点v序号
	j = LocateVex(*G, w); //顶点w序号
	if(i < 0 || j < 0){
		return ERROR;
	}

	//删除弧<v,w>
	p = (*G).vertices[i].firstarc;
	while(p && p->adjvex != j){ //p不空且所指之弧不是待删除弧<v,w>
	 //p指向下一条弧
		q = p;
		p = p->nextarc;
	}
	if(p && p->adjvex == j) {//找到弧<v,w>
		if(p == (*G).vertices[i].firstarc){ //p所指是第1条弧
			(*G).vertices[i].firstarc = p->nextarc;//指向下一条弧
		}
		else{//指向下一条弧
			q->nextarc = p->nextarc;
		}
		if((*G).kind % 2){//网要多释放权值
			free(p->info);
		}
		free(p); //释放此结点
		(*G).arcnum--; //弧或边数减1
	}

	//无向图要删除对称弧<w,v>
	if((*G).kind >= 2){
		p = (*G).vertices[j].firstarc;
		while(p && p->adjvex != i) {//p不空且所指之弧不是待删除弧<w,v> 
			q = p;//p指向下一条弧 
			p = p->nextarc;
		}
		if(p && p->adjvex == i){ //找到弧<w,v>
			if(p == (*G).vertices[j].firstarc){ //p所指是第1条弧
				(*G).vertices[j].firstarc=p->nextarc;//指向下一条弧
			}
			else{//指向下一条弧
				q->nextarc=p->nextarc;
			}
			if((*G).kind % 2){//网要多释放权值
				free(p->info);
			}
			free(p); //释放此结点
		}
	}
	return OK;
 }

/*返回值：   无
*函数功能： 从第v个顶点出发递归地深度优先遍历图G。*/

void DFS(ALGraph G,int v)
{
	int w;
	VertexType v1, w1;
	strcpy(v1, G.vertices[v].data);
	visited[v] = TRUE; //设置访问标志为TRUE(已访问)
	VisitFunc(G.vertices[v].data); /* 访问第v个顶点 */
	for(w = FirstAdjVex(G,v1); w >= 0; w = NextAdjVex(G, v1, strcpy(w1, G.vertices[w].data))){
		if(!visited[w]){
			DFS(G,w); //对v的尚未访问的邻接点w递归调用DFS
		}
	}
}

/*返回值：  Status 成功返回OK；
*函数功能： 对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函
*				数visit访问一次，且仅访问一次*/
Status DFSTraverse(ALGraph G, Status (*Visit)(VertexType a)){
	int v;
	VisitFunc = Visit; //使用全局变量VisitFunc,使DFS不必设函数指针参数
	for(v = 0; v < G.vexnum; v++){
		visited[v]=FALSE; //访问标志数组初始化
	}
	for(v = 0; v < G.vexnum; v++){
		if(!visited[v]){
			DFS(G,v); //对尚未访问的顶点调用DFS
		}
	}
	return OK;
}

/*返回值：  Status 成功返回OK；
*函数功能： 按广度优先非递归遍历图G。*/
Status BFSTraverse(ALGraph G, Status (*Visit)(VertexType a)){
	int v, u, w;
	VertexType u1, w1;
	LinkQueue Q;
	for(v = 0; v < G.vexnum; ++v) visited[v]=FALSE;
    InitQueue(&Q); //置空的辅助队列Q
    for(v = 0; v < G.vexnum; ++v)
		if(!visited[v]) {//v尚未访问
			visited[v] = TRUE;
			Visit(G.vertices[v].data);
			EnQueue(&Q, v); //v入队列
			while(!QueueEmpty(Q)){
				DeQueue(&Q, &u); //队头元素出队并置为u
				strcpy(u1, G.vertices[u].data);
				for(w = FirstAdjVex(G,u1); w >= 0; w = NextAdjVex(G, u1, strcpy(w1, G.vertices[w].data)))
					if(!visited[w]){ //w为u的尚未访问的邻接顶点
						visited[w] = TRUE;
						Visit(G.vertices[w].data);
						EnQueue(&Q,w); //w入队
					}
			}
		}
	return OK;
}

/*返回值：   int 图G的第i个顶点出度
*函数功能： 计算图G的第i个顶点出度*/
int OutDegree(VNode * i){
	int num = 0;
	ArcNode * p;
	p = (*i).firstarc;
	while (p != NULL){
		num++;
		p = p->nextarc;
	}
	return num;
}

/*返回值： Status
*函数功能： 读取线性表。*/

Status LoadGraph(ALGraph * G){
	int i, k = 0, num;
	FILE *fp;
	ArcNode *p;
	char filename[30];
	printf("请输入读取文件名: ");
	scanf("%s", &filename);
	if ((fp = fopen(filename,"r")) == NULL)
	{
		printf("文件打开失败！\n ");
		return ERROR;
	}
	//读取图基本信息
	fread(&G->kind, sizeof(int), 1, fp);
	fread(&G->vexnum, sizeof(int), 1, fp);
	fread(&G->arcnum, sizeof(int), 1, fp);
	//读取邻接表
	while(fread(G->vertices[k].data, sizeof(char), MAX_VERTEX_NUM, fp)){//有顶点
		fread(&num, sizeof(int), 1, fp);
		if (num == 0){
			G->vertices[k].firstarc = NULL;
		}
		else{
			G->vertices[k].firstarc = NULL;
			for (i = 0; i < num; i++){
				p = (ArcNode *)malloc(sizeof(ArcNode));
				fread(&(p->adjvex), sizeof(int), 1, fp);
				if ((*G).kind % 2){//网
					p->info = (int *)malloc(sizeof(int));
					fread(p->info, sizeof(InfoType), 1, fp);
				}
				else  {//图
					p->info = NULL;
				}
				p->nextarc = (*G).vertices[k].firstarc; //插在表头
				(*G).vertices[k].firstarc = p;
			}
		}
		k++;
	}
	fclose(fp);
	return OK;
}

/*返回值： Status
*函数功能： 保存线性表。*/

Status SaveGraph(ALGraph G){
	int i, num;
	FILE  *fp;
	char filename[30];
	ArcNode *p;
	printf("请输入保存文件名： ");
    scanf("%s",&filename);

    //写文件的方法
	if ((fp = fopen(filename, "w")) == NULL)
	{
		printf("文件打开失败\n ");
		return ERROR;
	}
	//保存图基本信息
	fwrite(&G.kind, sizeof(int), 1, fp);
	fwrite(&G.vexnum, sizeof(int), 1, fp);
	fwrite(&G.arcnum, sizeof(int), 1, fp);
	//保存邻接表
	for (i = 0; i < G.vexnum; i++){
		fwrite(G.vertices[i].data, sizeof(char), MAX_VERTEX_NUM, fp);
		num = OutDegree(&(G.vertices[i]));
		fwrite(&num, sizeof(int), 1, fp);
		if ((p = G.vertices[i].firstarc) != NULL){
			fwrite(&p->adjvex, sizeof(int), 1, fp);
			if (G.kind % 2){//网	
				fwrite(p->info, sizeof(int), 1, fp);
			}
			while ((p = p->nextarc) != NULL){
				fwrite(&p->adjvex, sizeof(int), 1, fp);
				if (G.kind % 2){//网
					fwrite(p->info, sizeof(int), 1, fp);
				}
			}
		}
	}
	fclose(fp);
	return OK;
}

/*返回值： Status 返回OK
*函数功能： 输出a*/

Status Visit(VertexType a)
{
	printf("%s ",a);
	return OK;
}
ALGraph g1;
int main(){
  int op=1;
  int i;
  int option; 
  char s[30]; 
  char temp[30]; 
  //BiTree thisnode ; 
  //BiTree newnode;
  //BiTree tempnode;
  int stringleng;
  int id;
  while(op){
	system("cls");	printf("\n\n");
	printf("                                       图操作菜单                        \n");
	printf("------------------------------------------------------------------------------------------\n");
	printf("    	  1. CreateGraph（创建图）       9. DeleteVex（删除顶点）\n");
	printf("    	  2. DestroyGraph（销毁图）      10. InsertArc（插入弧）\n");
	printf("    	  3. LocateVex   （查找顶点）    11. DeleteArc（删除弧）\n");
	printf("    	  4. GetVex     （获得顶点值）   \n");
	printf("    	  5. PutVex     （顶点赋值）     12. DFSTraverse （深度优先搜索遍历）\n");
	printf("    	  6. FirstAdjVex（获得第一邻接点）13. BFSTraverse  （广深度优先搜索遍历）\n");
	printf("    	  7. NextAdjVex （获得下一邻接点）     \n");
	printf("    	  8. InsertVex  （插入顶点）        \n");
	printf("    	  0. Exit      （退出系统）\n");
	printf("          14.Save      （将图保存到文件）   15.Load             （从文件中读取图）   \n");
	printf("--------------------------------------------------------------------------------------------\n");
	printf("    请选择你的操作[0~15]:");
	scanf("%d",&op);
	    switch(op){
		   case 1:
		   	
			 if(CreateGraph(&g1)==OK) printf("图1创建成功！\n");
			     else printf("二叉树1创建失败！\n");
			 getchar();getchar();
			 break;
			 
			 
		   case 2:
		   	
		   	
			 if(DestroyGraph(&g1)==OK) printf("图1删除成功！\n");
			     else printf("图1删除失败！\n");     
			 getchar();getchar();
			 break;
			 
			 
		   case 3: 
		     
		   	 printf("请输入你要查找的顶点：\n");getchar();
		   	 scanf("%s",s);
			 id=LocateVex(g1,s);
			 if(id==-1){
			 	printf("无此顶点\n");
			 }	 
			 else {
			 	printf("此顶点编号为：%d\n",id);
			 }   
			 getchar();getchar();
			 break;
			 
			 
		   case 4: 
		   
		   
			 printf("请输入你要获得值的顶点：\n");getchar();
		   	 scanf("%s",s);
			 id=LocateVex(g1,s);
			 if(id==-1){
			 	printf("无此顶点\n");
			 }	 
			 else {
			 	printf("此顶点值为：%s\n",g1.vertices[id].data);
			 }      
			 getchar();getchar();
			 break;
			 
			 
		   case 5:
		   	
		   	 
			 printf("请输入你要赋值的顶点：\n");getchar();
		   	 scanf("%s",s);
		   	 printf("请输入新的值：\n");getchar();
		   	 scanf("%s",temp);
			 id=LocateVex(g1,s);
			 if(id==-1){
			 	printf("无此顶点\n");
			 }	 
			 else {
			 	strcpy(g1.vertices[id].data,temp);
			 	printf("修改成功");
			 }          
			 getchar();getchar();
			 break;
			 
			 
		   case 6:
		   	
		   	 printf("请输入你要操作的顶点：\n");getchar();
		   	 scanf("%s",s);
			 id=FirstAdjVex(g1,s);
			 if(id==-1){
			 	printf("输入有误\n");
			 }	 
			 else if(id==-2){
			 	printf("不存在邻接点\n");
			 } 
			 else {
			 	printf("第一邻接点为编号为%d\n",id);
			 }   
			 getchar();getchar();
			 break;
			 
			 
		   case 7:  
		   
		      
			 printf("请输入你要操作的顶点：\n");getchar();
		   	 scanf("%s",s);
		   	 printf("请输入一个它的邻接点：\n");getchar();
		   	 scanf("%s",temp);
			 id=NextAdjVex(g1,s,temp);
			 if(id==-1){
			 	printf("无下一个邻接点\n");
			 }	 
			 else if(id==-2){
			 	printf("该顶点不存在\n");
			 }
			 else if(id==-3){
			 	printf("该邻接点不存在\n");
			 }
			 else{
			 	printf("下一邻接点为编号为%d\n",id);
			 }
			 getchar();getchar();
			 break;
			 
			 
		   case 8:
		   
		      
			 printf("请输入你加入的顶点：\n");getchar();
		   	 scanf("%s",s);
			 id=InsertVex(&g1,s);
			 if(id){
			 	printf("添加成功\n");
			 }	 
			 else {
			 	printf("操作失败，点数太大\n");
			 }
			 getchar();getchar();
			 break;
			 
			 
		   case 9:
		        
			 printf("请输入你删除的顶点：\n");getchar();
		   	 scanf("%s",s);
			 id=DeleteVex(&g1,s);
			 if(id){
			 	printf("删除成功\n");
			 }	 
			 else {
			 	printf("操作失败\n");
			 };
			 getchar();getchar();
			 break;
			 
			 
		   case 10:
		     printf("请输入第一个顶点：\n");getchar();
		   	 scanf("%s",s);
		   	 printf("请输入第二个顶点：\n");getchar();
		   	 scanf("%s",temp);
			 id=InsertArc(&g1,s,temp);
			 if(id){
			 	printf("添加成功\n");
			 }	 
			 else {
			 	printf("操作失败\n");
			 }  
			 getchar();getchar();
			 break;
			 
			 
		   case 11:
		   
		    
			 printf("请输入第一个顶点：\n");getchar();
		   	 scanf("%s",s);
		   	 printf("请输入第二个顶点：\n");getchar();
		   	 scanf("%s",temp);
			 id=DeleteArc(&g1,s,temp);
			 if(id){
			 	printf("删除成功\n");
			 }	 
			 else {
			 	printf("操作失败\n");
			 }    
			 getchar();getchar();
			 break;
			 
			 
		   case 12:    
		   
		    
			 if(DFSTraverse(g1,Visit) ){
			 	printf("遍历成功"); 
			 }
			 else {
			 	printf("操作失败"); 
			 }
			 getchar();getchar();
			 break;
			 
			 
		   case 13:
		   
		         
			 if(BFSTraverse(g1,Visit) ){
			 	printf("遍历成功"); 
			 }
			 else {
			 	printf("操作失败"); 
			 }     
			 getchar();getchar();
			 break;
			 
			  
	       case 14:
		   
		     if(SaveGraph(g1)){
		     	printf("保存成功");
			 }  
			 else{
			 	printf("操作失败");
			 }
			 getchar();getchar();
			 break;
			 
			 
		   case 15:
		   
		        
			 if(LoadGraph(&g1)){
		     	printf("读取成功");
			 }  
			 else{
			 	printf("操作失败");
			 }
			 getchar();getchar();
			 break;
		   case 0:
	         break;
		}//end of switch
  }//end of while
  printf("欢迎下次再使用本系统！\n");
  return 0;
}//end of main()

