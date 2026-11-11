Name:		move
Version:	0.0.1
Release:	alt1
Source:		%name-%version.tar.gz
Group:		Other
URL:		http://uneex.org/LecturesCMC/LinuxApplicationDevelopment2026/03_Packaging
Summary:	simple files mover
License:	BSD


%description
The program moves file from original source path to destination path

%prep
%setup

%build
%make_build

%install
%makeinstall_std

%files
%doc README
%_bindir/%name
