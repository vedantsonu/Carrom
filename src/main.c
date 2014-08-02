#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <pthread.h>
#include <GL/glui.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "defines.h"
#include "structs.h"
#include "Vector2D.h"
#include "physics.c"
#include "AI.c"
#include "draw.c"

//<glui parameters>
int obj=0;
int level=0;
int pnum=0;
int players=0;
char host[20]="";
GLUI *glui;


    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;


 int newsockfd[3];
     socklen_t clilen;
     char obuffer[1024],ibuffer[1024];
     struct sockaddr_in cli_addr;




void resetScores()
{
int i =0;
for(i = 0; i< totalPlayers; i++)
{
pScores[i] = 0;
}
}

void updateScores()
{
int i=0;
int j=0;
int prevScore = 0;
for(i = 0; i< totalPlayers; i++)
{
prevScore = pScores[i];
pScores[i] =0 ;
for(j = 0; j< totalCoins; j++)
{
pScores[i] += coin[j].SCORE * coinOwners[i][j];
}
if((pCounter == i) && f_strikerPocketed == 1 && prevScore <= 0 && pScores[i] == 0)
{
pScores[i] = prevScore - 10;
}
}
}

void initializeCoin(COIN *c,double x,double y, double m, double r, int h,double vx,double vy,int score)
{
c->X = x;
c->Y = y;
c->mass = m;
c->radius = r;
c->visible = h;
c->vX = vx;
c->vY = vy;
c->SCORE = score;
}

//<glui functions>

void start_game(int ID){
glui->close();
}

void start_game_client(int ID){
glui->close();
isServer=0;
char name[20]="";
     strcpy(name, host);
     char pno[10];

    portno = pnum;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

  int y=fcntl(sockfd,F_GETFL,0);             
  fcntl(sockfd,F_SETFL,y | O_NONBLOCK);   
    server = gethostbyname(name);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr, 
         server->h_length);
    serv_addr.sin_port = htons(portno);
    connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)); 

bzero(ibuffer,1024);
     //while(q < 0)
int q = -1;
while (q < 0){     
q = read(sockfd,ibuffer,1023);
     
if(q >= 0 ){
sscanf(ibuffer,"%d %d\n",&playerNo,&totalPlayers);
printf("I am player no. %d\n",playerNo);
}
}
        //error("ERROR connecting");
//playerNo = 1;
control = 0;
printf("setup done\n");
   
}

void start_game_server(int ID){
glui->close();
totalPlayers=players;
isServer = 1;
     char pno[10];
    // printf("Enter port no. : ");
     //scanf("%s",pno);
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) ;
       // error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     //portno = atoi("7770");
     portno = pnum;
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) ;
              //error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);

int i = 0;
for(i=0; i < totalPlayers-1 ; i++){     
newsockfd[i] = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);

     if (newsockfd[i] < 0) ;
          //error("ERROR on accept");

bzero(obuffer,1024);
sprintf(obuffer,"%d %d\n",i+1,totalPlayers);
write(newsockfd[i],obuffer,strlen(obuffer));
int x1=fcntl(newsockfd[i],F_GETFL,0);              // Get socket flags
fcntl(newsockfd[i],F_SETFL,x1 | O_NONBLOCK);   // Add non-blocking flag
}
playerNo = 0;
control =1;
    


}

void callback_level_single_player(int ID){
glui->close();
glui= GLUI_Master.create_glui("Carrom Game", 0 );
GLUI_Rollout *rollout=glui->add_rollout( "Help", 0 );
glui->add_statictext_to_panel( rollout,"Create Server" ); 
glui->add_button( "Start",-1,start_game);
if(level==0){AI_level=1;}
if(level==1){AI_level=2;}
if(level==2){AI_level=3;}
}

