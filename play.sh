#!/bin/bash

MYPIDFILE="$HOME/.play.sh.pid"
SOUNDSDIR="$HOME/media/music"

echo $$ > $MYPIDFILE

eval 'zenity --info --text "stop?"; test "$?" == "0" && echo $(kill -9 `cat /home/jalil/.play.sh.pid` && pkill mplayer)'&

LIST=( `find "$SOUNDSDIR" | tr ' ' '@'` )

for((;;)) do
  SEED=$((RANDOM % ${#LIST[*]}))
  MP3="$(echo ${LIST[$SEED]} | tr '@' ' ')"
  mplayer "$MP3"
  echo 'Playing next...'
  sleep 2s
done
