#include <iostream>
#include "Image.h"
#include <cstdio>
using namespace std;

int main() {

	Image<bool> image(3, 3);
	image(0, 0) = true;
	image(1, 1) = false;
	cout << "image:\n" << image << endl;

	Image<bool> image1(3, 3);
	image1(0, 0) = true;
	image1(1, 1) = true;
	cout << "bimage1:\n" << image1 << endl;

	cout << image + image1 << endl;
	cout << image * image1 << endl;

	Image<int> image2(3, 3);
	image2(0, 0) = 3;
	image2(1, 1) = 7;
	cout << "image2:\n" << image2 << endl;

	Image<int> image3(3, 3);
	image3(0, 0) = 4;
	image3(1, 1) = 1;
	cout << "image3:\n" << image3 << endl;

	cout << image2 + image3 << endl;
	cout << image2 * image3 << endl;

	Image<short> image4(3, 3);
	image4(0, 0) = 5;
	image4(1, 1) = 7;
	cout << "image4:\n" << image4 << endl;

	Image<char> image5(3, 3);
	image5(0, 0) = 's';
	image5(1, 1) = 'a';
	cout << "image5:\n" << image5 << endl;

	Image<char> image6(3, 3);
	image6(0, 0) = 'd';
	image6(1, 1) = 'r';
	cout << "image6:\n" << image6 << endl;

	Image<float> image7(3, 3);
	image7(0, 0) = 7.1;
	image7(1, 1) = 7.2;
	cout << "image7:\n" << image7 << endl;

	Image<float> image8(3, 3);
	image8(0, 0) = 5.4;
	image8(1, 1) = 8.9;
	cout << "image8:\n" << image8 << endl;

	cout << image7 + image8 << endl;
	cout << image7 * image8 << endl;

	cout << (image == image1) << endl;

	cout << image2.ratio() << endl;
	//bimage = !bimage;
	//cout << "!bimage:\n" << bimage << endl;	



}