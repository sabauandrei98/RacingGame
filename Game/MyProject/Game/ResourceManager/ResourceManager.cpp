//
//  ResourceManager.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 17/04/2019.
//

#include "ResourceManager.hpp"

// -------------
// PUBLIC GETTER
// -------------

// returns reference to the already existing static object
ResourceManager& ResourceManager::getResourceManager() {
    static ResourceManager resource_manager;
    return resource_manager;
}

// resets the resource manager
void ResourceManager::resetResourceManager() {
    ResourceManager& resource_manager = getResourceManager();
    
    resource_manager.textures.clear();
    resource_manager.models.clear();
    resource_manager.texture_cache.clear();
    resource_manager.model_cache.clear();
    resource_manager.FALLBACK_TEXTURE.reset();
}

// --------------------------------
// PUBLIC FUNCTION(S) AND METHOD(S)
// --------------------------------

// returns a shared pointer to the texture with the given name or to the fallback texture
const ResourceManager::TexturePtr& ResourceManager::getTexture(const std::string& name) const {
    StringToTexture::iterator location;
    IvTexture*                texture;
    
    location = textures.find(name);
    if (location != textures.end()) {
        texture_cache.remove(name);
        texture_cache.push_back(name);
        
        return location->second;
    }
    
    texture = loadTexture("../../Textures/" + name);
    if (!texture)
        return FALLBACK_TEXTURE;
    
    textures.insert(std::make_pair(name, TexturePtr(texture, CUSTOM_DELETER)));
    texture_cache.push_back(name);
    
    if (textures.size() > SIZE_OF_CACHE) {
        textures.erase(texture_cache.front());
        texture_cache.pop_front();
    }
    
    return textures[name];
}

// returns a shared pointer to the model with the given name or nullptr
const ResourceManager::ConstAiScenePtr& ResourceManager::getModel(const std::string& name) const {
    StringToAiScene::iterator   location;
    const aiScene*              scene;
    Assimp::Importer            importer;
    
    location = models.find(name);
    if (location != models.end()) {
        model_cache.remove(name);
        model_cache.push_back(name);
        
        return location->second;
    }
    
    importer.ReadFile("../../Models/" + name, aiProcess_Triangulate | aiProcess_FlipUVs);
    scene = importer.GetOrphanedScene();
    
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return NULL_POINTER;
    }
    
    models.insert(std::make_pair(name, ConstAiScenePtr(scene)));
    model_cache.push_back(name);
    
    if (models.size() > SIZE_OF_CACHE) {
        models.erase(model_cache.front());
        model_cache.pop_front();
    }
    
    return models[name];
}

// ---------------------------------
// PRIVATE FUNCTION(S) AND METHOD(S)
// ---------------------------------

IvTexture* ResourceManager::loadTexture(const std::string& file_name) const {
    IvImage*    image = IvImage::CreateFromFile(file_name.c_str());
    
    if (!image)
        return nullptr;
    
    return IvRenderer::mRenderer->GetResourceManager()->CreateTexture((image->GetBytesPerPixel() == 4) ? kRGBA32TexFmt : kRGB24TexFmt, image->GetWidth(), image->GetHeight(), image->GetPixels(), kImmutableUsage);
}

// -------------------
// PRIVATE CONSTRUCTOR
// -------------------

ResourceManager::ResourceManager() :
    SIZE_OF_CACHE(10),
    CUSTOM_DELETER([](IvTexture* texture) {
        IvRenderer::mRenderer->GetResourceManager()->Destroy(texture);
    }),
    FALLBACK_TEXTURE(TexturePtr(loadTexture("../../Textures/pink.tga"), CUSTOM_DELETER)),
    NULL_POINTER(nullptr) {
    }

