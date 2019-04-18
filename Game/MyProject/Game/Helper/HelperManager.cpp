//-------------------------------------------------------------------------------
//-- HelperManager.cpp ----------------------------------------------------------
//-------------------------------------------------------------------------------
#include "HelperManager.hpp"

namespace HelperManager{
    //---------------------------------------------------------------------------
    // @HelperManager::CreateBoxMesh()
    //---------------------------------------------------------------------------
    std::shared_ptr<Mesh> CreateBoxMesh()
    {
        float x=0;
        float y=0;
        float z=0;
        
        IvVertexFormat format=IvVertexFormat::kTNPFormat;
        std::vector<IvTNPVertex> vertices;
        std::vector<unsigned int> indices;
        
        IvTNPVertex vertex1;
        IvTNPVertex vertex2;
        IvTNPVertex vertex3;
        IvTNPVertex vertex4;
        
        std::shared_ptr<Mesh> square =std::make_shared<Mesh>();
        
        vertex1.position=IvVector3(x+0.5,y+0.5,z-0.5);    //v1
        vertex2.position=IvVector3(x-0.5,y+0.5,z-0.5);    //v2
        vertex3.position=IvVector3(x+0.5,y+0.5,z+0.5);    //v3
        vertex4.position=IvVector3(x-0.5,y+0.5,z+0.5);    //v4
        
        vertex1.texturecoord=IvVector2(1.,0.);
        vertex2.texturecoord=IvVector2(1.,1.);
        vertex3.texturecoord=IvVector2(0.,0.);
        vertex4.texturecoord=IvVector2(0.,1.);
        
        vertices.push_back(vertex1);
        vertices.push_back(vertex2);
        vertices.push_back(vertex3);
        vertices.push_back(vertex4);
        
        vertex1.position=IvVector3(x+0.5,y-0.5,z-0.5);     //v1'
        vertex2.position=IvVector3(x-0.5,y-0.5,z-0.5);     //v2'
        vertex3.position=IvVector3(x+0.5,y-0.5,z+0.5);     //v3'
        vertex4.position=IvVector3(x-0.5,y-0.5,z+0.5);     //v4'
        
        vertex1.texturecoord=IvVector2(1.,0.);
        vertex2.texturecoord=IvVector2(1.,1.);
        vertex3.texturecoord=IvVector2(0.,0.);
        vertex4.texturecoord=IvVector2(0.,1.);
        
        vertices.push_back(vertex1);
        vertices.push_back(vertex2);
        vertices.push_back(vertex3);
        vertices.push_back(vertex4);
        
        //front
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);
        indices.push_back(3);
        
        //back
        indices.push_back(6);
        indices.push_back(7);
        indices.push_back(4);
        indices.push_back(5);
        
        //left
        indices.push_back(5);
        indices.push_back(7);
        indices.push_back(1);
        indices.push_back(3);
        
        //right
        indices.push_back(4);
        indices.push_back(6);
        indices.push_back(0);
        indices.push_back(2);
        
        //up
        indices.push_back(6);
        indices.push_back(7);
        indices.push_back(2);
        indices.push_back(3);
        
        //down
        indices.push_back(0);
        indices.push_back(4);
        indices.push_back(1);
        indices.push_back(5);
        
        // setting buffers
        square->setVertexBuffer(vertices, format);
        square->setIndexBuffer(indices);
        
