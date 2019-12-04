#include <pic32mx.h>
#include <stdint.h>
#include <stdlib.h> 

#define DISPLAY_VDD PORTFbits.RF6
#define DISPLAY_VBATT PORTFbits.RF5
#define DISPLAY_COMMAND_DATA PORTFbits.RF4
#define DISPLAY_RESET PORTGbits.RG9


#define DISPLAY_VDD_PORT PORTF
#define DISPLAY_VDD_MASK 0x40
#define DISPLAY_VBATT_PORT PORTF
#define DISPLAY_VBATT_MASK 0x20
#define DISPLAY_COMMAND_DATA_PORT PORTF
#define DISPLAY_COMMAND_DATA_MASK 0x10
#define DISPLAY_RESET_PORT PORTG
#define DISPLAY_RESET_MASK 0x200


char textbuffer[4][16];

static const uint8_t const font[] = {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 94, 0, 0, 0, 0,
  0, 0, 4, 3, 4, 3, 0, 0,
  0, 36, 126, 36, 36, 126, 36, 0,
  0, 36, 74, 255, 82, 36, 0, 0,
  0, 70, 38, 16, 8, 100, 98, 0,
  0, 52, 74, 74, 52, 32, 80, 0,
  0, 0, 0, 4, 3, 0, 0, 0,
  0, 0, 0, 126, 129, 0, 0, 0,
  0, 0, 0, 129, 126, 0, 0, 0,
  0, 42, 28, 62, 28, 42, 0, 0,
  0, 8, 8, 62, 8, 8, 0, 0,
  0, 0, 0, 128, 96, 0, 0, 0,
  0, 8, 8, 8, 8, 8, 0, 0,
  0, 0, 0, 0, 96, 0, 0, 0,
  0, 64, 32, 16, 8, 4, 2, 0,
  0, 62, 65, 73, 65, 62, 0, 0,
  0, 0, 66, 127, 64, 0, 0, 0,
  0, 0, 98, 81, 73, 70, 0, 0,
  0, 0, 34, 73, 73, 54, 0, 0,
  0, 0, 14, 8, 127, 8, 0, 0,
  0, 0, 35, 69, 69, 57, 0, 0,
  0, 0, 62, 73, 73, 50, 0, 0,
  0, 0, 1, 97, 25, 7, 0, 0,
  0, 0, 54, 73, 73, 54, 0, 0,
  0, 0, 6, 9, 9, 126, 0, 0,
  0, 0, 0, 102, 0, 0, 0, 0,
  0, 0, 128, 102, 0, 0, 0, 0,
  0, 0, 8, 20, 34, 65, 0, 0,
  0, 0, 20, 20, 20, 20, 0, 0,
  0, 0, 65, 34, 20, 8, 0, 0,
  0, 2, 1, 81, 9, 6, 0, 0,
  0, 28, 34, 89, 89, 82, 12, 0,
  0, 0, 126, 9, 9, 126, 0, 0,
  0, 0, 127, 73, 73, 54, 0, 0,
  0, 0, 62, 65, 65, 34, 0, 0,
  0, 0, 127, 65, 65, 62, 0, 0,
  0, 0, 127, 73, 73, 65, 0, 0,
  0, 0, 127, 9, 9, 1, 0, 0,
  0, 0, 62, 65, 81, 50, 0, 0,
  0, 0, 127, 8, 8, 127, 0, 0,
  0, 0, 65, 127, 65, 0, 0, 0,
  0, 0, 32, 64, 64, 63, 0, 0,
  0, 0, 127, 8, 20, 99, 0, 0,
  0, 0, 127, 64, 64, 64, 0, 0,
  0, 127, 2, 4, 2, 127, 0, 0,
  0, 127, 6, 8, 48, 127, 0, 0,
  0, 0, 62, 65, 65, 62, 0, 0,
  0, 0, 127, 9, 9, 6, 0, 0,
  0, 0, 62, 65, 97, 126, 64, 0,
  0, 0, 127, 9, 9, 118, 0, 0,
  0, 0, 38, 73, 73, 50, 0, 0,
  0, 1, 1, 127, 1, 1, 0, 0,
  0, 0, 63, 64, 64, 63, 0, 0,
  0, 31, 32, 64, 32, 31, 0, 0,
  0, 63, 64, 48, 64, 63, 0, 0,
  0, 0, 119, 8, 8, 119, 0, 0,
  0, 3, 4, 120, 4, 3, 0, 0,
  0, 0, 113, 73, 73, 71, 0, 0,
  0, 0, 127, 65, 65, 0, 0, 0,
  0, 2, 4, 8, 16, 32, 64, 0,
  0, 0, 0, 65, 65, 127, 0, 0,
  0, 4, 2, 1, 2, 4, 0, 0,
  0, 64, 64, 64, 64, 64, 64, 0,
  0, 0, 1, 2, 4, 0, 0, 0,
  0, 0, 48, 72, 40, 120, 0, 0,
  0, 0, 127, 72, 72, 48, 0, 0,
  0, 0, 48, 72, 72, 0, 0, 0,
  0, 0, 48, 72, 72, 127, 0, 0,
  0, 0, 48, 88, 88, 16, 0, 0,
  0, 0, 126, 9, 1, 2, 0, 0,
  0, 0, 80, 152, 152, 112, 0, 0,
  0, 0, 127, 8, 8, 112, 0, 0,
  0, 0, 0, 122, 0, 0, 0, 0,
  0, 0, 64, 128, 128, 122, 0, 0,
  0, 0, 127, 16, 40, 72, 0, 0,
  0, 0, 0, 127, 0, 0, 0, 0,
  0, 120, 8, 16, 8, 112, 0, 0,
  0, 0, 120, 8, 8, 112, 0, 0,
  0, 0, 48, 72, 72, 48, 0, 0,
  0, 0, 248, 40, 40, 16, 0, 0,
  0, 0, 16, 40, 40, 248, 0, 0,
  0, 0, 112, 8, 8, 16, 0, 0,
  0, 0, 72, 84, 84, 36, 0, 0,
  0, 0, 8, 60, 72, 32, 0, 0,
  0, 0, 56, 64, 32, 120, 0, 0,
  0, 0, 56, 64, 56, 0, 0, 0,
  0, 56, 64, 32, 64, 56, 0, 0,
  0, 0, 72, 48, 48, 72, 0, 0,
  0, 0, 24, 160, 160, 120, 0, 0,
  0, 0, 100, 84, 84, 76, 0, 0,
  0, 0, 8, 28, 34, 65, 0, 0,
  0, 0, 0, 126, 0, 0, 0, 0,
  0, 0, 65, 34, 28, 8, 0, 0,
  0, 0, 4, 2, 4, 2, 0, 0,
  0, 120, 68, 66, 68, 120, 0, 0,
};

