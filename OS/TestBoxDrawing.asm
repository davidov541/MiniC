ldi $s0, 100
ldi $s1, 512
or $s0, $s1
wp $rr, 3
ldi $s0, 100
ldi $s1, 1024
or $s0, $s1
wp $rr, 3
ldi $s0, 2
ldi $s1, 1536
or $s0, $s1
wp $rr, 3
ldi $s0, 200
ldi $s1, 2560
or $s0, $s1
wp $rr, 3
ldi $s0, 200
ldi $s1, 2560
or $s0, $s1
wp $rr, 3
ldi $s0, 200
ldi $s1, 3072
or $s0, $s1
wp $rr, 3
ldi $s1, 4096
wp $s1, 3
infinite: j infinite