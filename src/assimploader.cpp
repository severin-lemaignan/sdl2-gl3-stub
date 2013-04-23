#include <iostream>
#include <fstream>

#include <glm/glm.hpp>

#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>

#include "assimploader.h"
#include "shader.h" // for attribute locations

using namespace std;
using namespace glm;

// currently these are hardcoded
static const std::string basepath = "../../test/models/OBJ/";
static const std::string modelname = "spider.obj";

bool AssimpLoader::Import3DFromFile( const string& pFile)
{
    //check if file exists
    ifstream fin(pFile.c_str());
    if(!fin.fail())
    {
        fin.close();
    }
    else
    {
        cerr << "Couldn't open file: " << pFile << endl;
        return false;
    }

    scene = importer.ReadFile( pFile, aiProcessPreset_TargetRealtime_Quality);

    // If the import failed, report it
    if( !scene)
    {
        cerr << importer.GetErrorString() << endl;
        return false;
    }

    // Now we can access the file's contents.
    cout << "Import of scene " + pFile + " succeeded." << endl;

    // We're done. Everything will be cleaned up by the importer destructor
    return true;
}
void AssimpLoader::loadNodes(Node& root, vector<Node>& nodes)
{
    size_t nbNodes = countNodes(scene->mRootNode);
    cout << "Loading " << nbNodes << " nodes..." << endl;

    nodes.reserve(nbNodes); // allocate now enough space to prevent later vector resizing (this would cause pointer invalidation).

    root = *recursiveLoad(scene->mRootNode, nodes);
}

size_t AssimpLoader::countNodes(const aiNode* nd) {

    size_t count = 1;

    for (int n = 0; n < nd->mNumChildren; ++n)
    {
        count += countNodes(nd->mChildren[n]);
    }

    return count;
}

Node* AssimpLoader::recursiveLoad(const aiNode* nd, vector<Node>& nodes)
{

    Node node;
    node.name = string(nd->mName.C_Str());
    cout << endl << "Created node " << node.name << endl;

    aiMatrix4x4 m = nd->mTransformation;
    m.Transpose();
    node.transformation =
        mat4(m.a1, m.a2, m.a3, m.a4,
             m.b1, m.b2, m.b3, m.b4,
             m.c1, m.c2, m.c3, m.c4,
             m.d1, m.d2, m.d3, m.d4 );

    for (int n = 0; n < nd->mNumMeshes; ++n)
    {
        Mesh out;
        makeMesh(*scene->mMeshes[nd->mMeshes[n]], out, node);
        node.meshes.push_back(out);
    }

    for (int n = 0; n < nd->mNumChildren; ++n)
    {
        Node* child = recursiveLoad(nd->mChildren[n], nodes);
        node.children.push_back(child);
    }

    nodes.push_back(node); // add myself to the list of nodes
    return &nodes.back(); // returns the pointer to my own copy in 'nodes'
}

void AssimpLoader::makeMesh(const aiMesh &in, Mesh &out, const Node& node)
{
    out.node = &node;
    out.name = string(in.mName.C_Str());
    cout << "Created mesh " << out.name << endl;

    const aiMaterial* material = scene->mMaterials[in.mMaterialIndex];
    fillMaterial(*material, out.diffuse);

    // One VertexArrayObject per object
    // All the state (vertex buffer, element buffer, vertex attrib) is ssaved in
    // the VAO.
    glGenVertexArrays(1, &out.vao);
    glBindVertexArray(out.vao);


    /*create face array*/
    GLuint *facearray;
    facearray = (GLuint *)malloc(sizeof(GLuint) * in.mNumFaces * 3);
    unsigned int faceIndex = 0;

    for ( unsigned int t = 0; t < in.mNumFaces; ++t )
    {
        const struct aiFace& face = in.mFaces[t];
        memcpy(&facearray[faceIndex], face.mIndices, 3 * sizeof( GLuint ) );
        faceIndex += 3;
    }
    out.numfaces = in.mNumFaces;


    /*face vbo*/
    glGenBuffers( 1, &out.ibo );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, out.ibo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * (in.mNumFaces * 3), facearray, GL_STATIC_DRAW);


    /* buffer for vertex positions*/
    GLfloat *vertexarray;
    vertexarray = ( GLfloat *)malloc(sizeof( GLfloat ) * in.mNumVertices * 3);
    unsigned int vertexindex = 0;

    if ( in.HasPositions() )
    {
        for ( unsigned int t = 0; t < in.mNumVertices; ++t )
        {

            vertexarray[ vertexindex ] = in.mVertices[ t ].x;
            vertexarray[ vertexindex + 1 ] = in.mVertices[ t ].y;
            vertexarray[ vertexindex + 2 ] = in.mVertices[ t ].z;
            vertexindex += 3;
        }
        //GL_ARRAY_BUFFER
        glGenBuffers( 1, &out.vbo );
        glBindBuffer( GL_ARRAY_BUFFER, out.vbo );
        glBufferData( GL_ARRAY_BUFFER, sizeof(float) * ( in.mNumVertices * 3 ), vertexarray, GL_STATIC_DRAW );
    }

    out.numvertices = in.mNumVertices;

    glVertexAttribPointer(Shader::POSITION_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    /*debug for faces or elements*/
    /*for( unsigned int x=0; x < in.mNumVertices ; ++x )
    {
        printf("%d  array %d x %f y %f z %f \n",x,facearray[ x ], vertexarray[ facearray[ x ] ], vertexarray[ facearray[ x ] + 1 ], vertexarray[ facearray[ x ] + 2 ] 	);
    }*/

    free( vertexarray );
    free( facearray );

}


void AssimpLoader::fillMaterial(const aiMaterial& mat, vec4& diffuse) {

    aiColor3D aiDiffuse;

    mat.Get(AI_MATKEY_COLOR_DIFFUSE, aiDiffuse);
    diffuse = vec4(aiDiffuse.r, aiDiffuse.g, aiDiffuse.b, 1.0f);
}


