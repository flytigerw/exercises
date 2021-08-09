// C/C++ header file



//row major 
#define A(i,j) a[(i)*lda + (j)]
#define B(i,j) b[(i)*ldb + (j)]
#define C(i,j) c[(i)*ldc + (j)]


//four rows of A and 1 column of B for every computation
void AddDot4×1_0(float* a,int lda,float* ldb,float* c,ldc,int k){

    //优化点:将C元素B(p,0)放到寄存器中复用
    for(int p=0;p<k;p++){

        C(0,0) += A(0,p) * B(p,0);
        C(1,0) += A(1,p) * B(p,0);
        C(2,0) += A(2,p) * B(p,0);
        C(3,0) += A(3,p) * B(p,0);

    }

}


void AddDot4×1_1(float* a,int lda,float* ldb,float* c,ldc,int k){

    register float reg_c_00,reg_c_10,reg_c_20,reg_c_30,reg_b_p0;
    reg_c_00 = 0.0;
    reg_c_10 = 0.0;
    reg_c_20 = 0.0;
    reg_c_30 = 0.0;


    for(int p=0;p<k;p++){
        reg_b_p0 = B(p,0);

        reg_c_00 += A(0,p) * reg_b_p0;
        reg_c_10 += A(1,p) * reg_b_p0;
        reg_c_20 += A(2,p) * reg_b_p0;
        reg_c_30 += A(3,p) * reg_b_p0;
    }

    C(0,0) += reg_c_00;
    C(1,0) += reg_c_10;
    C(2,0) += reg_c_20;
    C(3,0) += reg_c_30;

}


//unpack loop by 4 and usee indirect addressing

void AddDot4×1_2(float* a,int lda,float* ldb,float* c,ldc,int k){
    register float reg_c_00,reg_c_10,reg_c_20,reg_c_30,reg_b_p0;
    reg_c_00 = 0.0;
    reg_c_10 = 0.0;
    reg_c_20 = 0.0;
    reg_c_30 = 0.0;


    float* ptr_a_p0,*ptr_a_p1,*ptr_a_p2,*ptr_a_p3;
    ptr_a_0p = &A(0,0);
    ptr_a_1p = &A(1,0);
    ptr_a_2p = &A(2,0);
    ptr_a_3p = &A(3,0);

    for(int p=0;p<k;p+=4){

        //first 
        reg_b_p0 += B(p,0);
        reg_c_00 += *(ptr_a_0p) * reg_b_p0;
        reg_c_01 += *(ptr_a_1p) * reg_b_p0;
        reg_c_02 += *(ptr_a_2p) * reg_b_p0;
        reg_c_03 += *(ptr_a_3p) * reg_b_p0;

        //second
        reg_b_p0 += B(p,1);
        reg_c_00 += *(ptr_a_0p+1) * reg_b_p0;
        reg_c_01 += *(ptr_a_1p+1) * reg_b_p0;
        reg_c_02 += *(ptr_a_2p+1) * reg_b_p0;
        reg_c_03 += *(ptr_a_3p+1) * reg_b_p0;

        //third
        reg_b_p0 += B(p,2);
        reg_c_00 += *(ptr_a_0p+2) * reg_b_p0;
        reg_c_01 += *(ptr_a_1p+2) * reg_b_p0;
        reg_c_02 += *(ptr_a_2p+2) * reg_b_p0;
        reg_c_03 += *(ptr_a_3p+2) * reg_b_p0;

        //forth
        reg_b_p0 += B(p,3);
        reg_c_00 += *(ptr_a_0p+3) * reg_b_p0;
        reg_c_01 += *(ptr_a_1p+3) * reg_b_p0;
        reg_c_02 += *(ptr_a_2p+3) * reg_b_p0;
        reg_c_03 += *(ptr_a_3p+3) * reg_b_p0;

        ptr_a_0p += 4;
        ptr_a_1p += 4;
        ptr_a_2p += 4;
        ptr_a_3p += 4;
    }

    C(0,0) += reg_c_00;
    C(1,0) += reg_c_10;
    C(2,0) += reg_c_20;
    C(3,0) += reg_c_30;
}


