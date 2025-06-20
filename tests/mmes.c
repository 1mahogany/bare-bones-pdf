
#include "mmes.h"

#define MMES_END { (MMES_COL_ZZZ << 8) + 0xff }

#define MMES_FMT_HEAD_BPR_1 MMES_END
#define MMES_FMT_HEAD_BPR_2 MMES_END
#define MMES_FMT_HEAD_BPR_3                  \
{                                            \
    (MMES_COL_BPR_PAYER        << 8) + 0x0a, \
    (MMES_COL_ZZZ              << 8) + 0xff, \
}

#define MMES_FMT_HEAD_BPR_4 MMES_END
#define MMES_FMT_HEAD_BPR_5                  \
{                                            \
    (MMES_COL_BPR_PAYEE        << 8) + 0x77, \
    (MMES_COL_ZZZ              << 8) + 0xff, \
}

#define MMES_FMT_HEAD_BPR_6                  \
{                                            \
    (MMES_COL_BPR_NPI          << 8) + 0x7a, \
    (MMES_COL_ZZZ              << 8) + 0xff, \
}

#define MMES_FMT_HEAD_BPR_7 MMES_END
#define MMES_FMT_HEAD_BPR_8                  \
{                                            \
    (MMES_COL_BPR_CHECK_NUMBER << 8) + 0x7a, \
    (MMES_COL_ZZZ              << 8) + 0xff, \
}

#define MMES_FMT_HEAD_BPR_9                  \
{                                            \
    (MMES_COL_BPR_PAYMENT_DATE << 8) + 0x7a, \
    (MMES_COL_ZZZ              << 8) + 0xff, \
}

#define MMES_FMT_HCAD_CAS_2                  \
{                                            \
    (MMES_COL_CLP_ICN          << 8) + 0x00, \
    (MMES_COL_CLP_MRN          << 8) + 0x0f, \
    (MMES_COL_SVC_DATE_FROM    << 8) + 0x2b, \
    (MMES_COL_SVC_DATE_TO      << 8) + 0x33, \
    (MMES_COL_SVC_BILLED_AMT   << 8) + 0x3d, \
    (MMES_COL_SVC_ALLOW_AMT    << 8) + 0x4d, \
    (MMES_COL_SVC_COPAY_AMT    << 8) + 0x6a, \
    (MMES_COL_SVC_PAID_AMT     << 8) + 0x7a, \
    (MMES_COL_ZZZ              << 8) + 0xff, \
}

#define MMES_FMT_HCPD_CLP_1                  \
{                                            \
    (MMES_COL_CLP_PATIENT_NAME << 8) + 0x0d, \
    (MMES_COL_CLP_PATIENT_ID   << 8) + 0x3c, \
    (MMES_COL_CLP_PCN          << 8) + 0x5e, \
    (MMES_COL_ZZZ              << 8) + 0xff, \
}

#define MMES_FMT_HCPD_CLP_2                  \
{                                            \
    (MMES_COL_CLP_ICN          << 8) + 0x00, \
    (MMES_COL_CLP_MRN          << 8) + 0x0f, \
    (MMES_COL_ZZZ              << 8) + 0xff, \
}

#define MMES_FMT_HCPD_SVC_1                  \
{                                            \
    (MMES_COL_SVC_PROC_CD      << 8) + 0x04, \
    (MMES_COL_SVC_MODIFIERS    << 8) + 0x0c, \
    (MMES_COL_SVC_ALLOW_UNITS  << 8) + 0x16, \
    (MMES_COL_SVC_DETAIL_EOBS  << 8) + 0x5e, \
    (MMES_COL_ZZZ              << 8) + 0xff, \
}

