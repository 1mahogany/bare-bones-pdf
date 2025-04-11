
#include <stdint.h>
#include <string.h>

#include "txix.h"

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
    (FWF_COL_BPR_PAYEE        << 8) + 0x76, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HEAD_BPR_6               \
{                                           \
    (FWF_COL_BPR_NPI          << 8) + 0x79, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HEAD_BPR_7               \
{                                           \
    (FWF_COL_BPR_CHECK_NUMBER << 8) + 0x79, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HEAD_BPR_8               \
{                                           \
    (FWF_COL_BPR_PAYMENT_DATE << 8) + 0x79, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HCAD_CLP_1               \
{                                           \
    (FWF_COL_CLP_PATIENT_NAME << 8) + 0x12, \
    (FWF_COL_CLP_PATIENT_ID   << 8) + 0x45, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HCAD_CLP_2               \
{                                           \
    (FWF_COL_CLP_ICN          << 8) + 0x00, \
    (FWF_COL_CLP_PCN          << 8) + 0x0f, \
    (FWF_COL_CLP_MRN          << 8) + 0x1c, \
    (FWF_COL_SVC_DATE_FROM    << 8) + 0x2b, \
    (FWF_COL_SVC_DATE_TO      << 8) + 0x32, \
    (FWF_COL_SVC_BILLED_AMT   << 8) + 0x3d, \
    (FWF_COL_SVC_PAID_AMT     << 8) + 0x6e, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HCAD_CLP_3               \
{                                           \
    (FWF_COL_SVC_PROC_CD      << 8) + 0x00, \
    (FWF_COL_SVC_MODIFIERS    << 8) + 0x08, \
    (FWF_COL_SVC_ALLOW_UNITS  << 8) + 0x23, \
    (FWF_COL_SVC_DETAIL_EOBS  << 8) + 0x23, \
    (FWF_COL_SVC_ALLOW_AMT    << 8) + 0x3d, \
    (FWF_COL_SVC_COPAY_AMT    << 8) + 0x5d, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HCPD_CLP_1               \
{                                           \
    (FWF_COL_CLP_PATIENT_NAME << 8) + 0x12, \
    (FWF_COL_CLP_PATIENT_ID   << 8) + 0x45, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HCPD_CLP_2               \
{                                           \
    (FWF_COL_CLP_ICN          << 8) + 0x00, \
    (FWF_COL_CLP_PCN          << 8) + 0x0f, \
    (FWF_COL_CLP_MRN          << 8) + 0x1c, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HCPD_CLP_3 FWF_END

#define FWF_FORMAT_HCPD_SVC_1               \
{                                           \
    (FWF_COL_SVC_PROC_CD      << 8) + 0x00, \
    (FWF_COL_SVC_MODIFIERS    << 8) + 0x08, \
    (FWF_COL_SVC_DATE_FROM    << 8) + 0x15, \
    (FWF_COL_SVC_DATE_TO      << 8) + 0x1c, \
    (FWF_COL_SVC_ALLOW_UNITS  << 8) + 0x23, \
    (FWF_COL_SVC_DETAIL_EOBS  << 8) + 0x55, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HCPD_SVC_2               \
{                                           \
    (FWF_COL_SVC_COPAY_AMT    << 8) + 0x22, \
    (FWF_COL_SVC_BILLED_AMT   << 8) + 0x2f, \
    (FWF_COL_SVC_ALLOW_AMT    << 8) + 0x3c, \
    (FWF_COL_SVC_PAID_AMT     << 8) + 0x49, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HCDN_CLP_1               \
{                                           \
    (FWF_COL_CLP_PATIENT_NAME << 8) + 0x12, \
    (FWF_COL_CLP_PATIENT_ID   << 8) + 0x42, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HCDN_CLP_2               \
{                                           \
    (FWF_COL_CLP_ICN          << 8) + 0x00, \
    (FWF_COL_CLP_PCN          << 8) + 0x0f, \
    (FWF_COL_CLP_MRN          << 8) + 0x1c, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HCDN_SVC_1               \
{                                           \
    (FWF_COL_SVC_PROC_CD      << 8) + 0x00, \
    (FWF_COL_SVC_MODIFIERS    << 8) + 0x08, \
    (FWF_COL_SVC_ALLOW_UNITS  << 8) + 0x15, \
    (FWF_COL_SVC_DATE_FROM    << 8) + 0x21, \
    (FWF_COL_SVC_DATE_TO      << 8) + 0x28, \
    (FWF_COL_SVC_DETAIL_EOBS  << 8) + 0x53, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

#define FWF_FORMAT_HCDN_SVC_2               \
{                                           \
    (FWF_COL_SVC_COPAY_AMT    << 8) + 0x38, \
    (FWF_COL_SVC_ALLOW_AMT    << 8) + 0x38, \
    (FWF_COL_SVC_PAID_AMT     << 8) + 0x38, \
    (FWF_COL_SVC_BILLED_AMT   << 8) + 0x45, \
    (FWF_COL_ZZZ              << 8) + 0xff, \
}

static const uint16_t fwf_col_format[][FORMAT_SIZE] = {

    [TXIX_HEAD_BPR_1] = FWF_FORMAT_HEAD_BPR_1,
    [TXIX_HEAD_BPR_2] = FWF_FORMAT_HEAD_BPR_2,
    [TXIX_HEAD_BPR_3] = FWF_FORMAT_HEAD_BPR_3,
    [TXIX_HEAD_BPR_4] = FWF_FORMAT_HEAD_BPR_4,
    [TXIX_HEAD_BPR_5] = FWF_FORMAT_HEAD_BPR_5,
    [TXIX_HEAD_BPR_6] = FWF_FORMAT_HEAD_BPR_6,
    [TXIX_HEAD_BPR_7] = FWF_FORMAT_HEAD_BPR_7,
    [TXIX_HEAD_BPR_8] = FWF_FORMAT_HEAD_BPR_8,
    [TXIX_HCAD_CLP_1] = FWF_FORMAT_HCAD_CLP_1,
    [TXIX_HCAD_CLP_2] = FWF_FORMAT_HCAD_CLP_2,
    [TXIX_HCAD_CLP_3] = FWF_FORMAT_HCAD_CLP_3,
    [TXIX_HCPD_CLP_1] = FWF_FORMAT_HCPD_CLP_1,
    [TXIX_HCPD_CLP_2] = FWF_FORMAT_HCPD_CLP_2,
    [TXIX_HCPD_CLP_3] = FWF_FORMAT_HCPD_CLP_3,
    [TXIX_HCPD_SVC_1] = FWF_FORMAT_HCPD_SVC_1,
    [TXIX_HCPD_SVC_2] = FWF_FORMAT_HCPD_SVC_2,
    [TXIX_HCDN_CLP_1] = FWF_FORMAT_HCDN_CLP_1,
    [TXIX_HCDN_CLP_2] = FWF_FORMAT_HCDN_CLP_2,
    [TXIX_HCDN_SVC_1] = FWF_FORMAT_HCDN_SVC_1,
    [TXIX_HCDN_SVC_2] = FWF_FORMAT_HCDN_SVC_2,

};

static const uint8_t fwf_line_format[][FORMAT_SIZE] = {

    [TXIX_HCAD_CLP_1] = { 0, 0,  81, 255,  16, ':',  67, ':' },
    [TXIX_HCAD_CLP_2] = { 0, 0, 122, 255,  72, ')', 121, ')' },
    [TXIX_HCAD_CLP_3] = { 0, 1, 122, 255,  72, ')',  43, ' ' },
    [TXIX_HCPD_CLP_1] = { 0, 0,  81, 255,  16, ':',  67, ':' },
    [TXIX_HCPD_CLP_2] = { 0, 0, 122, 255,  69, '.',  86, '.' },
    [TXIX_HCPD_CLP_3] = { 0, 0,  70, 255,   0, ' ',  69, '.' },
    [TXIX_HCPD_SVC_1] = { 1, 0, 105, 255,  27, ' ',  42, '.' },
    [TXIX_HCPD_SVC_2] = { 0, 1,  85, 255,  55, '.',  81, '.' },
    [TXIX_HCDN_CLP_1] = { 0, 0,  78, 255,  16, ':',  64, ':' },
    [TXIX_HCDN_CLP_2] = { 0, 0,  87, 255,  49, ' ',  69, '.' },
    [TXIX_HCDN_SVC_1] = { 0, 0, 103, 255,  28, '.',  39, ' ' },
    [TXIX_HCDN_SVC_2] = { 1, 1,  81, 255,   0, ' ',  77, '.' },

};

static void fwf_write_line(FWFRow* fwf, PDFLine* line, TXIXLine l) {

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

static void fwf_parse_line(FWFRow* fwf, PDFLine* line, TXIXLine l) {

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

int fwf_parse_txix(FWFRow* fwf, PDFPage* page) {

    PDFLine* line = NULL;

    if (pdf_next_line(page, &line) != PDF_OK) { return 1; }

    TXIXLine l = 0;
    const uint8_t* c = line->cursor + 14;

    if (line->n_bytes < 20) { return 1; }
    else if (memcmp(c, "HCPD", 4) == 0) { l = TXIX_HCPD_CLP_1; }
    else if (memcmp(c, "HCDN", 4) == 0) { l = TXIX_HCDN_CLP_1; }
    else if (memcmp(c, "HCAD", 4) == 0) { l = TXIX_HCAD_CLP_1; }
    else { return 1; }

    for (TXIXLine h = TXIX_HEAD_BPR_1; h <= TXIX_HEAD_BPR_8; h++) {

        if (fwf->header == 0) { fwf_write_line(fwf, line, h); }
        if (pdf_next_line(page, &line) != PDF_OK) { return 1; }

    }

    fwf->header = 1;
    do { fwf_parse_line(fwf, line, l); }
    while (pdf_next_line(page, &line) == PDF_OK);

    return 0;

}
