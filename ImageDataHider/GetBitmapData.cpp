//
//  GetBitmapData.cpp
//  ImageDataHider
//
//  Created by JamEngulfer on 11/11/2015.
//
//

#include "GetBitmapData.h"

#include <fstream>
#include <iterator>
#include <vector>
#include <iostream>

std::vector<char> BitmapHandler::getBitmapData(std::string filename) {
    
    std::ifstream input(filename, std::ios::binary);
    
    std::vector<char> buffer((std::istreambuf_iterator<char>(input)),(std::istreambuf_iterator<char>()));
    
    return buffer;
}

std::vector<char> BitmapHandler::getPixelData(std::vector<char> bytes) {
    
    char * offset[4];
    
    for (int i = 0; i < 4; i++) {
        offset[i] = &bytes[i+10];
    }
    
    int x; std::memcpy(&x, offset, 4);
    
    x = (bytes[10]<<0) | (bytes[11]<<8) | (bytes[12]<<16) | (bytes[13]<<24);
    
    bytes.erase(bytes.begin(), bytes.begin() + x);
    
    return bytes;
    
}

std::vector<char> BitmapHandler::getHeaderData(std::vector<char> bytes) {
    
    char * offset[4];
    
    for (int i = 0; i < 4; i++) {
        offset[i] = &bytes[i+10];
    }
    
    uint32_t x; std::memcpy(&x, offset, 4);
    
    x = (bytes[10]<<0) | (bytes[11]<<8) | (bytes[12]<<16) | (bytes[13]<<24);
    
    bytes.resize(x);
    
    return bytes;
    
}

void BitmapHandler::saveBitmapData(std::string filename, std::vector<char> headerVector, std::vector<char> imageVector) {
    
    char * headerData = headerVector.data();
    char * imageData = imageVector.data();
    
    std::ofstream outputFile(filename, std::ios::out | std::ios::binary);
    
    if ( ! outputFile.is_open() ){
        std::cout << "Could not open \"" << filename<< "\"";
    }
    
    if( ! outputFile ) { std::cout << "BREAK"; }
    
    //outputFile.open(fileName, std::ios::out | std::ios::binary);
    outputFile.write(headerData, headerVector.size());
    outputFile.write(imageData, imageVector.size());
    
    if ( outputFile.bad() ){
        std::cout <<  "Could not save to \""<<filename<<"\"";
    }
    
    outputFile.close();
    
}