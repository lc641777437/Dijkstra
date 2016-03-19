#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dijkstra.h"

int main(int argc, char *argv[])
{
    node graphic[MAX_VERTEX_NUM] = {0};
    int sid, did;
    int selnum;

    /*          init grap               */
    if(!InitGraphic(graphic, MAX_VERTEX_NUM))
    {
        UnitGraphic(graphic);
        exit(1);
    }

    printf("/****  Print The Graphic information  ****/");


    /*          dijkstra  process        */
    if(!Dijkstra(graphic))
    {
        UnitGraphic(graphic);
        exit(1);
    }

    while(true)
    {

        ViewGraphic(graphic);//print the graph

        printf("\nEnter source node ID:");
        scanf("%d",&sid);
        printf("\nEnter destination node ID:");
        scanf("%d",&did);

        MinRoute(graphic, sid, did);//打印最优路径
    }

    UnitGraphic(graphic);

    return 0;
}
