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
    for(int ystep = ymax; ystep > 0; ystep--){
        for(int xstep = 0; xstep < xmax; xstep++){
            float alpha = distance(xstep, ystep, 100, 100, 25, 90) / distance(61, 10, 100, 100, 25, 90); //distance from xstep,ystep to CB
            float beta = distance(xstep, ystep, 61, 10, 25, 90) / distance(100, 100, 61, 10, 25, 90); //distance from xstep,ystep to AC
            float gamma = distance(xstep, ystep, 100, 100, 61, 10) / distance(25, 90, 100, 100, 61, 10); //distance from xstep,ystep to BA
            cout << alpha << " " << beta << " " << gamma << endl;
            if(alpha < 0.0 || beta < 0.0 || gamma < 0.0){
                image << 255 << " " << 255 << " " << 192 << " ";
                continue;
            }
            int R = (100 + (100 * alpha));
            int G = 100 + (100 * beta);
            int B = 100 + (100 * gamma);
            R = (R < 0)? 0 : (R > 255)? 255 : R;
            G = (G < 0)? 0 : (G > 255)? 255 : G;
            B = (B < 0)? 0 : (B > 255)? 255 : B;

            image << R << " " << G << " " << B << " ";
        }
        image << endl;
    }

}

void halfplanetest(ofstream & image, float xmax, float ymax){
    for(int ystep = ymax; ystep > 0; ystep--){
        for(int xstep = 0; xstep < xmax; xstep++){
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
    for(int ystep = ymax; ymax > 0; ystep--){
        for(int xstep = 0; xstep < xmax; xstep++){
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
    for(int ystep = ymax; ystep > 0; ystep--){
        for(int xstep = 0; xstep < ymax; xstep++){
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
    int h, w, max;
    getline(in, p3);
    // if(p3 != "P3"){
    //     cout << "incorrect file format" << endl;
    //     return;
    // }
    in.ignore(100, '\n');
    in >> w; in >> h; in >> max;
    cout << h << w <<max << endl;
    int pixels[h][w*3];
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w*3; j++){
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

    for(int ystep = ymax; ystep > 0; ystep--){
        for(int xstep = 0; xstep < xmax; xstep++){
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

            int texely = h * b1;
            int texelx = w * b2;

            int R = pixels[texely][(texelx*3)];
            int G = pixels[texely][(texelx*3+1)];
            int B = pixels[texely][(texelx*3+2)];

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
    ofstream image(argv[1]);
    image << "P3" << endl;
    image << "#" << endl;
    image << argv[2] << " " << argv[3] << endl;
    image << "255" << endl;
    
    //fullcolour(image, stoi(argv[2]), stoi(argv[3]));
    //halfplanetest(image, stoi(argv[2]), stoi(argv[3]));
    baryinterp(image, stoi(argv[2]), stoi(argv[3]));

    //ifstream in(argv[1]);
    //readPPM(in);
    image.close();
    //in.close();
    
    return 0;
}