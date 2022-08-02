#pragma once
#include <vector>
#include <string>
using namespace std;

struct Pixel
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

struct Header
{
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
    long imageSize;
    Pixel* image = new Pixel[width * height];
};

void outputData(string fileID, Header& headerObject);
void loadData(string fileID, Header& headerObject);
void multBlend(Header& headerObject, Header& headerObject2);
void subBlend(Header& bottomLayer, Header& topLayer);
void screen(Header& bottomLayer, Header& topLayer);
void add(Header& headerObject, int value, string color);
void scale(Header& headerObject, int value, string color);
void colorChannel(Header& headerObject, string color);
void combineColorChannels(Header& headerObjectR, Header& headerObjectG, Header& headerObjectB);
void flipOutput(string fileID, Header& headerObject);
void combine(Header& topLeft, Header& topRight, Header& bottomLeft, Header& bottomRight);
bool compare(Header& example, Header& copy);
void overlay(Header& bottomLayer, Header& topLayer);