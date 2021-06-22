#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <math.h>


    int **M;
    int F_Row,F_Column,S_Row,S_Column,T_Row,T_Column;

    int i,Row,Column;
    int **F_Matrix;
    int **S_Matrix;
    int **Mult;

    struct arg_struct
    {
        int thr_row;
        int thr_column;

    };

void printing_of_matrix(int rows, int cols, int **mat){
    int i=0,j=0;
  for(i=0; i<rows; i++){
        for(j=0; j<cols; j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
}


void freeing_of_matrix(int rows, int **mat){
    int i=0;
    for(i=0;i<rows;i++)
        free(mat[i]);
    free(mat);
}


void* multiplication_matrix(void *arguments)
{

    struct arg_struct *args = arguments;

    int thr_sum=0;

   ///////////matrix of the second row being calculated //////////////////////////////////////////////
    for (i = 0; i < S_Row; i++)
        {


          thr_sum = thr_sum + (F_Matrix[args -> thr_row][i]*S_Matrix[i][args -> thr_column]);

        }
        /////////////////////Result of the multiplied matrix stored here///////////////////////////////////
        Mult[args -> thr_row][args -> thr_column] = thr_sum;

    pthread_exit(NULL);
    return NULL;


}
int main(int argc,char* argv[])
{

///////////////////// Reading of the inputs //////////////////////////////////////////////

    FILE *fp;
    pthread_t  *threads;//array of thread generated here
    struct arg_struct *args;
    args=( struct arg_struct *) malloc((F_Row*S_Column)* sizeof( struct arg_struct));


    if (argc != 2) {
        fprintf(stderr, "Usage: %s input_file.txt\n", argv[0]);
        exit(1);
    }
    if (!(fp = fopen(argv[1], "r"))) {
        perror(argv[1]);
        exit(1);
    }

    for(i=1;i<=2;i++)
    {
        /////////////////////reading of  matrix////////////
            fscanf(fp, "%d%d",&T_Row,&T_Column);
            printf("Matrix Input is%d : Row is = %d,Column is= %d\n",i,T_Row,T_Column);

            //@D array set to store the matrix
            M = (int **) malloc(sizeof(int *)*T_Row);
            for(Row=0; Row<T_Row; Row++)
                M[Row] = (int *) malloc(sizeof(int)*T_Column);



           // reading of  a matrix
            for (Row = 0; Row < T_Row; Row++)
                for (Column = 0; Column < T_Column; Column++)
                    fscanf(fp,"%d", &M[Row][Column]);
/////////////////////////end reading the  matrix//////
            if(i==1)
            {
                F_Matrix=M;
                F_Row=T_Row;
                F_Column=T_Column;
                print_matrix(F_Row,F_Column,F_Matrix);
            }

            else
            {
                S_Matrix=M;
                S_Row=T_Row;
                S_Column=T_Column;
                print_matrix(S_Row,S_Column,S_Matrix);


            }




    }


    fclose(fp);

 ///////////////finish reading of the input matrixes


// 2D array set up to store the result of the multiplication

    Mult = (int **) malloc(sizeof(int *)*F_Row);
    for(Row=0; Row<F_Row; Row++)
        Mult[Row] = (int *) malloc(sizeof(int)*S_Column);

    //Thread of array to read the multiplication of matrix
    threads = (pthread_t *) malloc((F_Row*S_Column)* sizeof(pthread_t));

    // Array of thread with the same function of the multiplication
    args=( struct arg_struct *) malloc((F_Row*S_Column)* sizeof( struct arg_struct));

    int num_of_thread=0;


    //multiplication of two matrices
    for (Row = 0; Row < F_Row; Row++)
    {
      for (Column = 0; Column < S_Column; Column++)
      {

        args[num_of_thread].thr_row = Row;
        args[num_of_thread].thr_column = Column;


        if(pthread_create(&threads[num_of_thread], NULL, multiplication_matrix,(void *)&args[num_of_thread] ) <0)
        {
            perror("The thread could not be created");
            return 1;
        }
        num_of_thread++;
      }
    }

    for (i = 0; i < (F_Row*S_Column); i++)
    {
        pthread_join(threads[i], NULL);

    }

    //printing of the calculated results
    printf(" Product obtained from the values entered: Row= %d,Column= %d\n",F_Row,S_Column);

    print_matrix(F_Row,S_Column,Mult);

    printf("\n");




    fp = fopen( "output_file.txt", "w" );

    fprintf(fp, "%d %d\n",F_Row,S_Column );
    for (Row = 0; Row < F_Row; Row++)
    {       for (Column = 0; Column < S_Column; Column++)
                    fprintf(fp,"%d ", Mult[Row][Column]);
                fprintf(fp, "\n" );
    }


    fclose(fp);


    free_of_matrix( T_Row, M);
    free_of_matrix( F_Row, Mult);

    F_Matrix=NULL;
    S_Matrix=NULL;
    M=NULL;
    Mult=NULL;
    return 0;
}
