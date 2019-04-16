//-------------------------------------------------------------------------------
//-- HelperManager.cpp ----------------------------------------------------------
//-------------------------------------------------------------------------------
#include"HelperManager.h"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ HelperManager::CreateBoxMesh()
//-------------------------------------------------------------------------------
std::shared_ptr<Mesh>
HelperManager::CreateBoxMesh()
{
    float x=0;
    float y=0;
    float z=0;
    
    // setting squares
    IvVertexFormat format=IvVertexFormat::kTNPFormat;
    std::vector<IvTNPVertex> vertices;
    IvTNPVertex vertex1;
    IvTNPVertex vertex2;
    IvTNPVertex vertex3;
    IvTNPVertex vertex4;
    
    std::shared_ptr<Mesh> square =std::make_shared<Mesh>();
    
    //front
    vertex1.position=IvVector3(x+0.5,y+0.5,z-0.5);
    vertex2.position=IvVector3(x-0.5,y+0.5,z-0.5);
    vertex3.position=IvVector3(x+0.5,y+0.5,z+0.5);
    vertex4.position=IvVector3(x-0.5,y+0.5,z+0.5);
    
    vertex1.texturecoord=IvVector2(1.,0.);
    vertex2.texturecoord=IvVector2(1.,1.);
    vertex3.texturecoord=IvVector2(0.,0.);
    vertex4.texturecoord=IvVector2(0.,1.);
    
    vertex1.normal=IvVector3::yAxis;
    vertex2.normal=IvVector3::yAxis;
    vertex3.normal=IvVector3::yAxis;
    vertex4.normal=IvVector3::yAxis;
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    vertices.push_back(vertex4);
    
    // back
    vertex1.position=IvVector3(x+0.5,y-0.5,z+0.5);
    vertex2.position=IvVector3(x-0.5,y-0.5,z+0.5);
    vertex3.position=IvVector3(x+0.5,y-0.5,z-0.5);
    vertex4.position=IvVector3(x-0.5,y-0.5,z-0.5);
   
    vertex1.texturecoord=IvVector2(1.,0.);
    vertex2.texturecoord=IvVector2(1.,1.);
    vertex3.texturecoord=IvVector2(0.,0.);
    vertex4.texturecoord=IvVector2(0.,1.);
    
    vertex1.normal=IvVector3::yAxis;
    vertex2.normal=IvVector3::yAxis;
    vertex3.normal=IvVector3::yAxis;
    vertex4.normal=IvVector3::yAxis;
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    vertices.push_back(vertex4);
    
    // left
    vertex1.position=IvVector3(x-0.5,y-0.5,z-0.5);
    vertex2.position=IvVector3(x-0.5,y-0.5,z+0.5);
    vertex3.position=IvVector3(x-0.5,y+0.5,z-0.5);
    vertex4.position=IvVector3(x-0.5,y+0.5,z+0.5);
    
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
    
    // right
    vertex1.position=IvVector3(x+0.5,y-0.5,z-0.5);
    vertex2.position=IvVector3(x+0.5,y-0.5,z+0.5);
    vertex3.position=IvVector3(x+0.5,y+0.5,z-0.5);
    vertex4.position=IvVector3(x+0.5,y+0.5,z+0.5);
    
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
    
    //up
    vertex1.position=IvVector3(x+0.5,y-0.5,z+0.5);
    vertex2.position=IvVector3(x-0.5,y-0.5,z+0.5);
    vertex3.position=IvVector3(x+0.5,y+0.5,z+0.5);
    vertex4.position=IvVector3(x-0.5,y+0.5,z+0.5);
    
    vertex1.texturecoord=IvVector2(1.,0.);
    vertex2.texturecoord=IvVector2(1.,1.);
    vertex3.texturecoord=IvVector2(0.,0.);
    vertex4.texturecoord=IvVector2(0.,1.);
    
    vertex1.normal=IvVector3::zAxis;
    vertex2.normal=IvVector3::zAxis;
    vertex3.normal=IvVector3::zAxis;
    vertex4.normal=IvVector3::zAxis;
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    vertices.push_back(vertex4);
    
    //down
    vertex1.position=IvVector3(x+0.5,y+0.5,z-0.5);
    vertex2.position=IvVector3(x+0.5,y-0.5,z-0.5);
    vertex3.position=IvVector3(x-0.5,y+0.5,z-0.5);
    vertex4.position=IvVector3(x-0.5,y-0.5,z-0.5);
    
    vertex1.texturecoord=IvVector2(1.,0.);
    vertex2.texturecoord=IvVector2(1.,1.);
    vertex3.texturecoord=IvVector2(0.,0.);
    vertex4.texturecoord=IvVector2(0.,1.);
    
    vertex1.normal=IvVector3::zAxis;
    vertex2.normal=IvVector3::zAxis;
    vertex3.normal=IvVector3::zAxis;
    vertex4.normal=IvVector3::zAxis;
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    vertices.push_back(vertex4);
    
    
    // setting buffers
    square->setVertexBuffer(vertices, format);
    
    std::vector<unsigned int> indices;
    for(int i=0;i<vertices.size();i++)
        indices.push_back(i);
    
    square->setIndexBuffer(indices);
    
    return square;
}
//-------------------------------------------------------------------------------
// @ HelperManager::CreateQuadMesh()
//-------------------------------------------------------------------------------
std::shared_ptr<Mesh>
HelperManager::CreateQuadMesh()
{
    float x=0;
    float y=0;
    float z=0;
    
    IvVertexFormat format=IvVertexFormat::kTNPFormat;
    std::vector<IvTNPVertex> vertices;
    IvTNPVertex vertex1;
    IvTNPVertex vertex2;
    IvTNPVertex vertex3;
    IvTNPVertex vertex4;
    
    std::shared_ptr<Mesh> quad=std::make_shared<Mesh>();
    
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
    
    
    //setting buffers
    quad->setVertexBuffer(vertices, format);
    
    std::vector<unsigned int> indices;
    for(int i=0;i<4;i++)
        indices.push_back(i);
    
    quad->setIndexBuffer(indices);
    
    return quad;
}
//-------------------------------------------------------------------------------
// @ HelperManager::CreateSphereMesh()
//-------------------------------------------------------------------------------
std::shared_ptr<Mesh>
HelperManager::CreateSphereMesh()
{
    //first create 12 points
    float t=(1.0+sqrt(5.0))/2.0;
    
    IvVertexFormat format=IvVertexFormat::kTNPFormat;
    std::vector<IvVector3> points;
    
    std::shared_ptr<Mesh> sphereMesh=std::make_shared<Mesh>();
    
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

    std::vector<IvTNPVertex> vertices;
    IvTNPVertex vertex1;
    IvTNPVertex vertex2;
    IvTNPVertex vertex3;
    
    // triangle faces
    vertex1.position=points[0];
    vertex2.position=points[11];
    vertex3.position=points[5];
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    
    vertex1.position=points[0];
    vertex2.position=points[5];
    vertex3.position=points[1];
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
   
    vertex1.position=points[0];
    vertex2.position=points[1];
    vertex3.position=points[7];
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    
    vertex1.position=points[0];
    vertex2.position=points[7];
    vertex3.position=points[10];
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    
    vertex1.position=points[0];
    vertex2.position=points[10];
    vertex3.position=points[11];
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    
    vertex1.position=points[1];
    vertex2.position=points[5];
    vertex3.position=points[9];
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    
    vertex1.position=points[5];
    vertex2.position=points[11];
    vertex3.position=points[4];
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    
    vertex1.position=points[11];
    vertex2.position=points[10];
    vertex3.position=points[2];
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    
    vertex1.position=points[10];
    vertex2.position=points[7];
    vertex3.position=points[6];
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    
    vertex1.position=points[7];
    vertex2.position=points[1];
    vertex3.position=points[8];
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    
    
    vertex1.position=points[3];
    vertex2.position=points[9];
    vertex3.position=points[4];
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    
    vertex1.position=points[3];
    vertex2.position=points[4];
    vertex3.position=points[2];
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    
    vertex1.position=points[3];
    vertex2.position=points[2];
    vertex3.position=points[6];
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    
    vertex1.position=points[3];
    vertex2.position=points[6];
    vertex3.position=points[8];
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    
    vertex1.position=points[3];
    vertex2.position=points[8];
    vertex3.position=points[9];

    
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    
    
    vertex1.position=points[4];
    vertex2.position=points[9];
    vertex3.position=points[5];
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    
    vertex1.position=points[2];
    vertex2.position=points[4];
    vertex3.position=points[11];
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    
    vertex1.position=points[6];
    vertex2.position=points[2];
    vertex3.position=points[10];
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    
    vertex1.position=points[8];
    vertex2.position=points[6];
    vertex3.position=points[7];
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    
    vertex1.position=points[9];
    vertex2.position=points[8];
    vertex3.position=points[1];
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    
    vertex1.position=points[0];
    vertex2.position=points[11];
    vertex3.position=points[5];
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    
    std::vector<IvTNPVertex> vertices2;
    vertices2=RefineTriangles(vertices, 4);
    sphereMesh->setVertexBuffer(vertices2, format);
    
    std::vector<unsigned int> indices;
    for(int i=0;i<vertices2.size();i++)
        indices.push_back(i);
    
    sphereMesh->setIndexBuffer(indices);

    return sphereMesh;
}

