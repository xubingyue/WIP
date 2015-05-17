#include <Floekr2d/Floekr2d.h>
using namespace Floekr2d;

#define ESC_KEY 27

f2Space* space;
const int32 width = 1334;
const int32 height = 750;
const int32 pad = 10;

void Mouse(int button, int state, int x, int y)
{
    x /= 10.0f;
    y /= 10.0f;

    if(state == GLUT_DOWN)
    {
        switch(button)
        {
        case GLUT_LEFT_BUTTON:
        {
                                 
                                 f2PolygonShape* polygon = (f2PolygonShape*) space->createShape(f2Shape::e_polygon);

                                 uint32 count = (uint32) f2Random(3, F2_MAX_POLYVERTEXCOUNT);
                                 math::f2Vector2f *v = new math::f2Vector2f[count];

                                 float32 e = f2Random(5, 10);
                                 for(uint32 i = 0; i < count; ++i)
                                     v[i].set(f2Random(-e, e), f2Random(-e, e));

                                 polygon->setVertices(v, count);
                                 polygon->setPosition(x, y);
                                 polygon->setDensity(1.0f);

                                 f2Body* b = space->createBody();
                                 b->setShape(polygon);
                                 b->setRadians(f2Random(-PI, PI));
                                 b->restitution = 0.2f;
                                 b->dynamicFriction = 0.9f;
                                 b->staticFriction = 0.8f;
                                 delete[] v;
                                 break;
        }
        case GLUT_RIGHT_BUTTON:
        {
                                  f2CircleShape* circle = (f2CircleShape*) space->createShape(f2Shape::e_circle);
                                  circle->setRadius(f2Random(1.0f, 3.0f));
                                  circle->setPosition(x, y);
                                  circle->setDensity(1.0f);

                                  f2Body* body = space->createBody();
                                  body->setShape(circle);
                                  //body->setCollisionFeedBack(false);
                                  break;
        }
        }
    }
}

void Keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
    case ESC_KEY:
        exit(0);
        break;
    }
}

void PhysicsLoop(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    plugin::f2Renderer* renderer = &plugin::f2Renderer::getRenderer();

    renderer->drawString("Left click to spawn a polygon", 1, 2);
    renderer->drawString("Right click to spawn a circle", 1, 4);
    
    space->step();

    for(int32 i = 0; i < space->getBodyList().size(); i++)
    {
        renderer->drawShape(space->getBodyList()[i]->getShape());
    }

    for(int32 i = 0; i < space->getBodyList().size(); i++)
    {
        f2Body* b = space->getBodyList()[i];
        math::f2Vector2f p = b->getPosition();

        if(p.x > width + pad || p.x < 0 - pad)
        {
            if(p.y < 0 - pad || p.y > height + pad)
            {
                space->deleteBody(b);
            }

        }
    }

    Sleep(1000.0f / 70.0f);

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_DOUBLE);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(width, height);
    glutCreateWindow("Floekr2d");
    glClearColor(0.9, 0.9, 0.9, 0.0);
    glutDisplayFunc(PhysicsLoop);
    glutIdleFunc(PhysicsLoop);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width / 10, height / 10, 0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glutKeyboardFunc(Keyboard);
    glutMouseFunc(Mouse);

    space = new f2Space();
    space->setGravity(0.0, 50.0f);
    space->setIteration(4);

    f2PolygonShape* poly = (f2PolygonShape*) space->createShape(f2Shape::e_polygon);
    poly->setAsBox(30.0f, 1.0f);
    poly->setDensity(0.0f);
    poly->setPosition(40, 55);
    
    f2Body* body = space->createBody();
    body->setShape(poly);
    body->setRadians(0.0f);

    f2PolygonShape* poly1 = (f2PolygonShape*) space->createShape(f2Shape::e_polygon);
    poly1->setAsBox(20.0f, 10.0f);
    poly1->setPosition(30, 20);

    f2Body* body1 = space->createBody();
    body1->setShape(poly1);
    body1->setRadians(0.0f);

    srand(1);
    glutMainLoop();

    return 0;
}
