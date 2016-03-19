#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

#define MAX_VERTEX_NUM 100                        //��󶥵���
#define MAX_EDGE_NUM 50                            //�������ڵ���
#define INFINITE 1E5                            //��ʾ�ڵ�֮�������ӵ�һ���ϴ����
#define MAX_STRLEN 256                            //����ַ����ֽ���
#define FALSE 0
#define TRUE 1
typedef int BOOL;
typedef unsigned int UINT;

#define SAFEFREE(p) {if(NULL!=(p)) free(p);}

extern int g_node_num;                            //һ��ͼ�У�ʵ�ʽڵ�����ȫ�ֱ���

typedef struct _vertex
{                        //ͨ�õĶ������ݽṹ��
     int id;//id
     struct _vertex *pLinkList[MAX_EDGE_NUM];    //���ڶ����ָ������
     int nCost[MAX_VERTEX_NUM];                    //�����ڶ����Ȩ������
     struct _vertex **next;                        //��ʣ�ඥ��֮������·��
     int *pmincost;                                //��ʣ�ඥ��֮�����С����
}vertex;

typedef struct _node
{                            //���ͼ�Ķ���Ԫ����Ϣ���з�װ
     int nID;
     struct _vertex *pVer;
}node;

BOOL InitGraphic(node arr[], UINT nsize);
void UnitGraphic(node arr[]);
void ViewGraphic(node arr[]);
BOOL Dijkstra(node arr[]);
void MinRoute(node arr[], UINT nSrID, UINT nDsID);

#endif