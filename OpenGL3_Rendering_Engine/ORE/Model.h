#pragma once
#pragma comment(lib, "assimp.lib")
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "BaseMesh.h"
#include "Mesh.h"

//TODO: Change to use hierarchy

namespace ORE {
	class Model :
		public BaseMesh {
	public:
		Model(std::string path);
		virtual ~Model();
		void draw(World* world) override;
	private:
		vector<Mesh*> meshes;
		std::string directory;
		void processNode(aiNode* node, const aiScene* scene);
		Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
		GLuint loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	};
}
