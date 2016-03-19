#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dijkstra.h"

int g_node_num;/*���ڼ���ʵ�ʽڵ�����ȫ�ֱ���*/
/****************************************
*��������InitGraphic
*������path-ͼ����Ϣ�ļ�·����arr-����ͼ�����飻nsize-�����С
*����ֵ��BOOL-�ɹ�����1�����󷵻�0
*˵��������ͼ����Ϣ�ļ�����ʼ������
*****************************************/
BOOL InitGraphic(node arr[], UINT nsize)
{
    char buf[MAX_STRLEN];
    char *pos;
    char ctemp;
    int ncost;
    int i;
    UINT nid;//��ʱ����ID
    UINT ncid;//��ʱ���Ӷ����ID
    UINT nlinkpos;//���Ӷ��������е�λ��

    memset(arr, 0, sizeof(node)*nsize);//��ֵ0
    FILE *pfile = fopen("test.csv", "r");
    if(NULL == pfile)
    {
        printf("Error opening file.\n");
        return FALSE;
    }
    while(NULL != fgets(buf, MAX_STRLEN, pfile))
    {
        pos = strtok(buf, ":");//��ȡһ�У�������һ��ð��֮ǰ�ı�ţ����ڼ����ڵ�
        nid = atoi(pos);
        if(nid < nsize) {
            arr[nid-1].nID = nid;
            arr[nid-1].pVer = (vertex*)malloc(sizeof(vertex));//����һ������struct
            if(NULL == arr[nid-1].pVer) {
                printf("out of memory!\n");
                return FALSE;
            }
            memset(arr[nid-1].pVer, 0, sizeof(vertex));//��ֵ0
            arr[nid-1].pVer->id = nid;
            g_node_num++;//�ڵ�����1
        } else {
            fprintf(stderr, "access the boundary of setting:%d\n", nid);
        }
    }
    rewind(pfile);//�ļ�ָ����ת����ʼ������ȡ����������ڽڵ�
    for(i=0; i<g_node_num; i++)
    {
        fscanf(pfile, "%d", &nid);//��ȡ��һ���ڵ���
        nlinkpos = 0;//ָʾ�����ڽڵ�ṹ��ĵ�ǰλ��
        while((ctemp=fgetc(pfile)) != ';')
        {
            fscanf(pfile, "%u-%d", &ncid, &ncost);
            if(ncid > nsize || ncost < 0)
            {
                fprintf(stderr, "access the boundary of setting or find negative cost:%u-%d\n", ncid, ncost);
                return FALSE;
            }

            arr[nid-1].pVer->pLinkList[nlinkpos] = arr[ncid-1].pVer;/*���ڽڵ�ָ�����鸳ֵ*/
            arr[nid-1].pVer->nCost[ncid-1] = ncost;/*�˽ڵ㵽���ڽڵ��cost*/
            arr[nid-1].pVer->pmincost = NULL;
            arr[nid-1].pVer->next = NULL;
            nlinkpos++;
        }
    }
    fclose(pfile);
    return TRUE;
}

/*******************************************
*��������ViewGraphic
*������arr-ͼ������
*����ֵ����
*˵������ӡͼ�Ľṹ��Ϣ
*******************************************/
void ViewGraphic(node arr[])
{
    int i, j;
    int nidtemp;//��ʱ�ڵ����
    printf("\nID\tConnceted to-ID:cost");
    for(i=0; i<g_node_num; i++)
    {
        printf("\n%d\t",arr[i].nID);
        for(j=0; arr[i].pVer->pLinkList[j] != NULL; j++)
        {
            nidtemp = arr[i].pVer->pLinkList[j]->id;
            printf("%d:", nidtemp);
            printf("%d ",arr[i].pVer->nCost[nidtemp-1]);
        }
    }
}

