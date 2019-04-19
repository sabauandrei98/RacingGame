//
//  ModelLoader.hpp
//  Game
//
//  Created by Tamas Both - (p) on 09/04/2019.
//

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <IvImage.h>

#include "SceneNode.hpp"

#pragma once

class ModelLoader {
public:
    // public function(s) and method(s)
    static void loadModel(const std::string&, const std::string&, const std::string&, SceneNode*);
    
private:
    // private variable(s)
    static std::string  directory;
    static IvTexture*   texture;
    
    // private function(s) and method(s)
    static void processNode(aiNode*, const aiScene*, SceneNode*, const std::string&);
    static std::shared_ptr<SceneNode> makeSceneNode(const aiMesh*, const aiScene*, const aiNode*, const std::string&);
    static void loadTexture(const char*);
};
