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

#ifndef BARE_BONES_PDF_PARSER_H
#define BARE_BONES_PDF_PARSER_H

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

#endif // BARE_BONES_PDF_PARSER_H
