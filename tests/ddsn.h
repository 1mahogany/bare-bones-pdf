
#ifndef BARE_BONES_PDF_DDSN_H
#define BARE_BONES_PDF_DDSN_H

#ifndef BARE_BONES_PDF_FWF_H
#define DDSN_ROW_SIZE 224
#define DDSN_COL_SIZE 23

#include "fwf.h"

typedef enum {
    
    DDSN_LINE_BPR_1,
    DDSN_LINE_BPR_2,
    DDSN_LINE_BPR_3,
    DDSN_LINE_SVC_1,
    DDSN_LINE_SVC_2,
    DDSN_LINE_CLP_1,
    DDSN_LINE_ZZZ_1,
    
} DDSNLine;

typedef enum {
    
    DDSN_COL_BPR_PAYER,
    DDSN_COL_BPR_PAYEE,
    DDSN_COL_BPR_CHECK_NUMBER,
    DDSN_COL_BPR_PAYMENT_DATE,
    DDSN_COL_CLP_PCN,
    DDSN_COL_CLP_ICN,
    DDSN_COL_CLP_MRN,
    DDSN_COL_CLP_PATIENT_ID,
    DDSN_COL_CLP_PATIENT_NAME,
    DDSN_COL_SVC_DATE_FROM,
    DDSN_COL_SVC_DATE_TO,
    DDSN_COL_SVC_PROC_CD,
    DDSN_COL_SVC_BILLED_AMT,
    DDSN_COL_SVC_PAID_AMT,
    DDSN_COL_SVC_STS,
    DDSN_COL_SVC_MOD,
    DDSN_COL_SVC_ALLOW_AMT,
    DDSN_COL_SVC_COPAY_AMT,
    DDSN_COL_SVC_DETAIL_EOBS,
    DDSN_COL_ZZZ,
    
} DDSNCol;

typedef struct {

    uint8_t buffer[DDSN_ROW_SIZE * 9];
    uint8_t offset[DDSN_COL_SIZE];
    uint8_t n_rows;
    FILE* output;

} DDSNSec;

#define DDSN_SEC_AUTO(X) &(DDSNSec) {       \
    .buffer =                               \
        "SCMCD       "                      \
        "PAYEE       "                      \
        "CHECK_NUMBER"                      \
        "PAYMENT_DATE"                      \
        "PCN      "                         \
        "ICN              "                 \
        "               "                   \
        "PATIENT_ID"                        \
        "FIMILAST_NAME      "               \
        "FROM  "                            \
        "TO    "                            \
        "PROC  "                            \
        "  BILLED"                          \
        "    PAID"                          \
        "S"                                 \
        "MOD"                               \
        "  ALLOW"                           \
        "  COPAY"                           \
        "    "                              \
        "\n"                              , \
    .offset = {                             \
        [DDSN_COL_BPR_PAYER]        = 0x00, \
        [DDSN_COL_BPR_PAYEE]        = 0x0c, \
        [DDSN_COL_BPR_CHECK_NUMBER] = 0x18, \
        [DDSN_COL_BPR_PAYMENT_DATE] = 0x24, \
        [DDSN_COL_CLP_PCN]          = 0x30, \
        [DDSN_COL_CLP_ICN]          = 0x39, \
        [DDSN_COL_CLP_MRN]          = 0x4a, \
        [DDSN_COL_CLP_PATIENT_ID]   = 0x59, \
        [DDSN_COL_CLP_PATIENT_NAME] = 0x63, \
        [DDSN_COL_SVC_DATE_FROM]    = 0x76, \
        [DDSN_COL_SVC_DATE_TO]      = 0x7c, \
        [DDSN_COL_SVC_PROC_CD]      = 0x82, \
        [DDSN_COL_SVC_BILLED_AMT]   = 0x88, \
        [DDSN_COL_SVC_PAID_AMT]     = 0x90, \
        [DDSN_COL_SVC_STS]          = 0x98, \
        [DDSN_COL_SVC_MOD]          = 0x99, \
        [DDSN_COL_SVC_ALLOW_AMT]    = 0x9c, \
        [DDSN_COL_SVC_COPAY_AMT]    = 0xa3, \
        [DDSN_COL_SVC_DETAIL_EOBS]  = 0xaa, \
        [DDSN_COL_ZZZ]              = 0xae, \
    }                                     , \
    .n_rows = 0                           , \
    .output = X                             \
}

#endif // BARE_BONES_PDF_FWF_H

int ddsn_parse_file(PDFFile* pdf, FILE* out);

#endif // BARE_BONES_PDF_DDSN_H