int meteor1Info[5] = {0,0,0,0,0}; // Info about meteor1, {xPos,yPos,status,xMovement,yMovement}
int meteor2Info[5] = {0,0,0,0,0}; // Info about meteor2
int meteor3Info[5] = {0,0,0,0,0}; // Info about meteor3

int shot1Info[5] = {0,0,0,0,0}; // Info about shot 1  {xPos,yPos,status,xMovement,yMovement}

int shipInfo[5] = {0,0,0,0,0}; // Info about ship. 


uint8_t  icon1[512] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,/* End of first line, or the top 8 pixels */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, /* End of second line */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, /* End of third line */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff /* Last (fourth) line */
};

uint8_t icon2[512] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,/* End of first line, or the top 8 pixels */
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, /* End of second line */
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, /* End of third line */
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff /* Last (fourth) line */
};

uint8_t icon3[512] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,/* End of first line, or the top 8 pixels */
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, /* End of second line */
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, /* End of third line */
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff /* Last (fourth) line */
};

uint8_t icon4[512] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,/* End of first line, or the top 8 pixels */
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, /* End of second line */
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, /* End of third line */
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff /* Last (fourth) line */
};

void delay(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 0x01));
	return SPI2BUF;
}

void display_init() {
	DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;
	delay(10);
	DISPLAY_VDD_PORT &= ~DISPLAY_VDD_MASK;
	delay(1000000);
	
	spi_send_recv(0xAE);
	DISPLAY_RESET_PORT &= ~DISPLAY_RESET_MASK;
	delay(10);
	DISPLAY_RESET_PORT |= DISPLAY_RESET_MASK;
	delay(10);
	
	spi_send_recv(0x8D);
	spi_send_recv(0x14);
	
	spi_send_recv(0xD9);
	spi_send_recv(0xF1);
	
	DISPLAY_VBATT_PORT &= ~DISPLAY_VBATT_MASK;
	delay(10000000);
	
	spi_send_recv(0xA1);
	spi_send_recv(0xC8);
	
	spi_send_recv(0xDA);
	spi_send_recv(0x20);
	
	spi_send_recv(0xAF);
}

