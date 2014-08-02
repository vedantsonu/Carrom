typedef struct 
{
double X;
double Y;
} Vector2D;

double dotProduct(Vector2D *a,Vector2D *b)
{
return (a->X * b->X + a->Y * b->Y);
}

Vector2D subtract(Vector2D *a,Vector2D *b)
{
Vector2D temp ;
temp.X = a->X - b->X;
temp.Y = a->Y - b->Y;
return (temp);
}

void mulScalar(Vector2D *a,double k)
{
a->X = a->X * k;
a->Y = a->Y *k;
}


double magnitude(double x,double y)
{
return sqrt(x * x + y * y);
}

void normalize(Vector2D *a)
{
double mag = magnitude(a->X,a->Y);
a->X = a->X / mag;
a->Y = a->Y / mag;
}

Vector2D holes[4];