        return square;
    }
    //---------------------------------------------------------------------------
    // @HelperManager::CreateQuadMesh()
    //---------------------------------------------------------------------------
    std::shared_ptr<Mesh> CreateQuadMesh()
    {
        std::shared_ptr<Mesh> quad=std::make_shared<Mesh>();
        
        
        float x=0;
        float y=0;
        float z=0;
        
        IvVertexFormat format=IvVertexFormat::kTNPFormat;
        std::vector<IvTNPVertex> vertices;
        std::vector<unsigned int> indices;
        
        IvTNPVertex vertex1;
        IvTNPVertex vertex2;
        IvTNPVertex vertex3;
        IvTNPVertex vertex4;
        
        vertex1.position=IvVector3(x,y+0.5,z-0.5);
        vertex2.position=IvVector3(x,y-0.5,z-0.5);
        vertex3.position=IvVector3(x,y+0.5,z+0.5);
        vertex4.position=IvVector3(x,y-0.5,z+0.5);
        
        vertex1.texturecoord=IvVector2(1.,0.);
        vertex2.texturecoord=IvVector2(1.,1.);
        vertex3.texturecoord=IvVector2(0.,0.);
        vertex4.texturecoord=IvVector2(0.,1.);
        
        vertex1.normal=IvVector3::xAxis;
        vertex2.normal=IvVector3::xAxis;
        vertex3.normal=IvVector3::xAxis;
        vertex4.normal=IvVector3::xAxis;
        
        vertices.push_back(vertex1);
        vertices.push_back(vertex2);
        vertices.push_back(vertex3);
        vertices.push_back(vertex4);
        
        for(int i=0;i<4;i++)
            indices.push_back(i);
        
        //setting buffers
        quad->setVertexBuffer(vertices, format);
        quad->setIndexBuffer(indices);
        
        return quad;
    }
    //---------------------------------------------------------------------------
    // @HelperManager::CreateSphereMesh()
    //---------------------------------------------------------------------------
    std::shared_ptr<Mesh> CreateSphereMesh()
    {
        
        std::shared_ptr<Mesh> sphereMesh=std::make_shared<Mesh>();
        
        IvVertexFormat format=IvVertexFormat::kTNPFormat;
        
        std::vector<IvTNPVertex> vertices;
        std::vector<unsigned int> indices;
        
        IvTNPVertex vertex1;
        IvTNPVertex vertex2;
        IvTNPVertex vertex3;
        IvTNPVertex vertex4;
        
        //first create 12 points
        float t=(1.0+sqrt(5.0))/2.0;
        std::vector<IvVector3> points;
        
        points.push_back(IvVector3(-1, t, 0));   // p0
        points.push_back(IvVector3( 1, t, 0));   // p1
        points.push_back(IvVector3(-1,-t, 0));   // p2
        points.push_back(IvVector3( 1,-t, 0));   // p3
        
        points.push_back(IvVector3( 0,-1, t));    // p4
        points.push_back(IvVector3( 0, 1, t));    // p5
        points.push_back(IvVector3( 0,-1,-t));    // p6
        points.push_back(IvVector3( 0, 1,-t));    // p7
        
        points.push_back(IvVector3( t, 0,-1));    // p8
        points.push_back(IvVector3( t, 0, 1));    // p9
        points.push_back(IvVector3(-t, 0,-1));    // p10
        points.push_back(IvVector3(-t, 0, 1));    // p11
        
        
        // 12 vertices
        vertex1.position=points[0];
        vertex2.position=points[1];
        vertex3.position=points[2];
        vertex4.position=points[3];
        
        vertices.push_back(vertex1);
        vertices.push_back(vertex2);
        vertices.push_back(vertex3);
        vertices.push_back(vertex4);
        
        vertex1.position=points[4];
        vertex2.position=points[5];
        vertex3.position=points[6];
        vertex4.position=points[7];
        
        vertices.push_back(vertex1);
        vertices.push_back(vertex2);
        vertices.push_back(vertex3);
        vertices.push_back(vertex4);
        
        vertex1.position=points[8];
        vertex2.position=points[9];
        vertex3.position=points[10];
        vertex4.position=points[11];
        
        vertices.push_back(vertex1);
        vertices.push_back(vertex2);
        vertices.push_back(vertex3);
        vertices.push_back(vertex4);
        
        
        indices.push_back(0);
        indices.push_back(11);
        indices.push_back(5);
        
        indices.push_back(0);
        indices.push_back(5);
        indices.push_back(1);
        
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(7);
        
        indices.push_back(0);
        indices.push_back(7);
        indices.push_back(10);
        
        indices.push_back(0);
        indices.push_back(10);
        indices.push_back(11);
        
        
        indices.push_back(1);
        indices.push_back(5);
        indices.push_back(9);
        
        indices.push_back(5);
        indices.push_back(11);
        indices.push_back(4);
        
        indices.push_back(11);
        indices.push_back(10);
        indices.push_back(2);
        
        indices.push_back(10);
        indices.push_back(7);
        indices.push_back(6);
        
        indices.push_back(7);
        indices.push_back(1);
        indices.push_back(8);
        
        
        indices.push_back(3);
        indices.push_back(9);
        indices.push_back(4);
        
        indices.push_back(3);
        indices.push_back(4);
        indices.push_back(2);
        
        indices.push_back(3);
        indices.push_back(2);
        indices.push_back(6);
        
        indices.push_back(3);
        indices.push_back(6);
        indices.push_back(8);
        
        indices.push_back(3);
        indices.push_back(8);
        indices.push_back(9);
        
        
        indices.push_back(4);
        indices.push_back(9);
        indices.push_back(5);
        
        indices.push_back(2);
        indices.push_back(4);
        indices.push_back(11);
        
        indices.push_back(6);
        indices.push_back(2);
        indices.push_back(10);
        
        indices.push_back(8);
        indices.push_back(6);
        indices.push_back(7);
        
        indices.push_back(9);
        indices.push_back(8);
        indices.push_back(1);
        
        indices.push_back(10);
        indices.push_back(11);
        indices.push_back(5);
        
        
        RefineTriangles(vertices,indices,4);
        
        sphereMesh->setVertexBuffer(vertices, format);
        sphereMesh->setIndexBuffer(indices);
        
        return sphereMesh;
    }
    //---------------------------------------------------------------------------
    // @HelperManager::CreateMeshInstance()
    //---------------------------------------------------------------------------
    std::shared_ptr<MeshInstance> CreateMeshInstance(const std::shared_ptr<Mesh> &mesh,
                                                     const char* shaderName)
    {
        std::shared_ptr<MeshInstance> meshInstance=std::make_shared<MeshInstance>();
        meshInstance->setMesh(mesh);
        meshInstance->setShader(shaderName);
        
        return meshInstance;
    }
    
    //---------------------------------------------------------------------------
    // @HelperManager::CreateMeshInstance()
    //---------------------------------------------------------------------------
    std::shared_ptr<MeshInstance> CreateMeshInstance(const std::shared_ptr<Mesh> &mesh,
                                                     const std::vector<std::string>& uniforms,
                                                     const char* shaderName)
    {
        std::shared_ptr<MeshInstance> meshInstance=std::make_shared<MeshInstance>();
        meshInstance->setMesh(mesh);
        meshInstance->setShader(shaderName);
        meshInstance->addShaderUniforms(uniforms);
        
        return meshInstance;
    }
    //---------------------------------------------------------------------------
    // @HelperManager::BuildSphere()
    //---------------------------------------------------------------------------
    std::shared_ptr<SceneNode>
    BuildSphere(const std::shared_ptr<MeshInstance>&meshInstance,bool wireframeValue)
    {
        RenderPacket myRenderPacket;
        myRenderPacket._use_blend = true;
        myRenderPacket._use_depth = true;
        myRenderPacket._use_wireframe = wireframeValue;
        myRenderPacket._prim_type = kTriangleListPrim;
        
        std::shared_ptr<HelperSceneNode> node = std::make_shared<HelperSceneNode>("node", myRenderPacket);
        node->setRenderable(meshInstance);
        
        return node;
    }
    
    //---------------------------------------------------------------------------
    // @HelperManager::BuildBox()
    //---------------------------------------------------------------------------
    std::shared_ptr<SceneNode>
    BuildBox(const std::shared_ptr<MeshInstance>&meshInstance,bool wireframeValue)
    {
        RenderPacket myRenderPacket;
        myRenderPacket._use_blend = true;
        myRenderPacket._use_depth = true;
        myRenderPacket._use_wireframe = wireframeValue;
        myRenderPacket._prim_type = kTriangleStripPrim;
        
        std::shared_ptr<HelperSceneNode> node = std::make_shared<HelperSceneNode>("node", myRenderPacket);
        node->setRenderable(meshInstance);
        
        return node;
    }
    //---------------------------------------------------------------------------
    // @HelperManager::BuildQuad()
    //---------------------------------------------------------------------------
    std::shared_ptr<SceneNode>
    BuildQuad(const std::shared_ptr<MeshInstance>&meshInstance,IvVector3 axis,bool wireframeValue)
    {
        RenderPacket myRenderPacket;
        myRenderPacket._use_blend = true;
        myRenderPacket._use_depth = true;
        myRenderPacket._use_wireframe = wireframeValue;
        myRenderPacket._prim_type = kTriangleStripPrim;
        
        std::shared_ptr<HelperSceneNode> node = std::make_shared<HelperSceneNode>("node", myRenderPacket);
        node->setRenderable(meshInstance);
        
        IvVector3 position=IvVector3(0,0,0);
        IvVector3 rotation=IvVector3(0,0,0);
        IvVector3 scale=IvVector3(1,1,1);
        if (axis == IvVector3::xAxis)
            rotation += IvVector3(0, 1.5, 0);
        else if (axis == IvVector3::yAxis)
            rotation += IvVector3(1.5, 0, 0);
        else if (axis == IvVector3::zAxis)
            rotation += IvVector3(0, 0, 1.5);
        node->setLocalTransform(position, rotation, scale);
        return node;
    }
    
    //---------------------------------------------------------------------------
    // @HelperManager::BuildTexturedQuad()
    //---------------------------------------------------------------------------
    std::shared_ptr<SceneNode>
    BuildTexturedQuad(const std::shared_ptr<MeshInstance>&meshInstance,const char* textureName,const char* shaderName,IvVector3 axis,bool wireframeValue)
    {
        RenderPacket myRenderPacket;
        myRenderPacket._use_blend = true;
        myRenderPacket._use_depth = true;
        myRenderPacket._use_wireframe = wireframeValue;
        myRenderPacket._prim_type = kTriangleStripPrim;
        
        std::shared_ptr<HelperSceneNode> node = std::make_shared<HelperSceneNode>("node", myRenderPacket);
        node->setRenderable(meshInstance);
        
        IvVector3 position=IvVector3(0,0,0);
        IvVector3 rotation=IvVector3(0,0,0);
        IvVector3 scale=IvVector3(1,1,1);
        if (axis == IvVector3::xAxis)
            rotation += IvVector3(0, 1.5, 0);
        else if (axis == IvVector3::yAxis)
            rotation += IvVector3(1.5, 0, 0);
        else if (axis == IvVector3::zAxis)
            rotation += IvVector3(0, 0, 1.5);
        node->setLocalTransform(position, rotation, scale);
        
        IvImage* image = IvImage::CreateFromFile(textureName);
        IvTexture* quadTexture;
        
        if (image)
        {
            quadTexture = IvRenderer::mRenderer->GetResourceManager()->CreateTexture((image->GetBytesPerPixel() == 4) ? kRGBA32TexFmt : kRGB24TexFmt, image->GetWidth(), image->GetHeight(), image->GetPixels(), kImmutableUsage);
            delete image;
            image = 0;
        }
        
        IvUniform* unif = meshInstance->getShaderUniforms()[0];
        if (unif)
            unif->SetValue(quadTexture);
        
        return node;
    }
    //---------------------------------------------------------------------------
    // @HelperManager::GetMiddlePoint()
    //---------------------------------------------------------------------------
    IvVector3 GetMiddlePoint(const IvVector3& point1,const IvVector3& point2)
    {
        IvVector3 mid=IvVector3(    (point1.x+point2.x)/2.0,
                                    (point1.y+point2.y)/2.0,
                                    (point1.z+point2.z)/2.0);
        
        return mid;
    }
    //---------------------------------------------------------------------------
    // @HelperManager::RefineTriangles()
    //---------------------------------------------------------------------------
    void RefineTriangles(std::vector<IvTNPVertex>& vertices,std::vector<unsigned int>& indices,int recursionLevel)
    {
        std::vector<IvTNPVertex> newVertices;
        std::vector<unsigned int> newIndices;
        
        IvTNPVertex vertex1;
        IvTNPVertex vertex2;
        IvTNPVertex vertex3;
        
        
        
        for(int i=0;i<recursionLevel;i++)
        {
            newVertices.clear();
            newIndices.clear();
            int index=0;
            
            for(int j=0;j<indices.size();j+=3)
            {
                IvVector3 p1=GetMiddlePoint(vertices[indices[j]].position, vertices[indices[j+1]].position);
                IvVector3 p2=GetMiddlePoint(vertices[indices[j+1]].position, vertices[indices[j+2]].position);
                IvVector3 p3=GetMiddlePoint(vertices[indices[j+2]].position, vertices[indices[j]].position);
                
                float lengthJ=CalculateLength(vertices[indices[j]].position);
                float lengthJ1=CalculateLength(vertices[indices[j+1]].position);
                float lengthJ2=CalculateLength(vertices[indices[j+2]].position);
                
                float lengthP1=CalculateLength(p1);
                float lengthP2=CalculateLength(p2);
                float lengthP3=CalculateLength(p3);
                
                //replace triangle by 4 triangles
                vertex1.position=vertices[indices[j]].position/lengthJ;
                vertex2.position=p1/lengthP1;
                vertex3.position=p3/lengthP3;
                
                newVertices.push_back(vertex1);
                newVertices.push_back(vertex2);
                newVertices.push_back(vertex3);
                
                vertex1.position=vertices[indices[j+1]].position/lengthJ1;
                vertex2.position=p2/lengthP2;
                vertex3.position=p1/lengthP1;
                
                newVertices.push_back(vertex1);
                newVertices.push_back(vertex2);
                newVertices.push_back(vertex3);
                
                vertex1.position=vertices[indices[j+2]].position/lengthJ2;
                vertex2.position=p3/lengthP3;
                vertex3.position=p2/lengthP2;
                
                newVertices.push_back(vertex1);
                newVertices.push_back(vertex2);
                newVertices.push_back(vertex3);
                
                vertex1.position=p1/lengthP1;
                vertex2.position=p2/lengthP2;
                vertex3.position=p3/lengthP3;
                
                newVertices.push_back(vertex1);
                newVertices.push_back(vertex2);
                newVertices.push_back(vertex3);
                
                newIndices.push_back(index);
                newIndices.push_back(index+1);
                newIndices.push_back(index+2);
                newIndices.push_back(index+3);
                newIndices.push_back(index+4);
                newIndices.push_back(index+5);
                newIndices.push_back(index+6);
                newIndices.push_back(index+7);
                newIndices.push_back(index+8);
                newIndices.push_back(index+9);
                newIndices.push_back(index+10);
                newIndices.push_back(index+11);
                
                index+=12;
            }
            vertices.clear();
            vertices=newVertices;
            indices.clear();
            indices=newIndices;
        }
        
    }
    //---------------------------------------------------------------------------
    // @HelperManager:: CalculateLength()
    //---------------------------------------------------------------------------
    float CalculateLength(const IvVector3& point)
    {
        return sqrt(point.x*point.x+point.y*point.y+point.z*point.z);
    }
}
