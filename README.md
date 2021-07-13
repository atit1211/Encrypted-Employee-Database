# Encrypted-Employee-Database
store the information of people working in a company in a tree data structure and in a file using encryption

structure of the tree and the corresponding key value
l=0         l=1         l=2         l=3
000 
            001
                        011
                                    111
                                    211
                                    311
                        021
                                    121
                                    221
                                    321
                        031
                                    131
                                    231
                                    331
            002
                        012
                                    112
                                    212
                                    312
                        022
                                    122
                                    222
                                    322
                        032
                                    132
                                    232
                                    332
            003
                        013
                                    113
                                    213
                                    313
                        023
                                    123
                                    223
                                    323
                        033
                                    133
                                    233
                                    333
e.g of key values:
000
001
021
321

note:-deleteing a higher level node will delete all the lower level nodes also

ATTRIBUTES OF THE EMPLOYEE
1.key     3
2.level   5
3.salary  10
4.id      3
5.name    10
6.phno    10
7.email   20


OPTIONS FOR THE ADMIN:
1.ADDING THE NODES
1.1 ask the level 
1.2 traverse the tree and print of the level -1
1.3 print the parent options 
1.4 add the node to the options

2.DISPLAY THE INFO
2.1 ask for the emp info
2.2 traverse the tree to find it
2.3 print all the names under the found node

3.DELETING THE NODES
3.1 find the node and deallocat the node and all the
3.2 put the pionter as null

4.EXIT
