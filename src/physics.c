int f_coinPocketed=0; 
int f_queenPocketed=0;
int coinsLeft  = 5;
int isQueenOnBoard = 1;
int f_strikerPocketed = 0;
int pScores[4];
int f_prevChanceQueen = 0;
int curChanceCoinsPocketed = 0;
int invalidPosition = 0;
int coinOwners[4][5];
int totalPlayers=2;
int totalCoins = 5;
int pCounter = 0;
int initialised = 1;
     
void simulatePhysicsAdvanced()
{
double sep;
int i=0;
int j=0,k=0;
Vector2D posRel,vRel;

if(magnitude(2.3933-striker.X,2.3933-striker.Y) < 0.105f)
{
striker.visible = 0;
f_strikerPocketed = 1;
}
if(magnitude(-2.3933-striker.X,2.3933-striker.Y) < 0.105f)
{
striker.visible = 0;
f_strikerPocketed = 1;
}
if(magnitude(2.3933-striker.X,-2.3933-striker.Y) < 0.105f)
{
striker.visible = 0;
f_strikerPocketed = 1;
}
if(magnitude(-2.3933-striker.X,-2.3933-striker.Y) < 0.105f)
{
striker.visible = 0;
f_strikerPocketed = 1;
}

for (i=0 ; i < totalCoins ; i++)
{
if(magnitude(2.3933-coin[i].X,2.3933-coin[i].Y) < 0.105f && coin[i].visible == 1)
{
coin[i].visible = 0;
coinOwners[pCounter][i] = 1; 
coinsLeft -= 1;
f_coinPocketed = 1;
curChanceCoinsPocketed += 1;
if(isQueenOnBoard == 0 && f_queenPocketed == 0)
{
f_queenPocketed = 1;
}
if(i == 2)
{
isQueenOnBoard = 0;
}

}
if(magnitude(-2.3933-coin[i].X,2.3933-coin[i].Y) < 0.105f && coin[i].visible == 1)
{
coin[i].visible = 0;
coinOwners[pCounter][i] = 1;
coinsLeft -= 1;
f_coinPocketed = 1;
curChanceCoinsPocketed += 1;
if(isQueenOnBoard == 0 && f_queenPocketed == 0)
{
f_queenPocketed = 1;
}
if(i == 2)
{
isQueenOnBoard = 0;
}
}
if(magnitude(2.3933-coin[i].X,-2.3933-coin[i].Y) < 0.105f && coin[i].visible == 1)
{
coin[i].visible = 0;
coinOwners[pCounter][i] = 1;
coinsLeft -= 1;
f_coinPocketed = 1;
curChanceCoinsPocketed += 1;
if(isQueenOnBoard == 0 && f_queenPocketed == 0)
{
f_queenPocketed = 1;
}
if(i == 2)
{
isQueenOnBoard = 0;
}
}
if(magnitude(-2.3933-coin[i].X,-2.3933-coin[i].Y) < 0.105f && coin[i].visible == 1)
{
coin[i].visible = 0;
coinOwners[pCounter][i] = 1;
coinsLeft -= 1;int totalPlayers=2;
int totalCoins = 5;
int pCounter = 0;
int initialised = 1;
f_coinPocketed = 1;
curChanceCoinsPocketed += 1;
if(isQueenOnBoard == 0 && f_queenPocketed == 0)
{
f_queenPocketed = 1;
}
if(i == 2)
{
isQueenOnBoard = 0;
}
}
}



for (i = 0; i < totalCoins ; i++){
posRel.X = striker.X - coin[i].X;
posRel.Y = striker.Y - coin[i].Y;
vRel.X = striker.vX - coin[i].vX;
vRel.Y = striker.vY - coin[i].vY;
sep = magnitude(striker.X - coin[i].X, striker.Y - coin[i].Y);
if((sep < striker.radius + coin[i].radius) && dotProduct(&vRel,&posRel) < 0 && coin[i].visible == 1 && striker.visible == 1)
{
double cosineTheta = (striker.X - coin[i].X)/sep;
double sineTheta = (coin[i].Y - striker.Y)/sep;
Vector2D xprime,yprime;
xprime.X = cosineTheta;
xprime.Y = -sineTheta;
yprime.X = sineTheta;
yprime.Y = cosineTheta;
Vector2D vorg1,vorg2;
Vector2D v1,v2,v3,v4,v5,v6;
vorg1.X = striker.vX;
vorg1.Y = striker.vY;
vorg2.X = coin[i].vX;
vorg2.Y = coin[i].vY;
v1.X = dotProduct(&vorg1,&xprime);
v1.Y = dotProduct(&vorg1,&yprime);
v2.X = dotProduct(&vorg2,&xprime);
v2.Y = dotProduct(&vorg2,&yprime);
v3.Y = v1.Y;
v4.Y = v2.Y;
v3.X = (striker.mass * v1.X + coin[i].mass *(v2.X - (eCS * v1.X) + (eCS * v2.X)))/ (striker.mass + coin[i].mass);
v4.X = (coin[i].mass * v2.X + striker.mass * (v1.X - (eCS * v2.X) + (eCS * v1.X)))/(striker.mass + coin[i].mass);
v5.X = v3.X * cosineTheta + v3.Y * sineTheta;
v5.Y = v3.Y * cosineTheta - v3.X * sineTheta;
v6.X = v4.X * cosineTheta + v4.Y * sineTheta;
v6.Y = v4.Y * cosineTheta - v4.X * sineTheta;
striker.vX = v5.X;
striker.vY = v5.Y;
coin[i].vX = v6.X;
coin[i].vY = v6.Y;
}
}

for(j=0;j < totalCoins ; j++)
{
for(k=j+1;k < totalCoins ; k++)
{
posRel.X = coin[j].X - coin[k].X;
posRel.Y = coin[j].Y - coin[k].Y;
vRel.X = coin[j].vX - coin[k].vX;
vRel.Y = coin[j].vY - coin[k].vY;
sep = magnitude(coin[j].X - coin[k].X, coin[j].Y - coin[k].Y);
if((sep < coin[j].radius + coin[k].radius) && dotProduct(&posRel,&vRel) < 0 && coin[k].visible == 1 && coin[j].visible == 1)
{
double cosineTheta = (coin[j].X - coin[k].X)/sep;
double sineTheta = (coin[k].Y - coin[j].Y)/sep;
Vector2D xprime,yprime;
xprime.X = cosineTheta;
xprime.Y = -sineTheta;
yprime.X = sineTheta;
yprime.Y = cosineTheta;
Vector2D vorg1,vorg2;
Vector2D v1,v2,v3,v4,v5,v6;
vorg1.X = coin[j].vX;
vorg1.Y = coin[j].vY;
vorg2.X = coin[k].vX;
vorg2.Y = coin[k].vY;
v1.X = dotProduct(&vorg1,&xprime);
v1.Y = dotProduct(&vorg1,&yprime);
v2.X = dotProduct(&vorg2,&xprime);
v2.Y = dotProduct(&vorg2,&yprime);
v3.Y = v1.Y;
v4.Y = v2.Y;
v3.X = (coin[j].mass * v1.X + coin[k].mass *(v2.X - (eCS * v1.X) + (eCS * v2.X)))/ (coin[j].mass + coin[k].mass);
v4.X = (coin[k].mass * v2.X + coin[j].mass * (v1.X - (eCS * v2.X) + (eCS * v1.X)))/(coin[j].mass + coin[k].mass);
v5.X = v3.X * cosineTheta + v3.Y * sineTheta;
v5.Y = v3.Y * cosineTheta - v3.X * sineTheta;
v6.X = v4.X * cosineTheta + v4.Y * sineTheta;
v6.Y = v4.Y * cosineTheta - v4.X * sineTheta;
coin[j].vX = v5.X;coinOwners[pCounter][i] = 1;
coin[j].vY = v5.Y;
coin[k].vX = v6.X;
coin[k].vY = v6.Y;
}
}
}

}

