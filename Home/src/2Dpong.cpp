#include <GL/glut.h>
#include <iostream>

using namespace std;

// Game state variables
float paddle1Y = 0.0f;
float paddle2Y = 0.0f;
float ballX = 0.0f;
float ballY = 0.0f;
float ballDirX = 0.02f;
float ballDirY = 0.01f;

// Function to draw a rectangle
void drawRect(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

// Function to draw the paddles and ball
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw paddles
    glColor3f(1.0f, 0.0f, 0.0f);
    drawRect(-0.9f, paddle1Y, 0.05f, 0.2f);
    drawRect(0.85f, paddle2Y, 0.05f, 0.2f);

    // Draw ball
    glColor3f(0.0f, 1.0f, 0.0f);
    drawRect(ballX, ballY, 0.05f, 0.05f);

    glutSwapBuffers();
}

// Function to update the game state
void update(int value) {
    // Update ball position
    ballX += ballDirX;
    ballY += ballDirY;

    // Check for collision with paddles
    if (ballX < -0.85f && ballY > paddle1Y && ballY < paddle1Y + 0.2f) {
        ballDirX = -ballDirX;
    }
    if (ballX > 0.8f && ballY > paddle2Y && ballY < paddle2Y + 0.2f) {
        ballDirX = -ballDirX;
    }

    // Check for collision with top and bottom walls
    if (ballY > 1.0f || ballY < -1.0f) {
        ballDirY = -ballDirY;
    }

    // Check for scoring
    if (ballX > 1.0f || ballX < -1.0f) {
        ballX = 0.0f;
        ballY = 0.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// Function to handle keyboard input
void handleKeys(unsigned char key, int x, int y) {
    if (key == 'w') {
        paddle1Y += 0.1f;
    } else if (key == 's') {
        paddle1Y -= 0.1f;
    } else if (key == 'i') {
        paddle2Y += 0.1f;
    } else if (key == 'k') {
        paddle2Y -= 0.1f;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Pong Game");

    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeys);
    glutTimerFunc(16, update, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glutMainLoop();
    return 0;
}