# Spec file for OpenSG Source RPM

%define name    OpenSG
%define release	1

Name: %{name}
Summary: OpenSG
Version: %{version}
Release: %{release}
Source: %{name}-%{version}.tgz
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
gmake

%install
mkdir -p $RPM_BUILD_ROOT
rm -rf  $RPM_BUILD_ROOT/usr
mkdir -p $RPM_BUILD_ROOT/usr

make install > /dev/null
sed -i "s/prefix=\".*/prefix=\"\/usr\"/" $RPM_BUILD_ROOT/usr/bin/osg-config

cd $RPM_BUILD_ROOT/usr/lib

mv opt OpenSG-1.6.0-opt
mv dbg OpenSG-1.6.0-dbg
ln -sf OpenSG-1.6.0-opt OpenSG-1.6.0
# Create version-based links
cd OpenSG-1.6.0-opt
for l in *;
do
    ln -sf $l ../$l.1
    ln -sf $l ../$l.1.6.0
    ln -sf OpenSG-1.6.0/$l ../$l
done

%clean
rm -rf $RPM_BUILD_ROOT

%pre

%post

%preun

%postun

%files
%defattr(-, root, root)
/usr/bin
/usr/lib/lib*
/usr/lib/*opt

%files devel
%defattr(-, root, root)
/usr/include
/usr/lib/*dbg

%doc CHANGELOG COPYING INSTALL PEOPLE README VERSION ${docfiles}

%changelog
