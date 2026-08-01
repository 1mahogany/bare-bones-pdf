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

#define _XOPEN_SOURCE 700 // POSIX.1-2008
#define USE_FD 8 // nftw file descriptors

#include <ftw.h>
#include <getopt.h>

#include "parser.h"
#include "mcd_ar.h"
#include "mcd_ms.h"
#include "mcd_sc.h"

static PDFParser* p = NULL;

static int pdf_parse_file(
    const char* filename,
	const struct stat* status,
    int flag,
	struct FTW* info
) {
    if (flag == FTW_F) {

        // silence compiler errors
        (void)status;
        (void)info;

    } else { return EXIT_SUCCESS; }

    PDFFile* pdf = PDF_FILE_INIT();

    if (pdf_read_file(pdf, filename) != PDF_OK) {

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

    int opt = 0;

    while ((opt = getopt(argc, argv, "p:")) != -1) {

        switch (opt) {

        case 'p':

            if      (strlen(optarg) < 5) { }
            else if (memcmp(optarg, "armcd", 5) == 0) { p = parse_mcd_ar; }
            else if (memcmp(optarg, "msmcd", 5) == 0) { p = parse_mcd_ms; }
            else if (memcmp(optarg, "scmcd", 5) == 0) { p = parse_mcd_sc; }
            break;

        default:
            printf("usage: %s -p parser path\n", argv[0]);
            return EXIT_FAILURE;

        }

    }

    if (p == NULL) {
        
        printf("missing PDF parser selection\n");
        return EXIT_FAILURE;
        
    } else if (optind >= argc) {

        printf("missing input path\n");
        return EXIT_FAILURE;

    } else { 
        
        p(NULL, stdout);
        return nftw(argv[optind], pdf_parse_file, USE_FD, 0);
    
    }

}
