##
# Bare Bones PDF: A bare-bones C library for PDF files
# Copyright (C) 2025 Ian Wang
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
##

FROM debian:trixie-slim

RUN <<EOF
    groupadd --gid 1000 dev
    useradd --gid 1000 --uid 1000 -m -s /usr/bin/bash dev
    apt update
    apt upgrade -y
    apt install gcc gdb git make zlib1g-dev -y
    apt autoremove -y
    apt clean
EOF

USER dev
