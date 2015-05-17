#ifndef F2_RENDERER_H
#define F2_RENDERER_H

#include <Floekr2d/protected/f2Settings.h>
//#include <Floekr2d/plugin/glut.h>
//#include <GL/glut.h>
#include <Floekr2d/plugin/gl/src/glew.h>
#include <Floekr2d/plugin/gl/src/glut.h>


// 插件可以删除 并不会对整体带来影响
namespace Floekr2d
{
    class f2Shape;
    class f2Body;
    class f2CircleShape;
    class f2PolygonShape;
    namespace plugin
    {
        class f2Renderer
        {
        public:
            static f2Renderer& getRenderer();

            void drawShape(f2Shape* shape, float32 r = 0.0f, float32 b = 0.0f, float32 g = 0.0f);

            void drawString(const char *s, int32 x, int32 y, float32 r = 0.0f, float32 b = 0.0f, float32 g = 0.0f);

        private:
            void drawCircle(f2CircleShape* circle, float32 r = 0.0f, float32 b = 0.0f, float32 g = 0.0f);

            void drawPolygon(f2PolygonShape* polygon, float32 r = 0.0f, float32 b = 0.0f, float32 g = 0.0f);


            // 不可删除 不可复制 不可自己创建实例
            // --!倘若不使用renderer即便是include此plugin也不会对最终引擎的内存占用造成额外的增长
            // --!除非手动调用getRenderer()那么将会自动在程序开始时创建static的renderer
            f2Renderer();
            f2Renderer(const f2Renderer&) {};
            ~f2Renderer() {};
            f2Renderer& operator=(const f2Renderer& generator) const {};
        };
    }
}

#endif