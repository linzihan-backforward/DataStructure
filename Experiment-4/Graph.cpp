#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//�������״̬����
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2


//Status�Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef int Status;

typedef int QElemType;

typedef struct QNode{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front,rear; //��ͷ����βָ��
}LinkQueue;

Status InitQueue(LinkQueue *Q){
    //����һ���ն���Q
	(*Q).front = (*Q).rear = (QueuePtr)malloc(sizeof(QNode));
	if(!(*Q).front) exit(OVERFLOW);
	(*Q).front->next = NULL;
	return OK;
}

Status QueueEmpty(LinkQueue Q){//��QΪ�ն���,�򷵻�TRUE,���򷵻�FALSE
	if(Q.front == Q.rear) return TRUE;
	else return FALSE;
}

Status EnQueue(LinkQueue *Q, QElemType e){//����Ԫ��eΪQ���µĶ�βԪ��    
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if(!p) //�洢����ʧ��
		exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	(*Q).rear->next = p;
	(*Q).rear = p;
	return OK;
}

Status DeQueue(LinkQueue *Q, QElemType *e){ //�����в���,ɾ��Q�Ķ�ͷԪ��,��e������ֵ,������OK,���򷵻�ERROR
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

#define MAX_VERTEX_NUM 20 //��󶥵���
#define MAX_VERNAME_LEN 10 //����������󳤶�

//����Ԫ�����Ͷ���
typedef char VertexType[MAX_VERNAME_LEN];
typedef int InfoType;

typedef struct ArcNode{
	int adjvex;               //�û���ָ��Ķ���λ��
	struct ArcNode * nextarc; //ָ����һ������ָ��
	InfoType *info;           //�û������Ϣ��ָ��
}ArcNode;

typedef struct VNode{
	ArcNode * firstarc;      //ָ���һ�������ö���Ļ���ָ��
	VertexType data;         //������Ϣ
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct{
	AdjList vertices;
	int vexnum, arcnum;       //ͼ�ĵ�ǰ�������ͻ���
	int kind;                 //ͼ�������־
}ALGraph;

Status CreateGraph(ALGraph * G);//��V��VR�Ķ��幹��ͼG  
Status DestroyGraph(ALGraph * G);//����ͼG   
int LocateVex(ALGraph G, VertexType u);//��u��ͼG�д��ڣ����ض���u��λ����ţ����򷵻�-1 
int FirstAdjVex(ALGraph G, VertexType v);//����v�ĵ�һ���ڽӶ��㣬���vû���ڽӶ��㣬���ؿ�
int NextAdjVex(ALGraph G, VertexType v, VertexType w);//����v�ģ������w����һ���ڽӶ��㣬���w�����һ���ڽӶ��㣬���ؿա�
Status InsertVex(ALGraph * G, VertexType v);//��ͼG�������¶���v
Status DeleteVex(ALGraph * G, VertexType v);//��ͼG��ɾ������v����v��صĻ�
Status InsertArc(ALGraph * G, VertexType v, VertexType w);//��ͼG�����ӻ�<v,w>�����ͼG������ͼ������Ҫ����<w,v>
Status DeleteArc(ALGraph * G, VertexType v, VertexType w);//��ͼG��ɾ����<v,w>�����ͼG������ͼ������Ҫɾ��<w,v>
Status DFSTraverse(ALGraph G, Status (*visit)(VertexType a));//��ͼG������������������� 
Status BFSTraverse(ALGraph G, Status (*visit)(VertexType a));//��ͼG���й��������������
int OutDegree(VNode * i);//����ͼG��i������ĳ���
Status SaveGraph(ALGraph G);//����
Status LoadGraph(ALGraph * G);//��ȡ
Status Visit(VertexType a);//���a
Boolean visited[MAX_VERTEX_NUM]; 
  //���ʱ�־����
Status (*VisitFunc)(VertexType a);
  //��������

/*����ֵ�� Status �ɹ��򷵻�OK
*�������ܣ� ����ͼG*/
Status CreateGraph(ALGraph * G)
{
	int i,j,k;
	int w; //ȨֵW
	VertexType va,vb;//��βVa����ͷVb
	ArcNode *p;
	printf("������ͼ��3�������Ϣ��\n����(0-����ͼ, 1-������, 2-����ͼ, 3-������): ");
	//��ͼ����
	scanf("%d",&(*G).kind);
	while ((*G).kind < 0 || (*G).kind > 3){
		printf("����ֵ�Ƿ���������: ");
		scanf("%d",&(*G).kind);
	}
	//�䶥����
	printf("��������%d���ڣ�: ", MAX_VERTEX_NUM);
	scanf("%d", &(*G).vexnum);
	while ((*G).vexnum < 0 || (*G).vexnum > MAX_VERTEX_NUM){
		printf("����ֵ�Ƿ���������: ");
		scanf("%d",&(*G).vexnum);
	}
	//�����
	printf("��(��)��: ");
	scanf("%d", &(*G).arcnum);
	printf("������%d����������ƻ�ֵ(%d���ַ�����,�ո�ֿ�):\n", (*G).vexnum, MAX_VERNAME_LEN);
	for (i = 0; i < (*G).vexnum; i++) {//�����������Ϣ
		getchar();
		scanf("%s",(*G).vertices[i].data);
		(*G).vertices[i].firstarc = NULL;
	}
	if ((*G).kind % 2) {//1��3Ϊ��
		printf("�밴�����뻡(��)ȨֵW����βVa�ͻ�ͷVb(�ո�ֿ�):\n   W Va Vb\n");
	}
	else {//0��2Ϊͼ
		printf("�밴�����뻡(��)�Ļ�βVa�ͻ�ͷVb(�ո�ֿ�):\n   Va Vb\n");
	}
	for (k = 0; k < (*G).arcnum; k++) {//�����ڽӱ�
		printf("%d: ", k+1);
		if ((*G).kind % 2) {//��
			scanf("%d%s%s", &w, va, vb);
		}
		else {//ͼ
			scanf("%s%s", va, vb);
		}
		i = LocateVex(*G, va); //��β
		j = LocateVex(*G, vb); //��ͷ
		if (i == -1 || j == -1){//���㲻����
			printf("���㲻���ڣ������䣡\n");
			k--;
			continue;
		}
		p = (ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex = j;
		if ((*G).kind % 2){//��
			p->info = (int *)malloc(sizeof(int));
			*(p->info) = w;
		}
		else  {//ͼ
			p->info = NULL;
		}
		p->nextarc = (*G).vertices[i].firstarc; //���ڱ�ͷ
		(*G).vertices[i].firstarc = p;

		//����ͼ�����������������
		if((*G).kind >= 2){
			p = (ArcNode*)malloc(sizeof(ArcNode));
			p->adjvex = i;
			if ((*G).kind == 3) {//������
				p->info = (int*)malloc(sizeof(int));
				*(p->info) = w;
			}
			else {//����ͼ
				p->info = NULL;
			}
			p->nextarc = (*G).vertices[j].firstarc; //���ڱ�ͷ
			(*G).vertices[j].firstarc = p;
		}
	}
	return OK;
}

/*����ֵ��  Status �ɹ��򷵻�OK
*�������ܣ� ����ͼG*/
Status DestroyGraph(ALGraph *G){
	int i;
	ArcNode * p, * q;
	for(i = 0; i < (*G).vexnum; i++){
		p=(*G).vertices[i].firstarc;
		while(p){
			q = p->nextarc;
			if((*G).kind % 2) {//��
				free(p->info);
			}
			free(p);
			p = q;
		}
	}
	(*G).vexnum = 0;
	(*G).arcnum = 0;
	(*G).kind = -1;//��-1����ͼ������
	return OK;
}
/*����ֵ�� int
*�������ܣ� ��u��ͼG�д��ڣ����ض���u��λ����ţ����򷵻�-1*/
int LocateVex(ALGraph G, VertexType u)
{
	int i;
	for(i = 0; i < G.vexnum; i++){
		if(strcmp(u,G.vertices[i].data) == 0){ //������ͬ 
			return i;
		}
	}
	return -1;//δ�ҵ��򷵻�-1
}

/*����ֵ�� int
*�������ܣ� ����v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ���,�򷵻�-1*/
int FirstAdjVex(ALGraph G, VertexType v)
{
	ArcNode *p;
	int v1;
	v1 = LocateVex(G,v);//��ȡv��ͼG�е����v1
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

/*����ֵ�� int
*�������ܣ� ����v��(�����w��)��һ���ڽӶ������ţ�
*			��w��v�����һ���ڽӵ�,�򷵻�-1*/
int NextAdjVex(ALGraph G,VertexType v,VertexType w){
	ArcNode *p;
	int v1, w1;
	v1 = LocateVex(G,v); //��ȡv��ͼG�е����v1
	w1 = LocateVex(G,w); //��ȡw��ͼG�е����w1
	if (v1 == -1){//���㲻����
		return(-2);
	}
	if (w1 == -1){//�ڽӵ㲻����
		return(-3);
	}
	p = G.vertices[v1].firstarc;
	while (p && p->adjvex != w1){//ָ��p��������ָ���㲻��w
		p = p->nextarc;
	}
	//û�ҵ�w��w�����һ���ڽӵ�
	if(!p || !p->nextarc){
		return -1;
	}
	else{//����v��(�����w��)��һ���ڽӶ�������
		return p->nextarc->adjvex;
	}
}
/*����ֵ��  Status
*�������ܣ� ��ͼG�������¶���v*/
Status InsertVex(ALGraph *G, VertexType v){
	if((*G).vexnum == MAX_VERTEX_NUM){//�����������ֵ
		return ERROR;
	}
	//�����¶���
	strcpy((*G).vertices[(*G).vexnum].data, v);
	(*G).vertices[(*G).vexnum].firstarc=NULL;
	(*G).vexnum++; //ͼG�Ķ�������1
	return OK;
 }

/*����ֵ��  Status �ɹ�����OK
*�������ܣ� ɾ��G�ж���v������صĻ�*/

Status DeleteVex(ALGraph *G, VertexType v){
	int i, j;
	ArcNode *p, *q;
	j = LocateVex(*G, v); //��ȡ����v�����
	if(j == -1) {//v����ͼG�Ķ���
		return ERROR;
	}
	//ɾ����vΪ���ȵĻ����
    p = (*G).vertices[j].firstarc;
	while(p){
		q = p;
		p = p->nextarc;
		if((*G).kind%2) {//��
			free(q->info);
		}
		free(q);
		(*G).arcnum--; //���������1
	}

	//�������ж���
	(*G).vexnum--; //��������1
	for(i = j; i < (*G).vexnum; i++) //����v����Ķ���ǰ��
	{
		(*G).vertices[i] = (*G).vertices[i+1];
	}

	//ɾ����vΪ��ȵĻ�������޸Ļ���ָ����λ��ֵ
	for(i = 0; i < (*G).vexnum; i++){
		p = (*G).vertices[i].firstarc; //ָ���1�������
		while(p){ //�л����
			if(p->adjvex == j){//�û�ָ��ɾ���
				if(p == (*G).vertices[i].firstarc){ //��ɾ����ǵ�1�����
					(*G).vertices[i].firstarc = p->nextarc;
					if((*G).kind%2) {//��
						free(p->info);
					}
					free(p);
					p = (*G).vertices[i].firstarc;
					if((*G).kind < 2){//����ͼ���ټ�һ��
						(*G).arcnum--; //���������1
					}
				}
				else{
					q->nextarc = p->nextarc;
					if((*G).kind % 2) {//��
						free(p->info);
					}
					free(p);
					p = q->nextarc;
					if((*G).kind < 2){//�������ټ�һ��
						(*G).arcnum--; //���������1
					}
				}
			}
			else{//�û���ָ��ɾ���

				if(p->adjvex > j){//�û���ָԪ��λ�������ɾ������֮��
					p->adjvex--;//���Ļ���ָ����λ�����
				}
				q = p;
				p = p->nextarc;//������һ����
			}
		}
	}
	return OK;
}

/*����ֵ��  Status �ɹ�����OK��
*�������ܣ���ͼG�����ӻ�<v,w>�����ͼG������ͼ������Ҫ����<w,v>*/
Status InsertArc(ALGraph *G,VertexType v,VertexType w){
	ArcNode *p;
	int w1, i, j;
	i = LocateVex(*G, v); //��ȡvλ�����
	j = LocateVex(*G, w); //��ȡwλ�����
	if(i == -1 || j == -1){//δ�ҵ���Ӧ����
		return ERROR;
	}

	//������v-w
	(*G).arcnum++;
	if((*G).kind % 2){ //��Ҫ��Ȩֵ
		printf("�����뻡(��)%s->%s��Ȩֵ: ", v, w);
		scanf("%d", &w1);
	}
	p=(ArcNode*)malloc(sizeof(ArcNode));
	p->adjvex = j;
	if((*G).kind % 2) {//��
		p->info = (int *)malloc(sizeof(int));
		*(p->info) = w1;
	}
	else{
		p->info=NULL;
	}
	p->nextarc = (*G).vertices[i].firstarc;
	(*G).vertices[i].firstarc = p;

	//����ͼ��Ҫ�ٽ�����w-v
	if((*G).kind >= 2){
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = i;
		if((*G).kind == 3) {//������
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

/*����ֵ��  Status �ɹ�����OK��
*�������ܣ� ��ͼG��ɾ����<v,w>�����ͼG������ͼ������Ҫɾ��<w,v>*/
Status DeleteArc(ALGraph * G,VertexType v,VertexType w){
	ArcNode *p, *q;
	int i, j;
	i = LocateVex(*G, v); //����v���
	j = LocateVex(*G, w); //����w���
	if(i < 0 || j < 0){
		return ERROR;
	}

	//ɾ����<v,w>
	p = (*G).vertices[i].firstarc;
	while(p && p->adjvex != j){ //p��������ָ֮�����Ǵ�ɾ����<v,w>
	 //pָ����һ����
		q = p;
		p = p->nextarc;
	}
	if(p && p->adjvex == j) {//�ҵ���<v,w>
		if(p == (*G).vertices[i].firstarc){ //p��ָ�ǵ�1����
			(*G).vertices[i].firstarc = p->nextarc;//ָ����һ����
		}
		else{//ָ����һ����
			q->nextarc = p->nextarc;
		}
		if((*G).kind % 2){//��Ҫ���ͷ�Ȩֵ
			free(p->info);
		}
		free(p); //�ͷŴ˽��
		(*G).arcnum--; //���������1
	}

	//����ͼҪɾ���Գƻ�<w,v>
	if((*G).kind >= 2){
		p = (*G).vertices[j].firstarc;
		while(p && p->adjvex != i) {//p��������ָ֮�����Ǵ�ɾ����<w,v> 
			q = p;//pָ����һ���� 
			p = p->nextarc;
		}
		if(p && p->adjvex == i){ //�ҵ���<w,v>
			if(p == (*G).vertices[j].firstarc){ //p��ָ�ǵ�1����
				(*G).vertices[j].firstarc=p->nextarc;//ָ����һ����
			}
			else{//ָ����һ����
				q->nextarc=p->nextarc;
			}
			if((*G).kind % 2){//��Ҫ���ͷ�Ȩֵ
				free(p->info);
			}
			free(p); //�ͷŴ˽��
		}
	}
	return OK;
 }

/*����ֵ��   ��
*�������ܣ� �ӵ�v����������ݹ��������ȱ���ͼG��*/

void DFS(ALGraph G,int v)
{
	int w;
	VertexType v1, w1;
	strcpy(v1, G.vertices[v].data);
	visited[v] = TRUE; //���÷��ʱ�־ΪTRUE(�ѷ���)
	VisitFunc(G.vertices[v].data); /* ���ʵ�v������ */
	for(w = FirstAdjVex(G,v1); w >= 0; w = NextAdjVex(G, v1, strcpy(w1, G.vertices[w].data))){
		if(!visited[w]){
			DFS(G,w); //��v����δ���ʵ��ڽӵ�w�ݹ����DFS
		}
	}
}

/*����ֵ��  Status �ɹ�����OK��
*�������ܣ� ��ͼG������������������������ζ�ͼ�е�ÿһ������ʹ�ú�
*				��visit����һ�Σ��ҽ�����һ��*/
Status DFSTraverse(ALGraph G, Status (*Visit)(VertexType a)){
	int v;
	VisitFunc = Visit; //ʹ��ȫ�ֱ���VisitFunc,ʹDFS�����躯��ָ�����
	for(v = 0; v < G.vexnum; v++){
		visited[v]=FALSE; //���ʱ�־�����ʼ��
	}
	for(v = 0; v < G.vexnum; v++){
		if(!visited[v]){
			DFS(G,v); //����δ���ʵĶ������DFS
		}
	}
	return OK;
}

/*����ֵ��  Status �ɹ�����OK��
*�������ܣ� ��������ȷǵݹ����ͼG��*/
Status BFSTraverse(ALGraph G, Status (*Visit)(VertexType a)){
	int v, u, w;
	VertexType u1, w1;
	LinkQueue Q;
	for(v = 0; v < G.vexnum; ++v) visited[v]=FALSE;
    InitQueue(&Q); //�ÿյĸ�������Q
    for(v = 0; v < G.vexnum; ++v)
		if(!visited[v]) {//v��δ����
			visited[v] = TRUE;
			Visit(G.vertices[v].data);
			EnQueue(&Q, v); //v�����
			while(!QueueEmpty(Q)){
				DeQueue(&Q, &u); //��ͷԪ�س��Ӳ���Ϊu
				strcpy(u1, G.vertices[u].data);
				for(w = FirstAdjVex(G,u1); w >= 0; w = NextAdjVex(G, u1, strcpy(w1, G.vertices[w].data)))
					if(!visited[w]){ //wΪu����δ���ʵ��ڽӶ���
						visited[w] = TRUE;
						Visit(G.vertices[w].data);
						EnQueue(&Q,w); //w���
					}
			}
		}
	return OK;
}

/*����ֵ��   int ͼG�ĵ�i���������
*�������ܣ� ����ͼG�ĵ�i���������*/
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

/*����ֵ�� Status
*�������ܣ� ��ȡ���Ա�*/

Status LoadGraph(ALGraph * G){
	int i, k = 0, num;
	FILE *fp;
	ArcNode *p;
	char filename[30];
	printf("�������ȡ�ļ���: ");
	scanf("%s", &filename);
	if ((fp = fopen(filename,"r")) == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n ");
		return ERROR;
	}
	//��ȡͼ������Ϣ
	fread(&G->kind, sizeof(int), 1, fp);
	fread(&G->vexnum, sizeof(int), 1, fp);
	fread(&G->arcnum, sizeof(int), 1, fp);
	//��ȡ�ڽӱ�
	while(fread(G->vertices[k].data, sizeof(char), MAX_VERTEX_NUM, fp)){//�ж���
		fread(&num, sizeof(int), 1, fp);
		if (num == 0){
			G->vertices[k].firstarc = NULL;
		}
		else{
			G->vertices[k].firstarc = NULL;
			for (i = 0; i < num; i++){
				p = (ArcNode *)malloc(sizeof(ArcNode));
				fread(&(p->adjvex), sizeof(int), 1, fp);
				if ((*G).kind % 2){//��
					p->info = (int *)malloc(sizeof(int));
					fread(p->info, sizeof(InfoType), 1, fp);
				}
				else  {//ͼ
					p->info = NULL;
				}
				p->nextarc = (*G).vertices[k].firstarc; //���ڱ�ͷ
				(*G).vertices[k].firstarc = p;
			}
		}
		k++;
	}
	fclose(fp);
	return OK;
}

/*����ֵ�� Status
*�������ܣ� �������Ա�*/

Status SaveGraph(ALGraph G){
	int i, num;
	FILE  *fp;
	char filename[30];
	ArcNode *p;
	printf("�����뱣���ļ����� ");
    scanf("%s",&filename);

    //д�ļ��ķ���
	if ((fp = fopen(filename, "w")) == NULL)
	{
		printf("�ļ���ʧ��\n ");
		return ERROR;
	}
	//����ͼ������Ϣ
	fwrite(&G.kind, sizeof(int), 1, fp);
	fwrite(&G.vexnum, sizeof(int), 1, fp);
	fwrite(&G.arcnum, sizeof(int), 1, fp);
	//�����ڽӱ�
	for (i = 0; i < G.vexnum; i++){
		fwrite(G.vertices[i].data, sizeof(char), MAX_VERTEX_NUM, fp);
		num = OutDegree(&(G.vertices[i]));
		fwrite(&num, sizeof(int), 1, fp);
		if ((p = G.vertices[i].firstarc) != NULL){
			fwrite(&p->adjvex, sizeof(int), 1, fp);
			if (G.kind % 2){//��	
				fwrite(p->info, sizeof(int), 1, fp);
			}
			while ((p = p->nextarc) != NULL){
				fwrite(&p->adjvex, sizeof(int), 1, fp);
				if (G.kind % 2){//��
					fwrite(p->info, sizeof(int), 1, fp);
				}
			}
		}
	}
	fclose(fp);
	return OK;
}

/*����ֵ�� Status ����OK
*�������ܣ� ���a*/

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
	printf("                                       ͼ�����˵�                        \n");
	printf("------------------------------------------------------------------------------------------\n");
	printf("    	  1. CreateGraph������ͼ��       9. DeleteVex��ɾ�����㣩\n");
	printf("    	  2. DestroyGraph������ͼ��      10. InsertArc�����뻡��\n");
	printf("    	  3. LocateVex   �����Ҷ��㣩    11. DeleteArc��ɾ������\n");
	printf("    	  4. GetVex     ����ö���ֵ��   \n");
	printf("    	  5. PutVex     �����㸳ֵ��     12. DFSTraverse �������������������\n");
	printf("    	  6. FirstAdjVex����õ�һ�ڽӵ㣩13. BFSTraverse  ���������������������\n");
	printf("    	  7. NextAdjVex �������һ�ڽӵ㣩     \n");
	printf("    	  8. InsertVex  �����붥�㣩        \n");
	printf("    	  0. Exit      ���˳�ϵͳ��\n");
	printf("          14.Save      ����ͼ���浽�ļ���   15.Load             �����ļ��ж�ȡͼ��   \n");
	printf("--------------------------------------------------------------------------------------------\n");
	printf("    ��ѡ����Ĳ���[0~15]:");
	scanf("%d",&op);
	    switch(op){
		   case 1:
		   	
			 if(CreateGraph(&g1)==OK) printf("ͼ1�����ɹ���\n");
			     else printf("������1����ʧ�ܣ�\n");
			 getchar();getchar();
			 break;
			 
			 
		   case 2:
		   	
		   	
			 if(DestroyGraph(&g1)==OK) printf("ͼ1ɾ���ɹ���\n");
			     else printf("ͼ1ɾ��ʧ�ܣ�\n");     
			 getchar();getchar();
			 break;
			 
			 
		   case 3: 
		     
		   	 printf("��������Ҫ���ҵĶ��㣺\n");getchar();
		   	 scanf("%s",s);
			 id=LocateVex(g1,s);
			 if(id==-1){
			 	printf("�޴˶���\n");
			 }	 
			 else {
			 	printf("�˶�����Ϊ��%d\n",id);
			 }   
			 getchar();getchar();
			 break;
			 
			 
		   case 4: 
		   
		   
			 printf("��������Ҫ���ֵ�Ķ��㣺\n");getchar();
		   	 scanf("%s",s);
			 id=LocateVex(g1,s);
			 if(id==-1){
			 	printf("�޴˶���\n");
			 }	 
			 else {
			 	printf("�˶���ֵΪ��%s\n",g1.vertices[id].data);
			 }      
			 getchar();getchar();
			 break;
			 
			 
		   case 5:
		   	
		   	 
			 printf("��������Ҫ��ֵ�Ķ��㣺\n");getchar();
		   	 scanf("%s",s);
		   	 printf("�������µ�ֵ��\n");getchar();
		   	 scanf("%s",temp);
			 id=LocateVex(g1,s);
			 if(id==-1){
			 	printf("�޴˶���\n");
			 }	 
			 else {
			 	strcpy(g1.vertices[id].data,temp);
			 	printf("�޸ĳɹ�");
			 }          
			 getchar();getchar();
			 break;
			 
			 
		   case 6:
		   	
		   	 printf("��������Ҫ�����Ķ��㣺\n");getchar();
		   	 scanf("%s",s);
			 id=FirstAdjVex(g1,s);
			 if(id==-1){
			 	printf("��������\n");
			 }	 
			 else if(id==-2){
			 	printf("�������ڽӵ�\n");
			 } 
			 else {
			 	printf("��һ�ڽӵ�Ϊ���Ϊ%d\n",id);
			 }   
			 getchar();getchar();
			 break;
			 
			 
		   case 7:  
		   
		      
			 printf("��������Ҫ�����Ķ��㣺\n");getchar();
		   	 scanf("%s",s);
		   	 printf("������һ�������ڽӵ㣺\n");getchar();
		   	 scanf("%s",temp);
			 id=NextAdjVex(g1,s,temp);
			 if(id==-1){
			 	printf("����һ���ڽӵ�\n");
			 }	 
			 else if(id==-2){
			 	printf("�ö��㲻����\n");
			 }
			 else if(id==-3){
			 	printf("���ڽӵ㲻����\n");
			 }
			 else{
			 	printf("��һ�ڽӵ�Ϊ���Ϊ%d\n",id);
			 }
			 getchar();getchar();
			 break;
			 
			 
		   case 8:
		   
		      
			 printf("�����������Ķ��㣺\n");getchar();
		   	 scanf("%s",s);
			 id=InsertVex(&g1,s);
			 if(id){
			 	printf("��ӳɹ�\n");
			 }	 
			 else {
			 	printf("����ʧ�ܣ�����̫��\n");
			 }
			 getchar();getchar();
			 break;
			 
			 
		   case 9:
		        
			 printf("��������ɾ���Ķ��㣺\n");getchar();
		   	 scanf("%s",s);
			 id=DeleteVex(&g1,s);
			 if(id){
			 	printf("ɾ���ɹ�\n");
			 }	 
			 else {
			 	printf("����ʧ��\n");
			 };
			 getchar();getchar();
			 break;
			 
			 
		   case 10:
		     printf("�������һ�����㣺\n");getchar();
		   	 scanf("%s",s);
		   	 printf("������ڶ������㣺\n");getchar();
		   	 scanf("%s",temp);
			 id=InsertArc(&g1,s,temp);
			 if(id){
			 	printf("��ӳɹ�\n");
			 }	 
			 else {
			 	printf("����ʧ��\n");
			 }  
			 getchar();getchar();
			 break;
			 
			 
		   case 11:
		   
		    
			 printf("�������һ�����㣺\n");getchar();
		   	 scanf("%s",s);
		   	 printf("������ڶ������㣺\n");getchar();
		   	 scanf("%s",temp);
			 id=DeleteArc(&g1,s,temp);
			 if(id){
			 	printf("ɾ���ɹ�\n");
			 }	 
			 else {
			 	printf("����ʧ��\n");
			 }    
			 getchar();getchar();
			 break;
			 
			 
		   case 12:    
		   
		    
			 if(DFSTraverse(g1,Visit) ){
			 	printf("�����ɹ�"); 
			 }
			 else {
			 	printf("����ʧ��"); 
			 }
			 getchar();getchar();
			 break;
			 
			 
		   case 13:
		   
		         
			 if(BFSTraverse(g1,Visit) ){
			 	printf("�����ɹ�"); 
			 }
			 else {
			 	printf("����ʧ��"); 
			 }     
			 getchar();getchar();
			 break;
			 
			  
	       case 14:
		   
		     if(SaveGraph(g1)){
		     	printf("����ɹ�");
			 }  
			 else{
			 	printf("����ʧ��");
			 }
			 getchar();getchar();
			 break;
			 
			 
		   case 15:
		   
		        
			 if(LoadGraph(&g1)){
		     	printf("��ȡ�ɹ�");
			 }  
			 else{
			 	printf("����ʧ��");
			 }
			 getchar();getchar();
			 break;
		   case 0:
	         break;
		}//end of switch
  }//end of while
  printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
  return 0;
}//end of main()

