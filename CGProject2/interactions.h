#ifndef INTERACTIONS_H
#define INTERACTIONS_H

namespace Interactions {

    extern GLsizei WINDOW_WIDTH;
    extern GLsizei WINDOW_HEIGHT;

    void handleMouseEvent(int button, int state, int x, int y);
    void handleMotionEvent(int x, int y);
    void drawScene(void);
    void timer(int v);

    class Coordinate {
    public:
        GLfloat size = 10;
        GLfloat coords[2];
        bool first_point = false;

        Coordinate(GLfloat x, GLfloat y) {
            coords[0] = x; coords[1] = y;
        }
        Coordinate() {};

        void drawPoint();

        void setCoord(GLfloat x, GLfloat y) {
            coords[0] = x; coords[1] = y;
        }
    };

    class Polygon {
    public:

        std::vector<Coordinate> vertices;
        int vert_count = 0;
        bool is_rotating = true;
        bool is_being_scaled = false;

        Polygon(int v_count, std::vector<Coordinate> v) {
            vertices = v;
            vert_count = v_count;
        }

        Polygon() {};

        void drawPolygon();
    };

}
#endif