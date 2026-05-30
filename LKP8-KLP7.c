#include <stdio.h>
#define MAXNUM_VERTICES 100

/* Implementasi COLOR untuk DFS
*/
typedef enum {WHITE, GRAY, BLACK} COLOR;

/*
Struktur data untuk merepresentasikan sebuah graf dengan
menggunakan adjacency matrix.
Graph akan memiliki sebanyak n_vertices simpul dan n_edges sisi.
Kita mengasumsikan bahwa graph akan memiliki maksimal hanya MAXNUM_VERTICES simpul.
*/

typedef struct
{
    int n_vertices;
    int n_edges;
    int adjacency_matrix[MAXNUM_VERTICES][MAXNUM_VERTICES];
} Graph;

/* Prosedur DFS_visit sesuai instruksi gambar
*/
void DFS_visit(Graph *g, COLOR *vertex_colors, int v)
{
    int i;
    printf("%d ", v);

    vertex_colors[v] = GRAY;

    for (i = 0; i < g->n_vertices; i++)
    {
        /* Soal 5: Manggil DFS_visit pada vertex i yang 
           adjacent terhadap v dan masih berwarna WHITE */
        if (g->adjacency_matrix[v][i] == 1 && vertex_colors[i] == WHITE)
        {
            DFS_visit(g, vertex_colors, i);
        }
    }

    vertex_colors[v] = BLACK;
}

/* Prosedur utama untuk menjalankan DFS
*/
void DFS(Graph *g)
{
    COLOR vertex_colors[MAXNUM_VERTICES];
    int i;
    for (i = 0; i < g->n_vertices; i++)
        vertex_colors[i] = WHITE;

    for (i = 0; i < g->n_vertices; i++)
    {
        if(vertex_colors[i] == WHITE)
            DFS_visit(g, vertex_colors, i);
    }
    printf("\n");
}

/*
Fungsi untuk menginisialisasi adjacency matrix graph dg cara mengisi
sub-matrix kiri atas dg ukuran n_vertices x n_vertices dari adjacency matrix
dg nilai 0, sedangkan sisanya (yang tidak relevan untuk tujuan representasi graph dg jumlah vertex sebanyak n_vertices) akan diisi dg nilai -1.
*/

void inisialisasi_graph (Graph *g, int n_v, int n_e)
{
    int i,j;

    g->n_vertices = n_v;
    g->n_edges = n_e;

    for(i = 0; i < MAXNUM_VERTICES; i++)
    {
        for(j=0; j < MAXNUM_VERTICES; j++)
        {
            if(i < n_v && j < n_v)
            /* Soal no. 1: lengkapi untuk menyimpan nilai 0 pada sub-matrix kiri-atas dari adjacency matrix*/
            g->adjacency_matrix[i][j] = 0; 
            else
            /* Soal no. 2: lengkapi untuk menyimpan nilai -1 pada elemen-elemen sisanya */
            g->adjacency_matrix[i][j] = -1;
        }
    }
}

/*
Fungsi untuk mencetak adjacency matrix dari sebuah graph g
*/
void print_adjacency_matrix(Graph *g)
{
    int i,j;
    for(i = 0; i < g->n_vertices; i++)
        printf("\t%d", i);
    printf("\n");
    
    for(i = 0; i < g->n_vertices; i++)
    {
        printf("%d", i);
        for(j = 0; j < g->n_vertices; j++)
        {
            printf("\t%d", g->adjacency_matrix[i][j]);
        }
        printf("\n");
    }
}

/*
catatan:
compile bisa lewat vscode
jalankan "adjacency < input.txt" lewat cmd, bukan powershell atau terminal vscode

contoh: 
di vscode: g++ ./prak8/[solved]_adjacencyMatrix.cpp -o ./prak8/adjacency
di command prompt: C:\Users\M. Syafiq Romadhon\Documents\GitHub\PraktikumStrukdatGenap2526\Prak8>adjacency < input.txt
*/

int main()
{
    int n_v = 0;
    int n_e = 0;
    int i,j;
    scanf("%d %d", &n_v, &n_e);

    Graph g;
    inisialisasi_graph (&g, n_v, n_e);

    for(i = 0; i < n_e; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        /* Soal 3 lengkapi agar adjacency matrix pada g menyimpan nilai 1 pada baris a kolom b */
        g.adjacency_matrix[a][b] = 1;
        /* Soal 4 merepresentasikan graph tidak berarah */
        g.adjacency_matrix[b][a] = 1;
    }
    print_adjacency_matrix(&g);
    
    /* ngeprint dfs nya */
    DFS(&g);
    
return 0;
}