/*************************************************
*��������Dijkstra
*������arr-ͼ������
*����ֵ��TRUE-�ɹ���FALSE-ʧ��
*˵�������ν�ÿ���ڵ���Ϊ��ʼ�ڵ㣬����ʣ��ڵ�����֮������·��
*************************************************/
BOOL Dijkstra(node arr[])
{
    UINT i, j, k;
    vertex *pbegin, *ptemp, *ptemp1;
    int *tcost;//���ڴ�������ڵ㵽��ʼ�ڵ����С����
    BOOL *pbDone;//�����жϽڵ��Ƿ������ϵ�����
    int nidtemp;//�뵱ǰ�ڵ����ڵ������ڵ��У�cost��С�Ķ������
    int nmixcost = INFINITE;

    tcost = (int*)malloc(g_node_num * sizeof(int));
    pbDone = (BOOL*)malloc(g_node_num * sizeof(BOOL));
    if(NULL == tcost || NULL == pbDone)
    {
        printf("out of memory\n");
        return FALSE;
    }
    for(i=0; arr[i].pVer!=0; i++)
    {//���ν�ÿ��������Ϊ��ʼ�ڵ�
        for(j=0; j<g_node_num; j++)
        {//��ʼ������
            tcost[j] = INFINITE;//�����ڵ㵽��ʼ�ڵ�Ĵ���
            pbDone[j] = 0;
        }
        pbegin = arr[i].pVer;//��ʼ����
        pbegin->next = (vertex**)malloc(g_node_num * sizeof(vertex*));//����ÿ���������ŵ�ǰ�������id������
        pbegin->pmincost = (int*)malloc(g_node_num * sizeof(int));//����ÿ�����㵽��ʼ�������С��������
        tcost[i] = 0;//��ʼ��
        pbDone[i] = 1;
        pbegin->pmincost[i] = 0;
        ptemp = pbegin;//�趨��ʼ����Ϊ��ǰ����

        while(1)
        {
            for(j=0; ptemp->pLinkList[j]!=0; j++)
            {//������ǰ��������ڽڵ㣬������С����(�ɳڱ�)
                ptemp1 = ptemp->pLinkList[j];
                if(tcost[ptemp1->id-1] > tcost[ptemp->id-1] + ptemp->nCost[ptemp1->id-1] && pbDone[ptemp1->id-1] == 0)
                {
                    tcost[ptemp1->id-1] = tcost[ptemp->id-1] + ptemp->nCost[ptemp1->id-1];
                    pbegin->next[ptemp1->id-1] = ptemp;//�趨������º��ǰ������
                }
            }
            nmixcost = INFINITE;
            for(j=0; j<g_node_num; j++)
            {//�ҳ����º�,���ж����У�������С�Ķ��㣬������Ϊ��ǰ���㡣��һ�������Ż���
                if(pbDone[arr[j].nID-1] != 1 && tcost[arr[j].nID-1] < nmixcost && tcost[arr[j].nID-1] != 0)
                {
                        nmixcost = tcost[arr[j].nID-1];
                        nidtemp = arr[j].nID;
                }
            }
            if(nmixcost == INFINITE)
            {//����ʼ����������нڵ㶼�Ѿ���������ϣ��˳�
                break;
            }
            pbegin->pmincost[nidtemp-1] = nmixcost;
            ptemp = arr[nidtemp-1].pVer;//�����趨��ǰ����
            pbDone[nidtemp-1] = 1;//��ʾ��ǰ�����Ѿ���������ˣ���·���Ѿ���̣�������С
        }
    }

    free(pbDone);

    free(tcost);

    return TRUE;
}

/**********************************************************
*��������MinRoute
*������arr-ͼ�����飻nSrID-��ʼ�ڵ���ţ�nDsID-Ŀ�Ľڵ����
*����ֵ����
*˵��������ͼ�����飬����Dijkstra��������֮�󣬸����趨����ʼ����ֹ�ڵ���ţ���ӡ
*���·������С���ۡ�
***********************************************************/
void MinRoute(node arr[], UINT nSrID, UINT nDsID)
{
    if(nSrID < 0 || nSrID > g_node_num || nDsID < 0 || nDsID > g_node_num)
    {
        printf("Invalid node number!\n");
        return;
    }
    int nid;
    vertex *ptemp = arr[nSrID-1].pVer;
    printf("the total cost is: %d\n", ptemp->pmincost[nDsID-1]);
    printf("the path is:");
    nid = nDsID;
    printf("%d->",arr[nid-1].nID);
    while(ptemp->next[nid-1]->id != arr[nSrID-1].nID)
    {
        nid = ptemp->next[nid-1]->id;//����·��
        printf("%d->",nid);
    }
    printf("%d\n",arr[nSrID-1]);
}
/*****************************************
*��������UnitGraphic
*������arr-ͼ������
*����ֵ����
*˵�����ͷ��ڴ�
*****************************************/
void UnitGraphic(node arr[])
{
    UINT i;
    for(i=0; i<g_node_num; i++)
    {
        if(arr[i].pVer != NULL)
        {
            SAFEFREE(arr[i].pVer->next);
            SAFEFREE(arr[i].pVer->pmincost);
        }
    }
}