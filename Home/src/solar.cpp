#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <string>

// Planet class to encapsulate properties and behaviors of each planet
class Planet {
public:
    Planet(float orbitRadius, float orbitSpeed, float size, const std::string& name, const float color[3])
        : orbitRadius(orbitRadius), orbitSpeed(orbitSpeed), size(size), name(name), angle(0.0f) {
        this->color[0] = color[0];
        this->color[1] = color[1];
        this->color[2] = color[2];
    }

    void updatePosition() {
        angle += orbitSpeed;
        if (angle > 2 * M_PI) angle -= 2 * M_PI;
    }

    void draw() const {
        float x = orbitRadius * cos(angle);
        float z = orbitRadius * sin(angle);

        // Set the color for the planet and draw it
        glPushMatrix();
        glTranslatef(x, 0.0f, z);
        glColor3fv(color); 
        glutSolidSphere(size, 30, 30);
        glPopMatrix();

        // Draw the label slightly above the planet
        drawLabel(x, size + 0.2f, z);
    }

    void drawOrbitRing() const {
        glColor3f(0.3f, 0.3f, 0.3f);  // Dark gray for the orbit ring
        glBegin(GL_LINE_LOOP);
        for (int j = 0; j < 100; ++j) {
            float angle = 2.0f * M_PI * j / 100;
            float x = orbitRadius * cos(angle);
            float z = orbitRadius * sin(angle);
            glVertex3f(x, 0.0f, z);
        }
        glEnd();
    }

private:
    float orbitRadius;
    float orbitSpeed;
    float size;
    float angle;
    float color[3];
    std::string name;

    void drawLabel(float x, float y, float z) const {
        glColor3f(0.0f, 0.0f, 0.0f);  // Black color for text labels
        glRasterPos3f(x, y, z);
        for (char c : name) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        }
    }
};

// SolarSystem class to manage the planets and the overall system
class SolarSystem {
public:
    SolarSystem() {
        float mercuryColor[3] = {0.4f, 0.4f, 0.4f};  // Dark gray
        float venusColor[3] = {0.8f, 0.4f, 0.1f};    // Brownish-orange
        float earthColor[3] = {0.0f, 0.3f, 0.8f};    // Dark blue
        float marsColor[3] = {0.7f, 0.2f, 0.2f};     // Dark red
        float jupiterColor[3] = {0.6f, 0.5f, 0.2f};  // Dark yellow-brown
        
        planets.push_back(Planet(1.5f, 0.02f, 0.3f, "Mercury", mercuryColor));
        planets.push_back(Planet(2.5f, 0.015f, 0.4f, "Venus", venusColor));
        planets.push_back(Planet(3.5f, 0.01f, 0.5f, "Earth", earthColor));
        planets.push_back(Planet(4.5f, 0.008f, 0.45f, "Mars", marsColor));
        planets.push_back(Planet(5.5f, 0.005f, 0.6f, "Jupiter", jupiterColor));
    }

    void update() {
        for (Planet& planet : planets) {
            planet.updatePosition();
        }
    }

    void draw() const {
        // Draw the Sun in orange
        glColor3f(1.0f, 0.6f, 0.0f);
        glutSolidSphere(1.0, 50, 50);

        // Draw each planet's orbit ring and planet itself
        for (const Planet& planet : planets) {
            planet.drawOrbitRing();
            planet.draw();
        }
    }

private:
    std::vector<Planet> planets;
};

// Global instance of SolarSystem
SolarSystem solarSystem;

// Lighting setup
void setupLighting() {
    GLfloat light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0f, 5.0f, 15.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    
    // Draw the entire solar system
    solarSystem.draw();
    
    glutSwapBuffers();
}

// Update function for animation
void update(int value) {
    solarSystem.update();
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);  // Approx. 60 FPS
}

// Initialize OpenGL settings
void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // Set the background to white
    glEnable(GL_DEPTH_TEST);
    setupLighting();
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.0, 1.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Solar System Simulation");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);

    glutMainLoop();
    return 0;
}
