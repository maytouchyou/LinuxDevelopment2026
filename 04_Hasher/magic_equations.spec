Name:		magic_equations
Version:	0.0.1
Release:	alt1
Source:		%name-%version.tar.gz
Group:		Other
URL:		http://uneex.org/LecturesCMC/LinuxApplicationDevelopment2026/03_Packaging
Summary:	mathematical expression solver
License:	BSD


%description
The program finds the shortest mathematical expression that uses numbers from 
the first list and +-*/ operators along with parentheses to represent numbers 
in the second list. Lists are separated by a zero

%prep
%setup

%build
%make_build

%install
%makeinstall_std

%files
#%doc README
%_bindir/%name
