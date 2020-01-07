#include <iostream>
#include <ctime>
#include "ImageProcessing/ImageProcessing.hpp"
#include "EasyBMP/EasyBMP.h"

using namespace std;
using namespace ip;

int main()
{
	BMP img;
	img.ReadFromFile("test.bmp");

	byte** im = new byte*[img.TellHeight()];


	for ( int y = 0; y < img.TellHeight(); y++ )
	{
		im[y] = new byte[img.TellWidth()];
		for (int x = 0; x < img.TellWidth(); x++ )
		{
			im[y][x] = img(x, y) -> brightness();
		}
	}


	time_t currTime = time(NULL);

	byte threshold = percentThreshold(im, img.TellWidth(), img.TellHeight(), 200, 0.999f);
	//byte threshold = otsuThreshold(im, img.TellWidth(), img.TellHeight(), 255, 200, 2);

	std::list<Blob>* blobs = ip::findBlobs(im, img.TellWidth(), img.TellHeight(), threshold, 1);



	int numBlobs = 8;
	//ip::Blob* points = ip::getMainPoints(*blobs, numBlobs);
	ip::Blob* points = ip::listToArray(blobs); numBlobs = blobs->size();

	cout << (time(NULL) - currTime) << endl;

	cout << "Found: " << blobs->size() << " blobs." << endl;



	delete blobs;






	byte** im2 = new byte*[img.TellHeight()];

	for ( int y = 0; y < img.TellHeight(); y++ )
	{
		im2[y] = new byte[img.TellWidth()];
		for ( int x = 0; x < img.TellWidth(); x++ )
		{
			im2[y][x] = 0;
			for ( int i = 0; i < numBlobs; i++ )
			{
				if ( points[i].withinThreshold(x, y, 0) ) im2[y][x] = im[y][x];
			}
		}
	}
	ip::combineImages(im, im2, img.TellWidth(), img.TellHeight(), "test_output.bmp");

/*
	for ( int y = 0; y < img.TellHeight(); y++ )
	{
		for ( int x = 0; x < img.TellWidth(); x++ )
		{
			bool found = false;
			for ( int i = 0; i < numBlobs; i++ )
			{
				found |= points[i].withinThreshold(x, y, 0);
			}
			if ( !found )
			{
				img(x, y) -> Red = 0;
				img(x, y) -> Green = 0;
				img(x, y) -> Blue = 0;
			}
		}
	}

	img.WriteToFile("test_output.bmp");*/


	for ( int y = 0; y < img.TellHeight(); y++ )
	{
		delete[] im[y];
	}
	delete[] im;
	delete[] points;




	return 0;
}