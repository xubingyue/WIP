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