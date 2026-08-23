#!/bin/sh

test_dir=$(mktemp -d)

cleanup()
{
	rm -rf "$test_dir"
}

trap cleanup EXIT

pass=0
fail=0

test_command()
{
	"$@"
	if [ $? -eq 0 ]; then
		echo "PASS: $*"
		pass=$((pass+1))
	else 
		echo "FAIL: $*"
		fail=$((fail+1))
	fi
}

test_output()
{
	expected=$1
	shift

	output=$("$@")

	if [ "$output" = "$expected" ]; then
		echo "PASS: $*"
		pass=$((pass+1))
	else
		echo "FAIL: $*"
		echo " expected: $expected"
		echo " got: $output"
		fail=$((fail + 1))
	fi
}

test_command ./linix pwd
test_command ./linix help 
test_command ./linix touch "$test_dir/test.txt"

if [ -f "$test_dir/test.txt" ]; then
	echo "PASS: touch creates file"
	pass=$((pass + 1))
else 
	echo "FAIL: touch creates file"
	fail=$((fail + 1))
fi

test_command ./linix mkdir "$test_dir/testdir"

if [ -d "$test_dir/testdir" ]; then
	echo "PASS: mkdir creates directory"
	pass=$((pass + 1))
else
	echo "FAIL: mkdir creates directory"
	fail=$((fail + 1))
fi

test_command ./linix rm "$test_dir/test.txt"

if [ ! -e "$test_dir/test.txt" ]; then
	echo "PASS: rm removes file"
	pass=$((pass + 1))
else
	echo "FAIL: rm removes file"
	fail=$((fail + 1 ))
fi

echo "copy test data" > "$test_dir/src.txt"

test_command ./linix cp \
	"$test_dir/src.txt" \
	"$test_dir/dst.txt"

if [ -f "$test_dir/dst.txt" ] &&
	cmp -s "$test_dir/src.txt" "$test_dir/dst.txt"; then
		echo "PASS: cp copies file contents"
		pass=$((pass + 1))
else
	echo "FAIL: cp copies file contents"
	fail=$((fail + 1))
fi

echo "move test data" > "$test_dir/mv-src.txt"

test_command ./linix mv \
	"$test_dir/mv-src.txt" \
	"$test_dir/mv-dst.txt"

if [ ! -e "$test_dir/mv-src.txt" ] &&
	[ -f "$test_dir/mv-dst.txt" ]; then
		echo "PASS: mv moves file"
		pass=$((pass + 1))
else 
	echo "FAIL: mv moves file"
	fail=$((fail + 1))
fi

echo "cat test data" > "$test_dir/cat.txt"
test_output "cat test data" ./linix cat "$test_dir/cat.txt"

test_output "hello world" ./linix echo hello world

(
	cd "$test_dir" || exit 1

	echo "ls test" > ls-test.txt

	output=$("$OLDPWD/linix" ls)

	case "$output" in
		*ls-test.txt*)
			echo "PASS: ls lists file"
			pass=$((pass + 1))
			;;
		*)
			echo "FAIL: ls lists file"
			fail=$((fail + 1))
			;;
	esac
)

mkdir "$test_dir/lsdir"
echo "ls test" > "$test_dir/lsdir/hello.txt"

(
	cd "$test_dir" || exit 1

	output=$("$OLDPWD/linix" ls lsdir)

	case "$output" in
		*hello.txt*)
			echo "PASS: ls lists specified directory"
			pass=$((pass + 1))
			;;
		*)

			echo "FAIL: ls lists specified directory"
			fail=$((fail + 1))
			;;
	esac
)

echo
echo "Passed: $pass"
echo "Failed: $fail"

if [ "$fail" -ne 0 ]; then
	exit 1
fi

