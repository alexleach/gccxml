.. title:: GCC-XML Licensing

=================
GCC-XML Licensing
=================

GCC-XML has two major components that were developed independently and are
licensed separately.

* The ``gccxml`` command-line tool and other software in the ``GCC_XML`` source
  directory is distributed under the OSI-approved 3-clause BSD License.

* The ``gccxml_cc1plus`` backend and other software in the ``GCC`` directory is
  distributed under the GNU General Public License as published by the Free
  Software Foundation; either version 2 of the License, or (at your option) any
  later version.

=======================
gccxml_plugin Licensing
=======================

* The code for the ``gccxml`` tool, mentioned above, has been removed from the
  ``gccxml_plugin`` fork. There's no reason it can't be re-added, but this does
  mean that at the moment, the code in this repository is all GNU GPL licensed.

More specifically:

* xml.c
  
  This is more or less exactly the same as the source code used in the
  ``gccxml_cc1plus`` binary, so falls under the same GPL licensing mentioned
  above.

* gccxml_plugin.[ch]

  This code was developed specifically for ``gccxml_plugin``, and can
  therefore be licensed differently. For simplicity's sake - I also
  have a lot of respect for GNU and GPL - this will use the same
  licensing terminology as ``gccxml_cc1plus`` above, thereby making
  *all* code in this fork, from this point forward, licensed similarly.

* Other files

  I intend to add some more scripts, schema definitions, etc. which, if
  not mentioned specifically in the sources, can be considered as licensed
  under the same terms as that of ``gccxml_cc1plus``, above.

