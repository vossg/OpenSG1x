// -*- Mode:C++ -*-

// $Id: osg-conv.cpp,v 1.2 2004/11/20 01:18:17 dirk Exp $

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGGraphOpSeq.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGMaterialMergeGraphOp.h>
#include <OpenSG/OSGMergeGraphOp.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGPruneGraphOp.h>
#include <OpenSG/OSGSharePtrGraphOp.h>
#include <OpenSG/OSGSingleTypeGraphOp.h>
#include <OpenSG/OSGSplitGraphOp.h>
#include <OpenSG/OSGStringTokenizer.h>
#include <OpenSG/OSGStripeGraphOp.h>
#include <OpenSG/OSGVerifyGeoGraphOp.h>

#include <cstddef>
#include <cstdlib>
#include <getopt.h>
#include <libgen.h>
#include <sstream>
#include <string>
#include <unistd.h>

using namespace OSG;

namespace {
  
  struct program_options {

    program_options()
      : help(false),
        verbose(false),
        out_compressed(false),
        graphops("default"),
        in_filename_list(),
        out_filename()
    {}
    
    bool                     help;
    bool                     verbose;
    bool                     out_compressed;
    std::string              graphops;
    std::vector<std::string> in_filename_list;
    std::string              out_filename;
    
  };

  char const*   cmdl_options_short = "cg:hv";
  struct option cmdl_options_long[] = {
    {"compress", no_argument,       0, 'c'},
    {"graphops", required_argument, 0, 'g'},
    {"help",     no_argument,       0, 'h'},
    {"verbose",  no_argument,       0, 'v'},
    // {0,          optional_argument,       0, 0},
    {0,          no_argument,       0, 0}
  };
  
  int
  print_help_and_exit(int argc, char* argv[], program_options const& options, int exit_value)
  {
    std::cout << '\n'
              << basename(argv[0]) << " [-chv] [-g <string>] infile [infile2 ...] outfile\n"
              << '\n'
              << "  -c\tstore outfile compressed\t\t(default: "
              << (options.out_compressed ? "true" : "false") << ")\n"
              << "  -h\tthis help screen\t\t\t(default: "
              << (options.help ? "true" : "false") << ")\n"
              << "  -v\tbe verbose\t\t\t\t(default: "
              << (options.verbose ? "true" : "false") << ")\n"
              << "  -g\tgraph ops (colon separated string)\t(default: '"
              << (!options.graphops.empty() ? options.graphops : "<none specified>") << "')\n"
              << "    \tsupported: none, default,\n"
              << "    \t           materialmerge, merge, prune,\n"
              << "    \t           shareptr, split, stripe, verify\n"
              << std::endl;
    
    std::list<char const*> suffixes;
    
    SceneFileHandler::the().getSuffixList(suffixes, SceneFileType::OSG_READ_SUPPORTED);

    std::cout << "  infile [infile2 ...]\tinput file(s)\t\t(supported extensions: ";
    std::copy(suffixes.begin(), suffixes.end(),
              std::ostream_iterator<char const*>(std::cout, " "));
    std::cout << "\b)\n"
              << "\t\t\t\t\t\t(default: ";
    if (!options.in_filename_list.empty())
      std::copy(options.in_filename_list.begin(), options.in_filename_list.end(),
                std::ostream_iterator<std::string>(std::cout, " "));
    else
      std::cout << "<none specified> ";
    std::cout << "\b)"
              << std::endl;
    
    SceneFileHandler::the().getSuffixList(suffixes, SceneFileType::OSG_WRITE_SUPPORTED);

    std::cout << "  outfile\t\toutput file\t\t(supported extensions: ";
    std::copy(suffixes.begin(), suffixes.end(),
              std::ostream_iterator<char const*>(std::cout, " "));
    std::cout << "\b)\n"
              << "\t\t\t\t\t\t(default: "
              << (!options.out_filename.empty() ? options.out_filename : "<none specified>")
              << ")\n";
    std::cout << std::endl;

    osgExit();
    
    exit(exit_value);
  }
  
  bool
  parse_command_line(int argc, char* argv[], program_options& options)
  {
    bool    result = true;
    ssize_t cmdl_option_index = 0;

    ssize_t c;
    
    while (EOF != (c = getopt_long_only(argc, argv,
                                        cmdl_options_short, cmdl_options_long,
                                        &cmdl_option_index))) {

      switch (c) {
      case 'c':
        options.out_compressed = true;
        break;

      case 'g':
        if (optarg)
          options.graphops = std::string(optarg);
        else {
          std::cout << "argument required for option -"
                    << cmdl_options_long[cmdl_option_index].name
                    << std::endl;
          result = false;
        }
        break;

      case 'h':
        options.help = true;
        break;

      case 'v':
        options.verbose = true;
        break;

      default:
        result = false;
        break;
      }

      if (!result)
        break;
    }

    // check the remaining cmdline arguments
    if (result && optind < argc) {
      if (!options.in_filename_list.empty())
        options.in_filename_list.clear();
      
      for (size_t i = optind; i < (argc - 1); ++i)
        options.in_filename_list.push_back(argv[i]);

      options.out_filename = std::string(argv[argc - 1]);
    }
    
    return result;
  }
  
