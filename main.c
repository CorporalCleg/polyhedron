#include <GL/freeglut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>

void display(); 
void reshape(int, int);
void timer(int);
void processNormalKeys(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);

float rx = 0;
float ry = 0;
float rz = -10;
float angle_x = 0;
float angle_y = 0;
float angle_z = 0;
float sc = 1;
int n = 7;

typedef struct vector{
    float x;
    float y;
    float z;
}vector;

void init()
{
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glEnable(GL_DEPTH_TEST);
    
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowPosition(200, 200);
    glutInitWindowSize(900, 900);

    glutCreateWindow("win-1");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(processNormalKeys);
    glutMouseFunc(mouse);

    init();

    glutMainLoop();
    return 0;
}



void display()
{    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(rx, ry, rz);///here
    glRotatef(angle_x, 1, 0, 0);
    glRotatef(angle_y, 0, 1, 0);
    glRotatef(angle_z, 0, 0, 1);
    glScalef(sc, sc, sc);
    //glPointSize(6.0);
    //draw

    vector a[n];
    int i;
    for(i = 0; i < n-2; i++){
        a[i].x = cos(2*3.1415*i/(n-2));
        a[i].y = sin(2*3.1415*i/(n-2));
        a[i].z = 0;
        
    }
    
    a[n-2].x = a[0].x;
    a[n-2].y = a[0].y;
    a[n-2].z = a[0].z;
    vector v;
    v.x = 0;
    v.y = 0;
    v.z = 1;

    glBegin(GL_POLYGON);
    
    for(i = 0; i < n-1; i++)
    {
        glColor3f(0.3, 0, 0.9);
        glVertex3f(a[i].x, a[i].z, a[i].y);
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    
    for(i = 0; i < n-2; i++)
    {
        glColor3f(1 - i/(1.0*(n-1)), i/(1.0*(n-1)), 0.5);
        glVertex3f(a[i].x, a[i].z, a[i].y);
        glVertex3f(a[i+1].x, a[i+1].z, a[i+1].y);
        glVertex3f(v.x, v.z, v.y);
    }
    glEnd();///here
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 2, 50);
    glMatrixMode(GL_MODELVIEW);

}
void timer(int k)///here
{
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);
}
void mouse(int button, int state, int x, int y)
{
    // Save the left button state
    if (button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
            if(y >= 700 &&(x > 200 && x < 700))
                angle_x+=10;
            else if(y < 200  && (x > 200 && x < 700))
                angle_x-=10;
            if(x >= 700  &&(y > 200 && y < 700))
                angle_z-=10;
            else if(x < 200  &&(y > 200 && y < 700))
                angle_z+=10;

    }

    /*else if (button == GLUT_RIGHT_BUTTON)
    {
        leftMouseButtonDown = (state == GLUT_DOWN);
        zMovement -= 0.1f;
    }*/

    // Save the mouse position
    ///mouseXPos = x;
    ///mouseYPos = y;
}
void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 'a')
		rx+=1;
    else if (key == 'd')
		rx-=1;
    else if (key == 'w')
		rz+=1;
    else if (key == 's')
		rz-=1;
    else if (key == 'q')
		ry+=1;
    else if (key == 'e')
		ry-=1;
    else if (key == '+')
    {
        sc*=2;
    }
    else if (key == '-')
    {
        sc*=0.5;
    }
    else if (key == '2')
    {
        angle_y +=1;
    }
    else if (key == '3')
    {
        angle_z +=1;
    }
    else if (key == '1')
    {
        angle_x +=1;
    }
    else
        exit(0);///here
    glutPostRedisplay();
}