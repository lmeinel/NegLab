//------------------------------------------------------------------------------
// File:        example1.cpp
//
// Description: Simple example to read metadata from a file
//
// Syntax:      example1 FILE
//
// License:     Copyright 2013-2016, Phil Harvey (phil at owl.phy.queensu.ca)
//
//              This is software, in whole or part, is free for use in
//              non-commercial applications, provided that this copyright notice
//              is retained.  A licensing fee may be required for use in a
//              commercial application.
//
// Created:     2013-11-28 - Phil Harvey
//------------------------------------------------------------------------------

#include <iostream>
#include "ExifTool.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2) {
        cout << "Example1: Read metadata from an image." << endl;
        cout << "Please specify input file name" << endl;
        return 1;
    }
    // create our ExifTool object
    ExifTool *et = new ExifTool();
    // read metadata from the image
    TagInfo *info = et->ImageInfo(argv[1],NULL,5);
    if (info) {
        // print returned information
        for (TagInfo *i=info; i; i=i->next) {
            cout << i->name << " = " << i->value << endl;
        }
        // we are responsible for deleting the information when done
        delete info;
    } else if (et->LastComplete() <= 0) {
        cerr << "Error executing exiftool!" << endl;
    }
    // print exiftool stderr messages
    char *err = et->GetError();
    if (err) cerr << err;
    delete et;      // delete our ExifTool object
    return 0;
}

// end
