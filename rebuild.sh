rm -rf ./output
mkdir output
cd output
cmake ..
if [ $? -eq 0 ]; then
	make -j 4
	if [ $? -eq 0 ]; then
		cd codex.test
		./codex.test
	fi
fi
