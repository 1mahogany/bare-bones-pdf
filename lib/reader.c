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

#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <zlib.h>

#include "reader.h"

static inline void pdf_init_stream(PDFStream* s) {

    memset(s->shift, s->length, BYTE_SIZE);

    for (uint8_t i = 0; i < s->length; i++) {

        const uint8_t p = s->pattern[i];
        s->shift[p] = s->length - i - 1;

    }

}

static uint8_t* pdf_next_stream(PDFStream* s) {

    if (s->cursor == NULL) { return NULL; }
    const uint8_t p = s->length - 1;

    while (s->cursor < s->limits - p) {

        const uint8_t c = s->cursor[p];

        if (c == s->pattern[p]) {

            // align start of current buffer position with start of pattern
            // the last byte has already been compared by the outer if block
            // so only need to compare the first p = length - 1 bytes
            int cmp = memcmp(s->cursor, s->pattern, p);
            s->cursor += s->length;
            if (cmp != 0) { continue; }
            else { return  s->cursor; }

        } else { s->cursor += s->shift[c]; }

    }

    // No more match found
    return s->cursor = NULL;
    
}

static uint8_t* pdf_trim_stream(PDFStream* s) {

    if (s->cursor == NULL) { return NULL; }

    size_t j = 0;
    size_t esc = 0;

    while (s->cursor + j < s->limits) {

        uint8_t c = s->cursor[j];

        if (esc > 0) { esc = 0; }
        else if (c == ')' ) {    return s->cursor; }
        else if (c == '\\') { esc = ++j; continue; }

        s->cursor[0] = c;
        s->cursor++;

    }

    // cannot locate EOL
    return s->cursor = NULL;

}

static int pdf_read_page(PDFPage* page) {

    PDFStream* s = &page->stream;
    size_t n_bytes = s->limits - s->cursor - 10;

    /* allocate inflate state */
    z_stream* stream = &(z_stream)
    {
        .zalloc = Z_NULL,
        .zfree = Z_NULL,
        .opaque = Z_NULL,
        .avail_in = n_bytes,
        .avail_out = page->total_size,
        .next_in = s->cursor,
        .next_out = page->buffer
    };

    int inf = inflateInit(stream);
    if (inf != Z_OK) { return inf; }

    inf = inflate(stream, Z_FINISH);
    (void)inflateEnd(stream);

    page->n_bytes = stream->total_out;
    s->cursor = page->buffer;
    s->limits = page->buffer + page->n_bytes;

    return inf == Z_STREAM_END ? Z_OK : inf;

}

static PDFStatus pdf_init_file(PDFFile* pdf) {

    if (pdf->status == PDF_UNINITIALIZED) {

        pdf_init_stream(&pdf->stream);
        pdf_init_stream(&pdf->page->stream);

    } else { return pdf->status; }

    uint8_t* buffer = realloc(pdf->buffer, pdf->total_size);

    if (buffer) { pdf->buffer = buffer; } 
    else { return pdf->status = PDF_MALLOC_FAILED; }

    PDFPage* page = pdf->page;
    buffer = realloc(page->buffer, page->total_size);

    if (buffer) { page->buffer = buffer; }
    else { return pdf->status = PDF_MALLOC_FAILED; }

    return pdf->status = PDF_OK;

}

PDFStatus pdf_read_file(PDFFile* pdf, const char* file) {

    struct stat s;
    if (stat(file, &s) == 0) { pdf->total_size = s.st_size; }
    else { return pdf->status = PDF_INVALID_FILE; }

    if (pdf_init_file(pdf) != PDF_OK) { return pdf->status; }

    FILE* f = fopen(file, "rb");

    if (f) {

        PDFStream* s = &pdf->stream;
        pdf->n_bytes = fread(pdf->buffer, 1, pdf->total_size, f);
        s->cursor = pdf->buffer;
        s->limits = pdf->buffer + pdf->n_bytes;
        
        fclose(f);

    } else { pdf->status = PDF_INVALID_FILE; }

    return pdf->status;

}

PDFStatus pdf_next_page(PDFFile* pdf, PDFPage** page) {

    if (pdf->status != PDF_OK) { return pdf->status; }
    PDFStream* s = &pdf->stream;
    PDFStream* p = &pdf->page->stream;

    if (!pdf_next_stream(s)) { return PDF_EOF; }
    else { p->cursor = s->cursor; }

    if (!pdf_next_stream(s)) { return PDF_EOF; }
    else { p->limits = s->cursor; }

    int inf = pdf_read_page(pdf->page);
    if (inf != Z_OK) { return PDF_ZLIB_ERROR; }
    else { *page = pdf->page;  return PDF_OK; }

}

PDFStatus pdf_next_line(PDFPage* pdf, PDFLine** line) {

    PDFStream* s = &pdf->stream;
    PDFLine* l = pdf->line;
    
    if (pdf_next_stream(s)) { l->cursor = s->cursor; }
    else { return PDF_EOF; }

    if (pdf_trim_stream(s)) { *line = l; }
    else { return PDF_EOF; }

    l->n_bytes = s->cursor - l->cursor;
    return PDF_OK;

}

void pdf_file_free(PDFFile* pdf) {
    
    free(pdf->page->buffer);
    free(pdf->buffer);

}
