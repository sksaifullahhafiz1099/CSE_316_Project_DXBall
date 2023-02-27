#include "LedControl.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//  #include <SPI.h>
//  #include <SD.h>

LedControl lc=LedControl(7,6,5,8);
//-----SD---------------------------------------------------------------------
// File dataFile;
//-----LCD_Analog_stick--------------------------------------------------------
LiquidCrystal_I2C lcd(0x3F,20,4); 
int xValue = 0; // To store value of the X axis
char buffer1[10]; 

//-----Game_variables----------------------------------------------------------
const int x=0;
const int y=1;

int lives=2;
int score=0;
String highScore="0";

int pedal[2]={8,0};
int ball[2]={9,14};
int pedal_direction =0;
int render[24][16];
int temp_pos[2]={0,0};
int ball_angle[2]={-1,-1};
int heart[8][8] = {{0,0,0,0,0,0,0,0},
                   {0,0,1,0,0,0,1,0},
                   {0,1,1,1,0,1,1,1},
                   {0,1,1,1,1,1,1,1},
                   {0,0,1,1,1,1,1,0},
                   {0,0,0,1,1,1,0,0},
                   {0,0,0,0,1,0,0,0},
                   {0,0,0,0,0,0,0,0}};
//int joy_input=0;
bool life_check=true;

int counter=0;
bool two_dot=false;
int two_dot_frame=0;

//-----Save_variables----------------------------------------------------------

void ini(){

   // initialize render

    for(int i=0;i<24;i++)
        for(int j=0;j<16;j++)
            render[i][j]=0;

    //render only brick and wall

    for(int i = 0; i < 24; i++) {
        for(int j = 0; j < 16; j++) {
            if((j == 0 || i == 0 || i == 23) or (j<6 and i>0 and j>0 and i<23)) {
                render[i][j] = 1;
            }
        }
    }


  lives=2;
  score=0;
}



void Render(){


 for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
     
       
        if(render[col][row]==1)
          lc.setLed(3,row,col,true);
        else
          lc.setLed(3,row,col,false);
      }
    }

   for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
     
        if(render[col+8][row]==1)
          lc.setLed(2,row,col,true);
        else
          lc.setLed(2,row,col,false);
      }
    }

   for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
     
        if(render[col+16][row]==1)
          lc.setLed(1,row,col,true);
        else
          lc.setLed(1,row,col,false);
      }
    }

 for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
     
      

      if(render[col][row+8]){
          row=7-row;
          col=7-col;
          lc.setLed(4,row,col,true);
          row=7-row;
          col=7-col;
      }else
      { 
          row=7-row;
          col=7-col;
          lc.setLed(4,row,col,false);
          row=7-row;
          col=7-col;
      }
          
      }
    }

   for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
     
        
          if(render[col+8][row+8]){
          row=7-row;
          col=7-col;
          lc.setLed(5,row,col,true);
          row=7-row;
          col=7-col;
      }
      else{
          row=7-row;
          col=7-col;
          lc.setLed(5,row,col,false);
          row=7-row;
          col=7-col;
      }
      }
    }

   for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
     
      
          if(render[col+16][row+8]){
          row=7-row;
          col=7-col;
          lc.setLed(6,row,col,true);
          row=7-row;
          col=7-col;
      }else{
         row=7-row;
          col=7-col;
          lc.setLed(6,row,col,false);
          row=7-row;
          col=7-col;
      }
      }
    }


if(life_check)
  if(lives>0)
    {    
       for(int row=0;row<8;row++) 
          for(int col=0;col<8;col++) {
            if(heart[row][col]==1)
               lc.setLed(0,row,col,true);
            else
              lc.setLed(0,row,col,false);
         }

    
      if(lives>1){

          for(int row=0;row<8;row++) {
            for(int col=0;col<8;col++) {
             if(heart[row][col]){
                 row=7-row;
                  col=7-col;
                 lc.setLed(7,row,col,true);
                row=7-row;
                col=7-col;
            }else
              { 
               row=7-row;
               col=7-col;
                lc.setLed(7,row,col,false);
                 row=7-row;
               col=7-col;
               }
          
                  }
            }
      }else{
        for(int row=0;row<8;row++) {
          for(int col=0;col<8;col++) {
               lc.setLed(7,row,col,false);     
          }
        }
    }
    

    }else{

//----------
       for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
     
          lc.setLed(0,row,col,false);
        }
       }

    for(int row=0;row<8;row++) {
          for(int col=0;col<8;col++) {
               lc.setLed(7,row,col,false);     
          }
        }
//----------------
    }

 

}

void setup() {
  //we have already set the number of devices when we created the LedControl
  int devices=lc.getDeviceCount();
  //we have to init all devices in a loop
  for(int address=0;address<devices;address++) {
    /*The MAX72XX is in power-saving mode on startup*/
    lc.shutdown(address,false);
    /* Set the brightness to a medium values */
    lc.setIntensity(address,8);
    /* and clear the display */
    lc.clearDisplay(address);
  }


//--game_initialization--------------------------------------------

  ini();
  Render();
     //--lcd_analog------------------------------------------------------
  lcd.init();                  
  lcd.backlight(); 

  //--SD_card----------------------------------------------------
  // SD.begin(4);
  // dataFile = SD.open("data.txt", FILE_WRITE);
  
}




