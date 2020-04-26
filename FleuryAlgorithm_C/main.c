#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct{
    int size;
    int* matrix;
}graph;

void w_matrix( graph g , int i, int j, int v ){
  *(g.matrix + g.size * i + j ) = v;
}
int r_matrix(  graph g , int i, int j ){
 return *(g.matrix + g.size * i + j );
}

graph read_graph(){

    graph g;

    int i, j;

    FILE *stream = fopen("stream.txt", "r");

    fscanf( stream,"%d",&g.size );

    g.matrix = malloc( g.size * g.size * sizeof( int ) );

    for(i=0;i<g.size;i++){
        for(j=0;j<g.size;j++) {
            //g.matrix[i][j]=0;
            w_matrix( g, i, j, 0 );
        }
    }

    int old_P = 999;
    int new_P = 998;

    while( 1 )  {

        fscanf( stream, "%d %d", &i, &j);



        old_P = new_P;
        new_P = i+j;
        if( old_P == new_P ){
            break;
        }

        w_matrix( g, i, j, 1 );
        w_matrix( g, j, i, 1 );

    }
    fclose(stream);

    return g;
}

void print_graph( graph g ){

    for (int i = 0; i < g.size; ++i)
    {
        for (int j = 0; j < g.size; ++j)
        {
            printf("%d ", r_matrix( g, i, j) );
        }
        printf("\n");
    }
}

int findStartVert( graph g ) {
    for (int i = 0; i < g.size; i++) {
        int deg = 0;
        for (int j = 0; j < g.size; j++) {
            if ( r_matrix(g, i, j) )
                deg++; //increase degree, when connected edge found
        }
        if (deg % 2 != 0) //when degree of vertices are odd
            return i; //i is node with odd degree
    }
    return 0; //when all vertices have even degree, start from 0
}
//Test auto save
bool isBridge(graph g, int u, int v) {
    int deg = 0;
    for (int i = 0; i < g.size; i++)
        if ( r_matrix(g, v, i) )//v i
            deg++;
    if (deg > 1) {
        return false; //the edge is not forming bridge
    }
    return true; //edge forming a bridge
}
int edgeCount( graph g ) {
    int count = 0;
    for (int i = 0; i < g.size; i++)
        for (int j = i; j < g.size; j++)
            if ( r_matrix(g, i, j) )
                count++;
    return count; //count nunber of edges in the graph
}
void fleuryAlgorithm(graph g, int start) {
    int edge = edgeCount( g );
    for (int v = 0; v < g.size; v++) {
            if (r_matrix(g, start, v)) { //when (u,v) edge is presnt and not forming bridge
                if (edge <= 1 || !isBridge(g, start, v)) {

                    printf("\t%d->%d", start, v);
                    //tempGraph[start][v] = tempGraph[v][start] = 0; //remove edge from graph

                    w_matrix(g, start, v, 0);
                    w_matrix(g, v, start, 0);
                    edge--; //reduce edge
                    fleuryAlgorithm(g, v);
                }
            }
        }
}

void start_fleury( graph g ){

    fleuryAlgorithm( g, findStartVert(g) );
}


int main() {
//    for (int i = 0; i < NODE; i++) //copy main graph to tempGraph
//        for (int j = 0; j < NODE; j++)
//            tempGraph[i][j] = graph[i][j];
//    printf("Euler Path Or Circuit: ");
//    fleuryAlgorithm(findStartVert());

    graph my_graph = read_graph() ;

    printf("The Adjacent Matrix is:\n");

    print_graph( my_graph );

    printf("\n");

    printf("Euler Path Or Circuit:");

    start_fleury( my_graph );
    printf("\n");


    return 0;
}
