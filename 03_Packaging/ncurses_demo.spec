Name:		ncurses_demo
Version:	0.0.1
Release:	alt1
Source:		%name-%version.tar.gz
Group:		Other
URL:		http://uneex.org/LecturesCMC/LinuxApplicationDevelopment2026/03_Packaging
Summary:	Console text viewer
License:	BSD

BuildRequires:	libncursesw-devel

%description
Simple console text viewer on ncurses library

%prep
%setup

%build
%make_build

%install
%makeinstall_std
#%make_install DESTDIR=%buildroot PREFIX=%_bindir

%files
%doc README
%_bindir/%name
