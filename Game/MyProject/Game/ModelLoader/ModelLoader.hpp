//
//  ModelLoader.hpp
//  Game
//
//  Created by Tamas Both - (p) on 09/04/2019.
//

#pragma once

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <IvImage.h>

#include "SceneNode.hpp"

class ModelLoader {
public:
    // public function(s) and method(s)
    static void loadModel(const std::string&, const std::string&, SceneNode*);
    
private:
    // private variable(s)
    static std::string  directory;
    static std::string  last_texture_name;
    static IvTexture*   texture;
    
    static const std::string FALLBACK_TEXTURE;
    
    // private function(s) and method(s)
    static void processNode(aiNode*, const aiScene*, SceneNode*, const std::string&);
    static std::shared_ptr<SceneNode> makeSceneNode(const aiMesh*, const aiScene*, const aiNode*, const std::string&);
    static void loadTexture(const std::string&);
};
