#include <iostream>
#include <math.h>
#include <fstream>
#include <istream>
#include <vector>
#include <string>

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
}

void setupImage(vector<vector<int>> &image, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j * 3] = 255;
            image[i][j * 3 + 1] = 255;
            image[i][j * 3 + 2] = 192;
        }
    }
}

vector<vector<int>> readTexture(string path)
{
    ifstream in(path);
    if (in.fail())
    {
        throw "failed to read file";
    }
    string p3;
    string comment;
    int h, w, max;
    getline(in, p3);
    in.ignore(100, '\n');
    in >> w;
    in >> h;
    in >> max;
    vector<int> row(w * 3, 129);
    vector<vector<int>> pixels(h, row);
    for (int i = h - 1; i >= 0; i--)
    {
        for (int j = 0; j < w; j++)
        {
            in >> pixels[i][j * 3];
            in >> pixels[i][j * 3 + 1];
            in >> pixels[i][j * 3 + 2];
        }
    }
    in.close();
    return pixels;
};

void textureTriangle(vector<vector<int>> &texture, vector<vector<int>> &imageBuffer, int width, int height, int textureWidth, int textureHeight)
{
    for (int ystep = height - 1; ystep >= 0; ystep--)
    {
        for (int xstep = 0; xstep < width; xstep++)
        {
            float alpha = distance(xstep, ystep, 100, 100, 25, 90) / distance(61, 10, 100, 100, 25, 90); //distance from xstep,ystep to CB
            float beta = distance(xstep, ystep, 61, 10, 25, 90) / distance(100, 100, 61, 10, 25, 90);    //distance from xstep,ystep to AC
            float gamma = distance(xstep, ystep, 100, 100, 61, 10) / distance(25, 90, 100, 100, 61, 10); //distance from xstep,ystep to BA
            if (alpha < 0.0 || beta < 0.0 || gamma < 0.0)
            {
                continue;
            }

            float uweight = (0.160268 * alpha) + (0.083611 * beta) + (0.230169 * gamma);
            float vweight = ((0.290086) * alpha) + ((0.159907) * beta) + ((0.222781) * gamma);

            int texelx = textureWidth * uweight;
            int texely = textureHeight - (textureHeight * vweight);

            imageBuffer[ystep][xstep * 3] = texture[texely][(texelx * 3)];
            imageBuffer[ystep][xstep * 3 + 1] = texture[texely][(texelx * 3 + 1)];
            imageBuffer[ystep][xstep * 3 + 2] = texture[texely][(texelx * 3 + 2)];
        }
    }
}

void outputImage(ofstream &image, vector<vector<int>> &imageBuffer, int width, int height)
{
    image << "P3" << endl;
    image << "#" << endl;
    image << "128 128" << endl;
    image << "255" << endl;
    for (int ystep = height - 1; ystep >= 0; ystep--)
    {
        for (int xstep = 0; xstep < width; xstep++)
        {
            image << imageBuffer[ystep][xstep * 3] << " " << imageBuffer[ystep][xstep * 3 + 1] << " " << imageBuffer[ystep][xstep * 3 + 2] << " ";
        }
        image << endl;
    }
}

int main(int argc, char **argv)
{
    cout << "input path to texture" << endl;
    string path;
    cin >> path;
    ofstream image("./out/texture.ppm");
    vector<int> row(128 * 3, 129);
    vector<vector<int>> imageBuffer(128, row);
    setupImage(imageBuffer, 128, 128);
    try
    {
        vector<vector<int>> texture = readTexture(path);
        textureTriangle(texture, imageBuffer, 128, 128, 512, 256);
        outputImage(image, imageBuffer, 128, 128);
        image.close();
    }
    catch (const char *e)
    {
        cout << e << endl;
        image.close();
        return 1;
    }
}