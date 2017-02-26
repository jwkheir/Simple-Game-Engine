#include "stdafx.h"
#include "Level.h"
#include "Camera.h"
#include "Knight.h"
#include "CharacterController.h"
#include "light.h"
#include "shader.h"
#include "material.h"
#include "MeshRenderer.h"
#include "CubeMesh.h"
#include "fbxMesh.h"
#include "script.h"
#include "sphereMesh.h"
#include "rigidBody.h"



namespace Merlin{

	Level::Level(string name, lua_State * L){
		// Exercise 3.4
		this->name = name;
		gameObjects = new LinkedList<GameObject>();
		physics = new Physics(gameObjects);

		Shader *materialShader = new Shader("../Assets/Shaders/PointLight.vert", "../Assets/Shaders/PointLight.frag");
		Shader *textureShader = new Shader("../Assets/Shaders/TexturedpointLight.vert", "../Assets/Shaders/TexturedPointLight.frag");

		Material * redMaterial = new Material(materialShader, NULL, Material::redPlasticMaterial);
		Material * crateMaterial = new Material(textureShader, "../Assets/Textures/crate.bmp", Material::woodMaterial);
		// Exercise 6.2
		Material * floorMaterial = new Material(textureShader, "../Assets/Textures/floor.bmp", Material::brassMaterial);
		Material * wallMaterial = new Material(textureShader, "../Assets/Textures/wall.bmp", Material::brassMaterial);
		// Exercise 6.5
		Material * tableMaterial = new Material(textureShader, "../Assets/Models/Table/Textures/tableWood.bmp", Material::woodMaterial);
		Material * ballMaterial = new Material(textureShader, "../Assets/Textures/ball.bmp", Material::whiteMattMaterial);

		GameObject * camera = new GameObject("Main Camera", "camera", glm::vec3(0, 0, 450));
		// Pass near and far planes as arguments
		Camera * cameraComponent = new Camera(camera, 0.1, 10000.0);
		camera->AddComponent(cameraComponent);
		camera->AddComponent(new Script(camera, "../Assets/Scripts/CameraScript.lua", L));
		// Assign primary camera.
		Graphics::SetMainCamera(cameraComponent);

		// Exercise 3.7
		GameObject * light = new GameObject("Light", "light", glm::vec3(0, 130, 0), glm::vec3(0, 0, 0), glm::vec3(10, 10, 10));
		light->AddComponent(new MeshRenderer(light, new CubeMesh(), crateMaterial));
		Light * lightComponent = new Light(light, Light::duskLight);
		light->AddComponent(lightComponent);
		gameObjects->Insert(light);
		Graphics::SetLight(lightComponent);

		GameObject * box = new GameObject("box", "", glm::vec3(180.0, -90.0, -100.0), glm::vec3(0, 0, 0), glm::vec3(50, 50, 50));
		box->AddComponent(new MeshRenderer(box, new CubeMesh(), crateMaterial));
		box->AddComponent(new RigidBody(box, new btBoxShape(btVector3(btScalar(1.0), btScalar(1.0), btScalar(1.0))), physics->GetPhysicsWorld(), 0));
		// Exercise 8.9
		box->AddComponent(new Script(box, "../Assets/Scripts/BoxScript.lua", L));
		gameObjects->Insert(box);

		// Exercise 5.3
		GameObject * floor = new GameObject("Floor", "room", glm::vec3(0, -150, 0), glm::vec3(0, 0, 0), glm::vec3(290, 10, 200));
		floor->AddComponent(new MeshRenderer(floor, new CubeMesh(), floorMaterial));
		// Exercise 9.2
		floor->AddComponent(new RigidBody(floor, new btBoxShape(btVector3(btScalar(1.0), btScalar(1.0), btScalar(1.0))), physics->GetPhysicsWorld(), 0));
		gameObjects->Insert(floor);

		GameObject * backWall = new GameObject("Back Wall", "room", glm::vec3(0, 0, -200), glm::vec3(0, 0, 0), glm::vec3(400, 160, 10));
		backWall->AddComponent(new MeshRenderer(backWall, new CubeMesh(), wallMaterial));
		// Exercise 9.3
		backWall->AddComponent(new RigidBody(backWall, new btBoxShape(btVector3(btScalar(1.0), btScalar(1.0), btScalar(1.0))), physics->GetPhysicsWorld(), 0));
		gameObjects->Insert(backWall);

		GameObject * rightWall = new GameObject("Right wall", "room", glm::vec3(300, 0, 0), glm::vec3(0, 0, 0), glm::vec3(10, 160, 200));
		rightWall->AddComponent(new MeshRenderer(rightWall, new CubeMesh(), wallMaterial));
		// Exercise 9.3
		rightWall->AddComponent(new RigidBody(rightWall, new btBoxShape(btVector3(btScalar(1.0), btScalar(1.0), btScalar(1.0))), physics->GetPhysicsWorld(), 0));
		gameObjects->Insert(rightWall);

		GameObject * leftWall = new GameObject("Left Wall", "room", glm::vec3(-300, 0, 0), glm::vec3(0, 0, 0), glm::vec3(10, 160, 200));
		leftWall->AddComponent(new MeshRenderer(leftWall, new CubeMesh(), wallMaterial));
		// Exercise 9.3
		leftWall->AddComponent(new RigidBody(leftWall, new btBoxShape(btVector3(btScalar(1.0), btScalar(1.0), btScalar(1.0))), physics->GetPhysicsWorld(), 0));
		gameObjects->Insert(leftWall);

		GameObject * ceiling = new GameObject("Ceiling", "room", glm::vec3(0, 150, 0), glm::vec3(0, 0, 0), glm::vec3(290, 10, 200));
		ceiling->AddComponent(new MeshRenderer(ceiling, new CubeMesh(), floorMaterial));
		// Exercise 9.3
		ceiling->AddComponent(new RigidBody(ceiling, new btBoxShape(btVector3(btScalar(1.0), btScalar(1.0), btScalar(1.0))), physics->GetPhysicsWorld(), 0));
		gameObjects->Insert(ceiling);


		//PLAYER & CHARACTER CONTROLLER
		GameObject * knight = new GameObject("Knight", "ai", glm::vec3(-100, -150, 0));
		Knight * knightComponent = new Knight(knight, 4);
		knight->AddComponent(new MeshRenderer(knight, new  FBXMesh("../Assets/Models/Peasant/Peasant_Man.fbx"), redMaterial));
		knight->AddComponent(new RigidBody(knight, new btBoxShape(btVector3(btScalar(1.0), btScalar(1.0), btScalar(1.0))), physics->GetPhysicsWorld(), 0));
		knight->AddComponent(new Script(knight, "../Assets/Scripts/MoveScript.lua", L));
		knight->AddComponent(knightComponent);
		knight->AddComponent(new CharacterController(knight, knightComponent, physics->GetPhysicsWorld()));
		gameObjects->Insert(knight);

		//// Exercise 6.5
		GameObject * table = new GameObject("Table", "furniture", glm::vec3(-250, -140, 0), glm::vec3(-90, 0, 0));
		table->AddComponent(new MeshRenderer(table, new FBXMesh("../Assets/Models/Table/Table_Wood.fbx"), tableMaterial));
		gameObjects->Insert(table);

		for (int n = 0; n < 50; n++){
			GameObject * sphere = new GameObject("Sphere", "ball", glm::vec3(-250 + (n * 5), 0, 0), glm::vec3(0, 0, 0), glm::vec3(15, 15, 15));
			sphere->AddComponent(new MeshRenderer(sphere, new SphereMesh(), ballMaterial));
			sphere->AddComponent(new RigidBody(sphere, new btSphereShape(btScalar(1.0)), physics->GetPhysicsWorld(), 10));
			gameObjects->Insert(sphere);
		}

	}

	Level::~Level(void){
		// Exercise 3.6
		delete gameObjects;
	}

	void Level::Initialise(){
		// Exercise 3.5
		// Initialise all game objects
		GameObject *obj = gameObjects->first;
		while (obj != NULL){
			obj->Initialise();
			obj = obj->next;
		}
		// Initialise camera
		Graphics::GetMainCamera()->Initialise();
	}

	void Level::Update(){
		// Update the camera first
		Graphics::GetMainCamera()->gameObject->Update();
		// Update all game objects
		GameObject *obj = gameObjects->first;
		while (obj != NULL){
			obj->Update();
			// Remove inactive GameObjects
			if (!obj->IsActive()){
				gameObjects->Delete(obj);
				GameObject *temp = obj->next;
				delete obj;
				obj = temp->next;
			}
			else {
				obj = obj->next;
			}
		}
	}


}