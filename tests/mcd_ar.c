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

#include "mcd_ar.h"

#define MCD_END { (MCD_COL_ZZZ << 8) + 0xff }

#define MCD_FMT_HEAD_BPR_1 MCD_END
#define MCD_FMT_HEAD_BPR_2 MCD_END
#define MCD_FMT_HEAD_BPR_3                  \
{                                           \
    (MCD_COL_BPR_PAYER        << 8) + 0x0a, \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

#define MCD_FMT_HEAD_BPR_4 MCD_END
#define MCD_FMT_HEAD_BPR_5                  \
{                                           \
    (MCD_COL_BPR_PAYEE        << 8) + 0x76, \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

#define MCD_FMT_HEAD_BPR_6                  \
{                                           \
    (MCD_COL_BPR_NPI          << 8) + 0x79, \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

#define MCD_FMT_HEAD_BPR_7                  \
{                                           \
    (MCD_COL_BPR_CHECK_NUMBER << 8) + 0x79, \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

#define MCD_FMT_HEAD_BPR_8                  \
{                                           \
    (MCD_COL_BPR_PAYMENT_DATE << 8) + 0x79, \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

#define MCD_FMT_HCAD_CLP_1                  \
{                                           \
    (MCD_COL_CLP_PATIENT_NAME << 8) + 0x12, \
    (MCD_COL_CLP_PATIENT_ID   << 8) + 0x45, \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

#define MCD_FMT_HCAD_CLP_2                  \
{                                           \
    (MCD_COL_CLP_ICN          << 8) + 0x00, \
    (MCD_COL_CLP_PCN          << 8) + 0x0f, \
    (MCD_COL_CLP_MRN          << 8) + 0x1c, \
    (MCD_COL_SVC_DATE_FROM    << 8) + 0x2b, \
    (MCD_COL_SVC_DATE_TO      << 8) + 0x32, \
    (MCD_COL_SVC_BILLED_AMT   << 8) + 0x3d, \
    (MCD_COL_SVC_PAID_AMT     << 8) + 0x6e, \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

#define MCD_FMT_HCAD_CLP_3                  \
{                                           \
    (MCD_COL_SVC_PROC_CD      << 8) + 0x00, \
    (MCD_COL_SVC_MODIFIERS    << 8) + 0x08, \
    (MCD_COL_SVC_ALLOW_UNITS  << 8) + 0x23, \
    (MCD_COL_SVC_DETAIL_EOBS  << 8) + 0x23, \
    (MCD_COL_SVC_ALLOW_AMT    << 8) + 0x3d, \
    (MCD_COL_SVC_COPAY_AMT    << 8) + 0x5d, \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

#define MCD_FMT_HCPD_CLP_1                  \
{                                           \
    (MCD_COL_CLP_PATIENT_NAME << 8) + 0x12, \
    (MCD_COL_CLP_PATIENT_ID   << 8) + 0x45, \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

#define MCD_FMT_HCPD_CLP_2                  \
{                                           \
    (MCD_COL_CLP_ICN          << 8) + 0x00, \
    (MCD_COL_CLP_PCN          << 8) + 0x0f, \
    (MCD_COL_CLP_MRN          << 8) + 0x1c, \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

#define MCD_FMT_HCPD_CLP_3 MCD_END

#define MCD_FMT_HCPD_SVC_1                  \
{                                           \
    (MCD_COL_SVC_PROC_CD      << 8) + 0x00, \
    (MCD_COL_SVC_MODIFIERS    << 8) + 0x08, \
    (MCD_COL_SVC_DATE_FROM    << 8) + 0x15, \
    (MCD_COL_SVC_DATE_TO      << 8) + 0x1c, \
    (MCD_COL_SVC_ALLOW_UNITS  << 8) + 0x23, \
    (MCD_COL_SVC_DETAIL_EOBS  << 8) + 0x55, \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

#define MCD_FMT_HCPD_SVC_2                  \
{                                           \
    (MCD_COL_SVC_COPAY_AMT    << 8) + 0x22, \
    (MCD_COL_SVC_BILLED_AMT   << 8) + 0x2f, \
    (MCD_COL_SVC_ALLOW_AMT    << 8) + 0x3c, \
    (MCD_COL_SVC_PAID_AMT     << 8) + 0x49, \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

#define MCD_FMT_HCDN_CLP_1                  \
{                                           \
    (MCD_COL_CLP_PATIENT_NAME << 8) + 0x12, \
    (MCD_COL_CLP_PATIENT_ID   << 8) + 0x42, \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

#define MCD_FMT_HCDN_CLP_2                  \
{                                           \
    (MCD_COL_CLP_ICN          << 8) + 0x00, \
    (MCD_COL_CLP_PCN          << 8) + 0x0f, \
    (MCD_COL_CLP_MRN          << 8) + 0x1c, \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

#define MCD_FMT_HCDN_SVC_1                  \
{                                           \
    (MCD_COL_SVC_PROC_CD      << 8) + 0x00, \
    (MCD_COL_SVC_MODIFIERS    << 8) + 0x08, \
    (MCD_COL_SVC_ALLOW_UNITS  << 8) + 0x15, \
    (MCD_COL_SVC_DATE_FROM    << 8) + 0x21, \
    (MCD_COL_SVC_DATE_TO      << 8) + 0x28, \
    (MCD_COL_SVC_DETAIL_EOBS  << 8) + 0x53, \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

#define MCD_FMT_HCDN_SVC_2                  \
{                                           \
    (MCD_COL_SVC_COPAY_AMT    << 8) + 0x38, \
    (MCD_COL_SVC_ALLOW_AMT    << 8) + 0x38, \
    (MCD_COL_SVC_PAID_AMT     << 8) + 0x38, \
    (MCD_COL_SVC_BILLED_AMT   << 8) + 0x45, \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

static const uint16_t mcd_col_format[][8] = {

    [MCD_HEAD_BPR_1] = MCD_FMT_HEAD_BPR_1,
    [MCD_HEAD_BPR_2] = MCD_FMT_HEAD_BPR_2,
    [MCD_HEAD_BPR_3] = MCD_FMT_HEAD_BPR_3,
    [MCD_HEAD_BPR_4] = MCD_FMT_HEAD_BPR_4,
    [MCD_HEAD_BPR_5] = MCD_FMT_HEAD_BPR_5,
    [MCD_HEAD_BPR_6] = MCD_FMT_HEAD_BPR_6,
    [MCD_HEAD_BPR_7] = MCD_FMT_HEAD_BPR_7,
    [MCD_HEAD_BPR_8] = MCD_FMT_HEAD_BPR_8,
    [MCD_HCAD_CLP_1] = MCD_FMT_HCAD_CLP_1,
    [MCD_HCAD_CLP_2] = MCD_FMT_HCAD_CLP_2,
    [MCD_HCAD_CLP_3] = MCD_FMT_HCAD_CLP_3,
    [MCD_HCPD_CLP_1] = MCD_FMT_HCPD_CLP_1,
    [MCD_HCPD_CLP_2] = MCD_FMT_HCPD_CLP_2,
    [MCD_HCPD_CLP_3] = MCD_FMT_HCPD_CLP_3,
    [MCD_HCPD_SVC_1] = MCD_FMT_HCPD_SVC_1,
    [MCD_HCPD_SVC_2] = MCD_FMT_HCPD_SVC_2,
    [MCD_HCDN_CLP_1] = MCD_FMT_HCDN_CLP_1,
    [MCD_HCDN_CLP_2] = MCD_FMT_HCDN_CLP_2,
    [MCD_HCDN_SVC_1] = MCD_FMT_HCDN_SVC_1,
    [MCD_HCDN_SVC_2] = MCD_FMT_HCDN_SVC_2,

};

static const uint8_t mcd_line_format[][8] = {

    [MCD_HCAD_CLP_1] = { 0, 0,  81, 255,  16, ':',  67, ':' },
    [MCD_HCAD_CLP_2] = { 0, 0, 122, 255,  72, ')', 121, ')' },
    [MCD_HCAD_CLP_3] = { 0, 1, 122, 255,  72, ')',  43, ' ' },
    [MCD_HCPD_CLP_1] = { 0, 0,  81, 255,  16, ':',  67, ':' },
    [MCD_HCPD_CLP_2] = { 0, 0, 122, 255,  69, '.',  86, '.' },
    [MCD_HCPD_CLP_3] = { 0, 0,  70, 255,   0, ' ',  69, '.' },
    [MCD_HCPD_SVC_1] = { 1, 0, 105, 255,  27, ' ',  42, '.' },
    [MCD_HCPD_SVC_2] = { 0, 1,  85, 255,  55, '.',  81, '.' },
    [MCD_HCDN_CLP_1] = { 0, 0,  78, 255,  16, ':',  64, ':' },
    [MCD_HCDN_CLP_2] = { 0, 0,  87, 255,  49, ' ',  69, '.' },
    [MCD_HCDN_SVC_1] = { 0, 0, 103, 255,  28, '.',  39, ' ' },
    [MCD_HCDN_SVC_2] = { 1, 1,  81, 255,   0, ' ',  77, '.' },

};

static void mcd_write_line(MCDRow* row, PDFLine* line, MCDLine l) {

    const uint16_t* f = mcd_col_format[l];

    // each format must end with MCD_COL_ZZZ
    // or it's an infinite loop and will crash
    for (int i = 0; ; i++) {

        const MCDCol col = f[i] >> 8;
        if (col == MCD_COL_ZZZ) { break; }

        const uint8_t offset = row->offset[col];
        const size_t n_bytes = row->offset[col + 1] - offset;
        const uint8_t* start = line->cursor + (f[i] & 0x00ff);

        memcpy(row->buffer + offset, start, n_bytes);

    }

    if (!mcd_line_format[l][FWF_OUT]) { /* deferred fwrite */ }
    else { fwrite(row->buffer, 1, MCD_ROW_SIZE, row->output); }

}

static void mcd_parse_line(MCDRow* row, PDFLine* line, MCDLine l) {

    for (; l < INT32_MAX; l++) {

        const uint8_t* d = mcd_line_format[l];

        if      (line->n_bytes < d[FWF_MIN])             { }
        else if (line->n_bytes > d[FWF_MAX])             { }
        else if (line->cursor[d[FWF_I01]] != d[FWF_C01]) { }
        else if (line->cursor[d[FWF_I02]] != d[FWF_C02]) { }
        else    { return mcd_write_line(row, line, l); }

        if      (d[FWF_FIN]) { break; }

    }

}

static int mcd_parse_page(MCDRow* row, PDFPage* page) {

    PDFLine* line = NULL;

    if (pdf_next_line(page, &line) != PDF_OK) { return 1; }

    MCDLine l = 0;
    const uint8_t* c = line->cursor + 14;

    if (line->n_bytes < 20) { return 1; }
    else if (memcmp(c, "HCPD", 4) == 0) { l = MCD_HCPD_CLP_1; }
    else if (memcmp(c, "HCDN", 4) == 0) { l = MCD_HCDN_CLP_1; }
    else if (memcmp(c, "HCAD", 4) == 0) { l = MCD_HCAD_CLP_1; }
    else { return 1; }

    for (MCDLine h = MCD_HEAD_BPR_1; h <= MCD_HEAD_BPR_8; h++) {

        if (row->header == 0) { mcd_write_line(row, line, h); }
        if (pdf_next_line(page, &line) != PDF_OK) { return 1; }

    }

    row->header = 1;
    do { mcd_parse_line(row, line, l); }
    while (pdf_next_line(page, &line) == PDF_OK);

    return 0;

}

int parse_mcd_ar(PDFFile* pdf, FILE* out) {

    PDFPage* page = NULL;
    MCDRow* row = MCD_ROW_AUTO(out);

    while (pdf_next_page(pdf, &page) == PDF_OK)
        mcd_parse_page(row, page);

    return 0;

}
