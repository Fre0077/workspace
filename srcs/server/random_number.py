#! /usr/bin/env python3
from random import randint
import os

if __name__ == "__main__":
	print(
		"Content-type: text/plain\n\n"
		"<html>\n<body>\n"
		f"Was this your number? {randint(0, 100)}"
		"</body>\n</html>"
	)