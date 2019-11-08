#include <iostream>
#include <math.h>
#include <fstream>
#include <istream>
#include <vector>

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

void readPPM(ifstream & in){
    string p3;
    string comment;
    int x, y, max;
    getline(in, p3);
    // if(p3 != "P3"){
    //     cout << "incorrect file format" << endl;
    //     return;
    // }
    in.ignore(100, '\n');
    in >> x; in >> y; in >> max;
    //cout << x << y <<max << endl;
    int pixels[x][y*3];
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y*3; j++){
            in >> pixels[i][j];
        }
    }

    ofstream image("texturetest.ppm");

    image << "P3" << endl;
    image << "#" << endl;
    image << "128 128" << endl;
    image << "255" << endl;

    int xmax = 128;int ymax = 128;

    cout << xmax << ymax << endl;

    for(int xstep = 0; xstep < xmax; xstep++){
        for(int ystep = 0; ystep < ymax; ystep++){
            float alpha = distance(xstep, ystep, 100, 100, 25, 90) / distance(61, 10, 100, 100, 25, 90); //distance from xstep,ystep to CB
            float beta = distance(xstep, ystep, 61, 10, 25, 90) / distance(100, 100, 61, 10, 25, 90); //distance from xstep,ystep to AC
            float gamma = distance(xstep, ystep, 100, 100, 61, 10) / distance(25, 90, 100, 100, 61, 10); //distance from xstep,ystep to BA
            if(alpha < 0.0 || beta < 0.0 || gamma < 0.0){
                image << 0 << " " << 0 << " " << 0 << " ";
                continue;
            }
            //cout << alpha << " " << beta << " " << gamma << endl;

            float b1 = (0.160268 * alpha) + (0.083611 * beta) + (0.230169 * gamma);
            float b2 = (0.290086 * alpha) + (0.159907 * beta) + (0.222781 * gamma);
            
            float s = x * b1;
            float t = y * b2;

            int i = s;
            int j = t;

            float sParm = s - i;
            float tParm = t - j;

            int R0, G0, B0, R1, G1, B1, R2, G2, B2, R3, G3, B3;

            //ij
            R0 = pixels[i][j*3];
            G0 = pixels[i][j*3+1];
            B0 = pixels[i][j*3+2];
            //special cases
            if(i == y-1 && j == x-1){
                //ij+1
                R1 = pixels[i][(j)*3];
                G1 = pixels[i][(j)*3+1];
                B1 = pixels[i][(j)*3+2];
                //i+1j
                R2 = pixels[i][j*3];
                G2 = pixels[i][j*3+1];
                B2 = pixels[i][j*3+2];
                //i+1j+1
                R3 = pixels[i][(j)*3];
                G3 = pixels[i][(j)*3+1];
                B3 = pixels[i][(j)*3+2];

            }
            else if(i == y-1){
                R1 = pixels[i][(j+1)*3];
                G1 = pixels[i][(j+1)*3+1];
                B1 = pixels[i][(j+1)*3+2];
                //i+1j
                R2 = pixels[i][j*3];
                G2 = pixels[i][j*3+1];
                B2 = pixels[i][j*3+2];
                //i+1j+1
                R3 = pixels[i][(j+1)*3];
                G3 = pixels[i][(j+1)*3+1];
                B3 = pixels[i][(j+1)*3+2];
            }
            else if(j == x-1){
                //ij+1
                R1 = pixels[i][(j)*3];
                G1 = pixels[i][(j)*3+1];
                B1 = pixels[i][(j)*3+2];
                //i+1j
                R2 = pixels[i+1][j*3];
                G2 = pixels[i+1][j*3+1];
                B2 = pixels[i+1][j*3+2];
                //i+1j+1
                R3 = pixels[i+1][(j)*3];
                G3 = pixels[i+1][(j)*3+1];
                B3 = pixels[i+1][(j)*3+2];
            }
            else{
                //ij+1
                R1 = pixels[i][(j+1)*3];
                G1 = pixels[i][(j+1)*3+1];
                B1 = pixels[i][(j+1)*3+2];
                //i+1j
                R2 = pixels[i+1][j*3];
                G2 = pixels[i+1][j*3+1];
                B2 = pixels[i+1][j*3+2];
                //i+1j+1
                R3 = pixels[i+1][(j+1)*3];
                G3 = pixels[i+1][(j+1)*3+1];
                B3 = pixels[i+1][(j+1)*3+2];
            }


            int R, G, B;

            R = R0*(1-sParm)*(1-tParm) + R1 * (sParm) * (1-tParm) + R2*(1-sParm)*(tParm) + R3*sParm*tParm;
            G = G0*(1-sParm)*(1-tParm) + G1 * (sParm) * (1-tParm) + G2*(1-sParm)*(tParm) + G3*sParm*tParm;
            B = B0*(1-sParm)*(1-tParm) + B1 * (sParm) * (1-tParm) + B2*(1-sParm)*(tParm) + B3*sParm*tParm;

            image << R << " " << G << " " << B << " " ;
        }
        image << endl;
    }

}

int main(int argc, char ** argv){
    if(argc < 4){
        cout << "please provide output file name, xmax and ymax" << endl;
        return -1;
    }
    // ofstream image(argv[1]);
    // image << "P3" << endl;
    // image << "#" << endl;
    // image << argv[2] << " " << argv[3] << endl;
    // image << "255" << endl;
    // fullcolour(image, stoi(argv[2]), stoi(argv[3]));
    ifstream in(argv[1]);
    readPPM(in);
    //image.close();
    in.close();
    return 0;
}