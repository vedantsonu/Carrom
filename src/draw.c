double mx,my;
int control = 1;
int playerNo = 0;
double power = 1.0f;

void drawPowerBar()
{
	glColor3f(1.0f/255.0f,108.0f/255.0f,178.0f/255.0f);
	double x = -1.0f + (power/maxPower * 3.5f); 
    glBegin(GL_POLYGON);

glVertex3f(x,-2.55,0);
        glVertex3f(-1,-2.55,0);
        glVertex3f(-1,-2.65,0);
        
        glVertex3f(x,-2.65,0);

    glEnd();
glColor3f(0,0,0);
}

void RenderString(double x, double y, void *font, const char* string, RGB rgb)
{  
  char *c;

  glColor3f(rgb.r, rgb.g, rgb.b); 
  glRasterPos2f(x, y);

  glutBitmapString(font, (const unsigned char*)string);
}

void drawArrow(double length,double X, double Y, double dirX, double dirY)
{
	glDepthRange(0.3,0.4);
	double mag = sqrt(dirX * dirX + dirY * dirY);
	dirX = dirX / mag;
	dirY = dirY / mag;

	double fX,fY;
	fX = X + dirX * length;
	fY = Y + dirY * length;
	glLineWidth(2.0f);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(2, 0x0C0F);
    	glBegin(GL_LINES);
	
        glVertex3f(fX,fY,0);
        glVertex3f(X,Y,0);
	glEnd();
glDisable(GL_LINE_STIPPLE);
    glEnable(GL_LINE_SMOOTH);
}



