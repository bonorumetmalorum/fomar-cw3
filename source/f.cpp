#include <iomanip>
#include <math.h>
#include <iostream>

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

void calculateCoordinatesOfMysteryLocation()
{
    //find the texels for pixel coordinates 62, 65
    float alpha = distance(62, 65, 100, 100, 25, 90) / distance(61, 10, 100, 100, 25, 90); //distance from xstep,ystep to CB
    float beta = distance(62, 65, 61, 10, 25, 90) / distance(100, 100, 61, 10, 25, 90);    //distance from xstep,ystep to AC
    float gamma = distance(62, 65, 100, 100, 61, 10) / distance(25, 90, 100, 100, 61, 10); //distance from xstep,ystep to BA
    float uweight = (0.160268 * alpha) + (0.083611 * beta) + (0.230169 * gamma);
    float vweight = ((0.290086) * alpha) + ((0.159907) * beta) + ((0.222781) * gamma);
    //convert texels to lat and long
    double x = 512 * uweight;
    double y = 256 - (256 * (vweight));
    double lat = ((x/512.0) - 0.5)*(2*M_PI);
    double lon = ((y/256.0) - 0.5)*M_PI;
    //convert radians to degrees
    double deglat = lat*(180.0/M_PI);
    double deglon = lon*(180.0/M_PI);
    
    cout << setprecision(6) << fixed << "Question f) latitude: " << deglat << " longitude: " << deglon <<
    " Canada place cruise ship terminal is the mystery location" << endl;
    //bingo- Canada place cruise ship terminal :)!
}

int main(int argc, char ** argv){
    calculateCoordinatesOfMysteryLocation();
} 