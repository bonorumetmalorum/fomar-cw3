#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>

using namespace std;

float distance(float pointx, float pointy, float edgepoint1x, float edgepoint1y, float edgepoint2x, float edgepoint2y)
{
    //point in relation to one end of line
    float x = pointx - edgepoint1x;
    float y = pointy - edgepoint1y;
    //vector on line
    float ex = edgepoint2x - edgepoint1x;
    float ey = edgepoint2y - edgepoint1y;
    //normal to line
    float invex = -ey;
    float invey = ex;
    //dot product of point vector and normal
    float dotproduct = (x * invex) + (y * invey);
    //magnitude of normal
    float magnitudeNormal = sqrt((invex * invex) + (invey * invey));
    //removing scaling from distance
    return dotproduct / magnitudeNormal;
};

void setupImage(vector<vector<int>> &image, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j*3] = 255;
            image[i][j*3 + 1] = 255;
            image[i][j*3 + 2] = 192;
        }
    }
}

void baryinterp(vector<vector<int>> &imageBuffer, float xmax, float ymax)
{
    for (int ystep = ymax - 1; ystep >= 0; ystep--)
    {
        for (int xstep = 0; xstep < xmax; xstep++)
        {
            float alpha = distance(xstep, ystep, 100, 100, 25, 90) / distance(61, 10, 100, 100, 25, 90); //distance from xstep,ystep to CB
            float beta = distance(xstep, ystep, 61, 10, 25, 90) / distance(100, 100, 61, 10, 25, 90);    //distance from xstep,ystep to AC
            float gamma = distance(xstep, ystep, 100, 100, 61, 10) / distance(25, 90, 100, 100, 61, 10); //distance from xstep,ystep to BA
            if (alpha < 0.0 || beta < 0.0 || gamma < 0.0)
            {
                // imageBuffer[ystep][xstep*3] = 0;
                // imageBuffer[ystep][xstep*3+1] = 0;
                // imageBuffer[ystep][xstep*3+1] = 0;
                continue;
            }
            int R = 255 * alpha;
            int G = 255 * beta;
            int B = 255 * gamma;

            imageBuffer[ystep][xstep*3] = R;
            imageBuffer[ystep][xstep*3 + 1] = G;
            imageBuffer[ystep][xstep*3 + 2] = B;
        }
    }
};

void outputImage(ofstream & image, vector<vector<int>> & imageBuffer, int width, int height){
    image << "P3" << endl;
    image << "#" << endl;
    image << "128 128" << endl;
    image << "255" << endl;
    for(int ystep = height-1; ystep >= 0; ystep--){
        for(int xstep = 0; xstep < width; xstep++){
            image << imageBuffer[ystep][xstep*3] << " " << imageBuffer[ystep][xstep*3+1] << " " << imageBuffer[ystep][xstep*3+2] << " ";
        }
        image << endl;
    }
}

int main(int argc, char **argv)
{
    ofstream image("./out/rgb.ppm");
    vector<int> row(128 * 3, 0);
    vector<vector<int>> imageBuffer(128, row);
    setupImage(imageBuffer, 128, 128);
    baryinterp(imageBuffer, 128, 128);
    outputImage(image, imageBuffer, 128, 128);
    image.close();
}