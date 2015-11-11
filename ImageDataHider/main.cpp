//
//  main.cpp
//  ImageDataHider
//
//  Created by JamEngulfer on 11/11/2015.
//
//

#include <iostream>
#include <vector>
#include "GetBitmapData.h"
#include "Hider.h"

int main(int argc, const char * argv[]) {
    
    std::string readWrite(argv[1]);
    
    if (readWrite == "write") {
        
        std::string inputImage(argv[2]);
        std::string inputData(argv[3]);
        std::string outputFileName(argv[4]);
        
        std::vector<char> fileData = BitmapHandler::getBitmapData(inputImage);
        
        std::vector<char> headerData = BitmapHandler::getHeaderData(fileData);
        std::vector<char> imageData = BitmapHandler::getPixelData(fileData);
        
        std::vector<char> payloadData = DataHider::getDataToHide(inputData);
        
        /*for (int i = 0; i < inputData.size(); i++) {
         std::cout << inputData[i];
         }*/
        
        std::vector<char> dopedPixels = DataHider::hideDataInBytes(imageData, payloadData);
        
        BitmapHandler::saveBitmapData(outputFileName, headerData, dopedPixels);
        
    } else {
        
        std::string inputImage(argv[2]);
        std::string outputFileName(argv[3]);
        
        std::vector<char> fileData = BitmapHandler::getBitmapData(inputImage);
        
        std::vector<char> headerData = BitmapHandler::getHeaderData(fileData);
        std::vector<char> imageData = BitmapHandler::getPixelData(fileData);
        
        std::vector<char> extractedData = DataHider::getHiddenDataFromBytes(imageData);
        
        std::ofstream outputFile(outputFileName, std::ios::out | std::ios::binary);
        
        if ( ! outputFile.is_open() ){
            std::cout << "Could not open \"" << outputFileName << "\"";
        }
        
        outputFile.write(extractedData.data(), extractedData.size());
        
        if ( outputFile.bad() ){
            std::cout <<  "Could not save to \"" << outputFileName << "\"";
        }
        
        outputFile.close();
        
    }
    
    std::cout << "Done!";
    
    return 0;
}