/*
fern.cpp by Charles Adair
Made for CS3505 Software Practice II with Eric Heisler @ The University of Utah
Last Modified: January 16, 2026

This program generates Barnsley's Fern by iteratively applying vector transformations to points
and then prints the bit representation of the image as a representation of spaces and hashtags.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

const int width = 128;    // change width as desired
const int height = 48;   // change height as desired as long as width * height is a multiple of 8
const double xMax = 2.75; // DO NOT CHANGE
const double yMax = 10.1; // DO NOT CHANGE

const int probabilities[4] = {1, 7, 7, 85};
const double transformations[4][6] = {
    {0.0, 0.0, 0.0, 0.0, 0.16, 0.0},
    {0.2, -0.26, 0.0, 0.23, 0.22, 1.6},
    {-0.15, 0.28, 0.0, 0.26, 0.24, 0.44},
    {0.85, 0.04, 0.0, -0.04, 0.85, 1.6}
};

void performIterations(int iterations, unsigned char* image);
int selectTransformation();
void applyTransformation(double& x, double& y, const double* transformation);
void setPixel(double x, double y, unsigned char* image);
bool getPixel(int row, int col, unsigned char* image);
void drawImage(unsigned char* image);

/*
 Generates the seed, asks the user for the number of iterations, and then creates and prints the fern into standard output assuming that the number was valid.
 */
int main() {
    std::srand(time(0));
    unsigned char image[(width * height) / 8] = {0};
    int iterations;
std::cout << "How many iterations? ";

if (!(std::cin >> iterations) || iterations <= 0) {
    std::cout << "Invalid input. Please enter a whole number: " << std::endl;
    return 0;
}
    std::cout << std::endl;
    performIterations(iterations, image);
    drawImage(image);

    return 0;
}

/*
Iteratively selects a transformation, applies the transformation, then repeats a specified number or times.
*/
void performIterations(int iterations, unsigned char* image) {
    double x = 0.0;
    double y = 0.0;

    for (int i = 0; i < iterations; i++) {
        int transformation = selectTransformation();
        applyTransformation(x, y, transformations[transformation]);
        setPixel(x, y, image);
    }
}

/*
Gets a random number 1-100 and, based on the probabilities described by the Barnsley Fern wiki, decides which transformation to apply
*/
int selectTransformation() {
    int r = std::rand() % 100 + 1;

    if ( r == 1 ) {
        return 0;
    }
    if ( r <= 8 ) {
        return 1;
    }
    if ( r <= 15 ) {
        return 2;
    }
    return 3;
}

/*
 Sets the specified pixel as 'on' by editing the bit to a 1
 */
void setPixel(double x, double y, unsigned char* image) {
    int pixelX = (int)((width - 1) / 2 * (1 + x / xMax));
    int pixelY = (int)((height - 1) * (1 - y / yMax));

    // From the 2D array, calculates the location of the pixel in the 1D array
    int totalIndex = ( pixelY * width ) + pixelX;

    // Gets the byte, then the location of the bit within the byte
    int byteIndex = totalIndex / 8;
    int bitOffset = totalIndex % 8;

    // Sets the specified bit to 'on'
    image[byteIndex] = image[byteIndex] | (1 << bitOffset);
}

/*
Tells whether a specified pixel is 'on' or 'off'
*/
bool getPixel(int row, int col, unsigned char* image) {
    // From the 2D array, calculates the location of the pixel in the 1D array
    int totalIndex = ( row * width ) + col;

    // Gets the byte, then the location of the bit within the byte
    int byteIndex = totalIndex / 8;
    int bitOffset = totalIndex % 8;

    // Returns whether the pixel is on or off
    return (image[byteIndex] & (1 << bitOffset)) != 0;
}

/*
Takes a given transformation in the form of an 6 long array of doubles, and transforms the given point to a new point. 
 */
void applyTransformation(double& x, double& y, const double* transformation) {
    double newX = (x * transformation[0]) + (y * transformation[1]) + transformation[2];
    double newY = (x * transformation[3]) + (y * transformation[4]) + transformation[5];
    x = newX;
    y = newY;
}

/*v  m
Iterates through each pixel and prints it to the standard output.
*/
void drawImage(unsigned char* image) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (getPixel(row, col, image)) {
                std::cout << "#";
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}
