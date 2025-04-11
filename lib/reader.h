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

#ifndef BARE_BONES_PDF_READER_H
#define BARE_BONES_PDF_READER_H

#include <stdint.h>
#include <stdlib.h>

#define BYTE_SIZE (1 <<  8)
#define PAGE_SIZE (1 << 16)
#define FILE_SIZE (1 << 24) // unused

typedef enum {

    PDF_OK,
    PDF_EOF,
    PDF_ZLIB_ERROR,
    PDF_STREAM_ERROR,
    PDF_INVALID_FILE,
    PDF_UNINITIALIZED,
    PDF_MALLOC_FAILED,
    
} PDFStatus;

typedef struct {

    const uint8_t* pattern;
    const uint8_t length;

    uint8_t shift[BYTE_SIZE];
    uint8_t* cursor;
    uint8_t* limits;

} PDFStream;

typedef struct {

    uint8_t* cursor;
    size_t n_bytes;

} PDFLine;

typedef struct {

    uint8_t* buffer;
    size_t n_bytes;
    size_t total_size;

    PDFLine* line;
    PDFStream stream;

} PDFPage;

typedef struct {

    uint8_t* buffer;
    size_t n_bytes;
    size_t total_size;

    PDFPage* page;

    PDFStream stream;
    PDFStatus status;

} PDFFile;

PDFStatus pdf_read_file(PDFFile* pdf, const char* file);
PDFStatus pdf_next_page(PDFFile* pdf, PDFPage** page);
PDFStatus pdf_next_line(PDFPage* pdf, PDFLine** line);
void pdf_file_free(PDFFile* pdf);

#define PDF_STREAM(X)        \
{                            \
    .pattern = (uint8_t*) X, \
    .length = sizeof(X) - 1, \
    .cursor = NULL,          \
    .limits = NULL           \
}

#define PDF_LINE_INIT() &(PDFLine)   \
{                                    \
    .cursor = NULL,                  \
    .n_bytes = 0                     \
}

#define PDF_PAGE_INIT() &(PDFPage)   \
{                                    \
    .buffer = NULL,                  \
    .n_bytes = 0,                    \
    .total_size = PAGE_SIZE,         \
    .line = PDF_LINE_INIT(),         \
    .stream = PDF_STREAM("\n(")      \
}

#define PDF_FILE_INIT() &(PDFFile)   \
{                                    \
    .buffer = NULL,                  \
    .n_bytes = 0,                    \
    .total_size = 0,                 \
    .page = PDF_PAGE_INIT(),         \
    .status = PDF_UNINITIALIZED,     \
    .stream = PDF_STREAM("stream\n") \
}

#define PDF_FILE_FREE(X) pdf_file_free(X);

#endif // BARE_BONES_PDF_READER_H
