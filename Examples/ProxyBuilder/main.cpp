#include <OpenSG/OSGConfig.h>

#include <iostream>
#include <vector>

#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGProxyGroup.h>
#include <OpenSG/OSGGeometry.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/OSGChunkMaterial.h>

#include <OSGProxyBuilder.h>

using namespace osg;

std::vector<ChunkMaterialPtr> materials;

MaterialPtr checkMaterial(MaterialPtr mat)
{
    UInt32 m,c;
    ChunkMaterialPtr chunkMat = ChunkMaterialPtr::dcast(mat);
    StateChunkPtr c1,c2;
    bool equal;

    if(chunkMat == NullFC)
        return mat;

    for(m = 0 ; m < materials.size() ; ++m)
    {
        if(materials[m] == chunkMat)
            return mat;
        if(chunkMat->getChunks().size() == 
           materials[m]->getChunks().size())
        {
            equal = true;
            for(c = 0 ; c < chunkMat->getChunks().size() ; ++c)
            {
                c2 = materials[m]->getChunks()[c];
                c1 = chunkMat->getChunks()[c];
                if(c1 != c2)
                {
                    equal = false;
                }
            }
            if(equal == true)
            {
                return materials[m];
            }
        }
    }
    materials.push_back(chunkMat);
    return mat;
}

Action::ResultE optMaterial(NodePtr& node)
{   
    MaterialPtr      mat;
	MaterialGroupPtr matGroup = MaterialGroupPtr::dcast(node->getCore());

    if(matGroup != NullFC)
    {
        mat = checkMaterial(matGroup->getMaterial());
        if(mat != matGroup->getMaterial())
            matGroup->setMaterial(mat);
    }
	GeometryPtr geo = GeometryPtr::dcast(node->getCore());
    if(geo != NullFC)
    {
        mat = checkMaterial(geo->getMaterial());
        if(mat != geo->getMaterial())
            geo->setMaterial(mat);
    }
    return Action::Continue; 
}

int main(int argc, char *argv[])
{
    int i;
    char *opt;
    UInt32 threshold=1000;
    bool concurrent=false;
    bool zip=false;
    std::vector<std::string> files;
    std::string prefix = "scene";

    OSG::osgInit(argc, argv);

    for(int i = 1 ; i < argc ; ++i)
    {
        if(argv[i][0] == '-') {
            switch(argv[i][1])
            {
                case 't':
                    opt = argv[i][2] ? opt=argv[i]+2 : opt=argv[++i];
                    threshold = atoi(opt);
                    break;
                case 'c':
                    concurrent = true;
                    break;
                case 'z':
                    zip = true;
                    break;
                case 'o':
                    opt = argv[i][2] ? opt=argv[i]+2 : opt=argv[++i];
                    prefix = opt;
                    break;
                default:
                    printf("%s -t NUM -c -z -o NAME\n",argv[0]);
                    printf(" -t NUM = positions threshold to write proxy\n");
                    printf(" -c proxy for concurrent load\n");
                    printf(" -z zip output\n");
                    printf(" -h this text\n");
                    exit(0);
            }
        } else {
            files.push_back(argv[i]);
        }
    }

    OSG::NodePtr root = Node::create();
    beginEditCP(root);
    root->setCore(Group::create());
    ProxyBuilder::start(prefix,threshold,concurrent,zip);
    for(i = 0 ; i < files.size() ; ++i)
    {
        printf("Parsing %s...\n",files[i].c_str());
        OSG::NodePtr child = SceneFileHandler::the().read(files[i].c_str());
        root->addChild(child);
    }
    endEditCP(root);

    ProxyBuilder::stop();

    optMaterial(root);
    OSG::SceneFileHandler::the().write(root,(prefix+".osb").c_str(),zip);

    return 0;
}
