//
//  Hider.cpp
//  ImageDataHider
//
//  Created by JamEngulfer on 11/11/2015.
//
//

#include "Hider.h"
#include <algorithm>
#include <fstream>

std::vector<char> DataHider::getDataToHide(std::string filename) {
    
    std::ifstream input(filename, std::ios::binary);
    
    std::vector<char> buffer((std::istreambuf_iterator<char>(input)),(std::istreambuf_iterator<char>()));
    
    return buffer;
    
}

std::vector<char> DataHider::hideDataInBytes(std::vector<char> pixels, std::vector<char> payload) {
    
    /*char i = 74;
     
     Set To 1:
     
     i |= 1 << 0;
     
     Set To 0:
     
     i &= ~(1 << 0);
     
     Check Bit:
     
     bit = (byte >> x) & 1;
     
     */
    
    int currentBytePos = 0;
    int currentBit = 0;
    
    bool keepWriting = true;
    
    char currentByte = payload[currentBytePos];
    
    for(std::vector<int>::size_type i = 0; i != pixels.size(); i++) {
        
        char pixelChar = pixels[i];
        
        if (keepWriting) {
            
            char activeBit = (currentByte >> currentBit) & 1;
            
            if (activeBit == 0) {
                pixelChar &= ~(1 << 0);
            } else {
                pixelChar |= 1 << 0;
            }
            
            
            currentBit++;
            
            if (currentBit > 7) {
                currentBit = 0;
                currentBytePos++;
                
                if (currentBytePos < payload.size()) {
                    currentByte = payload[currentBytePos];
                } else {
                    keepWriting = false;
                }
                
            }
            
        } else {
            pixelChar &= ~(1 << 0);
        }
        
        pixels[i] = pixelChar;
        
    }
    
    return pixels;
    
}

std::vector<char> DataHider::getHiddenDataFromBytes(std::vector<char> pixels) {
    
    std::vector<char> extractedData;
    
    char constructedChar;
    int bitPos = 0;
    
    for(std::vector<int>::size_type i = 0; i != pixels.size(); i++) {
        
        char currentBit = (pixels[i] >> 0) & 1;
        
        if (currentBit == 0) {
            constructedChar &= ~(1 << bitPos);
        } else {
            constructedChar |= 1 << bitPos;
        }
        
        bitPos++;
        
        if (bitPos > 7) {
            bitPos = 0;
            extractedData.push_back(constructedChar);
        }
        
    }
    
    long delPos;
    
    for (std::vector<char>::reverse_iterator it = extractedData.rbegin(); it != extractedData.rend(); ++it) {
        
        if (*it != 0) {
            delPos = extractedData.size() - (it - extractedData.rbegin());
            break;
        }
        
    }
    
    extractedData.resize(delPos);
    
    return extractedData;
    
}