void display_string(int line, char *s) {
	int i;
	if(line < 0 || line >= 4)
		return;
	if(!s)
		return;
	
	for(i = 0; i < 16; i++)
		if(*s) {
			textbuffer[line][i] = *s;
			s++;
		} else
			textbuffer[line][i] = ' ';
}

void display_image(int x, const uint8_t *data) {
	int i, j;
	
	for(i = 0; i < 4; i++) {
		DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;
		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(x & 0xF);
		spi_send_recv(0x10 | ((x >> 4) & 0xF));
		
		DISPLAY_COMMAND_DATA_PORT |= DISPLAY_COMMAND_DATA_MASK;
		
		for(j = 0; j < 32; j++)
			spi_send_recv(~data[i*32 + j]);
	}
}

void display_update() {
	int i, j, k;
	int c;
	for(i = 0; i < 4; i++) {
		DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;
		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(0x0);
		spi_send_recv(0x10);
		
		DISPLAY_COMMAND_DATA_PORT |= DISPLAY_COMMAND_DATA_MASK;
		
		for(j = 0; j < 16; j++) {
		  c = textbuffer[i][j];
		  if(c & 0x80)
		    continue;
		  
		  for(k = 0; k < 8; k++)
		    spi_send_recv(font[c*8 + k]);
		}
	
	}
}


/* Helper to changeOnePixel. This focuses on a section of the picture. 
 * The status should either be 0 or 1.
 */
void helper_ChangeInSection(int x, int y, int status, uint8_t * icon) {
  int pixelPlace = 0;
  int rowCalc, rowRest;
  
  rowCalc = y/8;        /*Which row of hexdec values */
  rowRest = y % 8;      /*Number of pixels still to go down, after moving to correct row */
  pixelPlace += rowCalc * 32; /* Moving to the correct row of array*/
  pixelPlace += x;            /*Moving sideways on the row */
  if(status == 0){
    icon[pixelPlace] &= ~(1UL << rowRest);  /* Clearing the chosen bit */
  }
  if (status == 1) { /*Setting the bit */
    icon[pixelPlace] |= 1UL << rowRest; 
  }
}

/* A function for changing one pixel in the whole picture, by changing the arrays. The grid starts in the upper left corner. */
void changeOnePixel(int x, int y, int status) {
  if(x<0 | y<0 | x>127 | y>31 ){ // Things have to be in screen.
    return;
  }
	int section = x / 32; /* To see which section/icon the pixel is in */
  
	switch(section) {
		case 0 :
		  helper_ChangeInSection(x, y, status, icon1);
			break;
		
	case 1 :
	  helper_ChangeInSection(x-32, y, status, icon4);
	  break;
	  
	case 2 :
	  helper_ChangeInSection(x-64, y, status, icon3);
	  break;
	
	case 3 :
	  helper_ChangeInSection(x-96, y, status, icon2);
	  break;
	  
	}
	
}

// Clears screen from a certain coordinate and its radius.
void removeArea(int xMiddle, int yMiddle, int radius){
  int xCounter;
  int yCounter;
  for(xCounter = 0; xCounter <= (radius*2); xCounter++){
    for(yCounter = 0; yCounter <= (radius*2); yCounter++){
      changeOnePixel((xCounter+xMiddle-radius), (yCounter+yMiddle-radius), 1);
    }
  }
}