  void
  progress_cb(UInt32 p)
  {
    std::cout << "loaded " << p << "%\r";
  }
  
}

int
main(int argc, char* argv[])
{
  osgInit(argc, argv);
  
  program_options options;
  
  if (!parse_command_line(argc, argv, options))
    print_help_and_exit(argc, argv, options, EXIT_FAILURE);

  if (options.help)
    print_help_and_exit(argc, argv, options, EXIT_SUCCESS);

  if (options.in_filename_list.empty()) {
    std::cout << "\nno input file(s) specified; terminating" << std::endl;
    print_help_and_exit(argc, argv, options, EXIT_FAILURE);
  }

  if (options.out_filename.empty()) {
    std::cout << "\nno output file specified; terminating" << std::endl;
    print_help_and_exit(argc, argv, options, EXIT_FAILURE);
  }
  
  NodePtr scene_root = Node::create();
  
  beginEditCP(scene_root, Node::CoreFieldMask);
  {
    scene_root->setCore(Group::create());
  }
  endEditCP(scene_root, Node::CoreFieldMask);

  SceneFileHandler::the().setReadProgressCB(progress_cb);
  
  NodePtr fnode;
  
  for (std::vector<std::string>::iterator current = options.in_filename_list.begin();
       current != options.in_filename_list.end();
       ++current) {

    if (options.verbose)
      std::cout << "loading file: " << *current << std::endl;
    
    try {
      // don't use graphops here, we gonna do this later on the merged scene
      NodePtr fnode = SceneFileHandler::the().read((*current).c_str(), 0);
      
      if(NullFC == fnode) {
        std::cout << "unable to read file '" << *current << "'; skipping it" << std::endl;
      } else {
        beginEditCP(scene_root, Node::ChildrenFieldMask);
        {
          scene_root->addChild(fnode);
        }
        endEditCP(scene_root, Node::ChildrenFieldMask);
      }
    }
    
    catch(std::exception &e) {
      std::cout << "received exception '" << e.what() << "'while loading file '" << *current
                << "'; terminating" << std::endl;

      osgExit();

      return EXIT_FAILURE;
    }
  }
  
  if (std::string("none") != options.graphops) {
    GraphOpSeq* graphOpSeq = new GraphOpSeq;

    if (std::string("default") == options.graphops) {
      options.graphops = "verify:stripe:shareptr:verify";

      if (options.verbose)
        std::cout << "using default graph ops '" << options.graphops << "'" << std::endl;
    }
    
    std::string token_string(options.graphops);
    
    std::replace(token_string.begin(), token_string.end(), ':', ' '); // ':' -> ' '
    
    StringTokenizer tokens(token_string);
    
    while (tokens.hasNext()) {
      const std::string& current = tokens.getNext();
      GraphOp*           graph_op = 0;
      
      if      ("materialmerge" == current) {
        graph_op = new MaterialMergeGraphOp /* ("MaterialMerge") */ ;
      }
      
      else if ("merge" == current) {
        graph_op = new MergeGraphOp /* ("Merge") */ ;
      }
      
      else if ("prune" == current) {
        graph_op = new PruneGraphOp(1.0, PruneGraphOp::SUM_OF_DIMENSIONS /* , "Prune" */ );
      }
      
      else if ("shareptr" == current) {
        graph_op = new SharePtrGraphOp /* ("ShareCores") */ ;
      }

#if 0
      else if ("singletype" == current) {
        graph_op = new SingleTypeGraphOp<T> /* ("") */ ;
      }
#endif
      
      else if ("split" == current) {
        graph_op = new SplitGraphOp /* ("Split", 10000) */ ;
      }
      
      else if ("stripe" == current) {
        graph_op = new StripeGraphOp /* ("Stripe") */ ;
      }
      
      else if ("verify" == current) {
        graph_op = new VerifyGeoGraphOp /* ("Verify", repair = true) */ ;
      }
      
      if (0 != graph_op) {
        if (options.verbose)
          std::cout << "adding '" << graph_op->getClassname() << "' to sequence" << std::endl;
        
        graphOpSeq->addGraphOp(graph_op);
      } else {
        std::cout << "unknown graphop '" << current << "' encountered" << std::endl;
      }
    }
    
    if (options.verbose)
      std::cout << "applying graph operations" << std::endl;
      
    graphOpSeq->run(scene_root);
    
    delete graphOpSeq;
  } else {
    if (options.verbose)
      std::cout << "not using any graph ops" << std::endl;
  }
  
  if (options.out_compressed)
    options.out_filename += ".gz";

  if (options.verbose)
    std::cout << "storing file '" << options.out_filename.c_str() << "'" << std::endl;
  
  SceneFileHandler::the().write(scene_root, options.out_filename.c_str(), options.out_compressed);

  osgExit();
  
  return EXIT_SUCCESS;
}

// $Id: osg-conv.cpp,v 1.2 2004/11/20 01:18:17 dirk Exp $
