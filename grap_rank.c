#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

// graph struct
typedef struct graph_t{
    int index;
    uint32_t pointer;
}graph_t;

uint32_t handle_matrix(int);
int extract(uint32_t[], uint32_t[], int);
void insert_graph(graph_t[], uint32_t, int, int);
int find_max(graph_t[], int, int);
void build_max_heap(graph_t[], int);
void max_heapify(graph_t[], int, int);

int main (){
    int d; // Number of nodes for each graph
    int k; // Lenght of the ranking
    int count, i, trash;
    char command[14] = "v"; // The command can be either AggiungiGrafo or Topk - obviously the longest is the former and the lenght is 13 (14 with the end symbol)
    graph_t * ranking; // List of graph_t elements
    uint32_t score;
    trash = scanf("%d %d", &d, &k); // I need the *trash* variable just to check the correctness of the input
    if(trash != 2) // scanf() returns the number of correctly assigned values
        return 1; // Error
    if((ranking = malloc(k*sizeof(graph_t)))){
        count = 0;
        scanf("%s", command);
        while(!feof(stdin)){
            if(!strcmp(command, "AggiungiGrafo")){
                score = handle_matrix(d);
                if(count < k){ // Add the graph to the list (the first k input graphs are always added)
                    ranking[count].index = count;
                    ranking[count].pointer = score;
                }else if(count == k){ // I have k graphs so I can build the heap to handle the ranking and the new graph must be inserted only if it is in the topK
                    build_max_heap(ranking, k);
                    insert_graph(ranking, score, count, k);
                }else if(count > k){ // I already have k graphs so the new one must be inserted only if it is in the topK
                    insert_graph(ranking, score, count, k);
                }
                count++;

            }
            if(!strcmp(command, "TopK")){
                if(count == 0) // Nothing to print
                    printf("\n");
                else{
                    for(i = 0; i < k-1 && i < count-1; i++){
                        printf("%d ", ranking[i].index);
                    }
                    printf("%d\n", ranking[i].index);
                }
            }
            scanf("%s", command); // Ready to read another command
        }
    }else
        printf("Memory allocation error");
    return 0;
}

uint32_t handle_matrix(int dim){
    uint32_t dist[dim], visit[dim], score;
    uint32_t cost[dim][dim], num;
    int i, j, v, z;
    char ch;

    // Initialize the distance array
    for(i = 0; i < dim; i++){
        dist[i] = 0;
        visit[i] = 0;
    }

    // Initialize the cost matrix
    for(i = 0; i < dim; i++)
        for(j = 0; j < dim; j++)
            cost[i][j] = 0;

    // To get the correct costs for each arc I exploited the much more efficient getchar() function
    for(i = 0; i < dim; i++){
        j = 0;
        ch = getchar();
        while(ch == '\r' || ch == '\n')
            ch = getchar();
        while(ch != '\n'){
            if(ch != ',' && ch != '\r'){
                num = (int) ch - '0';
                cost[i][j] = cost[i][j]*10 + num;
                ch = getchar();
            }else if(ch == ','){
                j++;
                ch = getchar();
            }else if(ch == '\r')
                ch = getchar();
            
        }
    }

    // Check if the node 0 has actually arcs coming out of it
    for(z=0, i=1; i<dim && !z; i++){
        if(cost[0][i]!=0)
            z=1;
    }
    if(!z)
        return 0;
    visit[0] = 1;

    // Dijkstra algorithm to find the minimum path from node 0
    for(i = 1; i < dim; i++){
        if(cost[0][i] > 0){
            dist[i] = cost[0][i];
        }
    }
    for(j = 1; j < dim; j++){
        v = extract(dist, visit, dim);
        visit[v] = 1;
        for(i = 1; i < dim; i++){
            if(cost[v][i] > 0 && i != v){
                if(dist[i] == 0 || (dist[i] > 0 && dist[v] > 0 && dist[i] > dist[v] + cost[v][i])){
                    dist[i] = dist[v] + cost[v][i];
                }
            }
        }
    }

    // The score is the sum of the distances from node 0
    score = 0;
    for(i = 1; i < dim; i++)
        score += dist[i];
    return score;
}

int extract(uint32_t d[], uint32_t v[], int l){
    int i, min, flag;
    int i_min;
    i = 0;
    flag = 0;
    min = -1;
    i_min = -1;
    while(i < l && !flag){
        if(v[i] == 1 || d[i] == 0)
            i++;
        else{
            min = d[i];
            i_min = i;
            flag = 1;
        }
    }
    if(!flag){
        for(i=0; i<l; i++){
            if(v[i]==0 && d[i]==0){
                return i;
            }                
        }
    }
    for(i=0; i<l; i++){
        if(v[i]==0){
            if(d[i]>0 && d[i]<min){
                i_min=i;
                min=d[i];
            }
        }
    }
    return i_min;
}

void insert_graph(graph_t v[], uint32_t pts, int idx, int len){
    if(pts<v[0].pointer){
        v[0].pointer=pts;
        v[0].index=idx;
    }
    max_heapify(v, 0, len);
    return;
}


void build_max_heap(graph_t v[], int dim){
    int i;
    for(i=dim/2; i>=0; i--)
        max_heapify(v, i, dim);
    return;
}

void max_heapify(graph_t v[], int rad, int dim){
    int l, r, posmax;
    graph_t tmp;
    l=2*rad;
    r=2*rad+1;
    if(l<dim && v[l].pointer > v[rad].pointer)
        posmax=l;
    else
        posmax=rad;
    if(r<dim && v[r].pointer > v[posmax].pointer)
        posmax=r;
    if(posmax!=rad){
        tmp.pointer=v[posmax].pointer;
        tmp.index=v[posmax].index;
        v[posmax].pointer=v[rad].pointer;
        v[posmax].index=v[rad].index;
        v[rad].pointer=tmp.pointer;
        v[rad].index=tmp.index;
        max_heapify(v, posmax, dim);
    }
    return;
}