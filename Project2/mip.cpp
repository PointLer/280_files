#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include "image.h"
#include "constants.h"

using namespace std;

//I/O functions:
void readImage(istream &is, Image &imI);
void writeImage(ostream &os, const Image &imI);

//Basic operating functions:
void verticalFlip(const Image &imI, Image &imJ);
void rotate90(const Image &imI, Image &imJ);
void intensityInversion(const Image &imI, Image &imJ, unsigned char Max);

//Filters:
const int s = 1;
typedef unsigned char (*Agg) (const unsigned char values[2 * s + 1][2 * s + 1]);
unsigned char max(const unsigned char values[2 * s + 1][2 * s + 1]);
unsigned char mean(const unsigned char values[2 * s + 1][2 * s + 1]);
unsigned char median(const unsigned char values[2 * s + 1][2 * s + 1]);
void filter(const Image &imI, Image &imJ, Agg f);

//Show the ppm file for debugging:
void show(Image &im){
    cout << "P6" << endl << im.w << " " << im.h << endl << "255" << endl;
    for(auto i = 0u; i < im.w; i++){
        for(auto j = 0u; j < im.h; j++){
            cout << (int)im.image[i][j].red << " ";
        }
	cout << endl;
    }
    cout << endl;
}

int main(int argc, char *argv[]){
    bool in_standard = true, out_standard = true; //store whether the program will read from standard stream or not
    ifstream iFile;
    ofstream oFile;
    Image imI, imJ;       //input image and output image
    Agg trans;
    string transformation;//store the kind of transformation

    string order;         //store the orders in argv[]
    for(int i = 1; i < argc; i++){
        order = argv[i];
        if(order == "--help" || order == "-h"){
            cout << HELP_MESSAGE << endl;
            return 0;
        }
        else if(order == "-i"){
            in_standard = false;     //dosen't need to read from standard input
            string i_file = argv[i + 1];
            iFile.open(i_file);
            if(!iFile){
                cout << FILE_NOT_EXIST_ERROR << endl;
                return 0;
            }

            if(iFile && i_file.substr(i_file.size() - 4, 4) != ".ppm"){
                cout << FILE_TYPE_ERROR << endl;
                return 0;
            }
        }
        else if(order == "-o"){
            out_standard = false;     //dosen't need to read from standard output
            string o_file = argv[i + 1];
            oFile.open(o_file);
        }
        else if(order == "-t"){
            transformation = argv[i + 1];
            if(transformation != "verticalFlip" && transformation != "rotate90" &&
               transformation != "intensityInversion" && transformation != "maxFilter" &&
               transformation != "meanFilter" && transformation != "medianFilter"){
                cout << TRANSFORM_ERROR << endl; 
                return 0;
            }
        }   
    }

    //Test whether read from file or standard input
    if(in_standard){
        readImage(cin, imI);
    }
    else{
        readImage(iFile, imI);
    }

    //Apply typical transformation:
    if(transformation == "verticalFlip"){
        verticalFlip(imI, imJ);
    }
    else if(transformation == "rotate90"){
        rotate90(imI, imJ);
    }
    else if(transformation == "intensityInversion"){
        intensityInversion(imI, imJ, (unsigned int)M);
    }
    else if(transformation == "maxFilter"){
        trans = max;
        filter(imI, imJ, trans);
    }
    else if(transformation == "meanFilter"){
        trans = mean;
        filter(imI, imJ, trans);
    }
    else {
        trans = median;
        filter(imI, imJ, trans);
    }

    //test whether write to file or standard output
    if(out_standard){
        writeImage(cout, imJ);
    }
    else{
        writeImage(oFile, imJ);
    }
    
    iFile.close();
    oFile.close();
    return 0;
}


void readImage(istream &is, Image &imI){
    //EFFECTS: Reads an image from an input stream and stores it in an Image struct
    //REQUIRES: The size of is should be the same as imI
    string temp;
    getline(is, temp);         //flush the first line
    getline(is, temp);         //store the size of the image

    istringstream iStream;
    iStream.str(temp);
    iStream >> imI.w >> imI.h; //store the size in the struct
    getline(is, temp);         //flush the third line

    for(auto i = 0u; i < imI.w; i++){
        for(auto j = 0u; j < imI.h; j++){
            imI.image[i][j].red = is.get();
            imI.image[i][j].green = is.get();
            imI.image[i][j].blue = is.get();
        }
    }
}

void writeImage(ostream &os, const Image &imI){
    os << "P6" << endl << imI.w << " " << imI.h << endl << "255" << endl;
    for(auto i = 0u; i < imI.w; i++){
        for(auto j = 0u; j < imI.h; j++){
            os << imI.image[i][j].red         // red
		       << imI.image[i][j].green       // green
		       << imI.image[i][j].blue;       //blue
        }
    }
}

