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
#include "../Helper/HelperSceneNode.hpp"
#include "../ResourceManager/ResourceManager.hpp"
#include "../Helper/HelperSceneNode.hpp"

namespace ModelLoader {
    std::shared_ptr<SceneNode> loadModel(const std::string&, const std::string&, bool);
    
    void processNode(aiNode*, const aiScene*, SceneNode*, const std::string&);
    std::shared_ptr<SceneNode> makeSceneNode(const aiMesh*, const aiScene*, const aiNode*, const std::string&);
    void loadTexture(const std::string&);
};
