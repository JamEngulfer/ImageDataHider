//
//  GetBitmapData.h
//  ImageDataHider
//
//  Created by JamEngulfer on 11/11/2015.
//
//

#ifndef __ImageDataHider__GetBitmapData__
#define __ImageDataHider__GetBitmapData__

#include <stdio.h>
#include <fstream>
#include <iterator>
#include <vector>

class BitmapHandler {
    
    
public:
    static std::vector<char> getBitmapData(std::string fileName);
    static std::vector<char> getPixelData(std::vector<char> bytes);
    static std::vector<char> getHeaderData(std::vector<char> bytes);
    static void saveBitmapData(std::string fileName, std::vector<char> headerData, std::vector<char> imageData);
};

#endif /* defined(__ImageDataHider__GetBitmapData__) */
