%bcond_with harbour

Name:       harbour-trillium

Summary:    Trillium Client for Sailfish OS
Version:    0.1.0
Release:    1
Group:      Applications/Office
License:    GPLv3
URL:        https://github.com/mezmerize/harbour-trillium
Source0:    %{name}-%{version}.tar.bz2

Requires:   sailfishsilica-qt5 >= 0.10.9
BuildRequires:  pkgconfig(sailfishapp) >= 1.0.2
BuildRequires:  pkgconfig(sailfishsecrets)
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  pkgconfig(Qt5Network)
BuildRequires:  desktop-file-utils

%description
A native Trillium client for Sailfish OS built in C++ and Qt/QML that allows you to view and navigate your notes on a TrilliumNext server.

%prep
%setup -q -n %{name}-%{version}

%build
%if %{with harbour}
%qmake5 CONFIG+=harbour
%else
%qmake5
%endif

%make_build

%install
%qmake5_install

desktop-file-install --delete-original       \
  --dir %{buildroot}%{_datadir}/applications             \
   %{buildroot}%{_datadir}/applications/*.desktop

%files
%defattr(-,root,root,-)
%{_bindir}/%{name}
%{_datadir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/*/apps/%{name}.png
