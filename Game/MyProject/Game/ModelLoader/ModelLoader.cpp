//
//  ModelLoader.cpp
//  Game
//
//  Created by Tamas Both - (p) on 09/04/2019.
//

#include "ModelLoader.hpp"

std::string ModelLoader::directory;
IvTexture*  ModelLoader::texture;

// --------------------------------
// PUBLIC FUNCTION(S) AND METHOD(S)
// --------------------------------

// loads a model into the scene graph
// the given scene_node parameter will be the parent of the model
void ModelLoader::loadModel(const std::string& path, const std::string& texture_path, const std::string& shader_path, SceneNode* scene_node) {
    Assimp::Importer            import;
    const aiScene*              new_scene;
    std::shared_ptr<SceneNode>  new_root;
    
    new_scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if(!new_scene || new_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !new_scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    
    directory = path.substr(0, path.find_last_of('/'));
    
    new_root = std::make_shared<SceneNode>(new_scene->mRootNode->mName.data);
    scene_node->addChild(new_root);
    
    loadTexture(texture_path.c_str());
    processNode(new_scene->mRootNode, new_scene, new_root.get(), shader_path);
}

// --------------------------------
// PRIVATE FUNCTION(S) AND METHOD(S)
// --------------------------------

// transforms the assimp scene node to my scene node
void ModelLoader::processNode(aiNode* node, const aiScene* scene, SceneNode* my_scene_node, const std::string& shader_path) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        my_scene_node->addChild(makeSceneNode(mesh, scene, node, shader_path));
    }
    
    for (unsigned int i = node->mNumMeshes; i < node->mNumChildren; i++)
        my_scene_node->addChild(makeSceneNode(nullptr, scene, node, shader_path));
    
    for (unsigned int i = 0; i < node->mNumChildren; i++)
        processNode(node->mChildren[i], scene, my_scene_node->getChild(i), shader_path);
}

// returns a new scene node
std::shared_ptr<SceneNode> ModelLoader::makeSceneNode(const aiMesh *mesh, const aiScene *scene, const aiNode* node, const std::string& shader_path) {
    std::shared_ptr<Mesh>           my_mesh;
    std::shared_ptr<MeshInstance>   mesh_instace;
    std::shared_ptr<SceneNode>      scene_node;
    
    std::vector<IvTCPVertex>        vertices;
    std::vector<unsigned int>       indices;
    
    aiVector3t<float>               scale;
    aiVector3t<float>               rotation;
    aiVector3t<float>               position;
    
    scene_node = std::make_shared<SceneNode>(node->mName.data);
    
    if (mesh) {
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            IvTCPVertex vertex;
            
            if (mesh->HasPositions())
                vertex.position = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
            
            if (mesh->mTextureCoords[0])
                vertex.texturecoord = {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
            
            vertices.push_back(vertex);
        }
        
        if (mesh->HasFaces()) {
            for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
                
                aiFace face = mesh->mFaces[i];
                
                for (unsigned int j = 0; j < face.mNumIndices; j++)
                    indices.push_back(face.mIndices[j]);
            }
        }
        
        my_mesh = std::make_shared<Mesh>();
        mesh_instace = std::make_shared<MeshInstance>();
        
        my_mesh->setVertexBuffer(vertices, kTCPFormat);
        my_mesh->setIndexBuffer(indices);
        mesh_instace->setMesh(my_mesh);
        mesh_instace->setShader(shader_path.c_str());
        scene_node->setRenderable(mesh_instace);
        
        if (mesh->mMaterialIndex >= 0) {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    
            aiString str;
            material->GetTexture(aiTextureType_DIFFUSE, mesh->mMaterialIndex, &str);
            if (str.length > 0) {
                mesh_instace->addShaderUniforms(std::vector<std::string>{"TEXTURE"});
                mesh_instace->setUniformValue(0, texture);
            }
        }
    }
    
    node->mTransformation.Decompose(scale, rotation, position);
    scene_node->setLocalTransform({position.x, position.y, position.z}, {rotation.x, rotation.y, rotation.z}, {scale.x, scale.y, scale.z});
    
    return scene_node;
}

// loads a texture
void ModelLoader::loadTexture(const char* file_name) {
    IvImage*    image = IvImage::CreateFromFile(file_name);
    
    texture = IvRenderer::mRenderer->GetResourceManager()->CreateTexture((image->GetBytesPerPixel() == 4) ? kRGBA32TexFmt : kRGB24TexFmt, image->GetWidth(), image->GetHeight(), image->GetPixels(), kImmutableUsage);
}


