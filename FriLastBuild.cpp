#include <windows.h>
#include <math.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
using namespace std;
class Bullet
{
public:
    float x;
    float y;
    float dyBydx;
};

//--Screen Size And Ortho Co-ordinate--//
int GLWidth =1024;
int GLHeight = 580;
int counter_ = 0;
int randx=0;
int randy=0;
//--Player Skeleton Key Points--//
int Ax=105, Ay=300;
int BupX=110 ,BupY=300;
int BdnX=110 ,BdnY=250;
int Cx= 148, Cy=300;
int Ex=100 , Ey=250;
int Fx=120 , Fy=250;

int i =0;
float _move = 0.0f;

float rotateValue = 0;
int frontTheighAdjustment;

//--Enemy Skeleton Key Points--//
int EAx=795, EAy=300;
int EBupX=790 ,EBupY=300;
int EBdnX=790 ,EBdnY=250;
int ECx= 752, ECy=300;
int EEx=780 , EEy=250;
int EFx=800 , EFy=250;
int ECollisionCOunter=0;
int Ei =0;
float E_move = 0.0f;

float ErotateValue = 0;
int EfrontTheighAdjustment;

//--Player Bullet History--//
int BulletLimit = 100;
Bullet BulletCollection[100];
int BulletCounter = 0;

//--Enemy Bullet History--//
int EBulletLimit = 100;
Bullet EBulletCollection[100];
int EBulletCounter = 0;

//--Player Health--//
int healthLevel = 100;

void upperBodySkeleton();
void lowerBodySkeleton();
void upperBody();
void lowerBody();

void EupperBodySkeleton();
void ElowerBodySkeleton();
void EupperBody();
void ElowerBody();
void RandomEBody();///
void DrawHealth()
{
    if(healthLevel>50)
    {
        glColor3f (0.0, 1.0, 0.0);
    }
    else if(healthLevel>30)
    {
        glColor3f (1.0, 1.0, 0.0);
    }
    else
    {
        glColor3f (1.0, 0.0, 0.0);
    }
    for(int i = 0; i<healthLevel; i++)
    {
        glBegin(GL_QUADS);
        glVertex2i((10+i*10), GLHeight-10);
        glVertex2i((10+i*10), GLHeight-20);
        glVertex2i((20+i*10), GLHeight-20);
        glVertex2i((20+i*10), GLHeight-10);
        glEnd();
    }

}
void removeEBullet(int i)
{
    for(; i<EBulletCounter-1; i++)
    {
        EBulletCollection[i]=EBulletCollection[i+1];
    }
    BulletCounter--;
}
void frontTheigh()
{
    glColor3f (0.0, 0.0, 0.0);/// FrontThigh
    glBegin(GL_POLYGON);
    glVertex2i(Fx+5, Fy-15);
    glVertex2i(Fx, frontTheighAdjustment);
    glVertex2i(Fx-10, Fy);
    glVertex2i(Fx-4, Fy-20);
    glEnd();
}

void EfrontTheigh()
{
    glColor3f (0.0, 0.0, 0.0);/// FrontThigh
    glBegin(GL_POLYGON);
    glVertex2i(EFx+5, EFy-15);
    glVertex2i(EFx, EfrontTheighAdjustment);
    glVertex2i(EFx-10, EFy);
    glVertex2i(EFx-4, EFy-20);
    glEnd();
}


void ECollide(int value)
{
    //if(EAx < BulletCollection[0].x && EAy >= BulletCollection[0].y && ECx < BulletCollection[0].x && ECy <= BulletCollection[0].y) //&& EEx <= BulletCollection[0].x && Ey <= BulletCollection[0].y && EFx <= BulletCollection[0].x)
    if((EAx > BulletCollection[0].x && EAy >= BulletCollection[0].y && ECx < BulletCollection[0].x && EEx > BulletCollection[0].x && EEy < BulletCollection[0].y) || (EAx > BulletCollection[0].x && EEy >= BulletCollection[0].y && EFy >= BulletCollection[0].y && ECx < BulletCollection[0].x))
    {

        ECollisionCOunter++;

        cout << "Enemy Collision " <<ECollisionCOunter<<endl;

        if(ECollisionCOunter==3)
        {

            randy= rand() % 200;
            randx= (rand() % (GLWidth-600))+300;

            EAy=randy;
            EBupY=randy;
            EBdnY=randy-50;
            ECy=randy;
            EEy=randy-50;
            EFy=randy-50;

            EAx=randx;
            EBupX=randx-5;
            EBdnX=randx-5;
            ECx=randx-43;
            EEx=randx-15;
            EFx=randx+5;

            ECollisionCOunter=0;
            glutTimerFunc(300, ECollide, 3);
        }
    }
    else
    {
        glutTimerFunc(300, ECollide, 3);
        //return false;
    }
}

