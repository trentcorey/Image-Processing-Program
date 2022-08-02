#include "ImageProcessing.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstddef>
using namespace std;


void loadData(string fileID, Header &headerObject)
{
	ifstream file(fileID, ios_base::binary);

	if (file)
	{
		file.read(&headerObject.idLength, sizeof(headerObject.idLength));
		file.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
		file.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
		file.read((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
		file.read((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
		file.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
		file.read((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
		file.read((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
		file.read((char*)&headerObject.width, sizeof(headerObject.width));
		file.read((char*)&headerObject.height, sizeof(headerObject.height));
		file.read(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
		file.read(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

		long imageSize = headerObject.width * headerObject.height;
		Pixel tempPixel;

		for (long i = 0; i < imageSize; i++)
		{
			file.read((char*)&tempPixel.red, sizeof(tempPixel.red));
			file.read((char*)&tempPixel.green, sizeof(tempPixel.green));
			file.read((char*)&tempPixel.blue, sizeof(tempPixel.blue));
			headerObject.image[i] = (tempPixel);
		}
	}

	else
	{
		cout << "\n" << fileID << " not opened!\n";
	}
}

void outputData(string fileID, Header &headerObject)
{
	ofstream file(fileID, ios_base::binary);

	if (file)
	{
		file.write(&headerObject.idLength, sizeof(headerObject.idLength));
		file.write(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
		file.write(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
		file.write((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
		file.write((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
		file.write(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
		file.write((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
		file.write((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
		file.write((char*)&headerObject.width, sizeof(headerObject.width));
		file.write((char*)&headerObject.height, sizeof(headerObject.height));
		file.write(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
		file.write(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

		for (long i = 0; i < headerObject.height * headerObject.width; i++)
		{
			file.write((char*)&headerObject.image[i].red, sizeof(headerObject.image[i].red));
			file.write((char*)&headerObject.image[i].green, sizeof(headerObject.image[i].green));
			file.write((char*)&headerObject.image[i].blue, sizeof(headerObject.image[i].blue));
		}	
	}
}

void multBlend(Header& headerObject, Header& headerObject2)
{
	for (long i = 0; i < headerObject.width * headerObject.height; i++)
	{
		headerObject.image[i].red = (unsigned char)((((float)headerObject.image[i].red / 255.0f) * ((float)headerObject2.image[i].red / 255.0f)) * 255.0f + .5f);
		headerObject.image[i].green = (unsigned char)((((float)headerObject.image[i].green / 255.0f) * ((float)headerObject2.image[i].green / 255.0f)) * 255.0f + .5f);
		headerObject.image[i].blue = (unsigned char)((((float)headerObject.image[i].blue / 255.0f) * ((float)headerObject2.image[i].blue / 255.0f)) * 255.0f + .5f);
	}
}

void subBlend(Header& bottomLayer, Header& topLayer)
{
	int topColor;
	int bottomColor;
	int subColor;

	for (long i = 0; i < topLayer.width* bottomLayer.height; i++)
	{
		/*=====RED=====*/
		topColor = topLayer.image[i].red;
		bottomColor = bottomLayer.image[i].red;

		if (bottomColor - topColor < 0)
		{
			bottomLayer.image[i].red = 0;
		}
		else
		{
			subColor = bottomColor - topColor;
			bottomLayer.image[i].red = subColor;
		}

		/*=====GREEN=====*/
		topColor = topLayer.image[i].green;
		bottomColor = bottomLayer.image[i].green;

		if (bottomColor - topColor < 0)
		{
			bottomLayer.image[i].green = 0;
		}
		else
		{
			subColor = bottomColor - topColor;
			bottomLayer.image[i].green = subColor;
		}

		/*=====BLUE=====*/
		topColor = topLayer.image[i].blue;
		bottomColor = bottomLayer.image[i].blue;

		if (bottomColor - topColor < 0)
		{
			bottomLayer.image[i].blue = 0;
		}
		else
		{
			subColor = bottomColor - topColor;
			bottomLayer.image[i].blue = subColor;
		}
	}
}

void screen(Header& bottomLayer, Header& topLayer)
{
	for (long i = 0; i < bottomLayer.width * bottomLayer.height; i++)
	{
		bottomLayer.image[i].red = (unsigned char)(((1.0f - (1.0f - ((float)bottomLayer.image[i].red) / 255.0f) * (1.0f - ((float)(topLayer.image[i].red) / 255.0f))) * 255.0f) + .5f);
		bottomLayer.image[i].green = (unsigned char)(((1.0f - (1.0f - ((float)bottomLayer.image[i].green) / 255.0f) * (1.0f - ((float)(topLayer.image[i].green) / 255.0f))) * 255.0f) + .5f);
		bottomLayer.image[i].blue = (unsigned char)(((1.0f - (1.0f - ((float)bottomLayer.image[i].blue) / 255.0f) * (1.0f - ((float)(topLayer.image[i].blue) / 255.0f))) * 255.0f) + .5f);
	}
}

void add(Header& headerObject, int value, string color)
{
	int headerColor;
	int finalColor;

	if (color == "red")
	{
		for (long i = 0; i < headerObject.width * headerObject.height; i++)
		{
			headerColor = headerObject.image[i].red;

			if (headerColor + value > 255)
			{
				headerObject.image[i].red = 255;
			}
			else
			{
				finalColor = headerColor + value;
				headerObject.image[i].red = finalColor;
			}
		}
	}

	else if (color == "green")
	{
		for (long i = 0; i < headerObject.width * headerObject.height; i++)
		{
			headerColor = headerObject.image[i].green;

			if (headerColor + value > 255)
			{
				headerObject.image[i].green = 255;
			}
			else
			{
				finalColor = headerColor + value;
				headerObject.image[i].green = finalColor;
			}
		}
	}

	else if (color == "blue")
	{
		for (long i = 0; i < headerObject.width * headerObject.height; i++)
		{
			headerColor = headerObject.image[i].blue;

			if (headerColor + value > 255)
			{
				headerObject.image[i].blue = 255;
			}
			else
			{
				finalColor = headerColor + value;
				headerObject.image[i].blue = finalColor;
			}
		}
	}
}

void scale(Header& headerObject, int value, string color)
{
	int origColor;
	int newColor;

	if (color == "blue") // Red and Blue flipped?
	{
		for (long i = 0; i < headerObject.width * headerObject.height; i++)
		{
			origColor = headerObject.image[i].red;
			if (origColor * value > 255)
			{
				headerObject.image[i].red = 255;
			}
			else if (origColor * value <= 0)
			{
				headerObject.image[i].red = 0;
			}
			else
			{
				//int origRed = headerObject.image[i].red;
				//cout << "\nOriginal red color: " << origRed << endl;
				headerObject.image[i].red = (origColor * value);
				//int red = headerObject.image[i].red;
				//cout << "\nNew red color: " << red << endl;
			}
		}
	}

	else if (color == "green")
	{
		for (long i = 0; i < headerObject.width * headerObject.height; i++)
		{
			origColor = headerObject.image[i].green;
			if (origColor * value > 255)
			{
				headerObject.image[i].green = 255;
			}
			else if (origColor * value <= 0)
			{
				headerObject.image[i].green = 0;
			}
			else
			{
				//int origRed = headerObject.image[i].red;
				//cout << "\nOriginal red color: " << origRed << endl;
				headerObject.image[i].green = (origColor * value);
				//int red = headerObject.image[i].red;
				//cout << "\nNew red color: " << red << endl;
			}
		}
	}

	else if (color == "red") // Red and Blue flipped?
	{
		for (long i = 0; i < headerObject.width * headerObject.height; i++)
		{
			origColor = headerObject.image[i].blue;
			//cout << "\nOriginal Blue color: " << origColor << endl;
			if (origColor * value > 255)
			{
				headerObject.image[i].blue = 255;
				newColor = headerObject.image[i].blue;
				//cout << "\nIf color > 255: " << newColor << endl;
			}
			else if (origColor * value <= 0)
			{
				headerObject.image[i].blue = 0;
				newColor = headerObject.image[i].blue;
				//cout << "\nIf color <= 0: " << newColor << endl;
			}
			else
			{
				//int origRed = headerObject.image[i].red;
				//cout << "\nOriginal red color: " << origRed << endl;
				headerObject.image[i].blue = (origColor * value);
				//int red = headerObject.image[i].red;
				//cout << "\nNew red color: " << red << endl;
				newColor = headerObject.image[i].blue;
				//cout << "\nIf calculated: " << newColor << endl;
			}
		}
	}
}

void colorChannel(Header& headerObject, string color)
{
	if (color == "blue")
	{
		for (long i = 0; i < headerObject.height * headerObject.width; i++)
		{
				headerObject.image[i].green = headerObject.image[i].red;
				headerObject.image[i].blue = headerObject.image[i].red;
		}
	}

	else if (color == "green")
	{
		for (long i = 0; i < headerObject.height * headerObject.width; i++)
		{
			headerObject.image[i].red = headerObject.image[i].green;
			headerObject.image[i].blue = headerObject.image[i].green;
		}
	}

	else if (color == "red")
	{
		for (long i = 0; i < headerObject.height * headerObject.width; i++)
		{
			headerObject.image[i].red = headerObject.image[i].blue;
			headerObject.image[i].green = headerObject.image[i].blue;
		}
	}
}

void combineColorChannels(Header& headerObjectR, Header& headerObjectG, Header& headerObjectB)
{
	for (long i = 0; i < headerObjectR.height * headerObjectR.width; i++)
	{
		headerObjectR.image[i].red = headerObjectB.image[i].red;
		headerObjectR.image[i].green = headerObjectG.image[i].green;
		headerObjectR.image[i].blue = headerObjectR.image[i].blue;
	}
}

void flipOutput(string fileID, Header& headerObject)
{
	int temp;
	int count = headerObject.width * headerObject.height;

	for (long i = 0; i < count / 2; i++)
	{
		temp = headerObject.image[i].red;
		headerObject.image[i].red = headerObject.image[count - i - 1].red;
		headerObject.image[count - i - 1].red = temp;

		temp = headerObject.image[i].green;
		headerObject.image[i].green = headerObject.image[count - i - 1].green;
		headerObject.image[count - i - 1].green = temp;

		temp = headerObject.image[i].blue;
		headerObject.image[i].blue = headerObject.image[count - i - 1].blue;
		headerObject.image[count - i - 1].blue = temp;
	}
}

void combine(Header& topLeft, Header& topRight, Header& bottomLeft, Header& bottomRight)
{
	long totalwidth = topLeft.width + topRight.width + bottomLeft.width + bottomRight.width;
	long totalHeight = topLeft.height + topRight.height + bottomLeft.height + bottomRight.height;

	//for (long i = 0; )
	//long totalSize;
	//long size1 = topLeft.width * topLeft.height;
	//long size2 = topRight.width * topRight.height;
	//long size3 = bottomRight.width * bottomRight.height;
	//long size4 = bottomLeft.width * bottomLeft.height;
	//totalSize = size1 + size2 + size3 + size4;


}

void overlay(Header& bottomLayer, Header& topLayer)
{
	for (long i = 0; i < bottomLayer.width * bottomLayer.height; i++)
	{
		/*=====RED=====*/
		if (bottomLayer.image[i].red / 255.0f <= .5f)
		{
			bottomLayer.image[i].red = (unsigned char)((((float)bottomLayer.image[i].red / 255.0f) * ((float)topLayer.image[i].red / 255.0f)) * 255.0f * 2.0f + .5f);
		}
		else
		{
			bottomLayer.image[i].red = (unsigned char)(((1.0f - (1.0f - ((float)bottomLayer.image[i].red) / 255.0f) * (1.0f - ((float)(topLayer.image[i].red) / 255.0f))) * 255.0f * 2.0f) + 1.5f);
		}

		/*=====GREEN=====*/
		if (bottomLayer.image[i].green / 255.0f <= .5f)
		{
			bottomLayer.image[i].green = (unsigned char)((((float)bottomLayer.image[i].green / 255.0f) * ((float)topLayer.image[i].green / 255.0f)) * 255.0f * 2.0f + .5f);
		}
		else
		{
			bottomLayer.image[i].green = (unsigned char)(((1.0f - (1.0f - ((float)bottomLayer.image[i].green) / 255.0f) * (1.0f - ((float)(topLayer.image[i].green) / 255.0f))) * 255.0f * 2.0f) + 1.5f);
		}

		/*=====BLUE=====*/
		if (bottomLayer.image[i].blue / 255.0f <= .5f)
		{
			bottomLayer.image[i].blue = (unsigned char)((((float)bottomLayer.image[i].blue / 255.0f) * ((float)topLayer.image[i].blue / 255.0f)) * 255.0f * 2.0f + .5f);
		}
		else
		{
			bottomLayer.image[i].blue = (unsigned char)(((1.0f - (1.0f - ((float)bottomLayer.image[i].blue) / 255.0f) * (1.0f - ((float)(topLayer.image[i].blue) / 255.0f))) * 255.0f * 2.0f) + 1.5f);
		}
	}
}

bool compare(Header& example, Header& copy)
{
	bool success = true;
	int exampleColor;
	int copyColor;

	if (example.idLength != copy.idLength)
	{
		cout << "\nTest Failed! ID Length is not equal.\n";
		success = false;
	}

	if (example.colorMapType != copy.colorMapType)
	{
		cout << "\nTest Failed! Color Map Type is not equal.\n";
		success = false;
	}

	if (example.dataTypeCode != copy.dataTypeCode)
	{
		cout << "\nTest Failed! Data Type Code is not equal.\n";
		success = false;
	}

	if (example.colorMapOrigin != copy.colorMapOrigin)
	{
		cout << "\nTest Failed! Color Map Origin is not equal.\n";
		success = false;
	}

	if (example.colorMapLength != copy.colorMapLength)
	{
		cout << "\nTest Failed! Color Map Length is not equal.\n";
		success = false;
	}

	if (example.colorMapDepth != copy.colorMapDepth)
	{
		cout << "\nTest Failed! Color Map Depth is not equal.\n";
		success = false;
	}

	if (example.xOrigin != copy.xOrigin)
	{
		cout << "\nTest Failed! X Origin is not equal.\n";
		success = false;
	}

	if (example.yOrigin != copy.yOrigin)
	{
		cout << "\nTest Failed! Color Map Length is not equal.\n";
		success = false;
	}

	if (example.bitsPerPixel != copy.bitsPerPixel)
	{
		cout << "\nTest Failed! Bits Per Pixel is not equal.\n";
		success = false;
	}

	if (example.imageDescriptor != copy.imageDescriptor)
	{
		cout << "\nTest Failed! Image Descriptor is not equal.\n";
		success = false;
	}

	if (example.imageSize != copy.imageSize)
	{
		cout << "\nTest Failed! Image Size is not equal.\n";
		success = false;
	}

	if (example.width != copy.width)
	{
		cout << "\nTest Failed! Width is not equal.\n";
		success = false;
	}

	if (example.height != copy.height)
	{
		cout << "\nTest Failed! Height is not equal.\n";
		success = false;
	}

	for (long i = 0; i < example.width * example.height; i++)
	{
		exampleColor = example.image[i].red;
		copyColor = copy.image[i].red;

		if (exampleColor != copyColor)
		{
			//cout << "\nExample pixel color: " << exampleColor << endl;
			//cout << "\nCopy pixel color: " << copyColor << endl;
			success = false;
		}

		exampleColor = example.image[i].green;
		copyColor = copy.image[i].green;

		if (exampleColor != copyColor)
		{
			//cout << "\nExample pixel color: " << exampleColor << endl;
			//cout << "\nCopy pixel color: " << copyColor << endl;
			success = false;
		}

		exampleColor = example.image[i].blue;
		copyColor = copy.image[i].blue;

		if (exampleColor != copyColor)
		{
			//cout << "\nExample pixel color: " << exampleColor << endl;
			//cout << "\nCopy pixel color: " << copyColor << endl;
			success = false;
		}
	}
	return success;
}