<<<<<<< HEAD
/// Use memdup_user rather than duplicating its implementation
/// This is a little bit restricted to reduce false positives
///
// Confidence: High
// Copyright: (C) 2010-2012 Nicolas Palix.  GPLv2.
// Copyright: (C) 2010-2012 Julia Lawall, INRIA/LIP6.  GPLv2.
// Copyright: (C) 2010-2012 Gilles Muller, INRIA/LiP6.  GPLv2.
=======
/// Use kmemdup_user rather than duplicating its implementation
/// This is a little bit restricted to reduce false positives
///
// Confidence: High
// Copyright: (C) 2010 Nicolas Palix, DIKU.  GPLv2.
// Copyright: (C) 2010 Julia Lawall, DIKU.  GPLv2.
// Copyright: (C) 2010 Gilles Muller, INRIA/LiP6.  GPLv2.
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
// URL: http://coccinelle.lip6.fr/
// Comments:
// Options: -no_includes -include_headers

virtual patch
<<<<<<< HEAD
virtual context
virtual org
virtual report

@depends on patch@
expression from,to,size,flag;
identifier l1,l2;
@@

-  to = \(kmalloc\|kzalloc\)(size,flag);
=======

@@
expression from,to,size,flag;
position p;
identifier l1,l2;
@@

-  to = \(kmalloc@p\|kzalloc@p\)(size,flag);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
+  to = memdup_user(from,size);
   if (
-      to==NULL
+      IS_ERR(to)
                 || ...) {
   <+... when != goto l1;
-  -ENOMEM
+  PTR_ERR(to)
   ...+>
   }
-  if (copy_from_user(to, from, size) != 0) {
-    <+... when != goto l2;
-    -EFAULT
-    ...+>
-  }
<<<<<<< HEAD

@r depends on !patch@
expression from,to,size,flag;
position p;
statement S1,S2;
@@

*  to = \(kmalloc@p\|kzalloc@p\)(size,flag);
   if (to==NULL || ...) S1
   if (copy_from_user(to, from, size) != 0)
   S2

@script:python depends on org@
p << r.p;
@@

coccilib.org.print_todo(p[0], "WARNING opportunity for memdep_user")

@script:python depends on report@
p << r.p;
@@

coccilib.report.print_report(p[0], "WARNING opportunity for memdep_user")
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
