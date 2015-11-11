//
//  Hider.h
//  ImageDataHider
//
//  Created by JamEngulfer on 11/11/2015.
//
//

#ifndef __ImageDataHider__Hider__
#define __ImageDataHider__Hider__

#include <stdio.h>
#include <vector>

class DataHider {
    
    
public:
    static std::vector<char> getDataToHide(std::string filename);
    static std::vector<char> hideDataInBytes(std::vector<char> pixels, std::vector<char> payload);
    static std::vector<char> getHiddenDataFromBytes(std::vector<char> pixels);
};

#endif /* defined(__ImageDataHider__Hider__) */
