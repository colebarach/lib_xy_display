all: compile generate

compile: sort_and_format.c
	gcc sort_and_format.c -o sort_and_format.out

generate: parse_edges.py sort_and_format.out frames
	python parse_edges.py | ./sort_and_format.out > ../models.h
