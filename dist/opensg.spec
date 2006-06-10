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
%setup -q -n %{name}
#%setup -DT -q -n %{name}

%build
qt=`ls -1d %{_libdir}/qt* | tail -1`
./configure  --prefix=$RPM_BUILD_ROOT/usr --enable-glut --enable-jpg --enable-png --enable-tif --enable-gif --enable-qt --with-qt=$qt
export OSGSUBPARJOBS=`fgrep processor /proc/cpuinfo | wc -l`
make
make opt

%install
%ifarch x86_64
libsuffix=64
%else
libsuffix=''
%endif
mkdir -p $RPM_BUILD_ROOT
rm -rf  $RPM_BUILD_ROOT/usr
mkdir -p $RPM_BUILD_ROOT/usr

make install > /dev/null
sed -e "s/prefix=\".*/prefix=\"\/usr\"/" \
    -e "s|${exec_prefix}/lib/|${exec_prefix}/lib$libsuffix/OpenSG-1.6.0-|" \
    < $RPM_BUILD_ROOT/usr/bin/osg-config > $RPM_BUILD_ROOT/usr/bin/osg-config.sed
mv $RPM_BUILD_ROOT/usr/bin/osg-config.sed $RPM_BUILD_ROOT/usr/bin/osg-config
chmod 755 $RPM_BUILD_ROOT/usr/bin/osg-config

cd $RPM_BUILD_ROOT/usr/lib

mv opt OpenSG-%{version}-opt
mv dbg OpenSG-%{version}-dbg
ln -sf OpenSG-%{version}-opt OpenSG-%{version}
# Create version-based links
cd OpenSG-%{version}-opt
for l in *;
do
    ln -sf $l ../$l.1
    ln -sf $l ../$l.%{version}
    ln -sf OpenSG-%{version}/$l ../$l
done

if test %{_libdir} != "/usr/lib"
then
    cd $RPM_BUILD_ROOT/usr
    mv lib $RPM_BUILD_ROOT%{_libdir}
fi

%clean
rm -rf $RPM_BUILD_ROOT

%pre

%post

%preun

%postun

%files
%defattr(-, root, root)
/usr/bin
%{_libdir}/lib*
%{_libdir}/*opt

%files devel
%defattr(-, root, root)
/usr/include
%{_libdir}/*dbg

%doc CHANGELOG COPYING INSTALL PEOPLE README VERSION ${docfiles}

%changelog
