typedef struct{
double r,g,b;
} RGB;

typedef struct
{
double X;
double Y;
double vX;
double vY;
double accuracy;
} C_SHOT;

typedef struct{
double X;
double Y;
double vX, vY;
double mass;
double radius;
int visible;
int SCORE;
} COIN;

COIN striker;
COIN coin[5];
