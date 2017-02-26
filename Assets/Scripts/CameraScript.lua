require("class")

ScriptComponent = class()

zoomStep = 0.75
yawStep = 0.25
pitchStep = 0.25

function ScriptComponent:Update(this)
    if Merlin.InputManager.GetKey("CameraZoomIn") then
		Merlin.Graphics.GetCamera():Zoom(-zoomStep)
	end
	-- Exercise 8.5
		if Merlin.InputManager.GetKey("CameraZoomOut") then
		Merlin.Graphics.GetCamera():Zoom(zoomStep)
   	end
	-- Exercise 8.6
	if Merlin.InputManager.GetKey("CameraYawLeft") then
		Merlin.Graphics.GetCamera():Yaw(yawStep)
	end
   	if Merlin.InputManager.GetKey("CameraYawRight") then
		Merlin.Graphics.GetCamera():Yaw(-yawStep)
	end
   	if Merlin.InputManager.GetKey("CameraPitchUp") then
		Merlin.Graphics.GetCamera():Pitch(-pitchStep)
   	end
	if Merlin.InputManager.GetKey("CameraPitchDown") then
		Merlin.Graphics.GetCamera():Pitch(pitchStep)
	end
end


