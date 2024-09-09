// Elay Ben Yehoshua 214795668
#include "fmm.h"

// Slow fmm 
void slowfmm(int n, int* m1, int* m2, int* result) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i * n + j] = 0;
            for (int k = 0; k < n; k++)
                result[i * n + j] += m1[i * n + k] * m2[k * n + j];
        }
    }
}


void fmm(int n, int* m1, int* m2, int* result) {
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            int sum = m1[i * n + k];
            for (int j = 0; j < n; j++) 
                result[i * n + j] += sum * m2[k * n + j];  // result[i * len +j] += m1[i][k] * m2[k][j]
        }
    }
}

void add_mat(int n, int* m1, int* m2, int* result) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i * n + j] = m1[i * n + j] + m2[i * n + j];  // result[i * len +j] = m1[i * len +j] + m2[i * len +j]
        }
    }
}

void sub_mat(int n, int* m1, int* m2, int* result) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i * n + j] = m1[i * n + j] - m2[i * n + j];  // result[i * len +j] = m1[i * len +j] - m2[i * len +j]
        }
    }
}

void strassenfmm(int n, int* m1, int* m2, int* result) {
   //if mat is 1x1
   if (n == 1) {
    result[0] = (m1[0] * m2[0]);
       return;
   }

int len = n / 2;

//creating sub matrices to do reccursion
 int A11[len * len],  A12[len * len],  A21[len * len],
   A22[len * len],  B11[len * len],  B12[len * len],
   B21[len * len],  B22[len * len];

 //initializing the sub matrices
  for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            // init the sub A matrices
            A11[i * n + j] = m1[i * n + j];
            A12[i * n + j] = m1[i * n + j +len];
            A21[i * n + j] = m1[(i + len) * n + j];
            A22[i * n + j] = m1[(i + len) * n + j +len];
            
            // init the sub B matrices
            B11[i * n + j] = m2[i * n + j];
            B12[i * n + j] = m2[i * n + j +len];
            B21[i * n + j] = m2[(i + len) * n + j];
            B22[i * n + j] = m2[(i + len) * n + j +len];
        }

    }

    // Doing it like Strassen
     int T1[len * len], T2[len * len],
      T3[len * len], T4[len * len],
      T5[len * len], T6[len * len], T7[len * len];
      int R1[len * len], R2[len * len];

        // init T1
        add_mat(len, A11, A11,R1);
        add_mat(len, B11, B22,R2);
        fmm(len, R1, R2, T1);

         // init T2
        add_mat(len, A21, A22,R1);
        fmm(len, R1, B11, T2);

         // init T3
        sub_mat(len, B12, B22,R2);
        fmm(len, A11, R2, T3);

         // init T4
        sub_mat(len, B21, B11,R2);
        fmm(len, A22, R2, T4);

         // init T5
        add_mat(len, A11, A12,R2);
        fmm(len, R2, B22, T5);

          // init T6
        sub_mat(len, A21, A11,R1);
        add_mat(len, B11, B12,R2);
        fmm(len, R1, R2, T6);

         // init T7
        sub_mat(len, A12, A22,R1);
        add_mat(len, B21, B22,R2);
        fmm(len, R1, R2, T7);

        // puting together all the cuarters
        int Q11[len * len], Q12[len * len],
        Q21[len * len], Q22[len * len];

        // init Q1
        add_mat(len, T1, T4, R1);
        sub_mat(len, R1, T5, R2);
        add_mat(len, R2, T7, Q11);

        // init Q2
        add_mat(len, T3, T5, Q12);

        // init Q3
        add_mat(len, T2, T4, Q21);

        // init Q4
        sub_mat(len, T1, T2, R1);
        add_mat(len, R1, T3, R2);
        add_mat(len, R2, T6, Q22);

        // add all Q11,Q12... into result
        for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            result[i * len +j] = Q11[i * len +j];
            result[i * len +j + len] = Q12[i * len +j];
            result[i + len + j] = Q21[i * len +j];
            result[i + len + j + len] = Q22[i * len +j];
        }
    }


}
