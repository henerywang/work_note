#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "./list.h"
 
void list_demo_1()
{
    struct Node
    {
        struct list_head head;
        int value;
    };
 
    struct Node l = {0};
    struct list_head* list = (struct list_head*)&l;
    struct list_head* slider = NULL;
    int i = 0;
 
    INIT_LIST_HEAD(list); //初始化为一个双向循环链表
 
    printf("Insert begin ...\n");
 
    for(i=0; i<5; i++)
    {
        struct Node* n = (struct Node*)malloc(sizeof(struct Node));
 
        n->value = i;
 
        list_add_tail((struct list_head*)n, list);
    }
 
    list_for_each(slider, list)//用一个指针遍历list
    {
        printf("%d\n", ((struct Node*)slider)->value);
    }
 
    printf("Insert end ...\n");
 
    printf("Delete begin ...\n");
 
    list_for_each(slider, list)
    {
        if( ((struct Node*)slider)->value == 3 )
        {
            list_del(slider);
            free(slider);
            break;
        }
    }
 
    list_for_each(slider, list)
    {
        printf("%d\n", ((struct Node*)slider)->value);
    }
 
    printf("Delete end ...\n");
}
 
void list_demo_2()
{
    struct Node
    {
        int value;
        struct list_head head;
    };
 
    struct Node l = {0};
    struct list_head* list = &l.head;
    struct list_head* slider = NULL;
    int i = 0;
 
    INIT_LIST_HEAD(list);
 
    printf("Insert begin ...\n");
 
    for(i=0; i<5; i++)
    {
        struct Node* n = (struct Node*)malloc(sizeof(struct Node));
 
        n->value = i;
 
        list_add(&n->head, list);
    }
 
    list_for_each(slider, list)
    {
        printf("%d\n", list_entry(slider, struct Node, head)->value); //本质为container_of
    }
 
    printf("Insert end ...\n");
 
 
    printf("Delete begin ...\n");
 
    list_for_each(slider, list)
    {
        struct Node* n = list_entry(slider, struct Node, head);
 
        if( n->value == 3 )
        {
            list_del(slider);
            free(n);
            break;
        }
    }
 
    list_for_each(slider, list)
    {
        printf("%d\n", list_entry(slider, struct Node, head)->value);
    }
 
    printf("Delete end ...\n");
}
#define HLIST_HEAD_NUM  0xFF
struct hlist_head hlist_head_arry[HLIST_HEAD_NUM];
typedef struct hnode_t{
    struct hlist_node   list;
    int para;
}hnode;
void hlist_demo_1()
{
    int index = 0;
    for(index = 0; index < HLIST_HEAD_NUM; index++)
        INIT_HLIST_HEAD(&hlist_head_arry[index]);
    hnode *node1 = (hnode *)malloc(sizeof(hnode));
    assert(NULL != node1);
    INIT_HLIST_NODE(&(node1->list));
    node1->para = 55;
    int key = (node1->para) % (HLIST_HEAD_NUM - 4);
    hlist_add_head(&(node1->list), &hlist_head_arry[key]);

    if(hlist_empty(&hlist_head_arry[key])){
        printf("no data in hlist\r\n");
    }else{
        hnode *tpos = NULL;
        struct hlist_node *pos = NULL;
        
        hlist_for_each_entry(tpos, pos, &hlist_head_arry[key], list){
            if(node1->para == tpos->para)
                printf("find data para = %d\r\n", tpos->para);
        }
    }
    
}
int main()
{
     //list_demo_1();
    // list_demo_2();
    hlist_demo_1();
 
    return 0;
}