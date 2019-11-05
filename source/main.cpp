#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;


float distance(float pointx, float pointy, float edgepoint1x, float edgepoint1y, float edgepoint2x, float edgepoint2y){
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
    return dotproduct/magnitudeNormal;
}

//A = 61, 10
//B = 100, 100
//C = 25, 90

void baryinterp(ofstream & image, float xmax, float ymax){
    for(int xstep = 0; xstep < xmax; xstep++){
        for(int ystep = 0; ystep < ymax; ystep++){
            float alpha = distance(xstep, ystep, 100, 100, 25, 90) / distance(61, 10, 100, 100, 25, 90); //distance from xstep,ystep to CB
            float beta = distance(xstep, ystep, 61, 10, 25, 90) / distance(100, 100, 61, 10, 25, 90); //distance from xstep,ystep to AC
            float gamma = distance(xstep, ystep, 100, 100, 61, 10) / distance(25, 90, 100, 100, 61, 10); //distance from xstep,ystep to BA
            if(alpha < 0.0 || beta < 0.0 || gamma < 0.0){
                image << 255 << " " << 255 << " " << 192 << endl;
                continue;
            }
            cout << alpha << " " << beta << " " << gamma << endl;
            int R = (100 + (100 * alpha));
            int G = 100 + (100 * beta);
            int B = 100 + (100 * gamma);
            R = (R < 0)? 0 : (R > 255)? 255 : R;
            G = (G < 0)? 0 : (G > 255)? 255 : G;
            B = (B < 0)? 0 : (B > 255)? 255 : B;

            image << R << " " << G << " " << B << endl;
        }
    }

}

void halfplanetest(ofstream & image, float xmax, float ymax){
    for(int xstep = 0; xstep < xmax; xstep++){
        for(int ystep = 0; ystep < ymax; ystep++){
            float alpha = distance(xstep, ystep, 100, 100, 25, 90) / distance(61, 10, 100, 100, 25, 90); //distance from xstep,ystep to CB
            float beta = distance(xstep, ystep, 61, 10, 25, 90) / distance(100, 100, 61, 10, 25, 90); //distance from xstep,ystep to AC
            float gamma = distance(xstep, ystep, 100, 100, 61, 10) / distance(25, 90, 100, 100, 61, 10); //distance from xstep,ystep to BA
            if(alpha < 0){
                //R
                image << 255 << " ";
            }
            if(alpha >= 0){
                image << 0 << " ";
            }
            if(beta < 0){
                //G
                image << 255 << " ";
            }
            if(beta >= 0){
                image << 0 << " ";
            }
            if(gamma < 0){
                //B
                image << 255 << " " << endl;
            }
            if(gamma >= 0){
                image << 0 << " " << endl;
            }
        }
    }

}


void blacktriangle(ofstream & image, float xmax, float ymax){
    for(int xstep = 0; xstep < xmax; xstep++){
        for(int ystep = 0; ystep < ymax; ystep++){
            float alpha = distance(xstep, ystep, 100, 100, 25, 90) / distance(61, 10, 100, 100, 25, 90); //distance from xstep,ystep to CB
            float beta = distance(xstep, ystep, 61, 10, 25, 90) / distance(100, 100, 61, 10, 25, 90); //distance from xstep,ystep to AC
            float gamma = distance(xstep, ystep, 100, 100, 61, 10) / distance(25, 90, 100, 100, 61, 10); //distance from xstep,ystep to BA
            if(alpha < 0){
                //R
                image << 255 << " ";
            }
            if(alpha >= 0){
                image << 0 << " ";
            }
            if(beta < 0){
                //G
                image << 255 << " ";
            }
            if(beta >= 0){
                image << 0 << " ";
            }
            if(gamma < 0){
                //B
                image << 255 << " " << endl;
            }
            if(gamma >= 0){
                image << 0 << " " << endl;
            }
        }
    }

}

void fullcolour(ofstream & image, float xmax, float ymax){
    for(int xstep = 0; xstep < xmax; xstep++){
        for(int ystep = 0; ystep < ymax; ystep++){
            float alpha = distance(xstep, ystep, 100, 100, 25, 90) / distance(61, 10, 100, 100, 25, 90); //distance from xstep,ystep to CB
            float beta = distance(xstep, ystep, 61, 10, 25, 90) / distance(100, 100, 61, 10, 25, 90); //distance from xstep,ystep to AC
            float gamma = distance(xstep, ystep, 100, 100, 61, 10) / distance(25, 90, 100, 100, 61, 10); //distance from xstep,ystep to BA
            if(alpha < 0.0 || beta < 0.0 || gamma < 0.0){
                image << 0 << " " << 0 << " " << 0 << endl;
                continue;
            }
            cout << alpha << " " << beta << " " << gamma << endl;
            
            
            int R = 255 * alpha;
            int G = 255 * beta;
            int B = 255 * gamma;
           
           
            R = (R < 0)? 0 : (R > 255)? 255 : R;
            G = (G < 0)? 0 : (G > 255)? 255 : G;
            B = (B < 0)? 0 : (B > 255)? 255 : B;

            image << R << " " << G << " " << B << endl;
        }
    }

}

int main(int argc, char ** argv){
    if(argc < 4){
        cout << "please provide output file name, xmax and ymax" << endl;
        return -1;
    }
    ofstream image(argv[1]);
    image << "P3" << endl;
    image << "#" << endl;
    image << argv[2] << " " << argv[3] << endl;
    image << "255" << endl;
    fullcolour(image, stoi(argv[2]), stoi(argv[3]));
    image.close();
    return 0;
}