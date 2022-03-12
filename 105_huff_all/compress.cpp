#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <map>
#include <queue>
#include <assert.h>
#include <functional>
#include <stdlib.h>

#include "readFreq.h"
#include "node.h"



void writeHeader(BitFileWriter * bfw, const std::map<unsigned,BitString> &theMap) {
    for (int i =0 ; i < 257; i++) {
        std::map<unsigned,BitString>::const_iterator it = theMap.find(i);
        if (it != theMap.end()) {
            bfw->writeByte(it->second.size());
            bfw->writeBitString(it->second);
        }
        else {
            bfw->writeByte(0);
        }
    }
}

void writeCompressedOutput(const char* inFile,
                           const char *outFile,
                           const std::map<unsigned,BitString> &theMap ){
    BitFileWriter bfw(outFile);
    writeHeader(&bfw,theMap);

    //WRITE YOUR CODE HERE!
    //open the input file for reading
    std::ifstream ifs;
    ifs.open(inFile, std::ifstream::in);
    if(ifs.fail()){
        std::cerr<<"Fail to open the file!"<<std::endl;
        exit(EXIT_FAILURE);
    }

    //You need to read the input file, lookup the characters in the map,
    //and write the proper bit string with the BitFileWriter
    int c;
    while((c=ifs.get()) != EOF){
        if(theMap.find(c) == theMap.end()){
            std::cerr << "Can't find the char!" << std::endl;
        }
        bfw.writeBitString(theMap.find(c)->second);
    }

    //dont forget to lookup 256 for the EOF marker, and write it out.
    bfw.writeBitString(theMap.find(256)->second);
    //BitFileWriter will close the output file in its destructor
    //but you probably need to close your input file.
    ifs.close();
}

int main(int argc, char ** argv) {
    if (argc != 3) {
        fprintf(stderr,"Usage: compress input output\n");
        return EXIT_FAILURE;
    }
    //WRITE YOUR CODE HERE
    //Implement main
    //hint 1: most of the work is already done.
    //hint 2: you can look at the main from the previous tester for 90% of this
    uint64_t * counts = readFrequencies(argv[1]);
    assert(counts != NULL);
    Node * tree = buildTree(counts);
    std::map<unsigned, BitString> theMap;
    BitString empty;
    tree->buildMap(empty, theMap);
    char * input = argv[1];
    char * output = argv[2];
    writeCompressedOutput(input, output, theMap);

    delete[] counts;
    delete tree;
    return EXIT_SUCCESS;
}
