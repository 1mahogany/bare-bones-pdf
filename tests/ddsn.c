
#include "ddsn.h"

#define DDSN_FMT_BPR_1                       \
{                                            \
    (DDSN_COL_BPR_PAYEE        << 8) + 0x08, \
    (DDSN_COL_BPR_CHECK_NUMBER << 8) + 0x26, \
    (DDSN_COL_ZZZ              << 8) + 0xff, \
}

#define DDSN_FMT_BPR_2                       \
{                                            \
    (DDSN_COL_BPR_PAYMENT_DATE << 8) + 0x62, \
    (DDSN_COL_ZZZ              << 8) + 0xff, \
}

#define DDSN_FMT_BPR_3                       \
{                                            \
    (DDSN_COL_ZZZ              << 8) + 0xff, \
}

#define DDSN_FMT_BPR_4                       \
{                                            \
    (DDSN_COL_ZZZ              << 8) + 0xff, \
}

#define DDSN_FMT_CLP_1                       \
{                                            \
    (DDSN_COL_CLP_PCN          << 8) + 0x02, \
    (DDSN_COL_CLP_ICN          << 8) + 0x0c, \
    (DDSN_COL_CLP_PATIENT_ID   << 8) + 0x4a, \
    (DDSN_COL_CLP_FI           << 8) + 0x55, \
    (DDSN_COL_CLP_MI           << 8) + 0x57, \
    (DDSN_COL_CLP_LAST_NAME    << 8) + 0x59, \
    (DDSN_COL_ZZZ              << 8) + 0xff, \
}

#define DDSN_FMT_CLP_2                       \
{                                            \
    (DDSN_COL_CLP_PCN          << 8) + 0x02, \
    (DDSN_COL_CLP_ICN          << 8) + 0x0c, \
    (DDSN_COL_CLP_PATIENT_ID   << 8) + 0x48, \
    (DDSN_COL_CLP_LAST_NAME    << 8) + 0x53, \
    (DDSN_COL_CLP_FI           << 8) + 0x5d, \
    (DDSN_COL_CLP_MI           << 8) + 0x5f, \
    (DDSN_COL_ZZZ              << 8) + 0xff, \
}

#define DDSN_FMT_SVC_1                       \
{                                            \
    (DDSN_COL_SVC_DATE_FROM    << 8) + 0x25, \
    (DDSN_COL_SVC_DATE_TO      << 8) + 0x25, \
    (DDSN_COL_SVC_PROC_CD      << 8) + 0x2f, \
    (DDSN_COL_SVC_BILLED_AMT   << 8) + 0x36, \
    (DDSN_COL_SVC_PAID_AMT     << 8) + 0x3f, \
    (DDSN_COL_SVC_STS          << 8) + 0x48, \
    (DDSN_COL_SVC_MOD          << 8) + 0x69, \
    (DDSN_COL_SVC_ALLOW_AMT    << 8) + 0x6d, \
    (DDSN_COL_SVC_COPAY_AMT    << 8) + 0x75, \
    (DDSN_COL_ZZZ              << 8) + 0xff, \
}

#define DDSN_FMT_SVC_2                       \
{                                            \
    (DDSN_COL_SVC_DETAIL_EOBS  << 8) + 0x04, \
    (DDSN_COL_ZZZ              << 8) + 0xff, \
}

#define DDSN_FMT_SVC_3                       \
{                                            \
    (DDSN_COL_SVC_DATE_FROM    << 8) + 0x22, \
    (DDSN_COL_SVC_DATE_TO      << 8) + 0x22, \
    (DDSN_COL_SVC_PROC_CD      << 8) + 0x2c, \
    (DDSN_COL_SVC_BILLED_AMT   << 8) + 0x33, \
    (DDSN_COL_SVC_PAID_AMT     << 8) + 0x3d, \
    (DDSN_COL_SVC_STS          << 8) + 0x46, \
    (DDSN_COL_SVC_MOD          << 8) + 0x62, \
    (DDSN_COL_SVC_ALLOW_AMT    << 8) + 0x6e, \
    (DDSN_COL_SVC_COPAY_AMT    << 8) + 0x6e, \
    (DDSN_COL_ZZZ              << 8) + 0xff, \
}

static const uint16_t ddsn_col_format[][10] = {
    
    [DDSN_LINE_BPR_1] = DDSN_FMT_BPR_1,
    [DDSN_LINE_BPR_2] = DDSN_FMT_BPR_2,
    [DDSN_LINE_BPR_3] = DDSN_FMT_BPR_3,
    [DDSN_LINE_BPR_4] = DDSN_FMT_BPR_4,
    [DDSN_LINE_CLP_1] = DDSN_FMT_CLP_1,
    [DDSN_LINE_CLP_2] = DDSN_FMT_CLP_2,
    [DDSN_LINE_SVC_1] = DDSN_FMT_SVC_1,
    [DDSN_LINE_SVC_2] = DDSN_FMT_SVC_2,
    [DDSN_LINE_SVC_3] = DDSN_FMT_SVC_3,

};