void callback_level_multi_player(int ID){
glui->close();
glui= GLUI_Master.create_glui("Carrom Game", 0 );

if(ID==1){	//creates server
GLUI_EditText *text_input=glui->add_edittext( "Port Number",GLUI_EDITTEXT_INT,&pnum,-1);
GLUI_EditText *text_input_1=glui->add_edittext( "Number of Players",GLUI_EDITTEXT_INT,&players,-1);
GLUI_Panel *obj_panel_1 = glui->add_panel("Play as BOT" );                                      
GLUI_RadioGroup *group2 =glui->add_radiogroup_to_panel(obj_panel_1,&bot,3); 
glui->add_radiobutton_to_group( group2, "BOT" );
glui->add_radiobutton_to_group( group2, "Not a BOT" );
glui->add_button( "Create",-1,start_game_server);

}
else		//joins server
{
//GLUI_Listbox *list_servers=glui->add_listbox("Select",&pnum,-1);

GLUI_EditText *text_input=glui->add_edittext( "Host",GLUI_EDITTEXT_TEXT,host,-1);
GLUI_EditText *text_input_1=glui->add_edittext( "Port Number",GLUI_EDITTEXT_INT,&pnum,-1);
glui->add_button( "Join",-1,start_game_client);
}
}

void callback_game_type(int ID){
glui->close();
glui= GLUI_Master.create_glui("Carrom Game", 0 );
if(obj==0){
singlePlayerMode=1;
if(singlePlayerMode == 1)
{
playerNo = 1; 
totalPlayers = 2;
pCounter = 1;
control =1;
initializeCoin(&striker,-2.1,0,0.04f,0.1064f,1,0,0,-10);
}
glui->add_statictext( "Select Level");
GLUI_Panel *obj_panel = glui->add_panel("Level" );                                    
GLUI_RadioGroup *group1 =glui->add_radiogroup_to_panel(obj_panel,&level,3); 
glui->add_radiobutton_to_group( group1, "Ameteur" );
glui->add_radiobutton_to_group( group1, "Intermediate" );
glui->add_radiobutton_to_group( group1, "Expert" );
glui->add_button_to_panel( obj_panel,"select",-1,callback_level_single_player);
}
else{
GLUI_Panel *obj_panel = glui->add_panel("Create" );
glui->add_statictext_to_panel( obj_panel,"Create Server" ); 
glui->add_separator();  
glui->add_button( "Create",1,callback_level_multi_player);
glui->add_column(true);
GLUI_Panel *obj_panel_1 = glui->add_panel("Server" );
glui->add_statictext_to_panel(obj_panel_1,"Join Server" ); 
glui->add_separator(); 
glui->add_button( "Join",2,callback_level_multi_player);
}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void tryToPlaceAtCenter(COIN *c)
{
c->visible = 1;
c->X = 0;
c->Y = 0;
c->vX = 0;
c->vY = 0;
}

void init(void)
{

    glClearColor (0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_LINE_SMOOTH);

}






void reshape (int w, int h)

{

    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
glFrustum(-2.2, 2.2, -2.2, 2.2, 5, 100);
    glMatrixMode (GL_MODELVIEW);

}

void keyboard(unsigned char key, int x, int y)
{

    switch (key) {

        case 27: // ESC key

            exit(0);
            break;

	case '.':
		if(control == 1){
		power += 0.05f;
		if(power > maxPower)
		{power = maxPower;		
		}		
		}
		break;

	case ',':
		if(control == 1){
		power -= 0.05f;
		if(power < 0.1f)
		{
		power = 0.1f;
		}
		}
		break;


    }

}
void setupStriker(int pNo)
{

}

void mouse(int button, int state, int x, int y)
{

if(((button & GLUT_RIGHT_BUTTON) == GLUT_RIGHT_BUTTON) && control == 1)
{

invalidPosition = 0;
int i =0;
double sep = 0;
for (i = 0; i < totalCoins ; i++){
sep = magnitude(striker.X - coin[i].X, striker.Y - coin[i].Y);
if((sep < striker.radius + coin[i].radius) && coin[i].visible == 1 && striker.visible == 1)
{
invalidPosition = 1;
}
}
if(invalidPosition == 0){
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
double dirx =dX -striker.X ;
double diry = dY -striker.Y ;
double mag = magnitude(dirx,diry);
dirx = dirx / mag;
diry = diry / mag;
double tvX,tvY;
tvX= dirx * power;
tvY = diry * power;

if(pCounter == 0 && singlePlayerMode == 1){
AI(&striker.X,&striker.Y,&tvX,&tvY);
}

if(playerNo ==0 && bot==0 && pCounter==0)
{
AI(&striker.X,&striker.Y,&tvX,&tvY);
}
striker.vX = tvX;
striker.vY = tvY;
control = 0;

if(singlePlayerMode == 0){
if(isServer == 0){
bzero(obuffer,1024);
sprintf(obuffer,"%.45f %.45f %.45f %.45f\n",striker.X,striker.Y,tvX,tvY);
sscanf(obuffer,"%lf %lf %lf %lf\n",&striker.X,&striker.Y,&striker.vX,&striker.vY);
write(sockfd,obuffer,strlen(obuffer));
}
else
{
bzero(obuffer,1024);
sprintf(obuffer,"%.45f %.45f %.45f %.45f\n",striker.X,striker.Y,tvX,tvY);
sscanf(obuffer,"%lf %lf %lf %lf\n",&striker.X,&striker.Y,&striker.vX,&striker.vY);
		int i = 0;
		while(i < totalPlayers-1)
		{
				bzero(obuffer,1024);
				sprintf(obuffer,"%.45f %.45f %.45f %.45f\n",striker.X,striker.Y,striker.vX,striker.vY);
				write(newsockfd[i],obuffer,strlen(obuffer));
			i++;
		}

}
}
initialised = 0;
}
}

}

void pressedMotion(int x, int y)
{

mx = x;
my = y;

if(control == 1)
{

if(playerNo == 0){
striker.X = ((x-(width/2.0f)) * 2.5f) / (width/2.0f) ;

if(striker.X < -1.91)
{
striker.X = -1.91;
}else if(striker.X > 1.91){
striker.X = 1.91f;
}
if(singlePlayerMode == 0){
bzero(obuffer,1024);
sprintf(obuffer,"%.45f %.45f %c",striker.X,striker.Y,'d');

		int i = 0;
		while(i < totalPlayers-1)
		{
				bzero(obuffer,1024);
				sprintf(obuffer,"%.45f %.45f %c",striker.X,striker.Y,'d');
				write(newsockfd[i],obuffer,strlen(obuffer));
			i++;
		}
}

}

if(playerNo == 1)
{
striker.Y = -((x-(width/2.0f)) * 2.5f) / (width/2.0f) ;

if(striker.Y < -1.91)
{
striker.Y = -1.91;
}else if(striker.Y > 1.91){
striker.Y = 1.91f;
}
if(singlePlayerMode == 0){
bzero(obuffer,1024);
sprintf(obuffer,"%.45f %.45f %c",striker.X,striker.Y,'d');
write(sockfd,obuffer,strlen(obuffer));
}
}


if(playerNo == 2){
striker.X = -((x-(width/2.0f)) * 2.5f) / (width/2.0f) ;

if(striker.X < -1.91)
{
striker.X = -1.91;
}else if(striker.X > 1.91){
striker.X = 1.91f;
}
if(singlePlayerMode == 0){
bzero(obuffer,1024);
sprintf(obuffer,"%.45f %.45f %c",striker.X,striker.Y,'d');
write(sockfd,obuffer,strlen(obuffer));
}
}

if(playerNo == 3)
{
striker.Y = ((x-(width/2.0f)) * 2.5f) / (width/2.0f) ;

if(striker.Y < -1.91)
{
striker.Y = -1.91;
}else if(striker.Y > 1.91){
striker.Y = 1.91f;
}
if(singlePlayerMode == 0){
bzero(obuffer,1024);
sprintf(obuffer,"%.45f %.45f %c",striker.X,striker.Y,'d');
write(sockfd,obuffer,strlen(obuffer));
}
}

}

}


void passiveMotion(int x, int y)
{
mx = x;
my = y;
}







void* threadPhysics(void *s)
{

int te = 0;
simulatePhysicsAdvanced();
int a=0;
double mag,rX,rY,newVx,newVy;
if((striker.X < -2.5f+striker.radius+epsilon) && striker.vX < 0){striker.vX = -striker.vX * restitution; }
if((striker.X > 2.5f-striker.radius-epsilon) && striker.vX > 0) {striker.vX = -striker.vX * restitution; }
if((striker.Y < -2.5f+striker.radius+epsilon) && striker.vY < 0){striker.vY = -striker.vY * restitution; } 
if((striker.Y > 2.5f-striker.radius-epsilon) && striker.vY > 0) {striker.vY = -striker.vY * restitution; }

if(magnitude(striker.vX , striker.vY) > 0.0f){
if(striker.vX > 0){
	striker.X += striker.vX * dT - 0.5 * friction * dT * dT;
}else{ 	
	striker.X += striker.vX * dT + 0.5 * friction * dT * dT;
}
if(striker.vY > 0){
striker.Y += striker.vY * dT - 0.5 * friction * dT * dT;
}else{
striker.Y += striker.vY * dT + 0.5 * friction * dT * dT;
}
}
for(te = 0; te < totalCoins ; te++){
if((coin[te].X < -2.5f+coin[te].radius+epsilon) && coin[te].vX < 0){coin[te].vX = -coin[te].vX * restitution; }
if((coin[te].X > 2.5f-coin[te].radius-epsilon) && coin[te].vX > 0) {coin[te].vX = -coin[te].vX * restitution; }
if((coin[te].Y < -2.5f+coin[te].radius+epsilon) && coin[te].vY < 0){coin[te].vY = -coin[te].vY * restitution; } 
if((coin[te].Y > 2.5f-coin[te].radius-epsilon) && coin[te].vY > 0) {coin[te].vY = -coin[te].vY * restitution; }

if(magnitude(coin[te].vX , coin[te].vY) > 0.0f){
if(coin[te].vX > 0){
	coin[te].X += coin[te].vX * dT - 0.5 * friction * dT * dT;}
else{
 	coin[te].X += coin[te].vX * dT + 0.5 * friction * dT * dT;
}
if(coin[te].vY > 0){
coin[te].Y += coin[te].vY * dT - 0.5 * friction * dT * dT;
}else{
coin[te].Y += coin[te].vY * dT + 0.5 * friction * dT * dT;
}
}
}
if(magnitude(striker.vX , striker.vY) <= 0.0f)
{
a=a+1;
}
else{
double mag = sqrt(striker.vX * striker.vX + striker.vY * striker.vY);
double rX = (-striker.vX / mag) * friction  * dT;
double rY = (-striker.vY / mag) * friction  * dT;
double newVx = striker.vX + rX;
double newVy = striker.vY + rY;

if(newVx * striker.vX <=0.0f)
{
striker.vX = 0;
}else{
striker.vX = newVx;
}
if(newVy * striker.vY <=0.0f)
{
striker.vY = 0;
}else{
striker.vY = newVy;
}
}

for(te = 0;te< totalCoins; te++){

if(magnitude(coin[te].vX , coin[te].vY) <= 0.0f || coin[te].visible==0)
{
a=a+1;
}else{

 mag = sqrt(coin[te].vX * coin[te].vX + coin[te].vY * coin[te].vY);
rX = (-coin[te].vX / mag) * friction * dT;
rY = (-coin[te].vY / mag) * friction  * dT;
newVx = coin[te].vX + rX;
newVy = coin[te].vY + rY;
if(newVx * coin[te].vX <=0.0f)
{
coin[te].vX = 0;
}else{
coin[te].vX = newVx;
}
if(newVy * coin[te].vY <=0.0f)
{
coin[te].vY = 0;
}else{
coin[te].vY = newVy;
}
}

}

if(initialised == 0 && a==(totalCoins+1))
{
updateScores();
int pT = 0;
for(pT = 0;pT < totalPlayers;pT++)
{
printf("Player %d score : %d\n",pT+1,pScores[pT]);
}
if(isQueenOnBoard == 0 && f_coinPocketed == 0 && f_queenPocketed == 0)
{
tryToPlaceAtCenter(&coin[2]);
isQueenOnBoard  = 1;
coinOwners[pCounter][2] = 0; 
coinsLeft++;
}

if(isQueenOnBoard == 0 && curChanceCoinsPocketed >= 2 && f_queenPocketed == 0)
{
f_queenPocketed = 1;
}


if((f_strikerPocketed == 1) || (isQueenOnBoard == 1 && coinsLeft == 1))
{
if(coinOwners[pCounter][4] == 1){
tryToPlaceAtCenter(&coin[4]);
coinOwners[pCounter][4] = 0;
coinsLeft++;
}else if(coinOwners[pCounter][3] == 1)
{
tryToPlaceAtCenter(&coin[3]);
coinOwners[pCounter][3] = 0;
coinsLeft++;
}
else if(coinOwners[pCounter][1] == 1)
{
tryToPlaceAtCenter(&coin[1]);
coinOwners[pCounter][1] = 0;
coinsLeft++;
}
else if(coinOwners[pCounter][0] == 1)
{
tryToPlaceAtCenter(&coin[0]);
coinOwners[pCounter][0] = 0;
coinsLeft++;
}
striker.visible = 1;
if(pCounter == 0)
{
initializeCoin(&striker,0,-2.1,0.04f,0.1064f,1,0,0,-10);
}else if(pCounter == 1)
{
initializeCoin(&striker,-2.1,0,0.04f,0.1064f,1,0,0,-10);
}else if(pCounter == 2)
{
initializeCoin(&striker,0,2.1,0.04f,0.1064f,1,0,0,-10);
}else if(pCounter == 3)
{
initializeCoin(&striker,2.1,0,0.04f,0.1064f,1,0,0,-10);
}

}

if(f_coinPocketed == 0){
pCounter = (pCounter + 1)%totalPlayers ;
}

if(singlePlayerMode == 1 || bot==0)
{
if(pCounter == 0)
{
initializeCoin(&striker,0,-2.1,0.04f,0.1064f,1,0,0,-10);
}else if(pCounter == 1)
{
initializeCoin(&striker,-2.1,0,0.04f,0.1064f,1,0,0,-10);
}else if(pCounter == 2)
{
initializeCoin(&striker,0,2.1,0.04f,0.1064f,1,0,0,-10);
}else if(pCounter == 3)
{
initializeCoin(&striker,2.1,0,0.04f,0.1064f,1,0,0,-10);
}
control = 1;
}
curChanceCoinsPocketed = 0;
f_strikerPocketed = 0;
f_coinPocketed = 0;

if(control == 0 && pCounter == playerNo){
control = 1;
if(playerNo == 0)
{
initializeCoin(&striker,0,-2.1,0.04f,0.1064f,1,0,0,-10);
if(singlePlayerMode == 0){
bzero(obuffer,1024);
sprintf(obuffer,"%.45f %.45f %c",striker.X,striker.Y,'d');

		int i = 0;
		while(i < totalPlayers-1)
		{
				bzero(obuffer,1024);
				sprintf(obuffer,"%.45f %.45f %c",striker.X,striker.Y,'d');
				write(newsockfd[i],obuffer,strlen(obuffer));
			i++;
		}
}
}else if(playerNo == 1)
{
initializeCoin(&striker,-2.1,0,0.04f,0.1064f,1,0,0,-10);
if(singlePlayerMode == 0){
bzero(obuffer,1024);
sprintf(obuffer,"%.45f %.45f %c",striker.X,striker.Y,'d');
write(sockfd,obuffer,strlen(obuffer));
}
}else if(playerNo == 2)
{
initializeCoin(&striker,0,2.1,0.04f,0.1064f,1,0,0,-10);
if(singlePlayerMode == 0){
bzero(obuffer,1024);
sprintf(obuffer,"%.45f %.45f %c",striker.X,striker.Y,'d');
write(sockfd,obuffer,strlen(obuffer));
}
}else if(playerNo == 3)
{
initializeCoin(&striker,2.1,0,0.04f,0.1064f,1,0,0,-10);
if(singlePlayerMode == 0){
bzero(obuffer,1024);
sprintf(obuffer,"%.45f %.45f %c",striker.X,striker.Y,'d');
write(sockfd,obuffer,strlen(obuffer));
}
}

}

initialised = 1;

}



if(initialised == 1 && singlePlayerMode == 0){
if(isServer == 1)
{
	if(playerNo != pCounter)
	{

	int q=-1;
	bzero(ibuffer,1024);
     	q = read(newsockfd[pCounter-1],ibuffer,1023);
	if(q >= 0 ){
//puts(ibuffer);
		if(ibuffer[strlen(ibuffer)-1]=='d'){

		char c = ' ' ;
		sscanf(ibuffer,"%lf %lf %c",&striker.X,&striker.Y,&c);
		int i = 0;
		while(i < totalPlayers-1)
		{
			if( i+1 != pCounter)
			{
				bzero(obuffer,1024);
				sprintf(obuffer,"%.45f %.45f %c",striker.X,striker.Y,'d');
				write(newsockfd[i],obuffer,strlen(obuffer));
			}
			i++;
		}
		}else
		{
		//bzero(obuffer,1024);
		sscanf(ibuffer,"%lf %lf %lf %lf\n",&striker.X,&striker.Y,&striker.vX,&striker.vY);
		int i = 0;
		while(i < totalPlayers-1)
		{
			if( i+1 != pCounter)
			{
				bzero(obuffer,1024);
				sprintf(obuffer,"%.45f %.45f %.45f %.45f\n",striker.X,striker.Y,striker.vX,striker.vY);
				write(newsockfd[i],obuffer,strlen(obuffer));
			}
			i++;
		}
		
		initialised = 0;		
		}
	}
	}

}else
{
	if(playerNo != pCounter)
	{
		bzero(ibuffer,1024);
int q= -1;
     		q = read(sockfd,ibuffer,1023);		
		if(q>=0)     {
			if(ibuffer[strlen(ibuffer)-1]=='d'){
			char c = ' ';
			sscanf(ibuffer,"%lf %lf %c",&striker.X,&striker.Y,&c);
			}else
			{
			sscanf(ibuffer,"%lf %lf %lf %lf\n",&striker.X,&striker.Y,&striker.vX,&striker.vY);
			initialised = 0;
			}
		}
	}

}

}


}


void* redrawAll(void *p)
{

glutPostRedisplay();

}
void timerFunc(int val)
{
     pthread_t thread1, thread2;
     int  iret1, iret2;
     char *msg = (char*)"phy";

iret2 = pthread_create( &thread2, NULL, &redrawAll,(void*)msg);     
iret1 = pthread_create( &thread1, NULL, &threadPhysics, (void*)msg);
     
    pthread_join( thread1, NULL); 
     pthread_join( thread2, NULL);
 
glutTimerFunc(10.0f,&timerFunc,1);

}

void myglutidle(){

if(glutGetWindow() != main_window)
glutSetWindow(main_window);


}

int main(int argc, char** argv)
{
resetScores();
int t1,t2;
double aim = 2.47;
holes[0].X = -aim;
holes[0].Y = aim;
holes[1].X = aim;
holes[1].Y = aim;
holes[2].X = aim;
holes[2].Y = -aim;
holes[3].X = -aim;
holes[3].Y = -aim;
for(t1 =0 ; t1 < 4; t1++)
{
pScores[t1] = 0;
for(t2 =0 ; t2 < 5; t2++)
{
coinOwners[t1][t2]=0;
}
}
    initializeCoin(&striker,0,-2.1,0.04f,0.1064f,1,0,0,-10);
    initializeCoin(&coin[0],0,-0.16,0.03f,0.08f,1,0,0,20);
    initializeCoin(&coin[1],0,0.16,0.03f,0.08f,1,0,0,20);
    initializeCoin(&coin[3],0.16,0,0.03f,0.08f,1,0,0,10);
    initializeCoin(&coin[4],-0.16,0,0.03f,0.08f,1,0,0,10);
    initializeCoin(&coin[2],0,0,0.03f,0.08f,1,0,0,50);

if(singlePlayerMode == 1){
initializeCoin(&striker,-2.1,0,0.04f,0.1064f,1,0,0,-10);
}

srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize (width, height);
    glutInitWindowPosition (100, 100);
    main_window=glutCreateWindow (argv[0]);
    //glutGameModeString( "780x780:32" ); //the settings for fullscreen mode
	//glutEnterGameMode();    
   
init ();
	////////////////////////////////////////
  
  //glui = GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_RIGHT ); 
	
glui= GLUI_Master.create_glui("Carrom Game", 0 );
//glui->set_main_gfx_window( main_window );
   glui->add_statictext( "Let's Play ! The Game of Carrom" );                    
glui->add_separator();                          
GLUI_Panel *obj_panel = glui->add_panel("Select Game-Type" );                                      
GLUI_RadioGroup *group1 =glui->add_radiogroup_to_panel(obj_panel,&obj,3); 
glui->add_radiobutton_to_group( group1, "Single-Player" );
glui->add_radiobutton_to_group( group1, "Multi-Player" );
glui->add_button_to_panel( obj_panel,"select",-1,callback_game_type);
////////////////////////////////glutSetWindow(main_window);


GLUI_Master.set_glutIdleFunc(myglutidle);


    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
glutMouseFunc(mouse);


glutMotionFunc(pressedMotion);
glutPassiveMotionFunc(passiveMotion);    

glutTimerFunc(10.0f,&timerFunc,1);
    glutMainLoop();
    return 0;

} 
