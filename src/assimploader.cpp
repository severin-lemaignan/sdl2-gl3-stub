#include <iostream>
#include <fstream>

#include <assimp/postprocess.h>

#include "assimploader.h"

using namespace std;

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
    recursiveLoad(scene->mRootNode, root, nodes);
}

void AssimpLoader::recursiveLoad(const struct aiNode* nd, Node& parent, vector<Node>& nodes)
{

    Node node;
    node.name = string(nd->mName.C_Str());
    cout << endl << "Created node " << node.name << endl;

    for (int n = 0; n < nd->mNumMeshes; ++n)
    {
        Mesh out;
        makeMesh(*scene->mMeshes[nd->mMeshes[n]], out, node);
        node.meshes.push_back(out);
    }

    for (int n = 0; n < nd->mNumChildren; ++n)
    {
    recursiveLoad(nd->mChildren[n], node, nodes);
    }

    // must be done *after* the recursion, else recursiveLoad(..., node, ...) would not be useful ('node' discarded)
    nodes.push_back(node);
    parent.children.push_back(&nodes.back()); // tracks the node we just added to 'nodes'

}

void AssimpLoader::makeMesh(const aiMesh &in, Mesh &out, const Node& node)
{
    out.node = &node;
    out.name = string(in.mName.C_Str());
    cout << "Created mesh " << out.name << endl;


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
    unsigned int vetexindex = 0;

    if ( in.HasPositions() )
    {
        for ( unsigned int t = 0; t < in.mNumVertices; ++t )
        {

            vertexarray[ vetexindex ] = in.mVertices[ t ].x;
            vertexarray[ vetexindex + 1 ] = in.mVertices[ t ].y;
            vertexarray[ vetexindex + 2 ] = in.mVertices[ t ].z;
            vetexindex += 3;
        }
        //GL_ARRAY_BUFFER
        glGenBuffers( 1, &out.vbo );
        glBindBuffer( GL_ARRAY_BUFFER, out.vbo );
        glBufferData( GL_ARRAY_BUFFER, sizeof(float) * ( in.mNumVertices * 3 ), vertexarray, GL_STATIC_DRAW );
    }

    out.numvertices = in.mNumVertices;

    /*debug for faces or elements*/
    /*for( unsigned int x=0; x < in.mNumVertices ; ++x )
    {
        printf("%d  array %d x %f y %f z %f \n",x,facearray[ x ], vertexarray[ facearray[ x ] ], vertexarray[ facearray[ x ] + 1 ], vertexarray[ facearray[ x ] + 2 ] 	);
    }*/

    free( vertexarray );
    free( facearray );

}





