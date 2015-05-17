local app = require "lib"
local UIBase = require "UIBase"

--[[
this class has __gc
and
callback is called in lua due to callback state
callback state decid if to call the callback 
and 
maybe if to draw the button is decided in lua
--]]
local SwitchWidget = UIBase:new()

function SwitchWidget:new(o)
	local o = o or {}
	setmetatable(o,self)
	self.__index = self
	return o
end

function SwitchWidget:init(path_down,path_move,path_normal,callback)
	
end

function SwitchWidget:update(dt)
	
end

function SwitchWidget:update_button(x,y)
	
end

function SwitchWidget:setPosition(x,y)
	
end

--x,y may be nil in most cases
function SwitchWidget:reshape(w,h,x,y)
	
end

function SwitchWidget:setSwitchState(val)
	
end

function SwitchWidget:getSwitchState()
	
end

return SwitchWidget