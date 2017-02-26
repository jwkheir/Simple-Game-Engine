#include "stdafx.h"
#include "MeshRenderer.h"
#include "GameObject.h"
#include "Graphics.h"
#include "Camera.h"



namespace Merlin{
	MeshRenderer::MeshRenderer(GameObject * gameObject, Mesh * mesh, Material * material) :Renderer(gameObject, material){
		this->mesh = mesh;

	}


	MeshRenderer::~MeshRenderer()
	{
	}

	void MeshRenderer::Initialise(){
		GLuint program = material->GetShader()->GetProgram();
		mesh->Initialise();
		// Exercise 5.2
		matMVPIdx = glGetUniformLocation(program, "MVP");
		matNIdx = glGetUniformLocation(program, "NormalMatrix");
		matMVIdx = glGetUniformLocation(program, "ModelViewMatrix");
		// Get handle for the shader's material structure fields
		//Note: Returns invalid handles if not being used in the shader
		mAmbientIdx = glGetUniformLocation(program, "material.ambient");
		mDiffuseIdx = glGetUniformLocation(program, "material.diffuse");
		mSpecularIdx = glGetUniformLocation(program, "material.specular");
		mShininessIdx = glGetUniformLocation(program, "material.shininess");
		// Get handle for the shader's light structure fields
		lAmbientIdx = glGetUniformLocation(program, "light.ambient");
		lDiffuseIdx = glGetUniformLocation(program, "light.diffuse");
		lSpecularIdx = glGetUniformLocation(program, "light.specular");
		lPositionIdx = glGetUniformLocation(program, "light.position");
		// Get handle for the shader's camera position
		cameraPositionIdx = glGetUniformLocation(program, "cameraPosition");
	}






	void MeshRenderer::Update(){
		// Get the physics object
		RigidBody *rb = this->gameObject->GetRigidBody();
		// Position the rendered object based on the physics object's transform if it has a non static RB attached
		if (rb != NULL && !rb->IsStatic()){
			btScalar transform[16];
			// Get the transform of the physics object
			rb->GetPhysicsObjectTransform(transform);
			// Convert the array to a matrix ready for multiplication by the scale matrix
			modelMatrix = glm::make_mat4(transform);
			// Bullet's Model Matrix always records scale as 1.0 so apply this from transform
			// According to Bullet documentation objects in the physics world shouldn't have their scale changed.
			glm::vec3 s = gameObject->GetTransform()->GetScale();
			glm::mat4 scale = glm::scale(gameObject->GetTransform()->GetScale());
			modelMatrix *= scale;
		}
		else {
			modelMatrix = gameObject->GetTransform()->GetTransformation();
			// For kinematic RigidBodies (no mass) collider's is position and rotation is based on that of the Rendered Object 
			if (rb != NULL){
				glm::quat rot = gameObject->GetTransform()->GetRotation();
				glm::vec3 pos = gameObject->GetTransform()->GetPosition();
				rb->GetPhysicsRigidBody()->setWorldTransform(btTransform(btQuaternion(rot.x, rot.y, rot.z, rot.w), btVector3(pos.x, pos.y, pos.z)));
			}
		}
		//modelMatrix = gameObject->GetTransform()->GetTransformation();

		glm::mat4 mvp = Graphics::GetProjectionMatrix() * Graphics::GetMainCamera()->GetViewMatrix() * modelMatrix;
		glm::mat4 mv = Graphics::GetMainCamera()->GetViewMatrix() * modelMatrix;
		glm::mat3 mn = glm::mat3(glm::transpose(glm::inverse(mv)));

		material->Apply();

		// Pass matricies to shader
		glUniformMatrix4fv(matMVPIdx, 1, GL_FALSE, glm::value_ptr(mvp));
		glUniformMatrix4fv(matMVIdx, 1, GL_FALSE, glm::value_ptr(mv));
		glUniformMatrix3fv(matNIdx, 1, GL_FALSE, glm::value_ptr(mn));

		//// Pass material properties to shader.
		//// Note : current shader only uses shinness in calculating fragment colour
		MaterialInfo mat = material->GetProperties();
		glUniform4f(mAmbientIdx, mat.ambient.r, mat.ambient.g, mat.ambient.b, mat.ambient.a);
		glUniform4f(mDiffuseIdx, mat.diffuse.r, mat.diffuse.g, mat.diffuse.b, mat.diffuse.a);
		glUniform4f(mSpecularIdx, mat.specular.r, mat.specular.g, mat.specular.b, mat.specular.a);
		glUniform1f(mShininessIdx, mat.shininess);

		// Pass light properties to shader.
		// Only supports one light
		LightInfo light = Graphics::GetLight()->GetProperties();
		glUniform4f(lAmbientIdx, light.ambient.r, light.ambient.g, light.ambient.b, light.ambient.a);
		glUniform4f(lDiffuseIdx, light.diffuse.r, light.diffuse.g, light.diffuse.b, light.diffuse.a);
		glUniform4f(lSpecularIdx, light.specular.r, light.specular.g, light.specular.b, light.specular.a);
		glUniform3f(lPositionIdx, light.position.x, light.position.y, light.position.z);

		// Pass camera position to shader
		glm::vec3 cameraInitialPosition = Graphics::GetMainCamera()->gameObject->GetTransform()->GetPosition();
		glm::vec4 cameraPosition = Graphics::GetMainCamera()->GetViewMatrix() * glm::vec4(cameraInitialPosition,0.0);
		glUniform3f(cameraPositionIdx, -cameraPosition.x, -cameraPosition.y, -cameraPosition.z);

		mesh->Render();
	}





}