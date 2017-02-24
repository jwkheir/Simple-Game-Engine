#include "stdafx.h"
#include "FBXMesh.h"

namespace Merlin{
	FBXMesh::FBXMesh(const char * fileName){
		this->fileName = fileName;
	}

	FBXMesh::~FBXMesh(){
		cout << "\nA model has been destroyed!";
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	void FBXMesh::Initialise(){
		FbxManager *manager = FbxManager::Create();
		FbxIOSettings *ioSettings = FbxIOSettings::Create(manager, IOSROOT);
		manager->SetIOSettings(ioSettings);
		FbxImporter *importer = FbxImporter::Create(manager, "");
		importer->Initialize(fileName, -1, manager->GetIOSettings());
		FbxScene *scene = FbxScene::Create(manager, "");
		importer->Import(scene);
		importer->Destroy();
		FbxNode* rootNode = scene->GetRootNode();
		FbxGeometryConverter converter(rootNode->GetFbxManager());
		if (!converter.Triangulate(scene, true)){
			cout << "Error: Triangulation" << endl;
		}
		if (rootNode) { 
			this->GetFbxInfo(rootNode); 
		}
		manager->Destroy();
		// Create vertex array
		// Exercise 6.4
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		// Create vertex buffer 
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, (sizeof(GLfloat) * vertices.size()) + (sizeof(GLfloat) * normals.size()), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, (sizeof(GLfloat) * vertices.size()), &vertices[0]);
		glBufferSubData(GL_ARRAY_BUFFER, (sizeof(GLfloat) * vertices.size()), (sizeof(GLfloat) * normals.size()), &normals[0]);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)(sizeof(GLfloat) * vertices.size()));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		numberVertices = vertices.size() / 3;
		vertices.clear();
		normals.clear();
	}

	void FBXMesh::Render(){
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, numberVertices);
		// Unbind the vertex array
		glBindVertexArray(0);
	}

	void  FBXMesh::GetFbxInfo(FbxNode* Node){

		int colIdx = 0;
		int numKids = Node->GetChildCount();
		FbxNode *childNode = 0;

		for (int i = 0; i < numKids; i++){
			childNode = Node->GetChild(i);
			FbxMesh *mesh = childNode->GetMesh();
			if (mesh != NULL){
				FbxVector4* lVertexArray = NULL;
				const int lVertexCount = mesh->GetControlPointsCount();
				lVertexArray = new FbxVector4[lVertexCount];
				memcpy(lVertexArray, mesh->GetControlPoints(), lVertexCount * sizeof(FbxVector4));
				const int lPolygonCount = mesh->GetPolygonCount();
				for (int lPolygonIndex = 0; lPolygonIndex < lPolygonCount; lPolygonIndex++){
					const int lVerticeCount = mesh->GetPolygonSize(lPolygonIndex);
					for (int lVerticeIndex = 0; lVerticeIndex < lVerticeCount; lVerticeIndex++){

						vertices.push_back(lVertexArray[mesh->GetPolygonVertex(lPolygonIndex, lVerticeIndex)].mData[0]);
						vertices.push_back(lVertexArray[mesh->GetPolygonVertex(lPolygonIndex, lVerticeIndex)].mData[1]);
						vertices.push_back(lVertexArray[mesh->GetPolygonVertex(lPolygonIndex, lVerticeIndex)].mData[2]);

						FbxVector4  normal;
						mesh->GetPolygonVertexNormal(lPolygonIndex, lVerticeIndex, normal);

						normals.push_back(normal.mData[0]);
						normals.push_back(normal.mData[1]);
						normals.push_back(normal.mData[2]);
					}
				}
			}
			this->GetFbxInfo(childNode);
		}
	}

}