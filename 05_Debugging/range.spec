Name:		range
Version:	0.0.1
Release:	alt1
Source:		%name-%version.tar.gz
Group:		Other
URL:		http://uneex.org/LecturesCMC/LinuxApplicationDevelopment2026/03_Packaging
Summary:	simple range generator
License:	BSD


%description
The program is simple range generator in python style.
Prints range sequence in column

%prep
%setup

%build
%make_build

%install
%makeinstall_std

%files
#%doc README
%_bindir/%name
