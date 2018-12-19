#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
int GLWidth =1024;
int GLHeight = 580;
int Ax=105, Ay=300;
int BupX=110 ,BupY=300;
int BdnX=110 ,BdnY=250;
int Cx= 148, Cy=300;

int Ex=100 , Ey=250;
int Fx=120 , Fy=250;



//int GLWidth =1024;
//int GLHeight = 580;
int EAx=795, EAy=300;
int EBupX=790 ,EBupY=300;
int EBdnX=790 ,EBdnY=250;
int ECx= 752, ECy=300;
int EEx=780 , EEy=250;
int EFx=800 , EFy=250;

float rotateValue = 0;
int frontTheighAdjustment;

int i =0;
float _move = 0.0f;

float ErotateValue = 0;
int EfrontTheighAdjustment;

int Ei =0;
float E_move = 0.0f;

void upperBodySkeleton();
void lowerBodySkeleton();
void upperBody();
void lowerBody();

void EupperBodySkeleton();
void ElowerBodySkeleton();
void EupperBody();
void ElowerBody();


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

void Eupdate(int value)
{


    if(Ei<=150)
    {
        E_move -= 5;
        if(E_move+750 == 0)
        {
            E_move = -50 ;
        }
        glutPostRedisplay(); //Notify GLUT that the display has changed

        glutTimerFunc(3, Eupdate, 0); //Notify GLUT to call update again in 20 milliseconds

        Ei--;

    }

}

void Eshotfire()
{
    //glClear(GL_COLOR_BUFFER_BIT);


    glColor3d(1,0,0);
    //glLoadIdentity(); //Reset the drawing perspective
    //glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslatef(E_move, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2i(ECx, ECy);
    glVertex2i(ECx+5, ECy);
    glVertex2i(ECx+5, ECy+5);
    glVertex2i(ECx, ECy+5);
    glEnd();
    glPopMatrix();
    //rotateValue=5;
    glutTimerFunc(3, Eupdate, 0);





    //glFlush();        //Works only on single buffer
    //glutSwapBuffers();
}

void shotfire()
{
    //glClear(GL_COLOR_BUFFER_BIT);


    glColor3d(1,0,0);
    //glLoadIdentity(); //Reset the drawing perspective
    //glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslatef(_move, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2i(Cx, Cy);
    glVertex2i(Cx+5, Cy);
    glVertex2i(Cx+5, Cy+5);
    glVertex2i(Cx, Cy+5);
    glEnd();
    glPopMatrix();





    //glFlush();        //Works only on single buffer
    //glutSwapBuffers();
}

void update(int value)
{


    if(i<=150)
    {
        _move += 5;
        if(_move-750 == 0)
        {
            _move = -5;
        }
        glutPostRedisplay(); //Notify GLUT that the display has changed

        glutTimerFunc(2, update, 0); //Notify GLUT to call update again in 20 milliseconds

        i++;

    }

}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(5.0);




    lowerBody();

    shotfire();

    EupperBody();

    glPushMatrix();



    glTranslatef(BdnX, BdnY, 0);
    glRotatef(rotateValue,0,0,1);
    glTranslatef(-BdnX, -BdnY, 0);
    frontTheighAdjustment=BdnY;
    //lowerBodySkeleton();

    //EupperBody();
    upperBody();
    //lowerBody();



    glPopMatrix();
    // glClear(GL_COLOR_BUFFER_BIT);
    ElowerBody();
    //glLoadIdentity();
    Eshotfire();

    //frontTheigh();

    glutSwapBuffers();
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

void rotateCheck()
{
    rotateValue=(rotateValue==0)?30:0;
}

void ErotateCheck()
{
    ErotateValue=(ErotateValue==0)?30:0;
}

void SpecialKey(int key,int xx, int yy)
{

    switch(key)
    {

    case GLUT_KEY_UP:
        Ay+=50;
        BupY+=50;
        BdnY+=50;
        Cy+=50;
        Ey+=50;
        Fy+=50;
        //rotateCheck();
        glutPostRedisplay();
        break;

    case GLUT_KEY_DOWN:
        Ay-=50;
        BupY-=50;
        BdnY-=50;
        Cy-=50;
        Ey-=50;
        Fy-=50;
        //rotateCheck();
        glutPostRedisplay();
        break;
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
            glutTimerFunc(2, update, 0); //Add a timer


            rotateValue=5;

            glutPostRedisplay();

            i=0;

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
    glutInitWindowPosition (100, 150);
    glutCreateWindow ("Texas Duel");

    myInit ();


    glutMouseFunc(myMouse);
    glutDisplayFunc(myDisplay);
    glutSpecialFunc(SpecialKey);
    glutMainLoop();
    return 0;
}
