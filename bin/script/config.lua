local app = require "lib"
local CameraObject = require "CameraObject"
local System = require "System"
local SceneLoader = require "SceneLoader"
local UI = require "UIMaster"

local Config = {}

function Config.config()
	local ret = false
	ret = app.create_window("WIP Demo",1280,720)
	if ret==false then
		print("Lua:create window failed!")
	end
	System.init()
	
	camera = CameraObject:new(1280,720)
	app.app_add_camera(camera.camera_ptr)
	camera:moveWorldTo(0,0)
	camera:moveScreenTo(0,0)
	app.camera_set_screen_size(camera.camera_ptr,1280,720)
	
	SceneLoader.load_scene("./resources/scene.xml")
	
	--SceneLoader.load_scene("./resources/scene.xml")
	return ret
end

return Config