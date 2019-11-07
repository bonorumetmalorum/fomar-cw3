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
    cout << x << y <<max << endl;
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
            cout << "hello" << endl;
            float alpha = distance(xstep, ystep, 100, 100, 25, 90) / distance(61, 10, 100, 100, 25, 90); //distance from xstep,ystep to CB
            float beta = distance(xstep, ystep, 61, 10, 25, 90) / distance(100, 100, 61, 10, 25, 90); //distance from xstep,ystep to AC
            float gamma = distance(xstep, ystep, 100, 100, 61, 10) / distance(25, 90, 100, 100, 61, 10); //distance from xstep,ystep to BA
            if(alpha < 0.0 || beta < 0.0 || gamma < 0.0){
                image << 0 << " " << 0 << " " << 0 << " ";
                cout << "not inside triangle" << endl; 
                continue;
            }
            cout << alpha << " " << beta << " " << gamma << endl;

            float b1 = (0.160268 * alpha) + (0.083611 * beta) + (0.230169 * gamma);
            float b2 = (0.290086 * alpha) + (0.159907 * beta) + (0.222781 * gamma);
            
            float s = x * b1;
            float t = y * b2;

            int i = s;
            int j = s;

            float sParm = s - i;
            float tParm = t - j;

            //ij
            int R0 = pixels[i][j*3];
            int G0 = pixels[i][j*3+1];
            int B0 = pixels[i][j*3+2];
            //ij+1
            int R1 = pixels[i][(j+1)*3];
            int G1 = pixels[i][(j+1)*3+1];
            int B1 = pixels[i][(j+1)*3+2];
            //i+1j
            int R2 = pixels[i+1][j*3];
            int G2 = pixels[i+1][j*3+1];
            int B2 = pixels[i+1][j*3+2];
            //i+1j+1
            int R3 = pixels[i+1][(j+1)*3];
            int G3 = pixels[i+1][(j+1)*3+1];
            int B3 = pixels[i+1][(j+1)*3+2];

            //colours on edges
            int cR0, cG0, cB0, cR1, cG1, cB1;
            cR0 = R0 + tParm * (R1 - R0);
            cG0 = G0 + tParm * (G1 - G0);
            cB0 = B0 + tParm * (B1 - B0);

            cR1 = R2 + tParm * (R3 - R2);
            cG1 = R2 + tParm * (G3 - G2);
            cB1 = R2 + tParm * (B3 - B2);

            //calculate interpolated texel
            int colourR, colourG, colourB;
            colourR = cR1 + sParm * (cR1 - cR0);
            colourG = cG1 + sParm * (cG1 - cG0);
            colourB = cB1 + sParm * (cB1 - cB0);
            
            image << colourR << " " << colourG << " " << colourB << " " ;
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