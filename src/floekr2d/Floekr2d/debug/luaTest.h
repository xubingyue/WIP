#include <Floekr2d/Floekr2d.h>

#include <Floekr2d/debug/f2Input.h>
#include <Floekr2d/plugin/lua/src/lua.hpp>

using namespace Floekr2d;

f2Space* space;
const int32 width = 960;
const int32 height = 640;
const int32 pad = 10;

f2Input input;
bool useCommand = false;
lua_State* state;

static void luaStackDump(lua_State* state)
{
    cout << "\ndump start\n" << endl;
    for(int i = 1; i <= lua_gettop(state); i++)
    {
        int t = lua_type(state, i);
        switch(t)
        {
        case LUA_TNUMBER:
            printf("number:%g\n", lua_tonumber(state, i));
            break;
        case LUA_TBOOLEAN:
            printf(lua_toboolean(state, i) ? "true\n" : "false\n");
            break;
        case LUA_TSTRING:
            printf("string:%s\n", lua_tostring(state, i));
            break;
        default:
            printf("typename:%s\n", lua_typename(state, t));
            break;
        }
    }
    cout << "\ndump end\n" << endl;
}

char* lua_command(lua_State* state, char* c)
{
    lua_getglobal(state, "command");

    lua_pushstring(state, c);

    // 调用lua函数 参数个数 / 返回值个数
    lua_call(state, 1, 1);

    // 从栈顶读取返回值
    const char* luaReturned = lua_tostring(state, -1);

    // const char* to char*
    char* luaSays = new char[F2_MAX_INPUT];
    strcpy(luaSays, luaReturned);

    lua_pop(state, 1);

    return luaSays;
}

void luaInit()
{
    state = luaL_newstate();

    static const luaL_Reg lualibs[] =
    {
        {"base", luaopen_base},
        // 数据交换io库
        {"io", luaopen_io},
        {NULL, NULL}
    };

    const luaL_Reg* lib = lualibs;
    for(; lib->func != NULL; lib++)
    {
        luaL_requiref(state, lib->name, lib->func, 1);
        lua_pop(state, 1);
    }

    int status = luaL_loadfile(state, "../../Floekr2d/debug/f2LuaTest.lua");

    if(status == LUA_OK)
        printf("lua 加载成功\n");
    else if(status == LUA_ERRSYNTAX)
        printf("lua 存在语法错误\n");
    else
        printf("lua 加载失败\n");
}

void luaRun()
{
    // 压栈全局变量
    lua_pcall(state, 0, LUA_MULTRET, 0);

    if(useCommand)
        printf("lua says:%s \n", lua_command(state, input.getInputChar()));
}

void mouseCallback(int button, int state, int x, int y)
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
                                 b->dynamicFriction = 0.2f;
                                 b->staticFriction = 0.4f;
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

void keyboardCallback(unsigned char key, int x, int y)
{
    if(key == 27)
        exit(0);

    int mod = glutGetModifiers();

    switch(key)
    {
    case '\r':
        luaRun();
        input.clear();
        //printf("命令已发送至 lua\n");
        break;
        // 组合键
    case 'f':
        if(mod == GLUT_ACTIVE_ALT)
            useCommand = !useCommand;
        break;
        // backspace
    case 8:
        if(useCommand)
            input.deleteChar();
        break;

    default:
        if(useCommand)
            input.addChar(key);
        break;
    }
}

void physicsLoop(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    space->step();

    plugin::f2Renderer* renderer = &plugin::f2Renderer::getRenderer();
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

    if(useCommand)
    {
        glColor3f(0.05, 0.05, 0.05);
        glBegin(GL_POLYGON);// GL_POLYGON制定绘制的是多边形

        //指定要绘制的物体（此处为包含4个顶点的多边形）

        glVertex3f(0, height / 10, 0.0);//指定顶点，X=0.25 Y=0.25 Z=0.0

        glVertex3f(width / 10, height / 10, 0.0);

        glVertex3f(width / 10, height / 10 - 3, 0.0);

        glVertex3f(0, height / 10 - 3, 0.0);

        glEnd();


        plugin::f2Renderer* renderer = &plugin::f2Renderer::getRenderer();

        const char* command = input.getInputChar();
        renderer->drawString("Say something to f2Lua:", 1, height / 10 - 1, 0.85, 0.85, 0.85);
        renderer->drawString(command, 22, height / 10 - 1, 0.85, 0.85, 0.85);
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
    glutDisplayFunc(physicsLoop);
    glutIdleFunc(physicsLoop);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width / 10, height / 10, 0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glutKeyboardFunc(keyboardCallback);
    glutMouseFunc(mouseCallback);

    input.initInput();
    // lua
    luaInit();

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

    glutMainLoop();

    getchar();
    return 0;
}