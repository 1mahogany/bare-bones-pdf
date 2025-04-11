
#ifndef BARE_BONES_PDF_FWF_H
#define BARE_BONES_PDF_FWF_H

#include <stdio.h>
#include <stdint.h>

#define FWF_FIN 0 // last available line format - exit detection loop
#define FWF_OUT 1 // line is ready for fwrite output
#define FWF_MIN 2 // minimum number of bytes required
#define FWF_MAX 3 // maximum number of bytes allowed
#define FWF_I01 4 // 1st index to read
#define FWF_C01 5 // 1st byte to match
#define FWF_I02 6 // 2nd index to read
#define FWF_C02 7 // 2nd byte to match

#define FWF_COL_SIZE (1 << 5)
#define FWF_ROW_SIZE (1 << 8)

typedef enum {

    FWF_COL_BPR_PAYER,
    FWF_COL_BPR_PAYEE,
    FWF_COL_BPR_NPI,
    FWF_COL_BPR_CHECK_NUMBER,
    FWF_COL_BPR_PAYMENT_DATE,
    FWF_COL_CLP_PATIENT_NAME,
    FWF_COL_CLP_PATIENT_ID,
    FWF_COL_CLP_ICN,
    FWF_COL_CLP_PCN,
    FWF_COL_CLP_MRN,
    FWF_COL_SVC_PROC_CD,
    FWF_COL_SVC_MODIFIERS,
    FWF_COL_SVC_DATE_FROM,
    FWF_COL_SVC_DATE_TO,
    FWF_COL_SVC_ALLOW_UNITS,
    FWF_COL_SVC_DETAIL_EOBS,
    FWF_COL_SVC_COPAY_AMT,
    FWF_COL_SVC_BILLED_AMT,
    FWF_COL_SVC_ALLOW_AMT,
    FWF_COL_SVC_PAID_AMT,
    FWF_COL_ZZZ,

} FWFCol;

typedef struct {

    uint8_t buffer[FWF_ROW_SIZE];
    uint8_t offset[FWF_COL_SIZE];

    uint32_t header;
    FILE* output;

} FWFRow;

#define FWF_ROW_AUTO(X) &(FWFRow)          \
{                                          \
    .buffer =                              \
        "PAYER       "                     \
        "PAYEE       "                     \
        "         NPI"                     \
        "CHECK_NUMBER"                     \
        "PAYMENT_DATE"                     \
        "PATIENT_NAME                   "  \
        "PATIENT_ID  "                     \
        "ICN            "                  \
        "PCN          "                    \
        "MRN            "                  \
        "PROC_CD"                          \
        "M1 M2 M3 M4 "                     \
        "FROM  "                           \
        "TO    "                           \
        "ALLW_UNITS"                       \
        "EOB1 EOB2 EOB3 EOB4 "             \
        "   COPAY_AMT"                     \
        "  BILLED_AMT"                     \
        "   ALLOW_AMT"                     \
        "    PAID_AMT"                     \
        "\n"                             , \
    .offset = {                            \
        [FWF_COL_BPR_PAYER]        = 0x00, \
        [FWF_COL_BPR_PAYEE]        = 0x0c, \
        [FWF_COL_BPR_NPI]          = 0x18, \
        [FWF_COL_BPR_CHECK_NUMBER] = 0x24, \
        [FWF_COL_BPR_PAYMENT_DATE] = 0x30, \
        [FWF_COL_CLP_PATIENT_NAME] = 0x3c, \
        [FWF_COL_CLP_PATIENT_ID]   = 0x5b, \
        [FWF_COL_CLP_ICN]          = 0x67, \
        [FWF_COL_CLP_PCN]          = 0x76, \
        [FWF_COL_CLP_MRN]          = 0x83, \
        [FWF_COL_SVC_PROC_CD]      = 0x92, \
        [FWF_COL_SVC_MODIFIERS]    = 0x99, \
        [FWF_COL_SVC_DATE_FROM]    = 0xa5, \
        [FWF_COL_SVC_DATE_TO]      = 0xab, \
        [FWF_COL_SVC_ALLOW_UNITS]  = 0xb1, \
        [FWF_COL_SVC_DETAIL_EOBS]  = 0xbb, \
        [FWF_COL_SVC_COPAY_AMT]    = 0xcf, \
        [FWF_COL_SVC_BILLED_AMT]   = 0xdb, \
        [FWF_COL_SVC_ALLOW_AMT]    = 0xe7, \
        [FWF_COL_SVC_PAID_AMT]     = 0xf3, \
        [FWF_COL_ZZZ]              = 0xff, \
    }                                    , \
    .header = 0                          , \
    .output = X                            \
}

#endif // BARE_BONES_PDF_FWF_H
