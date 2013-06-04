TMPFILE=$HOME"/.signaturesource"
FILE=$TMPFILE".bak"
if [ -f $FILE ]
then
	mv $FILE $TMPFILE
fi