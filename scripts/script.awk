#!/usr/bin/awk

BEGIN {
	flag = 0
}
{
	if ($1 ~ ":") {
		if (flag > 0) {
			printf "%s %d\n", lable, flag
			flag = 0
		}

		lable = $1
	} else {
		flag++
	}
}
END {
	if (flag > 0) {
		printf "%s %d\n", lable, flag
	}
}
