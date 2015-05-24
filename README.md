![WIP](https://github.com/wubugui/WIP/blob/master/pic/pic.bmp)
##是什么?
他是一个简单的2D游戏引擎,初学游戏开发的时候写的。
现在正在使用WPF实现一个编辑器工具。


##有哪些功能?
* 数据驱动的游戏对象系统
* 基于Lua的脚本编程
* 相对完善的系统
* 刚体物理

##能干嘛?
可以尝试使用他来做游戏，但是由于他没有编辑器，所以相当麻烦。

我更多时候是在学习的时候使用他来做一些demo。

下面是截图：

![骨骼动画](https://github.com/wubugui/WIP/blob/master/pic/1%20(1).png)

![关节动画](https://github.com/wubugui/WIP/blob/master/pic/1%20(2).png)

![AI寻路](https://github.com/wubugui/WIP/blob/master/pic/1%20(3).png)

![Transform](https://github.com/wubugui/WIP/blob/master/pic/1%20(4).png)

![刚体物理](https://github.com/wubugui/WIP/blob/master/pic/1%20(5).png)

![一个场景](https://github.com/wubugui/WIP/blob/master/pic/1%20(6).png)

![UI和音乐](https://github.com/wubugui/WIP/blob/master/pic/1%20(7).png)

![Spine骨骼动画](https://github.com/wubugui/WIP/blob/master/pic/1%20(8).png)


##如何编译
* 下载依赖项[Deps](http://pan.baidu.com/s/1kTra999)解压覆盖到./
* 用VS2012打开./src/wip/wip.sln
* 生成即可。

如果使用其他版本的VS可能需要从新编译lib。

##如何使用
1、在xml中构建场景，例如

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<wip version="0.125">
    <scene>
		<total type="n">1</total>
		<e1>
			<name type="s">player</name>
			<active type="b">true</active>
			<type type="s">object</type>
			<Sprite>
				<active type="b">true</active>
				<texture type="s">resources/bg.jpg</texture>
			</Sprite>
			<Transform>
				<active type="b">true</active>
				<x type="n">640</x>
				<y type="n">360</y>
				<rad type="n">0</rad>
				<sx type="n">1</sx>
				<sy type="n">1</sy>
				<z_order type="n">8</z_order>
			</Transform>
			<Animation>
				<active type="b">true</active>
				<auto type="b">false</auto>
			</Animation>
			<Collider>
				<active type="b">false</active>
				<type type="s">GHOST</type>
				<cx type="n">0</cx>
				<cy type="n">0</cy>
				<w type="n">12</w>
				<h type="n">12</h>
			</Collider>
			<Mesh>
				<active type="b">true</active>
				<w type="n">1280</w>
				<h type="n">720</h>
				<cx type="n">0.5</cx>
				<cy type="n">0.5</cy>
			</Mesh>
			<components>
				<n type="n">1</n>
				<e1 type="s">UIDemo</e1>
				<UIDemo>
					<active type="b">true</active>
					<n type="n">0</n>
					<e1 type="s">resource</e1>
					<e2 type="s">volume</e2>
					<e3 type="s">loop</e3>
					<resource type="s">../Resources/test.ogg</resource>
					<volume type="n">100</volume>
					<loop type="b">true</loop>
				</UIDemo>
			</components>
		</e1>
	</scene>
</wip>
```
上述代码构建了如下场景，具体使用见文档 https://github.com/wubugui/WIP/wiki

2、参考API手册，为对象编使用Lua写自定义组件，例如上面的UIDemo组件，下面是一个简单的Drag组件的代码

```cpp
local BaseComponent = require "BaseComponent"
local app = require "lib"
local Input = require "Input"
local Utilities = require "Utilities"
local System = require "System"
local Drag = BaseComponent:new()

function Drag:new()
    local o = {}
	setmetatable(o,self)
	self.__index = self

	--add data member here
	o.camera = nil
	o.px = 0
	o.py = 0
	return o
end

function Drag:init()

end

function Drag:game_init()
	self.camera = camera
	--app.sprite_set_position(self.host_obj.sprite_ptr,0,0)
	app.collider_set_density(self.host_obj.Collider.collider_ptr,0.001)
end

function Drag:update(dt)

end

function Drag:game_exit()

end

function Drag:exit()

end

return Drag
```

3、安装./bin中的oalinst.exe文件，这是OpenAL。

4、运行./bin/wip.exe，查看效果.

5、你可以通过修改源代码，来修改或者添加LuaAPI，方法如下：

[LuaAPI修改方法](https://github.com/wubugui/WIP/wiki/%E4%BF%AE%E6%94%B9%E6%B7%BB%E5%8A%A0LuaAPI)


具体请参考：

[使用方法](https://github.com/wubugui/WIP/wiki/%E5%88%9B%E5%BB%BA%E4%B8%80%E4%B8%AA%E7%AE%80%E5%8D%95%E7%9A%84%E5%9C%BA%E6%99%AF)

##文件结构

下面要对几个关键的文件做说明：

./bin/是可执行文件是可以独立运行。

./bin/engine/script/存放引擎自带的脚本文件，这些文件一般不需要修改，自定义的脚本都在./bin/script中，其中只有config.lua是必须的文件，这个文件确定了一些初试化参数。

./bin/resources/存放资源，一般没有特别的规定，./bin/resources/UI是默认的UI素材，自定义UI的时候才会去修改。

##资源下载
[Demo下载](http://pan.baidu.com/s/1hq3XNX6)

[组件生成器](http://pan.baidu.com/s/1jG5VFIu)

##关于作者
```cpp
#include "author.h"
Author me;
me.name = "乌不归";
me.e_mail = "wubuguiqazwsx@126.com";
me.site = "http://www.cnblogs.com/wubugui/";

```
欢迎批评指导吐槽。

##Any More
[OSC镜像](https://git.oschina.net/JustKiss/WIPEngine)
