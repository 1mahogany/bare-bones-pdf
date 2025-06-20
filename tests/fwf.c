
#include <getopt.h>

#include "fwf.h"
#include "txix.h"
#include "mmes.h"
#include "ddsn.h"

static int pdf_parse_file(char* file, PDFParser* p) {

    PDFFile* pdf = PDF_FILE_INIT();

    if (pdf_read_file(pdf, file) != PDF_OK) {

        printf("read pdf failed\n");
        PDF_FILE_FREE(pdf);
        return EXIT_FAILURE;

    } else {

        p(pdf, stdout);
        PDF_FILE_FREE(pdf);
        return EXIT_SUCCESS;

    }

}

int main(int argc, char** argv) {

    PDFParser* p = NULL;
    int opt = 0;

    while ((opt = getopt(argc, argv, "p:")) != -1) {

        switch (opt) {

        case 'p':

            if      (strlen(optarg) < 4) { }
            else if (memcmp(optarg, "txix", 4) == 0) { p = txix_parse_file; }
            else if (memcmp(optarg, "mmes", 4) == 0) { p = mmes_parse_file; }
            else if (memcmp(optarg, "ddsn", 4) == 0) { p = ddsn_parse_file; }
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

    } else { return pdf_parse_file(argv[optind], p); }

}
