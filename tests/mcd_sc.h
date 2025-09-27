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

#ifndef BARE_BONES_PDF_MCD_SC_H
#define BARE_BONES_PDF_MCD_SC_H

#ifndef BARE_BONES_PDF_PARSER_H
#define MCD_ROW_SIZE 224
#define MCD_COL_SIZE 23

#include "parser.h"

typedef enum {
    
    MCD_LINE_BPR_1,
    MCD_LINE_BPR_2,
    MCD_LINE_BPR_3,
    MCD_LINE_BPR_4,
    MCD_LINE_SVC_1,
    MCD_LINE_SVC_2,
    MCD_LINE_SVC_3,
    MCD_LINE_CLP_1,
    MCD_LINE_CLP_2,
    MCD_LINE_ZZZ_1,
    
} MCDLine;

typedef enum {
    
    MCD_COL_BPR_PAYER,
    MCD_COL_BPR_PAYEE,
    MCD_COL_BPR_CHECK_NUMBER,
    MCD_COL_BPR_PAYMENT_DATE,
    MCD_COL_CLP_PCN,
    MCD_COL_CLP_ICN,
    MCD_COL_CLP_MRN,
    MCD_COL_CLP_PATIENT_ID,
    MCD_COL_CLP_FI,
    MCD_COL_CLP_MI,
    MCD_COL_CLP_LAST_NAME,
    MCD_COL_SVC_DATE_FROM,
    MCD_COL_SVC_DATE_TO,
    MCD_COL_SVC_PROC_CD,
    MCD_COL_SVC_BILLED_AMT,
    MCD_COL_SVC_PAID_AMT,
    MCD_COL_SVC_STS,
    MCD_COL_SVC_MOD,
    MCD_COL_SVC_ALLOW_AMT,
    MCD_COL_SVC_COPAY_AMT,
    MCD_COL_SVC_DETAIL_EOBS,
    MCD_COL_ZZZ,
    
} MCDCol;

typedef struct {

    uint8_t buffer[MCD_ROW_SIZE * 9];
    uint8_t offset[MCD_COL_SIZE];
    uint8_t n_rows;
    FILE* output;

} MCDSec;

#define MCD_SEC_AUTO(X) &(MCDSec) {        \
    .buffer =                              \
        "SCMCD       "                     \
        "PAYEE       "                     \
        "CHECK_NUMBER"                     \
        "PAYMENT_DATE"                     \
        "PCN      "                        \
        "ICN              "                \
        "               "                  \
        "PATIENT_ID"                       \
        "FI"                               \
        "MI"                               \
        "LAST_NAME      "                  \
        "FROM  "                           \
        "TO    "                           \
        "PROC  "                           \
        "  BILLED"                         \
        "    PAID"                         \
        "S"                                \
        "MOD"                              \
        "  ALLOW"                          \
        "  COPAY"                          \
        "    "                             \
        "\n"                             , \
    .offset = {                            \
        [MCD_COL_BPR_PAYER]        = 0x00, \
        [MCD_COL_BPR_PAYEE]        = 0x0c, \
        [MCD_COL_BPR_CHECK_NUMBER] = 0x18, \
        [MCD_COL_BPR_PAYMENT_DATE] = 0x24, \
        [MCD_COL_CLP_PCN]          = 0x30, \
        [MCD_COL_CLP_ICN]          = 0x39, \
        [MCD_COL_CLP_MRN]          = 0x4a, \
        [MCD_COL_CLP_PATIENT_ID]   = 0x59, \
        [MCD_COL_CLP_FI]           = 0x63, \
        [MCD_COL_CLP_MI]           = 0x65, \
        [MCD_COL_CLP_LAST_NAME]    = 0x67, \
        [MCD_COL_SVC_DATE_FROM]    = 0x76, \
        [MCD_COL_SVC_DATE_TO]      = 0x7c, \
        [MCD_COL_SVC_PROC_CD]      = 0x82, \
        [MCD_COL_SVC_BILLED_AMT]   = 0x88, \
        [MCD_COL_SVC_PAID_AMT]     = 0x90, \
        [MCD_COL_SVC_STS]          = 0x98, \
        [MCD_COL_SVC_MOD]          = 0x99, \
        [MCD_COL_SVC_ALLOW_AMT]    = 0x9c, \
        [MCD_COL_SVC_COPAY_AMT]    = 0xa3, \
        [MCD_COL_SVC_DETAIL_EOBS]  = 0xaa, \
        [MCD_COL_ZZZ]              = 0xae, \
    }                                    , \
    .n_rows = 0                          , \
    .output = X                            \
}

#endif // BARE_BONES_PDF_PARSER_H

int parse_mcd_sc(PDFFile* pdf, FILE* out);

#endif // BARE_BONES_PDF_MCD_SC_H
