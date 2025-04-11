
#ifndef BARE_BONES_PDF_TXIX_H
#define BARE_BONES_PDF_TXIX_H

#ifndef BARE_BONES_PDF_FWF_H

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

#endif // BARE_BONES_PDF_FWF_H

#include "reader.h"
#include "fwf.h"

int fwf_parse_txix(FWFRow* fwf, PDFPage* page);

#endif // BARE_BONES_PDF_TXIX_H