void loop() { 

  life_check=false;
  
  //--lcd_analog---------------------------
    xValue = analogRead(A0);

  sprintf(buffer1, "Score:%d", score);  

  lcd.clear();

  lcd.setCursor(1,0);
  lcd.print(buffer1);
  
  

  //   highScore=dataFile.read();
  //   if(score>highScore.toInt())
  //   {
  //       highScore=String(score);
  //      dataFile.write(highScore);
  //   }
    
  //  sprintf(buffer1, "hScore : %d", highScore);  
  //  lcd.setCursor(1,1);
  // lcd.print(buffer1);
  // dataFile.close();




 //---game_code---------------------------

  // refresh

    if(lives>0){

    render[ball[x]][ball[y]] = 0;

    render[pedal[x]][15] = 0; 
    render[pedal[x]+1][15] = 0; 
    render[pedal[x]+2][15] = 0; 
    render[pedal[x]+3][15] = 0; 
    render[pedal[x]+4][15] = 0; 
    render[pedal[x]+5][15] = 0; 
    render[pedal[x]+6][15] = 0;



    //Controlling pedal
    
	if(xValue>800) {

		if(pedal[x]>1)
			pedal_direction=-1;
		else
			pedal_direction=0;
    }
	else if(xValue<200) {

		if(pedal[x]<16)
			pedal_direction=1;
		else
			pedal_direction=0;
    }
	else {
		pedal_direction=0;
	}

    counter++;

    if(counter == 10000)
       counter = 0;

    //Physics

    if(counter %3 == 0) {

		two_dot_frame++;

		if(two_dot_frame%10==0)
			two_dot_frame=0;
		
		pedal[x]=pedal[x]+pedal_direction;

        //ground collision

        if(ball[y]==15){
          	ball[x]=pedal[x]+3;
            ball[y]=14;
			      ball_angle[x]= -1;
            ball_angle[y]= -1;
            lives--;
            life_check=true;
        }
		


        // pedal collision

		if(ball[x]>=pedal[x] and ball[x]<(pedal[x]+6) and ball[y]==14) {

			if(ball[x]==pedal[x] || ball[x]==pedal[x]+6) {
				if(ball_angle[x]>=0) {
					ball_angle[x] = 2;
                    ball_angle[y] = -1;
					two_dot=true;
                }
				else {
					ball_angle[x] = -2;
                    ball_angle[y] = -1;
					two_dot=true;	
                }
            }

			if(ball[x]==(pedal[x]+1) || ball[x]==(pedal[x]+5) ) {

                if(ball_angle[x]>=0) {
					ball_angle[x] = 1;
                    ball_angle[y] = -1;
					two_dot=false;
                }
				else {
					ball_angle[x] = -1;
                    ball_angle[y] = -1;
					two_dot=false;	
                }
            }

			if(ball[x]==(pedal[x]+2) || ball[x]==(pedal[x]+4)) {

                if(ball_angle[x]>=0) {
					ball_angle[x] = 1;
                    ball_angle[y] = -2;
					two_dot=true;
                }
				else {
					ball_angle[x] = -1;
                    ball_angle[y] = -2;
					two_dot=true;	
                }

            }


			if(ball[x]==(pedal[x]+3)) {

                if(ball_angle[x]>=0) {
					ball_angle[x] = 0;
                    ball_angle[y] = -1;
					two_dot=false;
                }
				else {
					ball_angle[x] = -0;
                    ball_angle[y] = -1;
					two_dot=false;	
                }

            }
		
        }

        // wall collision detection
		if(ball[x]==22)
			if(ball_angle[x]>0)
				ball_angle[x]=-ball_angle[x];
		if(ball[x]==1)
			if(ball_angle[x]<0)
				ball_angle[x]=-ball_angle[x];	
				
		if(ball[y]==1)
			if(ball_angle[y]<0)
				ball_angle[y]=-ball_angle[y];
				
		// ball physics

		if(two_dot==true){ 
			if(two_dot_frame%2==1) {
				if(abs(ball_angle[x])==2)
					ball[x]=ball[x]+ball_angle[x]/2;		
				if(abs(ball_angle[y])==2)
					ball[y]=ball[y]+ball_angle[y]/2;
            } else {
				if(abs(ball_angle[x])==2) {
					ball[x]=ball[x]+ball_angle[x]/2;
					ball[y]=ball[y]+ball_angle[y];
                }			
				if(abs(ball_angle[y])==2) {
					ball[y]=ball[y]+ball_angle[y]/2;
					ball[x]=ball[x]+ball_angle[x];
                }
            }
        if(ball[y]<6 and ball[x]>0 and ball[y]>0 and ball[x]<23)
          score++;

		} else{
			ball[x] = ball[x] + ball_angle[x];
            ball[y] = ball[y] + ball_angle[y];

          if(ball[y]<6 and ball[x]>0 and ball[y]>0 and ball[x]<23)
          score++;
        }


    }


	//rendering
	
	// ball render

    render[ball[x]][ball[y]] = 1;

	
    // Brick_render()


    //pedal render
	
	
    render[pedal[x]][15] = 1; 
    render[pedal[x]+1][15] = 1; 
    render[pedal[x]+2][15] = 1; 
    render[pedal[x]+3][15] = 1; 
    render[pedal[x]+4][15] = 1; 
    render[pedal[x]+5][15] = 1; 
    render[pedal[x]+6][15] = 1;

    Render();

    }
    else{

     for(int i=0;i<24;i++)
      for(int j=0;j<16;j++) 
        render[i][j]=1;

      Render();

      delay(1000);
 for(int i=0;i<24;i++)
      for(int j=0;j<16;j++) 
        render[i][j]=0;
      Render();
      
      life_check=true;
  ini();
  Render();

    }
 

  
  

  

}