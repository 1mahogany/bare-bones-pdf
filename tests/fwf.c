
#include <getopt.h>
#include <string.h>

#include "fwf.h"
#include "txix.h"
#include "mmes.h"

typedef int (FWFParser)(FWFRow*, PDFPage*);

static int fwf_parse_file(char* file, FWFParser* p) {

    PDFPage* page = NULL;
    PDFFile* pdf = PDF_FILE_INIT();
    FWFRow* fwf = FWF_ROW_AUTO(stdout);

    if (pdf_read_file(pdf, file) != PDF_OK) {

        printf("read pdf failed\n");
        PDF_FILE_FREE(pdf);
        return EXIT_FAILURE;

    } else {

        while (pdf_next_page(pdf, &page) == PDF_OK) { p(fwf, page); }
        PDF_FILE_FREE(pdf);
        return EXIT_SUCCESS;

    }

}

int main(int argc, char** argv) {

    FWFParser* p = NULL;
    int opt = 0;

    while ((opt = getopt(argc, argv, "p:")) != -1) {

        switch (opt) {

        case 'p':

            if      (strlen(optarg) < 4) { }
            else if (memcmp(optarg, "txix", 4) == 0) { p = fwf_parse_txix; }
            else if (memcmp(optarg, "mmes", 4) == 0) { p = fwf_parse_mmes; }
            break;

        default:
            printf("usage: %s -p parser file\n", argv[0]);
            return EXIT_FAILURE;

        }

    }

    if (p == NULL) {
        
        printf("missing PDF parser selection\n");
        return EXIT_FAILURE;
        
    } else if (optind >= argc) {

        printf("missing input file\n");
        return EXIT_FAILURE;

    } else { return fwf_parse_file(argv[optind], p); }

}
