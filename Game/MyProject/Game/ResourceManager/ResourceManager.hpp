//
//  ResourceManager.hpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 17/04/2019.
//

#pragma once

#include <list>
#include <unordered_map>
#include <functional>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <IvImage.h>
#include <IvRenderer.h>
#include <IvTexture.h>

#include "IvResourceManagerOGL.h"

class ResourceManager {
public:
    // typedefs
    typedef std::shared_ptr<IvTexture>                          TexturePtr;
    typedef std::shared_ptr<const aiScene>                      ConstAiScenePtr;
    typedef std::unordered_map<std::string, TexturePtr>         StringToTexture;
    typedef std::unordered_map<std::string, ConstAiScenePtr>    StringToAiScene;
    typedef std::vector<std::string>                            CacheHelper;
    typedef std::function<void(IvTexture*)>                     Lambda;
    
    // static function(s)
    static ResourceManager& getResourceManager();
    static void resetResourceManager();
    
    // public function(s) and method(s)
    const TexturePtr& getTexture(const std::string&) const;
    const ConstAiScenePtr& getModel(const std::string&, bool) const;
    
    // copy constructor and assignment operator are not needed
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator =(const ResourceManager&) = delete;
    
private:
    // private constructor
    ResourceManager();
    
    // private variable(s)
    const unsigned int      SIZE_OF_CACHE;
    const Lambda            CUSTOM_DELETER;
    TexturePtr              FALLBACK_TEXTURE;
    const ConstAiScenePtr   NULL_POINTER;
    
    mutable StringToTexture textures;
    mutable StringToAiScene models;
    mutable CacheHelper     texture_cache;
    mutable CacheHelper     model_cache;
    
    // private function(s) and method(s)
    IvTexture* loadTexture(const std::string&) const;
};
