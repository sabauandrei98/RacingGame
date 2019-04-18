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

#include "SceneNode.hpp"
#include "../ResourceManager/ResourceManager.hpp"

class ModelLoader {
public:
    // public function(s) and method(s)
    static std::shared_ptr<SceneNode> loadModel(const std::string&, const std::string&);
    
private:
    // private function(s) and method(s)
    static void processNode(aiNode*, const aiScene*, SceneNode*, const std::string&);
    static std::shared_ptr<SceneNode> makeSceneNode(const aiMesh*, const aiScene*, const aiNode*, const std::string&);
    static void loadTexture(const std::string&);
};
