# Simple URL parser

## Deployment

Essentials: 

* CMake version 3.14 or more (for FetchContent)
* C++ compiler supporting C++17 standard or more.

Parser allows to extract structural data from given URL according to RFC1738.

URL schemes supported:
* HTTPS
* FTP
* GOPHER
* NNTP
* WAIS
* FILE
* PROSPERO
* TELNET
* MAILTO
* NEWS

Parser implemented in a form of a class and has a method called parse. This method takes a std::string_view of a given URL either in a
form of <URL:<scheme>:<scheme-specific-part>> or just <scheme>:<scheme-specific-part>.



Unit tests are implemented using gtest.
