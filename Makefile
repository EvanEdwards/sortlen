


bin/sortlen: src/sortlen.c src/print_manpage.h
	mkdir -p bin
	gcc -o bin/sortlen src/sortlen.c
	echo "Have a Nice Day!"

src/print_manpage.h: src/sortlen.1.md
	( cd src ; ./generate_header.sh -g print_manpage sortlen.1.md )

clean:
	rm -f bin/sortlen src/print_manpage.h 
	[ -d bin ] && rmdir bin || true

release: clean
	sed -n '/^[[:space:]]*$$/,$$p' <project.md |sed "s/{{version}}/$$( grep -m 1 ^version: project.md |cut -d: -f2 )/" >README.md
	echo '\n\n\n# Manual\n' >>README.md
	sed -n '/^[[:space:]]*$$/,$$p' <src/sortlen.1.md |sed 's/^#/##/' >>README.md
	cat README.md |cat -s |sponge README.md

