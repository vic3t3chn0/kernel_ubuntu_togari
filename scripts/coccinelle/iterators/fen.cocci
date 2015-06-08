/// These iterators only exit normally when the loop cursor is NULL, so there
/// is no point to call of_node_put on the final value.
///
// Confidence: High
<<<<<<< HEAD
// Copyright: (C) 2010-2012 Nicolas Palix.  GPLv2.
// Copyright: (C) 2010-2012 Julia Lawall, INRIA/LIP6.  GPLv2.
// Copyright: (C) 2010-2012 Gilles Muller, INRIA/LiP6.  GPLv2.
=======
<<<<<<< HEAD
// Copyright: (C) 2010-2012 Nicolas Palix.  GPLv2.
// Copyright: (C) 2010-2012 Julia Lawall, INRIA/LIP6.  GPLv2.
// Copyright: (C) 2010-2012 Gilles Muller, INRIA/LiP6.  GPLv2.
=======
// Copyright: (C) 2010 Nicolas Palix, DIKU.  GPLv2.
// Copyright: (C) 2010 Julia Lawall, DIKU.  GPLv2.
// Copyright: (C) 2010 Gilles Muller, INRIA/LiP6.  GPLv2.
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
// URL: http://coccinelle.lip6.fr/
// Comments:
// Options: -no_includes -include_headers

virtual patch
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
virtual context
virtual org
virtual report

@depends on patch@
<<<<<<< HEAD
=======
=======

@@
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
iterator name for_each_node_by_name;
expression np,E;
identifier l;
@@

for_each_node_by_name(np,...) {
  ... when != break;
      when != goto l;
}
... when != np = E
- of_node_put(np);

<<<<<<< HEAD
@depends on patch@
=======
<<<<<<< HEAD
@depends on patch@
=======
@@
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
iterator name for_each_node_by_type;
expression np,E;
identifier l;
@@

for_each_node_by_type(np,...) {
  ... when != break;
      when != goto l;
}
... when != np = E
- of_node_put(np);

<<<<<<< HEAD
@depends on patch@
=======
<<<<<<< HEAD
@depends on patch@
=======
@@
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
iterator name for_each_compatible_node;
expression np,E;
identifier l;
@@

for_each_compatible_node(np,...) {
  ... when != break;
      when != goto l;
}
... when != np = E
- of_node_put(np);

<<<<<<< HEAD
@depends on patch@
=======
<<<<<<< HEAD
@depends on patch@
=======
@@
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
iterator name for_each_matching_node;
expression np,E;
identifier l;
@@

for_each_matching_node(np,...) {
  ... when != break;
      when != goto l;
}
... when != np = E
- of_node_put(np);
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

// ----------------------------------------------------------------------

@r depends on !patch forall@
//iterator name for_each_node_by_name;
//iterator name for_each_node_by_type;
//iterator name for_each_compatible_node;
//iterator name for_each_matching_node;
expression np,E;
identifier l;
position p1,p2;
@@

(
*for_each_node_by_name@p1(np,...)
{
  ... when != break;
      when != goto l;
}
|
*for_each_node_by_type@p1(np,...)
{
  ... when != break;
      when != goto l;
}
|
*for_each_compatible_node@p1(np,...)
{
  ... when != break;
      when != goto l;
}
|
*for_each_matching_node@p1(np,...)
{
  ... when != break;
      when != goto l;
}
)
... when != np = E
* of_node_put@p2(np);

@script:python depends on org@
p1 << r.p1;
p2 << r.p2;
@@

cocci.print_main("unneeded of_node_put",p2)
cocci.print_secs("iterator",p1)

@script:python depends on report@
p1 << r.p1;
p2 << r.p2;
@@

msg = "ERROR: of_node_put not needed after iterator on line %s" % (p1[0].line)
coccilib.report.print_report(p2[0], msg)
<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
