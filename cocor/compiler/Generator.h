/*----------------------------------------------------------------------
Compiler Generator Coco/R,
Copyright (c) 1990, 2004 Hanspeter Moessenboeck, University of Linz
extended by M. Loeberbauer & A. Woess, Univ. of Linz
ported to C++ by Csaba Balazs, University of Szeged
with improvements by Pat Terry, Rhodes University

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

As an exception, it is allowed to write an extension of Coco/R that is
used as a plugin in non-free software.

If not otherwise stated, any source code generated by Coco/R (other than
Coco/R itself) does not fall under the GNU General Public License.
-----------------------------------------------------------------------*/

#if !defined(COCO_GENERATOR_H__)
#define COCO_GENERATOR_H__

#include <stdio.h>
#include "Tab.h"
#include "Parser.h"

namespace Coco {

class Generator {
public:
	Generator(Tab *tab, Errors *errors);
  FILE* OpenFrame(const std::string& frame);
  FILE* OpenGen(const std::string& genName);
	void GenCopyright();
	void GenPrefixFromNamespace();
  void SkipFramePart(const std::string& stop);
  void CopyFramePart(const std::string& stop);

private:
	FILE* fram;
	FILE* gen;
	Tab *tab;
  std::string frameFile;
	Errors *errors;

  void CopyFramePart(const std::string& stop, bool generateOutput);

};

} // namespace

#endif // !defined(COCO_GENERATOR_H__)
