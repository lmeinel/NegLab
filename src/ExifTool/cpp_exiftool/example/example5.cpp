//------------------------------------------------------------------------------
// File:        example5.cpp
//
// Description: Example to test the exiftool command queue
//
// Syntax:      example5 FILE
//
// License:     Copyright 2013-2016, Phil Harvey (phil at owl.phy.queensu.ca)
//
//              This is software, in whole or part, is free for use in
//              non-commercial applications, provided that this copyright notice
//              is retained.  A licensing fee may be required for use in a
//              commercial application.
//
// Created:     2013-11-30 - Phil Harvey
//------------------------------------------------------------------------------

#include <stdio.h>
#include <unistd.h>
#include "ExifTool.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        puts("Example5: Test of queued commands.\n");
        puts("Please specify input file name\n");
        return 1;
    }
    // create our ExifTool object
    ExifTool et;
    // send 1000 commands as quickly as possible
    const int kNumCmds = 1000;
    for (int sent=0, recv=0, count=0; recv<kNumCmds; ) {
        int lastSent = sent;
        if (sent < kNumCmds) {
            int cmdNum = et.ExtractInfo(argv[1], "-filename\n-filemodifydate\n-exif:all");
            if (cmdNum < 0) {
                puts("\nError extracting information\n");
                break;
            }
            ++sent;
        }
        TagInfo *info = et.GetInfo(0, NOW);
        int cmdNum = et.LastComplete();
        if (cmdNum < 0) {
            printf("\nError %d receiving command\n", cmdNum);
            break;
        }
        if (cmdNum > 0) {
            // count the number of tags we extracted
            for (TagInfo *i=info; i; i=i->next) ++count;
            delete info;    // (may be null)
            ++recv;
        } else if (sent == lastSent) {
            usleep(100);    // give exiftool time to respond
            continue;
        }
        printf("\rCommands sent: %4d,  Received: %4d,  Tags extracted: %d",sent,recv,count);
        fflush(stdout);
    }
    puts("\nDone.\n");
    return 0;
}

// end
