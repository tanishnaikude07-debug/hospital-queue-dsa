#include <stdio.h>
#include <string.h>

#define N 10

int tokencounter = 1;

typedef struct patient
{
    int token;
    char name[50];
    int age;
    char ailment[50];
} patient;

typedef struct queue
{
    patient a[N];
    int front, rear;
} queue;

typedef struct servedlog
{
    patient a[N];
    int count;
} servedlog;

void enqueue(queue *q, patient p)
{
    if (q->rear == N - 1)
        printf("\nQueue overflow. Cannot add more patients.");
    else
    {
        if (q->rear == -1)
        {
            q->front = 0;
        }
        q->rear++;
        q->a[q->rear] = p;
    }
}

int isempty(queue *q)
{
    if (q->front == -1 || q->front > q->rear)
        return 1;
    else
        return 0;
}

patient dequeue(queue *q)
{
    patient p;
    p.token = -1;
    if (isempty(q))
    {
        return p;
    }
    else
    {
        p = q->a[q->front];
        q->front++;
        return p;
    }
}

void display(queue *q)
{
    int i, pos;
    if (isempty(q))
        printf("\nWaiting list is empty.");
    else
    {
        printf("\n--- Waiting List ---");
        printf("\nPos  Token  Name                 Age  Ailment");
        pos = 1;
        for (i = q->front; i <= q->rear; i++)
        {
            printf("\n%-4d %-6d %-20s %-4d %s", pos, q->a[i].token, q->a[i].name, q->a[i].age, q->a[i].ailment);
            pos++;
        }
        printf("\n--------------------");
    }
}

void addpatient(queue *q)
{
    patient p;
    p.token = tokencounter;
    tokencounter++;
    printf("\nEnter Patient Name: ");
    scanf(" %[^\n]", p.name);
    printf("Enter Patient Age: ");
    scanf("%d", &p.age);
    printf("Enter Ailment: ");
    scanf(" %[^\n]", p.ailment);
    enqueue(q, p);
    printf("\nPatient %s added.\nToken Number: %d", p.name, p.token);
}

void callnextpatient(queue *q, servedlog *log)
{
    patient served, next;

    if (isempty(q))
    {
        printf("\nNo patients in the waiting list.");
        return;
    }

    served = dequeue(q);

    if (log->count < N)
    {
        log->a[log->count] = served;
        log->count++;
    }

    printf("\nDone serving: %s\nToken: %d\nAge: %d\nAilment: %s", served.name, served.token, served.age, served.ailment);
    printf("\nPatient %s has been moved to served list.", served.name);

    if (!isempty(q))
    {
        next = q->a[q->front];
        printf("\nNext patient called: %s\nToken: %d", next.name, next.token);
    }
    else
    {
        printf("\nNo more patients in the waiting list.");
    }
}

void currentlyserving(queue *q)
{
    if (isempty(q))
    {
        printf("\nNo patient is currently being served.");
        return;
    }
    printf("\nCurrently Serving:");
    printf("\nToken: %d", q->a[q->front].token);
    printf("\nName: %s", q->a[q->front].name);
    printf("\nAge: %d", q->a[q->front].age);
    printf("\nAilment: %s", q->a[q->front].ailment);
}

