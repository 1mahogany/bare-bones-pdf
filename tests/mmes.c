
#include <stdint.h>
#include <string.h>

#include "mmes.h"

//* max 8 fields in a single line
//* mostly to reduce/limit array size
#define FORMAT_SIZE 8
#define FWF_END { (FWF_COL_ZZZ << 8) + 0xff }

#define FWF_FORMAT_HEAD_BPR_1 FWF_END
#define FWF_FORMAT_HEAD_BPR_2 FWF_END
#define FWF_FORMAT_HEAD_BPR_3               \
{                                           \
    (FWF_COL_BPR_PAYER        << 8) + 0x0a, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HEAD_BPR_4 FWF_END
#define FWF_FORMAT_HEAD_BPR_5               \
{                                           \
    (FWF_COL_BPR_PAYEE        << 8) + 0x77, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HEAD_BPR_6               \
{                                           \
    (FWF_COL_BPR_NPI          << 8) + 0x7a, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HEAD_BPR_7 FWF_END
#define FWF_FORMAT_HEAD_BPR_8               \
{                                           \
    (FWF_COL_BPR_CHECK_NUMBER << 8) + 0x7a, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HEAD_BPR_9               \
{                                           \
    (FWF_COL_BPR_PAYMENT_DATE << 8) + 0x7a, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HCAD_CAS_2               \
{                                           \
    (FWF_COL_CLP_ICN          << 8) + 0x00, \
    (FWF_COL_CLP_MRN          << 8) + 0x0f, \
    (FWF_COL_SVC_DATE_FROM    << 8) + 0x2b, \
    (FWF_COL_SVC_DATE_TO      << 8) + 0x33, \
    (FWF_COL_SVC_BILLED_AMT   << 8) + 0x3d, \
    (FWF_COL_SVC_ALLOW_AMT    << 8) + 0x4d, \
    (FWF_COL_SVC_COPAY_AMT    << 8) + 0x6a, \
    (FWF_COL_SVC_PAID_AMT     << 8) + 0x7a, \
}

#define FWF_FORMAT_HCPD_CLP_1               \
{                                           \
    (FWF_COL_CLP_PATIENT_NAME << 8) + 0x0d, \
    (FWF_COL_CLP_PATIENT_ID   << 8) + 0x3c, \
    (FWF_COL_CLP_PCN          << 8) + 0x5e, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HCPD_CLP_2               \
{                                           \
    (FWF_COL_CLP_ICN          << 8) + 0x00, \
    (FWF_COL_CLP_MRN          << 8) + 0x0f, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HCPD_SVC_1               \
{                                           \
    (FWF_COL_SVC_PROC_CD      << 8) + 0x04, \
    (FWF_COL_SVC_MODIFIERS    << 8) + 0x0c, \
    (FWF_COL_SVC_ALLOW_UNITS  << 8) + 0x16, \
    (FWF_COL_SVC_DETAIL_EOBS  << 8) + 0x5e, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HCPD_SVC_2               \
{                                           \
    (FWF_COL_SVC_DATE_FROM    << 8) + 0x04, \
    (FWF_COL_SVC_DATE_TO      << 8) + 0x0b, \
    (FWF_COL_SVC_BILLED_AMT   << 8) + 0x12, \
    (FWF_COL_SVC_ALLOW_AMT    << 8) + 0x1f, \
    (FWF_COL_SVC_COPAY_AMT    << 8) + 0x45, \
    (FWF_COL_SVC_PAID_AMT     << 8) + 0x51, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HCDN_CLP_1               \
{                                           \
    (FWF_COL_CLP_PATIENT_NAME << 8) + 0x0d, \
    (FWF_COL_CLP_PATIENT_ID   << 8) + 0x3c, \
    (FWF_COL_CLP_PCN          << 8) + 0x5e, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HCDN_CLP_2               \
{                                           \
    (FWF_COL_CLP_ICN          << 8) + 0x00, \
    (FWF_COL_CLP_MRN          << 8) + 0x0f, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HCDN_SVC_1               \
{                                           \
    (FWF_COL_SVC_PROC_CD      << 8) + 0x04, \
    (FWF_COL_SVC_MODIFIERS    << 8) + 0x0c, \
    (FWF_COL_SVC_ALLOW_UNITS  << 8) + 0x16, \
    (FWF_COL_SVC_DETAIL_EOBS  << 8) + 0x53, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HCDN_SVC_2               \
{                                           \
    (FWF_COL_SVC_DATE_FROM    << 8) + 0x04, \
    (FWF_COL_SVC_DATE_TO      << 8) + 0x0b, \
    (FWF_COL_SVC_BILLED_AMT   << 8) + 0x12, \
    (FWF_COL_SVC_ALLOW_AMT    << 8) + 0x79, \
    (FWF_COL_SVC_COPAY_AMT    << 8) + 0x79, \
    (FWF_COL_SVC_PAID_AMT     << 8) + 0x79, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}


static const uint16_t fwf_col_format[][FORMAT_SIZE] = {

    [MMES_HEAD_BPR_1] = FWF_FORMAT_HEAD_BPR_1,
    [MMES_HEAD_BPR_2] = FWF_FORMAT_HEAD_BPR_2,
    [MMES_HEAD_BPR_3] = FWF_FORMAT_HEAD_BPR_3,
    [MMES_HEAD_BPR_4] = FWF_FORMAT_HEAD_BPR_4,
    [MMES_HEAD_BPR_5] = FWF_FORMAT_HEAD_BPR_5,
    [MMES_HEAD_BPR_6] = FWF_FORMAT_HEAD_BPR_6,
    [MMES_HEAD_BPR_7] = FWF_FORMAT_HEAD_BPR_7,
    [MMES_HEAD_BPR_8] = FWF_FORMAT_HEAD_BPR_8,
    [MMES_HEAD_BPR_9] = FWF_FORMAT_HEAD_BPR_9,
    [MMES_HCAD_CAS_2] = FWF_FORMAT_HCAD_CAS_2,
    [MMES_HCPD_CLP_1] = FWF_FORMAT_HCPD_CLP_1,
    [MMES_HCPD_CLP_2] = FWF_FORMAT_HCPD_CLP_2,
    [MMES_HCPD_SVC_1] = FWF_FORMAT_HCPD_SVC_1,
    [MMES_HCPD_SVC_2] = FWF_FORMAT_HCPD_SVC_2,
    [MMES_HCDN_CLP_1] = FWF_FORMAT_HCDN_CLP_1,
    [MMES_HCDN_CLP_2] = FWF_FORMAT_HCDN_CLP_2,
    [MMES_HCDN_SVC_1] = FWF_FORMAT_HCDN_SVC_1,
    [MMES_HCDN_SVC_2] = FWF_FORMAT_HCDN_SVC_2,

};

static const uint8_t fwf_line_format[][FORMAT_SIZE] = {

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

static void fwf_write_line(FWFRow* fwf, PDFLine* line, MMESLine l) {

    const uint16_t* f = fwf_col_format[l];

    for (int i = 0; i < FORMAT_SIZE; i++) {

        const FWFCol col = f[i] >> 8;
        if (col == FWF_COL_ZZZ) { break; }

        const uint8_t offset = fwf->offset[col];
        const size_t n_bytes = fwf->offset[col + 1] - offset;
        const uint8_t* start = line->cursor + (f[i] & 0x00ff);

        memcpy(fwf->buffer + offset, start, n_bytes);

    }

    if (!fwf_line_format[l][FWF_OUT]) { /* deferred fwrite */ }
    else { fwrite(fwf->buffer, 1, FWF_ROW_SIZE, fwf->output); }

}

static void fwf_parse_line(FWFRow* fwf, PDFLine* line, MMESLine l) {

    for (; l < INT32_MAX; l++) {

        const uint8_t* d = fwf_line_format[l];

        if      (line->n_bytes < d[FWF_MIN])             { }
        else if (line->n_bytes > d[FWF_MAX])             { }
        else if (line->cursor[d[FWF_I01]] != d[FWF_C01]) { }
        else if (line->cursor[d[FWF_I02]] != d[FWF_C02]) { }
        else    { return fwf_write_line(fwf, line, l); }

        if      (d[FWF_FIN]) { break; }

    }

}

int fwf_parse_mmes(FWFRow* fwf, PDFPage* page) {

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

        if (fwf->header == 0) { fwf_write_line(fwf, line, h); }
        if (pdf_next_line(page, &line) != PDF_OK) { return 1; }

    }

    fwf->header = 1;
    do { fwf_parse_line(fwf, line, l); }
    while (pdf_next_line(page, &line) == PDF_OK);

    return 0;

}
