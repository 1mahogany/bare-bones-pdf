
#ifndef BARE_BONES_PDF_MMES_H
#define BARE_BONES_PDF_MMES_H

#ifndef BARE_BONES_PDF_FWF_H

typedef enum {
    
    MMES_HEAD_BPR_1,
    MMES_HEAD_BPR_2,
    MMES_HEAD_BPR_3,
    MMES_HEAD_BPR_4,
    MMES_HEAD_BPR_5,
    MMES_HEAD_BPR_6,
    MMES_HEAD_BPR_7,
    MMES_HEAD_BPR_8,
    MMES_HEAD_BPR_9,
    MMES_HCAD_CAS_2,
    MMES_HCPD_CLP_1,
    MMES_HCPD_CLP_2,
    MMES_HCPD_SVC_1,
    MMES_HCPD_SVC_2,
    MMES_HCDN_CLP_1,
    MMES_HCDN_CLP_2,
    MMES_HCDN_SVC_1,
    MMES_HCDN_SVC_2,
    
} MMESLine;

#endif // BARE_BONES_PDF_FWF_H

#include "reader.h"
#include "fwf.h"

int fwf_parse_mmes(FWFRow* fwf, PDFPage* page);

#endif // BARE_BONES_PDF_MMES_H
