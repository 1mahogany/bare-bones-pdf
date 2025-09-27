/**
 * Bare Bones PDF: A bare-bones C library for PDF files
 * Copyright (C) 2025 Ian Wang
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef BARE_BONES_PDF_MCD_AR_H
#define BARE_BONES_PDF_MCD_AR_H

#ifndef BARE_BONES_PDF_PARSER_H
#define MCD_ROW_SIZE 256
#define MCD_COL_SIZE 24

#include "parser.h"

typedef enum {
    
    MCD_HEAD_BPR_1,
    MCD_HEAD_BPR_2,
    MCD_HEAD_BPR_3,
    MCD_HEAD_BPR_4,
    MCD_HEAD_BPR_5,
    MCD_HEAD_BPR_6,
    MCD_HEAD_BPR_7,
    MCD_HEAD_BPR_8,
    MCD_HCAD_CLP_1,
    MCD_HCAD_CLP_3,
    MCD_HCAD_CLP_2,
    MCD_HCPD_CLP_1,
    MCD_HCPD_CLP_3,
    MCD_HCPD_CLP_2,
    MCD_HCPD_SVC_2,
    MCD_HCPD_SVC_1,
    MCD_HCDN_CLP_1,
    MCD_HCDN_CLP_2,
    MCD_HCDN_SVC_1,
    MCD_HCDN_SVC_2,
    
} MCDLine;

typedef enum {

    MCD_COL_BPR_PAYER,
    MCD_COL_BPR_PAYEE,
    MCD_COL_BPR_NPI,
    MCD_COL_BPR_CHECK_NUMBER,
    MCD_COL_BPR_PAYMENT_DATE,
    MCD_COL_CLP_PATIENT_NAME,
    MCD_COL_CLP_PATIENT_ID,
    MCD_COL_CLP_ICN,
    MCD_COL_CLP_PCN,
    MCD_COL_CLP_MRN,
    MCD_COL_SVC_PROC_CD,
    MCD_COL_SVC_MODIFIERS,
    MCD_COL_SVC_DATE_FROM,
    MCD_COL_SVC_DATE_TO,
    MCD_COL_SVC_ALLOW_UNITS,
    MCD_COL_SVC_DETAIL_EOBS,
    MCD_COL_SVC_COPAY_AMT,
    MCD_COL_SVC_BILLED_AMT,
    MCD_COL_SVC_ALLOW_AMT,
    MCD_COL_SVC_PAID_AMT,
    MCD_COL_ZZZ,

} MCDCol;

typedef struct {

    uint8_t buffer[MCD_ROW_SIZE];
    uint8_t offset[MCD_COL_SIZE];

    uint32_t header;
    FILE* output;

} MCDRow;

#define MCD_ROW_AUTO(X) &(MCDRow)          \
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
        [MCD_COL_BPR_PAYER]        = 0x00, \
        [MCD_COL_BPR_PAYEE]        = 0x0c, \
        [MCD_COL_BPR_NPI]          = 0x18, \
        [MCD_COL_BPR_CHECK_NUMBER] = 0x24, \
        [MCD_COL_BPR_PAYMENT_DATE] = 0x30, \
        [MCD_COL_CLP_PATIENT_NAME] = 0x3c, \
        [MCD_COL_CLP_PATIENT_ID]   = 0x5b, \
        [MCD_COL_CLP_ICN]          = 0x67, \
        [MCD_COL_CLP_PCN]          = 0x76, \
        [MCD_COL_CLP_MRN]          = 0x83, \
        [MCD_COL_SVC_PROC_CD]      = 0x92, \
        [MCD_COL_SVC_MODIFIERS]    = 0x99, \
        [MCD_COL_SVC_DATE_FROM]    = 0xa5, \
        [MCD_COL_SVC_DATE_TO]      = 0xab, \
        [MCD_COL_SVC_ALLOW_UNITS]  = 0xb1, \
        [MCD_COL_SVC_DETAIL_EOBS]  = 0xbb, \
        [MCD_COL_SVC_COPAY_AMT]    = 0xcf, \
        [MCD_COL_SVC_BILLED_AMT]   = 0xdb, \
        [MCD_COL_SVC_ALLOW_AMT]    = 0xe7, \
        [MCD_COL_SVC_PAID_AMT]     = 0xf3, \
        [MCD_COL_ZZZ]              = 0xff, \
    }                                    , \
    .header = 0                          , \
    .output = X                            \
}

#endif // BARE_BONES_PDF_PARSER_H

int parse_mcd_ar(PDFFile* pdf, FILE* out);

#endif // BARE_BONES_PDF_MCD_AR_H
