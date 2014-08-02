int singlePlayerMode = 0;
int main_window=0;
int AI_level=3;
int bot=1;

int sweepTest1(Vector2D start,Vector2D end,int index)
{
Vector2D curPos,tempRel,relPos;
curPos.X = start.X;
curPos.Y = start.Y;
Vector2D vel = subtract(&end,&start);
relPos = subtract(&end,&start);
double fLength = magnitude(relPos.X,relPos.Y);
double mag = magnitude(vel.X,vel.Y);
vel.X = (vel.X / mag);
vel.Y = (vel.Y / mag);
int col = 0;
int i =0;
double sep = 0;
tempRel = start;
while(magnitude(tempRel.X-start.X,tempRel.Y-start.Y) < fLength){
for (i = 0; i < totalCoins ; i++){
sep = magnitude(tempRel.X - coin[i].X, tempRel.Y - coin[i].Y);
if((sep < coin[index].radius + coin[i].radius) && coin[i].visible == 1 && index != i)
{
return 1;
}
}
tempRel.X += vel.X * dT;
tempRel.Y += vel.Y * dT;
}
return 0;
}


int sweepTest2(Vector2D start,Vector2D end,int index)
{
Vector2D curPos,tempRel,relPos;
curPos.X = start.X;
curPos.Y = start.Y;
Vector2D vel = subtract(&end,&start);
relPos = subtract(&end,&start);
double fLength = magnitude(relPos.X,relPos.Y);
double mag = magnitude(vel.X,vel.Y);
vel.X = (vel.X / mag);
vel.Y = (vel.Y / mag);
int col = 0;
int i =0;
double sep = 0;
tempRel = start;
while(magnitude(tempRel.X-start.X,tempRel.Y-start.Y) < fLength){
for (i = 0; i < totalCoins ; i++){
sep = magnitude(tempRel.X - coin[i].X, tempRel.Y - coin[i].Y);
if((sep < striker.radius + coin[i].radius + 0.005f) && coin[i].visible == 1 && index != i)
{
return 1;
}
}
tempRel.X += vel.X * dT;
tempRel.Y += vel.Y * dT;
}
return 0;
}


Vector2D computeVelocity(Vector2D start, Vector2D end, COIN *cToBeHit,COIN *cHitBy,Vector2D velRequired)
{
Vector2D fVel;
double fVelMag = 0;
Vector2D dir;
dir = subtract(&end,&start);
double mag = magnitude(dir.X,dir.Y);
dir.X = dir.X / mag;
dir.Y = dir.Y / mag;
Vector2D vReqDir;

if(cToBeHit == NULL)
{
fVelMag = sqrt(2 * friction * mag * 1.6f );
fVel.X = dir.X * fVelMag;
fVel.Y = dir.Y * fVelMag;
}else
{
double reqVel = magnitude(velRequired.X,velRequired.Y);
vReqDir.X = velRequired.X / reqVel;
vReqDir.Y = velRequired.Y / reqVel;
double xpVel = (magnitude(velRequired.X,velRequired.Y) * (cToBeHit->mass + cHitBy->mass))/(cHitBy->mass * (1.0f+eCS));
double cosT = dotProduct(&dir,&vReqDir);
if(cosT < 0) cosT = -cosT;
double iniVelReq = sqrt((xpVel / cosT) * (xpVel / cosT) + 2 * friction * mag * 1.6f);
fVel.X = iniVelReq * dir.X; 
fVel.Y = iniVelReq * dir.Y;
if(iniVelReq > maxPower)
{
fVel.X = maxPower * dir.X; 
fVel.Y = maxPower * dir.Y;
}
}

return fVel;
}

Vector2D backTrack(Vector2D dir,COIN *cCoinToBeHit, COIN *cHitBy)
{
Vector2D temp;
temp.X = cCoinToBeHit->X;
temp.Y = cCoinToBeHit->Y;
temp.X += dir.X * (cCoinToBeHit->radius + cHitBy->radius);
temp.Y += dir.Y * (cCoinToBeHit->radius + cHitBy->radius);
return temp;
}

Vector2D getRange(int index,int holeNo,int pNo)
{
Vector2D range;
Vector2D t1;
t1.X = coin[index].X;
t1.Y = coin[index].Y;
Vector2D dir = subtract(&t1,&holes[holeNo]);
normalize(&dir);
Vector2D aimPos = backTrack(dir,&coin[index],&striker);
double m = dir.Y  / dir.X;
double c = aimPos.Y - m * aimPos.X;
if(pNo == 0)
{

double high = (-2.1 - c)/ m;
if(high > 1.91)
{
high = 1.91;
}
if(high < -1.91)
{
high = -1.91;
}
if(t1.X < -1.91)
{
t1.X = -1.909;
}
if(t1.X > 1.91)
{
t1.X = 1.911;
}
range.X = t1.X;
range.Y = high;
return range;
}else if(pNo == 1)
{

double high = -2.1f * m + c;
if(high > 1.91)
{
high = 1.91;
}
if(high < -1.91)
{
high = -1.91;
}
if(t1.Y < -1.91)
{
t1.Y = -1.909;
}
if(t1.Y > 1.91)
{
t1.Y = 1.911;
}
range.X = t1.Y;
range.Y = high;
return range;
}else if(pNo == 2)
{
double high = (2.1 - c)/ m;
if(high > 1.91)
{
high = 1.91;
}
if(high < -1.91)
{
high = -1.91;
}
if(t1.X < -1.91)
{
t1.X = -1.909;
}
if(t1.X > 1.91)
{
t1.X = 1.911;
}
range.X = t1.X;
range.Y = high;
return range;
}else if(pNo == 3)
{
double high = 2.1f * m + c;
if(high > 1.91)
{
high = 1.91;
}
if(high < -1.91)
{
high = -1.91;
}
if(t1.Y < -1.91)
{
t1.Y = -1.909;
}
if(t1.Y > 1.91)
{
t1.Y = 1.911;
}
range.X = t1.Y;
range.Y = high;
return range;
}
}


