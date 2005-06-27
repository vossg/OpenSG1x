# Dummy Spec file for OpenSG dailybuilds
# Tricks RPM into using an already compiled OpenSG from the dailybuild
# Not nice, but recompiling everything just for RPM is not an option

%define name    OpenSG
%define release	1

Name: %{name}
Summary: OpenSG
Version: %{version}
Release: %{release}
Source: OpenSG-%{version}.tgz
URL: http://www.opensg.org
Group: System Environment/Libraries
BuildRoot: %{_tmppath}
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
# None necessary

%build
# None necessary

%install
mkdir -p $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/usr

pushd %{binroot}
cp -R include $RPM_BUILD_ROOT/usr
make INSTALL_DIR=$RPM_BUILD_ROOT/usr install-libs install-bin
popd
sed -i "s/prefix=\".*/prefix=\"\/usr\"/" $RPM_BUILD_ROOT/usr/bin/osg-config

mv $RPM_BUILD_ROOT/usr/include/OpenSG $RPM_BUILD_ROOT/usr/include/OpenSG-%{version}
ln -sf OpenSG-%{version} $RPM_BUILD_ROOT/usr/include/OpenSG

cd $RPM_BUILD_ROOT/usr/lib

mv opt OpenSG-%{version}-opt
mv dbg OpenSG-%{version}-dbg
ln -sf OpenSG-%{version}-opt OpenSG-%{version}
# Create version-based links
cd OpenSG-%{version}-dbg
for l in *;
do
    ln -sf $l ../$l.%{major}
    ln -sf $l ../$l.%{version}
    ln -sf OpenSG-%{version}/$l ../$l
done

cd ..

pushd %{opensgroot}

cp CHANGELOG COPYING INSTALL PEOPLE README VERSION $RPM_BUILD_ROOT/../BUILD

if test %{docfiles} == html
then
    cp -R Doc/Code/html $RPM_BUILD_ROOT/../BUILD
fi

popd
 
%clean

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
