#include <Floekr2d/plugin/f2Renderer.h>
#include <Floekr2d/public/f2Body.h>

#include <Floekr2d/public/shape/f2PolygonShape.h>
#include <Floekr2d/public/shape/f2CircleShape.h>

namespace Floekr2d
{
    namespace plugin
    {
        f2Renderer::f2Renderer()
        {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glEnable(GL_BLEND);

            glEnable(GL_POINT_SMOOTH);

            glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

            glEnable(GL_LINE_SMOOTH);

            glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

            glEnable(GL_POLYGON_SMOOTH);

            glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
        }

        f2Renderer& f2Renderer::getRenderer()
        {
            static f2Renderer renderer;
            return renderer;
        }

        void f2Renderer::drawShape(f2Shape* shape, float32 r, float32 b, float32 g)
        {
            f2Shape::shapeType type = shape->getType();
            switch(type)
            {
            case f2Shape::e_circle:
                drawCircle((f2CircleShape*)shape, r, g, b);
                break;

            case f2Shape::e_polygon:
                drawPolygon((f2PolygonShape*) shape, r, g, b);
                break;

            default:
                f2Log("无法找到该body的shape类型:%d 无法绘制", type);
                break;
            }
        }

        void f2Renderer::drawCircle(f2CircleShape* circle, float32 r, float32 b, float32 g)
        {
            // --!以下代码可以直接修改为特定平台的绘制函数

            const uint32 k_segments = 30;

            // 多边形逼近圆形
            glColor3f(r, g, b);
            glBegin(GL_LINE_LOOP);
            float32 theta = circle->getRadians();
            float32 inc = PI * 2.0f / (float32) k_segments;
            for(uint32 i = 0; i < k_segments; ++i)
            {
                theta += inc;
                math::f2Vector2f p(f2Cos(theta), f2Sin(theta));
                p *= circle->getRadius();
                p += circle->getPosition();
                glVertex2f(p.x, p.y);
            }
            glEnd();

            // 一个圆连带一根线 用于判别朝向
            glBegin(GL_LINE_STRIP);
            math::f2Vector2f radius(0, 1.0f);
            float32 c = f2Cos(circle->getRadians());
            float32 s = f2Sin(circle->getRadians());
            radius.set(radius.x * c - radius.y * s, radius.x * s + radius.y * c);
            radius *= circle->getRadius();
            radius = radius + circle->getPosition();
            glVertex2f(circle->getPosition().x, circle->getPosition().y);
            glVertex2f(radius.x, radius.y);
            glEnd();
        }

        void f2Renderer::drawPolygon(f2PolygonShape* polygon, float32 r, float32 b, float32 g)
        {
            // 以下代码可以修正为特定平台
            //glPolygonMode(GL_FRONT, GL_FILL);
            glColor3f(r, g, b);
            glBegin(GL_LINE_LOOP);
            for(uint32 i = 0; i < polygon->getVertexCount(); ++i)
            {
                math::f2Vector2f v = polygon->getPosition() + polygon->getOrient() * polygon->getVertice(i);
                glVertex2f(v.x, v.y);
            }
            glEnd();
        }

        void f2Renderer::drawString(const char *s, int32 x, int32 y, float32 r, float32 b, float32 g)
        {
            glColor3f(r, g, b);
            glRasterPos2i(x, y);
            uint32 l = (uint32) std::strlen(s);
            for(uint32 i = 0; i < l; ++i)
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *(s + i));
        }

    }
}