void insertArea(int xMiddle, int yMiddle, int radius){
  int xCounter;
  int yCounter;
  for(xCounter = 0; xCounter <= (radius*2); xCounter++){
    for(yCounter = 0; yCounter <= (radius*2); yCounter++){
      changeOnePixel((xCounter+xMiddle-radius), (yCounter+yMiddle-radius), 0);
    }
  }
}

void addMeteorExtras(int xPos, int yPos){
  changeOnePixel(xPos+4, yPos+2, 0); 
  changeOnePixel(xPos+4, yPos+3, 0);
  changeOnePixel(xPos, yPos+4, 0);
  changeOnePixel(xPos-1, yPos+4, 0);
  changeOnePixel(xPos-2, yPos+4, 0);
  changeOnePixel(xPos-4, yPos, 0);
  changeOnePixel(xPos-4, yPos+1, 0);
  changeOnePixel(xPos-3, yPos-4, 0);
  changeOnePixel(xPos-2, yPos-4, 0);
}
  
  
 // Function for making and controlling a meteor. 
 // xMovement is how many steps the meteor should take in x-axis (this is negative if the meteor goes left)
 // yMovement is steps in y-axis. 
 // For meteor to exist put status1 !=0, to remove it put status1=0
 // The meteor has a radius of 3.
void meteor1Movement(int xMovement, int yMovement){
  int xPos = meteor1Info[0];
  int yPos = meteor1Info[1];
  
  if(xMovement != 0 & yMovement == 0){  //Move meteor in x-axis.
    removeArea(xPos, yPos, 4);
    insertArea(xPos + xMovement, yPos ,3);
    addMeteorExtras(xPos + xMovement, yPos);

  }
  if(yMovement != 0 & xMovement == 0){  //Move meteor in y-axis.
    removeArea(xPos, yPos, 4);
    insertArea(xPos, yPos+yMovement, 3);
    addMeteorExtras(xPos + xMovement, yPos);
  }
  if(yMovement != 0 & xMovement != 0){  //Move meteor in y-axis.
    removeArea(xPos, yPos, 4);
    insertArea(xPos+xMovement, yPos+yMovement, 3);
    addMeteorExtras(xPos+xMovement, yPos+yMovement);
  }
  meteor1Info[0] = xPos + xMovement;
  meteor1Info[1] = yPos + yMovement;
}


void meteor2Movement(int xMovement, int yMovement){
  int xPos = meteor2Info[0];
  int yPos = meteor2Info[1];
  
  if(xMovement != 0 & yMovement == 0){  //Move meteor in x-axis.
    removeArea(xPos, yPos, 4);
    insertArea(xPos + xMovement, yPos ,3);
    addMeteorExtras(xPos + xMovement, yPos);
    
  }
  if(yMovement != 0 & xMovement == 0){  //Move meteor in y-axis.
    removeArea(xPos, yPos, 4);
    insertArea(xPos, yPos+yMovement, 3);
    addMeteorExtras(xPos + xMovement, yPos);
  }
  if(yMovement != 0 & xMovement != 0){  //Move meteor in y-axis.
    removeArea(xPos, yPos, 4);
    insertArea(xPos+xMovement, yPos+yMovement, 3);
    addMeteorExtras(xPos+xMovement, yPos+yMovement);
  }
  meteor2Info[0] = xPos + xMovement;
  meteor2Info[1] = yPos + yMovement;
}

void meteor3Movement(int xMovement, int yMovement){
  int xPos = meteor3Info[0];
  int yPos = meteor3Info[1];
  
  if(xMovement != 0 & yMovement == 0){  //Move meteor in x-axis.
    removeArea(xPos, yPos, 4);
    insertArea(xPos + xMovement, yPos ,3);
    addMeteorExtras(xPos + xMovement, yPos);
    
  }
  if(yMovement != 0 & xMovement == 0){  //Move meteor in y-axis.
    removeArea(xPos, yPos, 4);
    insertArea(xPos, yPos+yMovement, 3);
    addMeteorExtras(xPos + xMovement, yPos);
  }
  if(yMovement != 0 & xMovement != 0){  //Move meteor in y-axis.
    removeArea(xPos, yPos, 4);
    insertArea(xPos+xMovement, yPos+yMovement, 3);
    addMeteorExtras(xPos+xMovement, yPos+yMovement);
  }
  meteor3Info[0] = xPos + xMovement;
  meteor3Info[1] = yPos + yMovement;
}