#define MMES_FMT_HCPD_SVC_2                  \
{                                            \
    (MMES_COL_SVC_DATE_FROM    << 8) + 0x04, \
    (MMES_COL_SVC_DATE_TO      << 8) + 0x0b, \
    (MMES_COL_SVC_BILLED_AMT   << 8) + 0x12, \
    (MMES_COL_SVC_ALLOW_AMT    << 8) + 0x1f, \
    (MMES_COL_SVC_COPAY_AMT    << 8) + 0x45, \
    (MMES_COL_SVC_PAID_AMT     << 8) + 0x51, \
    (MMES_COL_ZZZ              << 8) + 0xff, \
}

#define MMES_FMT_HCDN_CLP_1                  \
{                                            \
    (MMES_COL_CLP_PATIENT_NAME << 8) + 0x0d, \
    (MMES_COL_CLP_PATIENT_ID   << 8) + 0x3c, \
    (MMES_COL_CLP_PCN          << 8) + 0x5e, \
    (MMES_COL_ZZZ              << 8) + 0xff, \
}

#define MMES_FMT_HCDN_CLP_2                  \
{                                            \
    (MMES_COL_CLP_ICN          << 8) + 0x00, \
    (MMES_COL_CLP_MRN          << 8) + 0x0f, \
    (MMES_COL_ZZZ              << 8) + 0xff, \
}

#define MMES_FMT_HCDN_SVC_1                  \
{                                            \
    (MMES_COL_SVC_PROC_CD      << 8) + 0x04, \
    (MMES_COL_SVC_MODIFIERS    << 8) + 0x0c, \
    (MMES_COL_SVC_ALLOW_UNITS  << 8) + 0x16, \
    (MMES_COL_SVC_DETAIL_EOBS  << 8) + 0x53, \
    (MMES_COL_ZZZ              << 8) + 0xff, \
}

#define MMES_FMT_HCDN_SVC_2                  \
{                                            \
    (MMES_COL_SVC_DATE_FROM    << 8) + 0x04, \
    (MMES_COL_SVC_DATE_TO      << 8) + 0x0b, \
    (MMES_COL_SVC_BILLED_AMT   << 8) + 0x12, \
    (MMES_COL_SVC_ALLOW_AMT    << 8) + 0x79, \
    (MMES_COL_SVC_COPAY_AMT    << 8) + 0x79, \
    (MMES_COL_SVC_PAID_AMT     << 8) + 0x79, \
    (MMES_COL_ZZZ              << 8) + 0xff, \
}

static const uint16_t mmes_col_format[][9] = {

    [MMES_HEAD_BPR_1] = MMES_FMT_HEAD_BPR_1,
    [MMES_HEAD_BPR_2] = MMES_FMT_HEAD_BPR_2,
    [MMES_HEAD_BPR_3] = MMES_FMT_HEAD_BPR_3,
    [MMES_HEAD_BPR_4] = MMES_FMT_HEAD_BPR_4,
    [MMES_HEAD_BPR_5] = MMES_FMT_HEAD_BPR_5,
    [MMES_HEAD_BPR_6] = MMES_FMT_HEAD_BPR_6,
    [MMES_HEAD_BPR_7] = MMES_FMT_HEAD_BPR_7,
    [MMES_HEAD_BPR_8] = MMES_FMT_HEAD_BPR_8,
    [MMES_HEAD_BPR_9] = MMES_FMT_HEAD_BPR_9,
    [MMES_HCAD_CAS_2] = MMES_FMT_HCAD_CAS_2,
    [MMES_HCPD_CLP_1] = MMES_FMT_HCPD_CLP_1,
    [MMES_HCPD_CLP_2] = MMES_FMT_HCPD_CLP_2,
    [MMES_HCPD_SVC_1] = MMES_FMT_HCPD_SVC_1,
    [MMES_HCPD_SVC_2] = MMES_FMT_HCPD_SVC_2,
    [MMES_HCDN_CLP_1] = MMES_FMT_HCDN_CLP_1,
    [MMES_HCDN_CLP_2] = MMES_FMT_HCDN_CLP_2,
    [MMES_HCDN_SVC_1] = MMES_FMT_HCDN_SVC_1,
    [MMES_HCDN_SVC_2] = MMES_FMT_HCDN_SVC_2,

};

