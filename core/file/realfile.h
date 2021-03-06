//This file is part of the HexaMonkey project, a multimedia analyser
//Copyright (C) 2013  Sevan Drapeau-Martin, Nicolas Fleury

//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#ifndef REALFILE_H
#define REALFILE_H

#include "core/file/file.h"

/** @brief High-level input stream operations on files with bit precision

The class is implemented as an adaptor for a std::ifstream instance that
reimplements common operation with bit precision instead of byte precision*/
class RealFile : public File
{
public:
    RealFile();

    /** @brief Sets the path to the file*/
    void setPath(const std::string& path);

    /** @brief Returns the path to the file*/
    const std::string& path() const;

    /** @brief Opens stream with the given path*/
    virtual void open() override;

    /** @brief Closes stream*/
    virtual void close() override;

    /** @brief Clears the file error flags*/
    virtual void clear() override;


    /** @brief Extracts bits from stream

    Puts the result in a byte array already allocated
    the result is right aligned and zero padded*/
    virtual void read(char* s, int64_t size) override;

    /** @brief Offsets the position

     * \param off Offset to apply in bits.
     * \param dir Where to start from to apply the offset.
     * begin (std::ios_base::beg), current (std::ios_base::cur) or
     * end (std::ios_base::end).
     */
    virtual void seekg(int64_t off, std::ios_base::seekdir dir) override;

    /** @brief Returns the current stream position */
    virtual int64_t tellg() override;

    /** @brief Returns the size of the file*/
    virtual int64_t size() override;

    /** @brief Checks if data can be recovered from the stream*/
    virtual bool good() override;


private:
    RealFile& operator=(const RealFile&) = delete;
    RealFile(const RealFile&) = delete;

    std::string _path;
    std::ifstream _file;
};

#endif // REALFILE_H
