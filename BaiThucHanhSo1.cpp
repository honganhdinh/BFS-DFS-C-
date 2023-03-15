#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#define MAXSIZE 100
#define MAX 20
using namespace std;

int c[MAXSIZE];
char vertex[MAXSIZE];
int a[MAXSIZE][MAXSIZE];
bool visited[MAXSIZE];
int dfs[MAXSIZE];
int sdfs[MAXSIZE];
int sbfs[MAXSIZE];
int ndfs=0;
int bfs[MAXSIZE];
int nbfs=0;
int n;
int startVertex, endVertex;

struct Node
{
    int info;
    Node *link;
};

void readMatrixFromFile(int a[][MAXSIZE], int &n)
{
    ifstream myfile;
    myfile.open("myfile.txt");
    if (myfile.is_open())
    {
        myfile >> n;

        for (int i = 0; i < n; i++)
        {
            myfile >> vertex[i];
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                myfile >> a[i][j];
            }
        }
        myfile.close();
        cout << "Doc ma tran thanh cong" << endl;
    }
    else
    {
        cout << "Khong mo duoc file" << endl;
    }
}

void displayMatrixFromFile(int a[][MAXSIZE], int n)
{
    cout << "\t";
    for (int i = 0; i < n; i++)
    {
        cout << vertex[i] << "\t";
    }
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << vertex[i] << "\t";
        for (int j = 0; j < n; j++)
        {
            cout << a[i][j] << "\t";
        }
        cout << endl;
    }
}
/* DFS USE STACK (IN AFTER OUT FIRST) */
Node* st;
void Init_Stack() {
    st = NULL;
}

bool isEmpty_Stack() {
    if(st == NULL) 
        return true;
    return false;
}

void push_Stack(int s) {
    Node *p = new Node;
    if (p == NULL) return;
    p -> info = s;
    p -> link = st;
    st = p;
}

void pop_Stack(int &v) {
    Node *p = st;
    v = p -> info;
    st = st -> link;
    delete p;
}

void initEdgesStatus() {
    for(int i = 0; i < n; i++) {
        //visited[i] = false;
        c[i] = 1;
    }
}
void DepthFirstSearch(int startVertex, int endVertex) {
    initEdgesStatus();
    Init_Stack();
    push_Stack(startVertex);
    dfs[ndfs] = startVertex;
    //visited[startVertex] = true;
    c[startVertex] = 0;
    int v = -1;
    int u = startVertex;

    while(!isEmpty_Stack()) {
        if (v == n)
            pop_Stack(u);
        for(v = 0; v < n; v ++) {
            if (a[u][v] != 0 && c[v] == 1 /*visited[i] == false*/) {
                //push_Stack(u);
                push_Stack(v);
                dfs[v] = u;
                //visited[i] = true;
                c[v] = 0;

                if(v == endVertex)
                    return;
                u = v;
                break;
            }
        }
    }

}
void displayDepthFirstSearch(int startVertex, int endVertex) {
    int i;
    i=0;
    if(dfs[endVertex] == 0) {
        cout << "Khong tim thay duong di" << endl;
    } else {
        while(endVertex != startVertex) {
            sdfs[i] = endVertex;
            endVertex = dfs[endVertex];
            i ++;
        }
        cout << "Depth First Search: ";
        for (int j = i; j >= 0; j--) {
            cout << vertex[sdfs[j]] << " -> ";
        }
    }
}
/* BFS USE QUEUE (IN FIRST OUT FIRST) */
Node *front, *rear;
void Init_Queue() {
    front = rear = NULL;
}
bool isEmpty_Queue() {
    if (front == NULL)
        return true;
    return false;
}

void push_Queue(int x) {
    Node *p = new Node;
    p -> info = x;
    p -> link = NULL;
    if(rear == NULL) 
        front = p;
    else
        rear -> link = p;
    rear = p;
}

void pop_Queue(int &x) {
    if (front != NULL) {
        Node *p = front;
        x = p ->info;
        front = front -> link;
        if(front == NULL)
            rear = NULL;
        delete p;
    }
}
void BreadthFirstSearch(int startVertex, int endVertex) {
    initEdgesStatus();
    Init_Queue();
    push_Queue(startVertex);
    bool check=false;
    //visited[startVertex] = true;
    c[startVertex]=0;
    int p, count = 0;

    while(!isEmpty_Queue()) {
        pop_Queue(p);

        if(count < n && check == false) {
            for(int i = 0; i < n; i++) {
                if(c[i] == 1 && a[p][i] == 1) {
                    push_Queue(i);
                    // visited[i] = true;
                    c[i] = 0;
                    bfs[i] = p;
                    count ++;
                    if(i == endVertex) {
                        check = true;
                        break;
                    }
                }
            }
        }
    }
}
void displayBreadthFirstSearch(int startVertex, int endVertex) {
    int i;
    i=0;
    if (bfs[endVertex] == 0) {
        cout << "Khong tim thay duong di" << endl;
    } else {
        while(endVertex != startVertex) {
            sbfs[i] = endVertex;
            endVertex = bfs[endVertex];
            i ++;
        }
        cout << "Breadth First Search: ";
        for (int j = i; j >= 0; j--) {
            cout << vertex[sbfs[j]] <<  " -> " ;
        }
    }
}

int main(int argc, char const *argv[])
{
    readMatrixFromFile(a, n);
    displayMatrixFromFile(a, n);

    cout << "Nhap dinh bat dau cua thuat toan DFS: ";
    cin >> startVertex;
    cout << "Nhap dinh ket thuc cua thuat toan DFS: ";
    cin >> endVertex;
 
    DepthFirstSearch(startVertex, endVertex);

    cout << "Result: " << endl;
    displayDepthFirstSearch(startVertex, endVertex);
    cout << "\n" << endl;

    cout << "Nhap dinh bat dau cua thuat toan BFS: ";
    cin >> startVertex;
    cout << "Nhap dinh ket thuc cua thuat toan BFS: ";
    cin >> endVertex;
    BreadthFirstSearch(startVertex, endVertex);
    cout << "Result: " << endl;
    displayBreadthFirstSearch(startVertex, endVertex);
    return 0;
}

