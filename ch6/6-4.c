/*
Basic idea is to go back to using and fixed-size array of structs (instead of
a tree) and then create a array of pointers to them. We sort this pointer
array instead of the struct array and then print. Printing is O(n), sorting
O(log n), updating/inserting a word is O(n).

Book keeps update/insert using tree (while still constructing pointer array),
so it's O(log n).
*/