int COllisonCounter = 0;
void PCollide(int value)
{
    //for(int i=0; i< EBulletCounter; i++)
    //{
        //if(Ax < EBulletCollection[i].x && Ay >= EBulletCollection[i].y && Cx > EBulletCollection[i].x && Ex <= EBulletCollection[i].x && Ey <= EBulletCollection[i].y && Fx >= EBulletCollection[i].x)
        if(Ax < EBulletCollection[0].x && Ay >= EBulletCollection[0].y && Cx > EBulletCollection[0].x && Ex <= EBulletCollection[0].x && Ey <= EBulletCollection[0].y && Fx >= EBulletCollection[0].x)
        {
            COllisonCounter++;
            //cout << "Player Collision " <<COllisonCounter<<endl;
		healthLevel--;
            glutTimerFunc(200, PCollide, 2);
            //return true;
        }
        else
        {
            glutTimerFunc(200, PCollide, 2);
            //return false;
        }
    //}
}


void EnemyTriger(int value)
{
    int NewBdnY = BdnY;

    switch(rand()%5)
    {
        case 0:
            NewBdnY = BdnY;
        break;
/*
        case 1:
            NewBdnY = BdnY-50;
        break;

        case 2:
            NewBdnY = BdnY+50;
        break;
*/
        case 3:
            NewBdnY = BdnY-200;
        break;

        case 4:
            NewBdnY = BdnY+200;
        break;
    }

    Bullet NewBullet;
    NewBullet.x = ECx;
    NewBullet.y = ECy;
    NewBullet.dyBydx = (float)((GLHeight-NewBdnY)-NewBullet.y)/(float)(BdnX-NewBullet.x);
    //cout<<NewBullet.dyBydx<<endl;
    if(EBulletCounter<EBulletLimit)
    {
        EBulletCollection[EBulletCounter] = NewBullet;
        EBulletCounter++;
    }
    else
    {
        //BulletCollection.pop_front(); //pop_front() is only available at list
        //BulletCollection.erase(BulletCollection.begin()); //this line throwrs some memory allocation error
        for(int i = 0; i<EBulletLimit-1; i++)
        {
            EBulletCollection[i]=EBulletCollection[i+1];
        }
        EBulletCollection[EBulletLimit-1]=NewBullet;
    }

    glutTimerFunc(1000, EnemyTriger, 1);
}

void Eshotfire()
{
    glColor3f(.9,.5,.3);

    for(int i = 0; i<EBulletCounter; i++)
    {
        glPushMatrix();
            glBegin(GL_QUADS);
            glVertex2i((int)EBulletCollection[i].x, (int)EBulletCollection[i].y);
            glVertex2i((int)EBulletCollection[i].x+5, (int)EBulletCollection[i].y);
            glVertex2i((int)EBulletCollection[i].x+5, (int)EBulletCollection[i].y+5);
            glVertex2i((int)EBulletCollection[i].x, (int)EBulletCollection[i].y+5);
            glEnd();
        glPopMatrix();
    }
}

void bulletFire()
{
    glColor3f(.3,.5,0.9);

    for(int i = 0; i<BulletCounter; i++)
    {
        glPushMatrix();
            glBegin(GL_QUADS);
            glVertex2i((int)BulletCollection[i].x, (int)BulletCollection[i].y);
            glVertex2i((int)BulletCollection[i].x+5, (int)BulletCollection[i].y);
            glVertex2i((int)BulletCollection[i].x+5, (int)BulletCollection[i].y+5);
            glVertex2i((int)BulletCollection[i].x, (int)BulletCollection[i].y+5);
            glEnd();
        glPopMatrix();glutPostRedisplay();
    }
}


