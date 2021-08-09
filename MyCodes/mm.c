


#include "common.h"




//朴素版本
void matrix_multiply_0(int m, int k, int n
                     float* a,int lda, 
                     float* b,int ldb,
                     float* c,int ldc){


    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            for(int p=0;p<k;p++){
                C(i,j) += A(i,p)*B(p,j);
            }
        }
    }

}


//compute 4×1 block of C at a time 
void matrix_multiply_1(int m, int k, int n
                       float* a,int lda, 
                       float* b,int ldb,
                       float* c,int ldc){
    for(int i=0;i<m;i+=4){
        for(int j=0;j<n;j++){
            AddDot4×1_2(&A(i,0),lda,&B(0,j),ldb,&C(i,j),ldc,k);
        }
    }
}

//compute 4×4 block of C at a time 
void matrix_multiply_2(int m, int k, int n
                       float* a,int lda, 
                       float* b,int ldb,
                       float* c,int ldc){
    for(int i=0;i<m;i+=4){
        for(int j=0;j<n;j+=4){
            AddDot4×4_1(&A(i,0),lda,&B(0,j),ldb,&C(i,j),ldc,k);
        }
    }
}


#define kc 256
#define nc 128

#define min(i,j) ((i)<(j) ? (i) : (j))


void pack_matrixA(float* a,int lda,int k,float* a_to){

    float *ptr_a_0p,*ptr_a_1p,*ptr_a_2p,*ptr_a_3p;
    ptr_a_0p = &A(0,0);
    ptr_a_1p = &A(1,0);
    ptr_a_2p = &A(2,0);
    ptr_a_3p = &A(3,0);

    for(int p=0;p<k;p++){

        *(a_to)   = *(ptr_a_0p+p); 
        *(a_to+1) = *(ptr_a_1p+p); 
        *(a_to+2) = *(ptr_a_2p+p); 
        *(a_to+3) = *(ptr_a_3p+p); 

        a_to += 4;
        
    }
}

void pack_matrixB(float* b,int ldb,int k,float* b_to){

    float* ptr_b_p0 = NULL;
    for(int p=0;p<k;p++){
        
        //横向pack4个元素
        ptr_b_p0 = &B(p,0);

        *(b_to)    =  *(ptr_b_p0);
        *(b_to+1)  =  *(ptr_b_p0+1);
        *(b_to+2)  =  *(ptr_b_p0+2);
        *(b_to+3)  =  *(ptr_b_p0+3);
    }

}


void submatrix_multiply(int m, int k, int n
                        float* a,int lda, 
                        float* b,int ldb,
                        float* c,int ldc){

    float packedAi[4*kc],packedB[kc*nc];

    //compute 4×4 block of C (mr = nr =4)
    for(int i=0;i<m;i+=4){
        //pack Ai
        pack_matrixA(&A(i,0),lda,k,&packedAi);

        for(int j=0;j<n;j+=4){

            //all Ai shared the same packedB
            if(i==0){
                pack_matrixB(&B(0,j),ldb,k,&packedB[4*kc]);
            }

            //..................
        }
    }
}




//partition + pack
void matrix_multiply_3(int m, int k, int n
                       float* a,int lda, 
                       float* b,int ldb,
                       float* c,int ldc){
    int rows,cols;
    for(int i=0;i<m;i+=kc){
        rows = min(kc,m-i);
        for(int j=0;j<n;j+=nc){
            cols = min(nc,n-j);


        }


    }


}







