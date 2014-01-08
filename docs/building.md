---
layout: default
title: MQWeb &bull; Building MQWeb
doc_building: true
---

> This page is still a work in progress and is about building the upcoming
> release 0.0.9. For building prior versions of MQWeb read the README.md file.
> If you find a problem or an error please let it know
> by entering an [issue](https://github.com/fbraem/mqweb/issues).

Building MQWeb
==============

POCO
----
Before you start building the MQWeb HTTP daemon, you need to build 
[POCO](http://www.pocoproject.com). It's the only dependency you need to build.
[POCO](http://www.pocoproject.com) is a collection of modern, powerful open 
source C++ class libraries and frameworks for building network- and 
internet-based applications that run on desktop, server, mobile and embedded 
systems.

MQWeb uses the 1.5.2 release. This is a development release, but it is stable to
use. [Download](http://pocoproject.org/download/index.html) and extract the
archive on your system.

It's possible to build POCO as shared or static libraries. When you plan to use
POCO for other projects, you can opt for shared libraries. I've choosen static
ones, which makes it easier to install MQWeb: there's only one executable you
need to care about.

Premake
-------
MQWeb uses [premake](http://industriousone.com/premake) as build tool. Premake
can generate Visual Studio solutions, make files, 
[Codelite](http://codelite.org/) workspaces and more.

[Download](http://industriousone.com/premake/download) premake. Binaries simply 
need to be unpacked and placed somewhere on the system search path or any other 
convenient location.

WebSphere MQ
------------
To build MQWeb you need to install the WebSphere MQ SDK package. Make sure you
select this component when installing WebSphere MQ.

[Building MQWeb for Linux](#linux)  
[Building MQWeb for Windows](#windows)  
<a name="linux"> </a>
Linux
-----
###POCO

Create a directory *static* or *shared* in the directory where POCO is 
extracted. Make this directory the current working directory and run the
 *configure* command:

for static build

    ../configure --static --omit=Data/MySQL,Data/ODBC,Data/SQLite --no-tests --no-samples
   
for shared build

    ../configure --shared --omit=Data/MySQL,Data/ODBC,Data/SQLite --no-tests --no-samples
   
The data libraries are omitted because MQWeb doesn't need them. If you only
going to use POCO for MQWeb, there is also no need to build the tests and 
samples.
> You can also omit the build of the XML library, when you 
> define POCO\_UTIL\_NO\_XMLCONFIGURATION in *Poco/Foundation/Config.h*. You 
> also need to update premake.lua in the MQWeb folder and remove the XML 
> definitions.

Now you are ready to build POCO.

    make
    
When you have build POCO as shared libraries, it is recommended to install them.

    make install

###MQWeb

Download a MQWeb source archive from the 
[releases](https://github.com/fbraem/mqweb/releases) or just download an archive
from the [source tree](https://github.com/fbraem/mqweb). Note that the 
[master](https://github.com/fbraem/mqweb/tree/master) always points to the 
latest release, while the source tree with the latest branch points to code
that is work in progress and it is possible that it doesn't work.

Extract the archive and make the root folder of the archive the current
folder. Open *poco.lua* and *mq.lua* and see if you need to make any changes. 
Now run premake:

    premake4 gmake
   
for makefiles or create [Codelite](http://codelite.org/) workspaces with

    premake4 codelite

Premake will generate the build files in the *build* folder. In this folder
you'll find another folder with the name of the action you have specified when
running premake4. With *gmake* change the current folder to *build/gmake* and
run *make* to build MQWeb:

    make config=debug32

Other available build configurations are debug64, release32 and release64. Just
run *make help* for more information.

When you use [Codelite](http://codelite.org/), you'll find the workspaces in
*build/codelite*.

The result of your build will be placed in *bin/Debug* or *bin/Release*.

<a name="windows"> </a>
Windows
-------
To build MQWeb on Windows you need [Visual Studio](http://www.visualstudio.com).
MQWeb can be build with the free Express editions.

###POCO

Build the Foundation, JSON, XML, Util and Net libraries.
> You can omit the build of the XML library, when you 
> define POCO\_UTIL\_NO\_XMLCONFIGURATION in *Poco/Foundation/Config.h*. Open 
> premake.lua in the MQWeb folder and remove the XML definitions.

###MQWeb

Run premake

    premake4 vs2008

Now you have a Visual Studio solution file in the build folder.