// Moves shot 1.
void shot1Movement(int xMovement, int yMovement){
  int xPos = shot1Info[0];
  int yPos = shot1Info[1];
  if(xMovement != 0 & yMovement == 0){  //Move meteor in x-axis.
    removeArea(xPos, yPos, 1);
    insertArea(xPos + xMovement, yPos ,1);
  }
  if(yMovement != 0 & xMovement == 0){  //Move meteor in y-axis.
    removeArea(xPos, yPos, 1);
    insertArea(xPos, yPos+yMovement, 1);
  }
  if(yMovement != 0 & xMovement != 0){  //Move meteor in y-axis.
    removeArea(xPos, yPos, 1);
    insertArea(xPos+xMovement, yPos+yMovement, 1);
  }
  shot1Info[0] = xPos + xMovement;
  shot1Info[1] = yPos + yMovement;
}

// Moves the ship
void shipMovement(int xMovement, int yMovement){
  int xPos = shipInfo[0];
  int yPos = shipInfo[1];
  if(xMovement != 0 & yMovement == 0){  //Move ship in x-axis.
    removeArea(xPos, yPos, 2);
    removeArea(xPos+2, yPos, 1);
    removeArea(xPos+4, yPos, 0);
    insertArea(xPos+xMovement, yPos ,2);
    insertArea(xPos+xMovement+2, yPos ,1);
    insertArea(xPos+xMovement+4, yPos ,0);
  }
  if(yMovement != 0 & xMovement == 0){  //Move ship in y-axis.
    removeArea(xPos, yPos, 2);
    removeArea(xPos+2, yPos, 1);
    removeArea(xPos+4, yPos, 0);
    insertArea(xPos, yPos+yMovement, 2);
    insertArea(xPos+2, yPos+yMovement, 1);
    insertArea(xPos+4, yPos+yMovement, 0);
  }
  if(yMovement != 0 & xMovement != 0){  //Move ship in y-axis.
    removeArea(xPos, yPos, 2);
    removeArea(xPos+2, yPos, 1);
    removeArea(xPos+4, yPos, 0);
    insertArea(xPos+xMovement, yPos+yMovement, 2);
    insertArea(xPos+xMovement+2, yPos+yMovement, 1);
    insertArea(xPos+xMovement+4, yPos+yMovement, 0);
  }
  shipInfo[0] = xPos + xMovement;
  shipInfo[1] = yPos + yMovement;
}


  // This will instantiate a meteor at the coordinates and give it a movement direction.
  // Function returns 1 if successful, 0 otherwise.
  int instantiateMeteor(int xPos, int yPos, int xMovement, int yMovement){
    if( meteor1Info[2] == 0){  // Meteor is ready to be instantiated, i.e. it is not currently on display.
      meteor1Info[0] = xPos; //x-pos
      meteor1Info[1] = yPos; //y-pos
      meteor1Info[2] = 1;    // Give the meteor a status of existing.
      meteor1Info[3] = xMovement;
      meteor1Info[4] = yMovement;
      return 1;
    }
    if( meteor2Info[2] == 0){
      meteor2Info[0] = xPos; //x-pos
      meteor2Info[1] = yPos; //y-pos
      meteor2Info[2] = 1; 
      meteor2Info[3] = xMovement;
      meteor2Info[4] = yMovement;
      return 1;
    }
    if( meteor3Info[2] == 0){
      meteor3Info[0] = xPos; //x-pos
      meteor3Info[1] = yPos; //y-pos
      meteor3Info[2] = 1; 
      meteor3Info[3] = xMovement;
      meteor3Info[4] = yMovement;
      return 1;
    }
    return 0;
  }

