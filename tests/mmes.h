
#ifndef BARE_BONES_PDF_MMES_H
#define BARE_BONES_PDF_MMES_H

#ifndef BARE_BONES_PDF_FWF_H
#define MMES_ROW_SIZE 256
#define MMES_COL_SIZE 24

#include "fwf.h"

typedef enum {
    
    MMES_HEAD_BPR_1,
    MMES_HEAD_BPR_2,
    MMES_HEAD_BPR_3,
    MMES_HEAD_BPR_4,
    MMES_HEAD_BPR_5,
    MMES_HEAD_BPR_6,
    MMES_HEAD_BPR_7,
    MMES_HEAD_BPR_8,
    MMES_HEAD_BPR_9,
    MMES_HCAD_CAS_2,
    MMES_HCPD_CLP_1,
    MMES_HCPD_CLP_2,
    MMES_HCPD_SVC_1,
    MMES_HCPD_SVC_2,
    MMES_HCDN_CLP_1,
    MMES_HCDN_CLP_2,
    MMES_HCDN_SVC_1,
    MMES_HCDN_SVC_2,
    
} MMESLine;

typedef enum {

    MMES_COL_BPR_PAYER,
    MMES_COL_BPR_PAYEE,
    MMES_COL_BPR_NPI,
    MMES_COL_BPR_CHECK_NUMBER,
    MMES_COL_BPR_PAYMENT_DATE,
    MMES_COL_CLP_PATIENT_NAME,
    MMES_COL_CLP_PATIENT_ID,
    MMES_COL_CLP_ICN,
    MMES_COL_CLP_PCN,
    MMES_COL_CLP_MRN,
    MMES_COL_SVC_PROC_CD,
    MMES_COL_SVC_MODIFIERS,
    MMES_COL_SVC_DATE_FROM,
    MMES_COL_SVC_DATE_TO,
    MMES_COL_SVC_ALLOW_UNITS,
    MMES_COL_SVC_DETAIL_EOBS,
    MMES_COL_SVC_COPAY_AMT,
    MMES_COL_SVC_BILLED_AMT,
    MMES_COL_SVC_ALLOW_AMT,
    MMES_COL_SVC_PAID_AMT,
    MMES_COL_ZZZ,

} MMESCol;

typedef struct {

    uint8_t buffer[MMES_ROW_SIZE];
    uint8_t offset[MMES_COL_SIZE];

    uint32_t header;
    FILE* output;

} MMESRow;

#define MMES_ROW_AUTO(X) &(MMESRow)         \
{                                           \
    .buffer =                               \
        "PAYER       "                      \
        "PAYEE       "                      \
        "         NPI"                      \
        "CHECK_NUMBER"                      \
        "PAYMENT_DATE"                      \
        "PATIENT_NAME                   "   \
        "PATIENT_ID  "                      \
        "ICN            "                   \
        "PCN          "                     \
        "MRN            "                   \
        "PROC_CD"                           \
        "M1 M2 M3 M4 "                      \
        "FROM  "                            \
        "TO    "                            \
        "ALLW_UNITS"                        \
        "EOB1 EOB2 EOB3 EOB4 "              \
        "   COPAY_AMT"                      \
        "  BILLED_AMT"                      \
        "   ALLOW_AMT"                      \
        "    PAID_AMT"                      \
        "\n"                             ,  \
    .offset = {                             \
        [MMES_COL_BPR_PAYER]        = 0x00, \
        [MMES_COL_BPR_PAYEE]        = 0x0c, \
        [MMES_COL_BPR_NPI]          = 0x18, \
        [MMES_COL_BPR_CHECK_NUMBER] = 0x24, \
        [MMES_COL_BPR_PAYMENT_DATE] = 0x30, \
        [MMES_COL_CLP_PATIENT_NAME] = 0x3c, \
        [MMES_COL_CLP_PATIENT_ID]   = 0x5b, \
        [MMES_COL_CLP_ICN]          = 0x67, \
        [MMES_COL_CLP_PCN]          = 0x76, \
        [MMES_COL_CLP_MRN]          = 0x83, \
        [MMES_COL_SVC_PROC_CD]      = 0x92, \
        [MMES_COL_SVC_MODIFIERS]    = 0x99, \
        [MMES_COL_SVC_DATE_FROM]    = 0xa5, \
        [MMES_COL_SVC_DATE_TO]      = 0xab, \
        [MMES_COL_SVC_ALLOW_UNITS]  = 0xb1, \
        [MMES_COL_SVC_DETAIL_EOBS]  = 0xbb, \
        [MMES_COL_SVC_COPAY_AMT]    = 0xcf, \
        [MMES_COL_SVC_BILLED_AMT]   = 0xdb, \
        [MMES_COL_SVC_ALLOW_AMT]    = 0xe7, \
        [MMES_COL_SVC_PAID_AMT]     = 0xf3, \
        [MMES_COL_ZZZ]              = 0xff, \
    }                                    , \
    .header = 0                          , \
    .output = X                            \
}

#endif // BARE_BONES_PDF_FWF_H

int mmes_parse_file(PDFFile* pdf, FILE* out);

#endif // BARE_BONES_PDF_MMES_H
