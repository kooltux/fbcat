Name: fbcat
Version:    1.0.0
Release:    0
Summary:	Framebuffer Text Display
URL:	https://github.com/kooltux/fbcat
Source: %{name}-%{version}.tar.gz
Source1001: fbcat.manifest
License: MIT
Group: Graphics & UI Framework/Service
BuildRequires: pkgconfig(elementary)

%description
Utility tool to display EFL text on a linux framebuffer device.

%prep
%setup -q
cp %{SOURCE1001} .

%build
%__make %{?_smp_mflags}

%install
mkdir -p %{buildroot}%{_bindir}
install -m 0755 fbcat.real %{buildroot}%{_bindir}/fbcat.real
install -m 0755 fbcat.sh %{buildroot}%{_bindir}/fbcat

%files
%manifest fbcat.manifest
%defattr(-,root,root,-)
%{_bindir}/*