// Function to instantiate shot. Will return 1 if done succesfully.
int instantiateShot(int xPos, int yPos, int xMovement, int yMovement){
  if(shot1Info[2] == 0){
    shot1Info[0] = xPos; //x-pos
    shot1Info[1] = yPos; //y-pos
    shot1Info[2] = 1;    // Give the meteor a status of existing.
    shot1Info[3] = xMovement;
    shot1Info[4] = yMovement;
    return 1;
  }
  return 0;
}

// Function to instantiate ship. Will return 1 if done succesfully.
int instantiateShip(int xPos, int yPos, int xMovement, int yMovement){
  if(shipInfo[2] == 0){
    shipInfo[0] = xPos; //x-pos
    shipInfo[1] = yPos; //y-pos
    shipInfo[2] = 1;    // Give the meteor a status of existing.
    shipInfo[3] = xMovement;
    shipInfo[4] = yMovement;
    return 1;
  }
  return 0;
}


  
// This function moves all objects (meteors, shots & ships) according to their speeds.
void moveObjects(){
  if(meteor1Info[2] != 0){
    int xMovement = meteor1Info[3];
    int yMovement = meteor1Info[4];
    meteor1Movement(xMovement, yMovement);
      }
  if(meteor2Info[2] != 0){
    int xMovement = meteor2Info[3];
    int yMovement = meteor2Info[4];
    meteor2Movement(xMovement, yMovement);
  }
  if(meteor3Info[2] != 0){
    int xMovement = meteor3Info[3];
    int yMovement = meteor3Info[4];
    meteor3Movement(xMovement, yMovement);
  }
  if(shot1Info[2] != 0){
    int xMovement = shot1Info[3];
    int yMovement = shot1Info[4];
    shot1Movement(xMovement, yMovement);
  }
  if(shipInfo[2] != 0){
    int xMovement = shipInfo[3];
    int yMovement = shipInfo[4];
    shipMovement(xMovement, yMovement);
  }
}

float Q_rsqrt( float number ) {  // From Quake III
  long i;
  float x2, y;
  const float threehalfs = 1.5F;
  
  x2 = number * 0.5F;
  y  = number;
  i  = * ( long * ) &y;                       // evil floating point bit level hacking
  i  = 0x5f3759df - ( i >> 1 );               // what is this?
  y  = * ( float * ) &i;
  y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
  return y;
}

// Checks distance between two points using pythagoras.
float distance(int x, int y){
  float toReturn = x*x + y*y;
  toReturn = Q_rsqrt(toReturn);
  return toReturn;
}

// Checks if a meteor has gotten inte the hitbox of the ship.
int shipCollision(){
  int shipXPos, shipYPos, met1XPos, met1YPos, met2XPos;
  shipInfo[0] = shipXPos;

}
  
int main(void) {
	/* Set up peripheral bus clock */
	OSCCON &= ~0x180000;
	OSCCON |= 0x080000;
	
	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;
	
	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;
	
	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);
	
	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	
	/* Clear SPIROV*/
	SPI2STATCLR &= ~0x40;
	/* Set CKP = 1, MSTEN = 1; */
        SPI2CON |= 0x60;
	
	/* Turn on SPI */
	SPI2CONSET = 0x8000;
	
	display_init();
	display_update();
	
int endGame = 0;
int timeCounter = 0;


instantiateMeteor(120, 10, -1,1);
instantiateMeteor(120, 25,-1,-1);
instantiateShot(0,20,3,1);
instantiateShip(0,16, 2, 0);

while(endGame != 1){
	display_image(288, icon4);
	display_image(192, icon3);
	display_image(96, icon2);
	display_image(0, icon1);
	
	int j;
	for(j = 0; j < 100000; j++) { /* Wait */
		int foo;
		foo = j +1;
		}	
	/* x,y, status */
	
	timeCounter++;
	moveObjects();
	
	
	display_image(288, icon4);
	display_image(192, icon3);
	display_image(96, icon2);
	display_image(0, icon1); 
}
	//for(;;) ;
	return 0;
}

