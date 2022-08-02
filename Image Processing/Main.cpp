#include "ImageProcessing.h"
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
	Header headerObject;
	Header headerObject2;
	Header headerObject3;
	
	/*=====TEST 1 PASSED=====*/
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/input/layer1.tga", headerObject); // in MakeFile: input/layer1
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/input/pattern1.tga", headerObject2);
	multBlend(headerObject, headerObject2);
	outputData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/output/part1.tga", headerObject);
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/examples/EXAMPLE_part1.tga", headerObject2);
	
	if (compare(headerObject2, headerObject))
	{
		cout << "Test 1 Passed!\n";
	}
	else
	{
		cout << "Test 1 Failed!\n";
	}

	/*=====TEST 2 PASSED=====*/
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/input/car.tga", headerObject);
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/input/layer2.tga", headerObject2);
	subBlend(headerObject, headerObject2);
	outputData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/output/part2.tga", headerObject);
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/examples/EXAMPLE_part2.tga", headerObject2);

	if (compare(headerObject2, headerObject))
	{
		cout << "\nTest 2 Passed!\n";
	}
	else
	{
		cout << "\nTest 2 Failed!\n";
	}


	/*=====TEST 3 PASSED=====*/
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/input/layer1.tga", headerObject);
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/input/pattern2.tga", headerObject2);
	multBlend(headerObject, headerObject2);
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/input/text.tga", headerObject2);
	screen(headerObject, headerObject2);
	outputData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/output/part3.tga", headerObject);
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/examples/EXAMPLE_part3.tga", headerObject2);

	if (compare(headerObject2, headerObject))
	{
		cout << "\nTest 3 Passed!\n";
	}
	else
	{
		cout << "\nTest 3 Failed!\n";
	}

	/*=====TEST 4 PASSED=====*/
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/input/layer2.tga", headerObject);
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/input/circles.tga", headerObject2);
	multBlend(headerObject, headerObject2);
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/input/pattern2.tga", headerObject2);
	subBlend(headerObject, headerObject2);
	outputData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/output/part4.tga", headerObject);
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/examples/EXAMPLE_part4.tga", headerObject2);

	if (compare(headerObject2, headerObject))
	{
		cout << "\nTest 4 Passed!\n";
	}
	else
	{
		cout << "\nTest 4 Failed!\n";
	}

	/*=====TEST 5=====*/
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/input/layer1.tga", headerObject);
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/input/pattern1.tga", headerObject2);
	overlay(headerObject2, headerObject);
	outputData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/output/part5.tga", headerObject2);
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/examples/EXAMPLE_part5.tga", headerObject);

	if (compare(headerObject, headerObject2))
	{
		cout << "\nTest 5 Passed!\n";
	}
	else
	{
		cout << "\nTest 5 Failed!\n";
	}

	/*=====TEST 6 PASSED=====*/
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/input/car.tga", headerObject);
	add(headerObject, 200, "green");
	outputData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/output/part6.tga", headerObject);
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/examples/EXAMPLE_part6.tga", headerObject2);

	if (compare(headerObject2, headerObject))
	{
		cout << "\nTest 6 Passed!\n";
	}
	else
	{
		cout << "\nTest 6 Failed!\n";
	}

	/*=====TEST 7 PASSED (COLORS INVERTED)=====*/
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/input/car.tga", headerObject);
	scale(headerObject, 4, "red");
	scale(headerObject, 0, "blue");
	outputData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/output/part7.tga", headerObject);
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/examples/EXAMPLE_part7.tga", headerObject2);

	if (compare(headerObject2, headerObject))
	{
		cout << "\nTest 7 Passed!\n";
	}
	else
	{
		cout << "\nTest 7 Failed!\n";
	}

	/*=====TEST 8 PASSED (COLORS INVERTED=====*/
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/input/car.tga", headerObject);
	colorChannel(headerObject, "blue");
	outputData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/output/part8_b.tga", headerObject);
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/examples/EXAMPLE_part8_b.tga", headerObject2);

	if (compare(headerObject2, headerObject))
	{
		cout << "\nTest 8.b Passed!\n";
	}
	else
	{
		cout << "\nTest 8.b Failed!\n";
	}

	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/input/car.tga", headerObject);
	colorChannel(headerObject, "green");
	outputData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/output/part8_g.tga", headerObject);
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/examples/EXAMPLE_part8_g.tga", headerObject2);

	if (compare(headerObject2, headerObject))
	{
		cout << "\nTest 8.g Passed!\n";
	}
	else
	{
		cout << "\nTest 8.g Failed!\n";
	}

	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/input/car.tga", headerObject);
	colorChannel(headerObject, "red");
	outputData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/output/part8_r.tga", headerObject);
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/examples/EXAMPLE_part8_r.tga", headerObject2);

	if (compare(headerObject2, headerObject))
	{
		cout << "\nTest 8.r Passed!\n";
	}
	else
	{
		cout << "\nTest 8.r Failed!\n";
	}

	/*=====TEST 9 PASSED (COLORS INVERTED)=====*/
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/input/layer_red.tga", headerObject);
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/input/layer_green.tga", headerObject2);
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/input/layer_blue.tga", headerObject3);
	colorChannel(headerObject, "blue");
	colorChannel(headerObject2, "green");
	colorChannel(headerObject3, "red");
	combineColorChannels(headerObject, headerObject2, headerObject3);
	outputData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/output/part9.tga", headerObject);
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/examples/EXAMPLE_part9.tga", headerObject2);

	if (compare(headerObject2, headerObject))
	{
		cout << "\nTest 9 Passed!\n";
	}
	else
	{
		cout << "\nTest 9 Failed!\n";
	}

	/*=====TEST 10 PASSED=====*/
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/input/text2.tga", headerObject);
	flipOutput("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/output/Test10.tga", headerObject);
	outputData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/output/part10.tga", headerObject);
	loadData("C:/Users/19044/Documents/UF Sophomore Year/COP3503/ImageProcessing/examples/EXAMPLE_part10.tga", headerObject2);

	if (compare(headerObject2, headerObject))
	{
		cout << "\nTest 10 Passed!\n";
	}
	else
	{
		cout << "\nTest 10 Failed!\n";
	}

	/*=====EXTRA CREDIT=====*/

	return 0;
}