//compute a 4×4 block of C  
void AddDot4×4_0(float* a,int lda,float* ldb,float* c,ldc,int k){

    //A和B均有元素可以用寄存器复用
    for(int p=0;p<k;p++){

        //first col       
        C(0,0) += A(0,p)*B(p,0);
        C(1,0) += A(1,p)*B(p,0);
        C(2,0) += A(2,p)*B(p,0);
        C(3,0) += A(3,p)*B(p,0);
                           
        //second col       
        C(0,1) += A(0,p)*B(p,1);
        C(1,1) += A(1,p)*B(p,1);
        C(2,1) += A(2,p)*B(p,1);
        C(3,1) += A(3,p)*B(p,1);
                           
        //third col        
        C(0,2) += A(0,p)*B(p,2);
        C(1,2) += A(1,p)*B(p,2);
        C(2,2) += A(2,p)*B(p,2);
        C(3,2) += A(3,p)*B(p,2);
                           
        //forth col        
        C(0,3) += A(0,p)*B(p,3);
        C(1,3) += A(1,p)*B(p,3);
        C(2,3) += A(2,p)*B(p,3);
        C(3,3) += A(3,p)*B(p,3);
                      
    }

}


#include <mmintrin.h>
#include <xmmintrin.h>  // SSE
#include <pmmintrin.h>  // SSE2
#include <emmintrin.h>  // SSE3

typedef union{
    __m128 v;
    float f[4];
}v4f;

//vector
void AddDot4×4_1(float* a,int lda,float* ldb,float* c,ldc,int k){

    v4f vreg_c_row_0, vreg_c_row_1,vreg_c_row_2,vreg_c_row_3;

    v4f vreg_b_row_p, vreg_a_0p, vreg_a_1p, vreg_a_2p, vreg_a_3p;


    vreg_c_row_0.v = __mm_setzero_ps();
    vreg_c_row_1.v = __mm_setzero_ps();
    vreg_c_row_2.v = __mm_setzero_ps();
    vreg_c_row_3.v = __mm_setzero_ps();
    

    float* ptr_a_p0,*ptr_a_p1,*ptr_a_p2,*ptr_a_p3;
    ptr_a_0p = &A(0,0);
    ptr_a_1p = &A(1,0);
    ptr_a_2p = &A(2,0);
    ptr_a_3p = &A(3,0);


    for(int p=0; p<k; p++){

        //load and duplicate
        vreg_a_0p.v = __mm_loadup_ps((float*)(ptr_a_0p+p));
        vreg_a_1p.v = __mm_loadup_ps((float*)(ptr_a_1p+p));
        vreg_a_2p.v = __mm_loadup_ps((float*)(ptr_a_2p+p));
        vreg_a_3p.v = __mm_loadup_ps((float*)(ptr_a_3p+p));

        //vector load
        vreg_b_row_p.v = __mm_load_ps((float*)&B(p,0));


        //vector mul 
        vreg_c_row_0.v += vreg_a_0p.v * vreg_b_row_p.v;
        vreg_c_row_1.v += vreg_a_1p.v * vreg_b_row_p.v;
        vreg_c_row_2.v += vreg_a_2p.v * vreg_b_row_p.v;
        vreg_c_row_3.v += vreg_a_3p.v * vreg_b_row_p.v;

    }

    //write back 
    //first row
    C(0,0) += vreg_c_row_0.4f[0];
    C(0,1) += vreg_c_row_0.4f[1];
    C(0,2) += vreg_c_row_0.4f[2];
    C(0,3) += vreg_c_row_0.4f[3];

    //second row 
    C(1,0) += vreg_c_row_1.4f[0];
    C(1,1) += vreg_c_row_1.4f[1];
    C(1,2) += vreg_c_row_1.4f[2];
    C(1,3) += vreg_c_row_1.4f[3];

    //third row 
    C(2,0) += vreg_c_row_2.4f[0];
    C(2,1) += vreg_c_row_2.4f[1];
    C(2,2) += vreg_c_row_2.4f[2];
    C(2,3) += vreg_c_row_2.4f[3];

    //forth row 
    C(3,0) += vreg_c_row_3.4f[0];
    C(3,1) += vreg_c_row_3.4f[1];
    C(3,2) += vreg_c_row_3.4f[2];
    C(3,3) += vreg_c_row_3.4f[3];

}
