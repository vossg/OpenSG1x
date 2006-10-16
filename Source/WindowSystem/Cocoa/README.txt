This directory contains an OpenSG window class that allows to integrate OpenSG into applications written using the native Mac OS UI API "Cocoa". This is the Objective-C API - there also exists another C++-based API called "Carbon" which cannot be used in conjunction with this library.

There is also a small test program called "testWindowCocoa.cpp" that demonstrates how to use the OpenSG Cocoa window class.

- Patrick Daehne


*IMPORTANT*:

Cocoa applications do not work correctly outside of application bundles, i.e. windows do not react to events etc. This means that you have to put the "testWindowCocoa" application into a bundle. Bundles are simply a special directory structure and some meta information in an XML file. The Finder does not (directly) allow to browse these directory structures, instead it presents them as one single application icon that can be double-clicked to start the application.

The directory structure looks like this:

testCocoa.app
  +- Contents
       +- Info.plist
       +- MacOS
            +-testWindowCocoa
            +-libOSGBase.dylib
            +-libOSGSystem.dylib
            +-libOSGWindowCocoa.dylib

The name of the top-level directory ("testCocoa.app") does not matter, it is simply used as the name of the application in the Finder window, but you have to add the suffix ".app".

The top-level directory contains one single subdirectory that has to be named "Contents".

The "Contents" directory contains "Info.plist", a XML file that contains meta information about the application, and another subdirectory named "MacOS".

The "MacOS" directory contains the application and (in our case) all libraries the application depends of.

You do not have to create this directory structure and the "Info.plist" file - it already exists in this directory. You only have to copy the test application and the libraries into the "testCocoa.app/Contents/MacOS" directory. Then, you have to adjust some pathes contained in the application and the libraries. Enter the following commands on the command line (or execute the script "adjustLibPathes"):

install_name_tool -change libOSGBase.dylib @executable_path/libOSGBase.dylib testWindowCocoa
install_name_tool -change libOSGSystem.dylib @executable_path/libOSGSystem.dylib testWindowCocoa
install_name_tool -change libOSGWindowCocoa.dylib @executable_path/libOSGWindowCocoa.dylib testWindowCocoa
install_name_tool -change libOSGBase.dylib @executable_path/libOSGBase.dylib libOSGSystem.dylib
install_name_tool -change libOSGBase.dylib @executable_path/libOSGBase.dylib libOSGWindowCocoa.dylib
install_name_tool -change libOSGSystem.dylib @executable_path/libOSGSystem.dylib libOSGWindowCocoa.dylib

Finally, you should be able to start the test application by double-clicking the application bundle in the Finder.
