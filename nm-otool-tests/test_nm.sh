rm -rf tmp
mkdir tmp
rm diff

RED='\033[0;31m'
GREEN='\033[0;32m'

for filename in *
do
	if [ ! -d $filename ] 
	then
		if [ ! "$filename" == "test_nm.sh" ]
		then 
			nm $filename > tmp/real_$filename
			../ft_nm $filename > tmp/our_$filename
			DIFF=$(diff tmp/real_$filename tmp/our_$filename)
			if [ "$DIFF" != "" ] 
			then
				echo "${RED} $filename"
				echo $DIFF >> diff;
			else
				echo "${GREEN} $filename"
			fi
		fi
	fi
done
