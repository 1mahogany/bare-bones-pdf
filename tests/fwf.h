
#ifndef BARE_BONES_PDF_FWF_H
#define BARE_BONES_PDF_FWF_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "reader.h"

#define FWF_FIN 0 // last available line format - exit detection loop
#define FWF_OUT 1 // line is ready for fwrite output
#define FWF_MIN 2 // minimum number of bytes required
#define FWF_MAX 3 // maximum number of bytes allowed
#define FWF_I01 4 // 1st index to read
#define FWF_C01 5 // 1st byte to match
#define FWF_I02 6 // 2nd index to read
#define FWF_C02 7 // 2nd byte to match

typedef int (PDFParser)(PDFFile*, FILE*);

#endif // BARE_BONES_PDF_FWF_H
