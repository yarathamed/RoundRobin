#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *name;
    int starting_time;
    int remaining_time;
} Process;

typedef struct
{
    Process data;
    struct Node* next;
} Node;

typedef struct
{
    Node *head, *tail;
} Queue;

Node* newNode(Process value)
{

    Node* n=malloc(sizeof(Node));
    n->data=value;
    n->next=NULL;
    return n;

}
Queue* init()
{
    Queue *q=malloc(sizeof(Queue));
    q->head=q->tail=NULL;
    return q;
}

int isEmpty(Queue *q)
{
    if(q->head==NULL)
        return 1;
    return -1;

}

Process dequeue(Queue *q)
{
    Node* temp =q->head;
    Process x=temp->data;
    q->head=q->head->next;
    free(temp);
    if(q->head==NULL)
        q->tail=NULL;

    return x;

}

void enqueue(Queue *q, Process value)
{
    Node *n=newNode(value);
    if(q->head==NULL)
        q->head=q->tail=n;
    else
    {
        q->tail->next=n;
        q->tail=n;
    }


}

void destroy(Queue *q)
{
    while(q->head!=NULL)
    {
        Node* temp =q->head;
        q->head=q->head->next;
        free(temp);
    }
    q->tail=NULL;
    free(q);
}
int count=0;
void RoundRobin(char* filename)
{
    int i,j;
    int hours;
    char fline[100];
    Queue* q=init();
    Process p[100];
    FILE* f=fopen(filename, "r");
    fscanf(f,"%[^\n]",fline);
    char *token = strtok(fline, " ");

    while(token!=NULL)
    {
        for(i=0; i<5; i++)
        {
            if(i==4)
            {
                hours=atoi(token);
            }
        }
        token = strtok(NULL, " ");

    }


    if(f!=NULL)
    {
        while(!feof(f))
        {
            p[count].name=malloc(2*sizeof(char));
            fscanf(f,"%s",p[count].name);
            fscanf(f,"%d",&p[count].starting_time);
            fscanf(f,"%d",&p[count].remaining_time);
            count++;

        }
        fclose(f);
    }

    Process t;
    for(i=0; i<hours; i++)
    {
        t.name=malloc(2*sizeof(char));
        for(j=0; j<count; j++)
        {

            if (p[j].starting_time==i)
            {
                enqueue(q,p[j]);
            }
        }

        if(isEmpty(q)==1)
        {
            printf("idle\t(%d-->%d)\n",i,i+1);
            continue;
        }
        else
            t=dequeue(q);
        if(t.remaining_time>0)
        {
            t.remaining_time--;
            if(t.remaining_time>0)
            {
                enqueue(q,t);
                printf("%s\t(%d-->%d)\n",t.name,i,i+1);
            }
            else if(t.remaining_time==0)
            {
                printf("%s\t(%d-->%d) %s aborts\n",t.name,i,i+1,t.name);
            }

        }


    }
    printf("stop\n");
}

int main()
{
    char filename[261];
    puts("Enter file name or Ctrl+Z to exit:");
    puts("----------------------------------");
    while(fgets(filename, 260, stdin) != NULL)
    {
        filename[strlen(filename)-1]='\0';
        if(fopen(filename,"r"))
            RoundRobin(filename);
        else
        {
            puts("File Not Found!");
            puts("----------------------------------");
        }
        puts("Enter file name or Ctrl+Z to exit:");
        puts("----------------------------------");
    }

    return 0;
}
