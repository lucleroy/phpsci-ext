--TEST--
Advanced test for 3-dimensional CArray slice with multiple indexes
--FILE--
<?php
$a = new CArray([[[1, 2], [3, 4]], [[1, 2], [3, 4]]]);
$b = $a[0][0];
$b->print();
--EXPECT--
[ 1  2 ]