void update(int value)
{
    if(BulletCounter<BulletLimit)
    {
        for(int x = 0; x < BulletCounter; x++)
        {
            BulletCollection[x].y += BulletCollection[x].dyBydx;
            BulletCollection[x].x += 1;
        }
        if(BulletCollection[0].x >= EAx&& BulletCollection>0 && BulletCounter != 0)
        {
            for(int i=0; i< BulletCounter-1; i++)
            {
                BulletCollection[i]=BulletCollection[i+1];
            }
            BulletCounter--;
        }
    }
    else
    {
        for(int x = 0; x<BulletLimit; x++)
        {
            BulletCollection[x].y += BulletCollection[x].dyBydx;
            BulletCollection[x].x += 1;
        }
        if(BulletCollection[0].x>=EAx&& BulletCollection>0)
        {
           for(int i=0; i<BulletCounter-1; i++)
            {
                BulletCollection[i]=BulletCollection[i+1];
            }
            BulletCounter--;
        }
    }
    if(EBulletCounter<EBulletLimit)
    {
        for(int x = 0; x<=EBulletCounter; x++)
        {
            EBulletCollection[x].y += EBulletCollection[x].dyBydx;
            EBulletCollection[x].x -= 1;
        }
        if(EBulletCollection[0].x<Ax&& EBulletCollection>0)
        {
            for(int i=0; i<=EBulletCounter-1; i++)
            {
                EBulletCollection[i]=EBulletCollection[i+1];
            }
            //EBulletCounter--;
        }
    }
    else
    {
        for(int x = 0; x<EBulletLimit; x++)
        {
            EBulletCollection[x].y += EBulletCollection[x].dyBydx;
            EBulletCollection[x].x -= 1;
        }
        if(EBulletCollection[0].x<Ax && EBulletCollection>0)
        {
           for(int i=0; i<EBulletCounter-1; i++)
            {
                EBulletCollection[i]=EBulletCollection[i+1];
            }
            //EBulletCounter--;
        }
    }
    glutTimerFunc(10, update, 0);
    glutPostRedisplay();
}


void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(5.0);

    DrawHealth();
    lowerBody();
    EupperBody();
    ElowerBody();

    Eshotfire();
    bulletFire();

    glPushMatrix();
        glTranslatef(BdnX, BdnY, 0);
        glRotatef(rotateValue,0,0,1);
        glTranslatef(-BdnX, -BdnY, 0);
        frontTheighAdjustment=BdnY;
        upperBody();
    glPopMatrix();
    //glutPostRedisplay();
    glutSwapBuffers();
}
void RandomEBody(){
    glColor3f (0.0, 0.0, 0.0);///Head
    glBegin(GL_QUADS);
    glVertex2i(EBupX, EBupY);
    glVertex2i(EBupX-5, EBupY-10);
    glVertex2i(EBupX-15, EBupY+10);
    glVertex2i(EBupX-5, EBupY+15);
    glEnd();

    glColor3f (0.0, 0.0, 0.0);///RightHand
    glBegin(GL_POLYGON);
    glVertex2i(EEx, EAy-5);
    glVertex2i(EEx, EAy);
    glVertex2i(EEx-28, EAy+1);
    glVertex2i(EEx-28, EAy-5);
    glEnd();

    glColor3f (0.0, 0.0, 0.0);///LeftArm
    glBegin(GL_POLYGON);
    glVertex2i(EFx-25, ECy-20);
    glVertex2i(EFx-5, ECy);
    glVertex2i(EFx-10, ECy);
    glVertex2i(EFx-25, ECy-15);
    glEnd();

    glColor3f (0.0, 0.0, 0.0);///LeftHand
    glBegin(GL_POLYGON);
    glVertex2i(EFx-25, EAy-20);
    glVertex2i(EFx-24, EAy-15);
    glVertex2i(EFx-48, EAy-5);
    glVertex2i(EFx-48, EAy-10);
    glEnd();

    glColor3f (0.0, 0.0, 0.0);///Gun
    glBegin(GL_POLYGON);
    glVertex2i(ECx-5, ECy);
    glVertex2i(ECx-5, ECy-10);
    glVertex2i(ECx, ECy-10);
    glVertex2i(ECx, ECy+5);
    glVertex2i(ECx-15, ECy+5);
    glVertex2i(ECx-15, ECy);



    glEnd();

    glColor3f (0.0, 0.0, 0.0);/// Body
    glBegin(GL_POLYGON);
    glVertex2i(EFx, EFy);
    glVertex2i(EFx-5, ECy);
    glVertex2i(EAx-15, EAy);
    glVertex2i(EEx, EEy);
    glEnd();

    glColor3f (0.0, 0.0, 0.0);/// BackThigh
    glBegin(GL_POLYGON);
    glVertex2i(EFx+5, EFy-20);
    glVertex2i(EFx, EFy);
    glVertex2i(EFx-10, EFy);
    glVertex2i(EFx-5, EFy-20);
    glEnd();

    //frontTheigh();

    glColor3f (0.0, 0.0, 0.0);/// FrontThigh
    glBegin(GL_POLYGON);
    glVertex2i(EEx+5, EEy-15);
    glVertex2i(EEx+10, EEy);
    glVertex2i(EEx, EEy);
    glVertex2i(EEx-5, EEy-15);
    glEnd();

    glColor3f (0.0, 0.0, 0.0);/// FrontLeg
    glBegin(GL_POLYGON);
    glVertex2i(EEx+5, EEy-40);
    glVertex2i(EEx+5, EEy-15);
    glVertex2i(EEx-5, EEy-15);
    glVertex2i(EEx-5, EEy-40);
    glEnd();


    glColor3f (0.0, 0.0, 0.0);/// BackLeg
    glBegin(GL_POLYGON);
    glVertex2i(EFx+15, EFy-40);
    glVertex2i(EFx+5, EFy-20);
    glVertex2i(EFx-5, EFy-20);
    glVertex2i(EFx+5, EFy-40);
    glEnd();

}

