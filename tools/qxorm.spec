%define version 1.4.3

Name: QxOrm
Version: %{version}
Release: 1%{?dist}
License: GPLv3+
Group: System Environment/Libraries
Summary: C++ Object Relational Mapping (ORM) library
URL: http://www.qxorm.com/

Source0: QxOrm_%{version}.zip

Buildroot: %{_tmppath}/%{name}-%{version}-%{release}-root
BuildRequires: boost-devel,qt-devel

%description
QxOrm is a C++ library designed to provide Object Relational Mapping (ORM) feature to C++ users.
QxOrm is developed by Lionel Marty, a software development engineer since 2003.
QxOrm provides many functionalities starting from a simple C++ setting function by class :

* persistence : communication with a lot of databases (with 1-1, 1-n, n-1 and n-n relationships)
* serialization : binary and xml format
* reflection (or introspection) : access to classes definitions, retrieve properties and call classes methods

%package devel
Summary: Development tools for QxOrm
Group: Development/Libraries
Requires: %{name}%{?_isa} = %{version}-%{release}

%description devel
The QxOrm-devel package contains header files and documentation necessary
for developing programs using the QxOrm

%package doc
Summary: Documentation for QxOrm
Group: Development/Libraries
Requires: %{name}%{?_isa} = %{version}-%{release}

%description doc
The QxOrm-devel package contains the Doxygen files for
QxOrm.

%prep
%setup -q -n QxOrm

%build

# Otherwise qmake installs everything into $PREFIX/lib
sed <QxOrm.pro >QxOrm.usrlib.pro "s#/lib#/%{_lib}#"
qmake-qt4 PREFIX=$RPM_BUILD_ROOT%{_usr} QxOrm.usrlib.pro
make release %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
make release-install

# We move the 'inl' into the include directory
# otherwise the name would be '/usr/inl'
mv $RPM_BUILD_ROOT%{_usr}/inl $RPM_BUILD_ROOT%{_includedir}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-,root,root)
%doc license.gpl3.txt
%{_libdir}/libQxOrm.so*

%files devel
%defattr(-,root,root)
%{_includedir}/*

%files doc
%defattr(-,root,root)
%doc doc

%clean
rm -rf $RPM_BUILD_ROOT

%changelog
* Wed Apr  3 2013 Erik Wasser <fuzz@namm.de> 1.2.5-1
- First version

