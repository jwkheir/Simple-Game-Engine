require("class")

ScriptComponent = class()

rotationSpeed = 0.1

function ScriptComponent:Update(this)
	angle = Merlin.InputManager.GetAxis("Xaxis") * rotationSpeed
	this:GetTransform():RotateAboutY(angle)
end
