#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct grafo_s{
    int index;
    uint32_t punt;
}grafo_t;

uint32_t gestiscimatrice(int);
int estrai(uint32_t[], uint32_t[], int);
void inserisci(grafo_t[], uint32_t, int, int);
int trovamax(grafo_t[], int, int);
void costruiscimaxheap(grafo_t[], int);
void maxheapify(grafo_t[], int, int);

int main (){
    int d, k, count, i, trash;
    char comando[14] = "v";
    grafo_t * class;
    uint32_t score;
    trash=scanf("%d %d", &d, &k);
    if(trash!=2)
        return 1;
    if((class=malloc(k*sizeof(grafo_t)))){
        count=0;
        trash=scanf("%s", comando);
        while(!feof(stdin)){
            if(!strcmp(comando, "AggiungiGrafo")){
                score=gestiscimatrice(d);
                if(count<k){
                    class[count].index=count;
                    class[count].punt=score;
                }else if(count==k){
                    costruiscimaxheap(class, k);
                    inserisci(class, score, count, k);
                }else if(count>k){
                    inserisci(class, score, count, k);
                }
                count++;

            }
            if(!strcmp(comando, "TopK")){
                if(count==0)
                    printf("\n");
                else{
                    for(i=0; i<k-1 && i<count-1; i++){
                        printf("%d ", class[i].index);
                    }
                    printf("%d\n", class[i].index);
                }
            }
            trash=scanf("%s", comando);
        }
    }else
        printf("Errore nell'allocazione di memoria");
    return 0;
}

uint32_t gestiscimatrice(int dim){
    uint32_t dist[dim], visit[dim], score;
    uint32_t cost[dim][dim], num;
    int i, j, v, z;
    char ch;
    for(i=0; i<dim; i++){
        dist[i]=0;
        visit[i]=0;
    }
    for(i=0; i<dim; i++)
        for(j=0; j<dim; j++)
            cost[i][j]=0;
    for(i=0;i<dim;i++){
        j=0;
        ch=getchar();
        while(ch=='\r' || ch=='\n')
            ch=getchar();
        while(ch!='\n'){
            if(ch!=',' && ch!='\r'){
                num=(int)ch-'0';
                cost[i][j]=cost[i][j]*10+num;
                ch=getchar();
            }else if(ch==','){
                j++;
                ch=getchar();
            }else if(ch=='\r')
                ch=getchar();
            
        }
    }
    for(z=0, i=1; i<dim && !z; i++){
        if(cost[0][i]!=0)
            z=1;
    }
    if(!z)
        return 0;
    visit[0]=1;
    for(i=1; i<dim; i++){
        if(cost[0][i]>0){
            dist[i]=cost[0][i];
        }
    }
    for(j=1; j<dim; j++){
        v=estrai(dist, visit, dim);
        visit[v]=1;
        for(i=1; i<dim; i++){
            if(cost[v][i]>0 && i!=v){
                if(dist[i]==0 || (dist[i]>0 && dist[v]>0 && dist[i]>dist[v]+cost[v][i])){
                    dist[i]=dist[v]+cost[v][i];
                }
            }
        }
    }
    score=0;
    for(i=1; i<dim; i++)
        score += dist[i];
    return score;
}

int estrai(uint32_t d[], uint32_t v[], int l){
    int i, min, flag;
    int i_min;
    i=0;
    flag=0;
    min=-1;
    i_min=-1;
    while(i<l && !flag){
        if(v[i]==1 || d[i]==0)
            i++;
        else{
            min=d[i];
            i_min=i;
            flag=1;
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

void inserisci(grafo_t v[], uint32_t pts, int idx, int len){
    if(pts<v[0].punt){
        v[0].punt=pts;
        v[0].index=idx;
    }
    maxheapify(v, 0, len);
    return;
}

void costruiscimaxheap(grafo_t v[], int dim){
    int i;
    for(i=dim/2; i>=0; i--)
        maxheapify(v, i, dim);
    return;
}

void maxheapify(grafo_t v[], int rad, int dim){
    int l, r, posmax;
    grafo_t tmp;
    l=2*rad;
    r=2*rad+1;
    if(l<dim && v[l].punt > v[rad].punt)
        posmax=l;
    else
        posmax=rad;
    if(r<dim && v[r].punt > v[posmax].punt)
        posmax=r;
    if(posmax!=rad){
        tmp.punt=v[posmax].punt;
        tmp.index=v[posmax].index;
        v[posmax].punt=v[rad].punt;
        v[posmax].index=v[rad].index;
        v[rad].punt=tmp.punt;
        v[rad].index=tmp.index;
        maxheapify(v, posmax, dim);
    }
    return;
}