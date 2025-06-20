
#ifndef BARE_BONES_PDF_TXIX_H
#define BARE_BONES_PDF_TXIX_H

#ifndef BARE_BONES_PDF_FWF_H
#define TXIX_ROW_SIZE 256
#define TXIX_COL_SIZE 24

#include "fwf.h"

typedef enum {
    
    TXIX_HEAD_BPR_1,
    TXIX_HEAD_BPR_2,
    TXIX_HEAD_BPR_3,
    TXIX_HEAD_BPR_4,
    TXIX_HEAD_BPR_5,
    TXIX_HEAD_BPR_6,
    TXIX_HEAD_BPR_7,
    TXIX_HEAD_BPR_8,
    TXIX_HCAD_CLP_1,
    TXIX_HCAD_CLP_3,
    TXIX_HCAD_CLP_2,
    TXIX_HCPD_CLP_1,
    TXIX_HCPD_CLP_3,
    TXIX_HCPD_CLP_2,
    TXIX_HCPD_SVC_2,
    TXIX_HCPD_SVC_1,
    TXIX_HCDN_CLP_1,
    TXIX_HCDN_CLP_2,
    TXIX_HCDN_SVC_1,
    TXIX_HCDN_SVC_2,
    
} TXIXLine;

typedef enum {

    TXIX_COL_BPR_PAYER,
    TXIX_COL_BPR_PAYEE,
    TXIX_COL_BPR_NPI,
    TXIX_COL_BPR_CHECK_NUMBER,
    TXIX_COL_BPR_PAYMENT_DATE,
    TXIX_COL_CLP_PATIENT_NAME,
    TXIX_COL_CLP_PATIENT_ID,
    TXIX_COL_CLP_ICN,
    TXIX_COL_CLP_PCN,
    TXIX_COL_CLP_MRN,
    TXIX_COL_SVC_PROC_CD,
    TXIX_COL_SVC_MODIFIERS,
    TXIX_COL_SVC_DATE_FROM,
    TXIX_COL_SVC_DATE_TO,
    TXIX_COL_SVC_ALLOW_UNITS,
    TXIX_COL_SVC_DETAIL_EOBS,
    TXIX_COL_SVC_COPAY_AMT,
    TXIX_COL_SVC_BILLED_AMT,
    TXIX_COL_SVC_ALLOW_AMT,
    TXIX_COL_SVC_PAID_AMT,
    TXIX_COL_ZZZ,

} TXIXCol;

typedef struct {

    uint8_t buffer[TXIX_ROW_SIZE];
    uint8_t offset[TXIX_COL_SIZE];

    uint32_t header;
    FILE* output;

} TXIXRow;

#define TXIX_ROW_AUTO(X) &(TXIXRow)         \
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
        [TXIX_COL_BPR_PAYER]        = 0x00, \
        [TXIX_COL_BPR_PAYEE]        = 0x0c, \
        [TXIX_COL_BPR_NPI]          = 0x18, \
        [TXIX_COL_BPR_CHECK_NUMBER] = 0x24, \
        [TXIX_COL_BPR_PAYMENT_DATE] = 0x30, \
        [TXIX_COL_CLP_PATIENT_NAME] = 0x3c, \
        [TXIX_COL_CLP_PATIENT_ID]   = 0x5b, \
        [TXIX_COL_CLP_ICN]          = 0x67, \
        [TXIX_COL_CLP_PCN]          = 0x76, \
        [TXIX_COL_CLP_MRN]          = 0x83, \
        [TXIX_COL_SVC_PROC_CD]      = 0x92, \
        [TXIX_COL_SVC_MODIFIERS]    = 0x99, \
        [TXIX_COL_SVC_DATE_FROM]    = 0xa5, \
        [TXIX_COL_SVC_DATE_TO]      = 0xab, \
        [TXIX_COL_SVC_ALLOW_UNITS]  = 0xb1, \
        [TXIX_COL_SVC_DETAIL_EOBS]  = 0xbb, \
        [TXIX_COL_SVC_COPAY_AMT]    = 0xcf, \
        [TXIX_COL_SVC_BILLED_AMT]   = 0xdb, \
        [TXIX_COL_SVC_ALLOW_AMT]    = 0xe7, \
        [TXIX_COL_SVC_PAID_AMT]     = 0xf3, \
        [TXIX_COL_ZZZ]              = 0xff, \
    }                                    , \
    .header = 0                          , \
    .output = X                            \
}

#endif // BARE_BONES_PDF_FWF_H

int txix_parse_file(PDFFile* pdf, FILE* out);

#endif // BARE_BONES_PDF_TXIX_H