void display(void)
{
double incAngle;
double tRadius = 0.2f;
double tempPar = 2.2f;

double tempPar2;
double xtemp;

xtemp = magnitude(1.2f,1.2f) + tRadius;
tempPar2 = magnitude(tempPar,tempPar);
incAngle = 1.0f/180.0f * PI;
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();

glPushMatrix();
    glRotatef((playerNo * 90), 0 , 0 , 1.0);
if(playerNo == 0){    
	glTranslatef(0,0.1,-6);
}else if(playerNo ==  1){
	glTranslatef(0.1,0,-6);
}else if(playerNo == 2){
glTranslatef(0,-0.1,-6);
}else{
glTranslatef(-0.1,0,-6);
}
	


    glDepthRange (0.8, 1.0);
    glColor3f(0.984375f,0.89453125f,0.73046875f);

// Main Board
    glBegin(GL_POLYGON);

        glVertex3f(2.5,2.5,0);
        glVertex3f(-2.5,2.5,0);
        glVertex3f(-2.5,-2.5,0);
        glVertex3f(2.5,-2.5,0);

    glEnd();

    glDepthRange (0.5, 0.8);

    glColor3f(0,0,0);

// Carrom lines

	glLineWidth(4.0f);
    glBegin(GL_LINES);

	
        glVertex3f(1.9,2.19,0);
        glVertex3f(-1.9,2.19,0);

        glVertex3f(1.9,-2.19,0);
        glVertex3f(-1.9,-2.19,0);

        glVertex3f(-2.19,1.9,0);
        glVertex3f(-2.19,-1.9,0);

        glVertex3f(2.19,1.9,0);
        glVertex3f(2.19,-1.9,0);
              
    glEnd();

	
	glLineWidth(1.5f);
    glBegin(GL_LINES);
	
        glVertex3f(1.9,2.02,0);
        glVertex3f(-1.9,2.02,0);

        glVertex3f(1.9,-2.02,0);
        glVertex3f(-1.9,-2.02,0);

        glVertex3f(-2.02,1.9,0);
        glVertex3f(-2.02,-1.9,0);

        glVertex3f(2.02,1.9,0);
        glVertex3f(2.02,-1.9,0);
              
    glEnd();
	
// Holes ...
static double angle = 0;
    	glBegin(GL_TRIANGLE_FAN);
 	 glVertex2f(2.3933,2.3933);
	 for( angle = 0 ; angle <= 2 * PI + 5*incAngle ; angle=angle + 5 * incAngle ){
	 glVertex2f(2.3933 + sin(angle) * 0.107, 2.3933 + cos(angle) * 0.107);
 	 }
 	 glEnd();

 	 glBegin(GL_TRIANGLE_FAN);
 	 glVertex2f(-2.3933,2.3933);
	 for( angle = 0 ; angle <= 2 * PI + 5*incAngle ; angle=angle + 5 * incAngle ){
	 glVertex2f(-2.3933 + sin(angle) * 0.107, 2.3933+ cos(angle) * 0.107);
 	 }
 	 glEnd();

 	 glBegin(GL_TRIANGLE_FAN);
 	 glVertex2f(-2.3933,-2.3933);
	 for( angle = 0 ; angle <= 2 * PI + 5*incAngle ; angle=angle + 5 * incAngle ){
	 glVertex2f(-2.3933 + sin(angle) * 0.107 , -2.3933 + cos(angle) * 0.107);
 	 }
 	 glEnd();

 	 glBegin(GL_TRIANGLE_FAN);
 	 glVertex2f(2.3933,-2.3933);
	 for( angle = 0 ; angle <= 2 * PI + 5*incAngle ; angle=angle + 5 * incAngle ){
	 glVertex2f(2.3933 + sin(angle) * 0.107, -2.3933 + cos(angle) * 0.107);
 	 }
 	 glEnd();

// Striker
	glDepthRange(0.0f,0.1f);
	glColor3f(1.0f/255.0f,108.0f/255.0f,178.0f/255.0f);
	if(striker.visible == 1)
{
    	glBegin(GL_TRIANGLE_FAN);
 	 glVertex2f(striker.X,striker.Y);
 for( angle = 0 ; angle <= 2 * PI + incAngle ; angle=angle + incAngle ){
	 glVertex2f(striker.X + sin(angle) * striker.radius, striker.Y + cos(angle) * striker.radius);
 	 }
 	 glEnd();
}
// Carrom Coins
	glColor3f(216.0f/255.0f,145.0f/255.0f,65.0f/255.0f); 
int t=0;
for(t=0;t < 2; t++){
if(coin[t].visible == 1){
	 glBegin(GL_TRIANGLE_FAN);
	glVertex2f(coin[t].X,coin[t].Y);
 for( angle = 0 ; angle <= 2 * PI + incAngle ; angle=angle + incAngle ){
	 glVertex2f(coin[t].X + sin(angle) * coin[t].radius, coin[t].Y + cos(angle) * coin[t].radius);
 	 }
 	 glEnd();	 
}
}
glColor3f(147.0f/255.0f,1.0/255.0f,138.0f/255.0f); 
if(coin[t].visible == 1){
	 glBegin(GL_TRIANGLE_FAN);
	glVertex2f(coin[t].X,coin[t].Y);
 for( angle = 0 ; angle <= 2 * PI + incAngle ; angle=angle + incAngle ){
	 glVertex2f(coin[t].X + sin(angle) * coin[t].radius, coin[t].Y + cos(angle) * coin[t].radius);
 	 }
 	 glEnd();	 
}
glColor3f(0,0,0); 
for(t=2;t < totalCoins; t++){
if(coin[t].visible == 1){
	 glBegin(GL_TRIANGLE_FAN);
	glVertex2f(coin[t].X,coin[t].Y);
 for( angle = 0 ; angle <= 2 * PI + incAngle ; angle=angle + incAngle ){
	 glVertex2f(coin[t].X + sin(angle) * coin[t].radius, coin[t].Y + cos(angle) * coin[t].radius);
 	 }
 	 glEnd();	 
}
}

// Carrom Centre circles
	 glDepthRange(0.4f,0.5f);
	 glColor3f(0.811764706f,0.168627451f,0.062745098f);
	 glLineWidth(0.1f);
 	 glBegin(GL_LINES);
 	 //glVertex2f(0,0)
	 for( angle = 0 ; angle < 360 ; angle=angle + 1 ){
	 glVertex2f(0 + sin(angle) * 0.6, 0 + cos(angle) * 0.6);
 	 }
 	 glEnd();

 	 glBegin(GL_TRIANGLE_FAN);
 	 glVertex2f(0,0);
	 for( angle = 0 ; angle < 360 ; angle=angle + 1 ){
	 glVertex2f(0 + sin(angle) * 0.1, 0 + cos(angle) * 0.1);
 	 }
 	 glEnd();

// Carrom lines(orange circles)
    	 glBegin(GL_TRIANGLE_FAN);
 	 glVertex2f(-1.91,-2.1);
	 for( angle = 0 ; angle <= 2 * PI + 5*incAngle ; angle=angle + 5 * incAngle ){
	 glVertex2f(-1.91 + sin(angle) * 0.07, -2.1 + cos(angle) * 0.07);
 	 }
 	 glEnd();
		
	 glBegin(GL_TRIANGLE_FAN);
 	 glVertex2f(1.91,-2.1);
	 for( angle = 0 ; angle <= 2 * PI + 5*incAngle ; angle=angle + 5 * incAngle ){
	 glVertex2f(1.91 + sin(angle) * 0.07, -2.1 + cos(angle) * 0.07);
 	 }
 	 glEnd();

	 glBegin(GL_TRIANGLE_FAN);
 	 glVertex2f(-1.91,2.1);
	 for( angle = 0 ; angle <= 2 * PI + 5*incAngle ; angle=angle + 5 * incAngle ){
	 glVertex2f(-1.91 + sin(angle) * 0.07, 2.1 + cos(angle) * 0.07);
 	 }
 	 glEnd();

	 glBegin(GL_TRIANGLE_FAN);
 	 glVertex2f(1.91,2.1);
	 for( angle = 0 ; angle <= 2 * PI + 5*incAngle ; angle=angle + 5 * incAngle ){
	 glVertex2f(1.91 + sin(angle) * 0.07, 2.1 + cos(angle) * 0.07);
 	 }
 	 glEnd();
	
  	 glBegin(GL_TRIANGLE_FAN);
 	 glVertex2f(-2.1,-1.91);
	 for( angle = 0 ; angle <= 2 * PI + 5*incAngle ; angle=angle + 5 * incAngle ){
	 glVertex2f(-2.1  + sin(angle) * 0.07, -1.91 + cos(angle) * 0.07);
 	 }
 	 glEnd();

  	 glBegin(GL_TRIANGLE_FAN);
 	 glVertex2f(-2.1,1.91);
	 for( angle = 0 ; angle <= 2 * PI + 5*incAngle ; angle=angle + 5 * incAngle ){
	 glVertex2f(-2.1  + sin(angle) * 0.07, 1.91 + cos(angle) * 0.07);
 	 }
 	 glEnd();
  	 
	 glBegin(GL_TRIANGLE_FAN);
 	 glVertex2f(2.1,1.91);
	 for( angle = 0 ; angle <= 2 * PI + 5*incAngle ; angle=angle + 5 * incAngle ){
	 glVertex2f(2.1  + sin(angle) * 0.07, 1.91 + cos(angle) * 0.07);
 	 }
 	 glEnd();
  	 
	 glBegin(GL_TRIANGLE_FAN);
 	 glVertex2f(2.1,-1.91);
	 for( angle = 0 ; angle <= 2 * PI + 5*incAngle ; angle=angle + 5 * incAngle ){
	 glVertex2f(2.1  + sin(angle) * 0.07, -1.91 + cos(angle) * 0.07);
 	 }
 	 glEnd();

// Carrom centre triangles
 	 glBegin(GL_TRIANGLES);
 	 glVertex2f(-0.05f,0.11f);
	 glVertex2f(0.05f,0.11f);
	 glVertex2f(0.0f,0.6f); 

         glVertex2f(-0.05f,-0.11f);
	 glVertex2f(0.05f,-0.11f);
	 glVertex2f(0.0f,-0.6f);

	 glVertex2f(0.11f,-0.05f);
	 glVertex2f(0.11f,0.05f);
	 glVertex2f(0.6f,0.0f); 
 
	 glVertex2f(-0.11f,-0.05f);
	 glVertex2f(-0.11f,0.05f);
	 glVertex2f(-0.6f,0.0f); 
	 glEnd();

// Carrom line circles (outer periphery encircling red circles)
	 glColor3f(0,0,0);
	 glLineWidth(1.6f);
    	 glBegin(GL_LINE_STRIP);
 	 glVertex2f(-1.91,-2.1);
	 for( angle = 0 ; angle <= 2 * PI  ; angle=angle + 5 * incAngle ){
	 glVertex2f(-1.91 + sin(angle) * 0.09, -2.1 + cos(angle) * 0.09);
 	 }
 	 glEnd();

	 glBegin(GL_LINE_STRIP);
 	 glVertex2f(1.91,-2.1);
	 for( angle = 0 ; angle <= 2 * PI  ; angle=angle + 5 * incAngle ){
	 glVertex2f(1.91 + sin(angle) * 0.09, -2.1 + cos(angle) * 0.09);
 	 }
 	 glEnd();

	 glBegin(GL_LINE_STRIP);
 	 glVertex2f(-1.91,2.1);
	 for( angle = 0 ; angle <= 2 * PI  ; angle=angle + 5 * incAngle ){
	 glVertex2f(-1.91 + sin(angle) * 0.09, 2.1 + cos(angle) * 0.09);
 	 }
 	 glEnd();

    	 glBegin(GL_LINE_STRIP);
 	 glVertex2f(1.91,2.1);
	 for( angle = 0 ; angle <= 2 * PI  ; angle=angle + 5 * incAngle ){
	 glVertex2f(1.91 + sin(angle) * 0.09, 2.1 + cos(angle) * 0.09);
 	 }
 	 glEnd();

    	 glBegin(GL_LINE_STRIP);
 	 glVertex2f(2.1,1.91);
	 for( angle = 0 ; angle <= 2 * PI  ; angle=angle + 5 * incAngle ){
	 glVertex2f(2.1 + sin(angle) * 0.09, 1.91 + cos(angle) * 0.09);
 	 }
 	 glEnd();
	 
	 glBegin(GL_LINE_STRIP);
 	 glVertex2f(-2.1,1.91);
	 for( angle = 0 ; angle <= 2 * PI  ; angle=angle + 5 * incAngle ){
	 glVertex2f(-2.1 + sin(angle) * 0.09, 1.91 + cos(angle) * 0.09);
 	 }
 	 glEnd();

    	 glBegin(GL_LINE_STRIP);
 	 glVertex2f(2.1,-1.91);
	 for( angle = 0 ; angle <= 2 * PI  ; angle=angle + 5 * incAngle ){
	 glVertex2f(2.1 + sin(angle) * 0.09, -1.91 + cos(angle) * 0.09);
 	 }
 	 glEnd();

    	 glBegin(GL_LINE_STRIP);
 	 glVertex2f(-2.1,-1.91);
	 for( angle = 0 ; angle <= 2 * PI  ; angle=angle + 5 * incAngle ){
	 glVertex2f(-2.1 + sin(angle) * 0.09, -1.91 + cos(angle) * 0.09);
 	 }
 	 glEnd();	

 // Tangential circles
    	 glBegin(GL_LINE_STRIP);
	 for( angle = 0 ; angle <= 2 * PI  ; angle=angle + 5 * incAngle ){
	 glVertex2f(-2.005 + sin(angle) * 0.045, -2.005 + cos(angle) * 0.045);
 	 }
 	 glEnd();
	
	    	 glBegin(GL_LINE_STRIP);
	 for( angle = 0 ; angle <= 2 * PI  ; angle=angle + 5 * incAngle ){
	 glVertex2f(2.005 + sin(angle) * 0.045, -2.005 + cos(angle) * 0.045);
 	 }
 	 glEnd();

    	 glBegin(GL_LINE_STRIP);
	 for( angle = 0 ; angle <= 2 * PI  ; angle=angle + 5 * incAngle ){
	 glVertex2f(-2.005 + sin(angle) * 0.045, 2.005 + cos(angle) * 0.045);
 	 }
 	 glEnd();

    	 glBegin(GL_LINE_STRIP);
	 for( angle = 0 ; angle <= 2 * PI  ; angle=angle + 5 * incAngle ){
	 glVertex2f(2.005 + sin(angle) * 0.045, 2.005 + cos(angle) * 0.045);
 	 }
 	 glEnd();
	glPushMatrix();
	glRotatef(45.0f,0,0,1.0f);
 	 glBegin(GL_TRIANGLES);
 	 glVertex2f(-0.05f,0.11f);
	 glVertex2f(0.05f,0.11f);
	 glVertex2f(0.0f,0.6f); 

         glVertex2f(-0.05f,-0.11f);
	 glVertex2f(0.05f,-0.11f);
	 glVertex2f(0.0f,-0.6f);

	 glVertex2f(0.11f,-0.05f);
	 glVertex2f(0.11f,0.05f);
	 glVertex2f(0.6f,0.0f); 
 
	 glVertex2f(-0.11f,-0.05f);
	 glVertex2f(-0.11f,0.05f);
	 glVertex2f(-0.6f,0.0f); 
	 glEnd();
	glPopMatrix();
	 

	 glLineWidth(2.0f);
         glBegin(GL_LINES);
	 glVertex2f(-tempPar,-tempPar);
	 glVertex2f(-1.2f,-1.2f);

	 glVertex2f(-tempPar,tempPar);
	 glVertex2f(-1.2f,1.2f);
		
	 glVertex2f(tempPar,-tempPar);
	 glVertex2f(1.2f,-1.2f);
	 
	 glVertex2f(tempPar,tempPar);
	 glVertex2f(1.2f,1.2f);

	 glEnd();


	 glPushMatrix();
	 glRotatef(45.0f,0,0,1);
	 glBegin(GL_TRIANGLES);
	 glVertex2f(0.0f,-tempPar2 - 0.07f);
	 glVertex2f(0.03f,-tempPar2);
	 glVertex2f(-0.03f,-tempPar2);
	   
         glVertex2f(0.0f,tempPar2 + 0.07f);
	 glVertex2f(0.03f,tempPar2-0.001f);
	 glVertex2f(-0.03f,tempPar2-0.001f);
	 glEnd();
	 glRotatef(-90.0f,0,0,1);	 
	glBegin(GL_TRIANGLES);
	 glVertex2f(0.0f,-tempPar2 - 0.07f);
	 glVertex2f(0.03f,-tempPar2);
	 glVertex2f(-0.03f,-tempPar2);
	   
         glVertex2f(0.0f,tempPar2 + 0.07f);
	 glVertex2f(0.03f,tempPar2-0.001f);
	 glVertex2f(-0.03f,tempPar2-0.001f);
	 glEnd();
	 glPopMatrix();

	 glLineWidth(1.5f);

glPushMatrix(); 
	 glRotatef(45,0,0,1);
	 glBegin(GL_LINE_STRIP);
	 for( angle = 50 ; angle <= 310 ; angle=angle + 1 ){
	 glVertex2f(xtemp+ cos(angle/180.0f * PI ) * tRadius,  sin(angle/180.0f * PI) * tRadius);
 	 }
         glEnd();

	 glBegin(GL_TRIANGLES);

	 glVertex2f(xtemp +  (tRadius) * cos(25/180.0f * PI) , (tRadius) * sin(25/180.0f * PI) );	 
         glVertex2f(xtemp +  (tRadius+0.03f) * cos(50/180.0f * PI) , (tRadius+0.03f) * sin(50/180.0f * PI) );
	 glVertex2f(xtemp +  (tRadius-0.03f) * cos(50/180.0f * PI) , (tRadius-0.03f) * sin(50/180.0f * PI) );

         glVertex2f(xtemp +  (tRadius) * cos(335/180.0f * PI) , (tRadius) * sin(335/180.0f * PI) );	 
         glVertex2f(xtemp +  (tRadius+0.03f) * cos(310/180.0f * PI) , (tRadius+0.03f) * sin(310/180.0f * PI) );
	 glVertex2f(xtemp +  (tRadius-0.03f) * cos(310/180.0f * PI) , (tRadius-0.03f) * sin(310/180.0f * PI) );

	 glEnd();

		 glRotatef(90,0,0,1);
	 glBegin(GL_LINE_STRIP);
	 for( angle = 50 ; angle <= 310 ; angle=angle + 1 ){
	 glVertex2f(xtemp+ cos(angle/180.0f * PI ) * tRadius,  sin(angle/180.0f * PI) * tRadius);
 	 }
         glEnd();

	 glBegin(GL_TRIANGLES);

	 glVertex2f(xtemp +  (tRadius) * cos(25/180.0f * PI) , (tRadius) * sin(25/180.0f * PI) );	 
         glVertex2f(xtemp +  (tRadius+0.03f) * cos(50/180.0f * PI) , (tRadius+0.03f) * sin(50/180.0f * PI) );
	 glVertex2f(xtemp +  (tRadius-0.03f) * cos(50/180.0f * PI) , (tRadius-0.03f) * sin(50/180.0f * PI) );

         glVertex2f(xtemp +  (tRadius) * cos(335/180.0f * PI) , (tRadius) * sin(335/180.0f * PI) );	 
         glVertex2f(xtemp +  (tRadius+0.03f) * cos(310/180.0f * PI) , (tRadius+0.03f) * sin(310/180.0f * PI) );
	 glVertex2f(xtemp +  (tRadius-0.03f) * cos(310/180.0f * PI) , (tRadius-0.03f) * sin(310/180.0f * PI) );

	 glEnd();

		 glRotatef(90,0,0,1);
	 glBegin(GL_LINE_STRIP);
	 for( angle = 50 ; angle <= 310 ; angle=angle + 1 ){
	 glVertex2f(xtemp+ cos(angle/180.0f * PI ) * tRadius,  sin(angle/180.0f * PI) * tRadius);
 	 }
         glEnd();

	 glBegin(GL_TRIANGLES);

	 glVertex2f(xtemp +  (tRadius) * cos(25/180.0f * PI) , (tRadius) * sin(25/180.0f * PI) );	 
         glVertex2f(xtemp +  (tRadius+0.03f) * cos(50/180.0f * PI) , (tRadius+0.03f) * sin(50/180.0f * PI) );
	 glVertex2f(xtemp +  (tRadius-0.03f) * cos(50/180.0f * PI) , (tRadius-0.03f) * sin(50/180.0f * PI) );

         glVertex2f(xtemp +  (tRadius) * cos(335/180.0f * PI) , (tRadius) * sin(335/180.0f * PI) );	 
         glVertex2f(xtemp +  (tRadius+0.03f) * cos(310/180.0f * PI) , (tRadius+0.03f) * sin(310/180.0f * PI) );
	 glVertex2f(xtemp +  (tRadius-0.03f) * cos(310/180.0f * PI) , (tRadius-0.03f) * sin(310/180.0f * PI) );

	 glEnd();

		 glRotatef(90,0,0,1);
	 glBegin(GL_LINE_STRIP);
	 for( angle = 50 ; angle <= 310 ; angle=angle + 1 ){
	 glVertex2f(xtemp+ cos(angle/180.0f * PI ) * tRadius,  sin(angle/180.0f * PI) * tRadius);
 	 }
         glEnd();

	 glBegin(GL_TRIANGLES);

	 glVertex2f(xtemp +  (tRadius) * cos(25/180.0f * PI) , (tRadius) * sin(25/180.0f * PI) );	 
         glVertex2f(xtemp +  (tRadius+0.03f) * cos(50/180.0f * PI) , (tRadius+0.03f) * sin(50/180.0f * PI) );
	 glVertex2f(xtemp +  (tRadius-0.03f) * cos(50/180.0f * PI) , (tRadius-0.03f) * sin(50/180.0f * PI) );

         glVertex2f(xtemp +  (tRadius) * cos(335/180.0f * PI) , (tRadius) * sin(335/180.0f * PI) );	 
         glVertex2f(xtemp +  (tRadius+0.03f) * cos(310/180.0f * PI) , (tRadius+0.03f) * sin(310/180.0f * PI) );
	 glVertex2f(xtemp +  (tRadius-0.03f) * cos(310/180.0f * PI) , (tRadius-0.03f) * sin(310/180.0f * PI) );

	 glEnd();
glPopMatrix();	
	 
	
	 
	if(control == 1 ){
	double dX = (((mx-(width/2.0f)) * 2.5f) / (width/2.0f));
	double dY = (-((my-(height/2.0f)) * 2.5f) / (height/2.0f) );
	double temp = dX;
	if(playerNo == 1)
	{
	dX = dY;
	dY = -temp;
	}else if(playerNo == 2)
	{
	dX = -dX;
	dY = -dY;
	}else if(playerNo == 3)
	{
	dX = -dY;
	dY = temp;
	}
	drawArrow(2.9f,striker.X,striker.Y, dX -striker.X , dY -  striker.Y);
	}
glPopMatrix();
    glTranslatef(0,0.1,-6);
    glDepthRange (0.8, 1.0);
	drawPowerBar();
 RGB col;
col.r = 1.0f;
col.g = 1.0f;
col.b = 1.0f;
char pr[100];
sprintf(pr,"Power ");
RenderString(-2.6f, -2.69f, GLUT_BITMAP_TIMES_ROMAN_24, pr,col);

    glutSwapBuffers();



}
