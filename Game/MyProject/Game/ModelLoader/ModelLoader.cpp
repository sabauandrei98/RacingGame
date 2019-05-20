//
//  ModelLoader.cpp
//  Game
//
//  Created by Tamas Both - (p) on 09/04/2019.
//

#include "ModelLoader.hpp"

// loads a model and returns the root scene node of it
std::shared_ptr<SceneNode> ModelLoader::loadModel(const std::string& name, const std::string& shader_name) {
    ResourceManager::ConstAiScenePtr    new_scene;
    std::shared_ptr<SceneNode>          new_root;
    ResourceManager&                    resource_manager = ResourceManager::getResourceManager();
    
    new_scene = resource_manager.getModel(name);
    
    new_root = std::make_shared<SceneNode>(new_scene->mRootNode->mName.data);
    processNode(new_scene->mRootNode, new_scene.get(), new_root.get(), shader_name);
    
    return new_root;
}

// transforms the assimp scene node to my scene node
void ModelLoader::processNode(aiNode* node, const aiScene* scene, SceneNode* my_scene_node, const std::string& shader_name) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        my_scene_node->addChild(makeSceneNode(mesh, scene, node, shader_name));
    }
    
    // there are children without mesh too
    for (unsigned int i = node->mNumMeshes; i < node->mNumChildren; i++)
        my_scene_node->addChild(makeSceneNode(nullptr, scene, node, shader_name));
    
    for (unsigned int i = 0; i < node->mNumChildren; i++)
        processNode(node->mChildren[i], scene, my_scene_node->getChild(i), shader_name);
}

// returns a new scene node
std::shared_ptr<SceneNode> ModelLoader::makeSceneNode(const aiMesh *mesh, const aiScene *scene, const aiNode* node, const std::string& shader_name) {
    std::shared_ptr<Mesh>           my_mesh;
    std::shared_ptr<MeshInstance>   mesh_instace;
    std::shared_ptr<SceneNode>      scene_node;
    
    std::vector<IvTNPVertex>        vertices;
    std::vector<unsigned int>       indices;
    
    aiVector3t<float>               scale;
    aiVector3t<float>               rotation;
    aiVector3t<float>               position;
    
    RenderPacket render;
    render._prim_type=kTriangleListPrim;
    render._use_blend=true;
    render._use_depth=true;
    
    scene_node = std::make_shared<HelperSceneNode>(node->mName.data,render);
    
    if (mesh) {
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            IvTNPVertex vertex;
            
            if (mesh->HasPositions())
                vertex.position = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
            
            if (mesh->mTextureCoords[0])
                vertex.texturecoord = {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
            
            if (mesh->HasNormals())
                vertex.normal = {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};
            
            //std::cout << vertex.position.x << " " << vertex.position.y << " " << vertex.position.z << std::endl;
            
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
        
        my_mesh->setVertexBuffer(vertices, kTNPFormat);
        my_mesh->setIndexBuffer(indices);
        mesh_instace->setMesh(my_mesh);
        mesh_instace->setShader(("../../Shaders/" + shader_name).c_str());
        scene_node->setRenderable(mesh_instace);
        
        if (mesh->mMaterialIndex >= 0) {
            std::string         texture_name;
            aiMaterial*         material;
            aiString            str;
            aiColor4D           ai_color;
            unsigned int        win_style;
            unsigned int        unix_style;
            ResourceManager&    resource_manager = ResourceManager::getResourceManager();
            
            material = scene->mMaterials[mesh->mMaterialIndex];
            
            if (material->GetTexture(aiTextureType_DIFFUSE, 0, &str) == AI_SUCCESS) {
                texture_name = str.C_Str();
                //std::cout << mesh->mMaterialIndex << " " << texture_name << std::endl;
                
                win_style = texture_name.find_last_of('\\');
                unix_style = texture_name.find_last_of('/');
                
                if (win_style < texture_name.length())
                    texture_name = texture_name.substr(win_style + 1, texture_name.length());
                if (unix_style < texture_name.length())
                    texture_name = texture_name.substr(unix_style + 1, texture_name.length());
                
                texture_name = texture_name.substr(0, texture_name.find_last_of('.')) + ".tga";
                
                //std::cout << mesh->mMaterialIndex << " " << texture_name << std::endl;
                
                // is 0. when has texture and 1. when has color
                mesh_instace->addShaderUniforms(std::vector<std::string>{"TEXTURE"});
                //mesh_instace->addShaderUniforms(std::vector<std::string>{"TEXTURE_OR_COLOR"});
                
                mesh_instace->setUniformValue(0, resource_manager.getTexture(texture_name).get());
                //mesh_instace->setUniformValue(1, 0.0f);
            }
            
//            if (material->Get(AI_MATKEY_COLOR_DIFFUSE, ai_color) == AI_SUCCESS) {
//                // is 0. when has texture and 1. when has color
//                mesh_instace->addShaderUniforms(std::vector<std::string>{"TEXTURE_OR_COLOR", "COLOR"});
//
//                mesh_instace->setUniformValue(0, 1.);
//                mesh_instace->setUniformValue(1, {ai_color.r, ai_color.g, ai_color.b, ai_color.a});
//            }
        }
    }
    
    node->mTransformation.Decompose(scale, rotation, position);
    scene_node->setLocalTransform({position.x, position.y, position.z}, {rotation.x, rotation.y, rotation.z}, {scale.x, scale.y, scale.z});
    
    return scene_node;
}