void verticalFlip(const Image &imI, Image &imJ){
    //EFFECTS:vertical flip
    auto Height = imI.h;
    auto Width = imI.w;
    for (auto i = 0u; i < Width; i++){
        for (auto j = 0u; j < Height; j++){
            /*imJ.image[i][j].red = imI.image[i][Height - 1 - j].red;
            imJ.image[i][j].green = imI.image[i][Height - 1 - j].green;
            imJ.image[i][j].blue = imI.image[i][Height - 1 - j].blue;*/  //verticalFLip by line
            imJ.image[i][j].red = imI.image[Width - 1 - i][j].red;
            imJ.image[i][j].green = imI.image[Width - 1 - i][j].green;
            imJ.image[i][j].blue = imI.image[Width - 1 - i][j].blue;
        }
    }
    imJ.h = Height;
    imJ.w = Width;
}

void rotate90(const Image &imI, Image &imJ){
    //EFFECTS:rotate 90 
    auto Height = imI.h;
    auto Width = imI.w;
    for (auto j = 0u; j < Height; j++ )
        for (auto i = 0u; i < Width; i++)
            /*imJ.image[Height - 1 - j][i] = imI.image[i][j]; */ //rotate90 clockwise
            imJ.image[j][Width - i - 1] = imI.image[i][j];
    
    imJ.h = Width;
    imJ.w = Height;
}

void intensityInversion(const Image &imI, Image &imJ, unsigned char Max){//M类型与RGB相同 默认为255
    //EFFECTS:change the intensity
    auto Height = imI.h;
    auto Width = imI.w;
    for (auto j = 0u; j < Height; j++){
        for (auto i = 0u; i < Width; i++){
            imJ.image[i][j].red = Max - imI.image[i][j].red; 
            imJ.image[i][j].green = Max - imI.image[i][j].green; 
            imJ.image[i][j].blue = Max - imI.image[i][j].blue; 
        }
    }
    
    imJ.h = Height;
    imJ.w = Width;
}

unsigned char max(const unsigned char values[2 * s + 1][2 * s + 1]){
    unsigned char max = values[0][0];
    for(int i = 0; i < 2 * s + 1; i++){
        for(int j = 0; j < 2 * s + 1; j++){
            if(values[i][j] > max)
                max = values[i][j];
        }
    }
    return max;
}


unsigned char mean(const unsigned char values[2 * s + 1][2 * s + 1]){
    int sum = 0;
    for(int i = 0; i < 2 * s + 1; i++){
        for(int j = 0; j < 2 * s + 1; j++){
            sum += (int) values[i][j];
        }
    }
    int mean =  sum / ((2 * s + 1) * (2 * s + 1));
    return (unsigned char) mean;
}

unsigned char median(const unsigned char values[2 * s + 1][2 * s + 1]){
    unsigned char temp_values[(2 * s + 1) * (2 * s + 1)];
    int count = 0;
    for(int i = 0; i < 2 * s + 1; i++){
        for(int j = 0; j < 2 * s + 1; j++){
            temp_values[count] = values[i][j];
            count ++;
        }
    }

    //ascending bubble sort:
    for(int i = 0; i < (2 * s + 1) * (2 * s + 1) - 1; i++){
        for(int j = 0; j < (2 * s + 1) * (2 * s + 1) - 1 - i; j++){
            if(temp_values[j] > temp_values[j + 1]){
                //swap
                unsigned char temp = temp_values[j];
                temp_values[j] = temp_values[j + 1];
                temp_values[j + 1] = temp;
            }
        }
    }

    unsigned char median = temp_values[2 * s * s + 2 * s];
    return median;
}

void filter(const Image &imI, Image &imJ, Agg f){
    auto Height = imI.h;
    auto Width = imI.w;
    unsigned char values_r[2 * s + 1][2 * s + 1], values_g[2 * s + 1][2 * s + 1], values_b[2 * s + 1][2 * s + 1]; //temp values
    for (int j = 0; j < (int)Height; j++){
        for (int i = 0; i < (int)Width; i++){
            //initialize the 3*3 matrix:
            for(int k = 0; k < (2 * s + 1); k++){
                for(int l = 0; l < (2 * s + 1); l++){
                    if(i - 1 + k < 0 || j - 1 + l < 0 || i - 1 + k == (int)Width || j - 1 + l == (int)Height){
                        values_r[k][l] = (unsigned char)0;
                        values_g[k][l] = (unsigned char)0;
                        values_b[k][l] = (unsigned char)0;
                    }
                    else{
                        values_r[k][l] = imI.image[i - 1 + k][j - 1 + l].red;
                        values_g[k][l] = imI.image[i - 1 + k][j - 1 + l].green;
                        values_b[k][l] = imI.image[i - 1 + k][j - 1 + l].blue;
                    }
                }
            }

            //apply Agg function
            imJ.image[i][j].red = f(values_r);
            imJ.image[i][j].green = f(values_g);
            imJ.image[i][j].blue = f(values_b);
        }
    }
    imJ.h = Height;
    imJ.w = Width;
}