static const uint8_t ddsn_line_format[][8] = {

    [DDSN_LINE_BPR_1] = { 0, 0, 133, 255,   2, '#',  37, '#' },
    [DDSN_LINE_BPR_2] = { 0, 0, 133, 255, 101, '/', 104, '/' },
    [DDSN_LINE_BPR_3] = { 1, 0, 133, 255,  59, '.',  72, ' ' },
    [DDSN_LINE_BPR_4] = { 1, 0, 133, 255,  56, '.',  70, ' ' },
    [DDSN_LINE_CLP_1] = { 1, 0, 133, 255,  59, '.', 121, ' ' },
    [DDSN_LINE_CLP_2] = { 1, 0, 133, 255,  56, '.',  34, ' ' },
    [DDSN_LINE_SVC_1] = { 0, 1, 133, 255,  59, '.', 121, '.' },
    [DDSN_LINE_SVC_2] = { 0, 0, 133, 255,  85, ' ',  91, ':' },
    [DDSN_LINE_SVC_3] = { 0, 1, 133, 255,  56, '.',  72, ' ' },

};

static void ddsn_write_sec(DDSNSec* sec) {

    uint8_t n = sec->offset[DDSN_COL_ZZZ] + 1;

    for (uint8_t i = 1; i <= sec->n_rows; i++) {

        const uint8_t* cur = sec->buffer + DDSN_ROW_SIZE * i;
        fwrite(cur, 1, n, sec->output);

    }

    const DDSNCol c = DDSN_COL_SVC_DETAIL_EOBS;
    n = sec->offset[c + 1] - sec->offset[c];
    uint8_t* dest = sec->buffer + sec->offset[c];

    for (uint8_t i = 0; i < n; i++) { dest[i] = ' '; }
    sec->n_rows = 0;

}

static void ddsn_write_line(DDSNSec* sec, PDFLine* line, DDSNLine l) {

    const uint16_t* f = ddsn_col_format[l];

    // each format must end with DDSN_COL_ZZZ
    // or it's an infinite loop and will crash
    for (int i = 0; ; i++) {

        const DDSNCol col = f[i] >> 8;
        if (col == DDSN_COL_ZZZ) { break; }

        const uint8_t offset = sec->offset[col];
        const size_t n_bytes = sec->offset[col + 1] - offset;
        const uint8_t* start = line->cursor + (f[i] & 0x00ff);

        memcpy(sec->buffer + offset, start, n_bytes);

    }

    if (ddsn_line_format[l][FWF_OUT]) {
        
        sec->n_rows++;
        const uint8_t n = sec->offset[DDSN_COL_ZZZ] + 1;
        uint8_t* dest = sec->buffer + DDSN_ROW_SIZE * sec->n_rows;
        
        memcpy(dest, sec->buffer, n);

    } else if (ddsn_line_format[l][FWF_FIN]) { ddsn_write_sec(sec); }

}

static void ddsn_write_eob(DDSNSec* sec, uint8_t* cur) {

    // safe-guard blanks, otherwise strtoul will return 0
    if (cur[0] != 'L') { return; }

    char index[3] = {0};
    memcpy(index, cur + 1, 2);
    const uint64_t i = strtoul(index, NULL, 10);

    const DDSNCol c = DDSN_COL_SVC_DETAIL_EOBS;
    const size_t n = sec->offset[c + 1] - sec->offset[c];
    uint8_t* dest = NULL;

    for (uint8_t j = 1; j <= sec->n_rows; j++) {

        if (i > 0 && i != j) { continue; }

        dest = sec->buffer + DDSN_ROW_SIZE * j + sec->offset[c];
        memcpy(dest, cur + 4, n);

    }

}

static void ddsn_parse_line(DDSNSec* sec, PDFLine* line, DDSNLine l) {

    for (; l < DDSN_LINE_ZZZ_1; l++) {

        const uint8_t* d = ddsn_line_format[l];

        if      (line->n_bytes < d[FWF_MIN])             { continue; }
        else if (line->n_bytes > d[FWF_MAX])             { continue; }
        else if (line->cursor[d[FWF_I01]] != d[FWF_C01]) { continue; }
        else if (line->cursor[d[FWF_I02]] != d[FWF_C02]) { continue; }

        if (l == DDSN_LINE_SVC_2) {

            ddsn_write_eob(sec, line->cursor +  93);
            ddsn_write_eob(sec, line->cursor + 110);
        
        } else { ddsn_write_line(sec, line, l); }

        break;

    }

}

int ddsn_parse_file(PDFFile* pdf, FILE* out) {

    PDFPage* page = NULL;
    PDFLine* line = NULL;
    DDSNSec* sec = DDSN_SEC_AUTO(out);
    
    while (pdf_next_page(pdf, &page) == PDF_OK)
        while (pdf_next_line(page, &line) == PDF_OK)
            ddsn_parse_line(sec, line, 0);

    return 0;

}
