cat $1 | sed 's/^\s*\..*$//g; s/.*#.*//g;' | grep -v '^$' > $2
