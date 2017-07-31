#include "Model.h"
#include <iostream>

namespace ORE {
	Model::Model(std::string path) {
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
			return;
		}
		directory = path.substr(0, path.find_last_of('/'));
		processNode(scene->mRootNode, scene);
	}


	Model::~Model() {
	}


	void Model::draw(World* world) {
		for (unsigned int i = 0; i < meshes.size(); i++) {
			meshes[i]->draw(world);
		}
	}

	void Model::processNode(aiNode* node, const aiScene* scene) {
		// process all the node's meshes (if any)
		for (unsigned int i = 0; i < node->mNumMeshes; i++) {
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
			Mesh* m = processMesh(mesh, scene);
			m->setParent(this);
			meshes.push_back(m);
		}
		// then do the same for each of its children
		for (unsigned int i = 0; i < node->mNumChildren; i++) {
			processNode(node->mChildren[i], scene);
		}
	}


	Mesh* Model::processMesh(aiMesh* mesh, const aiScene* scene) {
		// data to fill
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<GLuint> textures;

		// Walk through each of the mesh's vertices
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			Vertex vertex;
			glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
							  // positions
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.position = vector;
			// normals
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;
			// texture coordinates
			if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			{
				glm::vec2 vec;
				// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.texCoord = vec;
			} else
				vertex.texCoord = glm::vec2(0.0f, 0.0f);
			// tangent
			vector.x = mesh->mTangents[i].x;
			vector.y = mesh->mTangents[i].y;
			vector.z = mesh->mTangents[i].z;
			vertex.tangent = vector;
			// bitangent
			vector.x = mesh->mBitangents[i].x;
			vector.y = mesh->mBitangents[i].y;
			vector.z = mesh->mBitangents[i].z;
			vertex.bitangent = vector;
			vertices.push_back(vertex);
		}
		// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			// retrieve all indices of the face and store them in the indices vector
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		// process materials
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
		// Same applies to other texture as the following list summarizes:
		// diffuse: texture_diffuseN
		// specular: texture_specularN
		// normal: texture_normalN

		// 1. diffuse maps
		GLuint diffuseMap = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.push_back(diffuseMap);
		// 2. specular maps
		GLuint specularMap = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.push_back(specularMap);
		// 3. normal maps
		GLuint normalMap = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
		textures.push_back(normalMap);
		// 4. emission maps
		GLuint emission = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_emission");
		textures.push_back(emission);

		// return a mesh object created from the extracted mesh data
		return new Mesh(vertices, indices, textures);
	}


	GLuint Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) {
		GLuint texture = 0;
		for (unsigned int i = 0; i < mat->GetTextureCount(type) && i<2; i++) {
			aiString str;
			mat->GetTexture(type, i, &str);
			GLenum err = glGetError();
			texture = loadImage(directory + "/" + str.C_Str());
		}
		return texture;
	}
}
