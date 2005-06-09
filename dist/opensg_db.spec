# Spec file for OpenSG.
%define name    OpenSG
%define version	1.4
%define release	1

Name: %{name}
Summary: OpenSG
Version: %{version}
Release: %{release}
Source: %{name}-%{version}-src.tgz
URL: http://www.opensg.org
Group: System Environment/Libraries
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-buildroot
License: LGPL

Requires: libjpeg
Requires: libpng
Requires: libungif
Requires: libtiff
Requires: glut >= 3.7
Requires: qt >= 3.1
BuildRequires: libungif-devel
BuildRequires: libtiff-devel
BuildRequires: glibc-devel
BuildRequires: libjpeg-devel
BuildRequires: libpng-devel
BuildRequires: glut >= 3.7
BuildRequires: qt-devel >= 3.1
Provides: OpenSG = %{version}-%{release}
AutoReqProv: no
Prefix: /usr

%description
OpenSG

%package devel
Summary: OpenSG Headers
Group: System Environment/Libraries
Requires: OpenSG = %{version}-%{release}
Provides: OpenSG-devel = %{version}-%{release}

%description devel
The header files and libraries needed for developing programs using OpenSG.

%prep
rm -rf $RPM_BUILD_ROOT
# For now don't keep unpacking
%setup -q -n %{name}
#%setup -DT -q -n %{name}

%build
# Don't need to run autogen with most tarballs since we run it before compressing it.
qt=`ls -1d /usr/lib/qt* | tail -1`
./configure  --prefix=$RPM_BUILD_ROOT/usr --enable-glut --enable-jpg --enable-png --enable-tif --enable-gif --enable-qt --with-qt=$qt
gmake opt
#gmake

%install
mkdir -p $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/usr
gmake install
sed -i "s/prefix=\".*/prefix=\"\/usr\"/" $RPM_BUILD_ROOT/usr/bin/osg-config

cd $RPM_BUILD_ROOT/usr/lib
ln -sf opt/libOSGBase.so libOSGBase.so
ln -sf opt/libOSGSystem.so libOSGSystem.so
ln -sf opt/libOSGWindowX.so libOSGWindowX.so
ln -sf opt/libOSGWindowGLUT.so libOSGWindowGLUT.so
ln -sf opt/libOSGWindowQT.so libOSGWindowQT.so

%clean
rm -rf $RPM_BUILD_ROOT

%pre

%post

%preun

%postun

%files
%defattr(-, root, root)
/usr/bin
/usr/lib/libOSGBase.so
/usr/lib/libOSGSystem.so
/usr/lib/libOSGWindowX.so
/usr/lib/libOSGWindowGLUT.so
/usr/lib/libOSGWindowQT.so
/usr/lib/opt

%files devel
%defattr(-, root, root)
/usr/include

%doc CHANGELOG COPYING INSTALL PEOPLE README VERSION

%changelog
