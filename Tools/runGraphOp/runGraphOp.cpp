#include <iostream>
#include <OpenSG/OSGGraphOpFactory.h>
#include <OpenSG/OSGGraphOpSeq.h>
#include <OpenSG/OSGSceneFileHandler.h>


using namespace std;
OSG_USING_NAMESPACE


void usage() {
    cout << "Usage:" << endl;
    cout << "  runGraphOp <inFile> <outFile> <graphOp> [param1=value1 [param2=value2 ...]]" << endl;
    cout << endl;
    cout << "Supported GraphOps:" << endl;

    GraphOpFactory& factory = GraphOpFactory::the();
    if (factory.begin() == factory.end()) {
        cout << "  No GraphOps available!" << endl;
    } else {
        GraphOpFactory::iterator i = factory.begin();
        for (; i != factory.end(); ++i) {
            cout << "  " << i->first << endl;
        }
    }
}


int main(int argc, char** argv) {
    if (!osgInit(argc, argv)) {
        cout << "osgInit() failed" << endl;
        return EXIT_FAILURE;
    }

    if (argc < 4) {
        usage();
        return EXIT_FAILURE;
    }

    const char* inFile = argv[1];
    const char* outFile = argv[2];
    const char* graphOpName = argv[3];
    // Ignore parameters for now.

    GraphOpFactory& factory = GraphOpFactory::the();
    auto_ptr<GraphOp> graphOp(factory.create(graphOpName));
    if (!graphOp.get()) {
        cout << "Error: Could not create GraphOp of name " << graphOpName << endl;
        return EXIT_FAILURE;
    }

    cout << "Reading scene..." << endl;
    NodePtr scene = SceneFileHandler::the().read(inFile, NULL);
    if (!scene) {
        cout << "Error: Could not read scene " << inFile << endl;
        return EXIT_FAILURE;
    }

    cout << "Applying GraphOp..." << endl;
    if (!graphOp->traverse(scene)) {
        cout << "Error: Applying " << graphOpName << " GraphOp failed" << endl;
        return EXIT_FAILURE;
    }

    cout << "Writing scene..." << endl;
    if (!SceneFileHandler::the().write(scene, outFile)) {
        cout << "Error: Could not write scene " << outFile << endl;
        return EXIT_FAILURE;
    }
}
