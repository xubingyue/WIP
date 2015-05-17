#ifndef F2_BODY_H
#define F2_BODY_H

#include <Floekr2d/protected/f2Settings.h>
//#include <Floekr2d/private/f2Vector2.h>
#include <Floekr2d/protected/math/f2Matrix2.h>
#include <Floekr2d/protected/datastruct/f2List.h>

namespace Floekr2d
{
    class f2Shape;

    // --!允许Controller自动添加碰撞对象队列
    namespace core{ class f2ContactController; }

    // --!f2Body的实际创建工作全都是由f2Space中搭配allocator完成的
    // --!因此无需手动new / delete 相反的 这样可能会带来意想不到的错误
    class f2Body
    {
    public:
        enum f2BodyType
        {
            // 可碰撞的 不可运动 eg.地形
            e_static = 0,
            // 可碰撞的 可运动的
            e_kinematic,
            // 不可碰撞 可运动的
            e_dynamic
        };

        f2Body();

        void init();

		void setMass(float m)
		{
			mass = m;
		}


		void setInertia(float i)
		{
			inertia = i;
		}

        // setter
        // 初始化质量与转动惯量的信息
        void setShape(f2Shape* shape);

        void setPosition(math::f2Vector2f position);

        void setLinearVelocity(math::f2Vector2f linearVelocity);

        void setAngularVelocity(float32 angularVelocity);
        
        // 旋转一个物体 目前不能直接设定shape的orient 
        // --!核心为旋转该物体上绑定的形状
        void setRadians(float32 radians);

        void setType(f2BodyType type);

        // getter
        // 获得当前帧与当前物体发生碰撞的所有对象指针
        // --!允许外界对其对内容进行修改 因每帧都会重置且系统本身无需利用此进行计算
        f2List<f2Body*>& getCollideBodies();

        math::f2Matrix2f getOrient();

        math::f2Vector2f getPosition();

        math::f2Vector2f getLinearVelocity();

        math::f2Vector2f getForces();

        float32 getAngularVelocity();

        float32 getMass();

        float32 getInverseMass();

        float32 getInertia();

        float32 getInverseInertia();

        float32 getRadians();

        float32 getTorque();

        f2Shape* getShape();

        f2BodyType getType();

        // 提供接口判断body类型
        bool isKinematic();

        bool isDynamic();
        
        bool isStatic();

        // 施加力与冲量
        void applyForce(const math::f2Vector2f& force);
		void applyForce(float32 x,float32 y);


        void applyImpulse(const math::f2Vector2f& impulse, const math::f2Vector2f& contactVector);

        // 根据碰撞情况自动添加已碰撞对象
        void addCollideBody(f2Body* body);
        
        // 碰撞反馈 碰撞检测
        // 支持关闭碰撞反馈 / 碰撞应答
        void setCollisionDetectable(bool detectable);
        
        void setCollisionFeedBack(bool feedback);

        bool isCollisionDetectable();

        bool isCollisionFeedback();

        // 重置 进行下一步循环
        void reset();

		// 清空碰撞队列
		void clearCollideList();

        // debug
        void print();

        // 滑动摩擦系数
        float32 staticFriction;
        // 最大静摩擦系数
        float32 dynamicFriction;

        // 弹性恢复系数
        float32 restitution;

    private:
        // --!因为getCollideBodies()返回的是list的引用 能够直接改写内部的逻辑 本质与调用方法一致
        // --!因此这里就不打算封装addCollideBodies()到内部了
        //friend core::f2ContactController;

        // 线速度 角速度
        math::f2Vector2f linearVelocity;
        float32 angularVelocity;

        // 质量 转动惯量 与之倒数
        // --!直接创建body并不会生成任何质量信息 body本身也不会提供任何设定质量的相关方法
        // --!他们只会被设定为静态物体 mass = inertia = 0.0)
        // --!质量和转动惯量一定需要shape的绑定才能被特定的形状初始化 
        // --!其值与密度相关 且不同的形状所生成的质量大小都有所不同
        float32 mass, inverseMass;
        float32 inertia, inverseInertia;

        // 物体类型
        f2BodyType type;

        // 碰撞检测状态
        // --!若关闭了碰撞检测那么也会自动关闭碰撞反馈
        bool collisionDetectable;
        // 物理反馈状态
        bool collisionFeedback;

        // 物体被施加的合力与合力矩
        math::f2Vector2f force;
        float32 torque;

        // 当前帧与当前对象发生碰撞的碰撞对象队列
        f2List<f2Body*> collideBodies;

        f2Shape *shape;
    };
}

#endif