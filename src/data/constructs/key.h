#ifndef KEY
#define KEY

/*
 * Mutation.h
 *
 *  Created on: Aug 25, 2012
 *      Author: marc
 */

#include "../streaming/stream_ifc.h"
#include "../streaming/hadoop_stream.h"


#include <stdint.h>

#include <stdio.h>
#include <string.h>



namespace cclient
{
namespace data
{

using namespace cclient::data::streams;

/**
 * Code is partially based on some code I wrote in 2009 for a personal project
 */
class Key : public StreamInterface
{

public:

    Key() : deleted(false), timestamp( (uint64_t)-1 ),colVisSize(0), rowMaxSize(0), columnFamilySize(0),colQualSize(0), rowLength(0), columnFamilyLength(0),colQualLen(0)
    {

        row = new char[ 0 ];


        colFamily = new char[ 0 ];


        colQualifier = new char[ 0 ];

        keyVisibility = new char[ 0 ];

    }

    virtual ~Key()
    {
        delete [] row;
        delete [] colFamily;
        delete [] colQualifier;
        delete [] keyVisibility;
    }


    void setRow(const char *r, uint32_t size)
    {
        if (size > rowMaxSize)
        {
            delete [] row;
            row = new char[ size ];
            rowMaxSize = size;
        }

        memcpy(row,r,size);
        rowLength = size;

    }

    std::pair<char*,size_t> getRow()
    {
        return std::make_pair(row,rowLength);
    }



    void setColFamily(const char *r, uint32_t size)
    {

        if (size > columnFamilySize)
        {
            delete [] colFamily;
            colFamily = new char[ size ];
            columnFamilySize = size;
        }

        memcpy(colFamily,r,size);
        columnFamilyLength = size;

    }

    std::pair<char*,size_t> getColFamily()
    {
        return std::make_pair(colFamily,columnFamilyLength);
    }

    void setColQualifier(const char *r, uint32_t size, uint32_t offset = 0)
    {
        if (offset+size > colQualSize)
        {
            char *nr = new char[size+offset];
            memcpy(nr,colQualifier,colQualSize);
            delete [] colQualifier;
            colQualifier = nr;
            colQualSize = size+offset;
        }

        memcpy(colQualifier+offset,r,size);
        colQualLen = size+offset;

    }

    std::pair<char*,size_t> getColQualifier()
    {
        return std::make_pair(colQualifier,colQualLen);
    }

    void setColVisibility(const char *r, uint32_t size)
    {
        if (size > colVisSize)
        {
            delete [] keyVisibility;
            keyVisibility = new char[ size ];
            colVisSize = size;
        }


        memcpy(keyVisibility,r,size);

    }

    std::pair<char*,size_t> getColVisibility()
    {
        return std::make_pair(keyVisibility,colVisSize);
    }

    uint64_t getTimeStamp()
    {
        return timestamp;
    }

    void setTimeStamp(const uint64_t ts)
    {
        timestamp = ts;
    }

    bool isDeleted()
    {
        return deleted;
    }

    StreamInterface *getStream()
    {
        return this;
    }


    bool operator <(const Key &rhs) const
    {
        int compare = compareBytes(row,0,rowMaxSize,rhs.row,0,rhs.rowMaxSize);

        if (compare < 0)
            return true;
        else if (compare > 0)
            return false;

        compare = compareBytes(colFamily,0,columnFamilySize,rhs.colFamily,0,rhs.columnFamilySize);


        if (compare < 0)
            return true;
        else if (compare > 0)
            return false;

        compare = compareBytes(colQualifier,0,colQualSize,rhs.colQualifier,0,rhs.colQualSize);

        if (compare < 0)
            return true;


        return false;
    }
    bool operator <(const Key *rhs) const
    {
        return *this < *rhs;
    }


    bool operator == (const Key & rhs) const
    {
        int compare = compareBytes(row,0,rowMaxSize,rhs.row,0,rhs.rowMaxSize);

        if (compare != 0)
            return false;

        compare = compareBytes(colFamily,0,columnFamilySize,rhs.colFamily,0,rhs.columnFamilySize);

        if (compare != 0)
            return false;


        compare = compareBytes(colQualifier,0,colQualSize,rhs.colQualifier,0,rhs.colQualSize);

        if (compare != 0)
            return false;

        return (timestamp < rhs.timestamp);

    }
    bool operator != (const Key &rhs) const {
        return !(*this == rhs);
    }

    bool operator == (const Key *rhs) const
    {
        return *this == *rhs;
    }
    bool operator != (const Key *rhs) const {
        return !(*this == *rhs);
    }



    uint64_t write(OutputStream *outStream)
    {

        uint32_t offset = rowMaxSize;

        HadoopStream::writeHadoopLong(outStream,offset);
        //outStream->writeHadoopLong( offset ); // cf offset

        offset += columnFamilySize;
        HadoopStream::writeHadoopLong(outStream,offset);
        //outStream->writeHadoopLong( offset ); // cq offset

        offset += colQualSize;
        HadoopStream::writeHadoopLong(outStream,offset);
        //outStream->writeHadoopLong( offset ); // colvis offset

        offset +=colVisSize;
        HadoopStream::writeHadoopLong(outStream,offset);
        //outStream->writeHadoopLong( offset ); // total

        outStream->writeBytes(row,rowMaxSize);
        outStream->writeBytes(colFamily,columnFamilySize);
        outStream->writeBytes(colQualifier,colQualSize);
        outStream->writeBytes(keyVisibility,colVisSize);
        HadoopStream::writeHadoopLong(outStream,timestamp);
        //outStream->writeHadoopLong( timestamp);

        return outStream->writeBoolean( deleted );

    }



private:

	/**
	 * Row part of key
	 */
	char *row;
    uint32_t rowMaxSize;
    uint32_t rowLength;

    /**
     * Column family
     */
    uint32_t columnFamilyLength;
    char *colFamily;
    uint32_t columnFamilySize;


    /**
     * Column qualifier.
     */
    char *colQualifier;
    uint32_t colQualSize;
    uint32_t colQualLen;
    char *keyVisibility;
    uint32_t colVisSize;
    uint64_t timestamp;
    bool deleted;

    /**
     * copied from writable comparable utils
     */
    static int compareBytes(const char *b1, int s1, int l1,
                            const char *b2, int s2, int l2) {
        int end1 = s1 + l1;
        int end2 = s2 + l2;
        for (int i = s1, j = s2; i < end1 && j < end2; i++, j++) {
            int a = (b1[i] & 0xff);
            int b = (b2[j] & 0xff);
            if (a != b) {
                return a - b;
            }
        }
        return l1 - l2;
    }
};
}
}

#endif
