This directory contains an OpenSG window class that allows to integrate OpenSG into applications written using the native Mac OS UI API "Carbon". This is the C++ API - there also exists another Objective-C-based API called "Cocoa" which cannot be used in conjunction with this library.

There is also a small test program called "testWindowCarbon.cpp" that demonstrates how to use the OpenSG Carbon window class.

- Patrick Daehne


*IMPORTANT*:

Carbon applications do not work correctly outside of application bundles, i.e. windows do not react to events etc. This means that you have to put the "testWindowCarbon" application into a bundle. Bundles are simply a special directory structure and some meta information in an XML file. The Finder does not (directly) allow to browse these directory structures, instead it presents them as one single application icon that can be double-clicked to start the application.

The directory structure looks like this:

testCarbon.app
  +- Contents
       +- Info.plist
       +- MacOS
            +-testWindowCarbon
            +-libOSGBase.dylib
            +-libOSGSystem.dylib
            +-libOSGWindowCarbon.dylib

The name of the top-level directory ("testCarbon.app") does not matter, it is simply used as the name of the application in the Finder window, but you have to add the suffix ".app".

The top-level directory contains one single subdirectory that has to be named "Contents".

The "Contents" directory contains "Info.plist", a XML file that contains meta information about the application, and another subdirectory named "MacOS".

The "MacOS" directory contains the application and (in our case) all libraries the application depends of.

You do not have to create this directory structure and the "Info.plist" file - it already exists in this directory. You only have to copy the test application and the libraries into the "testCarbon.app/Contents/MacOS" directory. Then, you have to adjust some pathes contained in the application and the libraries. Enter the following commands on the command line (or execute the script "adjustLibPathes"):

install_name_tool -change libOSGBase.dylib @executable_path/libOSGBase.dylib testWindowCarbon
install_name_tool -change libOSGSystem.dylib @executable_path/libOSGSystem.dylib testWindowCarbon
install_name_tool -change libOSGWindowCarbon.dylib @executable_path/libOSGWindowCarbon.dylib testWindowCarbon
install_name_tool -change libOSGBase.dylib @executable_path/libOSGBase.dylib libOSGSystem.dylib
install_name_tool -change libOSGBase.dylib @executable_path/libOSGBase.dylib libOSGWindowCarbon.dylib
install_name_tool -change libOSGSystem.dylib @executable_path/libOSGSystem.dylib libOSGWindowCarbon.dylib

Finally, you should be able to start the test application by double-clicking the application bundle in the Finder.