void searchpatient(queue *q, servedlog *log)
{
    int ch, i, found, pos;
    int searchtoken;
    char searchname[50];
    char searchailment[50];

    printf("\nSearch by:");
    printf("\n1. Token");
    printf("\n2. Name");
    printf("\n3. Ailment");
    printf("\nEnter choice: ");
    scanf("%d", &ch);

    found = 0;

    if (ch == 1)
    {
        printf("Enter Token Number to search: ");
        scanf("%d", &searchtoken);

        printf("\n--- Search result in Waiting List ---");
        if (!isempty(q))
        {
            pos = 1;
            for (i = q->front; i <= q->rear; i++)
            {
                if (q->a[i].token == searchtoken)
                {
                    printf("\n[WAITING]");
                    printf("\nPosition in queue: %d", pos);
                    printf("\nToken: %d\nName: %s\nAge: %d\nAilment: %s", q->a[i].token, q->a[i].name, q->a[i].age, q->a[i].ailment);
                    found = 1;
                    break;
                }
                pos++;
            }
        }

        printf("\n--- Search result in Served Log ---");
        for (i = 0; i < log->count; i++)
        {
            if (log->a[i].token == searchtoken)
            {
                printf("\n[SERVED]");
                printf("\nToken: %d\nName: %s\nAge: %d\nAilment: %s", log->a[i].token, log->a[i].name, log->a[i].age, log->a[i].ailment);
                found = 1;
                break;
            }
        }
    }
    else if (ch == 2)
    {
        printf("Enter Patient Name to search: ");
        scanf(" %[^\n]", searchname);

        printf("\n--- Search result in Waiting List ---");
        if (!isempty(q))
        {
            pos = 1;
            for (i = q->front; i <= q->rear; i++)
            {
                if (strcmp(q->a[i].name, searchname) == 0)
                {
                    printf("\n[WAITING]");
                    printf("\nPosition in queue: %d", pos);
                    printf("\nToken: %d\nName: %s\nAge: %d\nAilment: %s", q->a[i].token, q->a[i].name, q->a[i].age, q->a[i].ailment);
                    found = 1;
                    break;
                }
                pos++;
            }
        }

        printf("\n--- Search result in Served Log ---");
        for (i = 0; i < log->count; i++)
        {
            if (strcmp(log->a[i].name, searchname) == 0)
            {
                printf("\n[SERVED]");
                printf("\nToken: %d\nName: %s\nAge: %d\nAilment: %s", log->a[i].token, log->a[i].name, log->a[i].age, log->a[i].ailment);
                found = 1;
                break;
            }
        }
    }
    else if (ch == 3)
    {
        printf("Enter Ailment to search: ");
        scanf(" %[^\n]", searchailment);

        printf("\n--- Waiting patients with ailment: %s ---", searchailment);
        if (!isempty(q))
        {
            for (i = q->front; i <= q->rear; i++)
            {
                if (strcmp(q->a[i].ailment, searchailment) == 0)
                {
                    printf("\n[WAITING]");
                    printf("\nToken: %d\nName: %s\nAge: %d", q->a[i].token, q->a[i].name, q->a[i].age);
                    found = 1;
                }
            }
        }

        printf("\n--- Served patients with ailment: %s ---", searchailment);
        for (i = 0; i < log->count; i++)
        {
            if (strcmp(log->a[i].ailment, searchailment) == 0)
            {
                printf("\n[SERVED]");
                printf("\nToken: %d\nName: %s\nAge: %d", log->a[i].token, log->a[i].name, log->a[i].age);
                found = 1;
            }
        }
    }
    else
    {
        printf("\nInvalid choice.");
        return;
    }

    if (!found)
        printf("\nNo patient found.");
}

void viewcount(queue *q, servedlog *log)
{
    int waiting;
    if (isempty(q))
        waiting = 0;
    else
        waiting = q->rear - q->front + 1;

    printf("\nTotal patients waiting: %d", waiting);
    printf("\nTotal patients served: %d", log->count);
}

void emergencyoverride(queue *q)
{
    patient p;
    int i;

    if (q->rear == N - 1)
    {
        printf("\nQueue is full. Cannot add emergency patient.");
        return;
    }

    p.token = tokencounter;
    tokencounter++;
    printf("\nEnter Emergency Patient Name: ");
    scanf(" %[^\n]", p.name);
    printf("Enter Patient Age: ");
    scanf("%d", &p.age);
    printf("Enter Ailment: ");
    scanf(" %[^\n]", p.ailment);

    if (isempty(q))
    {
        enqueue(q, p);
        printf("\nEmergency patient %s added.\nToken: %d\nNo one else was waiting.", p.name, p.token);
        return;
    }

    q->rear++;
    for (i = q->rear; i > q->front; i--)
    {
        q->a[i] = q->a[i - 1];
    }
    q->a[q->front] = p;

    printf("\nEmergency patient %s inserted at the front.\nToken: %d", p.name, p.token);
    printf("\nPrevious patient shifted to position 2.");
}

void viewservedlog(servedlog *log)
{
    int i;
    if (log->count == 0)
    {
        printf("\nNo patients have been served yet.");
        return;
    }
    printf("\n--- Served Patients Log ---");
    printf("\nToken  Name                 Age  Ailment");
    for (i = 0; i < log->count; i++)
    {
        printf("\n%-6d %-20s %-4d %s", log->a[i].token, log->a[i].name, log->a[i].age, log->a[i].ailment);
    }
    printf("\n---------------------------");
}

int main()
{
    int ch;
    queue q;
    servedlog log;

    q.front = -1;
    q.rear = -1;
    log.count = 0;

    printf("\n=============================");
    printf("\n  Hospital Patient Record System");
    printf("\n=============================");

    while (1)
    {
        printf("\n\nMenu:");
        printf("\n1. Add Patient");
        printf("\n2. Call Next Patient");
        printf("\n3. Currently Serving");
        printf("\n4. View Waiting List");
        printf("\n5. Search Patient");
        printf("\n6. View Patient Count");
        printf("\n7. Emergency Override");
        printf("\n8. View Served Patients Log");
        printf("\n9. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &ch);

        if (ch == 9)
        {
            printf("\nExiting system. Goodbye!\n");
            break;
        }

        switch (ch)
        {
        case 1:
            addpatient(&q);
            break;
        case 2:
            callnextpatient(&q, &log);
            break;
        case 3:
            currentlyserving(&q);
            break;
        case 4:
            display(&q);
            break;
        case 5:
            searchpatient(&q, &log);
            break;
        case 6:
            viewcount(&q, &log);
            break;
        case 7:
            emergencyoverride(&q);
            break;
        case 8:
            viewservedlog(&log);
            break;
        default:
            printf("\nInvalid choice. Please try again.");
        }
    }

    return 0;
}
