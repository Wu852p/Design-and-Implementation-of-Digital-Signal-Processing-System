/* =================================================================================
File name  : main.c
Modify     : MAIWEI /sales@mcudsp.com.tw
Website    : http://www.mcudsp.com.tw
Version    : V1.0
Description: Primary system file for the DTMF Labs.
==================================================================================*/
#include "easyDSP-Expansion_Board.h"
#include <math.h>
#include <stdio.h>

#define SAMPLING_FREQ 12000
#define PI 3.14159265358979
#define loop_time 12000/2

unsigned short row=0,col=0,sample=0;
unsigned short digital=0,old_digital=0,se1,se2;
short DTMF_count=0,DTMF_flag=0;
int bit=1;
long count=0;
int s1=0;
int s2=0;
int s3=1;
int s4=1;
int an=1;
int sbit=0;
int cbit[16];
int ccount=0;
int j=0,ij=0;
char pa[8]={'P','A','S','S','!','!','!','!'};
unsigned short sequence[8]={0,0,2,7,6,5,2};
//int cseq[16]={1, 0, 6, 0, 0, 5, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0};
//int cseq[16]={1, 0, 7, 11, 0, 10, 9, 8, 0, 0, 0, 0, 0, 0, 0, 0};
int cseq[16]={0, 0, 6, 10, 0, 9, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0};
float theta_increment;
float theta = 0.0;
int main(void)
{
  Board_Init(); //Initial easyDSP-Expansion_Board
  Setup_Audio_Init(FS_12000_HZ,ADC_GAIN_0DB,DAC_ATTEN_0DB,LINE_INPUT);
  for(j=0;j<=16;j++){
      cbit[j]=0;
  }

  while(1)
  {
      if ( Read_SW(4)==1){

          s1=0;
          s2=0;
          s3=1;
          s4=1;
          se1=0;
          se2=0;
          row=0;
          sample=0;
          digital=0;
          old_digital=0;
          DTMF_count=0;
          DTMF_flag=0;
          bit=1;
          count=0;
          an=1;
          sbit=0;
          ccount=0;
          j=0;
          ij=0;
          theta = 0.0;
          Board_Init(); //Initial easyDSP-Expansion_Board
          Setup_Audio_Init(FS_12000_HZ,ADC_GAIN_0DB,DAC_ATTEN_0DB,LINE_INPUT);

            for(j=0;j<=16;j++){
                cbit[j]=0;
            }
            LCD_PUT_CMD(LCD_FIRST_LINE);
            LCD_PUT_CHAR(' ');
            LCD_PUT_CHAR(' ');
            LCD_PUT_CHAR(' ');
            LCD_PUT_CHAR(' ');
            LCD_PUT_CHAR(' ');
            LCD_PUT_CHAR(' ');
            LCD_PUT_CHAR(' ');
            LCD_PUT_CHAR(' ');
      }

//      else if(Read_SW(1) == 1){
//          s1++;
//          s3++;
//      }
//      else if(Read_SW(2)==0){
//          s2++;
//          s1++;
//      }
//      else if(Read_SW(2)==1){
//          s2++;
//          s1++;
//      }
//      else if(Read_SW(3)==0){
//          s3++;
//          s4++;
//      }
//      else if(Read_SW(3)==1){
//          s3++;
//          s4++;
//      }
//      else if(Read_SW(4)==0){
//          s4++;
//          s1++;
//      }
//      else if(Read_SW(4)==1){
//          s4++;
//          s1++;
//      }


      if(s1%2==0){
          Control_LED_ON(1);
      }else if(s1%2==1){
          Control_LED_OFF(1);
      }

      if(s2%2==0){
          Control_LED_ON(2);

      }else if(s2%2==1){
          Control_LED_OFF(2);
      }

      if(s3%2==0){
          Control_LED_ON(3);
      }else if(s3%2==1){
          Control_LED_OFF(3);
      }

      if(s4%2==0){
          Control_LED_ON(4);
      }else if(s4%2==1){
          Control_LED_OFF(4);
      }

      if(an==1){
          se1=digital;
          se2=digital;
          while(1){
              digital = Read_keypad();
              se1=digital;
              if(se2 != se1){
                  break;
              }
              se2=se1;
          }
          an=0;
      }

      if(!(s1%2+s2%2+s3%2+s4%2)){
          digital = Read_keypad();
          se1=digital;

      if(se2 != se1){
          if(se1<=9){
              ij++;
              cbit[digital]=ij;
          }
      }

          if(Read_SW(2)==1){
              ccount=0;
//              for(j=0;j<16;j++){
//                  printf("%d, ",cbit[j]);
//              }
//              printf("\n");
              for(j=0;j<16;j++){
//                  ccount+=cbit[j];
//                  printf("%d, ",cbit[j]);
                  if(cseq[j]!=cbit[j]){
                      break;
                  }

              }

              if(j<16){
                  LCD_PUT_CMD(LCD_FIRST_LINE);
                  LCD_PUT_CHAR('W');
                  LCD_PUT_CHAR('r');
                  LCD_PUT_CHAR('o');
                  LCD_PUT_CHAR('n');
                  LCD_PUT_CHAR('g');
                  LCD_PUT_CHAR('!');
                  LCD_PUT_CHAR('!');
                  LCD_PUT_CHAR('!');
              }else if(j==16){
                  LCD_PUT_CMD(LCD_FIRST_LINE);
                  LCD_PUT_CHAR('P');
                  LCD_PUT_CHAR('A');
                  LCD_PUT_CHAR('S');
                  LCD_PUT_CHAR('S');
                  LCD_PUT_CHAR('!');
                  LCD_PUT_CHAR('!');
                  LCD_PUT_CHAR('!');
                  LCD_PUT_CHAR('!');
              }
//              printf("\n%d\n",j);
//              printf("%d\n",ccount);
          }


          switch(digital){
               case 1:
          //            row=697.0;
               row=262.0;
               col=1209.0;
          //            LCD_PUT_CHAR('1');
               break;

               case 2:
          //            row=697.0;
               row=294.0;
               col=1336.0;
          //            LCD_PUT_CHAR('2');
               break;

               case 3:
          //            row=697.0;
               row=330.0;
               col=1477.0;
          //            LCD_PUT_CHAR('3');
               break;

               case 4:
          //            row=770.0;
               row=349.0;
               col=1209.0;
          //            LCD_PUT_CHAR('4');
               break;

               case 5:
          //            row=770.0;
               row=392.0;
               col=1336.0;
          //            LCD_PUT_CHAR('5');
               break;

               case 6:
          //            row=770.0;
               row=440.0;
               col=1477.0;
          //            LCD_PUT_CHAR('6');
               break;

               case 7:
               row=494.0;
               col=1209.0;
          //            LCD_PUT_CHAR('7');
               break;

               case 8:
          //            row=852.0;
               row=524.0;
               col=1336.0;
          //            LCD_PUT_CHAR('8');
               break;

               case 9:
          //            row=852.0;
               row=588.0;
               col=1477.0;
          //            LCD_PUT_CHAR('9');
               break;

               case 0:
               row=0;
               col=1366.0;
          //            LCD_PUT_CHAR('0');
               break;

               case 10: //-->A
               row=0;
               col=1209.0;
          //            LCD_PUT_CHAR('A');
               break;

               case 11: //-->B
               row=0;
               col=1477.0;
          //            LCD_PUT_CHAR('B');
               break;

               case 12:
               row=0;
          //            LCD_PUT_CHAR('C');
               break;

               case 13:
               row=0;
          //            LCD_PUT_CHAR('D');
               break;

               case 14:
               row=0;
          //            LCD_PUT_CHAR('*');
               break;

               case 15:
               row=0;
          //            LCD_PUT_CHAR('#');
               break;
          }

          if(DTMF_flag==1)
          {
              if(old_digital != digital)
              {
                    DTMF_count = 0;
                    DTMF_flag = 0;
              }
           }
//          Setup_Audio();
          se2=se1;

      }




//      LCD_PUT_CMD(LCD_FIRST_LINE);



  }
}
//-------------------------------
// interrupt service routine #4
//-------------------------------
interrupt void INT4_ISR(void)
{
//    if(sbit==0){
//        theta_increment = 2*PI*row/SAMPLING_FREQ;
//        theta += theta_increment;
//        if (theta > 2*PI) theta -= 2*PI;
//        output_left_sample((short)(10000*(sin(theta))));
//    }

    if(DTMF_count < loop_time)
    {
        sample=10000*(sin(2.0*PI*DTMF_count*bit*row/SAMPLING_FREQ));
        DTMF_count++;
//        printf("123\n");
    }
    else
    {
        sample = 0;
        DTMF_flag=1;
        old_digital = digital;
        DTMF_count = loop_time;
//        printf("456\n");
    }
    output_left_sample(sample);
    return;
}
interrupt void INT5_ISR(void){
    s1++;
    s3++;
    return;
}
interrupt void INT6_ISR(void){
    s2++;
    s3++;
    return;
}
interrupt void INT7_ISR(void){

    s2++;
    s4++;
    return;
}
interrupt void INT8_ISR(void){
    s4++;
    return;
}