void lowerBodySkeleton()
{

    glBegin(GL_LINES);

    glVertex2i(Ex, Ey);
    glVertex2i(Fx, Fy);

    glEnd();

}

void ElowerBodySkeleton()
{

    glBegin(GL_LINES);

    glVertex2i(EEx, EEy);
    glVertex2i(EFx, EFy);

    glEnd();

}
void upperBodySkeleton()
{
    glBegin(GL_LINES);
    glColor3f (0.0, 0.0, 0.0); //skeleton
    glVertex2i(Ax, Ay);
    glVertex2i(Cx, Cy);
    glVertex2i(BupX, BupY);
    glVertex2i(BdnX, BdnY);
    glEnd();

}
void EupperBodySkeleton()
{
    glBegin(GL_LINES);
    glColor3f (0.0, 0.0, 0.0); //skeleton
    glVertex2i(EAx, EAy);
    glVertex2i(ECx, ECy);
    glVertex2i(EBupX, EBupY);
    glVertex2i(EBdnX, EBdnY);
    glEnd();

}
void upperBody()
{
    glColor3f (0.0, 0.0, 0.0);///Head
    glBegin(GL_QUADS);
    glVertex2i(BupX, BupY);
    glVertex2i(BupX+5, BupY-10);
    glVertex2i(BupX+15, BupY+10);
    glVertex2i(BupX+5, BupY+15);
    glEnd();

    glColor3f (0.0, 0.0, 0.0);///LeftHand
    glBegin(GL_POLYGON);
    glVertex2i(Cx-8, Cy-5);
    glVertex2i(Cx-8, Cy+1);
    glVertex2i(Cx-28, Cy);
    glVertex2i(Cx-28, Cy-5);
    glEnd();

    glColor3f (0.0, 0.0, 0.0);///RightArm
    glBegin(GL_POLYGON);
    glVertex2i(Ax+20, Ay-20);
    glVertex2i(Ax+24, Ay-15);
    glVertex2i(Ax+5, Ay);
    glVertex2i(Ax, Ay);
    glEnd();

    glColor3f (0.0, 0.0, 0.0);///RightHand
    glBegin(GL_POLYGON);
    glVertex2i(Ax+35, Ay-10);
    glVertex2i(Ax+35, Ay-5);
    glVertex2i(Ax+18, Ay-14);
    glVertex2i(Ax+20, Ay-20);
    glEnd();

    glColor3f (0.0, 0.0, 0.0);///Gun
    glBegin(GL_POLYGON);
    glVertex2i(Cx-3, Cy);
    glVertex2i(Cx+10, Cy);
    glVertex2i(Cx+10, Cy+5);
    glVertex2i(Cx-8, Cy+5);
    glVertex2i(Cx-8, Cy-10);
    glVertex2i(Cx-3, Cy-10);
    glEnd();

    glColor3f (0.0, 0.0, 0.0);/// Body
    glBegin(GL_POLYGON);
    glVertex2i(Fx, Fy);
    glVertex2i(Fx, Cy);
    glVertex2i(Ax, Ay);
    glVertex2i(Ex, Ey);
    glEnd();

}
void EupperBody()
{

    glColor3f (0.0, 0.0, 0.0);///Head
    glBegin(GL_QUADS);
    glVertex2i(EBupX, EBupY);
    glVertex2i(EBupX-5, EBupY-10);
    glVertex2i(EBupX-15, EBupY+10);
    glVertex2i(EBupX-5, EBupY+15);
    glEnd();

    glColor3f (0.0, 0.0, 0.0);///RightHand
    glBegin(GL_POLYGON);
    glVertex2i(EEx, EAy-5);
    glVertex2i(EEx, EAy);
    glVertex2i(EEx-28, EAy+1);
    glVertex2i(EEx-28, EAy-5);
    glEnd();

    glColor3f (0.0, 0.0, 0.0);///LeftArm
    glBegin(GL_POLYGON);
    glVertex2i(EFx-25, ECy-20);
    glVertex2i(EFx-5, ECy);
    glVertex2i(EFx-10, ECy);
    glVertex2i(EFx-25, ECy-15);
    glEnd();

    glColor3f (0.0, 0.0, 0.0);///LeftHand
    glBegin(GL_POLYGON);
    glVertex2i(EFx-25, EAy-20);
    glVertex2i(EFx-24, EAy-15);
    glVertex2i(EFx-48, EAy-5);
    glVertex2i(EFx-48, EAy-10);
    glEnd();

    glColor3f (0.0, 0.0, 0.0);///Gun
    glBegin(GL_POLYGON);
    glVertex2i(ECx-5, ECy);
    glVertex2i(ECx-5, ECy-10);
    glVertex2i(ECx, ECy-10);
    glVertex2i(ECx, ECy+5);
    glVertex2i(ECx-15, ECy+5);
    glVertex2i(ECx-15, ECy);



    glEnd();

    glColor3f (0.0, 0.0, 0.0);/// Body
    glBegin(GL_POLYGON);
    glVertex2i(EFx, EFy);
    glVertex2i(EFx-5, ECy);
    glVertex2i(EAx-15, EAy);
    glVertex2i(EEx, EEy);
    glEnd();

}
void lowerBody()
{
    glColor3f (0.0, 0.0, 0.0);/// BackThigh
    glBegin(GL_POLYGON);
    glVertex2i(Ex+5, Ey-20);
    glVertex2i(Ex+10, Ey);
    glVertex2i(Ex, Ey);
    glVertex2i(Ex-5, Ey-20);
    glEnd();

    //frontTheigh();

    glColor3f (0.0, 0.0, 0.0);/// FrontThigh
    glBegin(GL_POLYGON);
    glVertex2i(Fx+5, Fy-15);
    glVertex2i(Fx, Fy+5);
    glVertex2i(Fx-10, Fy);
    glVertex2i(Fx-4, Fy-20);
    glEnd();

    glColor3f (0.0, 0.0, 0.0);/// FrontLeg
    glBegin(GL_POLYGON);
    glVertex2i(Fx+5, Fy-40);
    glVertex2i(Fx+5, Fy-15);
    glVertex2i(Fx-4, Fy-20);
    glVertex2i(Fx-4, Fy-40);
    glEnd();


    glColor3f (0.0, 0.0, 0.0);/// BackLeg
    glBegin(GL_POLYGON);
    glVertex2i(Ex-5, Ey-40);
    glVertex2i(Ex+5, Ey-20);
    glVertex2i(Ex-5, Ey-20);
    glVertex2i(Ex-15, Ey-40);
    glEnd();
}
void ElowerBody()
{
    glColor3f (0.0, 0.0, 0.0);/// BackThigh
    glBegin(GL_POLYGON);
    glVertex2i(EFx+5, EFy-20);
    glVertex2i(EFx, EFy);
    glVertex2i(EFx-10, EFy);
    glVertex2i(EFx-5, EFy-20);
    glEnd();

    //frontTheigh();

    glColor3f (0.0, 0.0, 0.0);/// FrontThigh
    glBegin(GL_POLYGON);
    glVertex2i(EEx+5, EEy-15);
    glVertex2i(EEx+10, EEy);
    glVertex2i(EEx, EEy);
    glVertex2i(EEx-5, EEy-15);
    glEnd();

    glColor3f (0.0, 0.0, 0.0);/// FrontLeg
    glBegin(GL_POLYGON);
    glVertex2i(EEx+5, EEy-40);
    glVertex2i(EEx+5, EEy-15);
    glVertex2i(EEx-5, EEy-15);
    glVertex2i(EEx-5, EEy-40);
    glEnd();


    glColor3f (0.0, 0.0, 0.0);/// BackLeg
    glBegin(GL_POLYGON);
    glVertex2i(EFx+15, EFy-40);
    glVertex2i(EFx+5, EFy-20);
    glVertex2i(EFx-5, EFy-20);
    glVertex2i(EFx+5, EFy-40);
    glEnd();
}

