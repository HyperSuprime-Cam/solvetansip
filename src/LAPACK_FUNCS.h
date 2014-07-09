#ifndef  g9edcf01e_bcf6_4344_b6d2_fc21c92519b1
#define  g9edcf01e_bcf6_4344_b6d2_fc21c92519b1

extern "C"
void dgesv_(
    int    const& N,
    int    const& NRHS,
    double        A[],
    int    const& LDA,
    int           IPIV[],
    double        B[],
    int    const& LDB,
    int         * INFO );


extern "C"
void dgesvx_(
    char   const& FACT,
    char   const& TRANS,
    int    const& N,
    int    const& NRHS,
    double        A[],
    int    const& LDA,
    double        AF[],
    int    const& LDAF,
    int           IPIV[],
    char        * EQUED,
    double        R[],
    double        C[],
    double        B[],
    int    const& LDB,
    double        X[],
    int    const& LDX,
    double      * RCOND,
    double        FERR[],
    double        BERR[],
    double        WORK[],
    int           IWORK[],
    int         * INFO );


#endif //g9edcf01e_bcf6_4344_b6d2_fc21c92519b1
