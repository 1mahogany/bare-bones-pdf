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

#include "mcd_sc.h"

#define MCD_FMT_BPR_1                       \
{                                           \
    (MCD_COL_BPR_PAYEE        << 8) + 0x07, \
    (MCD_COL_BPR_CHECK_NUMBER << 8) + 0x26, \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

#define MCD_FMT_BPR_2                       \
{                                           \
    (MCD_COL_BPR_PAYMENT_DATE << 8) + 0x62, \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

#define MCD_FMT_BPR_3                       \
{                                           \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

#define MCD_FMT_BPR_4                       \
{                                           \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

#define MCD_FMT_CLP_1                       \
{                                           \
    (MCD_COL_CLP_PCN          << 8) + 0x02, \
    (MCD_COL_CLP_ICN          << 8) + 0x0c, \
    (MCD_COL_CLP_PATIENT_ID   << 8) + 0x4a, \
    (MCD_COL_CLP_FI           << 8) + 0x55, \
    (MCD_COL_CLP_MI           << 8) + 0x57, \
    (MCD_COL_CLP_LAST_NAME    << 8) + 0x59, \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

#define MCD_FMT_CLP_2                       \
{                                           \
    (MCD_COL_CLP_PCN          << 8) + 0x02, \
    (MCD_COL_CLP_ICN          << 8) + 0x0c, \
    (MCD_COL_CLP_PATIENT_ID   << 8) + 0x48, \
    (MCD_COL_CLP_LAST_NAME    << 8) + 0x53, \
    (MCD_COL_CLP_FI           << 8) + 0x5d, \
    (MCD_COL_CLP_MI           << 8) + 0x5f, \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

#define MCD_FMT_SVC_1                       \
{                                           \
    (MCD_COL_SVC_DATE_FROM    << 8) + 0x25, \
    (MCD_COL_SVC_DATE_TO      << 8) + 0x25, \
    (MCD_COL_SVC_PROC_CD      << 8) + 0x2f, \
    (MCD_COL_SVC_BILLED_AMT   << 8) + 0x36, \
    (MCD_COL_SVC_PAID_AMT     << 8) + 0x3f, \
    (MCD_COL_SVC_STS          << 8) + 0x48, \
    (MCD_COL_SVC_MOD          << 8) + 0x69, \
    (MCD_COL_SVC_ALLOW_AMT    << 8) + 0x6d, \
    (MCD_COL_SVC_COPAY_AMT    << 8) + 0x75, \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

#define MCD_FMT_SVC_2                       \
{                                           \
    (MCD_COL_SVC_DETAIL_EOBS  << 8) + 0x04, \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

#define MCD_FMT_SVC_3                       \
{                                           \
    (MCD_COL_SVC_DATE_FROM    << 8) + 0x22, \
    (MCD_COL_SVC_DATE_TO      << 8) + 0x22, \
    (MCD_COL_SVC_PROC_CD      << 8) + 0x2c, \
    (MCD_COL_SVC_BILLED_AMT   << 8) + 0x33, \
    (MCD_COL_SVC_PAID_AMT     << 8) + 0x3d, \
    (MCD_COL_SVC_STS          << 8) + 0x46, \
    (MCD_COL_SVC_MOD          << 8) + 0x62, \
    (MCD_COL_SVC_ALLOW_AMT    << 8) + 0x6e, \
    (MCD_COL_SVC_COPAY_AMT    << 8) + 0x6e, \
    (MCD_COL_ZZZ              << 8) + 0xff, \
}

static const uint16_t mcd_col_format[][10] = {
    
    [MCD_LINE_BPR_1] = MCD_FMT_BPR_1,
    [MCD_LINE_BPR_2] = MCD_FMT_BPR_2,
    [MCD_LINE_BPR_3] = MCD_FMT_BPR_3,
    [MCD_LINE_BPR_4] = MCD_FMT_BPR_4,
    [MCD_LINE_CLP_1] = MCD_FMT_CLP_1,
    [MCD_LINE_CLP_2] = MCD_FMT_CLP_2,
    [MCD_LINE_SVC_1] = MCD_FMT_SVC_1,
    [MCD_LINE_SVC_2] = MCD_FMT_SVC_2,
    [MCD_LINE_SVC_3] = MCD_FMT_SVC_3,

};

static const uint8_t mcd_line_format[][8] = {

    [MCD_LINE_BPR_1] = { 0, 0, 133, 255,   2, '#',  37, '#' },
    [MCD_LINE_BPR_2] = { 0, 0, 133, 255, 101, '/', 104, '/' },
    [MCD_LINE_BPR_3] = { 1, 0, 133, 255,  59, '.',  72, ' ' },
    [MCD_LINE_BPR_4] = { 1, 0, 133, 255,  56, '.',  70, ' ' },
    [MCD_LINE_CLP_1] = { 1, 0, 133, 255,  59, '.', 121, ' ' },
    [MCD_LINE_CLP_2] = { 1, 0, 133, 255,  56, '.',  34, ' ' },
    [MCD_LINE_SVC_1] = { 0, 1, 133, 255,  59, '.', 121, '.' },
    [MCD_LINE_SVC_2] = { 0, 0, 133, 255,  85, ' ',  91, ':' },
    [MCD_LINE_SVC_3] = { 0, 1, 133, 255,  56, '.',  72, ' ' },

};

static void mcd_write_sec(MCDSec* sec) {

    for (uint8_t i = 1; i <= sec->n_rows; i++) {

        const uint8_t* cur = sec->buffer + MCD_ROW_SIZE * i;
        const uint8_t n = sec->offset[MCD_COL_ZZZ] + 1;

        fwrite(cur, 1, n, sec->output);

    }

    const MCDCol col = MCD_COL_SVC_DETAIL_EOBS;

    uint8_t offset = sec->offset[col];
    size_t n_bytes = sec->offset[col + 1] - offset;
    uint8_t* start = sec->buffer + offset;

    memset(start, ' ', n_bytes);
    sec->n_rows = 0;

}

static void mcd_write_line(MCDSec* sec, PDFLine* line, MCDLine l) {

    const uint16_t* f = mcd_col_format[l];

    // each format must end with MCD_COL_ZZZ
    // or it's an infinite loop and will crash
    for (int i = 0; ; i++) {

        const MCDCol col = f[i] >> 8;
        if (col == MCD_COL_ZZZ) { break; }

        const uint8_t offset = sec->offset[col];
        const size_t n_bytes = sec->offset[col + 1] - offset;
        const uint8_t* start = line->cursor + (f[i] & 0x00ff);

        memcpy(sec->buffer + offset, start, n_bytes);

    }

    // CLP_LAST_NAME max out at 10 bytes with CLP_2
    // manually filling spaces for the remaining bytes
    if (l == MCD_LINE_CLP_2) {

        const MCDCol col = MCD_COL_CLP_LAST_NAME;

        uint8_t offset = sec->offset[col];
        size_t n_bytes = sec->offset[col + 1] - offset;
        uint8_t* start = sec->buffer + offset;

        // Field must have at least 10 bytes allocated space
        memset(start + 10, ' ', n_bytes - 10);

    }

    if (mcd_line_format[l][FWF_OUT]) {
        
        sec->n_rows++;
        const uint8_t n = sec->offset[MCD_COL_ZZZ] + 1;
        uint8_t* dest = sec->buffer + MCD_ROW_SIZE * sec->n_rows;
        
        memcpy(dest, sec->buffer, n);

    } else if (mcd_line_format[l][FWF_FIN]) { mcd_write_sec(sec); }

}

static void mcd_write_eob(MCDSec* sec, uint8_t* cur) {

    // safe-guard blanks, otherwise strtoul will return 0
    if (cur[0] != 'L') { return; }

    char index[3] = {0};
    memcpy(index, cur + 1, 2);
    const uint64_t i = strtoul(index, NULL, 10);

    const MCDCol c = MCD_COL_SVC_DETAIL_EOBS;
    const size_t n = sec->offset[c + 1] - sec->offset[c];
    uint8_t* dest = NULL;

    for (uint8_t j = 1; j <= sec->n_rows; j++) {

        if (i > 0 && i != j) { continue; }

        dest = sec->buffer + MCD_ROW_SIZE * j + sec->offset[c];
        memcpy(dest, cur + 4, n);

    }

}

static void mcd_parse_line(MCDSec* sec, PDFLine* line, MCDLine l) {

    for (; l < MCD_LINE_ZZZ_1; l++) {

        const uint8_t* d = mcd_line_format[l];

        if      (line->n_bytes < d[FWF_MIN])             { continue; }
        else if (line->n_bytes > d[FWF_MAX])             { continue; }
        else if (line->cursor[d[FWF_I01]] != d[FWF_C01]) { continue; }
        else if (line->cursor[d[FWF_I02]] != d[FWF_C02]) { continue; }

        if (l == MCD_LINE_SVC_2) {

            mcd_write_eob(sec, line->cursor +  93);
            mcd_write_eob(sec, line->cursor + 110);
        
        } else { mcd_write_line(sec, line, l); }

        break;

    }

}

int parse_mcd_sc(PDFFile* pdf, FILE* out) {

    PDFPage* page = NULL;
    PDFLine* line = NULL;
    MCDSec* sec = MCD_SEC_AUTO(out);
    
    while (pdf_next_page(pdf, &page) == PDF_OK)
        while (pdf_next_line(page, &line) == PDF_OK)
            mcd_parse_line(sec, line, 0);

    return 0;

}
