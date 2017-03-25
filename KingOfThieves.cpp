
#include <glut.h>
#include <math.h>
#include <time.h>
#include <string>
#include <stdio.h>
#include <iostream>

void Display(void);
void Anime(void);
void drawText(char*string,int x,int y);
void Counter(std::string string, int x, int y);
void Timer(int value);



std::string result;
int xloc = 0;
int xdir =1;
double xjump = 0;
bool jump = false;
double yloc =0;
double a =1.7;
double b = - 0.0196 * 0.35;
int ynode = 0;
bool doublejump = false;
static int g_counter = 0;
static int j=0;
long long counttime =0;
bool fall = false;
double ynode1 =0;
bool gameover = false;

void Display() {
		glClear(GL_COLOR_BUFFER_BIT );
	if (gameover ==false) {

	glPushMatrix();
	glTranslated(xloc,yloc,0);
	glBegin(GL_TRIANGLES);

	glColor3f(0.4f, 0.5f, 0.7f);
	glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(70.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 70.0f, 0.0f);

	glVertex3f(70.0f, 70.0f, 0.0f);
    glVertex3f(70.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 70.0f, 0.0f);
	glEnd();
	glPopMatrix();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 200.0f, 0.0f);
    glVertex3f(0.0f, 220.0f, 0.0f);
	glVertex3f(800.0f, 200.0f, 0.0f);

	glVertex3f(0.0f, 220.0f, 0.0f);

    glVertex3f(800.0f, 200.0f, 0.0f);
	glVertex3f(800.0f, 220.0f, 0.0f);


	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex3f(20.0f, 250.0f, 0.0f);
    glVertex3f(0.0f, 250.0f, 0.0f);
	glVertex3f(0.0f, 380.0f, 0.0f);

	glVertex3f(0.0f, 380.0f, 0.0f);

    glVertex3f(20.0f, 380.0f, 0.0f);
	glVertex3f(20.0f, 250.0f, 0.0f);
	glEnd();

		glColor3f(0.0f, 0.0f, 0.0f);
	
	Counter(result,850,550);


	
}
	else {
		drawText("The zombies ate your brains!", 420,300);
}
	glFlush();
}

void Counter(std::string string, int x, int y) {
     glRasterPos2d(x, y);
    int len = string.length();
    int i;
    for(i =0;i<len;i++){
       
       glutBitmapCharacter(GLUT_BITMAP_9_BY_15, result[i]);
	 
    }
    glutPostRedisplay();
}


void Timer(int value){
	counttime++;
	glColor3f(0.0f, 0.0f, 0.0f);
	std::string perfect = + " Time: " + std::to_string(counttime) + "s" ;
	result = perfect;
	glutTimerFunc(10*100, Timer, 0);
	 glutPostRedisplay();


}
void keyPressed (unsigned char key, int x, int y) {
	switch (key) {
      case 27:     // ESC key
         exit(0);
         break;
	  case ' ':
		  {
			  if(!jump)
		jump =true;



		if (jump == true && xloc >=900) {
		doublejump =true;
		xjump=0;
		ynode1 = yloc;
		
	}

		  }

	}


} 

void drawText(char*string,int x,int y) 
{ 
 char *c; 
 glPushMatrix(); 
 glTranslatef(x, y,0); 
 glScalef(0.1,0.1,1);


 for (c=string; *c != '\0'; c++) 
 { 
  glutStrokeCharacter(GLUT_STROKE_ROMAN , *c); 
 } 
 glPopMatrix(); 
}


void main(int argc, char** argr) {
	glutInit(&argc, argr);

	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(150, 150);

	glutCreateWindow("King Of Thieves");
	glutDisplayFunc(Display);	
	
	glutIdleFunc(Anime);
	glutKeyboardFunc(keyPressed);
	glutTimerFunc(0, Timer,0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(0.752941f, 0.752941f, 0.752941f, 0.752941f);
	gluOrtho2D(0.0, 1000, 0.0, 600);
    	
	glutMainLoop();
}

void Anime(){
	xloc+=xdir;
	if(xloc>=930 | xloc<=0) {	
		xdir *=-1;
	}
	if (fall == false){
		yloc=ynode;
	}
	if(jump){
	xjump+=1;
	if (doublejump)
		yloc= a * xjump+b*xjump*xjump + ynode1;
	else{
		yloc= a * xjump+b*xjump*xjump + ynode;
	}

	if(yloc <=ynode)
			{
 				jump = false;
				doublejump = false;
				yloc=ynode;
				xjump=0;

			}
	
	} 

	if (yloc>=200 && xloc<800 && doublejump){
				jump = false;
				doublejump = false;
				yloc=220;
				ynode=220;
				xjump=0;
	}
if (xloc > 800 && yloc >=220 && !jump) {
	fall = true;
	yloc= yloc -1;
	ynode=0;
}
if (fall && yloc>0){
	yloc--;
}
if (yloc == 0 && fall == true) {
	fall = false;
}


if (xloc >0 && xloc<20 && yloc >= 250) {
	gameover = true;
}


for(int i = 0; i < 1000000; i++);
	glutPostRedisplay();
}
