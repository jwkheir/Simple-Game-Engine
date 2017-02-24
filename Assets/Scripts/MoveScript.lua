--Authour: Jack Kheir
--Update 18.05.16
-- The update returns the Knight objects and acts upon that object
-- Again this can be updated so that can be added to any gameobject.
speed = 0.25

currentSpeed = 0;
require("class")

ScriptComponent = class()

function ScriptComponent:Update(this)

	------MOUSE ROTATION
	angle = Merlin.InputManager.GetAxis("Xaxis") * speed
	this:GetTransform():RotateAboutY(angle)

	-----MOVEMENT
	if Merlin.InputManager.GetKey("W") then
		Merlin.CharacterController.GetKnight():Move(speed)
	end

	if Merlin.InputManager.GetKey("S") then
		Merlin.CharacterController.GetKnight():Move(-speed)
	end

	if Merlin.InputManager.GetKey("A") then
		Merlin.CharacterController.GetKnight():Strafe(-speed)
	end

	if Merlin.InputManager.GetKey("D") then
		Merlin.CharacterController.GetKnight():Strafe(speed)
	end

	-----ROTATION
	if Merlin.InputManager.GetKey("Q") then
		Merlin.CharacterController.GetKnight():Rotate(-speed)
		--this:GetTransform():RotateAboutY(-speed)
	end

	if Merlin.InputManager.GetKey("E") then
		Merlin.CharacterController.GetKnight():Rotate(speed)
		--this:GetTransform():RotateAboutY(speed)
	end


	if not Merlin.InputManager.GetKey("W") and  not Merlin.InputManager.GetKey("S")
	and not Merlin.InputManager.GetKey("A") and not Merlin.InputManager.GetKey("D")
	and not Merlin.InputManager.GetKey("Q") and not Merlin.InputManager.GetKey("E")
	then
		Merlin.CharacterController.GetKnight():Reset()
	end
end
