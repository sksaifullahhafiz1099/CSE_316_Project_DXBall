#include <iostream.h>
using namespace std;

const x=0;
const y=1;

int pedal[2]={13,0};
int ball[2]={}9,14};
int pedal_direction =0;
int render[16][16];
int brick[16][16];
int wall[16][16];
int temp_pos[2]={0,0}

int counter=0;
bool two_dot=false;
int two_dot_frame=0;

setup(){
    for(int i=0;i<16;i++)
        for(int j=0;j<16;j++)
            render[i][j]=0;

    for(int i=0;i<16;i++)
        for(int j=0;j<16;j++)
            {
               if(y<6 and y>0 and x>0 and x<15)
                    brick[x][y]=1;
               else
                    brick[x][y]=0;
            }



}

int main(){




}
