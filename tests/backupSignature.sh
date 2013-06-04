FILE=$HOME"/.signaturesource"
if [ -f $FILE ]
then
	mv $FILE $FILE".bak"
fi