static const uint8_t mmes_line_format[][8] = {

    [MMES_HCAD_CAS_2] = { 0, 1, 134, 255, 50, ' ', 88, ')' },
    [MMES_HCPD_CLP_1] = { 0, 0, 114, 255, 11, ':', 58, ':' },
    [MMES_HCPD_CLP_2] = { 0, 0, 134, 255, 50, ' ', 69, '.' },
    [MMES_HCPD_SVC_1] = { 0, 0, 133, 255, 11, ' ', 28, '.' },
    [MMES_HCPD_SVC_2] = { 1, 1, 128, 255, 10, '-', 27, '.' },
    [MMES_HCDN_CLP_1] = { 0, 0, 114, 255, 11, ':', 58, ':' },
    [MMES_HCDN_CLP_2] = { 0, 0, 108, 255, 50, ' ', 69, '.' },
    [MMES_HCDN_SVC_1] = { 0, 0, 134, 255, 11, ' ', 28, '.' },
    [MMES_HCDN_SVC_2] = { 1, 1, 133, 255, 10, '-', 27, '.' },

};

static void mmes_write_line(MMESRow* row, PDFLine* line, MMESLine l) {

    const uint16_t* f = mmes_col_format[l];

    // each format must end with MMES_COL_ZZZ
    // or it's an infinite loop and will crash
    for (int i = 0; ; i++) {

        const MMESCol col = f[i] >> 8;
        if (col == MMES_COL_ZZZ) { break; }

        const uint8_t offset = row->offset[col];
        const size_t n_bytes = row->offset[col + 1] - offset;
        const uint8_t* start = line->cursor + (f[i] & 0x00ff);

        memcpy(row->buffer + offset, start, n_bytes);

    }

    if (!mmes_line_format[l][FWF_OUT]) { /* deferred fwrite */ }
    else { fwrite(row->buffer, 1, MMES_ROW_SIZE, row->output); }

}

static void mmes_parse_line(MMESRow* row, PDFLine* line, MMESLine l) {

    for (; l < INT32_MAX; l++) {

        const uint8_t* d = mmes_line_format[l];

        if      (line->n_bytes < d[FWF_MIN])             { }
        else if (line->n_bytes > d[FWF_MAX])             { }
        else if (line->cursor[d[FWF_I01]] != d[FWF_C01]) { }
        else if (line->cursor[d[FWF_I02]] != d[FWF_C02]) { }
        else    { return mmes_write_line(row, line, l); }

        if      (d[FWF_FIN]) { break; }

    }

}

static int mmes_parse_page(MMESRow* row, PDFPage* page) {

    PDFLine* line = NULL;

    if (pdf_next_line(page, &line) != PDF_OK) { return 1; }

    MMESLine l = 0;
    const uint8_t* c = line->cursor + 14;

    if (line->n_bytes < 20) { return 1; }
    else if (memcmp(c, "HCPD", 4) == 0) { l = MMES_HCPD_CLP_1; }
    else if (memcmp(c, "HCDN", 4) == 0) { l = MMES_HCDN_CLP_1; }
    else if (memcmp(c, "HCAD", 4) == 0) { l = MMES_HCAD_CAS_2; }
    else { return 1; }

    for (MMESLine h = MMES_HEAD_BPR_1; h <= MMES_HEAD_BPR_9; h++) {

        if (row->header == 0) { mmes_write_line(row, line, h); }
        if (pdf_next_line(page, &line) != PDF_OK) { return 1; }

    }

    row->header = 1;
    do { mmes_parse_line(row, line, l); }
    while (pdf_next_line(page, &line) == PDF_OK);

    return 0;

}

int mmes_parse_file(PDFFile* pdf, FILE* out) {

    PDFPage* page = NULL;
    MMESRow* row = MMES_ROW_AUTO(out);

    while (pdf_next_page(pdf, &page) == PDF_OK)
        mmes_parse_page(row, page);

    return 0;

}