void SpecialKey(unsigned char key, int x, int y)
{

    switch(key)
    {

    case 'W':
    case 'w':
        {
            if(BupY<GLHeight-50)
            {
                Ay+=50;
                BupY+=50;
                BdnY+=50;
                Cy+=50;
                Ey+=50;
                Fy+=50;
                //rotateCheck();
                glutPostRedisplay();
            }

            break;
        }
    case 'S':
    case 's':
        {
            if(Ey>50)
            {
                Ay-=50;
                BupY-=50;
                BdnY-=50;
                Cy-=50;
                Ey-=50;
                Fy-=50;
                //rotateCheck();
                glutPostRedisplay();
            }
            break;
        }
    case GLUT_KEY_RIGHT:
        /* Ax+=50;
         BupX+=50;
         BdnX+=50;
         Cx+=50;
         Ex+=50;
         Fx+=50;*/
        //rotateCheck();
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        /*Ax-=50;
        BupX-=50;
        BdnX-=50;
        Cx-=50;
        Ex-=50;
        Fx-=50;*/
        //rotateCheck();
        glutPostRedisplay();
        break;
    }
}
void myMouse(int button, int state, int x, int y)        // mouse click callback
{
    switch(button)
    {
    case GLUT_LEFT_BUTTON:
        if(state==GLUT_DOWN)
        {
            //glutTimerFunc(3, update, 0); //Add a timer
            //glutTimerFunc(3, Eupdate, 0);

            rotateValue=5;

            Bullet NewBullet;
            NewBullet.x = Cx;
            NewBullet.y = Cy;
            NewBullet.dyBydx = (float)((GLHeight-y)-NewBullet.y)/(float)(x-NewBullet.x);
            //cout<<NewBullet.dyBydx<<endl;
            if(BulletCounter<BulletLimit)
            {
                BulletCollection[BulletCounter] = NewBullet;
                BulletCounter++;
            }
            else
            {
                //BulletCollection.pop_front(); //pop_front() is only available at list
                //BulletCollection.erase(BulletCollection.begin()); //this line throwrs some memory allocation error
                for(int i = 0; i<BulletLimit-1; i++)
                {
                    BulletCollection[i]=BulletCollection[i+1];
                }
                BulletCollection[BulletLimit-1]=NewBullet;
            }
            glutPostRedisplay();
        }
        else if(state==GLUT_UP)
        {
            rotateValue=0;
            glutPostRedisplay();
        }
        break;
    default:
        break;
    }
}

void myInit (void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(5.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0.0, GLWidth, 0.0, GLHeight );
    //gluOrtho2D(-GLWidth /2, GLWidth /2, -GLHeight /2, GLHeight /2);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (GLWidth , GLHeight);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("Texas Duel");

    myInit ();


    glutMouseFunc(myMouse);
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(SpecialKey);
    glutTimerFunc(1, update, 0);
    glutTimerFunc(10, EnemyTriger, 1);
    glutTimerFunc(1, PCollide, 2);
    glutTimerFunc(1, ECollide, 3);
    glutMainLoop();
    return 0;
}