//-------------------------------------------------------------------------------
// @ HelperManager::CreateMeshInstance()
//-------------------------------------------------------------------------------
std::shared_ptr<MeshInstance>
HelperManager::CreateMeshInstance(const std::shared_ptr<Mesh> &mesh,
                                  const char* shaderName,
                                  const std::vector<std::string>& uniforms)
{
    std::shared_ptr<MeshInstance> meshInstance=std::make_shared<MeshInstance>();
    meshInstance->setMesh(mesh);
    meshInstance->setShader(shaderName);
    meshInstance->addShaderUniforms(uniforms);
    
    return meshInstance;
}
//------------------------------------------------------------------------------
//  PRIVATE METHODS
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ HelperManager::GetMiddlePoint()
//-------------------------------------------------------------------------------
IvVector3
HelperManager::GetMiddlePoint(IvVector3 p1, IvVector3 p2)
{
    IvVector3 mid=IvVector3(    (p1.x+p2.x)/2.0,
                                (p1.y+p2.y)/2.0,
                                (p1.z+p2.z)/2.0);
    
    return mid;
}
//-------------------------------------------------------------------------------
// @ HelperManager::GetMiddlePoint()
//-------------------------------------------------------------------------------
std::vector<IvTNPVertex>
HelperManager::RefineTriangles(std::vector<IvTNPVertex> vertices,int recursionLevel)
{
    std::vector<IvTNPVertex> newVertices;
    
    IvTNPVertex vertex1;
    IvTNPVertex vertex2;
    IvTNPVertex vertex3;
    
    for(int i=0;i<recursionLevel;i++)
    {
        newVertices.clear();
        for(int j=0;j<vertices.size();j+=3)
        {
            IvVector3 p1=GetMiddlePoint(vertices[j].position, vertices[j+1].position);
            IvVector3 p2=GetMiddlePoint(vertices[j+1].position, vertices[j+2].position);
            IvVector3 p3=GetMiddlePoint(vertices[j+2].position, vertices[j].position);
            
            float lengthJ=CalculateLength(vertices[j].position);
            float lengthJ1=CalculateLength(vertices[j+1].position);
            float lengthJ2=CalculateLength(vertices[j+2].position);
            
            float lengthP1=CalculateLength(p1);
            float lengthP2=CalculateLength(p2);
            float lengthP3=CalculateLength(p3);
            
            //replace triangle by 4 triangles
            vertex1.position=vertices[j].position/lengthJ;
            vertex2.position=p1/lengthP1;
            vertex3.position=p3/lengthP3;
            
            newVertices.push_back(vertex1);
            newVertices.push_back(vertex2);
            newVertices.push_back(vertex3);
            
            vertex1.position=vertices[j+1].position/lengthJ1;
            vertex2.position=p2/lengthP2;
            vertex3.position=p1/lengthP1;
            
            newVertices.push_back(vertex1);
            newVertices.push_back(vertex2);
            newVertices.push_back(vertex3);
            
            vertex1.position=vertices[j+2].position/lengthJ2;
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
        }
        vertices=newVertices;
    }
    return newVertices;
}

//-------------------------------------------------------------------------------
// @ HelperManager::CalculateLength()
//-------------------------------------------------------------------------------
float
HelperManager::CalculateLength(IvVector3 point)
{
    return sqrt(point.x*point.x+point.y*point.y+point.z*point.z);
}