void reset(C_SHOT *a,int length)
{
int local = 0;
for(local =0;local < length;local++)
{
a->accuracy = 0;
a++;
}
}

void reset_1(C_SHOT *a)
{
a->accuracy = 0;
}

void AI(double *X, double *Y, double *velX,double *velY)
{
C_SHOT tWork;
if(singlePlayerMode == 1 || bot == 1)
{
reset_1(&tWork);
Vector2D t1;
Vector2D strPos;
int y = 0;
int temporary = 0;

for(y = 0;y < 5 && temporary == 0; y++){
if(coinsLeft == 2 && f_queenPocketed == 0 && isQueenOnBoard == 1)
{
y=2;
temporary = 1;
}
int iP= 0;
int z=0;
for (z = 0; z < totalCoins ; z++){
double sepn = magnitude(coin[y].X - coin[z].X, coin[y].Y - coin[z].Y);
if((sepn <= coin[y].radius + coin[z].radius + 0.01f) && coin[z].visible == 1 && z != y)
{
iP = 1;
}
}
if(coin[y].visible == 1){

t1.X = coin[y].X;
t1.Y = coin[y].Y;
int loc = 0;
for(loc = 0;loc < 4; loc++){
Vector2D dir = subtract(&t1,&holes[loc]);
normalize(&dir);

Vector2D aimPos = backTrack(dir,&coin[y],&striker);
Vector2D range = getRange(y,loc,0);

double temp = range.Y;
strPos.Y = -2.1;
strPos.X = temp;
if(sweepTest1(t1,holes[loc],y) == 0){

Vector2D vel1 = computeVelocity(t1,holes[loc],NULL,&coin[y],t1);
if((coin[y].Y < -2.1 && loc >= 2) || (coin[y].Y > -2.1 && loc >= 0 && loc < 2)){
if((loc % 2 == 0 && loc < 2) || ((loc % 2 == 1 && loc >= 2)) ){
for( temp = range.Y; temp >= range.X ; temp -= 0.001f)
{
int ii =0;
double sepi = 0;
int invalidPosition= 0;
for (ii = 0; ii < totalCoins ; ii++){
sepi = magnitude(strPos.X - coin[ii].X, strPos.Y - coin[ii].Y);
if((sepi < striker.radius + coin[ii].radius) && coin[ii].visible == 1)
{
invalidPosition = 1;
}
}
if((sweepTest2(strPos,aimPos,y) == 0) && (invalidPosition == 0))
{
break;
}
strPos.X = temp;
}
}else
{
for( temp = range.Y; temp >= range.X ; temp += 0.001f)
{
int ii =0;
double sepi = 0;
int invalidPosition= 0;
for (ii = 0; ii < totalCoins ; ii++){
sepi = magnitude(strPos.X - coin[ii].X, strPos.Y - coin[ii].Y);
if((sepi < striker.radius + coin[ii].radius) && coin[ii].visible == 1)
{
invalidPosition = 1;
}
}
if((sweepTest2(strPos,aimPos,y) == 0) && (invalidPosition == 0))
{
break;
}
strPos.X = temp;
}
}
Vector2D dir2 = subtract(&strPos,&aimPos);
normalize(&dir2);
double acc = dotProduct(&dir,&dir2);
if(acc < 0) acc=-acc;
Vector2D fVel = computeVelocity(strPos,aimPos,&coin[y],&striker,vel1);
if((acc >= tWork.accuracy && acc > 0) || (coinsLeft == 2 && f_queenPocketed == 0 && isQueenOnBoard == 1))
{
tWork.accuracy = -acc;
tWork.X= strPos.X;
tWork.Y= strPos.Y;
tWork.vX = fVel.X;
tWork.vY = fVel.Y;
if(coinsLeft == 2 && f_queenPocketed == 0 && isQueenOnBoard == 1){

break;

}

}

}
}
}
}
}

}
double err = 0;
if(AI_level == 1){
err = (rand() % 100) / 1000.0f + 0.01f;
}else if(AI_level == 2)
{
err = (rand() % 1000) / 10000.0f + 0.001f;
}
*X = tWork.X + err;
*Y = tWork.Y;
*velX = tWork.vX;
*velY = tWork.vY;

}
