#include <GL/glut.h>
#include <vector>
#include "interactions.h"
#include "commonLibs.h"

using namespace Interactions;

Circle circle;
bool polygon_created = false;
bool initializing = true;
bool changeDirection = false;
bool freeFromRow = false;
float forceStrength = 5.0;
float force[] = { 0, 0 };

/*
 * Callback function for mouse events, also handling modifier key presses.
 * Currently handling left click up, left click down, shift+left click, alt+left click
 * and right click down.
 */
void Interactions::handleMouseEvent(int button, int state, int x, int y) {

    // bool variable created to help with readability of the if statments
    bool left_click_down = (button == GLUT_LEFT_BUTTON  && state == GLUT_DOWN);
    bool left_click_up   = (button == GLUT_LEFT_BUTTON  && state == GLUT_UP);
    bool right_click_up  = (button == GLUT_RIGHT_BUTTON && state == GLUT_UP);   
    
    // Handling points when the mouse clicks in the window
    if (left_click_down) {
        if (initializing) {
            force[0] = forceStrength;
            circle.applyForce(force);
            initializing = !initializing;
        }
        else if (!freeFromRow) {
            float t = force[0];
            force[0] = -t;
            circle.applyForce(force); // stop
            force[0] = t;
            force[1] = -forceStrength;
            circle.applyForce(force);
            freeFromRow = !freeFromRow;
        }
    }
    // Closes current window
    if (right_click_up) exit(0);

    glutPostRedisplay();
}
/**
 * Reverses the X direction of the circle
 */
void reverseX() {
    float x = force[0];
    float y = force[1];
    force[0] = -x;
    force[1] = -y;
    circle.applyForce(force); // STOP
    force[1] = y;
    circle.applyForce(force); // CONTINUE
}
/**
 * Reverses the Y direction of the circle
 */
void reverseY() {
    float x = force[0];
    float y = force[1];
    force[0] = -x;
    force[1] = -y;
    circle.applyForce(force); // STOP
    force[0] = x;
    circle.applyForce(force); // CONTINUE
}
/**
 * Check for collisions with the window boundaries, 
 * offset to account for overstep, and reverse the
 * direction of the object
 */
void handleCollisions() {
    float xmin = circle.getRadius()
        , xmax = WINDOW_WIDTH - circle.getRadius()
        , ymin = circle.getRadius()
        , ymax = WINDOW_HEIGHT - circle.getRadius()
        , x = circle.getPosition().coords[0]
        , y = circle.getPosition().coords[1]
        , xCorrection = int(x < xmin) * (xmin - x) + int(x > xmax) * (xmax - x)
        , yCorrection = int(y < ymin) * (ymin - y) + int(y > ymax) * (ymax - y);
    if (xCorrection != 0 || yCorrection != 0) {
        changeDirection = true;
        circle.translate(xCorrection, yCorrection);
        if(x < xmin || x > xmax) reverseX();
        if(y < ymin || y > ymax) reverseY();
    }    
}
/*
 * Function to be passed to glutDisplayFunc
 * Draws either a point or if polygon_created is true, a Polygon.
 */
void Interactions::drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (!polygon_created) {
        float radius = WINDOW_HEIGHT / 12.0;
        Interactions::Coordinate initialPosition = Interactions::Coordinate(WINDOW_WIDTH/2.0, radius);
        circle = Circle(initialPosition, radius);
        circle.drawCircle(1,1,1);
        polygon_created = true;
    }
    else {
        circle.drawCircle(1,1,1);
    }

    glFlush();
}

/*
 * Timer callback function to be passed to glutTimerFunc. Increments 
 * rotation_angle by 1 every frame.
 * resetting back to 0 once it hits 360 degrees,
 * Currently running at 60fps
 */
void Interactions::timer(int v) {
    if (polygon_created) {
        circle.update();      
        handleCollisions();
        glutPostRedisplay();
    }
    glutTimerFunc(1000 / 60, timer, v);
}