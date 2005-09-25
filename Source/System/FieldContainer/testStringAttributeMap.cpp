#include <OSGConfig.h>

#include <iostream>

#include <OSGNode.h>
#include <OSGStringAttributeMap.h>


int main(int argc, char* argv[])
{
    OSG::osgInit(argc, argv);

    std::cerr << "StringAttributeMap attachment" << std::endl;

    // Create a node and give it a field container pointer attribute map
    // attachment.
    OSG::NodePtr node = OSG::Node::create();
    OSG::StringAttributeMapPtr attr_map = OSG::stringAttributeMap(node);

    // Query the attribute map again to make sure that we get the same one
    // back.
    OSG::StringAttributeMapPtr attr_map2 = OSG::stringAttributeMap(node);

    if ( attr_map == attr_map2 )
    {
        std::cerr << "Retrieved attribute map successfully" << std::endl;
    }
    else
    {
        std::cerr << "Second call to OSG::stringAttributeMap() returned a "
                  << "different attribute map!"
                  << std::endl;
    }

    if ( ! attr_map->hasAttribute("not there") )
    {
        std::cerr << "New attribute map is empty" << std::endl;
    }
    else
    {
        std::cerr << "New attribute map is supposed to be empty!" << std::endl;
    }

    OSG::beginEditCP(attr_map);
        // Verify conversion from char* to std::string in setAttribute.
        const char* test1_attr = "test1";
        const char* test1_value = "test1 value";
        attr_map->setAttribute(test1_attr, test1_value);

        // Simple std::string set usage.
        const std::string test2_attr("test2");
        const std::string test2_value("test2 value");
        attr_map->setAttribute(test2_attr, test2_value);

        // operator[] set operation.
        const std::string test3_attr("test3");
        const std::string test3_value("test3 value");
        (*attr_map)[test3_attr] = test3_value;
    OSG::endEditCP(attr_map);

    if ( attr_map->getKeys().size() == 3 )
    {
        std::cerr << "Correct number of attributes" << std::endl;
    }
    else
    {
        std::cerr << "Incorrect number of attributes ("
                  << attr_map->getKeys().size() << ") after adding 3"
                  << std::endl;
    }

    if ( attr_map->hasAttribute(test1_attr) )
    {
        std::cerr << "Attribute " << test1_attr << " added successfully"
                  << std::endl;
    }
    else
    {
        std::cerr << "Failed to add attribute " << test1_attr << std::endl;
    }

    if ( attr_map->hasAttribute(test2_attr) )
    {
        std::cerr << "Attribute " << test2_attr << " added successfully"
                  << std::endl;
    }
    else
    {
        std::cerr << "Failed to add attribute " << test2_attr << std::endl;
    }

    if ( attr_map->hasAttribute(test3_attr) )
    {
        std::cerr << "Attribute " << test3_attr << " added successfully"
                  << std::endl;
    }
    else
    {
        std::cerr << "Failed to add attribute " << test3_attr << std::endl;
    }

    unsigned int success_count(0);
    std::string test1_value_check;
    attr_map->getAttribute(test1_attr, test1_value_check);

    if ( test1_value == test1_value_check )
    {
        std::cerr << "[Attempt #1] Value for " << test1_attr << " is correct"
                  << std::endl;
        ++success_count;
    }
    else
    {
        std::cerr << "[Attempt #1] Value for " << test1_attr
                  << " is incorrect; '" << test1_value
                  << "' expected but got '" << test1_value_check << "'"
                  << std::endl;
    }

    test1_value_check = attr_map->getAttribute(test1_attr);

    if ( test1_value == test1_value_check )
    {
        std::cerr << "[Attempt #2] Value for " << test1_attr << " is correct"
                  << std::endl;
        ++success_count;
    }
    else
    {
        std::cerr << "[Attempt #2] Value for " << test1_attr
                  << " is incorrect; '" << test1_value
                  << "' expected but got '" << test1_value_check << "'"
                  << std::endl;
    }

    test1_value_check = (*attr_map)[test1_attr];

    if ( test1_value == test1_value_check )
    {
        std::cerr << "[Attempt #3] Value for " << test1_attr << " is correct"
                  << std::endl;
        ++success_count;
    }
    else
    {
        std::cerr << "[Attempt #3] Value for " << test1_attr
                  << " is incorrect; '" << test1_value
                  << "' expected but got '" << test1_value_check << "'"
                  << std::endl;
    }

    if ( success_count != 3 )
    {
        std::cerr << 3 - success_count
                  << " variation(s) of attribute value querying failed!!"
                  << std::endl;
    }

    std::string test2_value_check = attr_map->getAttribute(test2_attr);

    if ( test2_value == test2_value_check )
    {
        std::cerr << "Value for " << test2_attr << " is correct" << std::endl;
    }
    else
    {
        std::cerr << "Value for " << test2_attr << " is incorrect; '"
                  << test2_value << "' expected but got '" << test2_value_check
                  << "'" << std::endl;
    }

    std::string test3_value_check = (*attr_map)[test3_attr];

    if ( test3_value == test3_value_check )
    {
        std::cerr << "Value for " << test3_attr << " is correct" << std::endl;
    }
    else
    {
        std::cerr << "Value for " << test3_attr << " is incorrect; '"
                  << test3_value << "' expected but got '" << test3_value_check
                  << "'" << std::endl;
    }

    OSG::subRefCP(node);

    OSG::osgExit();

    return 0;
}
